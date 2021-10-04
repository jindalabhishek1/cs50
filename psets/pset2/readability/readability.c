#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float average(int, int);
int calculate_grade(int, int, int);

int main(void)
{
    // input a string
    string input = get_string("Text: ");

    int letters = 0, words = 0, sentences = 0;

    // iterating over each character in the input
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        char c = input[i];

        // checking if char is between [a - z] or [A - Z]
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            letters++;
        }

        // checking if char is a space
        if (c == 32)
        {
            words++;
        }


        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }

    }

    // counting the last word
    if (letters > 0)
    {
        words++;
    }
    // printf("Letters: %i\nWords: %i\nSentences: %i\n", letters, words, sentences);

    int grade = calculate_grade(letters, words, sentences);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

float average(int x, int y)
{
    return (x * 100.0 / y);
}

int calculate_grade(int letters, int words, int sentences)
{
    float l = average(letters, words);
    float s = average(sentences, words);

    // Coleman-Liau index
    int index = round(0.0588 * l - 0.296 * s - 15.8);
    return index;
}