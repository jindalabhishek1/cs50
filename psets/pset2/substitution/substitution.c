#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validate_key(int, string []);
string encrypt(string, string);

int main(int argc, string argv[])
{
    bool validated = validate_key(argc, argv);

    if (validated == false)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // printf("Success\n");

    string key = argv[1];
    string plainText = get_string("plaintext: ");
    string cipherText = encrypt(plainText, key);
    printf("ciphertext: %s\n", cipherText);
    return 0;
}

string encrypt(string plainText, string key)
{
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        // getting a character from plain text
        char c = plainText[i];
        int index = 0;

        // checking if the character is between [A - Z]
        if (c >= 65 && c <= 90)
        {
            index = c - 65;
            c = toupper(key[index]);
        }
        // checking if character is between [a - z]
        else if (c >= 97 && c <= 122)
        {
            index = c - 97;
            c = tolower(key[index]);
        }

        // skipping if the character is non alphabetic
        else
        {
            continue;
        }

        // changing the character in plain text to cipher character
        plainText[i] = c;
    }
    return plainText;
}

bool validate_key(int argc, string argv[])
{
    bool flag = false;

    // checking if only 2 command line arguments are passed
    // ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI are two arguments
    if (argc != 2)
    {
        flag = false;
    }
    else
    {
        string key = argv[1];
        int len_key = strlen(key);

        // checking if the length of key is 26
        if (len_key != 26)
        {
            flag = false;
        }
        else
        {
            // validating the key if lenght is 26
            int alpha[26] = {0};
            for (int i = 0, n = strlen(key); i < n; i++)
            {
                int index = 0;
                char c = key[i];

                // checking if the character is in between [A - Z]
                if (c >= 65 && c <= 90)
                {
                    index = c - 65;
                }

                // checking if the character is in between [a - z]
                else if (c >= 97 && c <= 122)
                {
                    index = c - 97;
                }

                // character is a non alphabatic
                else
                {
                    flag = false;
                    break;
                }

                // checking if the same character existed before in the key
                if (alpha[index] != 0)
                {
                    flag = false;
                    break;
                }

                // storing the character count
                alpha[index]++;
                flag = true;
            }


        }
    }
    return flag;
}