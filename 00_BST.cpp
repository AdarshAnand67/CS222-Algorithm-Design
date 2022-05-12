/*Adarsh Anand*/
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void printBST(TreeNode *root)
{
    if (root == NULL)
        return;
    printBST(root->left);
    cout << root->val << " ";
    printBST(root->right);
}

bool searchBST(TreeNode *root, int key)
{
    if (root == NULL)
        return false;
    if (root->val == key)
        return true;
    if (root->val > key)
        return searchBST(root->left, key); // search in left subtree
    else
        return searchBST(root->right, key); // search in right subtree
}

int ceilBST(TreeNode *root, int key)
{
    // return the ceil of the key in the BST
    int ceil = -1;
    while (root != NULL)
    {
        if (root->val == key)
            return root->val;
        if (root->val > key)
        {
            ceil = root->val;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
}

int floorBST(TreeNode *root, int key)
{
    // return the floor of the key in the BST
    int floor = -1;
    while (root != NULL)
    {
        if (root->val == key)
            return root->val;
        if (root->val > key)
        {
            root = root->left;
        }
        else
        {
            floor = root->val;
            root = root->right;
        }
    }
}

void insertBST(TreeNode *&root, int key)
{
    if (root == NULL)
    {
        root = new TreeNode(key);
        return;
    }
    if (root->val > key)
        insertBST(root->left, key);
    else
        insertBST(root->right, key);
}

void deleteBST(TreeNode *node, int key)
{
    if (node == NULL)
        return;
    if (node->val > key)
        deleteBST(node->left, key);
    else if (node->val < key)
        deleteBST(node->right, key);
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            node = NULL;
        }
        else if (node->left == NULL)
        {
            TreeNode *temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == NULL)
        {
            TreeNode *temp = node;
            node = node->left;
            delete temp;
        }
        else
        {
            TreeNode *temp = node->right;
            while (temp->left != NULL)
                temp = temp->left;
            node->val = temp->val;
            deleteBST(node->right, temp->val);
        }
    }
}

TreeNode *LCA(TreeNode *root, int n1, int n2)
{
    if (root == NULL)
        return NULL;
    if (root->val > n1 && root->val > n2)
        return LCA(root->left, n1, n2);
    if (root->val < n1 && root->val < n2)
        return LCA(root->right, n1, n2);
    return root;
}

int largestvalBST(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int res = -1;
    while (root != NULL)
    {
        if (root->right == NULL)
        {
            res = root->val;
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return res;
    // Time Complexity: O(log(n))
}

int smallestvalBST(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int res = -1;
    while (root != NULL)
    {
        if (root->left == NULL)
        {
            res = root->val;
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return res;
    // Time Complexity: O(log(n))
}

void inorderBST(TreeNode *root)
{
    if (!root)
        return;
    // left root right
    inorderBST(root->left);
    cout << root->val << " ";
    inorderBST(root->right);
}

void postorderBST(TreeNode *root)
{
    if (!root)
        return;
    // left right root
    postorderBST(root->left);
    postorderBST(root->right);
    cout << root->val << " ";
}

void preorderBST(TreeNode *root)
{
    if (!root)
        return;
    // root left right
    cout << root->val << " ";
    preorderBST(root->left);
    preorderBST(root->right);
}

int main()
{
    // create a BST
    TreeNode *root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    // print the BST
    printBST(root);
    cout << endl;

    // search for a key in the BST
    if (searchBST(root, 2))
        cout << "Found 2" << endl;
    else
        cout << "2 not found" << endl;

    // if (searchBST(root, 5))
    //     cout << "Found 5" << endl;
    // else
    //     cout << "5 not found" << endl;

    // ceil and floor of a key=2
    cout << "ceil(2) = " << ceilBST(root, 2) << endl;
    cout << "floor(2) = " << floorBST(root, 2) << endl;

    // insert a key in the BST
    // insertBST(root, 9);
    // printBST(root);
    // cout << endl;

    // delete a key in the BST
    // deleteBST(root, 2);
    // printBST(root);
    // cout << endl;

    // LCA of 1,4
    TreeNode *lca = LCA(root, 1, 4);
    if (lca != NULL)
        cout << "LCA(1,4) = " << lca->val << endl;
    else
        cout << "LCA(1,4) = NULL" << endl;

    // Largest value in BST
    cout << "Largest value in BST = " << largestvalBST(root) << endl;

    // Smallest value in BST
    cout << "Smallest value in BST = " << smallestvalBST(root) << endl;

    // Inorder traversal
    inorderBST(root);
    cout << endl;

    // Preorder traversal
    preorderBST(root);
    cout << endl;

    // Postorder traversal
    postorderBST(root);
    cout << endl;
}