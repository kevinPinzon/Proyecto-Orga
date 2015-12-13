/*
main2.cpp 
este main lee el header por campos y los agrega al vector que se llama estructura. luego imprime el vector estructura
*/
#include "Campo.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using namespace std;

int main (int argc, char* argv[]){
	char str[80];
	Campo field;
	int cantDeCampos;
	vector <Campo> estructura;

	ifstream file;
	file.open("prueba2.txt", ios::in | ios::out);


	if (file.is_open()){
		//cout << file.get() << endl;
		file.getline(str, 80, ',');
		cantDeCampos = atoi(str);		
		
		for (int i = 0; i < cantDeCampos; i++){
			file >> field; 
			estructura.push_back(field);
		}
		//file.getline(str, 80, '\t');
		//cout << str << endl; 

		for (int i=0; i< estructura.size(); i++){
			field = estructura.at(i);
			cout << field.toString() << endl;
		}
	}

	file.close();

	return 0;
}