/* intro to pointers */

/* Helper
 * Swaps two characters
 */
void swapc(char *c1, char *c2) {
    char tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}

#include <string.h>

/* Task 2 "Baglæns"
 * Reverses a string
 * Expects a mutable string terminating in '\0'
 */
void reverse_str(char *str) {
    /* Take half the length because the loop will go from both
     * the left and right sides of the string and meet at the middle */
    size_t strl = strlen(str);
    size_t half_len = strl / 2;
    for (int i = 0; i < half_len; i++) {
        /* Take the chars from postion i from the left and right of the string */
        swapc(&str[i], &str[strl - i - 1]);
    }
}

#include <stdlib.h>

/* Helper
 * Compares 2 integers and returns -1, 0, or 1 depending
 * on if int1 is less than, equal to, or greater than int2
 * You can swap the left and right to get a descending order instead
 */
int compare_integers(void const *int1, void const *int2) {
    int left = *(int *)int1;
    int right = *(int *)int2;
    return (left > right) - (left < right);
}

/* Task 3 "Sortering"
 * Sorts an array of ints
 * Expecs a mutable array of integers
 */
void sort_int_array(int *arr, int num_ints) {
    qsort(arr, num_ints, sizeof(int), compare_integers);
}

#include <ctype.h>
#include <stdio.h>

/* Task 4 "Tæl ord"
 * Counts the words of a given string
 * Expects a string terminating in '\0'
 */
int word_count(char const *str) {
    int num_words = 0;
    while (*str) {
        if (isalpha(*str)) {
            /* Skip to the end of the word */
            while (isalpha(*str)) {
                str++;
            }
            num_words++;
        } else {
            /* Skip non-alphabetic character */
            str++;
        }
    }
    return num_words;
}

/* Helper
 * Compares 2 integers and returns -1, 0, or 1 depending
 * on if str1 is less than, equal to, or greater than str2
 * You can swap the left and right to get a descending order instead
 */
int compare_strings(void const *str1, void const *str2) {
    char *left = *(char **)str1;
    char *right = *(char **)str2;
    return strcmp(left, right);
}

/* Task 5 "Sorter ord"
 * Sorts 
 */
void sort_words(char const *str) {
    /* This means we have to run through the string twice but only need 1 allocation
     *  */
    int num_words = word_count(str);
    char **words = malloc(num_words * sizeof(* words));
    int current_word = 0;
    for (size_t i = 0; str[i];) {
        if (isalpha(str[i])) {
            int word_start = i;
            /* Skip to the end of the word */
            while (isalpha(str[i])) {
                i++;
            }
            /* Allocate a new string and copy it over */
            int word_len = i - word_start;
            char *new_word = malloc(word_len + 1);
            memcpy(new_word, &str[word_start], word_len);
            /* Null terminate the string */
            new_word[word_len] = '\0';
            words[current_word] = new_word;
            current_word++;
        } else {
            /* Skip non-alphabetic character */
            i++;
        }
    }
    qsort(words, num_words, sizeof (*words), compare_strings);
    printf("words sorted: \"");
    for (size_t i = 0; i < num_words; i++)
    {
        if (i) {
            printf(" ");
        }
        printf("%s", words[i]);
    }
    printf("\"\n");

    /* Free all the words */
    for (size_t i = 0; i < num_words; i++)
    {
        free(words[i]);
    }
    free(words);
}


/* Macro to get amount of elements of an array
 * DOES NOT WORK WITH heap allocated memory
 */
#define ARR_S(arr) (sizeof(arr)/sizeof(*(arr)))

int main() {
    char words_string[] = "the quick brown fox jumped over the lazy dog";
    
    /* Task 2 */
    printf("%s\n", words_string);
    reverse_str(words_string);
    printf("%s\n", words_string);
    reverse_str(words_string);
    printf("%s\n", words_string);
    /* End Task 2 */
    
    /* Task 3 */
    int arr[] = {231, 123, 2, 35, 63, 0, -1, -34, 34};

    for (size_t i = 0; i < ARR_S(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort_int_array(arr, ARR_S(arr));

    for (size_t i = 0; i < ARR_S(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    /* End Task 3 */

    /* Task 4 */
    int num_words = word_count(words_string);
    printf("number of words: %d for string \"%s\"\n", num_words, words_string);
    /* End Task 4 */

    /* Task 5 */
    sort_words(words_string);
    /* End Task 5 */

    return 0;
}