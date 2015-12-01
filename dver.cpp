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
    fileLEER.open(path.toStdString().c_str(), ios::in | ios::out);
    if(fileLEER.is_open()){
        fileLEER.getline(str, 20, ',');
        cantDeCampos = atoi(str);
        for (int i = 0; i < cantDeCampos; i++){
            fileLEER >> field;
            estructura.push_back(field);
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
        QString str(tempCadena.c_str());
        encabezados.append(str);
    }
    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);
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
}


void Dver::on_btn_agregarRegistro_clicked(){
    //AQUI DEBERIAMOS LEER LOS REGISTROS DEL ARCHIVO
    //se debe leer y guardar cada registro en un registro temp y luego hacerle push al VRegistros
    //luego con el VRegistros llenar la tabla de registros

    AgregarRegistro add(path,estructura,this);
    add.exec();
    if(add.seAgrego){
        VRegistros.push_back(add.actualizarTabla());
        actualizarRegistro();
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

}

void Dver::on_btn_modificarRegistro_clicked(){
    QMessageBox::information(this,"En construccion","       ..............................  ");
}

void Dver::on_btn_eliminarRegistro_clicked(){
    QMessageBox::information(this,"En construccion","       ..............................  ");
}

void Dver::on_pushButton_3_clicked(){
    if(VRegistros.empty()){
        OperacionesCampos a(path,estructura,this);
        a.exec();
    }else
        QMessageBox::information(this,"ERROR","   No puede modificar o elimiar campos porque existen registros  ");

}
