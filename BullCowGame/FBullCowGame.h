/* Game logic code. Simple guess the word game based on Mastermind.*/

#pragma once
#include <string>

struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();

	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;

	void Reset();
	EGuessStatus CheckGuessValidity(std::string);
	FBullCowCount SubmitValidGuess(std::string);

private:
	int MyCurrentTry;
	bool bGameWon;
	std::string MyHiddenWord;

	bool IsIsogram(std::string) const;
	bool IsLowercase(std::string) const;
};
