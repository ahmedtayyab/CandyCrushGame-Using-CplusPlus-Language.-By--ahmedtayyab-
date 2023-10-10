#pragma once
#include<iostream>
#include<conio.h>
#include<windows.h>									 // To change console text color and size
#include <fstream>									// To read and write data on file
#include<iomanip>									// For using setw
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;



void Logo() {		// Creates game logo which appears on the beginning of game
	system("cls");		// Clear screen
	cout << "\n\n\n\n\n\n\n\n\n";
	system("Color E5");
	cout << "                                      ==========  ==========  ||            ||  =========      \\\\           //" << endl;
	cout << "                                      ||          ||      ||  || ||         ||  ||       ||     \\\\         // " << endl;
	cout << "                                      ||          ||      ||  ||  ||        ||  ||        ||      \\\\     //" << endl;
	cout << "                                      ||          ||      ||  ||    ||      ||  ||         ||       \\\\  // " << endl;
	cout << "                                      ||          ||======||  ||      ||    ||  ||         ||         ||" << endl;
	cout << "                                      ||          ||      ||  ||        ||  ||  ||        ||          ||" << endl;
	cout << "                                      ||          ||      ||  ||         || ||  ||       ||           ||" << endl;
	cout << "                                      ==========  ||      ||  ||            ||  ||======||            ||" << endl << endl << endl;
	cout << "                                      ==========  ==========  ||          ||  ==========    ||        ||" << endl;
	cout << "                                      ||          ||      ||  ||          ||  ||            ||        ||" << endl;
	cout << "                                      ||          ||      ||  ||          ||  ||            ||        ||" << endl;
	cout << "                                      ||          ||      ||  ||          ||  ||========    ||========||" << endl;
	cout << "                                      ||          ||======||  ||          ||           ||   ||        ||" << endl;
	cout << "                                      ||          || \\        ||          ||           ||   ||        ||" << endl;
	cout << "                                      ||          ||   \\      ||          ||           ||   ||        ||" << endl;
	cout << "                                      ==========  ||     \\    ||==========||  =========||   ||        ||" << endl << endl << endl;
	Sleep(3500);				// Wait for 3.5 seconds then do next task
}
int GetKey()					// Checks which main menu option user is choosing
{
	int key = _getch();			// get the key
	return key;
}

void MainMenu() {
	system("cls");														// Clear screen
	cout << endl << endl;
	system("Color 09");													// Changing text color
	cout << endl << endl;
	cout << setw(105) << "<============> CANDY CRUSH <============>" << endl;
	cout << endl;
	cout << setw(98) << "=======> MAIN MENU <=======" << endl;
	cout << setw(90);
	cout << "1 -- PLAY GAME" << endl;
	cout << setw(87);
	cout << "2 -- CREDIT" << endl;
	cout << setw(94);
	cout << "3 -- INSTRUCTIONS " << endl;
	cout << setw(87);
	cout << "4 -- SCORE " << endl;
	cout << setw(86);
	cout << "5 -- EXIT " << endl << endl;
	cout << endl;
	cout << setw(89);
	cout << "Select Your Choice: ";

}


void game_type() {  								 // easy/hard mode function. 
	system("Color 07");
	cout << "-----------------------" << endl;
	cout << "Game types:" << endl;
	cout << "-----------------------" << endl;
	cout << endl;
	cout << "1. Easy Mode." << endl;
	cout << "2. Hard Mode." << endl;
	cout << endl;
	cout << "Select Your Choice: ";

}


namespace Game
{
	void TableGen(int);
	bool matchesExists(int);
	int Matches(int, int, int);
	void Swapping(int, int, int, int);
	void FalseSwap(int);
	void Bomb(int, int, int, int);



