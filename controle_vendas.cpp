#include "controle_vendas.h"
#include "ui_controle_vendas.h"

controle_vendas::controle_vendas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::controle_vendas)
{
    ui->setupUi(this);
}

controle_vendas::~controle_vendas()
{
    delete ui;
}
