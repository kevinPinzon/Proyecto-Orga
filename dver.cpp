#include "dver.h"
#include "campo.h"
#include "ui_dver.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>
#include<QStandardItemModel>

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
    /*Registro r;
    r.agregarDato("kevin");
    r.agregarDato("22");
    r.agregarDato("0801");
    r.agregarDato("05");
    cout<<r.getDatos().size()<<endl;
    tabla->setRowCount(tabla->rowCount());
    for(int i=0; i<r.getDatos().size(); i++){
        string cadenaTemp=r.getDatos().at(i);
        cout<<cadenaTemp<<endl;
        tabla->setItem(tabla->rowCount()-1,i,new QTableWidgetItem(cadenaTemp.data()));
    }
*/
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
                        pos= i;  // Solo subes quando encuentra el primer caracter, y por eso
                     i++; // es igual a i = i + 1
                }
            }
        }
    }
}

void Dver::on_btn_agregarRegistro_clicked(){
    QTableWidgetItem *itemTemp;
    cout<<"columas: "<<ui->tw_registros->columnCount()<<endl;
    for(int j=0; j<ui->tw_registros->columnCount(); j++){
        itemTemp = ui->tw_registros->item(ui->tw_registros->rowCount()-1,j);
        registro.agregarDato(itemTemp->text().toStdString());
    }
    fileESCRIBIR.open(path.toStdString().c_str(), ios::in | ios::out | ios::app);
        if (fileESCRIBIR.is_open()){
            //aqui deberiamos de escribir todo un vector de registros
            registro.Escribir(fileESCRIBIR, estructura);
        }
    ui->tw_registros->setRowCount(ui->tw_registros->rowCount()+1);

}

void Dver::on_tw_registros_itemClicked(QTableWidgetItem *item){
    row = item->row();

}

void Dver::on_pushButton_2_clicked(){
    cout<<"Registro tiene: "<<endl;
    for(int i=0; i<registro.getDatos().size(); i++){
        string temp=registro.getDatos().at(i);
        cout<<temp<<endl;
    }

    fileLEER.close();
    fileESCRIBIR.close();
    this->close();

}
