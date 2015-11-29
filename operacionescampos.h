#ifndef OPERACIONESCAMPOS_H
#define OPERACIONESCAMPOS_H

#include <QDialog>

namespace Ui {
class OperacionesCampos;
}

class OperacionesCampos : public QDialog
{
    Q_OBJECT

public:
    explicit OperacionesCampos(QWidget *parent = 0);
    ~OperacionesCampos();

private:
    Ui::OperacionesCampos *ui;
};

#endif // OPERACIONESCAMPOS_H
