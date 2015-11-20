#include "campo.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <cstdlib>

using namespace std;

Campo::Campo(){
}

Campo::Campo(const char* name, int fieldtype, int size, int sizedecimal, int keytype){
    strcpy(this->name, name);
    this-> fieldtype = fieldtype;
    this-> size = size;
    this-> sizedecimal = sizedecimal;
    this-> keytype = keytype;
}

string Campo::toString()const{
    stringstream ss;
    ss << "Name: " << name << "\tfieldtype: " << fieldtype << "\tsize: " << size << "\tsizedecimal: " << sizedecimal << "\tkeytype: " << keytype;
    return ss.str();
}

string Campo::inttoString(int num) const{
    stringstream ss;
    if(num < 10){
        ss << "00" << num;
    } else if (num <100){
        ss<<"0"<<num;
    } else {
        ss<<num;
    }
return ss.str();
}

string Campo::toStringArchivo() const{
    bool bandera=true;
    stringstream ss;//ss<<name<<";"<<fieldtype<<";"<<size<<";"<<sizedecimal<<";"<<keytype<<"\n";
    for (int i =0; i<30; i++){
        if (name[i] == '\0')
            bandera = false;
        if (bandera){
            ss << name[i];
        } else {
            ss<<'-';
        }
    }
    ss << ",";
    ss << inttoString(fieldtype) << ",";
    ss << inttoString(size) << ",";
    ss << inttoString(sizedecimal) << ",";
    ss << inttoString(keytype) << "\t";

    return ss.str();
}

ofstream& operator<<(ofstream& output, const Campo& campo){
    //std::string registro = toStringArchivo();
    output << campo.toStringArchivo();//registro.c_str();
    return output;
}
