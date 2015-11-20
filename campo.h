#ifndef CAMPO_H
#define CAMPO_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Campo{
    char name[30];
    int fieldtype;//0-texto 1-entero 2-decimal
    int size;
    int sizedecimal;
    int keytype;//0- nada 1- llave primiaria 2- llave secundaria

public:
    Campo();
    Campo(const char* name, int fieldtype, int size, int sizedecimal, int keytype);
    string toString()const;
    string inttoString(int num) const;
    string toStringArchivo() const;
    friend ofstream& operator << (ofstream&, const Campo&);
    //friend ifstream& operator >> (ifstream&, Persona&)
    //podriamos poner gets y sets para cambiar cosas acerca de los campos

};

#endif // CAMPO_H
