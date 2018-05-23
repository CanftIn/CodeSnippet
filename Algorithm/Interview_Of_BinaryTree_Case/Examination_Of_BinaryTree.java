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

    //判断是否平衡
    boolean isBalanced(TreeNode node)
    {
        return maxDepth2(node) != 1;
    }

    int maxDepth2(TreeNode node)
    {
        if(node == null) return 0;
        int left = maxDepth2(node.left);
        int right = maxDepth2(node.right);
        if(left == -1 || right == -1 || Math.abs(left - right) > 1)
            return -1;
        return Math.max(left, right) + 1;
    }

    //判断树相同
    boolean isSameTreeNode(TreeNode t1,TreeNode t2){
        if(t1==null&&t2==null){
            return true;
        }
        else if(t1==null||t2==null){
            return false;
        }
        if(t1.val != t2.val){
            return false;
        }
        boolean left = isSameTreeNode(t1.left,t2.left);
        boolean right = isSameTreeNode(t1.right,t2.right);
        return left&&right;
    }

    //判断树镜像
    boolean isMirror(TreeNode t1,TreeNode t2){
        if(t1==null&&t2==null){
            return true;
        }
        if(t1==null||t2==null){
            return false;
        }
        if(t1.val != t2.val){
            return false;
        }
        return isMirror(t1.left,t2.right)&&isMirror(t1.right,t2.left);
    }

    //翻转二叉树
    TreeNode mirrorTreeNode(TreeNode root){
        if(root == null){
            return null;
        }
        TreeNode left = mirrorTreeNode(root.left);
        TreeNode right = mirrorTreeNode(root.right);
        root.left = right;
        root.right = left;
        return root;
    }
}