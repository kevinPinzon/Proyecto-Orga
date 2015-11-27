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
            int pos = linea.find(',');
            file.seekg(pos);
            file >> field;

            cout<<field.getName()<<"  -ahi esta el name"<<endl;
            estructura.push_back(field);

        }
    }
    QTableWidget* tabla=ui->tw_registros;
    do{
        tabla->removeRow(0);
    }while(tabla->rowCount());
    QStringList encabezados;
    Campo temp;
    cout<<"size estructura: "<<estructura.size()<<endl;
    for (int cont = 0; cont < estructura.size(); ++cont) {
        temp=estructura.at(cont);
        QString str(temp.getName());
        encabezados.append(str);
        cout<<temp.getName()<<"  ahi esta el nombre"<<endl;
    }

    tabla->setColumnCount(estructura.size());
    tabla->setHorizontalHeaderLabels(encabezados);


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
