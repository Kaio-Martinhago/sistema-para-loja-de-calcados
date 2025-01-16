#include "inserir_produtos.h"
#include "ui_inserir_produtos.h"
#include "banco_de_dados.h"
#include <QMessageBox>

inserir_produtos::inserir_produtos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::inserir_produtos)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#484d54"));
    this->setPalette(palette);
}

inserir_produtos::~inserir_produtos()
{
    delete ui;
}

void inserir_produtos::on_btn_insere_estoque_clicked() {
    int cod = ui->line_cod_inserprod->text().toInt();
    int quantidade = ui->line_qtdpares_inseprod->text().toInt();
    int numeracao = -1;

    if (!banco_de_dados::verificar_codigo_existente(cod)) {
        QMessageBox::warning(this, "Erro", "Código do produto não existe. Cadastre o produto antes de inserir no estoque.");
        return;
    }

    // Identifica qual radio button foi selecionado
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

    if (numeracao == -1) {
        QMessageBox::warning(this, "Erro", "Selecione uma numeração antes de inserir no estoque.");
        return;
    }

    if (quantidade <= 0) {
        QMessageBox::warning(this, "Erro", "A quantidade deve ser maior que zero.");
        return;
    }

    if (banco_de_dados::inserir_estoque(QString::number(cod), quantidade, numeracao)) {
        QMessageBox::information(this, "Sucesso", "Estoque inserido com sucesso.");
    } else {
        QMessageBox::warning(this, "Erro", "Não foi possível inserir no estoque.");
    }

    ui->line_qtdpares_inseprod->clear();
    ui->line_qtdpares_inseprod->setFocus();

    ui->radio_33_34->setAutoExclusive(false);
    ui->radio_35_36->setAutoExclusive(false);
    ui->radio_37_38->setAutoExclusive(false);
    ui->radio_39_40->setAutoExclusive(false);
    ui->radio_41_42->setAutoExclusive(false);
    ui->radio_43_44->setAutoExclusive(false);
    ui->radio_33_34->setChecked(false);
    ui->radio_35_36->setChecked(false);
    ui->radio_37_38->setChecked(false);
    ui->radio_39_40->setChecked(false);
    ui->radio_41_42->setChecked(false);
    ui->radio_43_44->setChecked(false);
    ui->radio_33_34->setAutoExclusive(true);
    ui->radio_35_36->setAutoExclusive(true);
    ui->radio_37_38->setAutoExclusive(true);
    ui->radio_39_40->setAutoExclusive(true);
    ui->radio_41_42->setAutoExclusive(true);
    ui->radio_43_44->setAutoExclusive(true);
}

