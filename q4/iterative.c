/* FIXME: Implement! */

int maxSubArray(int* nums, int numsSize)
{
    int i , t = 0 , total = nums[0];
    for( i = 0; i < numsSize; i++ ) {
        t += nums[i];
        total = ( total > t ) ? total : t;
        t = ( t < 0 ) ? 0 : t;
    }
    return total;
}
