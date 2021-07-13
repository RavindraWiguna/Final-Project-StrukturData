#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>
using namespace std;
using std::left;
using std::right;

int main(){
    vector<int> arr;
    for(int i = 0;i<1000000;i++){
        arr.push_back(i);
    }
    int tgt;
    cin >> tgt;
    int id = 0;
    time_t timeStart, timeEnd;
    time(&timeStart);
    for(int i = 0;i<1000000;i++){
        if(arr[i] == tgt){
            id = i;
            break;
        }
    }
    time(&timeEnd);
    double timetaken = double(timeEnd-timeStart);
    cout << id << " with time: " << timetaken;
}