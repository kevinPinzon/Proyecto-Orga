/*
Registro.h 
Esta clase contiene un vector de string. en cada uno de esos strings guarda la información que corresponde a un campo 
de la estructura. Tiene métodos para guardarse en archivo y para leerse del archivo 
Elmer Lopez
20 noviembre 2015
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Campo.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;

class Registro{
	vector <string> datos;
public:
	Registro();
	string toString()const;
	string inttoString(int) const;
	string toStringArchivo(vector<Campo>)const;
	void Escribir(ofstream&, vector<Campo>);
	void Leer(ifstream&, vector<Campo>);

	/* data */
};