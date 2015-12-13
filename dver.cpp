#include "dver.h"
#include "campo.h"
#include "ui_dver.h"
#include <sstream>
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
<<<<<<< HEAD
=======
#include <QFileDialog>
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
#include<QStandardItemModel>
#include <QMessageBox>
#include"operacionescampos.h"
#include"agregarregistro.h"
<<<<<<< HEAD
=======
#include"modificarregistro.h"
#include "specialstack.h"
#include"eliminarregistro.h"
#include"cruzar.h"
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

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
<<<<<<< HEAD
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    if(fileLEER.is_open()){
        fileLEER.getline(str, 20, ',');
        cantDeCampos = atoi(str);
        for (int i = 0; i < cantDeCampos; i++){
            fileLEER >> field;
            estructura.push_back(field);
       }
=======
    char str[100];
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    string linea, sublinea;
    int pos1=0, pos2, cantDeCampos;
    Campo field;
    if(fileLEER.is_open()){
        fileLEER.clear();
        fileLEER.getline(str, 30, ';');
        linea = str;
        pos2 = linea.find(',', 0);
        sublinea = linea.substr(pos1, pos2-pos1);
        cantDeCampos = atoi(sublinea.c_str());
        for (int i = 0; i < cantDeCampos; i++){
            fileLEER >> field;
            estructura.push_back(field);
       // cout<<"CAMPO: "<<i<<" : "<<field.getName()<<endl;
       }
    for(int i=0; i<estructura.size(); i++)
        cout<<"CAMPO: "<<i<<" : "<<estructura.at(i).getName()<<endl;

>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
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
<<<<<<< HEAD
=======
        cout<<"ENCABEZADOS: "<<tempCadena<<endl;
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
        QString str(tempCadena.c_str());
        encabezados.append(str);
    }
    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);
<<<<<<< HEAD
/*    registro.Leer(fileLEER,estructura);
    contRegistros=registro.getDatos().size();
    if(registro.getDatos().size()>10){
        for(unsigned int i=0; i<10; i++){
            string cadenaTemp=registro.getDatos().at(i);
            cout<<cadenaTemp<<endl;
            ui->tw_registros->setItem(ui->tw_registros->rowCount(),i,new QTableWidgetItem(cadenaTemp.data()));
        }
    }else{
        for(int i=0; i<registro.getDatos().size(); i++){
            string cadenaTemp=registro.getDatos().at(i);
            cout<<cadenaTemp<<endl;
            ui->tw_registros->setItem(ui->tw_registros->rowCount(),i,new QTableWidgetItem(cadenaTemp.data()));
        }
    }
    tabla->setRowCount(tabla->rowCount()+1);
*/
    ui->tw_registros->setEnabled(false);
=======

    offsetRegistros = fileLEER.tellg();//tomamos el offset de donde empiezan los registros!!
    cout<<"offset registro, tellg: "<<offsetRegistros<<endl;
    registro.setiarValor0(estructura.size());
    sizeRegistro = registro.toStringArchivo(estructura).size();//tomamos la longitud de un registro de olongitud fija (ARLF)
    registro.clear();
    cout << "Size de un registro de tamaño fijo: " << sizeRegistro << endl;
    availlist.setSizeRegistro(sizeRegistro);
    availlist.setOffsetRegistro(offsetRegistros);//WATCH OUT!!!!!!!!!!!!!!!!!!!!!!!!
    cout<<"segun el availlist, el offset de registro empieza: "<<availlist.getOffsetRegistro()<<endl;

    //SE CARGAN REGISTROS
    int contador=0;
    int cantDeCamposregistro=10;
    if(fileLEER.is_open()){
        fileLEER.clear();
        fileLEER.seekg(availlist.getOffsetRegistro(),ios::beg);
        while (contador<cantDeCamposregistro && registro.Leer(fileLEER, estructura)){
            if (registro.esValido())
                VRegistros.push_back(registro);
            registro.clear();
            contador++;
        }
        availlist.inicializar(fileLEER);
        cout<<"termino inicializar"<<endl;
        stringstream ss;
        ss<<"       "<<availlist.toString()<<"      ";
        QMessageBox::information(this," AvailList   ",ss.str().c_str());
      //  fileLEER.close();
   }else
        cerr<<"No se pudo abrir el archivo, para lectura de registros"<<endl;
    actualizarRegistro();
    tabla->setEnabled(false);
    fileLEER.close();
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
}