	char Candies[12] = { '@','$','%','&','*','#','!','D','B','H','X' };		// Declaring all types of Candies , Hurdles and X which shows destroyed candy
	char Candy[12][12];														// These are the candies in the table
	int _Matched[12][12];													// It stores locations of candies which are being matched or makes combination
	int PointingRow = 0, PointingColumn = 0, SwappedWith_R, SwappedWith_C, Moves = 10, Score = 0; // Pointing Row & Column shows at which candy is the user pointing by default it is 0
	string Message;															// The message which will appear when user matches 3 or more candies
	void CandyGen(int Size, int Num_Types, int H)							// Generate random candies depending upon difficulty level
	{
		srand(time(0));														// initiate srand
		int Randomizer;
		for (int i = 0; i < Size; i++)										// It generates random candies in all cells
		{

			for (int j = 0; j < Size; j++)
			{
				Randomizer = rand() % Num_Types;
				Candy[i][j] = Candies[Randomizer];

			}

		}
		int r, c;
		for (int i = 0; i < H; i++)										// Generates hurdles according to difficulty
		{
			r = rand() % Size;											// at random row
			c = rand() % Size;											// and random column
			if (Candy[r][c] != 'H')										// If there's not a hurdle already there
				Candy[r][c] = Candies[9];
			else {														// if there is a hurdle already there
				r = rand() % Size;
				c = rand() % Size;
				i--;
			}
		}

		for (int i = 0; i < Size; i++)				// To make sure no more than 2 candies appears in consective blocks
		{
			for (int j = 0; j < Size - 1; j++)
			{
				if (Candy[i][j] == Candy[i][j + 1] && Candy[i][j] == Candy[i][j + 2]) // If three candies are in consective column blocks
				{
					do {
						Randomizer = rand() % Num_Types;
						Candy[i][j] = Candies[Randomizer];
					} while (Candy[i][j] == Candy[i][j + 1]);			// keep generating random candy at that location until no 3 candies are consective
				}
				if (Candy[j][i] == Candy[j + 1][i] && Candy[j][i] == Candy[j + 2][i]) // If three candies are in consective row blocks
				{
					do {
						Randomizer = rand() % Num_Types;
						Candy[j][i] = Candies[Randomizer];
					} while (Candy[j][i] == Candy[j + 1][i]); // keep generating random candy at that location until no 3 candies are consective
				}
			}


		}

	}
	void Moved(int& Moves)  // When successfull move is performed minus 1 from total moves left
	{
		Moves -= 1;
	}

	void Colors(int i, int j, char Candy[12][12], int Size) // Assign color to each candy
	{

		switch (Candy[i][j])
		{
		case '@':
			SetConsoleTextAttribute(h, 2); // Dark green
			cout << Candy[i][j];
			break;
		case '$':
			SetConsoleTextAttribute(h, 13); // Golden
			cout << Candy[i][j];
			break;
		case '%':
			SetConsoleTextAttribute(h, 14); // Yellow
			cout << Candy[i][j];
			break;
		case '&':
			SetConsoleTextAttribute(h, 12); // Red
			cout << Candy[i][j];
			break;
		case '*':
			SetConsoleTextAttribute(h, 11); // Cyan
			cout << Candy[i][j];
			break;
		case '#':
			SetConsoleTextAttribute(h, 10); // light green
			cout << Candy[i][j];
			break;
		case '!':
			SetConsoleTextAttribute(h, 9); // Blue
			cout << Candy[i][j];
			break;
		case 'D':
			SetConsoleTextAttribute(h, 6); // Brown
			cout << Candy[i][j];
			break;
		case 'B':
			SetConsoleTextAttribute(h, 5); // Purple
			cout << Candy[i][j];
			break;
		case 'H':
			SetConsoleTextAttribute(h, 4); // Dark Red
			cout << Candy[i][j];
			break;
		case 'X':
			SetConsoleTextAttribute(h, 7); // White
			cout << Candy[i][j];
			break;
		}

		SetConsoleTextAttribute(h, 5);

	}

