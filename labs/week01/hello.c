#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Getting the name from user and saying hello to the user
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}