#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class principal;
}
QT_END_NAMESPACE

class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal(QWidget *parent = nullptr);
    ~principal();

private slots:
    void on_actionNovo_Produto_triggered();

    void on_actionNovo_Vendedor_triggered();

    void on_actionNovo_Cliente_triggered();

    void on_actionInserir_produtos_triggered();

    void on_actionRemover_Produtos_triggered();

    void on_actionVendedores_2_triggered();

    void on_actionVendas_triggered();

    void on_actionConsulta_de_Estoque_triggered();

    void on_btn_insere_cod_clicked();

    void atualizarTotalEQuantidade();

    void updateParcelas();

    void on_radio_dinheiro_toggled(bool checked);

    void on_radio_cdebito_toggled(bool checked);

    void on_radio_ccredito_toggled(bool checked);

    void atualizarDesconto(int percDesconto);

    void atualizarParcelasComDesconto(double valorFinal);

    void on_btn_finalizar_clicked();

    double getTotalComprasCliente(const QString& cpf);

    double getTotalVendasVendedor(const QString& cod);

    void atualizarTotalVendasVendedor(const QString& cod, double novoTotal);

    void atualizarTotalComprasCliente(const QString& cpf, double novoTotal);

private:
    Ui::principal *ui;
};
#endif // PRINCIPAL_H
