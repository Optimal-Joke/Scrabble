#include "Player.h"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int scoreWord(const string word, const string overlappingWordLetters,
              const string doubleLetters, const string tripleLetters,
              const bool doubleWord, const bool tripleWord)
{
    map<char, int> LETTER_VALUES = {{'a', 1}, {'b', 3}, {'c', 3}, {'d', 2}, {'e', 1}, {'f', 4}, {'g', 2}, {'h', 4}, {'i', 1}, {'j', 8}, {'k', 5}, {'l', 1}, {'m', 3}, {'n', 1}, {'o', 1}, {'p', 3}, {'q', 10}, {'r', 1}, {'s', 1}, {'t', 1}, {'u', 1}, {'v', 4}, {'w', 4}, {'x', 8}, {'y', 4}, {'z', 10}};

    int score = 0;

    for (const auto &letter : word)
        score += LETTER_VALUES[letter];

    // double letters
    for (const auto &letter : doubleLetters)
        score += LETTER_VALUES[letter];

    // triple letters
    for (const auto &letter : tripleLetters)
        score += 2 * LETTER_VALUES[letter];

    if (doubleWord)
        score *= 2;

    if (tripleWord)
        score *= 3;

    // additional word letters
    for (const auto &letter : overlappingWordLetters)
        score += LETTER_VALUES[letter];

    return score;
}

void clearTerminal() { cout << "\033[2J\033[;H"; }

bool compareByScore(const Player &player1, const Player &player2)
{
    return player1.getScore() > player2.getScore();
}

int main()
{
    clearTerminal();

    // Introduce game
    cout << "Welcome to Scrabble Score Keeper!" << endl
         << endl;

    // Create players
    string input;
    cout << "Please type your players' names, separated by spaces: ";
    getline(cin, input);

    istringstream iss(input);
    vector<Player> players;
    string name;

    // Push player names into vector
    while (iss >> name)
        players.emplace_back(name);

    // Prompt to begin game
    cout << "\nScore Keeper is ready! Press ENTER to begin...";
    getchar();

    int turn = 1;
    bool gameIsActive = true;
    while (gameIsActive)
    {
        for (auto &player : players)
        {
            clearTerminal();

            cout << player.getName() << " - Turn " << turn << ":"
                 << " (current score: " << player.getScore() << ")" << endl;

            // Prompt for word
            cout << "Your word (enter \"e\" to end game): ";
            string word;
            getline(cin, word);

            if (word == "e")
            {
                gameIsActive = false;
                break;
            }

            // Prompt for double letters
            cout << "Double letters: ";
            string doubleLetters;
            getline(cin, doubleLetters);

            // Prompt for triple letters
            cout << "Triple letters: ";
            string tripleLetters;
            getline(cin, tripleLetters);

            // Prompt for double word
            cout << "Double word? y/[n]: ";
            string doubleWordInput;
            getline(cin, doubleWordInput);

            bool doubleWord = (doubleWordInput == "y");

            // Prompt for triple word
            cout << "Triple word? y/[n]: ";
            string tripleWordInput;
            getline(cin, tripleWordInput);

            bool tripleWord = (tripleWordInput == "y");

            // Prompt for any letters from additional words
            cout << "Additional letters from overlapping words: ";
            string additionalLetters;
            getline(cin, additionalLetters);

            // Score word
            int wordScore = scoreWord(word, additionalLetters,
                                      doubleLetters, tripleLetters,
                                      doubleWord, tripleWord);

            // Check if player played all their tiles
            if (word.length() >= 7)
            {
                cout << "Did you play all the tiles in your hand? y/[n]: ";
                string emptiedHandInput;
                getline(cin, emptiedHandInput);

                bool emptiedHand = (emptiedHandInput == "y");
                if (emptiedHand)
                    wordScore += 50;
            }

            // Update player score and show word and player scores
            player.adjustScore(wordScore);
            cout << "\nWord score: " << wordScore << endl;
            cout << "Player score: " << player.getScore() << endl
                 << endl;

            // Prompt to move to next turn
            cout << "Press ENTER to begin next turn...";
            getchar();
        }

        turn++;
    }

    // We're in the endgame now
    clearTerminal();
    cout << "Normal gameplay has now ended. Score adjustment time!\n\n";
    cout << "If you have no tiles remaining, add to your score all points on your opponents' remaining tiles.\n";
    cout << "If you still have tiles, add up the points of your tiles and subtract that from your score.\n\n";

    cout << "Enter the score adjustments for each player..." << endl;
    for (auto &player : players)
    {
        cout << player.getName() << ": ";
        string adjustmentInput;
        getline(cin, adjustmentInput);

        int adjustment;
        try
        {
            adjustment = stoi(adjustmentInput);
        }
        catch (const exception &e)
        {
            adjustment = 0;
        }

        player.adjustScore(adjustment);
    }

    // Sort players by score
    sort(players.begin(), players.end(), Player::compareByScore);

    // Show results
    clearTerminal();
    cout << players[0].getName() << " wins with a final score of " << players[0].getScore() << ". Not bad!" << endl
         << endl;
    cout << "Full results:" << endl;

    for (const auto &player : players)
        cout << player.getName() << " - " << player.getScore() << endl;

    cout << endl
         << "The game is now over. Goodbye!" << endl;
}