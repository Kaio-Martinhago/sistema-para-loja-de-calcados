#include "controle_vendedores.h"
#include "ui_controle_vendedores.h"
#include "vendedor.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>



controle_vendedores::controle_vendedores(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::controle_vendedores)
{
    ui->setupUi(this);
    connect(ui->btn_inserir_cod_convend, &QPushButton::clicked,
            this, &controle_vendedores::on_btn_inserir_cod_convend_clicked);
}

controle_vendedores::~controle_vendedores()
{
    delete ui;
}

void controle_vendedores::on_btn_inserir_cod_convend_clicked()
{
    QString cod = ui->line_cod_convend->text().trimmed();

    if (cod.isEmpty()) {
        qDebug() << "Código do vendedor está vazio!";
        return;
    }

    carregarDadosVendedor(cod);
}

void controle_vendedores::carregarDadosVendedor(const QString &cod)
{
    QSqlDatabase db = QSqlDatabase::database("CENTRAL_CALCADOS");
    if (!db.isOpen()) {
        qDebug() << "Erro: Banco de dados não está aberto!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT cargo, salario_base, percentual_comissao, total_vendas "
                  "FROM tb_vendedor WHERE cod = :cod");
    query.bindValue(":cod", cod);

    if (!query.exec()) {
        qDebug() << "Erro ao buscar dados do vendedor:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        int id = query.value("cod").toInt();
        QString cargo = query.value("cargo").toString();
        QString nome = query.value("nome").toString();
        double salario_base = query.value("salario_base").toDouble();
        double comissao = query.value("percentual_comissao").toDouble();
        double total_vendas = query.value("total_vendas").toDouble();
        double salario_total;
        float comissao_total;

        if(cargo == "Junior"){
            VendedorJunior v1 (id, nome, salario_base, total_vendas, comissao, cargo);
            salario_total = v1.CalcularSalario();
            comissao_total = v1.getComissao();
        }
        else if(cargo == "Pleno"){
            VendedorPleno v2 (id, nome, salario_base, total_vendas, comissao, cargo);
            salario_total = v2.CalcularSalario();
            comissao_total = v2.getComissao();
        }
        else if(cargo == "Senior"){
            VendedorSenior v3 (id, nome, salario_base, total_vendas, comissao, cargo);
            salario_total = v3.CalcularSalario();
            comissao_total = v3.getComissao();
        }

        ui->line_cargo_convend->setText(cargo);
        ui->line_salbase_convend->setText(QString::number(salario_base, 'f', 2));
        ui->line_comissao_convend->setText(QString::number(comissao_total, 'f', 2));
        ui->line_sal_totalconvend->setText(QString::number(salario_total, 'f', 2));
    } else {
        qDebug() << "Vendedor com código" << cod << "não encontrado.";
        ui->line_cargo_convend->clear();
        ui->line_salbase_convend->clear();
        ui->line_comissao_convend->clear();
        ui->line_sal_totalconvend->clear();
    }
}
