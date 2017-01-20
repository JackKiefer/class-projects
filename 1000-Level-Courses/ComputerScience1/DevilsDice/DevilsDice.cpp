// Devil's Dice: a simple command-line dice game

#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <limits>

namespace {
	std::string playerOneName; // SUPER DUPER EVIL GLOBAL VARIABLES 
	std::string playerTwoName;
	int WINNING_SCORE = 100;
	int DISPLAY_SCALE = 5;
	std::string versionNumber = "v1.4.1";
	int playerOneScore = 0; // starting scores for
	int playerTwoScore = 0; // players one and two
	bool playerOneTurn = true; // player one goes first
	std::string playerName; // changes depending on whose turn it is
}

char getAnswer() // Retrieves the answer to a question
{
	char answer;
	std::cin >> answer;
	std::string buf;
	std::getline(std::cin, buf);
	return answer;
}


void errorMessage()
{
	std::cout << "Error: Invalid input" << std::endl;
}

bool askQuestion(std::string question) // Asks a question. Returns true if "yes", returns false if "no"
{
	while (true)
	{
		std::cout << question << std::endl;
		char answer = getAnswer();
		if (answer == 'y' || answer == 'Y')
		{
			return true;
		}
		else if (answer == 'n' || answer == 'N')
		{
			return false;
		}
		else
		{
			errorMessage();
		}
	}
}

void titleScreen()
{
	std::cout << "            ,    ,     /\\   /\\" << std::endl;
	std::cout << "           /( /\\ )\\   _\\ \\_/ /_" << std::endl;
	std::cout << "           |\\_||_/|  < \\_   _/ >" << std::endl;
	std::cout << "           \\______/   \\|0   0|/" << std::endl;
	std::cout << "  ____       _\\/_    _(_  ^  _)_       _____" << std::endl;
	std::cout << " /\\\' .\\     ( () )  /`\\|V\"\"\"V|/`\\     / .  /\\" << std::endl;
	std::cout << "/: \\___\\      {}    \\  \\_____/  /    /____/..\\" << std::endl;
	std::cout << "\\' / . /      ()    /\\   )=(   /\\    \\\'  \'\\  /" << std::endl;
	std::cout << " \\/___/       {}   /  \\_/\\=/\\_/  \\    \\\'__\'\\/ " << std::endl;
	std::cout << std::endl;
	std::cout << "-+-------------+- WELCOME TO -+-------------+-" << std::endl;
	std::cout << "     _            _ _ _          _ _          " << std::endl;
	std::cout << "  __| | _____   _(_) ( )__    __| (_) ___ ___ " << std::endl;
	std::cout << " / _` |/ _ \\ \\ / / | |/ __|  / _` | |/ __/ _ \\" << std::endl;
	std::cout << "| (_| |  __/\\ V /| | |\\__ \\ | (_| | | (_|  __/" << std::endl;
	std::cout << " \\__,_|\\___| \\_/ |_|_||___/  \\__,_|_|\\___\\___|" << std::endl;
	std::cout << "                                      " << versionNumber << std::endl;
	std::cout << std::endl;
}

void instructions()
{
	std::cout << std::endl << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl << std::endl;
	std::cout << "Welcome to the ultimate battle with the Devil for the fate of your eternal soul." << std::endl;
	std::cout << "Each turn, a player repeatedly rolls a die until either a 1 is rolled or the player decides to \"hold\":" << std::endl;
	std::cout << "- If the player rolls a 1, they score nothing and it becomes the next player's turn." << std::endl;
	std::cout << "- If the player rolls any other number, it is added to their turn total and the player's turn continues." << std::endl;
	std::cout << "- If a player chooses to \"hold\", their turn total is added to their score, and it becomes the next player's turn." << std::endl;
	std::cout << "The first player to score 100 or more points wins." << std::endl;
	std::cout << std::endl << "-----------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

void about()
{
	std::cout << std::endl;
	std::cout << "---------------------------------------" << std::endl << std::endl;
	std::cout << "            Devil's Dice " << versionNumber << std::endl;
	std::cout << "        Programmed by Jack Kiefer" << std::endl; 
	std::cout << "    Utah State University, May 2016" << std::endl;
	std::cout << "Special thanks to Dr. Kenneth Sundberg" << std::endl;
	std::cout << "            ~ ~ Go Aggies! ~ ~" << std::endl << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << std::endl;
}

void customGame()
{
	int newWinningScore;
	int newDisplayScale;
	std::cout << std::endl << "Warning: improper usage of these settings will break the program." << std::endl;
	std::cout << std::endl << "Enter score to play to (default is 100):" << std::endl;
	std::cin >> newWinningScore;
	WINNING_SCORE = newWinningScore;
	std::cout << std::endl << "Enter increment scale for the scoreboard (default is 5):" << std::endl;
	std::cin >> newDisplayScale;
	DISPLAY_SCALE = newDisplayScale;
	std::cout << std::endl << "New parameters acceped" << std::endl << std::endl;
	return;
}

int rollDie() // Generates a random number from 1 to 6. do you even arcane bro
{
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<> die(1, 6);
	return die(engine);
}

void displayLogic(int score1, int score2, int i) // Generates the player's scores as bar graphs on the scoreboard
{
	if ((score1 % DISPLAY_SCALE) + i == score1)
	{
		std::cout << score1;
	}
	if (i <= (score1 - DISPLAY_SCALE))
	{
		std::cout << "##";
	}
	if ((score2 % DISPLAY_SCALE) + i == score2)
	{
		std::cout << "\t " << score2;
	}
	if (i <= (score2 - DISPLAY_SCALE))
	{
		std::cout << "\t @@";
	}
}

void display(int score1, int score2) // Displays the scoreboard in between rounds
{
	std::cout << " ____________________" << std::endl;
	std::cout << "|_______SCORES_______|" << std::endl;
	for (int i = WINNING_SCORE; i >= DISPLAY_SCALE; i -= DISPLAY_SCALE)
	{
		std::cout << "  " << i << "\t";
		displayLogic(score1, score2, i);
		std::cout << std::endl;
	}
	std::cout << " _0_____##_______@@__" << std::endl;
	std::cout << "|____________________|" << std::endl;
}

void getNames() // Gets the players' names
{
	std::cout << std::endl;
	std::cout << "Player #, enter your name: ";
	std::getline(std::cin, playerOneName);
	std::cout << "Hello, " << playerOneName << "." << std::endl << std::endl;
	std::cout << "Player @, enter your name: ";
	std::getline(std::cin, playerTwoName);
	std::cout << "Hello, " << playerTwoName << "." << std::endl << std::endl;
}

void menuText()
{
	std::cout << "   MENU:" << std::endl;
	std::cout << "[1| PLAY] [2| INSTRUCTIONS] [3| OPTIONS] [4| ABOUT] [5| EXIT]" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter an option:" << std::endl;
}

void menu() // Main Menu for the game
{
	while (true)
	{
		menuText();
		char option = getAnswer();
		if (option == '1' || option == 'p' || option == 'P') // starts the game
		{
			return;
		}
		else if (option == '2' || option == 'i' || option == 'I') // displays instructions
		{
			instructions();
		}
		else if (option == '3' || option == 'o' || option == 'O') // options
		{
			customGame();
		}
		else if (option == '4' || option == 'a' || option == 'A') // displays credits
		{
			about();
		}
		else if (option == '5' || option == 'e' || option == 'E') // prompts an exit to the program, but entices the user to play again
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			errorMessage();
		}
	}
}

