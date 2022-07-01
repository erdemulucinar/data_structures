#include "avl_tree.h"

//-------------------------------------------------------------------------------
//---------------------------Implementation Functions----------------------------
//-------------------------------------------------------------------------------

int height(AVLNode *node){
    int heightLeft, heightRight;
    
    //Recursively move down on both right and left subtrees, adding the number of
    //nodes on the way, and selecting the maximum one at every node.
    
    //Base case
    if(!node)
        return 0;
    
    heightLeft = height(node->left);
    heightRight = height(node->right);
    
    if(heightLeft > heightRight)
        return 1 + heightLeft;
    else
        return 1 + heightRight;
}

int getBalance(AVLNode *node){
    return height(node->left) - height(node->right);
}

AVLNode* rightRotate(AVLNode *x){
    AVLNode *y,*z;
    
    //      X                Y
    //   Y     b     =>   a     X
    // a   Z                   Z b
    
    y = x->left;    //Y is the left subtree of X
    z = y->right;   //Z is the right subtree of Y
    
    y->right = x;   //Y moves up, having X as the right subtree
    x->left = z;    //Z is bigger than Y but smaller than X, thus X's
                    //new left subtree is Z.
    
    return y;
}

AVLNode* leftRotate(AVLNode *x){
    AVLNode *y,*z;
    
    //    X                Y
    // a     Y     =>    X   b
    //      Z b        a   Z
    
    y = x->right;   //Y is the right subtree of X
    z = y->left;    //Z is the left subtree of Y
    
    y->left = x;    //Y moves up having X as the left subtree
    x->right = z;   //Z is smaller than Y but bigger than X, thus X's
                    //new right subtree is Z
    
    return y;
}

AVLNode* insertNode(AVLNode *node, void *key, copyFunction copy, compareFunction compare, int *success){
    //Recursively move down the tree to find the leaf to add the key. When it is
    //found, copy it there and start moving upwards, while checking for the balance
    //of the tree and when it is violated, fix the unbalance.
    AVLNode *newNode;
    int compareRes, balance, balanceChild;
    
    //Base case
    if(!node){ //Leaf is found
        newNode = malloc(sizeof(AVLNode));
        newNode->key = copy(key);
        newNode->right = 0;
        newNode->left = 0;
        return newNode;
    }
    
    //Adding the node
    compareRes = compare(key,node->key);
    if(compareRes > 0) //Key is bigger
        node->right = insertNode(node->right, key, copy, compare, success);
    else if(compareRes < 0) //Key is smaller
        node->left = insertNode(node->left, key, copy, compare, success);
    else{ //Key already exists and it is this node thus just return it.
        *success = 0;
        return node;
    }
    
    //After addition is complete, now move upwards and balance the tree
    balance = getBalance(node);
    if(balance > 1){ //Left is heavy need to rotate right
        balanceChild = getBalance(node->left);
        //If left child's left is heavy a simple right rotation is enough
        //Else, there is a zig-zag pattern and a left->right rotate is needed
        if(balanceChild > 0) //left and left heavy
            return rightRotate(node);
        else { //left and right heavy (zigzag)
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    } else if(balance < -1){ //Right is heavy need to rotate left
        balanceChild = getBalance(node->right);
        //If right child's right is heavy, a simple left rotation is enough.
        //Else, there is a zigzag pattern and a right->left rotation is needed
        if(balanceChild < 0) //Right and right heavy
            return leftRotate(node);
        else { //Right and left heavy (zigzag)
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    } else //Node in inspection is already balanced.
        return node;
}

void flushNode(AVLNode *node, deleteFunction delete){
    if(!node)
        return;
    
    flushNode(node->right, delete);
    flushNode(node->left, delete);
    
    delete(node->key);
    free(node);
}

//Debug Functions
void printNode(AVLNode *node, printFunction print, int tablvl){
    int i;
    
    if(!node)
        return;
    
    for(i = 0; i < tablvl; i++)
        printf("\t");
    
    print(node->key);
    printf("\n");
    printNode(node->right, print, tablvl+1);
    printNode(node->left, print, tablvl+1);
}

void sortList(AVLNode *node, int *i, void **sortedList){
    if(!node)
        return;
    
    sortList(node->left, i, sortedList);
    sortedList[*i] = node->key;
    *i = *i + 1;
    sortList(node->right, i, sortedList);
}

void balanceCheck(AVLNode *node, int* maxDev){
    int currBalance;
    
    if(!node)
        return;
    
    balanceCheck(node->right, maxDev);
    balanceCheck(node->left, maxDev);
    
    currBalance = getBalance(node);
    if(currBalance < 0)
        currBalance = currBalance * -1;
    
    if(currBalance > *maxDev)
        *maxDev = currBalance;
}

//-------------------------------------------------------------------------------
//-----------------------------Interface Functions-------------------------------
//-------------------------------------------------------------------------------

AVLTree* createAVL(copyFunction copy, deleteFunction del, compareFunction compare){
    AVLTree* tree;
    
    tree = malloc(sizeof(AVLTree));
    tree->copyFcn = copy;
    tree->delFcn = del;
    tree->compFcn = compare;
    tree->head = 0;
    tree->len = 0;
    
    return tree;
}

AVLTree* insertAVL(AVLTree *tree, void *key){
    AVLNode *head;
    int success;
    
    //Null pointer check
    if(!tree)
        return 0;
    
    //Insertion
    success = 1;
    head = insertNode(tree->head, key, tree->copyFcn, tree->compFcn, &success);
    tree->head = head;
    if(success)
        tree->len = tree->len+1;
    return tree;
}

void* searchAvl(AVLTree* tree, void *key){
    AVLNode *currNode;
    int compareRes;
    
    if(!tree)
        return 0;
    
    currNode = tree->head;
    while(currNode){
        compareRes = tree->compFcn(key,currNode->key);
        if(compareRes > 0) //Search right
            currNode = currNode->right;
        else if(compareRes < 0) //Search left
            currNode = currNode->left;
        else //Key found
            return currNode->key;
    }
    
    return 0;
}

void flushAVL(AVLTree *tree){
    flushNode(tree->head,tree->delFcn);
}

void printAVL(AVLTree *tree, printFunction print){
    printNode(tree->head,print,0);
}

void reportAVL(AVLTree *tree, int *isTreeSorted, int *maxDev){
    int i, compRes;
    void **sortedList;
    
    *maxDev = 0;
    balanceCheck(tree->head, maxDev);
    
    i = 0;
    sortedList = malloc(tree->len * sizeof(void*));
    sortList(tree->head, &i, sortedList);
    *isTreeSorted = 1;
    for(i = 0; i < tree->len-1; i++){
        compRes = tree->compFcn(sortedList[i],sortedList[i+1]);
        if(compRes >= 0){
            *isTreeSorted = 0;
            i = tree->len;
        }
    }
}
