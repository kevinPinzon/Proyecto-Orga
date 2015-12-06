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
string toStringArchivoD1RD(int);//devuelve la cadena que va en el registro borrado
string toStringArchivoHeadAvailist(int);//devuelve la posicion head del availist en cadena para escribirla en header

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
			if (registro.esValido())
				registros.push_back(registro);
			registro.clear();
		}

		availlist.inicializar(file, offsetRegistros, sizeRegistro);
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
					if (availlist.peek() == -1)
						archivo.seekp(offsetRegistros+(sizeRegistro*(registros.size()-1)));
					else {
						int posArchivo = availlist.pop();
						cout << "La posicion que sale del availlist: "<<posArchivo<<endl;
						archivo.seekp(offsetRegistros+posArchivo*sizeRegistro);
					}

					registro.Escribir(archivo, estructura);
					registro.clear();
					archivo.seekp(4);//4 es la posicion en el archivo donde empieza el espacio para el número 
					//que es la cabeza del availist en el header
					archivo << toStringArchivoHeadAvailist(availlist.peek());
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
							int sigPosDisp = availlist.peek();//tomo la siguiente posicióndisponible del availist
							string alBorrado = toStringArchivoD1RD(sigPosDisp);//hago la cadena que va a marcar al registro borrado
							int posArchivo = pos+availlist.posicionesAntesDe(pos);
							//int offsetBorrar = offsetRegistros+(sizeRegistro*(pos+availlist.posicionesAntesDe(pos)));
							archivo.seekp(offsetRegistros+(sizeRegistro*posArchivo));
							archivo << alBorrado;//ya marqué el registro borrado
							availlist.push(posArchivo);//actualizamos el availlist
							archivo.seekp(4);
							archivo << toStringArchivoHeadAvailist(posArchivo);
							//registros.at(pos).clear();
							registros.erase(registros.begin()+pos);//borra el registro del vector en memoria

						} else {//else para cuando esta vacío el availist que no deberia de estar porque deberia de estar -1
							cout << "EL AVAILLIST ESTA COMPLETAMENTE VACIO" << endl;
						}
					} else {
						cout << "ERROR la posicion que ha ingresado es invalida." << endl;
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

string toStringArchivoHeadAvailist(int num){//devuelve la cadena que es la cabeza del availist que se pone en header
	stringstream ss;
	if (num < 0){
		ss <<"0000-1";
	}else if(num < 10){
		ss << "00000" << num;
	} else if (num <100){
		ss<<"0000"<<num;
	} else if (num < 1000){
		ss<<"000"<<num;
	} else if (num < 10000){
		ss<<"00"<<num;
	} else if (num < 100000){
		ss<<"0"<<num;
	} else {
		ss<<num;
	}
	cout << "lo que escribe en el header en el head del availist " << ss.str() << "con size: "<< ss.str().size() << endl;
	return ss.str();
}