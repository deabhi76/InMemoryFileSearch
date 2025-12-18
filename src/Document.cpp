#include "Document.h"
#include "Tokenizer.h"

Document::Document(int id, const std::string& content)
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

const std::string& Document::getContent() const {
    return content;
}

const std::unordered_map<std::string, std::vector<int>>&
Document::getPositions() const {
    return positions;
}

