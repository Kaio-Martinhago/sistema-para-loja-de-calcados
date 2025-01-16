#ifndef CONTROLE_VENDAS_H
#define CONTROLE_VENDAS_H

#include <QDialog>

namespace Ui {
class controle_vendas;
}

class controle_vendas : public QDialog
{
    Q_OBJECT

public:
    explicit controle_vendas(QWidget *parent = nullptr);
    ~controle_vendas();

private:
    Ui::controle_vendas *ui;
};

#endif // CONTROLE_VENDAS_H
