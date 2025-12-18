#include "Tokenizer.h"
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;



unordered_set<string> Tokenizer::stopWords;

void Tokenizer::loadStopWords(const string& file) {
    ifstream fin(file);
    string word;
    while (fin >> word) {
        stopWords.insert(word);
    }
}

vector<string> Tokenizer::tokenize(const string& text) {
    stringstream ss(text);
    string word;
    vector<string> tokens;

    while (ss >> word) {
        string clean;
        for (char c : word) {
            if (isalnum(c))
                clean += tolower(c);
        }
        if (!clean.empty() && !stopWords.count(clean))
            tokens.push_back(clean);
    }
    return tokens;
}
