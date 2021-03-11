#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int key, y, x;
    Node* left;
    Node* right;
    Node(int key, int y, int x) : key{key}, y{y}, x{x}, left{nullptr}, right{nullptr} {};
};

Node* insert(Node* root, Node* node) {
    if (root == nullptr) return node;
    if (node->x < root->x) {
        root->left = insert(root->left, node);
    } else {
        root->right = insert(root->right, node);
    }
    return root;
}

void preorderTraverse(Node* root, vector<int>& order) {
    if (root == nullptr) return;
    order.push_back(root->key);
    preorderTraverse(root->left, order);
    preorderTraverse(root->right, order);
}

void postorderTraverse(Node* root, vector<int>& order) {
    if (root == nullptr) return;
    postorderTraverse(root->left, order);
    postorderTraverse(root->right, order);
    order.push_back(root->key);
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<pair<int,pair<int,int>>> ordered;
    for (int i = 0; i < nodeinfo.size(); ++i) {
        int x = nodeinfo[i][0], y = nodeinfo[i][1];
        ordered.push_back({-y,{x,i+1}});
    }
    sort(ordered.begin(), ordered.end());
    
    Node* root = nullptr;
    for (int i = 0; i < ordered.size(); ++i) {
        int y = -ordered[i].first, x = ordered[i].second.first, key = ordered[i].second.second;
        root = insert(root, new Node(key,y,x));
    }
    
    vector<int> preorder, postorder;
    preorderTraverse(root, preorder);
    postorderTraverse(root, postorder);
    deleteTree(root);
    return {preorder, postorder};
}
