/*
-----------------------------------
FINAL PROJECT STRUKTUR DATA TC 2021
-----------------------------------
Dibuat oleh: 
Nama    : Putu Ravindra Wiguna
NRP     : 5025201237
Kelas   : Struktur Data C
Tanggal Pembuatan pertama:
29 Juni 2021
*/

#include "utilities.hpp"
using namespace std;

int main(){
    fstream textfile;
    textfile.open("telepon.txt");

    AVL nameTree, numberTree;
    initializeAVL(&nameTree);
    initializeAVL(&numberTree);

    //extract data
    if(textfile.is_open()){
        contact person;
        string tmp;
        int counter = -1;
        while( getline(textfile, tmp)){
            counter++;
            if(counter%2 == 0){
                person.name = tmp;
            }else{
                person.number = tmp;
                avlInsert(&nameTree, person, NAME);
                avlInsert(&numberTree, person, NUMBER);
            }
        }
        textfile.close();
    }
    else{
        Log("Tidak dapat menemukan file telepon.txt!");
        return 0;
    }

    //UI Start
    welcomeMsg();
    //program start
    int command;
    bool Running = true;
    while(Running){
        showMenu();
        command = getCommand();
        switch (command){
        case 1:
            LihatKontak(&nameTree, &numberTree);
            break;

        case 2:
            TambahKontak(&nameTree, &numberTree);
            break;

        case 3:
            HapusKontak(&nameTree, &numberTree);
            break;

        case 4:
            SuntingKontak(&nameTree, &numberTree);
            break;

        case 5:
            Running = false;
            Log("Mengakhiri program");
            break;

        default:
            //seharusnya tidak terjadi
            Log("Terjadi suatu kesalahan");
            break;
        }
        system("cls");
    }
    return 0;
}