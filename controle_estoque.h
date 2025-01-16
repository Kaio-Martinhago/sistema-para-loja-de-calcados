#ifndef CONTROLE_ESTOQUE_H
#define CONTROLE_ESTOQUE_H

#include <QDialog>

namespace Ui {
class controle_estoque;
}

class controle_estoque : public QDialog
{
    Q_OBJECT

public:
    explicit controle_estoque(QWidget *parent = nullptr);
    ~controle_estoque();

private slots:

    void on_btn_filtrar_clicked();

private:
    Ui::controle_estoque *ui;
    void preencherTabela(const QString &codigo = "", const QString &quantidade = "", const QString &numeracao = "");
};

#endif // CONTROLE_ESTOQUE_H
