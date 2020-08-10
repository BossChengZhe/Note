### 二叉树的层次遍历

&emsp;&emsp;一般常说的二叉树的层次遍历或者说图的广度优先搜索算法都是借由队列实现的，下面详见代码

```c++
void levelorder(TreeNode *root)
{
    /**********************************
    二叉树前期数据处理
    **********************************/
    queue<TreeNode *> q;
    q.push(root);      // 首先将二叉树的根节点推入队列中
    while(!q.empty())
    {
        int q_size = q.size();  // 注意这里是固定队列的大小，在遍历的过程中队列大小会发生变化
        for(int i = 0; i < q_size; i++)
        {
            TreeNode *node = q.front();
            q.pop();
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
    }
}
/***************************************************************************************
上述代码只是二叉树层次遍历的框架，具体逻辑还需要各位自行添加，谢谢
***************************************************************************************/
```
