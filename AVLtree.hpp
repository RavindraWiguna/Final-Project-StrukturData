#pragma once
#include "contact.hpp"
using namespace std;
/*
Berisi segala fungsi dan struktur mengenai Struktur Data AVLTree
*/
struct AVLNode{
    contact data;
    struct AVLNode *left, *right;
    int height;
};

struct AVL{
    AVLNode *_root;
    unsigned int _size;
};

AVLNode* createAVLNode(contact &newContact){
    AVLNode *newNode = new AVLNode;
    newNode->data.name = newContact.name;
    newNode->data.number = newContact.number;
    newNode->height=1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

AVLNode* searchName(AVLNode *root, string &value){
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

AVLNode* searchNum(AVLNode *root, string &value){
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

AVLNode *search(AVLNode *root, string &value, int mode){
    if(mode == NAME){
        return searchName(root, value);
    }
    return searchNum(root, value);
}

int getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int maximum(int a,int b){
    return (a > b)? a : b;
}

AVLNode*rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=maximum(getHeight(pivotNode->left), getHeight(pivotNode->right))+1;
    newParrent->height=maximum(getHeight(newParrent->left), getHeight(newParrent->right))+1;
    return newParrent;
}

AVLNode* leftRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=maximum(getHeight(pivotNode->left), getHeight(pivotNode->right))+1;
    newParrent->height=maximum(getHeight(newParrent->left), getHeight(newParrent->right))+1;
    return newParrent;
}

AVLNode* leftCaseRotate(AVLNode* node){
    return rightRotate(node);
}

AVLNode* rightCaseRotate(AVLNode* node){
    return leftRotate(node);
}

AVLNode* leftRightCaseRotate(AVLNode* node){
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

AVLNode* rightLeftCaseRotate(AVLNode* node){
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

int getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return getHeight(node->left)-getHeight(node->right);
}

//sort by name
AVLNode *insertName(AVLNode* node,contact &value){
    
    if(node==NULL) // udah mencapai leaf
        return createAVLNode(value);
    if(value.name < node->data.name)
        node->left = insertName(node->left,value);
    else if(value.name > node->data.name)
    	node->right = insertName(node->right,value);
    
    node->height= 1 + maximum(getHeight(node->left),getHeight(node->right)); 

    int balanceFactor=getBalanceFactor(node);
    
    if(balanceFactor > 1 && value.name < node->left->data.name) // skewed kiri (left-left case)
        return leftCaseRotate(node);
    if(balanceFactor > 1 && value.name > node->left->data.name) // 
		return leftRightCaseRotate(node);
    if(balanceFactor < -1 && value.name > node->right->data.name)
        return rightCaseRotate(node);
    if(balanceFactor < -1 && value.name < node->right->data.name)
        return rightLeftCaseRotate(node);
    
    return node;    
}

AVLNode *insertNum(AVLNode* node,contact &value){
    
    if(node==NULL) // udah mencapai leaf
        return createAVLNode(value);
    if(value.number < node->data.number)
        node->left = insertNum(node->left,value);
    else if(value.number > node->data.number)
    	node->right = insertNum(node->right,value);
    
    node->height= 1 + maximum(getHeight(node->left),getHeight(node->right)); 

    int balanceFactor=getBalanceFactor(node);
    
    if(balanceFactor > 1 && value.number < node->left->data.number) // skewed kiri (left-left case)
        return leftCaseRotate(node);
    if(balanceFactor > 1 && value.number > node->left->data.number) // 
		return leftRightCaseRotate(node);
    if(balanceFactor < -1 && value.number > node->right->data.number)
        return rightCaseRotate(node);
    if(balanceFactor < -1 && value.number < node->right->data.number)
        return rightLeftCaseRotate(node);
    
    return node;      
}

AVLNode* insertToAVL(AVLNode* node,contact &value, int &mode) {
    if(mode == NAME){
        return insertName(node, value);
    }
    return insertNum(node, value);
}

AVLNode* findMinNode(AVLNode *node) {
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
            temp = findMinNode(node->right);
            node->data=temp->data;
            node->right=removeName(node->right,temp->data.name);
        }    
    }

	if(node==NULL) return node;
    
    node->height=maximum(getHeight(node->left),getHeight(node->right))+1;

    int balanceFactor= getBalanceFactor(node);
    
    if(balanceFactor>1 && getBalanceFactor(node->left)>=0) 
        return leftCaseRotate(node);

    if(balanceFactor>1 && getBalanceFactor(node->left)<0) 
        return leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && getBalanceFactor(node->right)<=0) 
        return rightCaseRotate(node);

    if(balanceFactor < -1 && getBalanceFactor(node->right)>0) 
        return rightLeftCaseRotate(node);
    
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
            temp = findMinNode(node->right);
            node->data=temp->data;
            node->right=removeName(node->right,temp->data.number);
        }    
    }

	if(node==NULL) return node;
    
    node->height=maximum(getHeight(node->left),getHeight(node->right))+1;

    int balanceFactor= getBalanceFactor(node);
    
    if(balanceFactor>1 && getBalanceFactor(node->left)>=0) 
        return leftCaseRotate(node);

    if(balanceFactor>1 && getBalanceFactor(node->left)<0) 
        return leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && getBalanceFactor(node->right)<=0) 
        return rightCaseRotate(node);

    if(balanceFactor < -1 && getBalanceFactor(node->right)>0) 
        return rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* removeAVL(AVLNode* node,string &value, int &mode){
    if(mode == NAME){
        return removeName(node, value);
    }
    return removeNum(node, value);
}

void initializeAVL(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avlIsEmpty(AVL *avl) {
    return avl->_root == NULL;
}

bool findInAVL(AVL *avl, string &value, int mode) {
    AVLNode *temp = search(avl->_root, value, mode);
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

void avlInsert(AVL *avl,contact &value, int mode){
    if(mode == NAME){
        if(!findInAVL(avl,value.name, mode)){
            avl->_root=insertToAVL(avl->_root,value, mode);
            avl->_size++;
        }
    }else{
        if(!findInAVL(avl,value.number, mode)){
            avl->_root=insertToAVL(avl->_root,value, mode);
            avl->_size++;
        }        
    }
}

void avlDelete(AVL *avl,string &value, int mode){
    if(findInAVL(avl,value, mode)){
        avl->_root=removeAVL(avl->_root,value, mode);
        avl->_size--;
    }
}

void avlPreorder(AVLNode *root) {
    if (root) {
        avlPreorder(root->left);
        printContact(root->data);
        avlPreorder(root->right);
    }
}

void avlPostorder(AVLNode *root){
    if(root){
        avlPostorder(root->right);
        printContact(root->data);
        avlPostorder(root->left);
    }
}

void inOrderSave(AVLNode *root, string filename){
    if(root){
        SaveToText(root->data, filename);
        inOrderSave(root->left, filename);
        inOrderSave(root->right, filename);
    }
}

string getNodeNumber(AVL *avl, string name){
    AVLNode *tmp = searchName(avl->_root, name);
    return tmp->data.number;
}

string getNodeName(AVL *avl, string number){
    AVLNode *tmp = searchNum(avl->_root, number);
    return tmp->data.name;
}