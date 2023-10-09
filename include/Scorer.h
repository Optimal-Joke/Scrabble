#pragma once

#include <map>
#include <string>
using std::map;
using std::string;

class Scorer
{
private:
    const map<char, int> LETTER_VALUES;

public:
    Scorer();

    int scoreWord(const string word, const string overlappingWordLetters,
                  const string doubleLetters, const string tripleLetters,
                  const bool doubleWord, const bool tripleWord) const;
};