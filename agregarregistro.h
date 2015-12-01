#ifndef AGREGARREGISTRO_H
#define AGREGARREGISTRO_H
#include "campo.h"
#include"registro.h"
#include<vector>
using std::vector;

#include <QDialog>

namespace Ui {
class AgregarRegistro;
}

class AgregarRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarRegistro(QString path,vector<Campo> , QWidget *parent = 0);
    ~AgregarRegistro();
    vector<Campo> estructura;
    Registro registro;
    ofstream fileESCRIBIR;
    QString path;
    void hacerTabla();
    Registro actualizarTabla();
    bool seAgrego=false;

private slots:
    void on_btn_agregarRegi_clicked();


    void on_btn_cerrar_clicked();

private:
    Ui::AgregarRegistro *ui;
};

#endif // AGREGARREGISTRO_H
