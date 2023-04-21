//Mykel Modeste
//April 20, 20203
//COP 3502

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET 26

struct Trie{
    struct Trie *child[ALPHABET];
    int counter;
    int endOfWord;
};

struct Trie *init()//Initialize the Trie
{
    int i;
    struct Trie *trie = (struct Trie*)malloc(sizeof(struct Trie));

    if(trie == NULL)
    {
        printf("Unable to allocate memory");
        exit(-1);
    }

    trie->endOfWord = 0;
    trie->counter = 0;

    for(i = 0; i < ALPHABET; i++)
    {
        trie->child[i] = NULL;
    }
    return trie;
}


void insert(struct Trie **ppTrie, char *word)
{
    int i, index;
    struct Trie* trie = *ppTrie;
    int size = strlen(word);

    for(i = 0; i < size; i++)
    {
        index = word[i] - 'a';

        if(trie->child[index] == NULL)
        {
            trie->child[index] = init();
        }
        trie = trie->child[index];
    }

    if(!trie->endOfWord)
    {
        trie->counter++;
    }
    trie->endOfWord = 1;
}


int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int i, index;
    struct Trie* trie = pTrie;
    int size = strlen(word);

    for(i = 0; i < size; i++)
    {
        index = word[i] - 'a';

        if(trie->child[index] == NULL)
        {
            return 0;
        }
        trie = trie->child[index];
    }
    if(trie != NULL && trie->endOfWord)
    {
        return trie->counter;
    }
    else{
        return 0;
    }


}


struct Trie *deallocateTrie(struct Trie *pTrie)
{
    int i;
    if(pTrie == NULL)
    {
        return NULL;
    }

    for(i = 0; i < ALPHABET; i++)
    {
        pTrie->child[i] = deallocateTrie(pTrie->child[i]);
    }

    free(pTrie);
    return NULL;
}


int main(void)
{
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct Trie* trie = init();

    for (int i = 0; i < 5; i++)
        insert(&trie, pWords[i]);

    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}