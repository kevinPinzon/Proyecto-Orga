#ifndef DVER_H
#define DVER_H

#include <QDialog>
#include "campo.h"
#include <QFile>
#include <vector>
#include"registro.h"
#include <QTableWidget>
<<<<<<< HEAD
=======
#include"specialstack.h"
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

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
<<<<<<< HEAD
    Campo field;
=======
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
    int cantDeCampos;
    vector <Campo> estructura;
    vector <Registro> VRegistros;
    Registro registro;
    QFile archivo;
    QString path;
    void llenarTabla();
    ifstream fileLEER;
    ofstream fileESCRIBIR;
    int row;
    int contRegistros;
    void actualizarRegistro();
<<<<<<< HEAD

=======
    int offsetRegistros, sizeRegistro;
    SpecialStack availlist; //declaración de availlist
    string toStringArchivoD1RD(int);
    vector <Campo>cargarHeader(ifstream&);
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
private slots:
    void on_pushButton_clicked();
    
    void on_btn_agregarRegistro_clicked();

    void on_tw_registros_itemClicked(QTableWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_btn_modificarRegistro_clicked();

    void on_btn_eliminarRegistro_clicked();

    void on_pushButton_3_clicked();

<<<<<<< HEAD
=======
    void on_btn_cruzar_clicked();

    void on_btn_operacionesCampos_clicked();

>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
private:
    Ui::Dver *ui;
};

#endif // DVER_H
