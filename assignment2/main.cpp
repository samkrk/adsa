/* ADSA Assignment 2 - AVL Tree Implementation  */
/* Sam Kirk, 1851921                            */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Node{
    int value;
    Node* left;
    Node* right;
    int height; 
};

class AVLTree{
private:
    Node* root;

    int height(Node* leaf);
    int getBalance(Node* leaf);

    Node* singleRightRotate(Node* &leaf);
    Node* singleLeftRotate(Node* &leaf);
    Node* doubleRightRotate(Node* &leaf);
    Node* doubleLeftRotate(Node* &leaf);

    Node* findMax(Node* leaf);
    Node* findMin(Node* leaf);

    Node* insert(Node* leaf, int key);    
	Node* remove(Node* leaf, int key);
	
	void inorder_print(Node* leaf);
	void postorder_print(Node* leaf);
	void preorder_print(Node* leaf);

    
public:
    // constructor 
    AVLTree();

    // insert and remove values 
    void insert(int key);
    void remove(int key);

    // print methods 
    void inorder_print();
	void postorder_print();
	void preorder_print();

};
////////////////////////////////////////////////
            // PRIVATE METHODS 
////////////////////////////////////////////////

int AVLTree::height(Node* leaf){
        return (leaf == NULL ? -1 : leaf->height);
    }

int AVLTree::getBalance(Node* leaf)
    {
        if(leaf == NULL)
            return 0;
        else
            return height(leaf->left) - height(leaf->right);
    }

// Rotating methods 
Node* AVLTree::singleRightRotate(Node* &leaf)
    {
        Node* u = leaf->left;
        leaf->left = u->right;
        u->right = leaf;
        leaf->height = std::max(height(leaf->left), height(leaf->right))+1;
        u->height = std::max(height(u->left), leaf->height)+1;
        return u;
    }
Node* AVLTree::singleLeftRotate(Node* &leaf)
    {
        Node* u = leaf->right;
        leaf->right = u->left;
        u->left = leaf;
        leaf->height = std::max(height(leaf->left), height(leaf->right))+1;
        u->height = std::max(height(leaf->right), leaf->height)+1 ;
        return u;
    }
Node* AVLTree::doubleLeftRotate(Node* &leaf)
    {
        leaf->right = singleRightRotate(leaf->right);
        return singleLeftRotate(leaf);
    }
Node* AVLTree::doubleRightRotate(Node* &leaf)
    {
        leaf->left = singleLeftRotate(leaf->left);
        return singleRightRotate(leaf);
    }

Node* AVLTree::findMin(Node* leaf)
    {
        if(leaf == NULL)
            return NULL;
        else if(leaf->left == NULL)
            return leaf;
        else
            return findMin(leaf->left);
    }
Node* AVLTree::findMax(Node* leaf)
    {
        if(leaf == NULL)
            return NULL;
        else if(leaf->right == NULL)
            return leaf;
        else
            return findMax(leaf->right);
    }

// private insert 
Node* AVLTree::insert(Node* leaf, int key){
    if (leaf == NULL){
        leaf = new Node;
        leaf->value = key;
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->height = 0;

    }
    else if (key < leaf->value){
        leaf->left = insert(leaf->left, key);
            if(height(leaf->left) - height(leaf->right) == 2)
            {
                if(key < leaf->left->value)
                    leaf = singleRightRotate(leaf);
                else
                    leaf = doubleRightRotate(leaf);
            }
    }

    else if (key > leaf->value){
            leaf->right = insert(leaf->right, key);
            if(height(leaf->right) - height(leaf->left) == 2)
            {
                if(key > leaf->right->value)
                    leaf = singleLeftRotate(leaf);
                else
                    leaf = doubleLeftRotate(leaf);
            }   
    }

    leaf->height = std::max(height(leaf->left), height(leaf->right))+1;
    return leaf;
}

