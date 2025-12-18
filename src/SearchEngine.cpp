#include "SearchEngine.h"
#include "Tokenizer.h"
#include "QueryParser.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>


using namespace std;

static string readFile(const string& path) {
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void SearchEngine::loadDocuments(const string& folder) {
    int id = 1;
    for (auto& entry : filesystem::directory_iterator(folder)) {
        if (entry.path().extension() == ".txt") {
            Document doc(id, readFile(entry.path().string()));
            documents.emplace(id, doc);   


            for (auto& [word, _] : doc.getPositions())
                invertedIndex[word].insert(id);

            id++;
        }
    }
}

bool SearchEngine::phraseMatch(const Document& doc,
                               const vector<string>& phrase) const {
    if (!doc.getPositions().count(phrase[0])) return false;

    for (int pos : doc.getPositions().at(phrase[0])) {
        bool ok = true;
        for (int i = 1; i < phrase.size(); i++) {
            if (!doc.getPositions().count(phrase[i]) ||
                find(doc.getPositions().at(phrase[i]).begin(),
                     doc.getPositions().at(phrase[i]).end(),
                     pos + i) == doc.getPositions().at(phrase[i]).end()) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

string SearchEngine::generateSnippet(const Document& doc,
                                     const string& term) const {
    string text = doc.getContent();
    string lower = text;
    for (char& c : lower) c = tolower(c);

    auto pos = lower.find(term);
    if (pos == string::npos) return "";

    int start = max(0, (int)pos - 40);
    int end = min((int)text.size(), (int)pos + 40);

    return "..." + text.substr(start, end - start) + "...";
}

void SearchEngine::search(const string& query) {

    if (query.empty()) {
        cout << "❌ Empty query.\n";
        return;
    }

    if (documents.empty()) {
        cout << "❌ No documents loaded.\n";
        return;
    }

    Query parsed = QueryParser::parse(query);
    unordered_map<int, double> scores;

    for (auto& [id, doc] : documents) {
        double score = 0;

        if (parsed.isPhrase && !phraseMatch(doc, parsed.terms))
            continue;

        for (auto& term : parsed.terms) {
            if (!doc.getPositions().count(term)) continue;

            int tf = doc.getPositions().at(term).size();
            int df = invertedIndex.at(term).size();
            double idf = log((double)documents.size() / df);

            score += tf * idf;
        }

        if (score > 0) {
            score /= log(doc.getLength() + 1);
            scores[id] = score;
        }
    }

    if (scores.empty()) {
        cout << "❌ No documents matched your query.\n";
        return;
    }

    vector<pair<double, int>> ranked;
    for (auto& [id, sc] : scores)
        ranked.push_back({sc, id});

    sort(ranked.rbegin(), ranked.rend());

    vector<int> resultOrder;

    cout << "\nSearch Results:\n";
    int idx = 1;
    for (auto& [sc, id] : ranked) {
        const Document& doc = documents.at(id);
        cout << "[" << idx << "] Document " << id
             << " | Score: " << sc << "\n";
        cout << generateSnippet(doc, parsed.terms[0]) << "\n\n";
        resultOrder.push_back(id);
        idx++;
    }

    cout << "Enter document number to view (0 to exit): ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice <= 0 || choice > resultOrder.size()) {
        cout << "Exiting.\n";
        return;
    }

    int selectedId = resultOrder[choice - 1];
    cout << "\n----- Document " << selectedId << " -----\n";
    cout << documents.at(selectedId).getContent() << "\n";
}
