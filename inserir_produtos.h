#ifndef INSERIR_PRODUTOS_H
#define INSERIR_PRODUTOS_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class inserir_produtos;
}

class inserir_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit inserir_produtos(QWidget *parent = nullptr);
    ~inserir_produtos();

private slots:
    void on_btn_insere_estoque_clicked();

private:
    Ui::inserir_produtos *ui;
};

#endif // INSERIR_PRODUTOS_H
