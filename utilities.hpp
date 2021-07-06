#pragma once
#include <iostream>
#include <fstream>
#include "AVLtree.hpp"
#include "contact.hpp"
#include "msg.hpp"
/*
Berisi segala fungsi utilities yang menggabungkan AVL, msg, dan contact header
*/

//-----------------------Util Function---------------------------------------------//

/* Return true jika berhasil dapat nama dan ada di dalam daftar kontak*/
bool getFindContactName(AVL *nameTree, string *namestr, bool *wantCancel){
    bool isExist = false;
    *namestr = getName();
    if(*namestr == CANCEL_NAME){
        *wantCancel = true;
    }
    if(findInAVL(nameTree, *namestr, NAME)){
        isExist = true;
    }
    return isExist; 
}
/* Return true jika berhasil dapat nomor dan ada di dalam daftar kontak*/
bool getFindContactNumber(AVL *numberTree, string *numberstr, bool *wantCancel){
    bool isExist = false;
    *numberstr = getNumber();
    if(*numberstr == CANCEL_NUM){
        *wantCancel = true;
    }
    if(findInAVL(numberTree, *numberstr, NUMBER)){
        isExist = true;
    }
    return isExist;
}

bool saveToAll(AVL *nameTree, AVL *numberTree, string filename, contact &newPerson){
    avlInsert(nameTree, newPerson, NAME);
    avlInsert(numberTree, newPerson, NUMBER);
    return SaveToText(newPerson, filename);
}

bool deleteToAll(AVL *nameTree, AVL *numberTree, contact &delContact){
    avlDelete(nameTree, delContact.name, NAME);
    avlDelete(numberTree, delContact.number, NUMBER);
    inOrderSave(nameTree->_root, "tmp.txt");
    if(std::remove("telepon.txt") == 0){
        if(std::rename("tmp.txt", "telepon.txt") == 0){
            return true;
        }
    }
    return false; 
}

void LihatKontak(AVL *nameTree, AVL *numberTree){
    int mode = getMode();
    bool isDescending = getStyle();
    system("cls");
    printf("Menampilkan %d Kontak\n", nameTree->_size);
    //table mode
    printTableLine();
    Log("|           N A M A            |   N O M O R   |");
    printTableLine();
    if(mode == NAME){
        if(isDescending){
            avlPostorder(nameTree->_root);
        }else{
            avlPreorder(nameTree->_root);
        }
    }else{
        if(isDescending){
            avlPostorder(numberTree->_root);
        }else{
            avlPreorder(numberTree->_root);
        }
    }
    system("pause");
}

void TambahKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    Log("Menambah Kontak...");
    contact newPerson;
    bool cancel = false;
    bool isExist = false;
    //Name phase
    while(true){
        isExist = getFindContactName(nameTree, &newPerson.name, &cancel);
        if(!isExist){
            break;
        }
        Log("Nama ini telah ada dalam kontak!");
    }
    //Number phase
    while(!cancel){
        isExist = getFindContactNumber(numberTree, &newPerson.number, &cancel);
        if(!isExist){
            break;
        }
        Log("Nomor ini telah ada dalam kontak!");
    }

    if(cancel){
        Log("Penambahan kontak dibatalkan");
        system("pause");
        return;
    }

    //Jika telah sukses melewati filter diatas, tambahkan ke kontak
    if(saveToAll(nameTree, numberTree, "telepon.txt", newPerson)){
        Log("Berhasil menambahkan kontak");
        system("pause");
        return;
    }
    Log("Gagal menambahkan kontak");
    system("pause");
}

void HapusKontak(AVL *nameTree, AVL *numberTree){
    int mode = getMode();
    system("cls");
    Log("Menghapus Kontak...");
    contact delContact;
    bool cancel = false;
    bool isExist = false;
    if(mode == NAME){
        while(true){
            isExist = getFindContactName(nameTree, &delContact.name, &cancel);
            if(isExist || cancel){
                break;
            }
            Log("Nama tidak ada dalam kontak!");
        }
        if(!cancel)
            delContact.number = getNodeNumber(nameTree, delContact.name);
    }
    else{
        while(true){
            isExist = getFindContactNumber(numberTree, &delContact.number, &cancel);
            if(isExist || cancel){
                break;
            }
            Log("Nomor tidak ada dalam kontak!");
        }
        if(!cancel)
            delContact.name = getNodeName(numberTree, delContact.number);        
    }

    if(cancel){
        Log("Penghapusan kontak dibatalkan");
        system("pause");
        return;
    }
    /*
    -Tambah PENGKONFIRMASIAN
    */
    if(deleteToAll(nameTree, numberTree, delContact)){
        Log("Berhasil menghapus kontak");
        system("pause");
        return;
    }
    Log("Gagal menghapus kontak");
    system("pause");
}

void SuntingKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    //TBC
    //algoritma when i think rite now
    /*
    -get the contact name or phone, just like when hapus
    -ask the modified version
    -confirm penggantian
    */
}