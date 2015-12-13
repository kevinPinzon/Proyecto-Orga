#include "Campo.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using namespace std; 


int main (int argc, char* argv[]){

	//cout << "¡HOLA! ¡Qué gusto verte!" << endl; 
	Campo field;

	vector <Campo> estructura; 
	int CantDeCampos = 0;

	ofstream archivo;
	archivo.open("prueba2.txt", ios::in | ios::out | ios::trunc);

//hace el header
	cout << "Ingrese la cantidad de campos que desea: " << endl; 
	cin >> CantDeCampos;

	for (int i =0 ; i < CantDeCampos; i++){
		cout << "Campo ";
		cin >> field;
		estructura.push_back(field);
	}
	 archivo << CantDeCampos ; 

	 archivo << "," ;

	for (int i = 0; i < CantDeCampos; ++i){
		field = estructura.at(i);
		cout << field.toString() << endl; 
		archivo << field;
	}


	//archivo<<field;
	archivo.close();

	return 0;
}// fin del main 