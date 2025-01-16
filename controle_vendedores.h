#ifndef CONTROLE_VENDEDORES_H
#define CONTROLE_VENDEDORES_H

#include <QDialog>

namespace Ui {
class controle_vendedores;
}

class controle_vendedores : public QDialog
{
    Q_OBJECT

public:
    explicit controle_vendedores(QWidget *parent = nullptr);
    ~controle_vendedores();

private slots:
    void on_btn_inserir_cod_convend_clicked();

private:
    Ui::controle_vendedores *ui;
    void carregarDadosVendedor(const QString &codigo);
};

#endif // CONTROLE_VENDEDORES_H
