#define _CRT_SECURE_NO_WARNINGS
#include "word_manager.h"
#include <stdio.h>
#include <string.h>

int insertSorted(WordData data[], int* count, const char* word, int key) {
    if (*count >= MAX_WORDS) {
        return -1;
    }

    int pos = 0;
    while (pos < *count && data[pos].key < key) {
        pos++;
    }

    for (int i = *count; i > pos; i--) {
        data[i] = data[i - 1];
    }

    strcpy(data[pos].word, word);
    data[pos].key = key;
    (*count)++;

    return pos;
}

int hasDuplicateKeys(const WordData data[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (data[i].key == data[j].key) {
                return 1;
            }
        }
    }
    return 0;
}

int findByKey(const WordData data[], int count, int key) {
    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (data[mid].key == key) {
            return mid;
        }
        if (data[mid].key < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int readFile(const char* filename, WordData data[], int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char word[MAX_WORD_LENGTH];
    int key;

    while (fscanf(file, "%49s %d", word, &key) == 2) {
        insertSorted(data, count, word, key);
    }

    fclose(file);
    return 0;
}
