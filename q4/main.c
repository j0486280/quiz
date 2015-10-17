#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_INPUT_SIZE 10000
#define LISTNODE_MAX_LENGTH 1000
#define OVERFLOWLENGTH 33

#define DATA_PATH "data/data.txt"

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

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0,out;
    char line[MAX_INPUT_SIZE];
    struct timespec start, end;
    double cpu_time;
    int argu [LISTNODE_MAX_LENGTH];
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
        inputarray_len = getIntArray(line,argu);
        assert( inputarray_len < LISTNODE_MAX_LENGTH && "Array length overflow !!!");
        clock_gettime(CLOCK_REALTIME, &start);
        out = maxSubArray(argu,inputarray_len);
        clock_gettime(CLOCK_REALTIME, &end);
        cpu_time += diff_in_second(start, end);
        printf("answer : %d\n",out);
    }

    printf("execution time : %lf sec\n", cpu_time);

    return 0;
}
