#include "SearchEngine.h"
#include "Tokenizer.h"
#include <iostream>

int main() {
    Tokenizer::loadStopWords("stopwords.txt");

    SearchEngine engine;
    engine.loadDocuments("data");

    std::string query;
    std::cout << "Enter query: ";
    std::getline(std::cin, query);

    engine.search(query);
    return 0;
}
