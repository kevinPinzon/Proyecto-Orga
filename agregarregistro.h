#ifndef AGREGARREGISTRO_H
#define AGREGARREGISTRO_H
#include "campo.h"
#include"registro.h"
#include<vector>
#include"specialstack.h"
#include <QDialog>

using std::vector;


namespace Ui {
class AgregarRegistro;
}

class AgregarRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarRegistro(SpecialStack, QString ,vector<Campo>,vector<Registro>, QWidget *parent = 0);
    ~AgregarRegistro();
    vector<Registro> VRegistros;
    vector<Campo> estructura;
    Registro registro;
    ofstream fileESCRIBIR;
    ifstream fileLEER;
    QString path;
    void hacerTabla();
<<<<<<< HEAD
    Registro actualizarTabla();
=======
    vector<Registro> actualizarRegistro();
>>>>>>> 5fd0c51c169a14e15dc98375627feb975be184c8
    bool seAgrego=false;
    SpecialStack availlist;
private slots:
    void on_btn_agregarRegi_clicked();


    void on_btn_cerrar_clicked();

private:
    Ui::AgregarRegistro *ui;
};

#endif // AGREGARREGISTRO_H
