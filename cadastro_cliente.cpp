#include "cadastro_cliente.h"
#include "ui_cadastro_cliente.h"
#include "banco_de_dados.h"
#include <QMessageBox>

cadastro_cliente::cadastro_cliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastro_cliente)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#484d54"));
    this->setPalette(palette);
}

cadastro_cliente::~cadastro_cliente()
{
    delete ui;
}

void cadastro_cliente::on_btn_cadastrar_cliente_clicked()
{
    QString nome = ui->line_nome_ccliente->text();
    QString cpf =ui->line_cpf_ccliente->text();

    if (banco_de_dados::verificar_cpf_existente(cpf)) {
        QMessageBox::warning(this, "Erro", "CPF já cadastrado. Tente um CPF diferente.");
        return;
    }

    if(banco_de_dados::inserir_novo_cliente(nome, cpf)){
        QMessageBox::information(this, "Sucesso", "Cliente cadastrado com sucesso.");
    }
    else{
        QMessageBox::warning(this, "Erro", "Cliente não foi cadastrado. Verifique os dados.");
    }

    ui->line_nome_ccliente->clear();
    ui->line_cpf_ccliente->clear();
}

