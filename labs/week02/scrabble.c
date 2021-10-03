#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // printf("Score1: %i\n", score1);
    // printf("Score2: %i\n", score2);

    // checking who wins
    string output = "\0";
    if (score1 > score2)
    {
        output = "Player 1 wins!";
    }
    else if (score1 < score2)
    {
        output = "Player 2 wins!";
    }
    else
    {
        output = "Tie!";
    }
    printf("%s\n", output);
}

int compute_score(string word)
{
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char c = word[i];

        // converting the char to Upper case
        c = toupper(c);

        if (c >= 65 && c <= 90)
        {
            // subtracting 65 fromt he ascii value to get the value relative to array index
            score += POINTS[(c - 65)];
        }
        else
        {
            score += 0;
        }
    }
    return score;
}
