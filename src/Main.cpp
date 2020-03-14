//============================================================================
// Name        : The.cpp
// Author      : Daniel Grieco
// Version     :
// Copyright   : All Rights Reserved. Owned by Daniel Grieco ©
// Description : The Game Of Eight in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int ChooseNumber(int pID, int lastNum);
void DisplayAvailablePicks(int numberPicked);
bool IsChoiceValid(int choice, int lastPicked);
void DisplayWinner(int initNum, int pID);
bool WantToPlayAgain();

int main() {
	int initialNumber = 8;
	int playerID = 1;
	int chosenNumber = 0;
	int lastPick = 0;

	// Replay the game from the start if user/s want/s to play again.
	do {
		// Reset initial values.
		initialNumber = 8;
		playerID = 1;
		chosenNumber = 0;
		lastPick = 0;

		cout << "==========Welcome to the game of eight!==========" << endl << endl;

		// Keep running this until initialNumber goes to zero.
		while (initialNumber > 0) {
			cout << "*****Initial Number is: " << initialNumber << "*****" << endl << endl;

			chosenNumber = ChooseNumber(playerID, lastPick);
			lastPick = chosenNumber;

			if ((initialNumber -= chosenNumber) <= 0)	break;

			// Next player's turn.
			(playerID == 1) ? playerID = 2 : playerID = 1;
		}

		DisplayWinner(initialNumber, playerID);
	} while (WantToPlayAgain());

	return 0;
}


int ChooseNumber(int pID, int lastNum) {
	// Characters to ignore when the input is not correct.
	const int IGNORE_CHARS = 256;
	bool failure = false;

	int number = 0;

	do {
		// Before getting the input reset the flag to false, in case
		// the input is immediately correct.
		failure = false;

		cout << "Player " << pID << ", choose your number ";
		DisplayAvailablePicks(lastNum);

		cin >> number;

		// The user input something completely wrong.
		if (cin.fail()) {
			// Rid the standard input of any bad input.
			cin.clear();
			// Ignore all incorrect input up to the newline.
			cin.ignore(IGNORE_CHARS, '\n');

			cout << "Input error... Please try again." << endl << endl;

			// We have to try again since there was a failure.
			failure = true;
		} else {
			if (!IsChoiceValid(number, lastNum)) {
				// Ignore all incorrect input up to the newline.
				cin.ignore(IGNORE_CHARS, '\n');

				// We have to try again since there was a failure.
				failure = true;
			}
		}

	} while (failure);

	return number;
}


void DisplayAvailablePicks(int numberPicked) {
	// Display all numbers but the last pick.
	switch (numberPicked) {
		case 1:
			cout << "(2,3): ";
			break;
		case 2:
			cout << "(1,3): ";
			break;
		case 3:
			cout << "(1,2): ";
			break;
		default:
			cout << "(1-3): ";
			break;
	}
}


bool IsChoiceValid(int choice, int lastPicked) {
	bool isValid = false;

	if ((choice < 1) || (choice > 3)) {
		cout << "Input number is not within the correct range... Try again." << endl << endl;
		isValid = false;
	} else if (choice == lastPicked) {
		cout << "You can't pick what the other player picked before you... Try again." << endl << endl;
		isValid = false;
	} else {
		cout << "You picked " << choice << endl << endl;
		isValid = true;
	}

	return isValid;
}


void DisplayWinner(int initNum, int pID) {
	if (initNum == 0) {
		cout << "Player " << pID << " won the game!" << endl;
	} else if (initNum < 0) {
		int winnerID = 0;
		(pID == 1) ? winnerID = 2 : winnerID = 1;

		cout << "Player " << winnerID << " won the game!" << endl;
	}

	cout << "=================================================" << endl;
}


bool WantToPlayAgain() {
	bool playAgain = false;

	const int IGNORE_CHARS = 256;
	bool failure = false;

	char answer = ' ';

	do {
		failure = false;

		// Prompt the user to play again.
		cout << "Want to play again? (y/n): ";
		cin >> answer;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');

			cout << "There was an input error... Please try again." << endl << endl;

			failure = true;
		} else {
			// We don't care about upper case character;
			char lowerCaseAnswer = (char) tolower(answer);

			// The only characters that work.
			const char CONFIRM_CHAR = 'y';
			const char REJECT_CHAR = 'n';

			switch (lowerCaseAnswer) {
				case CONFIRM_CHAR: {
					cout << endl;

					playAgain = true;
				}
					break;
				case REJECT_CHAR:
					playAgain = false;
					break;
				default: {
					cin.ignore(IGNORE_CHARS, '\n');

					cout << "The character you input isn't valid... Please try again." << endl << endl;

					failure = true;
				}
					break;
			}
		}
	} while (failure);

	return playAgain;
}
