/*
Main4.cpp
en este main lo que trato de hacer es leer los registros, todos los que estan en archivo hasata llegar al eof y después
imprimir los registros desde el vector donde se guardan
*/

#include "Campo.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using namespace std;

int main (int argc, char* argv[]){
	char str[80];
	Campo field;
	Registro registro;
	int cantDeCampos;
	vector <Campo> estructura;
	string dato;
	vector <Registro> registros;

	ifstream file;
	file.open("prueba2.txt", ios::in | ios::out);

	if (file.is_open()){
		file.getline(str, 80, ',');
		cantDeCampos = atoi(str);

		for (int i = 0; i < cantDeCampos; i++){
			file >> field; 
			estructura.push_back(field);
		}
	}

	while (registro.Leer(file, estructura)){
		registros.push_back(registro);
		registro.clear();
	}

	for (int i=0; i < registros.size(); i++)
		cout << registros.at(i).toString() << endl; 

	file.close();
	return 0; 
}