#include "remover_produtos.h"
#include "ui_remover_produtos.h"
#include "banco_de_dados.h"
#include <QMessageBox>

remover_produtos::remover_produtos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::remover_produtos)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#484d54"));
    this->setPalette(palette);

}

remover_produtos::~remover_produtos()
{
    delete ui;
}

void remover_produtos::on_btn_remprod_estoque_clicked()
{
    int cod = ui->line_cod_remprod->text().toInt();
    int qtd = ui->line_cod_qtd->text().toInt();
    int numeracao = 0;

    if (ui->radio_33_34->isChecked()) {
        numeracao = 33;
    } else if (ui->radio_35_36->isChecked()) {
        numeracao = 35;
    } else if (ui->radio_37_38->isChecked()) {
        numeracao = 37;
    } else if (ui->radio_39_40->isChecked()) {
        numeracao = 39;
    } else if (ui->radio_41_42->isChecked()) {
        numeracao = 41;
    } else if (ui->radio_43_44->isChecked()) {
        numeracao = 43;
    }

    if (cod <= 0 || qtd <= 0 || numeracao == 0) {
        QMessageBox::warning(this, "Erro", "Código, quantidade e numeração devem ser válidos.");
        return;
    }

    if (banco_de_dados::remover_do_estoque(cod, qtd, numeracao)) {
        QMessageBox::information(this, "Sucesso", "Produto removido do estoque com sucesso.");
    } else {
        QMessageBox::warning(this, "Erro", "Erro ao remover produto. Verifique os dados e tente novamente.");
    }

    ui->line_cod_remprod->clear();
    ui->line_cod_qtd->clear();
    ui->radio_33_34->setChecked(false);
    ui->radio_35_36->setChecked(false);
    ui->radio_37_38->setChecked(false);
    ui->radio_39_40->setChecked(false);
    ui->radio_41_42->setChecked(false);
    ui->radio_43_44->setChecked(false);
}

