#pragma once
#include "contact.hpp"
#define NAME 0
#define NUMBER 1
using namespace std;

struct AVLNode
{
    contact data;
    struct AVLNode *left, *right;
    int height;
};

struct AVL
{
    AVLNode *_root;
    unsigned int _size;
};

AVLNode* _avl_createNode(contact &newContact) {
    // cout << "creating node:" << newContact.name << ' ' << newContact.number << endl;
    AVLNode *newNode = new AVLNode;
    newNode->data.name = newContact.name;
    newNode->data.number = newContact.number;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* searchName(AVLNode *root, string &value) {
    // cout << "loading name" << endl;
    while (root != NULL) {
        if (value < root->data.name)
            root = root->left;
        else if (value > root->data.name)
            root = root->right;
        else
            return root;
    }
    return root;
}

AVLNode* searchNum(AVLNode *root, string &value) {
    // cout << "loading number" << endl;
    while (root != NULL) {
        if (value < root->data.number)
            root = root->left;
        else if (value > root->data.number)
            root = root->right;
        else
            return root;
    }
    return root;
}

AVLNode *_search(AVLNode *root, string &value, int &mode){
    if(mode == NAME){
        // cout << "doing search name" << endl;
        return searchName(root, value);
    }
    // cout << "doing search number" << endl;
    return searchNum(root, value);
}

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

//sort by name
AVLNode *insertName(AVL *avl,AVLNode* node,contact &value){
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value.name < node->data.name)
        node->left = insertName(avl,node->left,value);
    else if(value.name > node->data.name)
    	node->right = insertName(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value.name < node->left->data.name) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value.name > node->left->data.name) // 
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value.name > node->right->data.name)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value.name < node->right->data.name)
        return _rightLeftCaseRotate(node);
    
    return node;    
}

AVLNode *insertNum(AVL *avl,AVLNode* node,contact &value){
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value.number < node->data.number)
        node->left = insertNum(avl,node->left,value);
    else if(value.number > node->data.number)
    	node->right = insertNum(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value.number < node->left->data.number) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value.number > node->left->data.number) // 
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value.number > node->right->data.number)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value.number < node->right->data.number)
        return _rightLeftCaseRotate(node);
    
    return node;      
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,contact &value, int &mode) {
    if(mode == NAME){
        return insertName(avl, node, value);
    }
    return insertNum(avl, node, value);
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* removeName(AVLNode* node,string &value){
    if(node==NULL)
        return node;
    if(value > node->data.name)
    	node->right=removeName(node->right,value);
    else if(value < node->data.name)
    	node->left=removeName(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=removeName(node->right,temp->data.name);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* removeNum(AVLNode* node,string &value){
    if(node==NULL)
        return node;
    if(value > node->data.number)
    	node->right=removeNum(node->right,value);
    else if(value < node->data.number)
    	node->left=removeNum(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=removeName(node->right,temp->data.number);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _remove_AVL(AVLNode* node,string &value, int &mode){
    if(mode == NAME){
        return removeName(node, value);
    }
    return removeNum(node, value);
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

// string modeName[2] = {"name", "number"};

bool avl_find(AVL *avl, string &value, int &mode) {
    // cout << "Search by: " << modeName[mode] << endl; 
    AVLNode *temp = _search(avl->_root, value, mode);
    if (temp == NULL)
        return false;
    
    //check by mode
    if(mode == NAME){
        if (temp->data.name == value){
            return true;
        }
        return false;
    }else{
        if(temp->data.number == value){
            return true;
        }
        return false;
    }
}

void avl_insert(AVL *avl,contact &value, int mode){
    if(mode == NAME){
        // cout << "mode: Name" << endl;
        if(!avl_find(avl,value.name, mode)){
            // cout << "insert name to avl" << endl;
            avl->_root=_insert_AVL(avl,avl->_root,value, mode);
            // cout << "finished name" << endl;
            avl->_size++;
        }
    }else{
        // cout << "mode: NUMBER" << endl;
        if(!avl_find(avl,value.number, mode)){
            // cout << "insert number to avl" << endl;
            avl->_root=_insert_AVL(avl,avl->_root,value, mode);
            // cout << "finished number" << endl;
            avl->_size++;
        }        
    }
}

void avl_remove(AVL *avl,string &value, int mode){
    // cout << "removing by " << modeName[mode] << endl;
    if(avl_find(avl,value, mode)){
        avl->_root=_remove_AVL(avl->_root,value, mode);
        avl->_size--;
    }
}

void preorder(AVLNode *root) {
    if (root) {
        preorder(root->left);
        printContact(root->data);
        preorder(root->right);
    }
}