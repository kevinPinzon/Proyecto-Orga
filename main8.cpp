/*
main8.cpp
este main carga la estructura, los registros y el availlist a memoria.
se puede hacer todas las operaciones del CRUD en este main 
*/

#include "Campo.h"
#include "Registro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "SpecialStack.h"

using namespace std;

int menu();
vector <Campo> cargarEstructura(ifstream&);
vector <Registro> cargarRegistros(ifstream&, vector<Campo>, int, int);//file de lectura, estructura, offsetRegistros y cantDeRegistros que se quiere cargar
string toStringArchivoD1RD(int);//devuelve la cadena que marca el registro que se va a borrar
string toStringArchivoHeadAvailist(int);//devuelve la posicion head del availist en cadena para escribirla en header

int main (int argc, char* argv[]){
	Campo field;
	Registro registro;
	int cantDeCampos, offsetRegistros, sizeRegistro;
	vector <Campo> estructura;
	vector <Registro> registros;
	SpecialStack availlist;

	ifstream file;//abrimos el archivo para lectura 
	file.open("memestest2.txt", ios::in | ios::out);

	if (file.is_open()){

		estructura = cargarEstructura(file);//se cargó la estructura

		cantDeCampos = estructura.size();
		offsetRegistros = file.tellg();//tomamos el offset de donde termina el header y empiezan los registros
		registro.setiarValor0(cantDeCampos);
		sizeRegistro = registro.toStringArchivo(estructura).size();//tomamos la longitud de un registro de olongitud fija (ARLF)
		registro.clear();

		registros = cargarRegistros(file, estructura, offsetRegistros, 10);//último parámetro es la cantidad de registros que se quiere cargar

		availlist.inicializar(file, offsetRegistros, sizeRegistro);

		file.close();//cierra el flujo de lectura

	} else {
		cerr << "ERROR: no se pudo abrir el file para lectura." << endl;
	}
/*
---------------------------------------------------------------------------------------------------------------------
TODO LO QUE SE HACE EN ESTE MAIN ARRIBA DE ESTE PUNTO ES ESCENCIAL
QUE ES CARGAR LA ESTRUCTURA, ALGUNOS REGISTROS Y EL AVAILLIST
una vez que ya tenemos todo eso listo podemos seguir con las operaciones del CRUD
y abirmos un flujo de escritura para el mismo archivo
*/
	ofstream archivo;
	archivo.open("memestest2.txt", ios::in | ios::out);

	if (archivo.is_open()){
		int opcion = menu();
		while (opcion != 0){
			switch (opcion){
				case 1:{//agregar un registro nuevo
					registro.clear();//limpio el registro temporal para recibir el nuevo registro
					string datoEntrada;
					for (int i =0; i< cantDeCampos; i++){
						cout << "Ingrese " << estructura.at(i).getName() << ":" << endl;
						cin >> datoEntrada;
						registro.agregarDato(datoEntrada);
					}//una vez que ya tengo el nuevo registro completo lo agrego al vector y lo escribo en el archivo

					int sigPosDisponibleArchivo = availlist.peek();//revisa en el availlist si hay una posción disponible
					if (sigPosDisponibleArchivo == -1){//el availlist esta vacio y se debe agregar al final del archivo

						archivo.seekp(offsetRegistros+(sizeRegistro*(registros.size())));//me coloco en el final del archivo, como si fuera append
						registro.Escribir(archivo, estructura);
						registros.push_back(registro);

					} else {//el availlist no esta vacio y hay una posición disponible entre los registros

						int posAntes = availlist.buscarVIP(sigPosDisponibleArchivo) -1;//resto uno pq en la lista VIP esta el -1 del availlist
						int posVector = sigPosDisponibleArchivo-posAntes;
						availlist.pop();//hago pop hasta despues de buscarVIP pq si hago pop antes no voy a encontrar la posición ya que pop quita la posicion de l availlist y de la VIPList
						archivo.seekp(offsetRegistros + sigPosDisponibleArchivo * sizeRegistro);//me coloco en el archivo en la posición que salío del availlist
						registro.Escribir(archivo, estructura);

						archivo.seekp(4);//en mi archivo 4 es donde empieza el espacio designado para el head del availlist en el header
						archivo << toStringArchivoHeadAvailist(availlist.peek());//lamo al metodo que hace una cadena "0001"

						//posVecor es la posición en el vector de registros correspondiente a la posción del archivo donde escribí
						//el nuevo registro. ASI EL VECTOR DE REGISTROS ESTA ORDENADO IGUAL QUE LOS REGISTROS EN EL archivo
						if (posVector <= 0){
							registros.insert(registros.begin()+0, registro);
						} else {
							if (posVector >= registros.size()){
								registros.push_back(registro);
							} else {
								registros.insert(registros.begin()+posVector, registro);
							}
						}
					}
					registro.clear();//una vez que agregué correctamente el registro lo limpio
				}// fin del caso 1: agregar registro
				break;

				case 2:{//imprimir registros
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

				case 3:{//modificar un registro
					int pos;
					cout << "Ingrese posicion de registro que quiere modificar." <<endl;
					cin >> pos;
					pos--;
					if (!(pos <0 || pos>=registros.size())){

					} else {
						cout << "La poscion que ingreso para modificar es invalida." << endl;
					}
				}
				break;

				case 4:{//borrar un registro
					int pos;
					cout << "Ingrese la posicion del registro que quiere borrar." << endl;
					cin >> pos;
					pos--;//le bajo uno para que ya este en termino de i que usamos para los fors donde i=0
					if (!(pos <0 || pos>=registros.size())){
						if (!availlist.isEmpty()){
							int sigPosDisp = availlist.peek();//tomo la siguiente posición disponible del availist
							string alBorrado = toStringArchivoD1RD(sigPosDisp);
						//hago la cadena con la qu va a marcar el registro por borrar. la cadena incluye la posicion que le sigue en el availist.
						
							int posArchivo = availlist.posicionArchivo(pos);
						//en este paso hago la conversion de la posicion del vector de registros que quiere borrar a la posicion en archivo donde esta el registro que quiere borrar
							archivo.seekp(offsetRegistros+(sizeRegistro*posArchivo));//muevo el offset al comienzo del registro que quiero borrar
							archivo << alBorrado;//marco el registro para indicar que esta borrado y no debe ser incluido
							availlist.push(posArchivo);//actualizamos el availlist
							archivo.seekp(4);
							archivo << toStringArchivoHeadAvailist(posArchivo);//actualizo el header con la nueva posicion head de availlist
							registros.erase(registros.begin()+pos);//borro el registro del vector de registros

						} else {
							cout << "El availliste esta vacio en borrar registro." << endl; 
						}
					} else {
						cout << "La poscion que ingreso para borrar es invalida." << endl;
					}
				}
				break;

				default:{}
				break;
			}
			opcion = menu();
		}// fin del while(opcion!=0)
		archivo.close();
	} else {
		cerr << "ERROR: no se pudo abrir el archivo para escritura. " << endl;
	}

	return 0; 
}// fin main 

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

vector <Campo> cargarEstructura (ifstream& file){
	vector <Campo> estructura;
	Campo field;
	char str[100];
	string linea, sublinea;
	int pos1=0, pos2, cantDeCampos;
	if (file.is_open()){
		file.clear();
		file.seekg(0, ios::beg);//setea el offset al comienzo del archivo
		file.getline(str, 20, ';');
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

vector <Registro> cargarRegistros(ifstream& file, vector<Campo> estructura, int offsetRegistros, int cantDeRegistros){
	/*
	cantDeRegistros es el numero de registros por cargar
	-->> se debe hacer una modificacion para que reciba un vector de registros de los que ya estan cargados en memoria y 
	-->> le agregue una cantidad de registros mas del disco
	*/
	vector <Registro> registros;
	Registro registroTemp;
	int i=0; 
	if (file.is_open()){
		file.clear();
		file.seekg(offsetRegistros, ios::beg);//coloca el offset después, del header, donde empiezan los registros.
		while (i<cantDeRegistros && registroTemp.Leer(file, estructura)){
			if (registroTemp.esValido())
				registros.push_back(registroTemp);
			registroTemp.clear();
			i++;
		}
	}
	return registros;
}

string toStringArchivoD1RD(int pos){//to string Archivo de un registro disponible
//devuelve la cadena que marca un registro que se va a borrar
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