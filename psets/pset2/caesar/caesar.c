#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cipher(string, int);
bool validate_key(int, string []);

int main(int argc, string argv[])
{
    bool validated = validate_key(argc, argv);
    if (validated == false)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }

    string str_key = argv[1];

    // converting digit string to int
    int key = atoi(str_key);

    // getting plain text from user
    string plain_text = get_string("plaintext: ");

    // calulating cipher
    string cipher_text = cipher(plain_text, key);
    printf("ciphertext: %s\n", cipher_text);
    return 0;
}

string cipher(string plain, int key)
{
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        char c = plain[i];

        if (c >= 65 && c <= 90)
        {
            c = c - 65;
            c = c + key;
            c = c % 26;
            c = c + 65;
        }
        else if (c >= 97 && c <= 122)
        {
            c = c - 97;
            c = c + key;
            c = c % 26;
            c = c + 97;
        }
        plain[i] = c;
        // printf("%c\n", c);
    }
    return plain;
}

bool validate_key(int argc, string argv[])
{
    bool flag = false;
    // checking if there are more or less than 2 command line arguments
    // ./caesar 4000 are two arguments
    if (argc != 2)
    {
        flag = false;
    }
    else
    {
        // int key = retrieve_key(argv[1]);
        // validaing the key
        string str_key = argv[1];
        for (int i = 0, n = strlen(str_key); i < n; i++)
        {
            char c = str_key[i];
            if (! isdigit(c))
            {
                flag = false;
            }
            else
            {
                flag = true;
            }
        }

    }
    return flag;
}