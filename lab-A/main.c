#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "word_manager.h"

int main(void) {
    WordData data[MAX_WORDS];
    int count = 0;

    if (readFile("1.txt", data, &count) != 0) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    if (hasDuplicateKeys(data, count)) {
        printf("Ошибка: найдены одинаковые ключи\n");
        return 1;
    }

    printf("Список слов (отсортирован по ключам):\n");
    for (int i = 0; i < count; i++) {
        printf("%-12s %d\n", data[i].word, data[i].key);
    }

    int key;
    printf("\nВведите ключ для поиска: ");
    scanf("%d", &key);

    int index = findByKey(data, count, key);
    if (index >= 0) {
        printf("Найдено слово: %s\n", data[index].word);
    }
    else {
        printf("Слово не найдено\n");
    }

    return 0;
}
