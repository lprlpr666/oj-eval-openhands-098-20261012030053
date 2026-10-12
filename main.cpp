#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }
    
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    
    return root;
}

int visited_count = 0;
int result = -1;

void findKthLargest(TreeNode* root, int k) {
    if (root == nullptr || visited_count >= k) {
        return;
    }
    
    // Traverse right subtree first (for descending order)
    findKthLargest(root->right, k);
    
    // Process current node
    visited_count++;
    if (visited_count == k) {
        result = root->val;
        return;
    }
    
    // Traverse left subtree
    findKthLargest(root->left, k);
}

int main() {
    vector<int> values(8);
    
    // Read 8 integers: 7 for BST, 1 for kth count
    for (int i = 0; i < 8; i++) {
        cin >> values[i];
    }
    
    // Build BST from first 7 values (level-order insertion)
    TreeNode* root = nullptr;
    for (int i = 0; i < 7; i++) {
        root = insert(root, values[i]);
    }
    
    int k = values[7];
    
    // Find kth largest element
    visited_count = 0;
    result = -1;
    findKthLargest(root, k);
    
    cout << result << endl;
    
    return 0;
}