	void CandyMover(int& row, int& column, int Size, int Candy_Types) // Allow user to change the candy he is pointing at
	{
		int key = GetKey();
		if ((key == 87 || key == 119) && row > 0) // Press W to move up the menu
			row--;
		else if ((key == 83 || key == 115) && row < Size - 1) // Press S to move down the menu
			row++;
		else if ((key == 65 || key == 97) && column > 0) // Press A to move left on the menu
			column--;
		else if ((key == 68 || key == 100) && column < Size - 1) // Press S to move right on the menu
			column++;
		else if (key == 13 && Candy[row][column] != 'H') // Press S to move down the menu
		{
			Swapping(row, column, Size, Candy_Types); // Swap the the candy with selected direction
			Moved(Moves);
			if ((!matchesExists(Size) || Candy[PointingRow][PointingColumn] == 'H')) // If it doesn't make match or there's a hurdle then swap back and cancel move
				FalseSwap(Size);

		}
	}
	int Matches(int row, int column, int Size) // Checks how many candy matches
	{
		int Matches;
		int count = 1, temp = row;
		while ((Candy[temp][column] == Candy[temp + 1][column] && temp < Size - 1)) // Keeps checking matches on right side of row
		{
			count++;
			temp++; // move to next right 


		}
		temp = row;
		while ((Candy[temp][column] == Candy[temp - 1][column]) && temp > 0) // Keeps checking matches on left side of row
		{
			count++;
			temp--; // move to left

		}
		if (Candy[temp][column] == 'B') // Consider Bomb as a combination for itself
		{
			count = 3;
		}
		if (count >= 3)
			return count; // Return matches in rows
		count = 1;
		temp = column;
		while ((Candy[row][temp] == Candy[row][temp + 1]) && temp < Size - 1) // Keeps checking matches on  upside of column
		{
			count++;
			temp++; // move down

		}
		temp = column;
		while ((Candy[row][temp] == Candy[row][temp - 1]) && temp > 0) // Keeps checking matches on down side of column
		{
			count++;
			temp--; // move up

		}
		if (Candy[row][column] == 'B') //Consider bomb as a combination of three itself
		{
			count = 3;
		}
		return count;
	}
	bool matchesExists(int Size)  // If any cell shows 3 it means three candies are making combinations and hence matches exists
	{
		bool exists = false;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++) {
				if (Matches(i, j, Size) >= 3)// If any cell shows 3 it means three candies are making combinations
					return true; // matches exists
			}
		}
		return false;
	}
	void Swapping(int row, int column, int Size, int Candy_Types) // perform swaps
	{
		int key = GetKey(); // Input key from user
		char temp = Candy[row][column]; // Temporary stores value of that cell
		if (((key == 87 || key == 119) && row > 0)) // Press W to move up the menu
		{
			// Swaps candy with upper one
			Candy[row][column] = Candy[row - 1][column];
			Candy[row - 1][column] = temp;
			// Store location of cell with which swap is performed
			SwappedWith_R = row - 1;
			SwappedWith_C = column;
			if (Candy[row][column] == 'B') // if selected candy is a bomb
			{
				Bomb(Size, row, column, Candy_Types); // perform bomb function 
			}
			if (Candy[SwappedWith_R][SwappedWith_C] == 'B') // If the other cell which is being swapped with is bomb
			{
				Bomb(Size, SwappedWith_R, SwappedWith_C, Candy_Types);


			}
		}
		else if (((key == 83 || key == 115) && row < Size - 1)) // Press S to move down the menu
		{

			Candy[row][column] = Candy[row + 1][column];
			Candy[row + 1][column] = temp;
			// Store location of cell with which swap is performed
			SwappedWith_R = row + 1;
			SwappedWith_C = column;
			if (Candy[row][column] == 'B')  // if selected candy is a bomb
			{
				Bomb(Size, row, column, Candy_Types); // Perform bomb function

			}
			if (Candy[SwappedWith_R][SwappedWith_C] == 'B') // If the other cell which is being swapped with is bomb
			{
				Bomb(Size, SwappedWith_R, SwappedWith_C, Candy_Types);

			}
		}
		else if (((key == 65 || key == 97) && column > 0)) // Press S to move down the menu
		{
			Candy[row][column] = Candy[row][column - 1];
			Candy[row][column - 1] = temp;
			// Store location of cell with which swap is performed
			SwappedWith_R = row;
			SwappedWith_C = column - 1;
			if (Candy[row][column] == 'B')  // if selected candy is a bomb
			{
				Bomb(Size, row, column, Candy_Types);
			}
			if (Candy[SwappedWith_R][SwappedWith_C] == 'B') // If the other cell which is being swapped with is bomb
			{
				Bomb(Size, SwappedWith_R, SwappedWith_C, Candy_Types), Candy_Types; // Perform bomb function

			}
		}
		else if (((key == 68 || key == 100) && column < Size - 1)) // Press S to move down the menu
		{
			Candy[row][column] = Candy[row][column + 1];
			Candy[row][column + 1] = temp;
			// Store location of cell with which swap is performed
			SwappedWith_R = row;
			SwappedWith_C = column + 1;
			if (Candy[row][column] == 'B') // if selected candy is a bomb
			{
				Bomb(Size, row, column, Candy_Types); // Perform bomb functin
			}
			if (Candy[SwappedWith_R][SwappedWith_C] == 'B') // If the other cell which is being swapped with is bomb
			{
				Bomb(Size, SwappedWith_R, SwappedWith_C, Candy_Types); // Perform bomb function

			}
		}
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++) {

				_Matched[i][j] = Matches(i, j, Size); // perform matches function in each cell and store its location in _Matches[][]
			}
		}
	}
	void FalseSwap(int Size) // Cancels swap
	{
		char temp = Candy[SwappedWith_R][SwappedWith_C];
		Candy[SwappedWith_R][SwappedWith_C] = Candy[PointingRow][PointingColumn];
		Candy[PointingRow][PointingColumn] = temp;

	}
	bool SwapAvailable(int Size) // Checks if swap is available
	{
		for (int row = 0; row < Size; row++)
		{
			for (int column = 0; column < Size; column++)
			{

				int count = 0;
				if ((Candy[row][column] == Candy[row + 2][column] && Candy[row][column] == Candy[row + 3][column]) && row < Size - 3) // Checks if any combination exists in row
				{
					count++;
				}
				if (row > 3 && (Candy[row][column] == Candy[row - 2][column] && Candy[row][column] == Candy[row - 3][column])) // Checks if any combination exists in row
				{
					count++;
				}
				if (count >= 1)
					return true;
				else {
					count = 0;
					if ((Candy[row][column] == Candy[row][column + 2] && Candy[row][column] == Candy[row][column + 3]) && column < Size - 3) // Checks if any combination exists in column
					{
						count++;
					}
					if (column > 3 && (Candy[row][column] == Candy[row][column - 2] && Candy[row][column] == Candy[row][column - 3])) // Checks if any combination exists in column
					{
						count++;
					}
					if (count >= 1)
						return true;
				}
			}
		}
		return false;
	}
	void TableGen(int Size) // Function to create table of any size given.
	{
		system("cls");
		cout << setw(78) << "Score      : " << Score << endl;
		cout << setw(78) << "Moves Left : " << Moves << endl;
		cout << setw(78) << Message << endl;

		SetConsoleTextAttribute(h, 5);
		for (int i = 0; i < Size; i++) // This outter loop will control the Row of table mean all cells under 1 row
		{
			if (i == 0)  // At first row, the table upper border will be created
			{
				for (int j = 0; j < Size; j++) // Each cell of table has 6 spaces
					cout << "__________"; // For each cell 6 '_' will be printed
			}
			cout << endl; // After printing the upper border of table new line starts
			for (int j = 0; j < Size; j++) // This controls the column of table.
			{

				if (j == 0) // When J is 0, mean it is first column.
				{
					for (int k = 0; k < Size; k++)  // This loop runs to create borders( left and right) of each cell
					{


						if (k == Size - 1) // When it is last coloumn of cell
							cout << "|         |";
						else if (k == 0) // when it is first column of cell
							cout << "|         ";
						else  // if its between first and last column of cell
							cout << "|         ";

					}
					cout << endl;
					if (i == PointingRow && j == PointingColumn)
					{
						SetConsoleTextAttribute(h, 15);
						cout << "| >  ";
						SetConsoleTextAttribute(h, 5);
					}
					else
						cout << "|    ";
					Colors(i, j, Candy, Size);
					cout << "    "; //Print the first elements with its border (left and right)

				}
				else if (j == Size - 1) // if it is last column of cell
				{
					if (i == PointingRow && j == PointingColumn)
					{
						SetConsoleTextAttribute(h, 15);
						cout << "| >  ";
						SetConsoleTextAttribute(h, 5);
					}
					else
						cout << "|    ";
					Colors(i, j, Candy, Size);
					cout << "    |" << endl;
					for (int k = 0; k < Size; k++) // prints bottom border of cell
					{
						if (k != Size - 1)
							cout << "|_________";
						else
							cout << "|_________|";
					}

				}
				else // print elemts between borders of each cell
				{
					if (i == PointingRow && j == PointingColumn)
					{
						SetConsoleTextAttribute(h, 15);
						cout << "| >  ";
						SetConsoleTextAttribute(h, 5);
					}
					else
						cout << "|    ";
					Colors(i, j, Candy, Size);
					cout << "    ";
				}

			}

		}
		cout << endl << endl;
		Message = " ";
		SetConsoleTextAttribute(h, 7);
	}
	void DestroyCandy(int Size, int Candy_Types) // Destroys candies
	{
		int ScoreToBeAdded = 0;
		bool To_destroy = false;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++) {
				if (_Matched[i][j] >= 3 && Candy[i][j] != 'H' && Candy[i][j] != 'B') // there's any combination mark them as X which shows they are being destroyed
				{
					Candy[i][j] = Candies[10];
					To_destroy = true;
				}
			}
		}
		if (To_destroy)
		{
			TableGen(Size); // Recreate table
			ScoreToBeAdded = 30;
			Message = "Sweet";
			srand(time(0));
			int Randomizer, match = 0, count = 0;
			for (int i = 0; i < Size; i++)
			{
				for (int j = 0; j < Size; j++)
				{
					// Creates bomb if combination is greater than 3
					if (Candy[i][j] == Candies[10] && (_Matched[SwappedWith_R][SwappedWith_C] >= 4 && _Matched[SwappedWith_R][SwappedWith_C] < 6))
					{
						Candy[SwappedWith_R][SwappedWith_C] = Candies[8];
						ScoreToBeAdded = 40;
						Message = "Delicious";
					}
					// Creates bomb if combination is greater than 3
					else if (Candy[i][j] == Candies[10] && (_Matched[PointingRow][PointingColumn] >= 4 && _Matched[PointingRow][PointingColumn] < 6))
					{
						Candy[PointingRow][PointingColumn] = Candies[8];
						ScoreToBeAdded = 40;
						Message = "Delicious";
					}
					// Replace 'X' with new random candies making sure they do not form 3 consective candies
					if (Candy[i][j] == Candies[10])
					{
						do {
							Randomizer = rand() % Candy_Types;
							Candy[i][j] = Candies[Randomizer];
						} while ((Candy[i][j] == Candy[i + 1][j] && i < Size - 2) || (Candy[i][j] == Candy[i - 1][j] && i > 2) || (Candy[i][j] == Candy[i][j + 1] && j < Size - 2) || (Candy[i][j] == Candy[i][j + 1] && j > 2));

					}

					_Matched[i][j] = Matches(i, j, Size); // Reset their combination to neutral
				}
			}
			To_destroy = false;
		}
		Score += ScoreToBeAdded;						// Adds Score
		if (ScoreToBeAdded == 30) {
			Sleep(1400);
		}
		if (ScoreToBeAdded == 40) {
			Sleep(1400);
		}
		if (ScoreToBeAdded == 50) {
			Sleep(1400);
		}

	}
	void Bomb(int Size, int row, int column, int Candy_Types) // Function of Bomb
	{
		Candy[row][column] = Candies[10];
		for (int j = 0; j < Size; j++) // Destroys all cells(left,right,up and down) of that respective cell
		{
			if (Candy[row][j] != 'H')
				Candy[row][j] = Candies[10];
			if (Candy[j][column] != 'H')
				Candy[j][column] = Candies[10];
		}
		Message = "Divine"; // Display msg divine
		TableGen(Size);
		system("pause");
		int Randomizer;
		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < Size; j++)
			{
				if (Candy[i][j] == Candies[10])
				{
					do {
						Randomizer = rand() % Candy_Types;
						Candy[i][j] = Candies[Randomizer];
					} while ((i < Size - 2 && Candy[i][j] == Candy[i + 1][j]) || (i > 2 && Candy[i][j] == Candy[i - 1][j]) || (j < Size - 2 && Candy[i][j] == Candy[i][j + 1]) || (j > 2 && Candy[i][j] == Candy[i][j + 1]));

				}
			}
		}
		Score += 50;							// adds 50 score
	}
	void SaveScore(string Name)					// Save scores
	{
		ofstream WriteScore;
		WriteScore.open("Score.txt", ios::app);
		WriteScore << Score << " " << Name << endl;
		WriteScore.close();
	}
};

