#pragma once
#include <iostream>
#include "constant.hpp"
using namespace std;
/*
Berisi segala fungsi untuk mengirimkan pesan kepada pengguna
*/

void Log(const char *msg){
    cout << msg << endl;
}

void welcomeMsg(){
    Log("  _______ _____ _____  _                      ");
    Log(" |__   __/ ____|  __ \\| |                     ");
    Log("    | | | |    | |__) | |__   ___  _ __   ___ ");
    Log("    | | | |    |  ___/| '_ \\ / _ \\| '_ \\ / _ \\");
    Log("    | | | |____| |    | | | | (_) | | | |  __/");
    Log("    |_|  \\_____|_|    |_| |_|\\___/|_| |_|\\___|\n");
    Log("Selamat datang di layanan nomor telepon TCPhone :D");
}

void showMenu(){
    Log("Berikut adalah hal yang dapat anda lakukan:");
    Log("1. Lihat daftar telepon");
    Log("2. Tambahkan kontak");
    Log("3. Hapus kontak");
    Log("4. Sunting kontak");
    Log("5. Akhiri program");
}

int getCommand(){
    int cmd = 0;
    Log("Silahkan pilih menu yang ingin anda lakukan:");
    while(cin.fail() || cmd < 1 || cmd > 5){
        cout << "[Nomor Menu] > ";
        cin >> cmd;
        cin.clear();
        cin.ignore(100, '\n');
    }
    return cmd;
}

int getMode(){
    int cmd = 0;
    while(cin.fail() || (cmd !=1 && cmd != 2)){
        cout << "[" << NAME<< "= Nama|" << NUMBER << " = Nomor] : ";
        cin >> cmd;
        cin.clear();
        cin.ignore(100, '\n');
    }
    return cmd;
}

bool getStyle(){
    bool isDescending = false;
    string tmp;
    Log("[Default Style: Naik]");
    cout << "Masukkan 'D/d' untuk mengubah style menjadi turun | selain itu tetap naik : ";
    cin >> tmp;
    cout << '\n';
    if(tmp == "D" || tmp == "d"){
        isDescending = true;
    }
    return isDescending;
}

bool getConfirmation(){
    char accepted[100];
    string acc;
    bool affirmative = false;
    while(true){
        cout << "[Y/N] > ";
        cin.getline (accepted, 100);
        acc = accepted;
        if(acc == "Y" || acc == "y"){
            affirmative = true;
            break;
        }else if(acc == "N" || acc == "n"){
            break;
        }
    }
    return affirmative;    
}