void Dver::on_btn_agregarRegistro_clicked(){
<<<<<<< HEAD
    //AQUI DEBERIAMOS LEER LOS REGISTROS DEL ARCHIVO
    //se debe leer y guardar cada registro en un registro temp y luego hacerle push al VRegistros
    //luego con el VRegistros llenar la tabla de registros

    AgregarRegistro add(path,estructura,this);
    add.exec();
    if(add.seAgrego){
        VRegistros.push_back(add.actualizarTabla());
        actualizarRegistro();
    }

=======
    cout<<"to string availlist: "<<availlist.toString()<<endl;
    AgregarRegistro add(availlist,path,estructura,VRegistros,this);
    add.exec();
    if(add.seAgrego){
        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
        if (fileESCRIBIR.is_open()){
            VRegistros=add.actualizarRegistro();
         //   fileESCRIBIR.seekp(offsetRegistros+(sizeRegistro*(VRegistros.size()-1)));
            actualizarRegistro();
        }else
            QMessageBox::warning(this,"ERROR","       No se ha podido abrir el archivo para escritura en dVer  ");

    }
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
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
<<<<<<< HEAD

}


=======
}

>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
void Dver::on_tw_registros_itemClicked(QTableWidgetItem *item){
    row = item->row();

}

void Dver::on_pushButton_2_clicked(){
    for(int i=0; i<registro.getDatos().size(); i++){
        string temp=registro.getDatos().at(i);
<<<<<<< HEAD
        cout<<temp<<endl;
    }

    fileLEER.close();
    fileESCRIBIR.close();
    this->close();

}

void Dver::on_pushButton_clicked(){
    contRegistros=contRegistros-10;
    if(contRegistros>0){
        for(int i=0; i<10; i++){
            string cadenaTemp=registro.getDatos().at(i);
            cout<<cadenaTemp<<endl;
            ui->tw_registros->setItem(ui->tw_registros->rowCount(),i,new QTableWidgetItem(cadenaTemp.data()));
        }
        ui->tw_registros->setRowCount(ui->tw_registros->rowCount()+1);
    }else{
        QMessageBox::information(this,"ERROR","No hay mas registros que mostrar");

    }
        //cout<<"ERROR: "<<endl<<"No hay mas registros que mostrar"<<endl;
=======
        cout<<temp<<"en push cerrar"<<endl;
    }
    fileLEER.close();
    fileESCRIBIR.close();
    this->close();
}

void Dver::on_pushButton_clicked(){
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

}

void Dver::on_btn_modificarRegistro_clicked(){
    QMessageBox::information(this,"En construccion","       ..............................  ");
}

void Dver::on_btn_eliminarRegistro_clicked(){
<<<<<<< HEAD
    QMessageBox::information(this,"En construccion","       ..............................  ");
}

void Dver::on_pushButton_3_clicked(){
    if(VRegistros.empty()){
        OperacionesCampos a(path,estructura,this);
        a.exec();
    }else
        QMessageBox::information(this,"ERROR","   No puede modificar o elimiar campos porque existen registros  ");

=======
    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out);
    eliminarRegistro elimRecord(availlist,estructura,VRegistros,path,this);
    elimRecord.exec();
    availlist=elimRecord.actualizarAvaillist();
    VRegistros=elimRecord.actualizarRegistros();
    actualizarRegistro();
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


void Dver::on_btn_cruzar_clicked(){
    try {
        QString path2(QFileDialog::getOpenFileName(this,tr("Abrir Archivo De Registro"), "./", tr("DAT Files (*.dat)")));
        QFile archivo(path2);
        if (!archivo.exists()){
            return;
        }
        if (archivo.isOpen()) {
            archivo.close();
        }
    Cruzar cruzar(estructura,VRegistros,path,path2,this);
    cruzar.exec();

    } catch (...) {

    }

}

void Dver::on_btn_operacionesCampos_clicked(){
    OperacionesCampos operacionesC(path,estructura,this);
    operacionesC.exec();
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
}
