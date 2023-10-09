#include "Player.h"
#include "Scorer.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void clearTerminal() { cout << "\033[2J\033[;H"; }

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

    // Create word scorer object
    Scorer scorer;

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
            int wordScore = scorer.scoreWord(word, additionalLetters,
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

    // Sort players by score and check for tie
    sort(players.begin(), players.end(), Player::compareByScore);

    int highestScore = players[0].getScore();
    int peopleTied = 0;
    for (const auto &player : players)
    {
        if (player.getScore() < highestScore)
            break;
        peopleTied++;
    }
    bool isATie = peopleTied > 1;

    // Show results
    clearTerminal();
    if (isATie)
    {
        cout << "It's a tie! Here are the results:" << endl;
    }
    else
    {
        cout << players[0].getName() << " wins with a final score of " << players[0].getScore() << "!" << endl
             << endl;
        cout << "Full results:" << endl;
    }

    for (const auto &player : players)
        cout << player.getName() << " - " << player.getScore() << endl;

    cout << endl
         << "The game is now over. Goodbye!" << endl;
}