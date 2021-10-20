#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void print_matrix(int [MAX_VOTERS][MAX_CANDIDATES], int, int);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // print_matrix(preferences, voter_count, candidate_count);

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    // binary search
    int start = 0;
    int end = candidate_count - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        int compareResult = strcmp(name, candidates[mid].name);
        if (compareResult == 0)
        {
            // update preference
            preferences[voter][rank] = mid;
            return true;
        }
        else if (compareResult < 0)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0, j = 0; i < voter_count && j < candidate_count;)
    {
        int preference = preferences[i][j];

        // checking if preferred candidate is eliminated
        if (candidates[preference].eliminated == true)
        {
            j++;
        }
        else
        {
            candidates[preference].votes ++;
            i++;
            j = 0;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // winning votes should be more that half
        // for odd number: eg. 3 / 2 = 1 + 1 = 2 (more than half)
        // for even number: eg. 4 / 2 = 2 + 1 = 3 (more than half)
        int winning_votes = (voter_count / 2) + 1;
        if (candidates[i].votes == winning_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // assuming that first candidate has the minimum votes
    int min = 0;
    for (int i = 1; i < candidate_count; i++)
    {
        // skipping if candidate is eliminated
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        if (candidates[i].votes < candidates[min].votes)
        {
            min = i;
        }
    }
    return candidates[min].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        // for a tie, each candidate should have equal votes
        // so if a candidate is surely having min votes, each should have min votes
        if (candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // linear search
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

// Print the matrix
void print_matrix(int matrix[MAX_VOTERS][MAX_CANDIDATES], int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {

        // Query for each rank
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }
}