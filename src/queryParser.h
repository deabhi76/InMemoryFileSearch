#pragma once
#include <vector>
#include <string>

struct Query {
    bool isPhrase = false;
    bool isAND = false;
    bool isOR = false;
    std::vector<std::string> terms;
};

class QueryParser {
public:
    static Query parse(const std::string& rawQuery);
};
