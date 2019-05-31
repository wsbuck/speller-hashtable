// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

unsigned int hash(char *str)
{
   unsigned long hash = 5381;
   int c;
   while ((c = *str++)) {
       hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash % N;
}

void lower_string(char *word) {
    for (int i = 0; i < strlen(word); i++) {
        word[i] = tolower(word[i]);
    }
}

bool string_compare(char *word1, char *word2) {
    for (int i = 0; ; i++) {
        if (tolower(word1[i]) != tolower(word2[i])) {
        // if (word1[i] != word2[i]) {
            return false;
        } else if (word1[i] == '\0') {
            return true;
        }
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) {
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF) {
        int hash_code = hash(word);
        node *n = malloc(sizeof(node));
        if (!n) {
            return 1;
        }

        strcpy(n->word, word);
        n->next = NULL;

        if (hashtable[hash_code]) {
            n->next = hashtable[hash_code];
        }
        hashtable[hash_code] = n;
        // printf("%s\n", n->word);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) {
    int counter = 0;
    for (int i = 0; i < N; i++) {
        for (node *ptr = hashtable[i]; ptr != NULL; ptr = ptr->next) {
            counter++;
            // printf("%s, count: %i\n", ptr->word, counter);
        }
    }
    return counter;
}

// Returns true if word is in dictionary else false
bool check(char *word) {
    lower_string(word);
    int i = hash(word);
    for (node *ptr = hashtable[i]; ptr; ptr = ptr->next) {
        if (string_compare(ptr->word, word)) {
            return true;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) {
    for (int i = 0; i < N; i++) {
        node *ptr = hashtable[i];
        while (ptr != NULL) {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}