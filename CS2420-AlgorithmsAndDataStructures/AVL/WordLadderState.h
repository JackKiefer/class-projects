#ifndef WORD_LADDER_STATE_H
#define WORD_LADDER_STATE_H

#include <vector>
#include <string>
#include <iostream>

struct WordLadderState
{
	WordLadderState(std::vector<std::string> l, int p) :ladder(l), priority(p) {}
	std::vector<std::string> ladder;
	int priority;

	friend bool operator== (WordLadderState const & a, WordLadderState const & b)
	{
		return a.priority == b.priority;
	}

	friend bool operator< (WordLadderState const & a, WordLadderState const & b)
	{
		return a.priority < b.priority;
	}

	friend bool operator<= (WordLadderState const & a, WordLadderState const & b)
	{
		return (a < b || a == b);
	}

	friend bool operator> (WordLadderState const & a, WordLadderState const & b)
	{
		return !(a <= b);
	}

	friend bool operator>= (WordLadderState const & a, WordLadderState const & b)
	{
		return (a > b || a == b); 
	}

	friend bool operator!= (WordLadderState const & a, WordLadderState const & b)
	{
		return !(a == b); 
	}
	

};

#endif
