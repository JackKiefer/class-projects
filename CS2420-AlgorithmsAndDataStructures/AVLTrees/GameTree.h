// Implementation of the Word Ladder game

#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include "List.hpp"
#include "WordLadderState.h"
#include "AvlTree.h"

class Game
{
public:
  Game() :file("dictionary.txt") {}       
  Game(std::string const & f) :file(f) {} 
  bool listWords();
  void play();
  void play(std::string s);
  void play(std::string s, std::string t);
	unsigned int enqs;
	unsigned int deqs;
private:
  int randInt(int);
	AvlTree<WordLadderState> tree;
	std::string file;
  std::string start;
  std::string target;
  bool m_gotTarget;
  bool m_impossible;
  bool m_badStart;
  bool m_badTarget;
  bool m_unmatchedLengths;
  std::vector<std::string> dictionary = getDictionary(file);

  bool wordsPass();
  std::vector<std::string> getDictionary(std::string const &);
  int getRand() { return getRand(randInt(12)); }
  int getRand(int);
	int getPriority(std::vector<std::string> const &);
  void process();
  void addLadders();
  void display();
  void error();
  void reset();
  std::vector<std::string> getOneAways(std::vector<std::string> const& ladder);
  bool findWord(std::string const & word) {
    return findWord(word, 0, dictionary.size() - 1); }
  bool findWord(std::string const &, int, int);
};

void Game::reset() // Resets the win-condition booleans and the dictionary
{
  m_gotTarget = false;
  m_impossible = false;
  m_badStart = false;
  m_badTarget = false;
  m_unmatchedLengths = false;
  
  dictionary = getDictionary(file);
  tree.makeEmpty();
}

void Game::display() // Prints final ladder
{
  auto finalLadder = (tree.findMin()).ladder;
  std::cout << 
    "Path of length " << finalLadder.size() << " from " << start 
      << " to " << target << ": ";

	std::ostringstream oss;

	oss << '[';
	for (auto i = 0u; i < finalLadder.size() - 1; ++i) oss << finalLadder[i] << ',';
  oss << finalLadder.back() << ']';
	std::cout << oss.str();
}


void Game::error() 
{
  std::cout << "Failure:" << std::endl;
  if (m_unmatchedLengths) 
  { 
    std::cout << 
      "The length of \"" << target << "\" does not match the length of \"" 
      << start << "\"" << std::endl;
  }
  if (m_badStart)
  {
    std::cout << "\"" << start << "\" not found in dictionary" << std::endl;
  }
  if (m_badTarget)
  {
    std::cout << "\"" << target << "\" not found in dictionary" << std::endl;
  }
  if (m_impossible)
  {
    std::cout << "No ladder found from " << start << " to " 
      << target << std::endl;
  }
}

std::vector<std::string> Game::getOneAways   // Retrieves a vector filled with
  (                                          // all one-away words
    std::vector<std::string> const & ladder
  )
{
  auto word = ladder[ladder.size() - 1];
  std::vector<std::string> oneAways;

  for(auto&& c : word)
  {
    auto original = c;
    for(char letter = 'a'; letter <= 'z'; ++letter)
    {
      c = letter;
      if (findWord(word))
      {
        oneAways.push_back(word);
      }
      if (word == target)
      {
        oneAways.push_back(word);
      }
    }
    c = original;
  }
  return oneAways;
}

int Game::getPriority(std::vector<std::string> const & ladder)
{
	int incorrect = 0;
	auto lastWord = ladder.back();

  for(int i = 0; i < lastWord.length(); ++i)	
	{
		if(lastWord[i] != target[i]) ++incorrect;	
	}

	return ladder.size() + incorrect;
}

void Game::addLadders() 						// Fetches
{                                                               // word ladders
	auto state = tree.removeMin();
	++deqs;

	auto current = state.ladder;
  auto oneAways = getOneAways(current);


  for(int i = 0; i < oneAways.size(); ++i)
  {
    auto word = oneAways[i];
    std::vector<std::string> newLadder = current;
    newLadder.push_back(word);

		auto pri = getPriority(newLadder);
		if (word == target) pri = 0;
		
		tree.insert(WordLadderState(newLadder, pri));
		++enqs;

    if (word == target) { m_gotTarget = true; return; }
  }


  if (tree.isEmpty()) { m_impossible = true  ; return; }
  addLadders();
}

bool Game::wordsPass() // Checks to see if words are valid for play
{
  if (start.length() != target.length())  
  {
    m_unmatchedLengths = true;
    return false;
  }
  if ( !findWord(start) )
  {
    m_badStart = true;
    return false;
  }
  if ( !findWord(target) )
  {
    m_badTarget = true;
    return false;
  }

  return true;
}


void Game::process() // Gets the ball rolling
{
	enqs = 0;
	deqs = 0;
  if ( wordsPass() )
  {
    std::vector<std::string> ladder;
    ladder.push_back(start);

		WordLadderState first(ladder,1);
		tree.insert(first);
		++enqs;

    addLadders();
    if(m_gotTarget) display();
    else error();
  }
  else error();
  std::cout << std::endl;
  reset();
}

void Game::play() // Play with two random words
{
  start = dictionary[getRand()];
  target = dictionary[getRand(start.length())];
  start.pop_back();
  target.pop_back();
  process();
}

void Game::play(std::string s) // Play with one random word
{
  start = s;
  target = dictionary[getRand(s.length() + 1)];
  target.pop_back();
  process();
}

void Game::play(std::string s, std::string t) // Play with both words provided
{
  start = s;
  target = t;
  process();
}

bool Game::findWord(std::string const & word, int first, int last)
{                           // Binary search to check if word is in dictionary 
  if (first <= last)
  {
    auto mid = (first + last) / 2;
    if (word + "\r" == dictionary[mid])
    {
      if (word != target) dictionary[mid] = '*' + dictionary[mid];
      return true; 
    }
    else if (word < dictionary[mid]) return findWord(word, first, mid - 1);
    else if (word > dictionary[mid]) return findWord(word, mid + 1, last);
  }
  else return false;
}

int Game::getRand(int length) // Gets the index of a proper-length random word
{
  auto randomIndex = randInt(dictionary.size() - 1);
  std::string word = dictionary[randomIndex];
  int extraIndexes = 0;
  while (word.size() != length) // If the randomly selected word is the 
  {                             // incorrect length, iterates linearly
   ++extraIndexes;              // until an acceptable word is found.
   word = dictionary[randomIndex + extraIndexes];
  }
  return randomIndex + extraIndexes;
}

int Game::randInt(int i) // Uses a Mersenne-Twister to return a random int
{
  static std::random_device rd;
  static std::mt19937 engine(rd());
  std::uniform_int_distribution<> dist(2, i);
  return dist(engine);
}

bool Game::listWords() // List the first 10 words from the dictionary
{
  if (dictionary.size() < 10)
  {
    std::cout << 
      "Error: Dictionary is either too small or failed to initialize" 
      << std::endl;
    return false;
  }
  
  std::cout << "Dictionary read in. Size:" << dictionary.size() << std::endl;

  for (int i = 0; i < 10; ++i) std::cout << dictionary[i] << std::endl;
  std::cout << std::endl;
  return true;
}

std::vector<std::string> Game::getDictionary(std::string const & filename)
{                            // Reads dictionary into a vector of strings
  std::vector<std::string> dictionary;
  std::ifstream file (filename);
  std::string word;

  while(getline(file, word)) dictionary.push_back(word); 
  
  
  return dictionary;
}

#endif
