#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/param.h>
#include "timer.hpp"

bool isIOredir(char delim) { return delim == '>' || delim == '<' || delim == '|'; }
bool isDelim(char delim) { return delim == ' ' || delim == '\t' || isIOredir(delim); }

// Parses a string into arguments and places them in a vector
void parseInput(std::string & line, std::vector<std::string> & words)
{
  auto cur = line.begin();

  while (cur != line.end())
  {
    auto next = std::find_if(cur, line.end(), isDelim);
    std::string cmd(cur, next);
    words.push_back(cmd);

    cur = next;
    if (cur != line.end())
    {
      while (!isIOredir(*cur) && isDelim(*cur)) ++cur; 
      if (isIOredir(*cur)) words.emplace_back(1, *cur);
      cur = std::find_if(cur, line.end(), [](char c){ return !isDelim(c); });
    }
  }
}

// Retrieves user input
void getInput(std::vector<std::string> & words)
{
  std::string line;
  std::getline(std::cin,line);
  parseInput(line, words);
}

// Converts a vector of strings to a char* const* suitable for execvp
// Based on the design of an algorithm by Karel Lodewijk
// http://www.dreamincode.net/forums/topic/251269-converting-vector-string-to-char-const/
char* const* toCharConst(const std::vector<std::string> & words)
{
  char** args = new char*[words.size()];
  for (auto i = 0u; i < words.size(); ++i)
  {
    args[i] = new char[words[i].size() + 1];
    strcpy(args[i], words[i].c_str());
  }
  args[words.size()] = nullptr;
  return args;
}

// Prints the colorful shell prompt
void printPrompt(char* hostname)
{
    std::cout << "\e[1m" << "\033[34m" 
    << getenv("USER") << '@' << hostname << ':' << "\033[0m" 
    << "\e[1m\033[33m" << get_current_dir_name() << "$ " << "\033[0m";
}

enum boolName { DO_FORK, SKIP_FORK };

bool checkFuncs(bool&,std::vector<std::string>&,std::vector<std::vector<std::string>>&,Timer&);

// Executes history command
bool execHistory(std::vector<std::string> & words, std::vector< std::vector<std::string> > & history,
bool & exitCalled, Timer & timer)
{
  std::string arg2;
  if (words.size() > 1) arg2 = words[1];

  if (arg2[0] == '^')
  {
    arg2.erase(0,1);
    auto index = std::stoi(arg2);
    words = history[index - 1];
    if (checkFuncs(exitCalled, words, history, timer)) return SKIP_FORK;
    else return DO_FORK; 
  }
  else 
  {
    for (auto i = 1u; i <= history.size(); ++i)
    {
      std::cout << i << "\t";
      for (auto&& s : history[i - 1])
      {
        std::cout << s << ' ';
      }
      std::cout << std::endl;
    }
  }
  return SKIP_FORK;
}


/**
 *  Handles special-case arguments. Returns SKIP_FORK if no forking is required
 *  following the execution of the command.
 */
bool checkFuncs(bool & exitCalled, std::vector<std::string> & words, 
std::vector< std::vector<std::string> > & history, Timer & timer)
{
  if (words.empty()) return SKIP_FORK;

  auto arg1 = words[0];

  if (arg1 == "exit") 
  {
    exitCalled = true;
    exit(1);
    return SKIP_FORK;
  }
  else if (arg1 == "cd")
  {
    auto rc = chdir(words[1].c_str());
    if (rc < 0) perror("cd failed");
    return SKIP_FORK;
  }

  else if (arg1 == "history")
  {
    return execHistory(words, history, exitCalled, timer);
  }

  else if (arg1 == "ptime")
  {
    std::cout << "Time spent executing child processes: " << timer.toString() << std::endl;
    return SKIP_FORK;
  }
  
  return DO_FORK;
}

