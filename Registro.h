<<<<<<< HEAD
/*
Registro.h 
Esta clase contiene un vector de string. en cada uno de esos strings guarda la información que corresponde a un campo 
de la estructura. Tiene métodos para guardarse en archivo y para leerse del archivo 
Elmer Lopez
20 noviembre 2015
*/

=======
#ifndef REGISTRO_H
#define REGISTRO_H
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
<<<<<<< HEAD
#include "Campo.h"
=======

#include "campo.h"
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;

class Registro{
<<<<<<< HEAD
	vector <string> datos;
public:
	Registro();
	vector<string> getDatos();
	string toString()const;
	string inttoString(int, bool) const;
	string toStringArchivo(vector<Campo>)const;
	void Escribir(ofstream&, vector<Campo>);
	void Leer(ifstream&, vector<Campo>);
	void agregarDato(string);

	/* data */
};
=======
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
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
