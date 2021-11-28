#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];

// n(n-2)/2 = No. of pairs that can occur for n
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void print_matrix(int [MAX][MAX], int, int);
bool is_cycle(int, int);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();

    // print_matrix(preferences, candidate_count, candidate_count);

    sort_pairs();
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("\n%i : %i : %i\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    // }

    lock_pairs();

    // printf("\nLocked Matrix:\n");
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%d ", locked[i][j]);
    //     }
    //     printf("\n");
    // }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // binary search
    int start = 0, end = candidate_count - 1;
    while (start <= end)
    {
        int mid = start + (end - start) / 2;
        int match = strcmp(name, candidates[mid]);
        if (match == 0)
        {
            ranks[rank] = mid;
            return true;
        }
        else if (match < 0)
        {
            end = mid = 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // candidate a is not preferred over candidate a
            if (i == j)
            {
                continue;
            }

            // Checking if the number of users who prefered candidate
            // i over candidate j are more than the vice versa
            int winner = 0, loser = 0;
            if (preferences[i][j] > preferences[j][i])
            {
                winner = i;
                loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                winner = j;
                loser = i;
            }
            else
            {
                continue;
            }
            pairs[pair_count].winner = winner;
            pairs[pair_count].loser = loser;
            pair_count++;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // think which sort algo to use
    // should not use the merge sort, because the sort function (void)

    // implementing bubble sort
    int swap = -1;
    int pass = 0;
    while (swap != 0)
    {
        swap = 0;
        for (int i = 0; i < pair_count - pass - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                // swapping
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;

                // incrementing the swap counter
                swap++;
            }
        }

        // incrementing the pass counter
        pass++;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (is_cycle(winner, loser) == false)
        {
            locked[winner][loser] = true;
        }
    }
}

// Check if the pair creates a cycle
bool is_cycle(int winner, int loser)
{
    bool result = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == true)
        {
            if (loser == i)
            {
                return true;
            }
            else
            {
                winner = i;
                result = is_cycle(winner, loser);
            }
        }
    }
    return result;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    for (int i = 0; i < candidate_count; i++)
    {
        bool flag = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 1)
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            printf("%s\n", candidates[i]);
            break;
        }

    }
    return;
}

// Print the matrix
void print_matrix(int matrix[MAX][MAX], int rows, int columns)
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