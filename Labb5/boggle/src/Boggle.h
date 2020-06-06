// Labb 5, Boggle - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * The functions below declare the methods to be implemented in the class file Boggle.cpp.
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include <set>

using namespace std;

class Boggle {
public:
    Boggle();
    Boggle(string board);
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    void clearAllWords();

    void clearFoundWords();

    void drawBoard() const;

    void generateRandomBoard();

    void generateCustomBoard(const string& boardLetters);

    void insertWord(const string& word);

    /*
     * Method that finds all the words in the board with the help of the recursive
     * function 'backtrackAllWords'.
    */
    void findAllWords();

    /*
     * Recursive help function that adds all the found words in the 'allWords' vector.
     */
    void backtrackAllWords(set<int> visited, int objectRow, int objectCol, string chosen);

    /*
     * Transforms a string to uppercase with ASCII code.
     */
    void to_upper(string& word) const;

    /*
     * Method that returns whether word is in the board with the help of the recursive
     * function 'backtrackWord'.
    */
    bool isWordInBoard(string word) const;

    /*
     * Recursive help function that returns whether the word is in the board.
     */
    bool backtrackWord(string word, int objectRow, int objectCol, set<int> visited, bool found) const;

    bool isValidString(const string& line) const;

    bool isValidWord(const string& word) const;

    bool containsWord(const vector<string>& words, const string& word) const;

    void getFoundWords(vector<string>& _foundWords);

    void getAllWords(vector<string>& _allWords);

    int getScore();

    int calculateComputerScore();

private:
    Lexicon lexicon;

    /* Datastructure representing the board. */
    Grid<char> board = Grid<char>(4, 4);

    /* Vector containing words found by the player. */
    vector<string> foundWords;

    /* Vector containing words found by the computer. */
    vector<string> allWords;

    /* Player score */
    int playerScore = 0;
};

#endif
