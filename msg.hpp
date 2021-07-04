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
    while(cmd < 1 || cmd > 5){
        Log("Silahkan pilih menu yang ingin anda lakukan:");
        printf("[Nomor Menu] > ");
        cin >> cmd;
    }
    return cmd;
}

int getMode(){
    int cmd = -1;
    while(cmd < 0 || cmd > 1){
        Log("Menggunakan mode [0 = Nama| 1 = Nomor]: ");
        cin >> cmd;
    }
    return cmd;
}