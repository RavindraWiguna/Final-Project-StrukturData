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
    system("cls");
    Log("Menampilkan kontak");
    //table mode
    printTableLine();
    Log("|           N A M A            |   N O M O R   |");
    printTableLine();
    if(mode == NAME){
        preorder(nameTree->_root);
    }else{
        preorder(numberTree->_root);
    }
    system("pause");
}

void TambahKontak(AVL *nameTree, AVL *numberTree){
    char tmp[2];
    cin.getline (tmp, MAX_NAME);
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
        if(!avl_find(nameTree, newPerson.name, NAME)){
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
        if(!avl_find(numberTree, newPerson.number, NUMBER)){
            break;
        }else{
            Log("Nomor ini telah ada di dalam kontak!");
        }
    }

    if(cancel){
        return;
    }

    //Jika telah sukses melewati filter diatas, tambahkan ke kontak
    avl_insert(nameTree, newPerson, NAME);
    avl_insert(numberTree, newPerson, NUMBER);
    //Tambahkan ke file telepon
    cancel = Save(newPerson);
    if(!cancel){
        Log("Kontak telah berhasil ditambahkan");
        system("pause");
        return;
    }
    Log("Gagal menambahkan kontak");
    system("pause");
}

void HapusKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    //TBC
}

void SuntingKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    //TBC
}