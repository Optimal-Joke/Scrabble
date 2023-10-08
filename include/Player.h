#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;

class Player
{
private:
    string name;
    int score;
    vector<string> playedWords;

public:
    Player(string name);

    static bool compareByScore(const Player& player1, const Player& player2);

    string getName() const;
    int getScore() const;
    vector<string> getPlayedWords() const;

    void adjustScore(int points);
    void addPlayedWord(string word);
};