/* Handles piping and IO redirection */
void redirectPipe(std::vector< std::vector<std::string> > & commands, bool redirIn, bool redirOut, std::string inFile, std::string outFile )
{
  int fDs[2][2];
  fDs[0][0] = 0;
  fDs[0][1] = 0;
  fDs[1][0] = 0;
  fDs[1][1] = 0;

  auto pipeStatus0 = pipe(fDs[0]);
  auto pipeStatus1 = pipe(fDs[1]);

  auto argID = 0u;

  if ( pipeStatus0 < 0 || pipeStatus1 < 0)
  {
    perror("Pipe failed");
    exit(EXIT_FAILURE);
  }

  for (auto&& args : commands)
  {
    auto pipeStatus = pipe(fDs[1]);

    if (pipeStatus < 0)
    {
      perror("pipe returned negative");
      exit(EXIT_FAILURE);
    }

    auto pid = fork();

    if (pid < 0)
    {
      perror("pid less than 0");
      exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
      if (argID == 0 && commands.size() > 1)
      {
        dup2(fDs[1][1], STDOUT_FILENO);
        if (redirIn)
        {
          auto inFd = open(inFile.c_str(), O_RDWR, 0200 | 0400);
          dup2(inFd, STDIN_FILENO);
          close(inFd);
        }
      }
      else if (argID == commands.size() - 1 && commands.size() > 1)
      {
        dup2(fDs[0][0], STDIN_FILENO);
        if (redirOut)
        {
          auto outFd = open(outFile.c_str(), O_RDWR | O_CREAT, 0200 | 0400);
          dup2(outFd, STDOUT_FILENO);
          close(outFd);
        }
      }
      else if (argID == 0 && commands.size() - 1 < 1) 
      {
        if (redirOut)
        {
          auto outFd = open(outFile.c_str(), O_RDWR | O_CREAT, 0200 | 0400);
          dup2(outFd, STDOUT_FILENO);
          close(outFd);
        }
        else if (redirIn)
        {
          auto inFd = open(inFile.c_str(), O_RDWR, 0200 | 0400);
          dup2(inFd, STDIN_FILENO);
          close(inFd);
        }
      }
      else
      {
        dup2(fDs[0][0], STDIN_FILENO);
        dup2(fDs[1][1], STDOUT_FILENO);
      }
      close(fDs[0][1]);
      close(fDs[1][1]);

      execvp(args[0].c_str(), toCharConst(args));
      perror("hyoosten we haev a problen");
      exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
      int status;
      waitpid(pid, &status, 0);
      close(fDs[1][1]);
      std::swap(fDs[0], fDs[1]);
    }

    ++argID;
  }
}

void removeFalseCommand(std::vector< std::vector<std::string > > & commands, std::string target)
{
  std::vector<std::string> vec = { target };
  commands.erase(std::remove(commands.begin(),commands.end(), vec), commands.end());
}

bool redirectIO(std::vector<std::string> & words, std::vector < std::vector<std::string> > & commands)
{
  std::string inFile = "";
  std::string outFile = "";
  bool redirIn = false;
  bool redirOut = false;
  bool pipePresent = false;

  for (auto i = 0u; i < words.size(); ++i)
  {
    if (words[i] == ">")
    {
      redirOut = true;
      outFile = words[i+1];
      removeFalseCommand(commands, outFile);
    }
    else if (words[i] == "<")
    {
      redirIn = true;
      inFile = words[i+1];
      removeFalseCommand(commands, inFile);
    }
    else if (words[i] == "|")
    {
      pipePresent = true;
    } 
  }

  if (pipePresent || redirIn || redirOut) 
  {
    redirectPipe(commands, redirIn, redirOut, inFile, outFile);
    return SKIP_FORK;
  }

  return DO_FORK;
}

std::vector< std::vector<std::string> > separate(std::vector<std::string> & words)
{
  std::vector< std::vector<std::string> > separated;
  auto cur = words.begin();

  for (auto i = 0u; i < words.size(); ++i)
  {
    auto c = words[i];
    if (c == "|" || c == "<" || c == ">")
    {
      auto end = words.begin() + i;

      std::vector<std::string> newVec(cur, end);
      separated.push_back(newVec);

      cur = end + 1; 
    }
  }

  separated.emplace_back(cur, words.end());


  return separated;
}

int main()
{
  char hostname[1024];
  gethostname(hostname, 1024);
  bool exitCalled = false;
  std::vector< std::vector<std::string> > history;
  Timer timer;

  while (!exitCalled)
  {
    printPrompt(hostname);

    std::vector<std::string> words;
    getInput(words);
    auto commands = separate(words);
    history.push_back(words);
  
    if (!redirectIO(words, commands) && !checkFuncs(exitCalled, words, history, timer)) 
    {
      auto args = toCharConst(words);

      auto pid = fork();

      if (pid < 0)
      {
        perror("pid less than 0");
        exit(1);
      }
      if (pid == 0)
      {
        execvp(args[0], args); 
        perror("Exec failed");
        exit(EXIT_FAILURE);
      }
      if (pid > 0)
      {
        int status;
        timer.start();
        waitpid(pid, &status, 0);
        timer.end();
        timer.addToTotal();
      }
    }
  }
}
