
#include "IDGenerator.h"
#include <fstream>
#include <iostream>

#define ID_LENGTH 11

string IDGenerator::generate() {
    string strID;
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < ID_LENGTH; i++) {
        strID += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return strID;
}

void IDGenerator::init() {
    // in
    string line;
    ifstream ifile("counter_id.txt", ios::in);
    int i = 0;
    int counter = 0;
    getline(ifile, line);
    while (i < line.length()) {
        counter *= 10;
        counter += line[i++] - '0';
    }
    // change random feeder each time
    srand(counter * ID_LENGTH);
    ifile.close();
    // out
    ofstream ofile("counter_id.txt", ios::out);
    ofile << ++counter;
    ofile.close();
}

