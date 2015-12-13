#ifndef AGREGARREGISTRO_H
#define AGREGARREGISTRO_H
#include "campo.h"
#include"registro.h"
#include<vector>
<<<<<<< HEAD
using std::vector;

#include <QDialog>
=======
#include"specialstack.h"
#include <QDialog>

using std::vector;

>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8

namespace Ui {
class AgregarRegistro;
}

class AgregarRegistro : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit AgregarRegistro(QString path,vector<Campo> , QWidget *parent = 0);
    ~AgregarRegistro();
    vector<Campo> estructura;
    Registro registro;
    ofstream fileESCRIBIR;
    QString path;
    void hacerTabla();
    Registro actualizarTabla();
    bool seAgrego=false;

=======
    explicit AgregarRegistro(SpecialStack, QString ,vector<Campo>,vector<Registro>, QWidget *parent = 0);
    ~AgregarRegistro();
    vector<Registro> VRegistros;
    vector<Campo> estructura;
    Registro registro;
    ofstream fileESCRIBIR;
    ifstream fileLEER;
    QString path;
    void hacerTabla();
    vector<Registro> actualizarRegistro();
    bool seAgrego=false;
    SpecialStack availlist;
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
private slots:
    void on_btn_agregarRegi_clicked();


    void on_btn_cerrar_clicked();

private:
    Ui::AgregarRegistro *ui;
};

#endif // AGREGARREGISTRO_H
