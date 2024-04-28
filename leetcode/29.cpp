class Solution {
private:
    void di(TreeNode* cur,string path,vector<string>&result)
    {
        path+=to_string(cur->val);
        if(cur->left==NULL&&cur->right==NULL)
        {
            result.push_back(path);
            return;
        }
        if(cur->left)
        {
            di(cur->left,path+"->",result);

        }
        if(cur->right)
        {
            di(cur->right,path+"->",result);
        }
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
    vector<string>result;
    string path;
    if(root==NULL)
    {
        return result;
    }
    di(root,path,result);
    return result;
    }

};
