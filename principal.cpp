#include "principal.h"
#include "ui_principal.h"
#include "cadastroprodutos.h"
#include "cadastrovendedor.h"
#include "cadastro_cliente.h"
#include "inserir_produtos.h"
#include "remover_produtos.h"
#include "controle_vendedores.h"
#include "controle_vendas.h"
#include "controle_estoque.h"
#include "banco_de_dados.h"
#include <QtSql>
#include <QTableWidgetItem>
#include <QMessageBox>

principal::principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);

    connect(ui->radio_dinheiro, SIGNAL(toggled(bool)), this, SLOT(on_radio_dinheiro_toggled(bool)));
    connect(ui->radio_cdebito, SIGNAL(toggled(bool)), this, SLOT(on_radio_cdebito_toggled(bool)));
    connect(ui->radio_ccredito, SIGNAL(toggled(bool)), this, SLOT(on_radio_ccredito_toggled(bool)));

    connect(ui->spin_perc_desc, SIGNAL(valueChanged(int)), this, SLOT(atualizarDesconto(int)));

    ui->tabelaprincipal->setColumnCount(3);
    ui->tabelaprincipal->setHorizontalHeaderLabels({"Código", "Nome", "Preço"});
    ui->tabelaprincipal->horizontalHeader()->setStretchLastSection(true);
    ui->tabelaprincipal->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tabelaprincipal->setSelectionBehavior(QAbstractItemView::SelectRows);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor("#b0abab"));
    this->setPalette(palette);

    banco_de_dados();

    //Cores da menu bar/submenus:
    QMenuBar* menuBar = this->menuBar();
    menuBar->setStyleSheet(
        "QMenuBar {"
        "    background-color: #193263;"
        "    color: #FFFFFF;"
        "}"
        "QMenuBar::item {"
        "    background-color: transparent;"
        "    color: #FFFFFF;"
        "}"
        "QMenuBar::item:selected {"
        "    background-color: #248;"
        "    color: #FFFFFF;"
        "}"
        "QMenu {"
        "    background-color: #193263 !important;"
        "    border: 1px solid #222222;"
        "    color: #FFFFFF;"
        "}"
        "QMenu::item {"
        "    background-color: transparent;"
        "    color: #FFFFFF;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #248;"
        "    color: #FFFFFF;"
        "}"
        "QMenu::item:pressed {"
        "    background-color: #193263;"
        "    color: #FFFFFF;"
        "}"
        "QMenu QMenu {"
        "    background-color: #193263 !important;"
        "    border: 1px solid #444444;"
        "    color: #FFFFFF;"
        "}"
        "QMenu QMenu::item {"
        "    background-color: #193263;"
        "    color: #FFFFFF;"
        "}"
        "QMenu QMenu::item:selected {"
        "    background-color: #248 !important;"
        "    color: #FFFFFF;"
        "}"
        );
}

principal::~principal()
{
    delete ui;
}

void principal::on_actionNovo_Produto_triggered()
{
    cadastroprodutos cadastra_prod;
    cadastra_prod.exec();
}


void principal::on_actionNovo_Vendedor_triggered()
{
    cadastrovendedor cadastra_vend;
    cadastra_vend.exec();
}


void principal::on_actionNovo_Cliente_triggered()
{
    cadastro_cliente cadastra_cliente;
    cadastra_cliente.exec();
}


void principal::on_actionInserir_produtos_triggered()
{
    inserir_produtos insere_prod;
    insere_prod.exec();
}


void principal::on_actionRemover_Produtos_triggered()
{
    remover_produtos remove_prod;
    remove_prod.exec();
}


void principal::on_actionVendedores_2_triggered()
{
    controle_vendedores controle_vendedor;
    controle_vendedor.exec();
}


void principal::on_actionVendas_triggered()
{
    controle_vendas controle_vendas;
    controle_vendas.exec();
}


void principal::on_actionConsulta_de_Estoque_triggered()
{
    controle_estoque consulta_estoque;
    consulta_estoque.exec();
}


