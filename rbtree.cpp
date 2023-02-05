/*
1. List of students: Cory Overgaard, Haden Johnson, Jonathon Hicks
2. External Sources: Lecture Slides,tutorialspoint.com, geeksforgeeks.org, Peer Teachers in PETR 127
3. Concerns: None
*/
#include <iostream>
#include <vector>
using namespace std;

//node class
class node{
    public:
        //node data members
        int data;
        bool color;
        node *LC, *RC, *parent;
        node(int d);
        node();

    private:
};

//node constructor 
node::node(){
    data = 0;
    color = 0;
    LC = nullptr;
    RC = nullptr;
    parent = nullptr;
}

//node default constructor
node::node(int d){
    data = d;
    color = 0;
    LC = nullptr;
    RC = nullptr;
    parent = nullptr;
}

//Tree class
class Tree{
    private:

    public:
        node *root;
        Tree();

};

//Tree default
Tree::Tree(){
    root = nullptr;
}

void left_rotate(Tree *T, node *x){
    //instantate new node
    node* y;
    y = x->RC;

    //Changing y's subtree to x subtree, this will allow us to rotate the tree properly
    x->RC = y->LC;
    if( y->LC != NULL ){
        y->LC->parent = x;
    }

    //change y's parent
    y->parent = x->parent;

    //Confirm we are not at the root so we can progress with the rotation
    if(x->parent == NULL){ 
        T->root = y;
    }else{
        //Setting x->parent child to y
        if(x == x->parent->LC){
            x->parent->LC = y;
        }else{
            x->parent->RC = y;
        }
    }

    //change x to be y's left child
    y->LC = x;
    x->parent = y;
}

void right_rotate(Tree *T, node *x){
    //instantate new node
    node* y;
    y = x->LC;

    //Changing y's subtree to x subtree, this will allow us to rotate the tree properly
    x->LC = y->RC;
    if ( y->RC != NULL ){
        y->RC->parent = x;
    }

    //change y's parent
    y->parent = x->parent;

    //Confirm we are not at the root so we can progress with the rotation
    if(x->parent == NULL ){ 
        T->root = y;
    }
    else{
        //Setting x->parent child to y 
        if(x == x->parent->RC){
            x->parent->RC = y;
        }else{
            x->parent->LC = y;
        }
    }

    //change x to be y's right child
    y->RC = x;
    x->parent = y;
}


void BST_Insert(node*& r, node*& insert){
    //Base case if root is null
    if (r == nullptr){
        r = insert;
        return;
    }

    //recursive call if data is less or greater than the root data
    if(insert->data > r->data) {
        BST_Insert(r->RC, insert);
        insert->parent = r;
    }else{
        BST_Insert(r->LC, insert);
        insert->parent = r;
    }  
}

void RB_Insert(Tree *T, node *x){
    node *y;
    x->color = 0;
    BST_Insert(T->root, x);

    //Initialize the color to 0
    x->color = 0;
    
    //intial check to make sure node parent is not null (new node is not the root)
    if(x->parent == nullptr){
        x->color = 1;
        return;
    }

    //case checking outter while loop parameters
    while(x != T->root && x->parent->color == 0){
        //cout << 1 << endl;
        //outer if to see if x parent is the right or left child of the grandparent node
        if(x->parent == x->parent->parent->LC){
            y = x->parent->parent->RC;
            //Enter to case 1 (recoloring); check color of y
            if(y != nullptr && y->color == 0){
                x->parent->color = 1;
                y->color = 1;
                x->parent->parent->color = 0;
                x = x->parent->parent;
            //Enter to case 2 or 3
            }else{
                //Enter to case 2; uses a left rotate to balence tree
                if(x == x->parent->RC){
                    x = x->parent;
                    left_rotate(T, x);
                //Enter to case 3; uses a right rotate to balence tree
                }else{
                    x->parent->color = 1;
                    x->parent->parent->color = 0;
                    right_rotate(T, x->parent->parent);
                }
            }
        }else{
            y = x->parent->parent->LC;
            //Enter to case 1 (recoloring); check color of y
            if(y != nullptr && y->color == 0){
                x->parent->color = 1;
                y->color = 1;
                x->parent->parent->color = 0;
                x = x->parent->parent;
            //Enter to case 2 or 3
            }else{
                //Enter to case 2; uses a right rotate to balence tree
                if(x == x->parent->LC){
                    x = x->parent;
                    right_rotate(T, x);
                //Enter to case 3; uses a left rotate to balence tree
                }else{
                    x->parent->color = 1;
                    x->parent->parent->color = 0;
                    left_rotate(T, x->parent->parent);
                }
            }
        }
    }
    //Neccessary, confirm that root is set to black if a shift occures the root could be red must be set back to black
    T->root->color = 1;
}

void Pre_order(node* node1){
    //Base case
    if(node1 == nullptr){
        return;
    }

    //Cout data and recursive call 
    cout << node1->data << " ";
    //Recursive with left child
    Pre_order(node1->LC);
    //Recursive with right child
    Pre_order(node1->RC);
}

int main(int argc, char **argv){
    //Initialize Tree
    Tree tree;
    //tree->root = NULL;

    //Intialize inputs into a vector
    vector<int> input{};

    //Populate input vector
    for(int i = 0; i < argc; i++){
        input.push_back(atoi(argv[i]));
    }

    //Erase file name from argv list
    input.erase(input.begin());

    for(unsigned i = 0; i < input.size(); i++){
        //cout << i << endl;
        //cout << "input " << input.at(i) << endl;
        RB_Insert(&tree, new node(input.at(i)));
    }  

    //Call preorder traversal
    Pre_order(tree.root);
    cout << endl;
}