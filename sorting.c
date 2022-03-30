#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct SortResult {
    unsigned long long swaps;
    unsigned long long comparisons;
} SortResult;

void swap(int *left, int *right) {
    int temp = *left;
    *left = *right;
    *right = temp;
}

SortResult merger(int arr[], int num, int depth) {
    unsigned long long swaps = 0, comparisons = 0;
    if (num == 1) {
        return (SortResult){0};
    }
    if (num == 2) {
        if (arr[0] > arr[1]) {
            swap(arr, arr + 1);
            swaps++;
        }
        return (SortResult){swaps, 1};
    }
    int half = num / 2;
    int leftlen = num - half;
    merger(arr, leftlen, depth + 1);
    merger(arr + leftlen, half, depth + 1);
    int left = 0, right = leftlen;
    int *mergearr = malloc(sizeof(mergearr) * num);
    int k = 0;
    while (left < leftlen && right < num) {
        if (arr[left] > arr[right]) {
            mergearr[k++] = arr[right++];
        } else {
            mergearr[k++] = arr[left++];
        }
        comparisons++;
    }
    while (left < leftlen) {
        mergearr[k++] = arr[left++];
    }
    while (right < num) {
        mergearr[k++] = arr[right++];
    }
    for (int i = 0; i < num; i++) {
        arr[i] = mergearr[i];
    }
    free(mergearr);
    return (SortResult){swaps, comparisons};
}

SortResult merge(int arr[], int num) {
    return merger(arr, num, 0);
}

SortResult insertion(int arr[], int num) {
    unsigned long long swaps = 0, comparisons = 0;
    for (int i = 1; i < num; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] < arr[j]) {
                swap(arr + i, arr + j);
                swaps++;
            }
            comparisons++;
        }
    }
    return (SortResult){swaps, comparisons};
}

#include <memory.h>

SortResult radix(int arr[], int num) {
    unsigned long long swaps = 0, comparisons = 0;
    int numbits = 16;
    int *buckets = malloc(numbits * num * sizeof(*buckets));
    int bucket_num[16] = {0};
    int *new_bucket = malloc(numbits * num * sizeof(*buckets));
    int new_bucket_num[16] = {0};
    int *bucket_ptr = &buckets[0];
    int *new_bucket_ptr = &new_bucket[0];
    for (int j = 0; j < num; j++) {
        int buck = arr[j] & 0b1111;
        buckets[buck * num + bucket_num[buck]++] = arr[j];
    }
    for (int i = 1; i < sizeof(int) * 8 / 4; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < bucket_num[j]; k++) {
                int number = bucket_ptr[j * num + k];
                int buck = (number >> (4 * i)) & 0b1111;
                new_bucket_ptr[num * buck + new_bucket_num[buck]++] = number;
            }
        }
        int *tmp = new_bucket_ptr;
        new_bucket_ptr = bucket_ptr;
        bucket_ptr = tmp;
        memcpy(bucket_num, new_bucket_num, sizeof(new_bucket_num));
        memset(new_bucket_num, 0, sizeof(new_bucket_num));
    }
    int i = 0;
    for (int j = 0; j < 16; j++) {
        for (int k = 0; k < bucket_num[j]; k++) {
            arr[i++] = buckets[j * num + k];
        }
    }
    
    return (SortResult){swaps, comparisons};
}

SortResult selection(int arr[], int num) {
    unsigned long long swaps = 0;
    unsigned long long comparisons = 0;
    for (int i = 0; i < num - 1; i++) {
        int lowidx = i;
        for (int j = i + 1; j < num; j++) {
            if (arr[j] < arr[lowidx]) {
                lowidx = j;
            }
            comparisons++;
        }
        swap(arr + i, arr + lowidx);
        swaps++;
    }
    return (SortResult){swaps, comparisons};
}

SortResult mysort(int arr[], int numele) {
    unsigned long long swaps = 0, comparisons = 0;
    int *st = arr;
    int *end = arr + numele - 1;

    while (st != end) {
        // find the lowest
        int *lowest = st;
        int *highest = end;
        for (int *i = st; i <= end; i++) {
            if (*i < *lowest) {
                lowest = i;
            }
            if (*i > *highest) {
                highest = i;
            }
            comparisons += 2;
        }
        if (lowest == highest) {
            break;
        }
        if (lowest == end && highest == st) {
            swap(st++, end--);
            swaps++;
        } else if (lowest == end) {
            swap(st++, lowest);
            swap(end--, highest);
            swaps += 2;
        } else {
            swap(end--, highest);
            swap(st++, lowest);
            swaps += 2;
        }
    }
    return (SortResult){swaps, comparisons};
}

void push(int *s, int *idx, int i) {
    s[*idx] = i;
    (*idx)++;
}

int pop(int *s, int *idx) {
    (*idx)--;
    return s[*idx];
}

