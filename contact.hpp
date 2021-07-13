#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "constant.hpp"
using namespace std;
/*
Berisi segala fungsi dan struktur yang berhubungan dengan perkontakan
*/
/*Deklarasi Struct Kontak*/
struct contact{
    string name;
    string number;
};
/*Memprint garis tabel*/
void printTableLine(){
     cout << "+------------------------------+---------------+" << endl;
}
/*Memprint isi kontak dengan bentuk tabel*/
void printContact(contact &person){
    cout << '|' << setw(MAX_NAME) << left << person.name << setfill(' ') << "|"<< setw(MAX_NUM) << left << person.number << '|' <<endl;
    printTableLine();
}
/*Mengecek ke-validan input nomor*/
bool isValidNumber(std::string number){
    bool rtnval = true;
    if(number.size() > MAX_NUM){
        return false;
    }
    //special case for first number
    if(!((number[0] >= '0' && number[0] <= '9') || number[0] == '+')){
        return false;
    }
    for(string::iterator it = number.begin()+1; it != number.end(); ++it){
        if(*it < '0' || *it > '9'){
            rtnval = false;
            break;
        }
    }
    return rtnval;
}
/*Mengecek ke-validan input nama*/
bool isValidName(std::string name){
    return name.size() < MAX_NAME;
}
/*Mengambil input nama dari user sampai mendapat input yang valid*/
std::string getName(){
    // string namestr;
    char namechar[MAX_NAME*MAX_NAME];
    while(true){
        cout<<"Masukkan nama kontak [Maksimal: "<<MAX_NAME<<" karakter | Masukkan '"<<CANCEL_NAME<<"' untuk batal] >";
        cin.getline (namechar, MAX_NAME*MAX_NAME);
        // namestr = namechar;
        // cin.clear();
        // cin.ignore(100, '\n');
        if(isValidName(namechar)){
            break;
        }
    }
    return namechar;
}
/*Mengambil input nomor dari user sampai mendapat input yang valid*/
std::string getNumber(){
    // string numstr;
    char numchar[MAX_NUM*MAX_NUM];
    while(true){
        cout << "Masukkan nomor kontak [Maksimal: "<<MAX_NUM<<" digit| Masukkan '"<<CANCEL_NUM<<"' untuk batal] >";
        cin.getline (numchar, MAX_NUM*MAX_NUM);
        // cin.clear();
        // cin.ignore(100, '\n');
        if(isValidNumber(numchar)){
            break;
        }        
    }
    return numchar;
}
/*Menambahkan suatu kontak ke dalam suatu text*/
bool SaveToText(contact &newPerson, std::string fileName){
    bool success = true;
    ofstream textfile;
    textfile.open(fileName, std::ios_base::app); 
    if(textfile.is_open()){
        textfile << newPerson.name << endl;
        textfile << newPerson.number << endl;
        textfile.close();
    }else{
        cout << "Tidak dapat menemukan " << fileName << endl;
        success = false;
    }
    return success;
}