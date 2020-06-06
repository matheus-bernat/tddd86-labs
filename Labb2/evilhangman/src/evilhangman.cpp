// Labb2, Del B - Evil Hangman - Matheus Bernat (matvi959), Caspian Süsskind (cassu286)

/*
 * Program description:
 *
 * The program is a version of hangman that cheats against the user.
 * The game cheats by always choosing the longest family available, so that
 * it becomes difficult for the player to win.
*/

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string VOWELS = "aeiouyw";

// Declaration of functions:
unsigned getWordLength();
bool isValidLength(const unsigned wordLength);
bool getChoice();
int getNumberOfGuesses();
char getGuess(set<char>& usedLetters);
void buildDictionary(const unsigned wordLength, set<string>& dictionary);
void playHangman(int guessesLeft, const unsigned wordLength, set<string>& dictionary, const bool choice);
void printInfo(const int guessesLeft, const set<string>& dictionary, const bool choice, const string& currentWord, const set<char>& usedLetters);
void buildCurrentWord(const set<string>& dictionary, const set<char>& usedLetters, string& currentWord);
void getLongestFamily(set<string>& dictionary, const char guess, const unsigned wordLength, int& guessesLeft);

int main() {
    cout << "Welcome to Hangman." << endl;
    bool gameOn = true;
    while(gameOn) {
        unsigned wordLength = getWordLength();
        int guessesLeft = getNumberOfGuesses();
        bool seeWordsLeft = getChoice();
        set<string> dictionary;
        buildDictionary(wordLength, dictionary);
        playHangman(guessesLeft, wordLength, dictionary, seeWordsLeft);
        cout << "Do you want to play again, yes or no? ";
        string answer;
        cin >> answer;
        if(answer == "no") {
            gameOn = false;
        }
   }
    cout << "\nWELCOME BACK!\n";
    return 0;
}

/* Take input from user on word length. */
unsigned getWordLength() {
    while(true) {
        cout << "Give me a word length: ";
        unsigned wordLength;
        cin >> wordLength;
        cout << endl;
        if(wordLength > 0 && isValidLength(wordLength)) {
            return wordLength;
        }
    }
}

/* Check whether the word's length is valid. */
bool isValidLength(const unsigned wordLength) {
    ifstream input;
    string word;
    string fileName = "di.txt";
    input.open(fileName);
    while(!input.fail()) {
        getline(input, word);
        if (word.size() == wordLength) {
            input.close();
            return true;
        }
    }
    return false;
}

/* Ask user if he/she wants to see number of words left. */
bool getChoice() {
    string choice;
    while(true) {
        cout << "Do you want to see the number of words left in the dictionary, yes or no? ";
        cin >> choice;
        if(choice == "yes") {
            return true;
        } else if(choice == "no") {
            return false;
        }
    }
}

/* Take input on number of wished guesses. */
int getNumberOfGuesses() {
    int guesses = 0;
    while(guesses <= 0) {
        cout << "How many guesses do you want? ";
        cin >> guesses;
        cout << endl;
    }
    return guesses;
}

/* Ask user for a letter. */
char getGuess(set<char>& usedLetters) {
    while(true) {
        cout << "Guess a letter: ";
        string guess;
        cin >> guess;
        if(guess.size() == 1 && !usedLetters.count(guess[0]) & (ALPHABET.find(guess[0]) != std::string::npos)) {
            usedLetters.insert(guess[0]);
            return guess[0];
        }
    }
}

/* Build dictionary with wished size of word. */
void buildDictionary(const unsigned wordLength, set<string>& dictionary) {
    ifstream input;
    string word;
    string fileName = "di.txt";
    input.open(fileName);
    while(!input.fail()) {
        getline(input, word);
        if (word.size() == wordLength)
            dictionary.insert(word);
    }
    input.close();
}

/* Game Loop. Implement game rules, print info, get guesses, check if player won. */
void playHangman(int guessesLeft, const unsigned wordLength, set<string>& dictionary, const bool choice) {
    set<char> usedLetters;
    string currentWord;
    while(guessesLeft) {
        buildCurrentWord(dictionary, usedLetters, currentWord);
        printInfo(guessesLeft, dictionary, choice, currentWord, usedLetters);
        if(dictionary.count(currentWord)) {
            cout << "You win! The word was: " << currentWord << endl;
            break;
        }
        char guess = getGuess(usedLetters);
        getLongestFamily(dictionary, guess, wordLength, guessesLeft);
    }
    if(!guessesLeft) {
        printInfo(guessesLeft, dictionary, choice, currentWord, usedLetters);
        auto it = dictionary.begin();
        cout << "You lose! The word was: " << *it << endl;
    }
}

/* Output game information: number of guesses left, current word, used letters, words left. */
void printInfo(const int guessesLeft, const set<string>& dictionary, const bool choice, const string& currentWord, const set<char>& usedLetters) {
    cout << endl << "Tries left: " << guessesLeft << endl;
    cout << "Used letters: ";
    for(auto it = usedLetters.cbegin(); it != usedLetters.cend(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    cout << currentWord << endl;
    if(choice) {
        cout << "Words left: " << dictionary.size() << endl;
    }
}

/* Build the current word. */
void buildCurrentWord(const set<string>& dictionary, const set<char>& usedLetters, string& currentWord) {
   auto it = dictionary.begin();
   string word = *it;
   currentWord.clear();

   for(unsigned i = 0; i < word.size(); i++) {
       if(usedLetters.count(word[i])) {
            currentWord += word[i];
       } else {
            currentWord += "-";
       }
   }
}

/* Group the words in families and later choose the biggest family and set that dictionary equals that. */
void getLongestFamily(set<string>& dictionary, const char guess, const unsigned wordLength, int& guessesLeft) {
    map<string, set<string>> families;
    // Create all different word families and add words to these.
    for(auto it = dictionary.begin(); it != dictionary.end(); it ++) {
        string familyKey;
        for(unsigned i = 0; i < wordLength; i++) {
            if((*it)[i] == guess) {
                familyKey += guess;
            } else {
                familyKey += "-";
            }
        }
        if(families.count(familyKey)) {
            families[familyKey].insert(*it);
        } else {
            set<string> words;
            words.insert(*it);
            families.insert(pair<string, set<string>> (familyKey, words));
        }
    }
    set<string> longestFamily;

    // Check if we can make the player lose game. EXTRA UPPGIFT E1
    string noLetters;
    for(unsigned i = 0; i < wordLength; i++) {
        noLetters += '-';
    }
    if(guessesLeft == 1 && families.count(noLetters)) {
        dictionary = families[noLetters];
        guessesLeft--;
    }else {
        string longestFamilyKey;
        for(auto it = families.begin(); it != families.end(); it++) {
            // Count the number of keys in families to see which family is bigger.
            if(longestFamily.size() < (it->second).size()) {  // byta denna funktion mot "getFamilyWeight()" -- UPPGIFT E2
                longestFamily = (it->second);
                longestFamilyKey = (it->first);
            }
        }
        dictionary = longestFamily;
        // If wrong, reduce guesses left.
        if(longestFamilyKey == noLetters) {
            guessesLeft--;
        }
    }
}
