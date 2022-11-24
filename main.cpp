// C++ Program to Solve Sudoku Problem
// Concept Use Recursion and Backtracking

#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define N 9

unordered_set<int> rows[9];
unordered_set<int> columns[9];
unordered_set<int> blocks[3][3];


void print(int arr[N][N]) // Print the sudoku
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
				cout << arr[i][j] << " ";


		cout<<endl;
	}
}
// Checks whether it will be legal to assign number to the given row, col
bool isValid(int sudoku[N][N], int row, int col, int number)
{
	// Check for same number in the same row
	for (int x = 0; x <= 8; x++)
		if (sudoku[row][x] == number)
			return false;

	// Check for same number in the same col
	for (int x = 0; x <= 8; x++)
		if (sudoku[x][col] == number)
			return false;

	/*Check if we find the same number in
	 the particular 3*3 matrix*/
	int sRow = row - row % 3, sCol = col - col % 3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (sudoku[i + sRow][j + sCol] == number)
				return false;
	return true;
}

bool isValid2(int sudoku[N][N], int row, int col, int number){

    if(rows[row].count(number)==0 && columns[col].count(number)==0 && blocks[row/3][col/3].count(number)==0){
        return true;
    }
    return false;
}

// Function to Solve the sudoku
bool solution(int sudoku[N][N], int row, int col)
{
	/* If the 8th row and 9th column (0 indexed matrix) is reached,
	then return true to avoid backtracking*/
	if (row == N - 1 && col == N)
		return true;

	/*If column value becomes 9, move to next row and column
	Now start from 0*/
	if (col == N)
	{
		row++;
		col = 0;
	}

	/*If the current position contains value >0, then iterate for next column*/
	if (sudoku[row][col] > 0)
		return solution(sudoku, row, col + 1);

	for (int value = 1; value <= N; value++)
	{
		// Check whether a number (1-9) can be placed in the given row,col
		if (isValid2(sudoku, row, col, value))
		{
			sudoku[row][col] = value;
			rows[row].insert(sudoku[row][col]);
            columns[col].insert(sudoku[row][col]);
            blocks[row/3][col/3].insert(sudoku[row][col]);

			// Checking for next possibility with next column
			if (solution(sudoku, row, col + 1))
				return true;
		}
		/* If assumption is wrong, then Backtrack means remove the assigned number
		Proceed with a different value for next assumption*/
		rows[row].erase(sudoku[row][col]);
        columns[col].erase(sudoku[row][col]);
        blocks[row/3][col/3].erase(sudoku[row][col]);
		sudoku[row][col] = 0;
	}
	return false;
}

bool addToMap(int (&sudoku)[N][N]){
    int count=0;
    for(int row=0;row<9;row++){
        for(int col=0;col<9;col++){
            if(sudoku[row][col]!=0){
            int number=sudoku[row][col];
            if(rows[row].count(number)>0 || columns[col].count(number)>0 || blocks[row/3][col/3].count(number)>0){
            return true;
            }

            rows[row].insert(sudoku[row][col]);
            columns[col].insert(sudoku[row][col]);
            blocks[row/3][col/3].insert(sudoku[row][col]);
            count++;
            }
        }
    }
    //cout<<endl<<"inserted elemeents= "<<count<<endl;
    return false;
}

void readFramVal(int (&sudoku)[N][N])
{
	cout << "\nEnter the specified value.\n";
	cout << "Enter 0 if cell is empty.\n\n";
	int row, col;
	for (row = 0; row < 9; row++)
	{
		// Iterating over cells to read vals.
		for (col = 0; col < 9; col++)
		{
			int value;
			cout << "Enter value for cell[" << row + 1 << "][" << col + 1 << "] --> ";
			cin >> value;

			if (!(value >= 0 && value <= 9)) // Checking for bounds in input.
			{
				while (true) // We loop until valid input is read from user.
				{
					cout << "Oops! You seem to have entered a wrong value! Try again.\n";
					cout << "Enter value for cell again [" << row + 1 << "][" << col + 1 << "] --> ";
					cin >> value;
					if (value >= 0 && value <= 9)
						break;
				}
			}
			sudoku[row][col] = value;
		}
		cout << "-------\n";
	}
}

void readFrameValuesFile(int (&sudoku)[N][N])
{

	char filename[30]; // Getting filename.

	cout << "\nEnter the name of the file that contains the Sudoku Puzzle.\n";
	cout << "\t   --> ";
	cin >> filename;
	ifstream sudokuFile; // Opening file for reading.
	sudokuFile.open(filename, ios::in);
	int row, col;

	for (row = 0; row < 9; row++) // Iterating over file values.
	{
		for (col = 0; col < 9; col++)
		{
			int readValue;
			sudokuFile >> readValue;
			if (!(readValue >= 0 && readValue <= 9)) // Checking bounds for input.
			{
				cout << "\nValue " << ((row * 9) + col + 1) << " in " << filename;
				cout << " seems to be wrong! Correct the value and try again!\n";
				exit(EXIT_FAILURE);
			}

			sudoku[row][col] = readValue;
			if (sudokuFile.eof())
				break;
		}
	}
}

int main()
{
	int sudoku[N][N];
	cout << "\n\t\t\t\t*-*-*-*-*-*-*-*-*-*-*\n";
	cout << "\t\t\t\t    Sudoku Solver\n";
	cout << "\t\t\t\t*-*-*-*-*-*-*-*-*-*-*\n\n";

	cout << "Welcome to Sudoku Solver!\n";
	cout << "Before we start, you will have to input the sudoku into this program.\n\n";
	cout << "Enter your choice :-\n";
	cout << "Manually. (Enter 1)\n";
	cout << "Input File (Enter 2)\n";
	cout << "\t    The file must be in the same directory as this C++ file.\n";
	cout << "\t    The file must have all 81 values seperated with spaces.\n";
	cout << "\t    Blank cells must be filled in as 0\n";
	cout << "\tEnter Your Choice--\t ";

	int choice;
	cin >> choice;

	if (choice == 1)
		readFramVal(sudoku);
	else if (choice == 2)
		readFrameValuesFile(sudoku);
	else
	{
		while (true)
		{
			cout << "\nYou seem to have entered an invalid option. Try again.\n";
			cout << "\tEnter Your Choice Again \t";
			cin >> choice;

			if (choice == 1)
				readFramVal(sudoku);
			else if (choice == 2)
				readFrameValuesFile(sudoku);
			else
				continue;

			break;
		}
	}

	cout << "Before Solving " << endl;
	print(sudoku);
	cout << "" << endl;
	if(addToMap(sudoku)){
        cout<<"Invalid Sudoku Entered"<<endl;
        return 0;
	}
	cout << "After Solving " << endl;
	if (solution(sudoku, 0, 0))
		print(sudoku);
	else
		cout << "No solution exists " << endl;

	return 0;
}
