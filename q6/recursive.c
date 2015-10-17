/* FIXME: Implement! */
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    if( n == 1 ) return head;
    struct ListNode* now = reverseBetween(head->next,m-1,n-1);
    if( m <= 1 ) {
        struct ListNode* t = head -> next;
        head -> next = t -> next;
        t -> next = head;
        head = now;
    } else	head -> next = now;
    return head;
}
