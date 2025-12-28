#pragma once

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int key;
} WordData;

int insertSorted(WordData data[], int* count, const char* word, int key);
int hasDuplicateKeys(const WordData data[], int count);
int findByKey(const WordData data[], int count, int key);
int readFile(const char* filename, WordData data[], int* count);
