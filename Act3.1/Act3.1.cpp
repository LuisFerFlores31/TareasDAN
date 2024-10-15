#include <iostream>
#include <vector>
using namespace std;

struct BST{
    int check;
    BST * right;
    BST * left;
};

BST *tree = nullptr;



void preorden(BST*tree){
    if (tree != NULL){
        cout << tree->check;
        preorden (tree->left);
        preorden (tree->right);
    }
    cout<<"NULL";
} 

void inorder(BST*tree){
    if (tree != NULL){
        preorden (tree->left);
        cout << tree->check;
        preorden (tree->right);
    }
}

void postorder(BST*tree){
    if (tree != NULL){
        preorden (tree->left);
        preorden (tree->right);
        cout << tree->check;
    }
}

void LevBLev (BST* tree){
    cout<<"Level by Level"<<endl;
}
    

void traversal (int opc){
    switch (opc){
        case 1: //Preorder
        preorden(tree);
        break;

        case 2://inorder
        inorder(tree);
        break;

        case 3://postorder
        postorder(tree);
        break;

        case 4://Level by Level
        LevBLev(tree);
        break;
    }
}

int main(){
    int opc = 0;
    cout<<"Actividad 3.1"<<endl;
    cin>>opc;
    traversal(opc);
};