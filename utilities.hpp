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
    contact tmp;
    tmp.name = *namestr;
    tmp.number = "";
    *wantCancel = *namestr == CANCEL_NAME;
    isExist = findInAVL(nameTree, tmp, NAME);
    return isExist; 
}
/* Return true jika berhasil dapat nomor dan ada di dalam daftar kontak*/
bool getFindContactNumber(AVL *numberTree, string *numberstr, bool *wantCancel){
    bool isExist = false;
    *numberstr = getNumber();
    contact tmp;
    tmp.name = "";
    tmp.number = *numberstr;
    *wantCancel = *numberstr == CANCEL_NUM;
    isExist = findInAVL(numberTree, tmp, NUMBER);
    return isExist;
}
/*Mengambil input dari user mengenai kontak sesuai mode*/
void receiveIdentity(AVL *nameTree, AVL *numberTree, contact *person, bool *wantCancel, int mode){
    bool isExist;
    if(mode == NAME){
        while(true){
            isExist = getFindContactName(nameTree, &person->name, wantCancel);
            if(isExist || *wantCancel){
                break;
            }
            Log("Nama tidak ada dalam kontak!");
        }
        if(!(*wantCancel))
            person->number = getNodeNumber(nameTree, person->name);
    }
    else{
        while(true){
            isExist = getFindContactNumber(numberTree, &person->number, wantCancel);
            if(isExist || *wantCancel){
                break;
            }
            Log("Nomor tidak ada dalam kontak!");
        }
        if(!(*wantCancel))
            person->name = getNodeName(numberTree, person->number);       
    }    
}
/*Return True jika berhasil mengupdate telepon.txt*/
bool updateDataBase(AVL *sourceTree){
    Log("Mengupdate data base");
    //memastikan telah dibuat file tmp.txt dulu
    ofstream myfile("tmp.txt");
    myfile.close();
    inOrderSave(sourceTree->_root, "tmp.txt");
    Log("33% done");
    if(std::remove("telepon.txt") == 0){
        Log("67% done");
        if(std::rename("tmp.txt", "telepon.txt") == 0){
            Log("100% done");
            return true;
        }
    }
    return false;
}
/*Fungsi khusus untuk hanya menampilkan kontak sesuai dengan parametr (mode, dan style)*/
void showContact(int mode, bool isDescending, AVL *numberTree, AVL *nameTree){
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
}
/*Fungsi untuk menghandle lihat kontak, mengambil mode dan style cara menampilkan kontak
kemudian memanggil showContact dengan mode dan style yang di dapat*/
void LihatKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    if(nameTree->_size < 1){
        Log("Tidak ada kontak yang dapat di tampilkan!");
        system("pause");
        return;
    }
    cout << "Menampilkan " << nameTree->_size << " Kontak\n";
    Log("Diurutkan berdasar:");
    int mode = getMode();
    bool isDescending = getStyle();
    //table mode
    showContact(mode, isDescending, numberTree, nameTree);
    system("pause");
}
/*Fungsi untuk menambah kontak ke dalam tree dan file telepon.txt*/
void TambahKontak(AVL *nameTree, AVL *numberTree){
    system("cls");
    //cek size kontal
    if(nameTree->_size  >= MAX_CONTACT){
        Log("Maaf, kontak sudah penuh!");
        system("pause");
        return;
    }
    Log("Menambah Kontak...");
    contact newPerson;
    bool cancel = false;
    bool isExist = false;
    GetDataLabel:
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
    cout << "Menambahkan " << newPerson.name << " / " << newPerson.number << endl;
    Log("Apakah data sudah benar?");
    if(!getConfirmation()){
        goto GetDataLabel;
    }
    avlInsert(nameTree, newPerson, NAME);
    avlInsert(numberTree, newPerson, NUMBER);
    if(SaveToText(newPerson, "telepon.txt")){
        Log("Berhasil menambahkan kontak");
        system("pause");
        return;
    }
    Log("Gagal menambahkan kontak");
    system("pause");
}
/*Fungsi untuk menghapus kontak di dalam tree dan telepon.txt*/
void HapusKontak(AVL *nameTree, AVL *numberTree){
    contact delContact;
    bool cancel = false;
    system("cls");
    Log("Menghapus Kontak...");
    GetDataLabel:
        Log("Mencari kontak yang akan dihapus dengan:");
        int mode = getMode();
        receiveIdentity(nameTree, numberTree, &delContact, &cancel, mode);

    if(cancel){
        Log("Penghapusan kontak dibatalkan");
        system("pause");
        return;
    }
    //Hapus the kontak
    cout << "Menghapus " << delContact.name << " / " << delContact.number << endl;
    if(!getConfirmation()){
        goto GetDataLabel;
    }
    avlDelete(nameTree, delContact, NAME);
    avlDelete(numberTree, delContact, NUMBER);
    if(updateDataBase(numberTree)){
        Log("Berhasil menghapus kontak!");
        system("pause");
        return;
    }
    Log("Gagal menghapus kontak");
    system("pause");
}
/*Fungsi untuk menyunting kontak dalam tree dan telepon.txt*/
void SuntingKontak(AVL *nameTree, AVL *numberTree){
    contact editContact;
    bool cancel = false;
    system("cls");
    Log("Menyunting Kontak...");
    Log("Apakah ingin menampilkan kontak terlebih dahulu?");
    if(getConfirmation()){
        showContact(1, false, numberTree, nameTree);
    }
    GetDataLabel:
        Log("Mencari kontak yang akan disunting berdasarkan:");
        int mode = getMode();
        receiveIdentity(nameTree, numberTree, &editContact, &cancel, mode);

    if(cancel){
        Log("Penyuntingan kontak dibatalkan");
        system("pause");
        return;
    }
    cout << "Mengganti " << editContact.name << " / " << editContact.number << endl;
    if(!getConfirmation()){
        goto GetDataLabel;
    }

    //dapatkan identitas baru
    Log("Pilih yang ingin anda ganti:");
    mode = getMode();
    if(mode == NAME){
        GetNewNameLabel:
            //dapatkan nama baru
            string newName;
            while(true){
                bool isExist = getFindContactName(nameTree, &newName, &cancel);
                if(!isExist || cancel){
                    break;
                }
                Log("Nama telah ada pada kontak!");
            }

        if(cancel){
            Log("Peyuntingan Kontak dibatalkan");
            system("pause");
            return;
        }
        cout << "Mengganti " << editContact.name << " menjadi " << newName << endl;
        if(!getConfirmation()){
            goto GetNewNameLabel;
        }
        //hapus node kontak yang akan di edit pada nametree
        avlDelete(nameTree, editContact, NAME);
        //ambil node kontak yang akan di edit pada numbertree
        AVLNode *tmp = searchNum(numberTree->_root, editContact.number);
        //ganti nama kontak
        editContact.name = newName;
        //ubah nama pada node numbertree
        tmp->data.name = newName;
        //simpan editContact ke nameTree
        nameTree->_root=insertToAVL(nameTree->_root,editContact, NAME);
        avlInsert(nameTree, editContact, NAME);
        if(updateDataBase(numberTree)){
            Log("Berhasil menyunting kontak");
            system("pause");
            return;
        }
    }
    else{
        GetNewNumberLabel:
            //dapet nomor baru
            string newNumber;
            while(true){
                bool isExist = getFindContactNumber(numberTree, &newNumber, &cancel);
                if(!isExist || cancel){
                    break;
                }
                Log("Nomor telah ada pada kontak!");
            }

        if(cancel){
            Log("Peyuntingan Kontak dibatalkan");
            system("pause");
            return;
        }
        cout << "Mengganti " << editContact.number << " menjadi " << newNumber << endl;
        if(!getConfirmation()){
            goto GetNewNumberLabel;
        }

        //hapus node kontak yang akan di edit pada numbertree
        avlDelete(numberTree, editContact, NUMBER);
        //ambil node kontak yang akan di edit pada nametree
        AVLNode *tmp = searchName(nameTree->_root, editContact.name);        
        //ganti nomor kontak
        editContact.number = newNumber;
        //ubah nomor pada node nametree
        tmp->data.number = editContact.number;
        //simpan editContact ke numberTree
        avlInsert(numberTree, editContact, NUMBER);
        if(updateDataBase(numberTree)){
            Log("Berhasil menyunting kontak");
            system("pause");
            return;
        }        
    }
    Log("Gagal menyunting kontak");
    system("pause");
    return;
}