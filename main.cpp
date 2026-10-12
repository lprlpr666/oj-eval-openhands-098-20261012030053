#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeFromLevelOrder(const vector<int>& values) {
    if (values.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(values[0]);
    queue<TreeNode*> q;
    q.push(root);
    
    int i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();
        
        if (i < values.size()) {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
            i++;
        }
        
        if (i < values.size()) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
            i++;
        }
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

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<int> values(8);
    
    // Read 8 integers: 7 for BST, 1 for kth count
    for (int i = 0; i < 8; i++) {
        cin >> values[i];
    }
    
    // Build tree from first 7 values (level-order structure)
    vector<int> tree_values(values.begin(), values.begin() + 7);
    TreeNode* root = buildTreeFromLevelOrder(tree_values);
    
    int k = values[7];
    
    // Find kth largest element
    if (k >= 1 && k <= 7) {
        visited_count = 0;
        result = -1;
        findKthLargest(root, k);
        cout << result << endl;
    } else {
        cout << -1 << endl;
    }
    
    // Clean up memory
    deleteTree(root);
    
    return 0;
}