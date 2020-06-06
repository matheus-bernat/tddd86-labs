// Labb 5, Boggle - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

/*
 * This class' functions implements the user interface, as well as handles all
 * the interaction and output.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include <set>


/* Method declaration */
void playersTurn(Boggle& boggle);
void computersTurn(Boggle& boggle);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    boggle.clearAllWords();
    boggle.clearFoundWords(); // to assure that words from an old game won't be left if we choose to play again.
    cout << "Do you want to generate a random board? ";
    string line;
    getline(cin, line);
    if(line == "y" || line == "Y") {
        boggle.generateRandomBoard();
    } else {
        do {
        cout << "Enter a 16 character string to generate a 4x4 boggle board: ";
        getline(cin, line);
        } while(!boggle.isValidString(line));
        boggle.generateCustomBoard(line);
    }
    std::cout << "It's your turn" << std::endl << std::endl;
    boggle.drawBoard();
    playersTurn(boggle);
    computersTurn(boggle);
    vector<string> foundWords, allWords;
    boggle.getFoundWords(foundWords);
    boggle.getAllWords(allWords);

    if(foundWords.size() >= allWords.size()) {
        std::cout << "You miserable human just won" << std::endl;
    }
    else {std::cout << std::endl << "BETTER LUCK NEXT TIME, YOU DUMBASS!" << std::endl;}
}

void playersTurn(Boggle& boggle) {
    string line;
    vector<string> foundWords;
    boggle.getFoundWords(foundWords);

     do {
        std::cout << std::endl << "Your words(" << foundWords.size() << "): {";
        if(foundWords.size() != 0) {
            for(unsigned i = 0; i < (foundWords.size() - 1); i++) {
                std::cout << foundWords[i] << ", ";
            }
            std::cout << foundWords[foundWords.size() - 1] << "}" << std::endl;
        } else {
            std::cout << "}" << std::endl;
        }
        std::cout << "Your score: " << boggle.getScore() << std::endl;
        std::cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, line);
        if(boggle.isValidWord(line)) {
            boggle.to_upper(line);
            boggle.insertWord(line);
            foundWords.push_back(line);
        }
        clearConsole();
        std::cout << std::endl;
        boggle.drawBoard();
    } while(line.length() != 0);
}

void computersTurn(Boggle& boggle) {
    std::cout << "It's my turn!" << std::endl;
    boggle.findAllWords();
    vector<string> allWords;
    boggle.getAllWords(allWords);
    size_t allWordsSize = allWords.size();
    std::cout << std::endl << "My words(" << allWordsSize << "): {";
    if(allWordsSize != 0) {
        for(unsigned i = 0; i < (allWordsSize - 1); i++) {
            std::cout << allWords[i] << ", ";
        }
        std::cout << allWords[allWordsSize - 1] << "}" << std::endl;
    } else {
        std::cout << "}" << std::endl;
    }
    std::cout << std::endl << "My score: " << boggle.calculateComputerScore() << std::endl;
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
