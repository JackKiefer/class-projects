#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "Tree.hpp"

namespace
{
    const auto VERSION = "1.0.0";
}

std::ofstream fout("tree_data.txt");

void welcomeText()
{
    std::cout << std::endl <<
   "         ,/   *" << std::endl <<
   "      _,\'/_   | "  << std::endl <<            
   "      `(\")\' ,\'/   Welcome to" << std::endl <<
   "   _ _,-H-./ /    ╔═╗┬ ┬┌─┐┌─┐┌─┐   ╦┌┬┐  ╦ ╦┬┌─┐┌─┐┬─┐┌┬┐" << std::endl <<
   "   \\_\\_\\.   /     ║ ╦│ │├┤ └─┐└─┐───║ │   ║║║│┌─┘├─┤├┬┘ ││" << std::endl <<
   "     )' |  (      ╚═╝└─┘└─┘└─┘└─┘   ╩ ┴   ╚╩╝┴└─┘┴ ┴┴└──┴┘" << std::endl <<
   "  __/   H   \\__                                v" << VERSION << std::endl <<
   "  \\    /|\\    /" << std::endl <<
   "   `--\'|||`--\'" << std::endl <<
   "hh    ==^==" << std::endl << std::endl << 
   "Think of a noun, and I, the guess-it wizard, will magically guess what's on your mind!"
	<< std::endl;
}

int main()
{
    welcomeText();

    std::string question = "Are you ready to begin?";

    std::shared_ptr<TreeNode> BST = std::make_shared<Answer>("a penguin");
    while (ask(question))
    {
        BST->process(BST);
        question = "Do you want to play again?";
    }
    BST->write(fout);
}
