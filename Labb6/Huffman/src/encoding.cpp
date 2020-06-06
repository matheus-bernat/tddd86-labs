// Labb 6, Huffman - Matheus Bernat (matvi959) & Caspian Süsskind (cassu286)

#include "encoding.h"
#include <queue>

/* -------------- Headers ----------- */
void helpBuildEncodingMap(map<int, string>& encodingMap, HuffmanNode* encodingTree, string path = "");
void helpDecodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output, bool& isDone);
/* ---------------------------------- */

/* Builds the frequency table by reading input. */
map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char c;

    while(input.get(c)) {
        freqTable[c]++;
    }
    freqTable[PSEUDO_EOF] = 1;

    return freqTable;
}

/* Struct used for redefining the ()-operator in order to compare two Node pointers. */
struct CompareNodes {
    bool operator() (const HuffmanNode* node1, const HuffmanNode* node2) {
        return node1->count > node2->count;
    }
};

/* Builds the encoding tree with the help of a given frequency table. */
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable) {
    std::priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> myQueue;
    // Creates nodes based on 'freqTable' and adds them to 'myQueue'.
    for(auto key : freqTable) {
        HuffmanNode* node = new HuffmanNode(key.first, key.second, nullptr, nullptr);
        myQueue.push(node);
    }
    while(myQueue.size() != 1) {
        HuffmanNode* firstNode = myQueue.top();
        myQueue.pop();
        HuffmanNode* secondNode = myQueue.top();
        myQueue.pop();
        HuffmanNode* newNode = new HuffmanNode;
        newNode->count = firstNode->count + secondNode->count;
        newNode->zero = firstNode;
        newNode->one = secondNode;
        myQueue.push(newNode);
    }
    return myQueue.top();
}

/* Builds a encoding map with a given encoding tree. Calls a help recursive function. */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    helpBuildEncodingMap(encodingMap, encodingTree);
    return encodingMap;
}

/* Recursive function helping the buildEncodingMap function. */
void helpBuildEncodingMap(map<int,string>& encodingMap, HuffmanNode* encodingTree, string path) {
    if(encodingTree->isLeaf()) {
        encodingMap[encodingTree->character] = path;
    }
    else if(encodingTree != nullptr) {
        helpBuildEncodingMap(encodingMap, encodingTree->zero, path + "0");
        helpBuildEncodingMap(encodingMap, encodingTree->one, path + "1");
    }
}

/* Encodes a given input with the help of a given encoding map and writes it to output. */
void encodeData(istream& input, const map<int,string>& encodingMap, obitstream& output) {
    char c;
    while(input.get(c)) {
        for(int bit : encodingMap.at(c)) {
            if(bit == '1') {
                output.writeBit(1);
            }
            else if(bit == '0') {
                output.writeBit(0);
            }
        }
    }
    for(int bit : encodingMap.at(PSEUDO_EOF)) {
        if(bit == '1') {
            output.writeBit(1);
        }
        else if(bit == '0') {
            output.writeBit(0);
        }
    }
}

/* Decodes a given input with the help of a given encoding tree and writes to output */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    bool isDone = false;
    while(!isDone) {
        helpDecodeData(input, encodingTree, output, isDone);
    }
}

/* Recursive function helping the decodeData function. */
void helpDecodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output, bool& isDone) {
    if(encodingTree->isLeaf()) {
        if(encodingTree->character != PSEUDO_EOF) {
            output.write((char*)&encodingTree->character, 1);
        }
        else {
            isDone = true;
        }
    }
    else {
        int bit = input.readBit();
        if(bit == 0) {
            helpDecodeData(input, encodingTree->zero, output, isDone);
        }
        else {
            helpDecodeData(input, encodingTree->one, output, isDone);
        }
    }
}

/* Compresses a given file and writes the compressed data to output. */
void compress(istream& input, obitstream& output) {
    map<int,int> freqTable = buildFrequencyTable(input);

    // Write frequency table to the compressed file:
    for(auto key: freqTable) {
        output << key.first << ":" << key.second << ",";
    }
    output << "}";

    input.clear();
    input.seekg(0);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);
}

/* Decompresses a compressed file and writes the data to output. */
void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable;
    char c;
    int helpInt = 0;
    string key;
    string value;
    bool loopVar = true;
    while(loopVar) {
        input.get(c);
        if(c == ':') {
            helpInt++;
        }
        else if(c == ',') {
            freqTable[std::stoi(key)] = std::stoi(value);
            key.clear();
            value.clear();
            helpInt++;
        }
        else if(c == '}') {
            loopVar = false;
        }
        else if(helpInt%2 == 0) {
            key += c;
        }
        else if(helpInt%2 == 1) {
            value += c;
        }
    }

    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

/* Frees memory allocated for the tree's nodes. */
void freeTree(HuffmanNode* node) {
    if(node != nullptr) {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
