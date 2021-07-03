/*
-----------------------------------
FINAL PROJECT STRUKTUR DATA TC 2021
-----------------------------------
Dibuat oleh: 
Nama    : Putu Ravindra Wiguna
NRP     : 5025201237
Kelas   : Struktur Data C
*/

#include "utilities.hpp"
using namespace std;

int main(){
    fstream textfile;
    textfile.open("telepon.txt");

    AVL nameTree, numberTree;
    avl_init(&nameTree);
    avl_init(&numberTree);

    if(textfile.is_open()){
        //extract data
        contact person;
        string tmp;
        int counter = -1;
        while( getline(textfile, tmp)){
            counter++;
            if(counter%2 == 0){
                person.name = tmp;
            }else{
                person.number = tmp;
                avl_insert(&nameTree, person, NAME);
                avl_insert(&numberTree, person, NUMBER);
            }
        }
        textfile.close();
    }
    else{
        cout << "Tidak dapat menemukan file telepon.txt!";
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
            LihatKontak(nameTree._root, numberTree._root);
            break;

        case 2:
            //TO DO finish tambak kontak
            TambahKontak(nameTree._root, numberTree._root);
            break;

        case 3:
            HapusKontak(nameTree._root, numberTree._root);
            Log("Blum ada\n");
            break;

        case 4:
            SuntingKontak(nameTree._root, numberTree._root);
            Log("Belum ada\n");
            break;

        case 5:
            Running = false;
            Log("Mengakhiri program\n");
            break;

        default:
            //seharusnya tidak terjadi
            Log("Terjadi suatu kesalahan\n");
            break;
        }
    }
    return 0;
}