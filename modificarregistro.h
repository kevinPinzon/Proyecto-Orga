#ifndef MODIFICARREGISTRO_H
#define MODIFICARREGISTRO_H

#include <QDialog>

namespace Ui {
class modificarRegistro;
}

class modificarRegistro : public QDialog
{
    Q_OBJECT

public:
    explicit modificarRegistro(int pos,QWidget *parent = 0);
    ~modificarRegistro();
    int pos;

private slots:
    void on_btn_modifRegistro_clicked();

    void on_btn_cerrar_clicked();

private:
    Ui::modificarRegistro *ui;
};

#endif // MODIFICARREGISTRO_H
