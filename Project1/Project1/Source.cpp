# include <iostream>
#include <stdlib.h>
#include<ctime>
#include<fstream>
#include "Header.h"
#include<string>
using namespace std;
using namespace Game;

int main() {
	srand(time(0));
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);				// maximize screen 
	Logo();
	int Size, hurdles, CandyTypes, Matches;
	int choice;
	bool gameOver = false;
	bool exit = false;
	MainMenu();
	string abc;
	cin >> choice;
	Moves = 10;
	while (!gameOver) {
		switch (choice) {
		case 1: 									// if the user chooses play game option
			system("cls");    						// clear screen funtion.
			cout << "Type Your Name: ";
			cin >> abc;       						// inpouts name.
			system("cls");
			game_type();
			choice = 0; 							// setting choice value to zero so that it does not conflict with old value. 
			cin >> choice;  						// gettin easy or hard mord selection. 
			if (choice == 1) // if easy
			{
				Size = 8; hurdles = 5, CandyTypes = 5;
			}
			else if (choice == 2) { // if hard
				Size = 10; hurdles = 10, CandyTypes = 8;
			}
			Moves = 15; // Reset moves
			Score = 0; // Reset score
			CandyGen(Size, CandyTypes, hurdles); // Create random candies
			while (!gameOver) // Loop until game ends
			{
				if (Moves == 0) {				// if out of moves game over
					gameOver = true;
					break;
				}
				else if (SwapAvailable(Size) == false) // If no match is possible then shuffle
					CandyGen(Size, CandyTypes, hurdles);

				TableGen(Size); // Create table
				CandyMover(PointingRow, PointingColumn, Size, CandyTypes); // allow user to move 
				DestroyCandy(Size, CandyTypes); // Destroy matched candies

			}
			SaveScore(abc); // Save score
			cout << "=====> Out Of Moves <=====" << endl;
			cout << setw(80) << "Score  : " << Score << endl << endl;
			system("pause");
			system("cls");
			cout << setw(80) << "=====> Game Over! <=====" << endl;
			break;
		case 2:  // If Selected is 2
			system("cls");
			CreateCredit(); // Display credits
			break;
		case 3:  // If Selected is 3
			system("cls");
			Instructions(); // Display Rules/instructions
			break;
		case 4:  // If Selected is 4
			system("cls");
			LoadScores(); // Load Scores and display top 3 score with names
			break;
		case 5:  // If Selected is 5
			exit = Exit(); // Confirm if user wants to exit
			if (exit) // if user want to exit
			{
				cout << "/Closing Files........\n..\n..\n..\n/Exiting Program.........\n..\n..\n..\nSuccesfully Quited\n";
			}
			break;
		}
		gameOver = true;
		break;
	}






	return 0;
}
