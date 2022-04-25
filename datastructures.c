typedef struct BST BST;

struct BST {
    int key;
    BST *left, *right;
};

#include <malloc.h>

BST *newbst(void) {
    BST *b = malloc(sizeof(BST));
    *b = (BST){0};
    return b;
}

BST *insert(BST *bst, int key) {
    BST *orig = bst;
    BST *to_insert = newbst();
    to_insert->key = key;
    if (!bst) {
        return to_insert;
    }
    for (;;) {
        BST **next = NULL;
        if (bst->key < key) {
            next = &bst->right;
        } else {
            next = &bst->left;
        }
        if (!*next) {
            *next = to_insert;
            return orig;
        }
        bst = *next;
    }
}



#define MAX(a,b) ((a) < (b) ? (b) : (a))

#include <math.h>

typedef struct vallist {
    int *k;
    int numk;
} vallist;

vallist flatten_bst(BST *bst) {
    if (!bst) return (vallist){0};
    vallist left = flatten_bst(bst->left);
    vallist right = flatten_bst(bst->right);
    vallist s;
    s.numk = left.numk + right.numk + 1;
    s.k = malloc(s.numk * sizeof(*s.k));
    for (size_t i = 0; i < left.numk; i++) {
        s.k[i] = left.k[i];
    }
    s.k[left.numk] = bst->key;
    for (size_t i = 0; i < right.numk; i++) {
        s.k[i + left.numk + 1] = right.k[i];
    }
    return s;
}

int max_depth_bst(BST *bst) {
    if (!bst) return 0;
    int left = max_depth_bst(bst->left);
    int right = max_depth_bst(bst->right);
    return MAX(left, right) + 1;
}

void print_bst__(BST *bst, int space) {
    if (!bst) return;
    space += 2;
    print_bst__(bst->right, space);
    for (int i = 2; i < space; i++)
        printf(" ");
    printf("%d\n", bst->key);
    print_bst__(bst->left, space);
}

void print_bst(BST *bst) {
    print_bst__(bst, 0);
    return;
    vallist l = flatten_bst(bst);
    if (!l.numk) {
        printf("[]");
    }
    printf("[%d", l.k[0]);
    for (size_t i = 1; i < l.numk; i++) {
        printf(", %d", l.k[i]);
    }
    printf("]\n");
}

int main() {
    int asd[] = {2,13,1,2,3,5,1,12,3,1,99,12,-1,3,21,4};
    int n = sizeof(asd)/sizeof(*asd);
    BST *b = insert(NULL, asd[0]);
    for (size_t i = 1; i < n; i++)
    {
        insert(b, asd[i]);
    }
    print_bst(b);
}