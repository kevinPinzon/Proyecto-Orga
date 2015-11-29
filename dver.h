#ifndef DVER_H
#define DVER_H

#include <QDialog>
#include "campo.h"
#include <QFile>
#include <vector>
#include"registro.h"
#include <QTableWidget>

using std::vector;

namespace Ui {
class Dver;
}

class Dver : public QDialog
{
    Q_OBJECT

public:
    explicit Dver(QString path,QWidget *parent = 0);
    ~Dver();
    void leerHeader();
    char str[80];
    Campo field;
    int cantDeCampos;
    vector <Campo> estructura;
    QFile archivo;
    QString path;
    void llenarTabla();
    Registro registro;
    ifstream fileLEER;
    ofstream fileESCRIBIR;
    int row;
    int contRegistros;
private slots:
    void on_pushButton_clicked();
    
    void on_btn_agregarRegistro_clicked();

    void on_tw_registros_itemClicked(QTableWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_btn_modificarRegistro_clicked();

    void on_btn_eliminarRegistro_clicked();

private:
    Ui::Dver *ui;
};

#endif // DVER_H
