#include "Player.h"

Player::Player(string name) : name(name) {}

string Player::getName() const { return name; }
int Player::getScore() const { return score; }
vector<string> Player::getPlayedWords() const { return playedWords; }

void Player::adjustScore(int points) { score += points; }
void Player::addPlayedWord(string word) { playedWords.push_back(word); }
