#pragma once
#include "Document.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

class SearchEngine {
private:
    std::unordered_map<int, Document> documents;
    std::unordered_map<std::string, std::unordered_set<int>> invertedIndex;

    bool phraseMatch(const Document& doc,
                     const std::vector<std::string>& phrase) const;

    std::string generateSnippet(const Document& doc,
                                const std::string& term) const;

public:
    void loadDocuments(const std::string& folder);
    void search(const std::string& query);
};