// private remove 
Node* AVLTree::remove(Node* leaf, int key)
    {
        Node* temp;

        // Element not found
        if(leaf == NULL)
            return NULL;

        // Searching for element
        if(key < leaf->value)
            leaf->left = remove(leaf->left, key);
        else if(key > leaf->value)
            leaf->right = remove(leaf->right, key);

        // Element found
        // With 2 children
        else if(leaf->left && leaf->right)
        {
            temp = findMax(leaf->left);
            leaf->value = temp->value;
            leaf->left = remove(leaf->left, leaf->value);
        }
        // With one or zero child
        else
        {
            temp = leaf;
            if(leaf->left == NULL)
                leaf = leaf->right;
            else if(leaf->right == NULL)
                leaf = leaf->left;
            delete temp;
        }

        // if tree only had one node, return
        if(leaf == NULL)
            return leaf;

        leaf->height = std::max(height(leaf->left), height(leaf->right))+1;

        // If Node is unbalanced
        // Balancing the node
        int balance = height(leaf->left) - height(leaf->right);

        // Left-heavy cases
        if (balance > 1)
        {
            // Left-left case
            if (height(leaf->left->left) >= height(leaf->left->right))
                return singleRightRotate(leaf);
            // Left-right case
            else
                return doubleRightRotate(leaf);
        }

        // Right-heavy cases
        if (balance < -1)
        {
            // Right-right case
            if (height(leaf->right->right) >= height(leaf->right->left))
                return singleLeftRotate(leaf);
            // Right-left case
            else
                return doubleLeftRotate(leaf);
        }

        return leaf;
    }

// private print methods 
void AVLTree::inorder_print(Node *leaf){
	if(leaf == NULL)
        return;
	inorder_print(leaf->left);
	std::cout << leaf->value << " ";
	inorder_print(leaf->right);
}
void AVLTree::postorder_print(Node *leaf){
	if(leaf == NULL)
        return;
	postorder_print(leaf->left);
	postorder_print(leaf->right);
	std::cout << leaf->value << " ";
}
void AVLTree::preorder_print(Node *leaf){
	if(leaf == NULL)
        return;
	std::cout << leaf->value << " ";
	preorder_print(leaf->left);
	preorder_print(leaf->right);
}

////////////////////////////////////////////////
            // PUBLIC METHODS 
////////////////////////////////////////////////

// AVLTree constructor 
AVLTree::AVLTree(){
    root = nullptr;
}

// public insert 
void AVLTree::insert(int key){
    root = insert(root, key);
}

// public remove 
void AVLTree::remove(int key){
    root = remove(root, key);
    
}

// public printing methods
void AVLTree::inorder_print(){
    if (root == nullptr){
        std::cout << "EMPTY" << std::endl;
        return;
    }
    else {
        inorder_print(root);
        std::cout << std::endl;
        return;
    }
}
void AVLTree::postorder_print(){
    if (root == nullptr){
        std::cout << "EMPTY" << std::endl;
        return;
    }
    else {
        postorder_print(root);
        std::cout << std::endl;
        return;
    }
}
void AVLTree::preorder_print(){
    if (root == nullptr){
        std::cout << "EMPTY" << std::endl;
        return;
    }
    else {
        preorder_print(root);
        std::cout << std::endl;
        return;
    }
}


int main(void){
    AVLTree tree;

    // get input 
    std::string input;
    std::getline(std::cin, input);

    // split input into vector of strings
    std::vector<std::string> inputs;
    int index = 0;
    for (int i = 0; i <= input.length(); ++i) {
        if (i == input.length() || input[i] == ' ') {
            inputs.push_back(input.substr(index, i - index));
            index = i + 1;
        }
    }
    
    // get output type 
    std::string o_type = inputs.back();
    inputs.pop_back();
    
    // add and remove elements to tree 
    for (const std::string& command : inputs){
        if (command[0] == 'A' || command[0] == 'D') {
            std::string val = command.substr(1);
            try {
                int num = std::stoi(val);
                if (command[0] == 'A'){
                    // std::cout << "Inserting: " << num << std::endl;
                    tree.insert(num);
                    // std::cout << "Inserted: " << num << std::endl;
                }
                else if (command[0] == 'D'){            
                    // std::cout << "Removing: " << num << std::endl;
                    tree.remove(num);
                    // std::cout << "Removed: " << num << std::endl;
                }
            } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: Unable to convert '" << val << "' to an integer." << std::endl;
            } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: The value '" << val << "' is too large or too small to fit in an integer." << std::endl;
        }
        }
    }

    // print tree
    if (o_type == "PRE"){
        tree.preorder_print();
    }
    else if (o_type == "IN"){
        tree.inorder_print();
    }
    else if (o_type == "POST"){
        tree.postorder_print();
    }
    return 0;
}


