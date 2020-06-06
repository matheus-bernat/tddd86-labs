// TDDD86 - Labb1 - Game of Life - Matheus Bernat (matvi959), Caspian Süsskind (cassu286)
// Källor: föreläsningsbilderna från föreläsning 2 hjälpte oss att förstå hur man läser ifrån en fil.

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

/*Declaration of functions:*/
void chooseFile(string& fileName);
void getRowsAndColumns(const string& fileName, int& gridRows, int& gridColumns);
void createGrid(const string& fileName, const int gridRows, const int gridColumns, Grid<char>& grid);
void printWelcomeMessage();
void updateGrid(Grid<char>& grid);
void updateCell(Grid<char>& grid, const int row, const int column, const int neighbours);
void printGrid(const Grid<char>& grid);
void chooseAction(Grid<char>& grid);
void animate(Grid<char>& grid);

/*
 * Run the game by calling other smaller functions.
 */
int main() {
   printWelcomeMessage();
   string fileName;
   chooseFile(fileName);
   int gridRows;
   int gridColumns;
   getRowsAndColumns(fileName, gridRows, gridColumns);
   Grid<char> grid;
   createGrid(fileName, gridRows, gridColumns, grid);
   printGrid(grid);

   chooseAction(grid);

   cout << "\nHave a nice life!";
   return 0;
}

/*
 * Print welcoming message.
 */
void printWelcomeMessage() {
    cout << "Welcome to the TDDD86 Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbours dies." << endl;
    cout << "- Locations with 2 neighbours remain stable." << endl;
    cout << "- Locations with 3 neighbours will create life." << endl;
    cout << "- A cell with 4 or more neighbours dies.\n" << endl;
}

/*
 * Take input from user to let him choose which file he wants to run.
 */
void chooseFile(string& fileName) {
    cout << "Grid input file name? ";
    cin >> fileName;
}

/*
 * Gets from the text file how many rows and columns the grid has.
 */
void getRowsAndColumns(const string& fileName, int& gridRows, int& gridColumns) {
    ifstream input;
    string line;
    input.open(fileName);
    getline(input, line); // read first line with rows
    gridRows = stoi(line); // stoi transforms line into integer
    getline(input, line); // read second line with columns
    gridColumns = stoi(line);
    input.close();
}

/*
 * Creates a new empty grid with the wished dimensions.
 */
void createGrid(const string& fileName, const int gridRows, const int gridColumns, Grid<char>& grid) {
    ifstream input;
    string line;
    input.open(fileName);
    getline(input, line);
    getline(input, line) ; // Ignores the two first lines that have already been read

    grid = Grid<char>(gridRows, gridColumns);

    for(int row = 0; row < gridRows; row++) {
        getline(input, line);
        for(int column = 0; column < gridColumns; column++) {
            grid.set(row, column, line[column]);
        }
    }
    input.close();
}

/*
 * Updates the grid's cells based on how many neighbours the cell has.
 * It calls the function updateCell() for each cell.
 */
void updateGrid(Grid<char>& grid) {
    int neighbours = 0;
    Grid<char> gridCopy{grid}; // copy everything that was in grid to gridCopy.

    for(int row = 0; row < grid.numRows(); row++) {
        for(int column = 0; column < grid.numCols(); column++) {

            for(int rowCounter = -1; rowCounter <= 1; rowCounter++) {
                for(int columnCounter = -1; columnCounter <= 1; columnCounter++) {

                    if ((rowCounter != 0) | (columnCounter != 0)) {

                        if((gridCopy.inBounds(row + rowCounter, column + columnCounter))&&
                                (gridCopy.get(row + rowCounter, column + columnCounter) == 'X'))
                            neighbours++;
                    }
                }
            }
            updateCell(grid, row, column, neighbours);
            neighbours = 0; // set neighbours to 0 since now we're gonna start counting neighbours for a new cell
        }
    }
}

/*
 * Updates each cell based on the rules of the game.
 */
void updateCell(Grid<char>& grid, const int row, const int column, const int neighbours) {
    switch (neighbours) {
        case 2:
            break;
        case 3:
            grid.set(row, column, 'X');
            break;
        default:
            grid.set(row, column, '-');
            break;
    }
}

/*
 * Prints the grid.
 */
void printGrid(const Grid<char>& grid) {
    for(int row = 0; row < grid.numRows(); row++) {
        for(int column = 0; column < grid.numCols(); column++) {
            cout << grid.get(row, column);
        }
        cout << endl;
    }
}

/*
 * Interacts with user, asking him which action he'd like to pick.
 */
void chooseAction(Grid<char>& grid) {
    char choice;
    bool gameOn = true;
    while (gameOn) {
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> choice;

        switch(choice) {
            case 'a':
                animate(grid);
                break;
            case 't':
                updateGrid(grid);
                printGrid(grid);
                break;
            case 'q':
                gameOn = false;
                break;
            default:
                cout << "Don't get what you mean bro" << endl;
                break;
        }
    }
}

/*
 * Runs the animation.
 */
void animate(Grid<char>& grid) {
    while (true) {
        updateGrid(grid);
        printGrid(grid);
        pause(70);
        clearConsole();
    }
}
