/* FIXME: Implement! */
#include <stdio.h>
#include <stdlib.h>

#define OVERFLOWLENGTH 33

typedef struct TreeNode {
    char val[OVERFLOWLENGTH];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void flatten( struct TreeNode* root )
{
    struct TreeNode* now = root;
    while( now != NULL ) {
        if( now -> left != NULL ) {
            struct TreeNode* prev = now -> left;
            while( prev -> right != NULL )
                prev = prev -> right;
            prev -> right = now -> right;
            now -> right = now -> left;
            now -> left = NULL;
        }
        now = now -> right;
    }
}

void initialize() {}
