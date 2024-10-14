#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Clase NodeT para los nodos del árbol
class NodeT {
private:
    int data;
    NodeT *left, *right;

public:
    NodeT(int d) : data(d), left(nullptr), right(nullptr) {}

    friend class BST; // Permitir acceso a la clase BST
};

// Clase BST para el Árbol Binario de Búsqueda
class BST {
private:
    NodeT *root;

    NodeT* insert(NodeT* node, int value);
    NodeT* remove(NodeT* node, int value);
    bool ancestors(NodeT* node, int value, vector<int>& ancestor);
    int whatlevelamI(NodeT* node, int value, int level);
    void preOrder(NodeT* node, vector<int>& result);
    void inOrder(NodeT* node, vector<int>& result);
    void postOrder(NodeT* node, vector<int>& result);
    int height(NodeT* node);
    void levelOrder(vector<int>& result);

public:
    BST() : root(nullptr) {}
    void insert(int value);
    void remove(int value);
    vector<int> getAncestors(int value);
    int getLevel(int value);
    void getPreOrder(vector<int>& result);
    void getInOrder(vector<int>& result);
    void getPostOrder(vector<int>& result);
    void getLevelOrder(vector<int>& result);
    int getHeight();
};
//Complejidad O(n)
NodeT* BST::insert(NodeT* node, int value) {
    if (!node) return new NodeT(value);
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    return node;
}
//Complejidad O(n)
NodeT* BST::remove(NodeT* node, int value) {
    if (!node) return nullptr;
    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        if (!node->left) {
            NodeT* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            NodeT* temp = node->left;
            delete node;
            return temp;
        }
        NodeT* successor = node->right;
        while (successor->left) successor = successor->left;
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
    }
    return node;
}
//Complejidad O(n)
bool BST::ancestors(NodeT* node, int value, vector<int>& ancestor) {
    if (!node) return false;
    if (node->data == value) return true;

    // Si se encuentra el valor en alguno de los subárboles
    if (ancestors(node->left, value, ancestor) || 
        ancestors(node->right, value, ancestor)) {
        ancestor.insert(ancestor.begin(), node->data); // Insertar al inicio
        return true;
    }
    return false;
}
//Complejidad O(n)
int BST::whatlevelamI(NodeT* node, int value, int level) {
    if (!node) return -1;
    if (node->data == value) return level;
    int left = whatlevelamI(node->left, value, level + 1);
    return (left != -1) ? left : whatlevelamI(node->right, value, level + 1);
}
//Complejidad O(n)
void BST::preOrder(NodeT* node, vector<int>& result) {
    if (!node) return;
    result.push_back(node->data);
    preOrder(node->left, result);
    preOrder(node->right, result);
}
//Complejidad O(n)
void BST::inOrder(NodeT* node, vector<int>& result) {
    if (!node) return;
    inOrder(node->left, result);
    result.push_back(node->data);
    inOrder(node->right, result);
}
//Complejidad O(n)
void BST::postOrder(NodeT* node, vector<int>& result) {
    if (!node) return;
    postOrder(node->left, result);
    postOrder(node->right, result);
    result.push_back(node->data);
}
//Complejidad O(n)
int BST::height(NodeT* node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}
//Complejidad O(n)
void BST::levelOrder(vector<int>& result) {
    if (!root) return;
    queue<NodeT*> q;
    q.push(root);
    while (!q.empty()) {
        NodeT* node = q.front();
        q.pop();
        result.push_back(node->data);
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

// Implementación de métodos públicos
void BST::insert(int value) {
    root = insert(root, value);
}

void BST::remove(int value) {
    root = remove(root, value);
}

vector<int> BST::getAncestors(int value) {
    vector<int> ancestor;
    if (!ancestors(root, value, ancestor)) ancestor.push_back(-1);
    return ancestor;
}

int BST::getLevel(int value) {
    return whatlevelamI(root, value, 0);
}

void BST::getPreOrder(vector<int>& result) {
    preOrder(root, result);
}

void BST::getInOrder(vector<int>& result) {
    inOrder(root, result);
}

void BST::getPostOrder(vector<int>& result) {
    postOrder(root, result);
}

void BST::getLevelOrder(vector<int>& result) {
    levelOrder(result);
}

int BST::getHeight() {
    return height(root);
}

// Función principal
int main() {
    BST tree;
    int n, m, q, r;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        tree.insert(value);
    }

    cin >> m;
    for (int i = 0; i < m; ++i) {
        int value;
        cin >> value;
        tree.remove(value);
    }

    cin >> q;
    vector<int> queryAncestors(q);
    for (int i = 0; i < q; ++i) cin >> queryAncestors[i];

    cin >> r;
    vector<int> queryLevels(r);
    for (int i = 0; i < r; ++i) cin >> queryLevels[i];

    vector<int> result;
    tree.getPreOrder(result);
    for (int val : result) cout << val << " ";
    cout << endl;

    result.clear();
    tree.getInOrder(result);
    for (int val : result) cout << val << " ";
    cout << endl;

    result.clear();
    tree.getPostOrder(result);
    for (int val : result) cout << val << " ";
    cout << endl;

    result.clear();
    tree.getLevelOrder(result);
    for (int val : result) cout << val << " ";
    cout << endl;

    cout << tree.getHeight() << endl;

    for (int val : queryAncestors) {
        vector<int> ancestor = tree.getAncestors(val);
        for (int anc : ancestor) cout << anc << " ";
        cout << endl;
    }

    for (int val : queryLevels) {
        cout << tree.getLevel(val) << endl;
    }

    return 0;
}
