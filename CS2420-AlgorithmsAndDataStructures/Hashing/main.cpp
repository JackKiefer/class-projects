// A word game that utilizes a hash table

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HashTable.h"

// Pair containing a word and how many times it's been used before
class Pair
{
public:
	std::string word;
	int count;
	Pair(std::string w = "no word", int c = 0){
		word = w;
		count = c; 
	}
	std::string toString(){
		std::stringstream ss;
		ss << word << " " << count;
		return ss.str();
	}	
};

// Allows user to input which file they'd like to open
int getGameNum()
{
	int gameNum;
	std::cout << "Enter the game number to play (between 0 and 4):" << std::endl;
	std::cin >> gameNum;
	return gameNum;
}

// Opens user-selected file
void getGame(std::ifstream & fin)
{
	auto gameNum = getGameNum();
	std::ostringstream oss;
	oss << "game" << gameNum << ".txt";
	auto filename = oss.str();
	fin.open(filename);
	std::cout << "-- " << filename << " opened --" << std::endl << std::endl;
}

// Allows user to input output frequency
int getOutputFrequency()
{
	int outFreq;
	std::cout 
		<< "Enter output frequency (number of words between each printing of the score):" 
		<< std::endl;

	std::cin >> outFreq;
	std::cout << std::endl;
	return outFreq;
}

// Calculates score multiplier based on length
// See table in assignment doc
int getLengthValue(std::string & word)
{
	auto len = word.length();
	if (len == 1) return 0;
	if (len <= 8) return len - 2;
	if (len > 8) return 6;
}

// Calculates score multiplier based on letter value.
// See table in assignment doc
int getLetterValue(std::string & word)
{
	static const std::vector<int> values = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

	auto score = 0;

	for (auto i = 0u; i < word.size(); ++i)
	{
		auto c = word.at(i);

		int sub = c-'a'; // Gets letter number from 0-25

		score += values[sub];
	}

	return score;
}

// Calculates score multiplier based on number of times the word has already been used
// See table in assignment doc
int getBonus(int count)
{
	if (count == 1) return 5;
	if (count <= 4) return 4;
	if (count <= 7) return 3;
	if (count <= 8) return 2;
	if (count <= 10) return 2;
	return 1;
}

// Calculates the score of a given word
int getScore(std::string & word, int count)
{
	auto letter = getLetterValue(word);
	auto length = getLengthValue(word);
	auto bonus = getBonus(count);
	return letter * length * bonus;
}

// Adds words to the hashtable, or modifies their count if they're already there
void addWords(std::string & word, HashTable<std::string, Pair> & table, int & repeats, std::vector<int> & lengths)
{
	Pair * p = table.find(word);

	if (!p) 
	{ 
		auto newPair = new Pair(word, 1);
		table.insert(word, newPair);
		repeats = newPair->count;
	}
	else 
	{
		p->count++;
		repeats = p->count;
	}

	++lengths[word.length()];
}

// Calculates word scores, adds them up, and displays intermittent score updates
void playGame(unsigned int & gameScore, unsigned int & wordCount, std::string & word, int outFreq, int & repeats)
{
	auto wordScore = getScore(word, repeats); 
	gameScore += wordScore;
	++wordCount;

	if (wordCount % outFreq == 0)
	{
		std::cout << wordCount << " words played, total score: " << gameScore << std::endl;
	}
	
}

// Displays the number of words of each length
void reportLengths(std::vector<int> & lengths)
{
	for (auto i = 0u; i < lengths.size(); ++i)
	{
		if (lengths[i] > 0)
		{
			std::cout << lengths[i] << " words of length " << i << std::endl;
		}
	}
}

int main()
{
	std::string word;                     // 
	HashTable<std::string, Pair> table;   //
                                        //  Initialize variables
	std::ifstream fin;                    //  and get user input
	getGame(fin);                         //
	auto outFreq = getOutputFrequency();  //
                                        //
	unsigned int gameScore = 0;           //
	unsigned int wordCount = 0;           //
	std::vector<int> lengths(100, 0);     //

	while (fin >> word) // Begin reading words from file
	{
		int repeats;
		addWords(word, table, repeats, lengths);
		playGame(gameScore, wordCount, word, outFreq, repeats);
	}

	std::cout << "Final score: " << gameScore << std::endl;
	reportLengths(lengths);
	
//	 std::cout << table.toString() << std::endl; //  Display first few contents of the hash table
}
