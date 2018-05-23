class TreeNode
{
    int val;
    TreeNode left;
    TreeNode right;
}

class TreeNode_Examination
{
    //求最大深度
    int maxDepth(TreeNode node)
    {
        if(node == null) return 0;
        int left = maxDepth(node.left);
        int right = maxDepth(node.right);
        return Math.max(left, right) + 1;
    }

    //求最小深度
    int getMinDepth(TreeNode root)
    {
        if(root == null) return 0;
        return getMin(root);
    }

    int getMin(TreeNode root)
    {
        if(root == null) return Integer.MAX_VALUE;
        if(root.left == null || root.right == null) return 1;
        return Math.min(getMin(roor.left), getMin(root.right)) + 1;
    }

    //求节点个数
    int numOfTreeNode(TreeNode root)
    {
        if(root == null) return 0;
        int left = numOfTreeNode(root.left);
        int right = numOfTreeNode(root.right);
        return left + right + 1;
    }

    //求叶子节点个数
    int numOfNoChild(TreeNode root)
    {
        if(root == null) return 0;
        if(root.left == null && root.right == null) return 1;
        return numOfNoChild(root.left) + numOfNoChild(root.right);
    }

    //求第k层节点个数
    int numOfKLevel(TreeNode root, int k)
    {
        if(root == null || k < 1) return 0;
        if(k == 1) return 1;
        return numOfKLevel(root.left, k - 1) + numOfKLevel(root.right, k - 1);
    }

    
}