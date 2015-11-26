#include "dver.h"
#include "ui_dver.h"
#include <QFile>
#include <QTextStream>

Dver::Dver(QString path,QWidget *parent):QDialog(parent),ui(new Ui::Dver){
    this->path = path;
    ui->setupUi(this);
    leerHeader();
}

Dver::~Dver()
{
    delete ui;
}
void Dver::llenarTablaRegistro(){

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
