int Compare(const void *a,const void *b)
{
    return *(int*)b-*(int*)a;
}
int findKthLargest(int* nums, int numsSize, int k) {
    qsort(nums,numsSize,sizeof(int),Compare);
    return nums[k-1];
}