void winMessages()
{
	if (playerOneScore >= WINNING_SCORE)
	{
		std::cout << std::endl;
		std::cout << "~~~~~ " << playerOneName << " wins! ~~~~~" << std::endl;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "~~~~~ " << playerTwoName << " wins! ~~~~~" << std::endl;
	}
}

void determineName() // Determines the name of the player whose turn it is
{
	if (playerOneTurn)
	{
		playerName = playerOneName;
	}
	else
	{
		playerName = playerTwoName;
	}
}

void dieGraphic(int rollNumber)
{
	switch (rollNumber)
	{
	case 1:
		std::cout << " _____" << std::endl;
		std::cout << "|     |" << std::endl;
		std::cout << "|  o  |" << std::endl;
		std::cout << "|_____|" << std::endl;
		break;
	case 2:
		std::cout << " _____" << std::endl;
		std::cout << "|    o|" << std::endl;
		std::cout << "|     |" << std::endl;
		std::cout << "|o____|" << std::endl;
		break;
	case 3:
		std::cout << " _____" << std::endl;
		std::cout << "|    o|" << std::endl;
		std::cout << "|  o  |" << std::endl;
		std::cout << "|o____|" << std::endl;
		break;
	case 4:
		std::cout << " _____" << std::endl;
		std::cout << "|o   o|" << std::endl;
		std::cout << "|     |" << std::endl;
		std::cout << "|o___o|" << std::endl;
		break;
	case 5:
		std::cout << " _____" << std::endl;
		std::cout << "|o   o|" << std::endl;
		std::cout << "|  o  |" << std::endl;
		std::cout << "|o___o|" << std::endl;
		break;
	case 6:
		std::cout << " _____" << std::endl;
		std::cout << "|o   o|" << std::endl;
		std::cout << "|o   o|" << std::endl;
		std::cout << "|o___o|" << std::endl;
		break;
	}
}

int playTurn() // Logic dictating each individual turn
{
	int roundScore = 0;
	determineName();
	std::cout << "It's " << playerName << "'s turn" << std::endl;
	while (askQuestion("Roll the die? (y/n)"))
	{
		int roll = rollDie();
		std::cout << std::endl << playerName << " rolls a " << roll << std::endl;
		dieGraphic(roll);
		std::cout << std::endl;

		if (roll == 1)
		{
			std::cout << "Zing! " << playerName << " scores nothing this round" << std::endl;
			std::cout << "Press Enter to continue..." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ARCANE ENTER TO CONTINUE. CHECK HERE IF SOMETHING BREAKS
			roundScore = 0;
			return roundScore;
		}
		else
		{
			roundScore = roundScore + roll;
			std::cout << playerName << "'s score this round is now " << roundScore << std::endl << std::endl;
		}
	}
	std::cout << std::endl << playerName << " decides to hold" << std::endl;
	return roundScore;
}

void playGame() // Logic dictating the overall rules of the game
{
	std::cout << playerOneName << " goes first" << std::endl;
	while (playerOneScore < WINNING_SCORE && playerTwoScore < WINNING_SCORE)
	{
		if (playerOneTurn)
		{
			playerOneScore += playTurn();
		}
		else
		{
			playerTwoScore += playTurn();
		}
		playerOneTurn = !playerOneTurn; // swaps turns back and forth
		display(playerOneScore, playerTwoScore);
		std::cout << std::endl;
	}
	winMessages();
}

void testDisplay() // Used for testing changes made to the scoreboard
{
	display(34, 56);
	display(0, 98);
	display(55, 42);
}

int main()
{
	titleScreen();
	menu();
	while (askQuestion("Start a new game? (y/n)"))
	{
		getNames();
		playGame();
		playerOneScore = 0;
		playerTwoScore = 0;
	}
	return EXIT_SUCCESS;
}
