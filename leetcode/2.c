int a(struct TreeNode* root,int b)
 {
     if(root==NULL)
     return 0;
     int sum=b*10+root->val;
     if(root->left==NULL&&root->right==NULL)
      return sum;
      else
      return a(root->left,sum)+a(root->right,sum);
 }
int sumNumbers(struct TreeNode* root) {
    return a(root,0);
}

