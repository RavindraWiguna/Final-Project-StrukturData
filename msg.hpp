#pragma once
#include <iostream>
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
        printf("[Nomor Menu] > ");
        cin >> cmd;
        cin.clear();
        cin.ignore(100, '\n');
    }
    return cmd;
}

int getMode(){
    int cmd = 0;
    while(cin.fail() || (cmd !=1 && cmd != 2)){
        printf("Menggunakan mode [%d = Nama| %d = Nomor] : ", NAME, NUMBER);
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
    printf("Masukkan 'D/d' untuk mengubah style menjadi turun | selain itu tetap naik : ");
    cin >> tmp;
    printf("\n");
    if(tmp == "D" || tmp == "d"){
        isDescending = true;
    }
    return isDescending;
}