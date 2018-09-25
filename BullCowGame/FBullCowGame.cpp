#pragma once
#include <map>
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset();
}

int FBullCowGame::GetMaxTries() const
{
	std::map<int, int> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,16} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;
}

void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;

	const std::string HIDDEN_WORD = "planet"; //must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	bGameWon = false;

	MyCurrentTry = 1;
}

EGuessStatus FBullCowGame::CheckGuessValidity(std::string Guess)
{
	if (!IsIsogram(Guess)) //if guess is not isogram return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if guess isn't all lowercase return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) //if guess length is wrong return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}

// Receives a valid guess, increments tries and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{
	MyCurrentTry++;
	FBullCowCount BCCount;

	//loop through all the letters in the guess
	int HiddenWordLength = MyHiddenWord.length(); //Assuming same length as guess
	for (int i = 0; i < HiddenWordLength; i++)
	{
		//compare letters against the hidden word
		for (int j = 0; j < HiddenWordLength; j++)
		{
			//if they match
			if (Guess[i] == MyHiddenWord[j])
			{
				//increment bulls if they're in the same place
				//increment cows if they're not
				if (i == j)
				{
					BCCount.Bulls++;
				}
				else
				{
					BCCount.Cows++;
				}
			}
				
		}
	}

	if (BCCount.Bulls == HiddenWordLength)
	{
		bGameWon = true;
	}
		
	return BCCount;
}

bool FBullCowGame::IsIsogram(std::string Word) const
{
	if (Word.length() <= 1)
	{
		return true;
	}

	//Create map of letters
	std::map<char, bool> LettersSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter])
		{
			return false; //not an isogram
		}
		else
		{
			LettersSeen[Letter] = true; //Add the letter to the map
		}
	}
		
	return true;
}

bool FBullCowGame::IsLowercase(std::string Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}

	return true;
}
