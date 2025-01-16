#include "controle_estoque.h"
#include "ui_controle_estoque.h"
#include "banco_de_dados.h"
#include <QTableWidgetItem>

controle_estoque::controle_estoque(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::controle_estoque)
{
    ui->setupUi(this);

    ui->table_estoque->setColumnCount(3);
    ui->table_estoque->setHorizontalHeaderLabels({"Código", "Quantidade", "Numeração"});
    ui->table_estoque->horizontalHeader()->setStretchLastSection(true);
    ui->table_estoque->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_estoque->setSelectionBehavior(QAbstractItemView::SelectRows);
}

controle_estoque::~controle_estoque()
{
    delete ui;
}

void controle_estoque::preencherTabela(const QString &codigo, const QString &quantidade, const QString &numeracao){

    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    if (!d.isOpen()) {
        qDebug() << "Erro: Conexão com o banco de dados não aberta!" << query.lastError().text();
        return;
    }

    QString queryStr = "SELECT * FROM tb_estoque WHERE 1";

    if (!codigo.isEmpty()) {
        queryStr += " AND cod = :cod";
    }
    if (!quantidade.isEmpty()) {
        queryStr += " AND qtd = :quantidade";
    }
    if (!numeracao.isEmpty()) {
        queryStr += " AND numeracao = :numeracao";
    }

    query.prepare(queryStr);

    if (!codigo.isEmpty()) {
        query.bindValue(":cod", codigo);
    }
    if (!quantidade.isEmpty()) {
        query.bindValue(":quantidade", quantidade);
    }
    if (!numeracao.isEmpty()) {
        query.bindValue(":numeracao", numeracao);
    }

    if (!query.exec()) {
        qDebug() << "Erro ao filtrar o estoque: " << query.lastError().text();
        return;
    }

    ui->table_estoque->clearContents();
    ui->table_estoque->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->table_estoque->insertRow(row);
        ui->table_estoque->setItem(row, 0, new QTableWidgetItem(query.value("cod").toString()));
        ui->table_estoque->setItem(row, 1, new QTableWidgetItem(query.value("qtd").toString()));
        ui->table_estoque->setItem(row, 2, new QTableWidgetItem(query.value("numeracao").toString()));
        row++;
    }
}


void controle_estoque::on_btn_filtrar_clicked(){
    QString codigo = ui->line_cod->text();
    QString quantidade = ui->line_qtd->text();
    QString numeracao = ui->line_numeracao->text();

    preencherTabela(codigo, quantidade, numeracao);
}

