#include "cadastroprodutos.h"
#include "ui_cadastroprodutos.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "banco_de_dados.h"

cadastroprodutos::cadastroprodutos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroprodutos)
{
    ui->setupUi(this);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#484d54"));
    this->setPalette(palette);
}

cadastroprodutos::~cadastroprodutos()
{
    delete ui;
}

void cadastroprodutos::on_btn_cadastrar_clicked()
{
    QString nome = ui->line_nome_cprod->text();
    double valor =ui->line_valor_cprod->text().toDouble();
    int cod = ui->line_cod_cprod->text().toInt();

    if (banco_de_dados::verificar_codigo_existente(cod)) {
        QMessageBox::warning(this, "Erro", "Código do produto já foi utilizado, escolha outro código.");
        return;
    }

    if(banco_de_dados::inserir_novo_produto(nome, valor, cod)){
        QMessageBox::information(this, "Sucesso", "Produto cadastrado com sucesso.");
    }
    else{
        QMessageBox::warning(this, "Erro", "Produto não foi cadastrado. Verifique os dados.");
    }


    ui->line_nome_cprod->clear();
    ui->line_valor_cprod->clear();
    ui->line_cod_cprod->clear();
}

