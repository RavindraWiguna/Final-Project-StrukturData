#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#define MAX_NAME 30
#define MAX_NUM 15
#define CANCEL_NAME "/cancel"
#define CANCEL_NUM "+0"
using namespace std;
/*
Berisi segala fungsi dan struktur yang berhubungan dengan perkontakan
*/
struct contact{
    string name;
    string number;
};

void printTableLine(){
     cout << "+------------------------------+---------------+" << endl;
}

void printContact(contact &person){
    cout << '|' << setw(MAX_NAME) << left << person.name << setfill(' ') << "|"<< setw(MAX_NUM) << left << person.number << '|' <<endl;
    printTableLine();
}

bool isValidNumber(string number){
    bool rtnval = true;
    if(number.size() > MAX_NUM){
        return false;
    }
    //special case for first number
    if(!((number[0] >= '0' && number[0] <= '9') || number[0] == '+')){
        return false;
    }
    for(string::iterator it = number.begin()+1; it != number.end(); ++it){
        if(*it < '0' && *it > '9'){
            rtnval = false;
            break;
        }
    }
    return rtnval;
}

bool isValidName(string name){
    return name.size() < MAX_NAME;
}

string getName(){
    // string namestr;
    char namechar[MAX_NAME];
    while(true){
        printf("Masukkan nama kontak [Maksimal: %d karakter | Masukkan '%s' untuk batal] >", MAX_NAME, CANCEL_NAME);
        cin.getline (namechar, MAX_NAME);
        // namestr = namechar;
        if(isValidName(namechar)){
            break;
        }
    }
    return namechar;
}

string getNumber(){
    // string numstr;
    char numchar[MAX_NUM];
    while(true){
        printf("Masukkan nomor kontak [Maksimal: %d digit| Masukkan '%s' untuk batal] >", MAX_NUM, CANCEL_NUM);
        cin.getline (numchar, MAX_NUM);
        if(isValidNumber(numchar)){
            break;
        }
    }
    return numchar;
}

bool Save(contact &newPerson){
    bool fail = false;
    std::ofstream textfile;
    textfile.open("telepon.txt", std::ios_base::app); 
    if(textfile.is_open()){
        textfile << newPerson.name << endl;
        textfile << newPerson.number << endl;
        textfile.close();
    }else{
        printf("Tidak dapat menemukan telepon.txt!");
        fail = true;
    }
    return fail;
}