/* ============================================================
 * Rabin-Karp String Matching Algorithm using Rolling Hash
 * ============================================================
 * Description:
 * This program finds all occurrences of a pattern
 * inside a given text using the Rabin-Karp algorithm.
 * ============================================================ */

#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------
   d = Number of characters in input character set
   ASCII has 256 characters
------------------------------------------------------------ */
#define d 256

/* ------------------------------------------------------------
   q = Prime number used for hashing
------------------------------------------------------------ */
#define q 101

/* ============================================================
   Function: rabinKarp()
   Purpose : Implements Rabin-Karp string matching
   ============================================================ */
void rabinKarp(char text[], char pattern[])
{
    int n = strlen(text);      // Length of text
    int m = strlen(pattern);   // Length of pattern

    int i, j;

    int p_hash = 0;   // Hash value of pattern
    int t_hash = 0;   // Hash value of current text window

    int h = 1;

    int found = 0;

    /* --------------------------------------------------------
       Compute h = d^(m-1) % q
       Used to remove leftmost character contribution
    -------------------------------------------------------- */
    for(i = 0; i < m - 1; i++)
    {
        h = (h * d) % q;
    }

    /* --------------------------------------------------------
       Calculate initial hash values for:
       1. Pattern
       2. First window of text
    -------------------------------------------------------- */
    for(i = 0; i < m; i++)
    {
        p_hash = (d * p_hash + pattern[i]) % q;
        t_hash = (d * t_hash + text[i]) % q;
    }

    printf("\nPattern Hash = %d\n\n", p_hash);

    printf("-------------------------------------------------\n");
    printf("Window\tSubstring\tHash\tResult\n");
    printf("-------------------------------------------------\n");

    /* --------------------------------------------------------
       Slide pattern over text one by one
    -------------------------------------------------------- */
    for(i = 0; i <= n - m; i++)
    {
        printf("%d\t", i);

        /* Print current substring */
        for(j = 0; j < m; j++)
        {
            printf("%c", text[i + j]);
        }

        printf("\t\t%d\t", t_hash);

        /* ----------------------------------------------------
           If hash values match,
           verify characters one by one
        ---------------------------------------------------- */
        if(p_hash == t_hash)
        {
            int match = 1;

            for(j = 0; j < m; j++)
            {
                if(text[i + j] != pattern[j])
                {
                    match = 0;
                    break;
                }
            }

            /* ------------------------------------------------
               If all characters matched
            ------------------------------------------------ */
            if(match)
            {
                printf("MATCH FOUND");
                found = 1;
            }
            else
            {
                printf("SPURIOUS HIT");
            }
        }
        else
        {
            printf("NO MATCH");
        }

        printf("\n");

        /* ----------------------------------------------------
           Compute hash for next window
           Remove left character and add next character
        ---------------------------------------------------- */
        if(i < n - m)
        {
            t_hash = (d * (t_hash - text[i] * h)
                     + text[i + m]) % q;

            /* ------------------------------------------------
               Convert negative hash to positive
            ------------------------------------------------ */
            if(t_hash < 0)
            {
                t_hash = t_hash + q;
            }
        }
    }

    printf("-------------------------------------------------\n");

    /* --------------------------------------------------------
       Final Search Summary
    -------------------------------------------------------- */
    printf("\nSearch Complete.\n");

    if(!found)
    {
        printf("Pattern NOT FOUND in text.\n");
    }
    else
    {
        printf("Pattern found. See MATCH FOUND rows above.\n");
    }
}

/* ============================================================
   Main Function
   ============================================================ */
int main()
{
    char text[1000];
    char pattern[100];

    /* --------------------------------------------------------
       Input text and pattern
    -------------------------------------------------------- */
    printf("Enter Text    : ");
    scanf("%s", text);

    printf("Enter Pattern : ");
    scanf("%s", pattern);

    /* --------------------------------------------------------
       Edge Case:
       Pattern length greater than text length
    -------------------------------------------------------- */
    if(strlen(pattern) > strlen(text))
    {
        printf("\nPattern length is greater than text length.\n");
        return 0;
    }

    /* --------------------------------------------------------
       Display input
    -------------------------------------------------------- */
    printf("\nText    : %s", text);
    printf("\nPattern : %s\n", pattern);

    /* --------------------------------------------------------
       Call Rabin-Karp function
    -------------------------------------------------------- */
    rabinKarp(text, pattern);

    return 0;
}