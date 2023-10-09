#include "Scorer.h"

Scorer::Scorer() : LETTER_VALUES({{'a', 1}, {'b', 3}, {'c', 3}, {'d', 2}, {'e', 1}, {'f', 4}, {'g', 2}, {'h', 4}, {'i', 1}, {'j', 8}, {'k', 5}, {'l', 1}, {'m', 3}, {'n', 1}, {'o', 1}, {'p', 3}, {'q', 10}, {'r', 1}, {'s', 1}, {'t', 1}, {'u', 1}, {'v', 4}, {'w', 4}, {'x', 8}, {'y', 4}, {'z', 10}}) {}

int Scorer::scoreWord(const string word, const string overlappingWordLetters,
                      const string doubleLetters, const string tripleLetters,
                      const bool doubleWord, const bool tripleWord) const
{
    int score = 0;

    for (const auto &letter : word)
        score += LETTER_VALUES.at(letter);

    // double letters
    for (const auto &letter : doubleLetters)
        score += LETTER_VALUES.at(letter);

    // triple letters
    for (const auto &letter : tripleLetters)
        score += 2 * LETTER_VALUES.at(letter);

    if (doubleWord)
        score *= 2;

    if (tripleWord)
        score *= 3;

    // additional word letters
    for (const auto &letter : overlappingWordLetters)
        score += LETTER_VALUES.at(letter);

    return score;
}