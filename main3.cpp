/*
Main3.cpp trata hace uso de los resgistros. para esto primero lee el header y luego hace operaciones con los reshistros
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
	file.close();

	for (int i =0; i < estructura.size(); i++){
		cout << "Ingrese " << estructura.at(i).getName() << endl;
		cin>>dato;
		registro.agregarDato(dato);
		cin.ignore();
	}

	cout << registro.toString() << endl; 

	cout << "" << registro.toStringArchivo(estructura) ;

	ofstream archivo;
	archivo.open("prueba2.txt", ios::in | ios::out | ios::app);
	if (archivo.is_open()){
		//aqui deberiamos de escribir todo un vector de registros
		registro.Escribir(archivo, estructura);
	}
	archivo.close();

	return 0; 
}