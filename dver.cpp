#include "dver.h"
#include "campo.h"
#include "ui_dver.h"
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>
#include <QMessageBox>
#include"operacionescampos.h"
#include"agregarregistro.h"
#include"modificarregistro.h"
#include "specialstack.h"
#include"eliminarregistro.h"

Dver::Dver(QString path,QWidget *parent):QDialog(parent),ui(new Ui::Dver){
    this->path = path;
    ui->setupUi(this);
    llenarTabla();
}

Dver::~Dver()
{
    delete ui;
}
void Dver::llenarTabla(){
    char str[80];
    string linea,sublinea;
    int pos1;
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    if(fileLEER.is_open()){
        fileLEER.getline(str, 20, ',');
        cantDeCampos = atoi(str);
        fileLEER.getline(str, 20, ';');
        for (int i = 0; i < cantDeCampos; i++){
            fileLEER >> field;
            estructura.push_back(field);
        cout<<"CAMPO: "<<i<<" : "<<field.getName()<<endl;
       }
    for(int i=0; i<estructura.size(); i++){
        cout<<"CAMPO: "<<i<<" : "<<estructura.at(i).getName()<<endl;
    }
    } else
        cerr << "No se abrio el archivo para leer en tabla"<<endl;
    QTableWidget* tabla=ui->tw_registros;
    do{
        tabla->removeRow(0);
    }while(tabla->rowCount());
    QStringList encabezados;
    Campo temp;
    string tempCadena;
    int posTemp;
    for (int cont = 0; cont < estructura.size(); ++cont) {
        temp=estructura.at(cont);
        tempCadena=temp.getName();
        posTemp=tempCadena.find('-');
        tempCadena=tempCadena.substr(0,posTemp);
        cout<<"ENCABEZADOS: "<<tempCadena<<endl;
        QString str(tempCadena.c_str());
        encabezados.append(str);
    }
    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);

    offsetRegistros = fileLEER.tellg();//tomamos el offset de donde empiezan los registros!!
    registro.setiarValor0(estructura.size());
    sizeRegistro = registro.toStringArchivo(estructura).size();//tomamos la longitud de un registro de olongitud fija (ARLF)
    registro.clear();
    int i;
    cout << "Size de un registro de tamaño fijo: " << sizeRegistro << endl;
    availlist.setSizeRegistro(sizeRegistro);
    availlist.setOffsetRegistro(offsetRegistros-sizeRegistro);//WATCH OUT!!!!!!!!!!!!!!!!!!!!!!!!
    cout<<"segun el availlist, el offset de registro empieza: "<<availlist.getOffsetRegistro()<<endl;

    if(fileLEER.is_open()){
        cout<<"abrio el archivo para lectura"<<endl;
        while (registro.Leer(fileLEER, estructura,cantDeCampos)){
            cout<<" vuelta: "<<i<<endl;
            VRegistros.push_back(registro);
            registro.clear();
            i++;
        }
        fileLEER.clear();
        fileLEER.seekg(0, ios::beg);
        cout << "Cargando el availist Offset en: " << fileLEER.tellg() << endl;
        fileLEER.getline(str, 20, ';');
        linea = str;
        cout << "Cargando el availist: " << linea << endl;
        pos1 = linea.find(',', 0);
        pos1++;
        sublinea = linea.substr(pos1, linea.size()-pos1);
        cout << sublinea << endl;
        availlist.inicializar(fileLEER, atoi(sublinea.c_str()), offsetRegistros, sizeRegistro);
        cout<<"termino inicializar"<<endl;
        stringstream ss;
        ss<<"       "<<availlist.toString()<<"      ";
        QMessageBox::information(this," AvailList   ",ss.str().c_str());
   }else
        cerr<<"No se pudo abrir el archivo, para lectura de registros"<<endl;
    actualizarRegistro();
    tabla->setEnabled(false);
//    fileLEER.close();
}


void Dver::on_btn_agregarRegistro_clicked(){
    AgregarRegistro add(availlist,path,estructura,VRegistros,this);
    add.exec();
    if(add.seAgrego){
        if (fileESCRIBIR.is_open()){
            VRegistros.push_back(add.actualizarTabla());
            fileESCRIBIR.seekp(offsetRegistros+(sizeRegistro*(VRegistros.size()-1)));
            actualizarRegistro();
        }else{
            fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
            if (fileESCRIBIR.is_open()){
                VRegistros.push_back(add.actualizarTabla());
                fileESCRIBIR.seekp(offsetRegistros+(sizeRegistro*(VRegistros.size()-1)));
                actualizarRegistro();
            }else
                QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura  ");
        }
    }
}

void Dver::actualizarRegistro(){
    int contRegistros = VRegistros.size();
    ui->tw_registros->setRowCount(contRegistros);
    Registro registroTemp;
    string cadenaTemp;
    for(int i=0; i<VRegistros.size(); i++){
        registroTemp=VRegistros.at(i);
        for(int columnas=0; columnas<ui->tw_registros->columnCount(); columnas++){
            cadenaTemp=registroTemp.getDatos().at(columnas);
            ui->tw_registros->setItem(i,columnas,new QTableWidgetItem(cadenaTemp.data()));
        }
    }

}


void Dver::on_tw_registros_itemClicked(QTableWidgetItem *item){
    row = item->row();

}

void Dver::on_pushButton_2_clicked(){
    for(int i=0; i<registro.getDatos().size(); i++){
        string temp=registro.getDatos().at(i);
        cout<<temp<<endl;
    }

    fileLEER.close();
    fileESCRIBIR.close();
    this->close();

}

void Dver::on_pushButton_clicked(){
   /* if(contRegistros>0){
        for(int i=0; i<10; i++){
            string cadenaTemp=registro.getDatos().at(i);
            //cout<<cadenaTemp<<endl;
            ui->tw_registros->setItem(ui->tw_registros->rowCount(),i,new QTableWidgetItem(cadenaTemp.data()));
        }
        ui->tw_registros->setRowCount(ui->tw_registros->rowCount()+1);
        contRegistros=contRegistros-10;
    }else{
        QMessageBox::information(this,"ERROR","No hay mas registros que mostrar");

    }
    */
}

void Dver::on_btn_modificarRegistro_clicked(){
    QMessageBox::information(this,"En construccion","       ..............................  ");
}

void Dver::on_btn_eliminarRegistro_clicked(){
    eliminarRegistro elimRecord(availlist,estructura,VRegistros,path,this);
    elimRecord.exec();
    VRegistros=elimRecord.actualizarRegistros();
    actualizarRegistro();

}

void Dver::on_pushButton_3_clicked(){
    if(VRegistros.empty()){
        OperacionesCampos a(path,estructura,this);
        a.exec();
    }else
        QMessageBox::warning(this,"ERROR","   No puede modificar o elimiar campos porque existen registros  ");

}

vector <Campo> Dver::cargarHeader (ifstream& file){
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

