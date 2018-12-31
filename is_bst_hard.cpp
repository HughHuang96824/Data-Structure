#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool GoLeft(const vector<Node>& tree, const Node& node, const int& benchmark);
bool GoRight(const vector<Node>& tree, const Node& node, const int& benchmark);

bool IsBinarySearchTree(const vector<Node>& tree, const Node& node) {
    
    if (!tree.size())
        return true;
    
    bool is_tree = true;
    
    if (node.left != -1) {
        if (node.key > tree[node.left].key) {
            is_tree = GoLeft(tree, tree[node.left], node.key);
            if (!is_tree)
                return is_tree;
        }
        else
            return false;
    }
    
    if (node.right != -1) {
        if (node.key <= tree[node.right].key)
            is_tree = GoRight(tree, tree[node.right], node.key);
        else
            return false;
    }

    return is_tree;
}

bool GoLeft(const vector<Node>& tree, const Node& node, const int& benchmark) {
    
    bool is_tree = true;
    
    if (node.left != -1) {
        if (node.key > tree[node.left].key && benchmark > tree[node.left].key) {
            is_tree = GoLeft(tree, tree[node.left], node.key);
            if (!is_tree)
                return is_tree;
        }
        else
            return false;
    }
    
    if (node.right != -1) {
        if (node.key <= tree[node.right].key && benchmark > tree[node.right].key)
            is_tree = GoRight(tree, tree[node.right], node.key);
        else
            return false;
    }
    return is_tree;
}

bool GoRight(const vector<Node>& tree, const Node& node, const int& benchmark) {
    
    bool is_tree = true;
    
    if (node.left != -1) {
        if (node.key > tree[node.left].key && benchmark <= tree[node.left].key){
            is_tree = GoLeft(tree, tree[node.left], node.key);
            if (!is_tree)
                return is_tree;
        }
        else
            return false;
    }
    
    if (node.right != -1) {
        if (node.key <= tree[node.right].key && benchmark <= tree[node.right].key)
            is_tree = GoRight(tree, tree[node.right], node.key);
        else
            return false;
    }
    return is_tree;
}

int main() {
    //std::cout << "enter: \n";
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree, tree[0])) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}

