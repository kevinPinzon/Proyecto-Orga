/*
Main5.cpp
En este main ya podemos escribir al archivo y leer del archivo y cargamos los registros a memoria enun vector para los 
registros y tenrmos otro vector para los campos.
AHORA vamos a tratar de implementar el availlist
ESTE MAIN TOMA UN ARCHIVO EN FORMATO NO AVAILIST Y HACE UN NUEVO ARCHIVO CON OS MISMOS CAMPOS y registros
PERO EN FORMATO AVAILST
*/

#include "Campo.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using std::string;
using std::vector;
using namespace std;

int main (int argc, char* argv[]){
	char str[80];
	Campo field;
	Registro registro;//AQUI >>>>>>>>>>>>>>>>>>>>>>>>> TWNGO QUE LLAMAR AL METODO setviarValor0
	int cantDeCampos;
	vector <Campo> estructura;
	string dato;
	vector <Registro> registros;// vector donde se guardan los registros 
	int offsetRegistros, sizeRegistro;

	ifstream file;//abrimos el archivo
	file.open("memestest1.txt", ios::in | ios::out);

	if (file.is_open()){//si el archivo esta abierto 
		file.getline(str, 80, ',');
		cantDeCampos = atoi(str);

		for (int i = 0; i < cantDeCampos; i++){//leemos los campos
			file >> field; 
			estructura.push_back(field);
		}//terminamos de leer los campos

		offsetRegistros = file.tellg();//tomamos offset de donde empeizan los registros
		registro.setiarValor0( estructura.size());//Setiamos un string = "0" en cada dato del vector datos para 
		sizeRegistro = registro.toStringArchivo(estructura).size();//poder calcular la longitud de cada registro ARLF
		registro.clear();//quitamos los datos = "0" por cualquier cosa
		cout << "Tamaño de un registro (ARLF): " << sizeRegistro << endl; 


		while (registro.Leer(file, estructura)){//leemos TODOS los registros que hay en el archivo hasta eof
			registros.push_back(registro);
			registro.clear();
		}
		file.close();
	} else {
		cerr << "ERROR: no se pudo abrir el archivo para lectura" << endl;
	}	

	ofstream archivo;
	archivo.open("memestest2.txt", ios::in | ios::out | ios::trunc);

	stack <int> availlist;//declaración del availlist
	availlist.push(-1);

	if (archivo.is_open()){
		archivo << cantDeCampos << ',' << availlist.top() << ';';
		for (int i = 0; i < cantDeCampos; ++i)
			archivo << estructura.at(i);
		for (int i = 0; i < registros.size(); i++)
			registros.at(i).Escribir(archivo, estructura);
		archivo.close();

	} else{
		cerr << "ERROR: no se pudo abrir el archivo para escritura" << endl;
	}

	return 0;
}