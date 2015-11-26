#ifndef DVER_H
#define DVER_H

#include <QDialog>
#include "campo.h"
#include <QFile>
#include <vector>

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

private:
    Ui::Dver *ui;
    void llenarTablaRegistro();
    QString path;
    QFile archivo;
    vector<Campo*> campos;
};

#endif // DVER_H
