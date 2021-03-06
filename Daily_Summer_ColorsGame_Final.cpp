// Daily_Summer_ColorsGame_Final.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
using namespace std;

int setup();
int rollDice(int playerNumber);

string player[4];
int positionPlayer[4];

int main()
{
	cout << "Welcome to The Colors Game! Here's how to play:" << endl;
	cout << "There are 50 spaces on the board, and the goal is to be the first player to land on the last space." << endl;
	cout << "Rule 1: You must roll double colors to get onto the board." << endl;
	cout << "Rule 2: If you land on the same space as someone else, whoever was there first gets kicked back to space 1." << endl;
	cout << "Rule 3: You must land exactly on space 50 to win. You can't pass it." << endl << endl;
	cout << "When it's your turn, press 'ENTER' to roll two four-sided dice that are colored red, green, orange, and blue." << endl;
	cout << "Based on the color combination of the dice, you'll do one of the following: " << endl << endl;
	cout << setw(16) << "Green/Green: " << "Swap spots with the leading player, or do nothing if player is in lead." << endl;
	cout << setw(16) << "Green/Orange: " << "Move three spaces" << endl;
	cout << setw(16) << "Green/Blue: " << "Move four spaces" << endl;
	cout << setw(16) << "Red/Green: " << "Lose your turn" << endl;
	cout << setw(16) << "Red/Red: " << "Start back at square one" << endl;
	cout << setw(16) << "Red/Blue: " << "Move back one space" << endl;
	cout << setw(16) << "Red/Orange: " << "Swap spots with the last player, or do nothing if player is already last." << endl;
	cout << setw(16) << "Blue/Blue: " << "Move five spaces" << endl;
	cout << setw(16) << "Blue/Orange: " << "Move six spaces" << endl;
	cout << setw(16) << "Orange/Orange: " << "Move eight spaces" << endl << endl;
	
	char playAgain = 'y';

	while (playAgain == 'y' || playAgain == 'Y')
	{
		srand(time(NULL));
		int numOfPlayers = setup();
		while (positionPlayer[0] != 50 && positionPlayer[1] != 50 && positionPlayer[2] != 50 && positionPlayer[3] != 50)
		{
			bool endGame = false;
			for (int number = 0; number < numOfPlayers; number++)
			{
				positionPlayer[number] = rollDice(number);
				if (positionPlayer[number] == 50)
				{
					endGame = true;
					break;
				}
			}
		}

		string winner;
		for (int number = 0; number < 4; number++)
			if (positionPlayer[number] == 50)
				winner = player[number];

		cout << "We have a winner! Congratulations, " << winner << "!" << endl << endl;
		cout << "Would you like to play again? y/n: ";
		cin >> playAgain;
		cout << endl;
		while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N')
		{
			cout << "You have to enter y or n. Would you like to play again? ";
			cin >> playAgain;
			cout << endl;
		}
	}

	cout << "Thanks for playing! Come again!" << endl;

	system("pause");
    return 0;
}

int setup()
{
	int numberOfPlayers = 0;
	cout << "This game is for 2-4 players. Enter the number of players: ";
	cin >> numberOfPlayers;
	while (numberOfPlayers < 2 && numberOfPlayers > 4)
	{
		cout << "The number of players must be between 2 and 4. Try again: ";
		cin >> numberOfPlayers;
	}
	for (int number = 0; number < numberOfPlayers; number++)
	{
		cout << "Enter the name of player " << number + 1 << ": ";
		cin >> player[number];
	}
	
	return numberOfPlayers;
}

