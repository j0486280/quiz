#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_INPUT_SIZE 10000
#define LISTNODE_MAX_LENGTH 1000
#define OVERFLOWLENGTH 33

#define DATA_PATH "data/data.txt"
#define INPUT_STATUS_ARRAY 0
#define INPUT_STATUS_M 1
#define INPUT_STATUS_N 2

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

ListNode *buildListNode(int *argu, int numSize )
{
    ListNode *head, *now;
    head = malloc(sizeof(ListNode *));
    head -> next = NULL;
    now = head;

    int i;
    for( i = 0; i < numSize; i++ ) {
        ListNode *node = malloc(sizeof(ListNode *));
        node -> val = argu [i];
        node -> next = NULL;
        now -> next = node;
        now = node;
    }

    return head -> next;
}

int getIntArray(char *str, int *out)
{
    assert( strlen(str) != 0 && "You input empty array !!!");
    int i = 0 ,count = 0,index = 0;
    char num[OVERFLOWLENGTH];
    while( str[i] != '\0' ) {
        if(str[i] == ',') {
            num[index] = '\0';
            out[count++] = atoi(num);
            index = 0;
        } else {
            assert( ((index < OVERFLOWLENGTH) && (index != (OVERFLOWLENGTH-1) || num[0] != '-')) && "Input value is overflow !!!");
            num[index++] = str[i];
        }
        i++;
    }

    num[index] = '\0';
    out[count++] = atoi(num);

    return count;
}

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

void printListNode(ListNode *head)
{
    ListNode *now = head;
    while(now != NULL) {
        printf("%d\t",now -> val);
        now = now -> next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0, count = 0,status = INPUT_STATUS_ARRAY;
    char line[MAX_INPUT_SIZE],input[MAX_INPUT_SIZE];
    struct timespec start, end;
    double cpu_time =0;
    int argu [LISTNODE_MAX_LENGTH];
    struct ListNode *head,*out;
    int inputarray_len;
    int argu_m,argu_n;

    fp = fopen(DATA_PATH, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    while (fgets(line, sizeof(line), fp)) {
        while(1) {
            while (line[i] != '\0' && line[i] != '\t') {
                input[count++]=line[i];
                i++;
            }
            input[count] = '\0';
            count = 0;
            switch(status) {
                case INPUT_STATUS_ARRAY:
                    inputarray_len = getIntArray(input,argu);
                    break;
                case INPUT_STATUS_M:
                    argu_m = atoi(input);
                    break;
                case INPUT_STATUS_N:
                    argu_n = atoi(input);
                    break;
            }

            status = (line[i] == '\0' ) ? 0 : status + 1;

            if(line[i] == '\0') {
                assert( inputarray_len < LISTNODE_MAX_LENGTH && "Array length overflow !!!");
                head = buildListNode(argu,inputarray_len);
                clock_gettime(CLOCK_REALTIME, &start);
                out = reverseBetween(head,argu_m,argu_n);
                clock_gettime(CLOCK_REALTIME, &end);
                cpu_time += diff_in_second(start, end);
                printf("answer : ");
                printListNode(out);
                i = 0;
                break;
            }
            i++;
        }
    }
    printf("execution time : %lf sec\n", cpu_time);

    return 0;
}
