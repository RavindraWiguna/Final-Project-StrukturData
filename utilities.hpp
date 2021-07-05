#pragma once
#include <iostream>
#include <fstream>
#include "AVLtree.hpp"
#include "contact.hpp"
#include "msg.hpp"
/*
Berisi segala fungsi utilities yang menggabungkan AVL, msg, dan contact header
*/

//Util Function
void LihatKontak(AVL *nameTree, AVL *numberTree){
    int mode = getMode();
    bool isDescending = getStyle();
    system("cls");
    Log("Menampilkan kontak");
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
    //Name phase
    while(true){
        newPerson.name = getName();
        //if user want to cancel
        if(newPerson.name == CANCEL_NAME){
            cancel = true;
            break;
        }
        //cek apakah sudah ada di daftar
        if(!findInAVL(nameTree, newPerson.name, NAME)){
            break;
        }else{
            Log("Nama ini telah ada di dalam kontak!");
        }
    }
    //Number phase
    while(!cancel){
        newPerson.number = getNumber();
        if(newPerson.number == CANCEL_NUM){
            cancel = true;
            break;
        }
        if(!findInAVL(numberTree, newPerson.number, NUMBER)){
            break;
        }else{
            Log("Nomor ini telah ada di dalam kontak!");
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
    //kalo make nama
    if(mode == NAME){
        while(true){
            delContact.name = getName();
            //if user want to cancel
            if(delContact.name == CANCEL_NAME){
                cancel = true;
                break;
            }
            //cek apakah sudah ada di daftar
            if(findInAVL(nameTree, delContact.name, NAME)){
                break;
            }else{
                Log("Nama ini tidak ada di dalam kontak!");
            }
        }
        //get the number
        if(!cancel)
            delContact.number = getNodeNumber(nameTree, delContact.name);
    }
    else{
        //klo pake nomor
        while(true){
            delContact.number = getNumber();
            //if user want to cancel
            if(delContact.number == CANCEL_NUM){
                cancel = true;
                break;
            }
            //cek apakah sudah ada di daftar
            if(findInAVL(numberTree, delContact.number, NUMBER)){
                break;
            }else{
                Log("Nomor ini tidak ada di dalam kontak!");
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
    //hapus in txt
    ofstream tmpfile("tmp.txt");
    inOrderSave(nameTree->_root);
    tmpfile.close();
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