void CreateCredit()  // Display credits 
{
	cout << "Project Created By :"<<endl;
		cout << "Name : Ahmad Tayyab" << endl;
		cout << "Institution: FAST NUCES" << endl;
		cout << "Semester : First" << endl;
		cout << "Subject : Programming Fundamentals" << endl;
	SetConsoleTextAttribute(h, 15);
	cout << "Press BackSpace to return to main menu";
	int key = GetKey(); // return to main menu if user press Backspace
	if (key == 8) // 8 is the ascii value of Backspace key.
		MainMenu();
}

void Instructions()
{
	cout << "=====>     Press w/s to move up or down in main menu and press enter to select an option \n";
	cout << endl;
	cout << "=====>     In play game select the game difficulty by pressing enter. You can choose between difficulties.";
	cout << endl;
	cout << "=====>     Easy Mode : 5 types of Candies \t 5 Hurdles \t 9x9 Size of Table\n";
	cout << endl;
	cout << "=====>     Hard Mode : 8 Types of Candies \t 10 Hurdles \t 12x12 Size of Table \n";
	cout << "\n\n\n==============How to Play===============\n\n\n";
	cout << ">>>>> Use W,A,S,D to move around the table.\n";
	cout << ">>>>> Press enter to select candy.\n";
	cout << ">>>> Use W,A,S,D to choose with what candy you want to swap.\n";
	cout << ">>>> Make combination of 3 or more candies\n";
	cout << ">>>> if more than 3 candies matches then Bomb( 'B' ) is formed \n";
	cout << ">>>> 3 Mathes = 30 Score \t More than 3 = 40 Score \t Bomb used = 50 Score \n";
	cout << ">>>> Game will over if you use all moves\n";
	cout << "\n\n\n\n\nPress Backspace key to return to main menu ";
	int key = GetKey();
	if (key == 8)
		MainMenu();
}

