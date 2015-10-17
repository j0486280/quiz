#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_INPUT_SIZE 10000
#define LISTNODE_MAX_LENGTH 1000
#define OVERFLOWLENGTH 33

#define DATA_PATH "data/data.txt"

typedef struct TreeNode {
    char val[OVERFLOWLENGTH];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *buildTreeNode(char *argu[], int numSize )
{
    TreeNode *nodeArray[10000];
    int index = 0,tail = 0,flag = 0,_NULL, i;
    for( i = 0; i < numSize; i++ ) {
        _NULL = strcmp(argu [i] , "null" );
        TreeNode *node = NULL;
        if(0 != _NULL) {
            node = malloc(sizeof(TreeNode *));
            strcpy(node-> val, argu[i]);
            node -> left = NULL;
            node -> right = NULL;
        }

        if( index < tail ) {
            if(flag == 0) nodeArray[index]->left =node;
            else nodeArray[index]->right = node;
            index = (flag == 1)? index +1 : index;
            flag = (flag + 1)%2;
        }

        if(0 !=_NULL)
            nodeArray[tail++]=node;
    }

    return nodeArray[0];
}

int getIntArray(char *str, char *out[])
{

    assert( strlen(str) != 0 && "You input empty array !!!");
    int i = 0 ,count = 0,index = 0;
    char num[OVERFLOWLENGTH];

    while( str[i] != '\0' ) {
        if(str[i] == ',') {
            num[index] = '\0';
            out[count] = malloc(sizeof(char)*index);
            strcpy(out[count],num) ;
            index = 0;
            count++;
        } else {
            assert( ((index < OVERFLOWLENGTH) && (index != (OVERFLOWLENGTH-1) || num[0] != '-')) && "Input value is overflow !!!");
            num[index++] = str[i];
        }
        i++;
    }
    num[index] = '\0';
    out[count] = malloc(sizeof(char)*index);
    strcpy(out[count],num) ;

    return ++count;
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

void printTreeNode(TreeNode *head)
{
    TreeNode *nodeArray[10000];
    int index = 0,tail = 0;
    nodeArray[tail++]=head;
    while( index != tail ) {
        if(nodeArray[index] == NULL)
            printf("null\t");
        else {
            printf("%s\t",nodeArray[index]->val);
            if(nodeArray[index] -> left != NULL || nodeArray[index] -> right != NULL ) {
                nodeArray[tail++] = nodeArray[index] -> left;
                nodeArray[tail++] = nodeArray[index] -> right;
            }
        }
        index++;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_INPUT_SIZE];
    struct timespec start, end;
    double cpu_time=0;
    char *argu[LISTNODE_MAX_LENGTH];
    struct TreeNode *head;
    int inputarray_len;

    fp = fopen(DATA_PATH, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;

        line[i - 1] = '\0';
        i = 0;
        initialize();
        inputarray_len = getIntArray(line,argu);
        assert( inputarray_len < LISTNODE_MAX_LENGTH && "Array length overflow !!!");
        head = buildTreeNode(argu,inputarray_len);
        clock_gettime(CLOCK_REALTIME, &start);
        flatten(head);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time += diff_in_second(start, end);
        printf("answer : ");
        printTreeNode(head);
    }

    printf("execution time : %lf sec\n", cpu_time);

    return 0;
}
