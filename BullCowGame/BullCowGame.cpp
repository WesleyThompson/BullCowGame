/*
This is the console interface for the game. All user input and
view stuff is in here.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
std::string GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Game model we use across plays

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while(bPlayAgain);
	

	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "\\|/          (__)" << "\n";
	std::cout << "     `\\------(oo)" << "\n";
	std::cout << "       ||    (__)" << "\n";
	std::cout << "       ||w--||     \\|/" << "\n";
	std::cout << "   \\|/" << "\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
}

//Loop continually until the user gives a valid guess
std::string GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	std::string Guess = "";
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		Guess = "";

		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case OK:
			break;
		case Not_Isogram:
			std::cout << "Please enter an isogram (a word without repeating letters).\n\n";
			break;
		case Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case Not_Lowercase:
			std::cout << "Please enter only lowercase letters\n\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK);

	return Guess;
}

//Play a single game until completed
void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	//Loop asking for guess while game is not won && there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		std::string Guess = GetValidGuess();

		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BCCount.Bulls << "  ";
		std::cout << "Cows = " << BCCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word?(y/n): ";
	std::string Response = "";
	std::getline(std::cin, Response);

	std::cout << "\n\n";

	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		return true;
	}

	return false;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Won!\n";
	}
	else
	{
		std::cout << "You Lost!\n";
	}
}
