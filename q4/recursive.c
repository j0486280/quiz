/* FIXME: Implement! */

static int t;
int maxSubArray(int* nums, int numsSize)
{
    if( numsSize == 1 ) return t = nums[0];
    int max = maxSubArray( nums ,numsSize -1 );
    t = (t < 0 )? 0 : t;
    t += nums[numsSize - 1];
    max =( max > t ) ? max : t;
    return max;
}
