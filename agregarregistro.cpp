#include "agregarregistro.h"
#include "ui_agregarregistro.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>

#include "campo.h"
#include"registro.h"

AgregarRegistro::AgregarRegistro(QString path,vector<Campo> estructura,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgregarRegistro)
{
    ui->setupUi(this);
    this->path=path;
    this->estructura=estructura;
    hacerTabla();
}

void AgregarRegistro::hacerTabla(){
    QTableWidget* tabla=ui->tw_registroAdd;
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
    ui->tw_registroAdd->setRowCount(ui->tw_registroAdd->rowCount()+1);

}

Registro AgregarRegistro::actualizarTabla(){
    return registro;
}

AgregarRegistro::~AgregarRegistro()
{
    delete ui;
}

void AgregarRegistro::on_btn_agregarRegi_clicked(){
    QTableWidgetItem *itemTemp;
    for(int j=0; j<ui->tw_registroAdd->columnCount(); j++){
        itemTemp = ui->tw_registroAdd->item(ui->tw_registroAdd->rowCount()-1,j);
        registro.agregarDato(itemTemp->text().toStdString());
    }
    if (fileESCRIBIR.is_open()){
            registro.Escribir(fileESCRIBIR, estructura);
            actualizarTabla();
        }
    else{
        fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out | ios::app);
        if (fileESCRIBIR.is_open()){
                registro.Escribir(fileESCRIBIR, estructura);
                actualizarTabla();
            }
    }
    seAgrego=true;
    this->close();
}


void AgregarRegistro::on_btn_cerrar_clicked(){
    if (fileESCRIBIR.is_open())
        fileESCRIBIR.close();
    seAgrego=false;
    this->close();
}
