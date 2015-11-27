#include "dver.h"
#include "campo.h"
#include "ui_dver.h"
#include <QFile>
#include <QTextStream>
#include <QTableWidget>
#include <QInputDialog>
#include <QDebug>

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
    ifstream file;
    file.open(path.toStdString().c_str(), ios::in | ios::out);
    if(file.is_open()){
        file.getline(str, 20, ',');
        cantDeCampos = atoi(str);

        for (int i = 0; i < cantDeCampos; i++){
            string linea=str;
            cout<<"STR: "<<str<<endl;
            int pos = linea.find(',');
            file.seekg(pos);
            file >> field;
            cout<<field.toString()<<endl;
            cout<<field.getName()<<"  -ahi esta el name"<<endl;
            estructura.push_back(field);

        }
    }
    QTableWidget* tabla=tabla=ui->tw_registros;
    do{
        tabla->removeRow(0);
    }while(tabla->rowCount());
    QStringList encabezados;
    Campo temp;
    string tempCadena;
    int posTemp;
    cout<<"size estructura: "<<estructura.size()<<endl;
    for (int cont = 0; cont < estructura.size(); ++cont) {
        temp=estructura.at(cont);
        tempCadena=temp.getName();
        //tempCadena="nombre------";
        posTemp=tempCadena.find('-');
        tempCadena=tempCadena.substr(0,posTemp);
        QString str(tempCadena.c_str());
        encabezados.append(str);
        cout<<temp.getName()<<"  ahi esta el nombre"<<endl;
    }


    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);
    tabla->setRowCount(1);


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

//cerrar archivo

void Dver::on_btn_agregarRegistro_clicked(){


}

void Dver::on_tw_registros_itemClicked(QTableWidgetItem *item){
    int row = item->row();
    //string dato=
    //cout<<dato<<endl;
    QTableWidget* tabla=ui->tw_registros;

    //registro.agregarDato();

}
