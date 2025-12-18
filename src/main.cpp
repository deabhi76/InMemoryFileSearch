#include "SearchEngine.h"
#include "Tokenizer.h"
#include <iostream>

using namespace std;

int main() {
    // Load stopwords once
    Tokenizer::loadStopWords("stopwords.txt");

    // Initialize search engine and load documents
    SearchEngine engine;
    engine.loadDocuments("data");

    cout << "InMemoryFileSearch\n";
    cout << "Type your query below.\n";
    cout << "Type 'exit' to quit.\n\n";

    while (true) {
        cout << "Enter query: ";

        string query;
        getline(cin, query);

        // Handle Ctrl+D / EOF
        if (cin.eof()) {
            cout << "\nExiting.\n";
            break;
        }

        // Exit command
        if (query == "exit") {
            cout << "Goodbye!\n";
            break;
        }

        // Skip empty queries
        if (query.empty()) {
            cout << "Please enter a non-empty query.\n\n";
            continue;
        }

        // Perform search
        engine.search(query);

        cout << "\n---------------------------------\n\n";
    }

    return 0;
}
