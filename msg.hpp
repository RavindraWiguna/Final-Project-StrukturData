#pragma once
#include <iostream>
using namespace std;
void Log(const char *msg){
    cout << msg;
}

void welcomeMsg(){
    Log("  _______ _____ _____  _                      \n");
    Log(" |__   __/ ____|  __ \\| |                     \n");
    Log("    | | | |    | |__) | |__   ___  _ __   ___ \n");
    Log("    | | | |    |  ___/| '_ \\ / _ \\| '_ \\ / _ \\\n");
    Log("    | | | |____| |    | | | | (_) | | | |  __/\n");
    Log("    |_|  \\_____|_|    |_| |_|\\___/|_| |_|\\___|\n\n");
    Log("Selamat datang di layanan nomor telepon TCPhone :D\n");
}

void showMenu(){
    Log("Berikut adalah hal yang dapat anda lakukan:\n");
    Log("1. Lihat daftar telepon\n");
    Log("2. Tambahkan kontak\n");
    Log("3. Hapus kontak\n");
    Log("4. Sunting kontak\n");
    Log("5. Akhiri program\n");
}

int getCommand(){
    int cmd = 0;
    while(cmd < 1 || cmd > 5){
        Log("Silahkan pilih menu yang ingin anda lakukan:\n");
        Log("[Nomor Menu] > ");
        cin >> cmd;
    }
    return cmd;
}

int getMode(){
    int cmd = -1;
    while(cmd < 0 || cmd > 1){
        Log("Menggunakan mode [0 = Nama| 1 = Nomor] > ");
        cin >> cmd;
        Log("\n");
    }
    return cmd;
}