void LoadScores() // Load scores of Top 3 players with their names
{
	string LargestN = " ", SecondLargestN = " ", ThirdLargestN = " "; // By Default set Top 3 names to Blank
	int Largest = 0, SecondLargest = 0, ThirdLargest = 0; // By default all scores are 0
	int Score = 0; // To read each score from file
	string Name;// To read each Name from file
	ifstream ReadScore; // To read Score file
	ReadScore.open("Score.txt"); // Opens score file
	if (ReadScore.is_open())  // if file opens 
	{
		while (!ReadScore.eof()) // Run loop until we reach end of the text file
		{
			ReadScore >> Score >> Name; // Inputs Score and Name from file
			/* Next to assign Largest , Second Largest and Third Largest Scores respectively*/
			if (Score > Largest)
			{
				ThirdLargest = SecondLargest;
				SecondLargest = Largest;
				Largest = Score;
				ThirdLargestN = SecondLargestN;
				SecondLargestN = LargestN;
				LargestN = Name;

			}
			else if (Score < Largest && Score > SecondLargest)
			{
				ThirdLargest = SecondLargest;
				SecondLargest = Score;
				ThirdLargestN = SecondLargestN;
				SecondLargestN = Name;
			}
			else if (Score < Largest && Score < SecondLargest && Score > ThirdLargest)
			{
				ThirdLargest = Score;
				ThirdLargestN = Name;

			}
		}



	}
	cout << "Highest Score:        " << LargestN << "   " << Largest << endl;
	cout << "Second Highest Score: " << SecondLargestN << "   " << SecondLargest << endl;
	cout << "Third Highest Score:  " << ThirdLargestN << "   " << ThirdLargest << endl;
	int key = GetKey();
	if (key == 8)
		MainMenu();
}
bool Exit()
{

	system("cls"); // Clear screen
	cout << "Are you sure you want to quit the game?\nY - To Confirm \nAny other key to return\n"; // Dispaly msg
	int key = GetKey(); // Input key from user
	if (key == 121 || key == 89) // If User press Y then he wants to quit
		return true;
	else  // if yes press any other key return to main menu
	{
		system("cls");
		MainMenu();
		return false;
	}
}

