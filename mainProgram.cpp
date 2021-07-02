#include <iostream>
#include <fstream>
#include "AVLtree.hpp"
using namespace std;

int main(){

    //Open and read the telepon.txt
    fstream textfile;
    textfile.open("telepon.txt");
    //tree
    AVL nameTree, numberTree;
    avl_init(&nameTree);
    avl_init(&numberTree);
    //extract data
    contact person;
    string tmp;
    int counter = -1;
    int modeName = 0;
    int modeNum = 1;
    if(textfile.is_open()){
        while( getline(textfile, tmp)){
            counter++;
            //genap == nama, ganjil == nomor
            if(counter%2 == 0){
                person.name = tmp;
            }else{
                person.number = tmp;
                //setelah dapet nomor dan angka, masukkan ke tree name dan nomor
                avl_insert(&nameTree, person, NAME);
                avl_insert(&numberTree, person, NUMBER);
            }
        }
        textfile.close();
    }else{
        cout << "Can not locate the telepon.txt";
    }
    preorder(nameTree._root);
    cout << "----------------------------" << endl;
    preorder(numberTree._root);
    cout << "program done" << endl;
    return 0;
}