void principal::on_btn_insere_cod_clicked(){
    int codigo = ui->insere_cod->text().toInt();

    if (codigo <= 0) {
        QMessageBox::warning(this, "Erro", "Por favor, insira um código válido.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(db);

    query.prepare("SELECT nome, preco FROM tb_produto WHERE id = :codigo");
    query.bindValue(":codigo", codigo);

    if (!query.exec()) {
        qDebug() << "Erro ao buscar produto: " << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString nome = query.value("nome").toString();
        double preco = query.value("preco").toDouble();

        int row = ui->tabelaprincipal->rowCount();
        ui->tabelaprincipal->insertRow(row);
        ui->tabelaprincipal->setItem(row, 0, new QTableWidgetItem(QString::number(codigo)));
        ui->tabelaprincipal->setItem(row, 1, new QTableWidgetItem(nome));
        ui->tabelaprincipal->setItem(row, 2, new QTableWidgetItem(QString::number(preco, 'f', 2)));

        atualizarTotalEQuantidade();
    } else {
        QMessageBox::warning(this, "Erro", "Produto não encontrado.");
    }

    ui->insere_cod->clear();
}

void principal::atualizarTotalEQuantidade(){
    double total = 0;
    int quantidade = 0;

    for (int row = 0; row < ui->tabelaprincipal->rowCount(); row++) {
        total += ui->tabelaprincipal->item(row, 2)->text().toDouble();
        quantidade++;
    }

    ui->totalvalor1->setText(QString::number(total, 'f', 2));
    ui->qtd_pecas->setText(QString::number(quantidade));
}

void principal::updateParcelas() {
    if (ui->tabelaprincipal->rowCount() == 0) {
        QMessageBox::warning(this, "Erro", "Adicione pelo menos um produto ao carrinho.");
        return;
    }

    double totalCompra = 0.0;
    for (int row = 0; row < ui->tabelaprincipal->rowCount(); ++row) {
        totalCompra += ui->tabelaprincipal->item(row, 2)->text().toDouble();
    }

    ui->combo_parcelas->clear();

    if (ui->radio_dinheiro->isChecked() || ui->radio_cdebito->isChecked()) {
        ui->combo_parcelas->addItem(QString("1x - R$ %1").arg(totalCompra, 0, 'f', 2));
    } else if (ui->radio_ccredito->isChecked()) {
        for (int i = 1; i <= 5; ++i) {
            double valorParcela = totalCompra / i;
            ui->combo_parcelas->addItem(QString("%1x - R$ %2").arg(i).arg(valorParcela, 0, 'f', 2));
        }
    }
}

void principal::on_radio_dinheiro_toggled(bool checked) {
    if (checked) {
        updateParcelas();
    }
}

void principal::on_radio_cdebito_toggled(bool checked) {
    if (checked) {
        updateParcelas();
    }
}

void principal::on_radio_ccredito_toggled(bool checked) {
    if (checked) {
        updateParcelas();
    }
}

void principal::atualizarDesconto(int percDesconto) {
    double totalCompra = ui->totalvalor1->text().toDouble();

    double valorDesconto = totalCompra * percDesconto / 100.0;

    ui->line_valor_desc->setText(QString::number(valorDesconto, 'f', 2));

    double valorFinal = totalCompra - valorDesconto;

    ui->totalvalor2->setText(QString::number(valorFinal, 'f', 2));

    atualizarParcelasComDesconto(valorFinal);
}

void principal::atualizarParcelasComDesconto(double valorFinal) {
    ui->combo_parcelas->clear();

    if (ui->radio_dinheiro->isChecked() || ui->radio_cdebito->isChecked()) {
        ui->combo_parcelas->addItem(QString("1x - R$ %1").arg(valorFinal, 0, 'f', 2));
    } else if (ui->radio_ccredito->isChecked()) {
        for (int i = 1; i <= 5; ++i) {
            double valorParcela = valorFinal / i;
            ui->combo_parcelas->addItem(QString("%1x - R$ %2").arg(i).arg(valorParcela, 0, 'f', 2));
        }
    }
}



void principal::on_btn_finalizar_clicked()
{
    QString cpfCliente = ui->line_cliente->text();
    QString codigoVendedor = ui->line_vendedor->text();

    if (cpfCliente.isEmpty() || codigoVendedor.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, insira o CPF do cliente e o código do vendedor.");
        return;
    }

    double valorCompra = 0.0;
    for (int row = 0; row < ui->tabelaprincipal->rowCount(); row++) {
        valorCompra += ui->tabelaprincipal->item(row, 2)->text().toDouble();
    }

    qDebug() << "Valor da compra antes do desconto: R$" << valorCompra;

    double totalComprasCliente = getTotalComprasCliente(cpfCliente);

    if (totalComprasCliente >= 2000.0) {
        valorCompra -= 100;
        qDebug() << "Desconto aplicado de R$ 100. Valor da compra com desconto: R$" << valorCompra;
    }

    double totalVendasVendedor = getTotalVendasVendedor(codigoVendedor);
    totalVendasVendedor += valorCompra;
    atualizarTotalVendasVendedor(codigoVendedor, totalVendasVendedor);

    atualizarTotalComprasCliente(cpfCliente, totalComprasCliente + valorCompra);

    QMessageBox::information(this, "Compra Finalizada", "Compra finalizada com sucesso!");

    qDebug() << "Compra finalizada com sucesso! Total da compra: R$" << valorCompra;
}

double principal::getTotalComprasCliente(const QString &cpf) {
    QSqlDatabase db = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(db);

    query.prepare("SELECT total_gasto FROM tb_cliente WHERE cpf = :cpf");
    query.bindValue(":cpf", cpf);

    if(!query.exec()){
        qDebug() << query.lastError().text();
    }

    if (query.next()) {
        qDebug() << "Cliente encontrado: CPF" << cpf << ", Total de compras:" << query.value(0).toDouble();
        return query.value(0).toDouble();
    } else {
        qDebug() << "Cliente não encontrado para CPF:" << cpf;
        QMessageBox::warning(this, "Erro", "Cliente não encontrado.");
        return 0.0;
    }
}

double principal::getTotalVendasVendedor(const QString &cod) {
    QSqlDatabase db = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(db);

    query.prepare("SELECT total_vendas FROM tb_vendedor WHERE cod = :cod");
    query.bindValue(":cod", cod);

    if (query.exec() && query.next()) {
        qDebug() << "Vendedor encontrado: Código" << cod << ", Total de vendas:" << query.value(0).toDouble();
        return query.value(0).toDouble();
    } else {
        qDebug() << "Vendedor não encontrado para código:" << cod;
        QMessageBox::warning(this, "Erro", "Vendedor não encontrado.");
        return 0.0;
    }
}

void principal::atualizarTotalVendasVendedor(const QString &cod, double novoTotal) {
    qDebug() << "Atualizando total de vendas do vendedor: Código" << cod << ", Novo total:" << novoTotal;

    QSqlDatabase db = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(db);

    query.prepare("UPDATE tb_vendedor SET total_vendas = :novoTotal WHERE cod = :cod");
    query.bindValue(":novoTotal", novoTotal);
    query.bindValue(":cod", cod);

    if (!query.exec()) {
        qDebug() << "Falha ao atualizar total de vendas do vendedor:" << query.lastError().text();
        QMessageBox::warning(this, "Erro", "Falha ao atualizar total de vendas do vendedor.");
    } else {
        qDebug() << "Total de vendas atualizado com sucesso para vendedor:" << cod;
    }
}


void principal::atualizarTotalComprasCliente(const QString &cpf, double novoTotal) {
    qDebug() << "Atualizando total de compras do cliente: CPF" << cpf << ", Novo total:" << novoTotal;

    QSqlDatabase db = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(db);

    query.prepare("UPDATE tb_cliente SET total_gasto = :novoTotal WHERE cpf = :cpf");
    query.bindValue(":novoTotal", novoTotal);
    query.bindValue(":cpf", cpf);

    if (!query.exec()) {
        qDebug() << "Falha ao atualizar total de compras do cliente:" << query.lastError().text();
        QMessageBox::warning(this, "Erro", "Falha ao atualizar total de compras do cliente.");
    } else {
        qDebug() << "Total de compras atualizado com sucesso para cliente:" << cpf;
    }
}