int rollDice(int playerNumber)
{
	int number = playerNumber;
	enum diceType {orange, red, blue, green};
	diceType die1;
	diceType die2;

	cout << "It's your turn, " << player[number] << "!" << endl;
	while (cin.get() != '\n')
	{
		cout << "You must pres 'Enter' to roll the dice. Try again!";
	}

	// Players must roll double colors to start. Here, if they are still at position 0, we make them roll once to see if they get a double in order to move to space 1 and then roll
	// again to get their turn move. If they don't roll a double, their position is still set to 0.
	if (positionPlayer[number] == 0)						
	{														
		die1 = static_cast<diceType>(rand() % green);
		die2 = static_cast<diceType>(rand() % green);
		if ((die1 == orange && die2 == orange) || (die1 == red && die2 == red) || (die1 == blue && die2 == blue) || (die1 == green && die2 == green))
		{
			positionPlayer[number] = 1;
			die1 = static_cast<diceType>(rand() % green);
			die2 = static_cast<diceType>(rand() % green);
		}
		else
		{
			cout << "Sorry, you're not on the board yet." << endl;
			positionPlayer[number] = 0;
		}
	}
	else
		die1 = static_cast<diceType>(rand() % green);
		die2 = static_cast<diceType>(rand() % green);
	
	// This if statement will only apply to those who have rolled a double and are now at position 1. Or those who have already made it on the board and now their position is higher than 1.
	if (positionPlayer[number] >= 1)						
	{
		if (die1 == green && die2 == green)
		{
			// swap with highest player position
			int highestPosition = 0;
			for (int n = 1; n < number; n++)
			{
				if (positionPlayer[n] > positionPlayer[highestPosition])
					highestPosition = n;
			}
			int usedToSwap = positionPlayer[highestPosition];
			positionPlayer[highestPosition] = positionPlayer[number];
			positionPlayer[number] = usedToSwap;
			cout << "Sweet! You rolled green/green. You swap places with " << player[highestPosition] << " and move to space " << positionPlayer[number] << endl;
		}
		else if ((die1 == green && die2 == orange) || (die1 == orange && die2 == green))
		{
			positionPlayer[number] = positionPlayer[number] + 3;
			cout << "You rolled green/orange. You moved to space " << positionPlayer[number] << endl;
		}
		else if ((die1 == green && die2 == blue) || (die1 == blue && die2 == green))
		{
			positionPlayer[number] = positionPlayer[number] + 4;
			cout << "You rolled green/blue. You moved to space " << positionPlayer[number] << endl;
		}
		else if ((die1 == green && die2 == red) || (die1 == red && die2 == green))
		{
			positionPlayer[number] = positionPlayer[number];
			cout << "Womp, womp! You rolled green/red. You don't move this turn. You're still at space " << positionPlayer[number] << endl;
		}
		else if (die1 == red && die2 == red)
		{
			positionPlayer[number] = 1;
			cout << "Womp, womp! You rolled red/red. You moved back to space " << positionPlayer[number] << endl;
		}
		else if ((die1 == red && die2 == blue) || (die1 == blue && die2 == red))
		{
			positionPlayer[number] = positionPlayer[number] - 1;
			cout << "Womp, womp! You rolled red/blue. You moved back to space " << positionPlayer[number] << endl;
		}
		else if ((die1 == red && die2 == orange) || (die1 == orange && die2 == red))
		{
			// swap with lowest player position;
			int lowestPosition = 0;
			for (int n = 1; n < number; n++)
			{
				if (positionPlayer[n] > positionPlayer[lowestPosition])
					lowestPosition = n;
			}
			int usedToSwap = positionPlayer[lowestPosition];
			positionPlayer[lowestPosition] = positionPlayer[number];
			positionPlayer[number] = usedToSwap;
			cout << "Womp, womp! You rolled red/orange. You swap places with " << player[lowestPosition] << " and move to space " << positionPlayer[number] << endl;
		}
		else if (die1 == blue && die2 == blue)
		{
			positionPlayer[number] = positionPlayer[number] + 5;
			cout << "You rolled blue/blue. You moved to space " << positionPlayer[number] << endl;
		}
		else if ((die1 == orange && die2 == blue) || (die1 == blue && die2 == orange))
		{
			positionPlayer[number] = positionPlayer[number] + 6;
			cout << "You rolled orange/blue. You moved to space " << positionPlayer[number] << endl;
		}
		else if (die1 == orange && die2 == orange)
		{
			positionPlayer[number] = positionPlayer[number] + 8;
			cout << "You rolled orange/orange. You moved to space " << positionPlayer[number] << endl;
		}
	}

	// If a player lands on a space alrady occupied by someone else, the person who was already there gets kicked back to space 1.
	for (int n = 0; n <= 3; n++)											
		if (player[number] != player[n])
		{
			if (positionPlayer[number] == positionPlayer[n])
			{
				positionPlayer[n] = 1;
				cout << "Oh, no! " << player[n] << " was already on that space. " << player[n] << " moves back to space 1." << endl;
			}
		}

	// Players must throw an exact roll to land on space 50. If their turn moves them to a space higher than 50, then this IF statement undoes that turn and moves them back to where they
	// were at the beginning of their turn.
	if (positionPlayer[number] >= 51)																
	{
		cout << "Sorry, " << player[number] << "! You have to land on the last space without moving past it to win. You don't move this round." << endl; 											
		if ((die1 == green && die2 == orange) || (die1 == orange && die2 == green))
		{
			positionPlayer[number] = positionPlayer[number] - 3;
		}
		else if ((die1 == green && die2 == blue) || (die1 == blue && die2 == green))
		{
			positionPlayer[number] = positionPlayer[number] - 4;
		}
		else if (die1 == blue && die2 == blue)
		{
			positionPlayer[number] = positionPlayer[number] - 5;
		}
		else if ((die1 == orange && die2 == blue) || (die1 == blue && die2 == orange))
		{
			positionPlayer[number] = positionPlayer[number] - 6;
		}
		else if (die1 == orange && die2 == orange)
		{
			positionPlayer[number] = positionPlayer[number] - 8;
		}
	}

	return positionPlayer[number];
}
