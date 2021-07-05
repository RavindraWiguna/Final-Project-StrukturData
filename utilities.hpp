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
        if(isExist){
            Log("Nama ini telah ada dalam kontak!");
        }else{
            break;
        }
    }
    //Number phase
    while(!cancel){
        isExist = getFindContactNumber(numberTree, &newPerson.number, &cancel);
        if(isExist){
            Log("Nomor ini telah ada dalam kontak!");
        }else{
            break;
        }
    }

    if(cancel){
        Log("Penambahan kontak dibatalkan");
        system("pause");
        return;
    }

    //Jika telah sukses melewati filter diatas, tambahkan ke kontak
    insertToAVL(nameTree, newPerson, NAME);
    insertToAVL(numberTree, newPerson, NUMBER);
    //Tambahkan ke file telepon
    cancel = Save(newPerson, "telepon.txt");
    if(!cancel){
        Log("Kontak telah berhasil ditambahkan");
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
    //kalo make nama
    if(mode == NAME){
        while(true){
            isExist = getFindContactName(nameTree, &delContact.name, &cancel);
            if(isExist || cancel){
                break;
            }else{
                Log("Nama tidak ada dalam kontak!");
            }
        }
        //get the number
        if(!cancel)
            delContact.number = getNodeNumber(nameTree, delContact.name);
    }
    else{
        //klo pake nomor
        while(true){
            isExist = getFindContactNumber(numberTree, &delContact.number, &cancel);
            if(isExist || cancel){
                break;
            }else{
                Log("Nomor tidak ada dalam kontak!");
            }
        }
        //get the name
        if(!cancel)
            delContact.name = getNodeName(numberTree, delContact.number);        
    }

    if(cancel){
        Log("Penghapusan kontak dibatalkan");
        system("pause");
        return;
    }

    //hapus in tree
    avlDelete(nameTree, delContact.name, NAME);
    avlDelete(numberTree, delContact.number, NUMBER);
    //save tree ke dalam tmp.txt
    inOrderSave(nameTree->_root);
    //hapus telepon txt dan gantikan dengan tmp.txt
    int status = std::remove("telepon.txt");
    if(status == 0){
        status = std::rename("tmp.txt", "telepon.txt");
        if(status == 0){
            Log("Berhasil menghapus kontak");
            system("pause");
            return;
        }
    }
    Log("Gagal menghapus kontak");
    system("pause");
}

void SuntingKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    //TBC
}