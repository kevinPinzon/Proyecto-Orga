#ifndef MODIFICARREGISTRO_H
#define MODIFICARREGISTRO_H

#include <QDialog>
#include"registro.h"
#include<vector>
#include"specialstack.h"

using std::vector;


namespace Ui {

class modificarRegistro;
}

class modificarRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit modificarRegistro(SpecialStack,vector<Registro>,vector<Campo>,QString,QWidget *parent = 0);
    ~modificarRegistro();
    vector<Registro> VRegistros;
    vector<Campo> estructura;
    QString path;
    ofstream fileESCRIBIR;//para marcar el registro y escribir el ultimo rrn
    ifstream fileLEER;//para escribir en el header el rrn del registro borrado
    int RRNaModificar;
    vector<Registro> actualizarRegistros();
    void hacerTabla();
    Registro registro;
    SpecialStack availlist;

private slots:
    void on_btn_modifRegistro_clicked();

    void on_btn_cerrar_clicked();

    void on_btn_visualizar_clicked();

private:
    Ui::modificarRegistro *ui;
};

#endif // MODIFICARREGISTRO_H
