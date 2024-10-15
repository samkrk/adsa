#include<iostream>

using namespace std;

class BST
{
    struct node
    {
        int data;
        node* left;
        node* right;
        int height;
    };

    node* root;

    void makeEmpty(node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->height = 0;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
        {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
            {
                if(x < t->left->data)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        }
        else if(x > t->data)
        {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2)
            {
                if(x > t->right->data)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right))+1;
        return t;
    }

    node* singleRightRotate(node* &t)
    {
        node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(u->left), t->height)+1;
        return u;
    }

    node* singleLeftRotate(node* &t)
    {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right))+1;
        u->height = max(height(t->right), t->height)+1 ;
        return u;
    }

    node* doubleLeftRotate(node* &t)
    {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node* doubleRightRotate(node* &t)
    {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t)
    {
        node* temp;

        // Element not found
        if(t == NULL)
            return NULL;

        // Searching for element
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        if(t == NULL)
            return t;

        t->height = max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2)
        {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2)
        {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }

    int height(node* t)
    {
        return (t == NULL ? -1 : t->height);
    }

    int getBalance(node* t)
    {
        if(t == NULL)
            return 0;
        else
            return height(t->left) - height(t->right);
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void preorder(node *t)
    {
        if (t == NULL)
            return;
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }

    void postorder(node *t)
    {
        if (t == NULL)
            return;
        postorder(t->left);
        postorder(t->right);
        cout << t->data << " ";
    }

public:
    BST()
    {
        root = NULL;
    }


    void insert(int x)
    {
        root = insert(x, root);
    }

    void remove(int x)
    {
        root = remove(x, root);
    }

    void inorder()
    {
        if (root == nullptr){
        cout << "EMPTY" << endl;
        return;
        }
        else {
            inorder(root);
            cout << endl;
            return;
        }
    }
    
    void preorder()
    {
        if (root == nullptr){
        cout << "EMPTY" << endl;
        return;
        }
        else {
            preorder(root);
            cout << endl;
            return;
        }
    }

    void postorder()
    {
        if (root == nullptr){
        cout << "EMPTY" << endl;
        return;
        }
        else {
            postorder(root);
            cout << endl;
            return;
        }
    }
};


int main(void){
    BST tree;

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
        }
    }

    // print tree
    if (o_type == "PRE"){
        tree.preorder();
    }
    else if (o_type == "IN"){
        tree.inorder();
    }
    else if (o_type == "POST"){
        tree.postorder();
    }

    return 0;
}
