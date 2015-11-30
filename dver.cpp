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

Dver::Dver(QString path,QWidget *parent):QDialog(parent),ui(new Ui::Dver){
    this->path = path;
    ui->setupUi(this);
    llenarTabla();
}
sdfdf

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
    /*Registro r;
    r.agregarDato("01");
    r.agregarDato("kevin");
    r.agregarDato("22");
    r.agregarDato("1.78");
    r.agregarDato("22359428");
    cout<<r.getDatos().size()<<endl;
    */
    //AQUI DEBERIAMOS LEER LOS REGISTROS DEL ARCHIVO
    //se debe leer y guardar cada registro en un registro temp y luego hacerle push al VRegistros
    //luego con el VRegistros llenar la tabla de registros
    registro.Leer(fileLEER,estructura);
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
}

void Dver::leerHeader(){
    archivo.setFileName(path);
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            QString str = in.readLine();
            string temp=str.toStdString();
            cout<<temp<<endl;
            int pos=-1;
            for (int i=0;i<temp.size();i++){
                while (temp[i] != '\t' ){
                    if ( temp[i] == '-' )
                        pos= i;  // Solo subes cuando encuentra el primer caracter, y por eso
                     i++; // es igual a i = i + 1
                }
            }
        }
    }
}

void Dver::on_btn_agregarRegistro_clicked(){
    QTableWidgetItem *itemTemp;
    //VALIDAR QUE LA ULTIMA FILA TENGA DATOS Y SEAN LOS CORRECTOS
    /*for(int j=0; j<ui->tw_registros->columnCount(); j++){
        itemTemp = ui->tw_registros->item(ui->tw_registros->rowCount()-1,j);
        registro.agregarDato(itemTemp->text().toStdString());
    }
    */if (fileESCRIBIR.is_open()){
            //aqui deberiamos de escribir todo un vector de registros
            registro.Escribir(fileESCRIBIR, estructura);
        }
    else{
        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out | ios::app);
        if (fileESCRIBIR.is_open()){
                //aqui deberiamos de escribir todo un vector de registros
                registro.Escribir(fileESCRIBIR, estructura);
            }
    }
    ui->tw_registros->setRowCount(ui->tw_registros->rowCount()+1);
    stringstream tempCad;
    tempCad<<"  El nuevo registro es el  #"<<registro.getDatos().size()<<"   ";
    QMessageBox::information(this," Registro agregado    ",tempCad.str().c_str());
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
    //Validar que no existan registros
    Registro a;
    VRegistros.push_back(a);
    if(VRegistros.size()!=0){

    }else{
        QMessageBox::information(this,"ERROR"," No Puede modificar los campos, porque existen registros");
    }

}
