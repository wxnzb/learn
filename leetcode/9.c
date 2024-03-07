static void swap(int nums[],int a,int b)
{
    int tmp=nums[a];
    nums[a]=nums[b];
    nums[b]=tmp;
}
int firstMissingPositive(int* nums, int numsSize) {
  for(int i=0;i<numsSize;)
  {
      int val=nums[i];
      if(val>0&&val<=numsSize&&val!=i+1&&nums[val-1]!=val)
      swap(nums,i,val-1);
      else
      i++;
  }  
  for(int i=0;i<numsSize;i++)
  {
      if(nums[i]!=i+1)
      return i+1;
  }
  return  numsSize+1;
}
