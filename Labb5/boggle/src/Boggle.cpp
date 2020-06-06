// Labb 5, Boggle - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * The functions below define the methods declared in the class header Boggle.h.
 * They handle the logic in the game.
 */

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <string>

#include <set>
#include <algorithm>

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const string validLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle() {
    lexicon = Lexicon(DICTIONARY_FILE);
}

void Boggle::clearAllWords() {
    allWords.clear();
}

void Boggle::clearFoundWords() {
    foundWords.clear();
}

void Boggle::drawBoard() const {
    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {
            std::cout << board.get(row, col);
        }
        cout << endl;
    }
}

void Boggle::generateRandomBoard() {
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            // Insert cube in board
            vector<char> cubeLetters;
            for(char letter: CUBES[4*row + col]) {
                cubeLetters.push_back(letter);
            }
            shuffle(cubeLetters);
            board.set(row, col, cubeLetters[0]);
        }
    }
    shuffle(board);
}

void Boggle::generateCustomBoard(const string& boardLetters) {
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            board.set(row, col, char(toupper(boardLetters[4*row + col])));
        }
    }
}

void Boggle::to_upper(string& word) const {
    for (int i = 0; i < word.length(); i++)
        if (word[i] >= 'a' and word[i] <= 'z')
            word[i] = word[i] - 32;
}

void Boggle::insertWord(const string& word) {
    playerScore += word.length() - 3;
    foundWords.push_back(word);
}

bool Boggle::containsWord(const vector<string>& words, const string& word) const {
    return (find(words.begin(), words.end(), word) != words.end());
}

bool Boggle::isValidString(const string& line) const {
    if(line.length() == 16) {
        bool allValid = true;
        for(char letter: line) {
            bool found = false;
            for(char validLetter: validLetters) {
                if(char(toupper(letter)) == validLetter) {
                    found = true;
                }
            }
            allValid = found && allValid;
        }
        return allValid;
    } else {
        return false;
    }
}

bool Boggle::isValidWord(const string& word) const {
    return lexicon.contains(word) && (word.length() > 3)
            && !containsWord(foundWords, word) && isWordInBoard(word);
}

void Boggle::getAllWords(vector<string>& _allWords) {
    _allWords = this->allWords;
}

void Boggle::getFoundWords(vector<string>& _foundWords) {
    _foundWords = this->foundWords;
}

int Boggle::calculateComputerScore() {
    int computerScore = 0;
    for(string word : allWords) {
        computerScore += word.size() - 3;
    }
    return computerScore;
}

int Boggle::getScore() {
    return playerScore;
}

/*
 * Loops through the board in search for word[0]. Start paths to look through the neighbours
 * by calling recursive function. If no word[0] found: return false.
 */
bool Boggle::isWordInBoard(string word) const {
    bool found = false;
    for(int row = 0; row < board.numRows(); row++) {
        for(int col = 0; col < board.numCols(); col++) {
            if(board.get(row, col) == toupper(word[0])) {
                set<int> visited;
                visited.insert(10*row+col);
                char c = word[0];
                // Start a new path:
                found = (backtrackWord(word.erase(0, 1), row, col, visited, false) || found);
                word.insert(0, 1, c);
            }
        }
    }
    return found;
}

/*
 * Recursivelly goes through all the given object's neighbours. Return true if word is found.
 */
bool Boggle::backtrackWord(string word, int objectRow, int objectCol, set<int> visited, bool found = false) const {
    if(word.size() == 0) {
        return true;
    }
    else {
        // Go through the 8 neighbours around object
        for(int row = objectRow - 1; row <= objectRow + 1; row++) {
            for(int col = objectCol - 1; col <= objectCol + 1; col++) {
                // Assure that the position is in bounds as well as not visited before
                if((board.inBounds(row, col)) && (visited.count(10*row+col) == 0)) {
                    // Check if the neighbour is the next searched letter. In that case, start a new path with the next letter
                    if(board.get(row, col) == toupper(word[0])) {
                        set<int> visitedCopy = visited;
                        visitedCopy.insert(10*row + col);
                        char c = word[0];
                        found = found || backtrackWord(word.erase(0, 1), row, col, visitedCopy);
                        word.insert(0, 1, c);
                    }
                }
            }
        }
        return found;
    }
}

/*
 * Finds all words in the board by calling another recursive function 'backtrackAllWords()'.
 */
void Boggle::findAllWords() {
    for(int row = 0; row < board.numRows(); row++) {
        for(int col = 0; col < board.numCols(); col++) {
            set<int> visited;
            string chosen = "";
            visited.insert(10*row+col);
            char c = board.get(row, col);
            backtrackAllWords(visited, row, col, chosen + c);
        }
    }
}

/*
 * Recursivelly find all words in the board and them in the 'allWords' vector.
 */
void Boggle::backtrackAllWords(set<int> visited, int objectRow, int objectCol, string chosen = "") {
    if(lexicon.contains(chosen) && (chosen.length() > 3)
            && !containsWord(allWords, chosen)
            && !containsWord(foundWords, chosen)) {
        allWords.push_back(chosen);
    }
    for(int row = objectRow - 1; row <= objectRow + 1; row++) {
        for(int col = objectCol - 1; col <= objectCol + 1; col++) {
            if((board.inBounds(row, col)) && (visited.count(10*row+col) == 0)) {
                if(lexicon.containsPrefix(chosen)) {
                    set<int> visitedCopy = visited;
                    visitedCopy.insert(10*row + col);
                    char c = board.get(row, col);
                    backtrackAllWords(visitedCopy, row, col, chosen + c);
                }
            }
        }
    }
}
