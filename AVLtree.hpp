#pragma once
#include "contact.hpp"
using namespace std;
/*
Berisi segala fungsi dan struktur mengenai Struktur Data AVLTree
*/
/*Deklarasi struct dari avl node*/
struct AVLNode{
    contact data;
    struct AVLNode *left, *right;
    int height;
};
/*Deklarasi dari struct AVL*/
struct AVL{
    AVLNode *_root;
    unsigned int _size;
};
/*Fungsi untuk membuat node baru berdasarkan parameter kontak yang diberikan*/
AVLNode* createAVLNode(contact &newContact){
    AVLNode *newNode = new AVLNode;
    newNode->data.name = newContact.name;
    newNode->data.number = newContact.number;
    newNode->height=1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/*Fungsi untuk mencari nama dalam tree*/
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
/*Fungsi untuk mencari nomor dalam tree*/
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
/*Fungsi untuk menghandle search pada avl (berdasarkan mode)*/
AVLNode *search(AVLNode *root, contact &value, int mode){
    if(mode == NAME){
        return searchName(root, value.name);
    }
    return searchNum(root, value.number);
}
/*Fungsi untuk mendapatkan height dari suatu node*/
int getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}
/*Fungsi untuk menentukan nilai maksimal antara 2 bilangan*/
int maximum(int a,int b){
    return (a > b)? a : b;
}
/*Fungsi untuk meng-Rotate Kanan avl tree*/
AVLNode*rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=maximum(getHeight(pivotNode->left), getHeight(pivotNode->right))+1;
    newParrent->height=maximum(getHeight(newParrent->left), getHeight(newParrent->right))+1;
    return newParrent;
}
/*Fungsi untuk meng-Rotate Kiri avl tree*/
AVLNode* leftRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=maximum(getHeight(pivotNode->left), getHeight(pivotNode->right))+1;
    newParrent->height=maximum(getHeight(newParrent->left), getHeight(newParrent->right))+1;
    return newParrent;
}
/*Fungsi untuk menghandle leftcase skewed*/
AVLNode* leftCaseRotate(AVLNode* node){
    return rightRotate(node);
}
/*Fungsi untuk menghandle rightcase skewed*/
AVLNode* rightCaseRotate(AVLNode* node){
    return leftRotate(node);
}
/*Fungsi untuk menghandle zigzag kiri kanan skewed*/
AVLNode* leftRightCaseRotate(AVLNode* node){
    node->left = leftRotate(node->left);
    return rightRotate(node);
}
/*Fungsi untuk menghandle zigzag kanan kiri skewed*/
AVLNode* rightLeftCaseRotate(AVLNode* node){
    node->right = rightRotate(node->right);
    return leftRotate(node);
}
/*Fungsi untuk mendapatkan faktor keseimbangan*/
int getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return getHeight(node->left)-getHeight(node->right);
}
/*Fungsi untuk menambah node berdasar nama pada avl tree*/
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
/*Fungsi untuk menambah node berdasar nomor pada avl tree*/
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
/*Fungsi untuk menghandle peng-insertan avl tree berdasarkan mode*/
AVLNode* insertToAVL(AVLNode* node,contact &value, int mode) {
    if(mode == NAME){
        return insertName(node, value);
    }
    return insertNum(node, value);
}
/*Fungsi untuk menemukan node terkecil dari suatu root*/
AVLNode* findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}
/*Fungsi untuk menghapus node berdasarkan nama*/
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
/*Fungsi untuk menghapus node berdasarkan nomor*/
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
/*Fungsi untuk menghandle penghapusan node pada avl*/
AVLNode* removeAVL(AVLNode* node,contact &value, int mode){
    if(mode == NAME){
        return removeName(node, value.name);
    }
    return removeNum(node, value.number);
}
/*Menginisialisasi avl*/
void initializeAVL(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}
/*Tidak dipakai*/
bool avlIsEmpty(AVL *avl) {
    return avl->_root == NULL;
}
/*Fungsi untuk mengecek apakah kontak itu ada di avl*/
bool findInAVL(AVL *avl, contact &value, int mode) {
    AVLNode *temp = search(avl->_root, value, mode);
    if (temp == NULL)
        return false;
    
    //check by mode
    if(mode == NAME){
        if (temp->data.name == value.name){
            return true;
        }
        return false;
    }else{
        if(temp->data.number == value.number){
            return true;
        }
        return false;
    }
}
/*Fungsi untuk menghandle penambahan avl tree*/
void avlInsert(AVL *avl,contact &value, int mode){
    if(!findInAVL(avl, value, mode)){
        avl->_root=insertToAVL(avl->_root,value, mode);
        avl->_size++;
    }
}
/*Fungsi untuk menghandle penghapusan node di avl*/
void avlDelete(AVL *avl,contact &value, int mode){
    if(findInAVL(avl,value, mode)){
        avl->_root=removeAVL(avl->_root,value, mode);
        avl->_size--;
    }
}
/*Fungsi untuk memprintkan isi avl tree secara preorder*/
void avlPreorder(AVLNode *root) {
    if (root) {
        avlPreorder(root->left);
        printContact(root->data);
        avlPreorder(root->right);
    }
}
/*Fungsi untuk menampilkan isi avl tree secara postorder*/
void avlPostorder(AVLNode *root){
    if(root){
        avlPostorder(root->right);
        printContact(root->data);
        avlPostorder(root->left);
    }
}
/*Fungsi untuk menyimpan isi avl tree ke dalam file secara inorder*/
void inOrderSave(AVLNode *root, string filename){
    if(root){
        SaveToText(root->data, filename);
        inOrderSave(root->left, filename);
        inOrderSave(root->right, filename);
    }
}
/*Fungsi untuk mendapatkan nomor dari nama suatu node*/
string getNodeNumber(AVL *avl, string name){
    AVLNode *tmp = searchName(avl->_root, name);
    return tmp->data.number;
}
/*Fungsi untuk mendapatkan nama dari nomor suatu node*/
string getNodeName(AVL *avl, string number){
    AVLNode *tmp = searchNum(avl->_root, number);
    return tmp->data.name;
}