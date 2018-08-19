/* 输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构） */

#include<cstdio>


struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        int result = false;
        /* 异常检测 */
        if (pRoot1 == NULL || pRoot2 == NULL)
            return false;

        /* pRoot1当前节点的值是否等于pRoot2 */
        if (pRoot1->val == pRoot2->val) {
            result =  isSubtree(pRoot1, pRoot2);
            /* 需要注意的地方：有可能有多个val与pRoot2->相等，
             * 所以若result为false时，还需要继续遍历pRoot1的左右节点 */
            if (result)
                return true;
        }

        /* 遍历左右节点 */
        return HasSubtree(pRoot1->left, pRoot2) ||
               HasSubtree(pRoot1->right, pRoot2);

    }

    bool isSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        /* 当pRoot2==NULL时，树2的所有点都已经和树1匹配 */
        if (pRoot2 == NULL)
            return true;

        /* pRoot2 != NULL 但 pRoot1 == NULL，不匹配 */
        if (pRoot1 == NULL)
            return false;

        /* 继续检测两树的左右节点是否相等 */
        if (pRoot1->val == pRoot2->val) {
            return isSubtree(pRoot1->left, pRoot2->left) &&
                   isSubtree(pRoot1->right, pRoot2->right);
        }

        return false;
    }
};
