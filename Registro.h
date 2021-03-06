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
    Registro(vector<Campo>);//este vector llena con datos insignificantes(-----,0000)
    vector<string> getDatos();
    string toString()const;
    string inttoString(int, bool) const;
    string toStringArchivo(vector<Campo>)const;
    void Escribir(ofstream&, vector<Campo>);
    bool Leer(ifstream&, vector<Campo>);
    void agregarDato(string);

    void clear();
    void setiarValor0(int);
    bool esValido();
    void setDatos(vector<string>);
};

#endif // REGISTRO_H
