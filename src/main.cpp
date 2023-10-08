#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

int scoreWord(const string word, const string doubleLetters, const string tripleLetters)
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

    return score;
}

int main()
{
    // Get player names
    string input;
    cout << "Enter player names, separated by spaces: ";
    getline(cin, input);

    istringstream iss(input);
    vector<string> playerNames;
    string name;

    // Push player names into vector
    while (iss >> name)
    {
        playerNames.push_back(name);
    }

    int turn = 1;
    bool gameIsActive = true;
    while (gameIsActive)
    {
        for (const auto &playername : playerNames)
        {
            cout << playername << " - Turn " << turn << ":" << endl;

            // Prompt for word
            cout << "Your word: ";
            string word;
            getline(cin, word);
            // cout << endl;

            // Prompt for double letters
            cout << "Double letters: ";
            string doubleLetters;
            getline(cin, doubleLetters);
            // cout << endl;

            // Prompt for triple letters
            cout << "Triple letters: ";
            string tripleLetters;
            getline(cin, tripleLetters);
            // cout << endl;

            // Prompt for double word
            cout << "Double word? y/[n]: ";
            string doubleWordInput;
            getline(cin, doubleWordInput);
            // cout << endl;

            bool doubleWord = (doubleWordInput == "n");

            // Prompt for triple word
            cout << "Triple word? y/[n]: ";
            string tripleWordInput;
            getline(cin, tripleWordInput);
            // cout << endl;

            bool tripleWord = (tripleWordInput == "n");

            // Score word
            int wordScore = scoreWord(word, doubleLetters, tripleLetters);

            if (doubleWord)
                wordScore *= 2;

            if (tripleWord)
                wordScore *= 3;

            // Check if player played all their tiles
            if (word.length() >= 7)
            {
                cout << "Did you play all the tiles in your hand? y/[n]: ";
                string emptiedHandInput;
                cin >> emptiedHandInput;
                cout << endl;

                bool emptiedHand = (emptiedHandInput == "n");
                if (emptiedHand)
                    wordScore += 50;
            }

            // Display word and player scores
            cout << "Word score: " << wordScore << endl;
            cout << "Player score: PLACEHOLDER" << endl
                 << endl;
        }

        turn++;
    }
}