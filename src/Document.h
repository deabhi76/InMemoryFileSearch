#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Document {
private:
    int id;
    std::string content;
    int length;
    std::unordered_map<std::string, std::vector<int>> positions;

public:
    Document(int id, const std::string& content);
    int getId() const;
    int getLength() const;
    const std::string& getContent() const;
    const std::unordered_map<std::string, std::vector<int>>& getPositions() const;
};
