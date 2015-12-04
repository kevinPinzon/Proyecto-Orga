/*
Main6.cpp
aqui tratamos de seguir con lo del availlist
*/

#include "Campo.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "SpecialStack.h"

using std::string;
using std::vector;
using namespace std;

int menu();
vector <Campo> cargarHeader(ifstream&);
string toStringArchivoD1RD(int);

int main (int argc, char* argv[]){
	char str[80];
	Campo field;
	Registro registro;
	int cantDeCampos, offsetRegistros, sizeRegistro, pos1=0;
	vector <Campo> estructura;
	string dato, linea, sublinea;
	vector <Registro> registros;// vector donde se guardan los registros 
	SpecialStack availlist; //declaración de availlist

	ifstream file;//abrimos el archivo para lectura 
	file.open("memestest2.txt", ios::in | ios::out);
	
	if (file.is_open()){
		estructura = cargarHeader(file);
//----------------- >>>>>>>>>>>>>>>>>> ESTE COMBITO DE LINEAS VA SIEMPRE DEPUES DE LEER LA ESTRUCTURA DEL HEADER
		offsetRegistros = file.tellg();//tomamos el offset de donde empiezan los registros!!
		registro.setiarValor0(estructura.size());
		sizeRegistro = registro.toStringArchivo(estructura).size();//tomamos la longitud de un registro de olongitud fija (ARLF)
		registro.clear();
//----------------- >>>>>>>>>>>>>>>>>> TERMINA COMBITO 

		cout << "Size de un registro de tamaño fijo: " << sizeRegistro << endl; 

// LEEMOS REGISTROS HASTA EOF
		while (registro.Leer(file, estructura)){//la verdad deberiamos de hacer un metodo aqui que regrese vector <Registro>
			registros.push_back(registro);
			registro.clear();
		}

		file.clear();
		file.seekg(0, ios::beg);
		cout << "Cargando el availist Offset en: " << file.tellg() << endl;
		file.getline(str, 20, ';');
		linea = str; 
		cout << "Cargando el availist: " << linea << endl;
		pos1 = linea.find(',', 0);
		pos1++;	
		sublinea = linea.substr(pos1, linea.size()-pos1);
		cout << sublinea << endl; 

		availlist.inicializar(file, atoi(sublinea.c_str()), offsetRegistros, sizeRegistro);
		cout<<"termino inicializar"<<endl;		
		file.close();
	} else {
		cerr << "ERROR: no se pudo abrir el archivo para lectura de header y registros." << endl;
	}

	ofstream archivo;
	archivo.open("memestest2.txt", ios::in | ios::out);

	if (archivo.is_open()){
		int opcion = menu();
		while (opcion != 0){
			switch (opcion){
				case 1:{//agregar registro
					cin.ignore();
					for (int i =0; i < estructura.size(); i++){
						cout << "Ingrese " << estructura.at(i).getName() << ":" << endl;
						//getline(cin, dato);
						//if (estructura.at(i).getFieldtype() == 1)//texto
						//else 
						cin>>dato;
						registro.agregarDato(dato);
					}
					registros.push_back(registro);
					archivo.seekp(offsetRegistros+(sizeRegistro*(registros.size()-1)));

					registro.Escribir(archivo, estructura);
					registro.clear();
				}
				break;

				case 2:{//listar CAMPOS y REGISTROS diunso
					cout << "CAMPOS" << endl;
					for (int i=0; i<estructura.size(); i++)
						cout << estructura.at(i).toString() << endl; 
					cout << "REGISTROS" << endl;
					for (int i=0; i<registros.size(); i++)
						cout << registros.at(i).toString() << endl;
					cout << "Availlist" << endl;
						cout << availlist.toString();
				}
				break;

				case 3:{}
				break;

				case 4:{//BORRAR REGISTRO
					int pos;
					cout <<"Ingrese la posicion del registro que quiere borrar"<< endl;
					cin>>pos;
					pos--;//le bajo uno para que ya este en termino de i que usamos para los fors donde i=0
					if (!(pos < 0 || pos >= registros.size())){	//validado que la pos 1 - registros.zise()
						if (!availlist.isEmpty()){
							int sigPosDisp = availlist.peek();
							string alBorrado = toStringArchivoD1RD(sigPosDisp);
							archivo.seekp(offsetRegistros+(sizeRegistro*(pos+availlist.posicionesAntesDe(pos))));
							archivo << alBorrado;//ya marqué el registro borrado
							availlist.push(pos);//actualizamos el availlist
							//registros.at(pos).clear();
							registros.erase(registros.begin()+pos);//borra el registro del vector en memoria

						} else {//else para cuando esta vacío el availist que no deberia de estar porque deberia de estar -1
							cout << "EL AVAILLIST ESTA COMPLETAMENTE VACIO" << endl;
						}
					} else {
						cout << "ERROR la posicionque ha ingresado es invalida." << endl;
					}

				}
				break;//fin borrar registro

				default:{}
				break;
			}
			opcion = menu();
		}
		archivo.close();
	} else {
		cerr << "ERROR: no se pudo abrir el archivo para escritura." << endl; 
	}
	

	return 0; 
}//fin del main 

int menu(){
	int opcion; 
	cout << "-- MENU -- " << endl; 
	cout << "1.- Agregar registro" << endl; 
	cout << "2.- Listar registros" << endl;
	cout << "3.- Modificar registro" << endl; 
	cout << "4.- Borrar registro" << endl;
	cin >> opcion;
	return opcion;
}// fin del menu 

vector <Campo> cargarHeader (ifstream& file){
	vector <Campo> estructura;
	Campo field;
	char str[100];
	string linea, sublinea;
	int pos1=0, pos2, cantDeCampos;
	if (file.is_open()){
		file.getline(str, 30, ';');
		linea = str;
		pos2 = linea.find(',', 0);
		sublinea = linea.substr(pos1, pos2-pos1);
		cantDeCampos = atoi(sublinea.c_str());

		for (int i=0; i<cantDeCampos; i++){
			file >> field;
			estructura.push_back(field);
		}

	} else {
		cerr << "ERROR: No se pudo abrir el archivo para cargar el header " << endl; 
	}

	return estructura; 
}// fin del método cargarHeader

string toStringArchivoD1RD(int pos){//devuelve la cadena que va en el registro borrado
	stringstream ss;
	ss<<"*"<<pos<<";";
	return ss.str();
}