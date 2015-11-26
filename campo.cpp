#include "campo.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <QString>
#include <QFile>

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


istream& operator>>(istream& input, Campo& campo){
    input.ignore();
    cout << "char: Nombre de campo" << endl;
    input.getline(campo.name, 30);
    cout << "int: fieldtype donde 1- entero 2- textp 3- decimal" << endl;
    input >> campo.fieldtype;
    cout << "int: size para longitud de cadena de texto" << endl;
    input >> campo.size;
    cout << "int: size para digitos decimales" << endl;
    input >> campo.sizedecimal;
    cout << "int: tipo de llave 0- nada 1- primaria 2- secundaria" << endl;
    input >> campo.keytype;
    return input;
}

ofstream& operator<<(ofstream& output, const Campo& campo){
    //std::string registro = toStringArchivo();
    output << campo.toStringArchivo();//registro.c_str();

    return output;
}
char* Campo::getName()const{

    return NULL;
}
int Campo::getFieldtype()const{

    return 0;
}
int Campo::getSize()const{

    return 0;
}
int Campo::getKeytype()const{

    return 0;
}

\
