#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class node {
public:
    node *parent;
    int key;
    node *left, *right;

    node() {
        this->parent = NULL;
    }
};

class TreeOrders {
    int n;
    vector<int> left;
    vector<int> right;
    vector<node> tree;

public:
    vector<int> in;
    vector<int> pre;
    vector<int> post;
    node root;

void read() {
    cin >> n;
    tree.resize(n);
    left.resize(n);
    right.resize(n);
    in.reserve(n);
    pre.reserve(n);
    post.reserve(n);
    tree[0].key = 9;
  
    for (int i = 0; i < n; i++)
        cin >> tree[i].key >> left[i] >> right[i];

    for (int i = 0; i < n; i++) {
        if (left[i] != -1) {
            tree[i].left = &tree[left[i]];
            tree[left[i]].parent = &tree[i];
        }
        else
            tree[i].left = NULL;
        
        if (right[i] != -1) {
            tree[i].right = &tree[right[i]];
            tree[right[i]].parent = &tree[i];
        }
        else
            tree[i].right = NULL;
    }
    
        root = FindRoot(tree[0]);
    }


    node& FindRoot(node& n) {
        if (n.parent == NULL)
        return n;
        else
        return FindRoot(*(n.parent));
    }


    int in_order(const node& n) {

        if (n.left == NULL && n.right == NULL) {
            in.push_back(n.key);
            return 0;
        }
        
        if (n.left != NULL)
            in_order(*(n.left));
        
        in.push_back(n.key);

        if (n.right != NULL)
            in_order(*(n.right));

            return 0;
        }

    int pre_order(const node& n) {
        if (n.left == NULL && n.right == NULL) {
            pre.push_back(n.key);
            return 0;
        }

        pre.push_back(n.key);
        
        if (n.left != NULL)
            pre_order(*(n.left));

        if (n.right != NULL)
            pre_order(*(n.right));
        
        return 0;
    }

    int post_order(const node& n) {

        if (n.left == NULL && n.right == NULL) {
            post.push_back(n.key);
            return 0;
        }
        
        if (n.left != NULL)
            post_order(*(n.left));

        if (n.right != NULL)
            post_order(*(n.right));
        
        post.push_back(n.key);

        return 0;
    }
};

void print(vector <int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0)
            cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    t.in_order(t.root);
    t.pre_order(t.root);
    t.post_order(t.root);
    print(t.in);
    print(t.pre);
    print(t.post);
    return 0;
}

int main (int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
// Allow larger stack space
const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
struct rlimit rl;
int result;

result = getrlimit(RLIMIT_STACK, &rl);
if (result == 0) {
    if (rl.rlim_cur < kStackSize) {
        rl.rlim_cur = kStackSize;
        result = setrlimit(RLIMIT_STACK, &rl);
        if (result != 0)
            std::cerr << "setrlimit returned result = " << result << std::endl;
    }
}
#endif
// std::cout << "enter: \n";
return main_with_large_stack_space();
}

