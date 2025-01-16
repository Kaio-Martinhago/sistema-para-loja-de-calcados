#ifndef CADASTRO_CLIENTE_H
#define CADASTRO_CLIENTE_H

#include <QDialog>

namespace Ui {
class cadastro_cliente;
}

class cadastro_cliente : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro_cliente(QWidget *parent = nullptr);
    ~cadastro_cliente();

private slots:
    void on_btn_cadastrar_cliente_clicked();

private:
    Ui::cadastro_cliente *ui;
};

#endif // CADASTRO_CLIENTE_H
