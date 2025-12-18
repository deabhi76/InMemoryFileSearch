#pragma once
#include <vector>
#include <string>
#include <unordered_set>

class Tokenizer {
public:
    static void loadStopWords(const std::string& file);
    static std::vector<std::string> tokenize(const std::string& text);

private:
    static std::unordered_set<std::string> stopWords;
};
