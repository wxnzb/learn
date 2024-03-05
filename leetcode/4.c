int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
  int** ans=(int**)malloc(sizeof(int*)*(1<<numsSize));
  *returnColumnSizes = malloc(sizeof(int) * (1 << numsSize));
  *returnSize=1<<numsSize;
  int z[numsSize];
  for(int i=0;i<(1<<numsSize);i++)
  {
      int t=0;
      for(int j=0;j<numsSize;j++)
      {
          if(i&(1<<j))
          {
            z[t++]=nums[j];
          }
      }
      int* tmp=(int*)malloc(sizeof(int)*t);
      memcpy(tmp,z,sizeof(int)*t);
      (*returnColumnSizes)[i]=t;
      ans[i]=tmp;
  } 
  return ans;
}
