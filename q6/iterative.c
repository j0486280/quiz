/* FIXME: Implement! */
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    struct ListNode *root = malloc(sizeof(struct ListNode*));
    root->next = head;

    int i;
    struct ListNode *prev = root,*start,*tail;
    for( i = 0; i < m - 1; i++ )
        prev = prev -> next;

    start = prev -> next;
    tail = start -> next;

    for( i =0; i<n-m; i++ ) {
        start -> next = tail -> next;
        tail -> next = prev -> next;
        prev -> next = tail;
        tail = start -> next;
    }

    head = root -> next;
    free(root);

    return root->next;
}
