#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

class Player
{
private:
    const string name;
    int score;
    vector<string> playedWords;

public:
    Player(string name);

    string getName() const;
    int getScore() const;
    vector<string> getPlayedWords() const;

    void adjustScore(int points);
    void addPlayedWord(string word);
};
