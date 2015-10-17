/* FIXME: Implement! */
#include <stdio.h>
#include <stdlib.h>

#define OVERFLOWLENGTH 33

typedef struct TreeNode {
    char val[OVERFLOWLENGTH];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static struct TreeNode* prev;

void flatten(struct TreeNode* root)
{
    if ( root == NULL ) return;

    flatten(root-> right);
    flatten(root -> left);
    root -> right = prev;
    root -> left = NULL;
    prev = root;
}

void initialize()
{
    prev = NULL;
}
