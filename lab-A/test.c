#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include "word_manager.h"


/* 1 */
void TestInsertSorted_Empty_no1(void) {
    WordData data[MAX_WORDS];
    int count = 0;
    insertSorted(data, &count, "apple", 10);
    assert(count == 1);
    assert(data[0].key == 10);
}

/* 2 */
void TestInsertSorted_Begin_no2(void) {
    WordData data[MAX_WORDS] = { {"banana", 20} };
    int count = 1;
    insertSorted(data, &count, "apple", 5);
    assert(data[0].key == 5);
}

/* 3 */
void TestInsertSorted_End_no3(void) {
    WordData data[MAX_WORDS] = { {"apple", 10} };
    int count = 1;
    insertSorted(data, &count, "banana", 30);
    assert(data[1].key == 30);
}

/* 4 */
void TestInsertSorted_Middle_no4(void) {
    WordData data[MAX_WORDS] = { {"a", 10}, {"c", 30} };
    int count = 2;
    insertSorted(data, &count, "b", 20);
    assert(data[1].key == 20);
}

/* 5 */
void TestDuplicate_Found_no5(void) {
    WordData data[] = { {"a", 10}, {"b", 10} };
    assert(hasDuplicateKeys(data, 2) == 1);
}

/* 6 */
void TestDuplicate_NotFound_no6(void) {
    WordData data[] = { {"a", 10}, {"b", 20} };
    assert(hasDuplicateKeys(data, 2) == 0);
}

/* 7 */
void TestFind_Existing_no7(void) {
    WordData data[] = { {"a", 10}, {"b", 20}, {"c", 30} };
    assert(findByKey(data, 3, 20) == 1);
}

/* 8 */
void TestFind_Missing_no8(void) {
    WordData data[] = { {"a", 10}, {"b", 20} };
    assert(findByKey(data, 2, 99) == -1);
}

/* 9 */
void TestFind_Single_no9(void) {
    WordData data[] = { {"a", 10} };
    assert(findByKey(data, 1, 10) == 0);
}

/* 10 */
void TestInsertSorted_Overflow_no10(void) {
    WordData data[MAX_WORDS];
    int count = MAX_WORDS;
    assert(insertSorted(data, &count, "x", 1) == -1);
}

int test(void) {
    setlocale(LC_ALL, "RUS");
    TestInsertSorted_Empty_no1();
    TestInsertSorted_Begin_no2();
    TestInsertSorted_End_no3();
    TestInsertSorted_Middle_no4();
    TestDuplicate_Found_no5();
    TestDuplicate_NotFound_no6();
    TestFind_Existing_no7();
    TestFind_Missing_no8();
    TestFind_Single_no9();
    TestInsertSorted_Overflow_no10();

    printf("бяе 10 реярнб сяоеьмн опнидемш\n");
    return 0;
}
