#include "QueryParser.h"
#include "Tokenizer.h"

Query QueryParser::parse(const std::string& rawQuery) {
    Query q;

    if (!rawQuery.empty() &&
        rawQuery.front() == '"' &&
        rawQuery.back() == '"') {
        q.isPhrase = true;
        q.terms = Tokenizer::tokenize(
            rawQuery.substr(1, rawQuery.size() - 2)
        );
        return q;
    }

    if (rawQuery.find(" AND ") != std::string::npos)
        q.isAND = true;
    else if (rawQuery.find(" OR ") != std::string::npos)
        q.isOR = true;

    q.terms = Tokenizer::tokenize(rawQuery);
    return q;
}
