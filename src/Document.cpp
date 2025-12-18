#include "Document.h"
#include "Tokenizer.h"
using namespace std;
Document::Document(int id, const string& content)
    : id(id), content(content), length(0) {

    auto tokens = Tokenizer::tokenize(content);
    for (int i = 0; i < tokens.size(); i++) {
        positions[tokens[i]].push_back(i);
        length++;
    }
}

int Document::getId() const {
    return id;
}

int Document::getLength() const {
    return length;
}

const string& Document::getContent() const {
    return content;
}

const unordered_map<string, vector<int>>&
Document::getPositions() const {
    return positions;
}