SortResult nijoanSort(int arr[], int num) {
    // x is unsorted
    // r is result
    // y is stack which contains the biggest number
    // z is discard
    int x[num], y[num], z[num];
    int xi = num, ri = 0, yi = 0, zi = 0;
    memcpy(x, arr, num * sizeof(*arr));
    while (xi > 0) {
        push(y, &yi, pop(x, &xi));
        while (xi > 0) {
            int k = pop(x, &xi);
            if (y[yi - 1] > k) {
                push(y, &yi, k);
            } else {
                push(z, &zi, k);
            }
        }
        push(arr, &ri, pop(y, &yi));
        while (yi) {
            push(x, &xi, pop(y, &yi));
        }
        while (zi) {
            push(x, &xi, pop(z, &zi));
        }
    }
    return (SortResult){0};
}

int cmpints(void const *leftp, void const *rightp) {
    int left = *(int *)leftp;
    int right = *(int *)rightp;
    return (left > right) - (left < right);
}

SortResult quicks(int arr[], int num) {
    qsort(arr, num, sizeof(*arr), cmpints);
    return (SortResult){0};
}

_Bool time_and_print(int arr[], int num, char *name, SortResult (*fn)(int arr[], int num)) {
    float start = (float)clock() / CLOCKS_PER_SEC;
    SortResult s = fn(arr, num);
    float end = (float)clock() / CLOCKS_PER_SEC;
    float diff = end - start;
    int prev = arr[0];
    for (int i = 1; i < num; i++) {
        if (prev > arr[i]) {
            printf("%d is not less than %d", prev, arr[i]);
            printf("Sort completed in %.2fs but did not sort by %s\n", diff, name);
            return 0;
        }
        prev = arr[i];
    }
    if (diff > 1) {
        printf("Sort completed in %.2fs with (name: %s, n: %d, swaps: %lld, comparisons: %lld)\n", diff, name, num, s.swaps, s.comparisons);
    } else {
        printf("Sort completed in %.2fms with (name: %s, n: %d, swaps: %lld, comparisons: %lld)\n", diff * 1000, name, num, s.swaps, s.comparisons);
    }
    return 1;
}


struct {
    char *name;
    SortResult (*fn)(int arr[], int num);
} sortingfns[] = {
    {"selection", selection},
    {"mysort", mysort},
    {"insertion", insertion},
    {"merge", merge},
    {"radix", radix},
    {"quick", quicks},
    {"nijoanSort", nijoanSort},
};

int main() {
    srand((unsigned) time(NULL));
    int numele = 0;
    int *orig = NULL;
    for (;;) {
        printf("elements: %d\n"
            "[0] set dataset\n"
            "[1] select sorting algo\n"
            "[2] compare all sorting algos\n", numele);
        int inp;
        scanf("%d", &inp);
        switch (inp)
        {
        case 0:
            printf("how many elements?\n");
            scanf("%d", &numele);
            free(orig);
            orig = malloc(sizeof(*orig) * numele);
            printf("[0] random dataset with n eles\n"
                   "[1] dataset reverse sorted\n"
                   "[2] dataset with 2 numbers swapped\n");
            scanf("%d", &inp);
            switch (inp)
            {
            case 0:
                for (int i = 0; i < numele; i++) {
                    orig[i] = rand() % 100;
                }
                break;
            case 1:
                for (int i = 0; i < numele; i++) {
                    orig[i] = numele - i;
                }
                break;
            case 2:
                for (int i = 0; i < numele; i++) {
                    orig[i] = i;
                }
                swap(orig, orig + 1);
                break;
            default:
                break;
            }
            break;
        case 1:
            printf("which algorithm?\n");
            for (size_t i = 0; i < sizeof(sortingfns)/sizeof(*sortingfns); i++) {
                printf("[%ld] %s\n", i, sortingfns[i].name);
            }
            scanf("%d", &inp);
            if ((unsigned)(inp) < sizeof(sortingfns)/sizeof(*sortingfns)) {
                int *arr = malloc(sizeof(*orig) * numele);
                memcpy(arr, orig, sizeof(*orig) * numele);
                if (!time_and_print(arr, numele, sortingfns[inp].name, sortingfns[inp].fn)) {
                    for (size_t i = 0; i < numele; i++)
                    {
                        printf("%x, ", arr[i]);
                    }
                    printf("\n");
                }
                free(arr);
            }
            break;
        case 2:
            for (size_t i = 0; i < sizeof(sortingfns)/sizeof(*sortingfns); i++) {
                int *arr = malloc(sizeof(*orig) * numele);
                memcpy(arr, orig, sizeof(*orig) * numele);
                if (!time_and_print(arr, numele, sortingfns[i].name, sortingfns[i].fn)) {
                    for (size_t i = 0; i < numele; i++)
                    {
                        printf("%x, ", arr[i]);
                    }
                    printf("\n");
                }
                free(arr);
            }
            break;
        default:
            break;
        }
    }
    free(orig);
    return 0;
}