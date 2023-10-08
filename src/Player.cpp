#include "Player.h"

Player::Player(string name) : name(name) {}

bool Player::compareByScore(const Player &player1, const Player &player2)
{
    return player1.getScore() > player2.getScore();
}

string Player::getName() const { return name; }
int Player::getScore() const { return score; }
vector<string> Player::getPlayedWords() const { return playedWords; }

void Player::adjustScore(int points) { score += points; }
void Player::addPlayedWord(string word) { playedWords.push_back(word); }
