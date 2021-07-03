#pragma once
#include <iostream>
#include <fstream>
#include "AVLtree.hpp"
#include "contact.hpp"
#include "msg.hpp"

//Util Function
void LihatKontak(AVLNode *rootName, AVLNode *rootNum){
    Log("Menampilkan Daftar Kontak\n");
    int mode = getMode();
    //table mode
    printTableLine();
    Log("|           N A M A            |   N O M O R   |\n");
    printTableLine();
    if(mode == NAME){
        preorder(rootName);
    }else{
        preorder(rootNum);
    }
}

void TambahKontak(AVLNode *rootName, AVLNode *rootNum){
    contact newPerson;
    bool GetContact = true;
    // while(GetContact){
    //     //name phase
    // }
}

void HapusKontak(AVLNode *rootName, AVLNode *rootNum){
    //TBC
}

void SuntingKontak(AVLNode *rootName, AVLNode *rootNum){
    //TBC
}