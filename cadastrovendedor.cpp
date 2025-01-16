#include "cadastrovendedor.h"
#include "ui_cadastrovendedor.h"
#include "banco_de_dados.h"
#include <QMessageBox>

cadastrovendedor::cadastrovendedor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastrovendedor)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#484d54"));
    this->setPalette(palette);
}

cadastrovendedor::~cadastrovendedor()
{
    delete ui;
}

void cadastrovendedor::on_btn_cadastrar_vend_clicked()
{
    QString nome = ui->line_nome_cvend->text();
    int cod = ui->line_cod_cvend->text().toInt();
    QString cargo;
    double salario_base;
    double percentual_comissao;

    if (ui->radio_junior_cvend->isChecked()) {
        cargo = "Junior";
        salario_base = 1300;
        percentual_comissao = 0.01;
    } else if (ui->radio_pleno_cvend->isChecked()) {
        cargo = "Pleno";
        salario_base = 2500;
        percentual_comissao = 0.03;
    } else if (ui->radio_senior_cvend->isChecked()) {
        cargo = "Senior";
        salario_base = 3600;
        percentual_comissao = 0.05;
    }

    if(banco_de_dados::inserir_novo_vendedor(nome, cod, cargo, salario_base, percentual_comissao)){
        QMessageBox::information(this, "Sucesso", "Vendedor cadastrado com sucesso.");
    }
    else{
        QMessageBox::warning(this, "Erro", "Vendedor não foi cadastrado. Verifique os dados.");
    }

    ui->line_nome_cvend->clear();
    ui->line_cod_cvend->clear();
}

