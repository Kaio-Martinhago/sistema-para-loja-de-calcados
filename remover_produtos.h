#ifndef REMOVER_PRODUTOS_H
#define REMOVER_PRODUTOS_H

#include <QDialog>

namespace Ui {
class remover_produtos;
}

class remover_produtos : public QDialog
{
    Q_OBJECT

public:
    explicit remover_produtos(QWidget *parent = nullptr);
    ~remover_produtos();

private slots:
    void on_btn_remprod_estoque_clicked();

private:
    Ui::remover_produtos *ui;
};

#endif // REMOVER_PRODUTOS_H
