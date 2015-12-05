#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "campo.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;

class Registro{
    vector <string> datos;
public:
    Registro();
    vector<string> getDatos();
    string toString()const;
    string inttoString(int, bool) const;
    string toStringArchivo(vector<Campo>)const;
    void Escribir(ofstream&, vector<Campo>);
    int Escribir(ifstream&,ofstream&, vector<Campo>,int);
    bool Leer(ifstream&, vector<Campo>,int);
    void agregarDato(string);
    void clear();
    void setiarValor0(int);

};

#endif // REGISTRO_H
