#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

bool ask(std::string q)
{
    std::cout << q << std::endl;
    std::string answer;

    for (;;)
    {
         std::getline(std::cin, answer);
         std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

         if (answer == "y" || answer == "yes") return true;
         else if (answer == "n" || answer == "no") return false;
         else
         {
             std::cout << "Invalid input" << std::endl;
         }
    }
}


struct TreeNode
{
    virtual void process(std::shared_ptr<TreeNode> &) = 0;
    virtual void write(std::ofstream &) = 0;
};


struct Question:TreeNode
{
    std::shared_ptr<TreeNode> yes;
    std::shared_ptr<TreeNode> no;
    std::string question;

    void process(std::shared_ptr<TreeNode> & ptr)
    {
        auto answer = ask(question);
        if (answer) yes->process(yes);
        else no->process(no);
    }

    void write(std::ofstream & o)
    {
        o << "Q:" << question << std::endl;
        yes->write(o);
        no->write(o);
    }
    
    Question(
        std::string q, std::shared_ptr<TreeNode> y = nullptr,
        std::shared_ptr<TreeNode> n = nullptr
        ) :question(q), yes(y), no(n) {}


};

class Answer : public TreeNode
{
public:
    std::string question;
   
    void process(std::shared_ptr<TreeNode> & ptr) override
    {
        auto a = ask("Are you thinking of " + question + "?");
        if (a) std::cout << "Aha! I win!" << std::endl;
        else getNewQuestion(ptr);
    }
    
    void write(std::ofstream & o)
    {
        o << "A:" << question << std::endl;
    }

    Answer(std::string q) :question(q){}
private:
    void getNewQuestion(std::shared_ptr<TreeNode> &);
};

void Answer::getNewQuestion(std::shared_ptr<TreeNode> & ptr)
{
    std::cout << "Diddly-darn! You got me. What were you thinking of?" << std::endl;
    std::string newAnswer;
    std::getline(std::cin, newAnswer);
    std::cout << "What question could I have asked to figure out what you were thinking of "
        << newAnswer << " and not " << question << "?" << std::endl;
    std::string newQuestion;
    std::getline(std::cin, newQuestion);

    std::cout << "Got it, thanks!" << std::endl << std::endl;

    auto answerNode = std::make_shared<Answer>(newAnswer);
    ptr = std::make_shared<Question>(newQuestion, answerNode, ptr);
}


#endif
