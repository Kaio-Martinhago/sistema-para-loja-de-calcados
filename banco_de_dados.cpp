#include "banco_de_dados.h"
#include <QMessageBox>

banco_de_dados::banco_de_dados(){

    db = QSqlDatabase::addDatabase("QSQLITE", "CENTRAL_CALCADOS");
    caminhobanco = QDir::homePath() + "/bancolojacalcados.db";
    db.setDatabaseName(caminhobanco);

    if(!db.open()){
        qDebug() << "Erro ao acessar informacoes" << db.lastError().text();
    }
    else{
        qDebug() << "Banco conectado com sucesso em " << caminhobanco;
    }

    //para criar tabela
    QSqlQuery query(db);
    if(!query.exec("CREATE TABLE IF NOT EXISTS tb_produto ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nome TEXT NOT NULL,"
                    "preco REAL NOT NULL)")){
        qDebug() << "ERRO! Nao foi possivel criar a tabela: " << query.lastError().text();
    }
    else{
        qDebug() << "Tabela criada com sucesso!";
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS tb_cliente ("
                    "nome TEXT NOT NULL,"
                    "cpf TEXT NOT NULL UNIQUE,"
                    "total_gasto REAL NOT NULL DEFAULT 0)")) {
        qDebug() << "ERRO! Não foi possível criar a tabela tb_cliente: " << query.lastError().text();
    } else {
        qDebug() << "Tabela tb_cliente criada com sucesso!";
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS tb_vendedor ("
                    "nome TEXT NOT NULL,"
                    "cod TEXT NOT NULL UNIQUE,"
                    "cargo TEXT NOT NULL,"
                    "total_vendas REAL DEFAULT 0,"
                    "salario_base REAL NOT NULL DEFAULT 0,"
                    "percentual_comissao REAL NOT NULL DEFAULT 0)")) {
        qDebug() << "ERRO! Não foi possível criar a tabela tb_vendedor: " << query.lastError().text();
    } else {
        qDebug() << "Tabela tb_vendedor criada com sucesso!";
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS tb_estoque ("
                    "cod INTEGER NOT NULL,"
                    "qtd INTEGER NOT NULL,"
                    "numeracao INTEGER NOT NULL,"
                    "UNIQUE (cod, numeracao))")) {
        qDebug() << "ERRO! Não foi possível criar a tabela tb_estoque: " << query.lastError().text();
    } else {
        qDebug() << "Tabela tb_estoque criada com sucesso!";
    }
};

bool banco_de_dados::verificar_codigo_existente(int cod) {
    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    query.prepare("SELECT COUNT(*) FROM tb_produto WHERE id = :id");
    query.bindValue(":id", cod);

    if (!query.exec()) {
        qDebug() << "Erro ao verificar código do produto:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}

bool banco_de_dados::inserir_novo_produto(QString nome, double valor, int cod){

    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS"); //variavel que vai acessar o banco de dados, que esta na conexao central_caklcados
    QSqlQuery query(d);

    query.prepare("INSERT INTO tb_produto (id, nome, preco) VALUES (:id, :nome, :preco)");
    query.bindValue(":id", cod);
    query.bindValue(":nome", nome);
    query.bindValue(":preco", valor);

    if(!query.exec()){
        qDebug() << "ERRO! nao foi possivel inserir novo produto";
        return false;
    }

    qDebug() << "Cadastro do produto foi um sucesso!!";

    return true;
};

bool banco_de_dados::verificar_cpf_existente(const QString &cpf) {
    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    query.prepare("SELECT COUNT(*) FROM tb_cliente WHERE cpf = :cpf");
    query.bindValue(":cpf", cpf);

    if (!query.exec()) {
        qDebug() << "Erro ao verificar CPF:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}

bool banco_de_dados::inserir_novo_cliente(const QString &nome, const QString &cpf) {
    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    query.prepare("INSERT INTO tb_cliente (nome, cpf) VALUES (:nome, :cpf)");
    query.bindValue(":nome", nome);
    query.bindValue(":cpf", cpf);

    if (!query.exec()) {
        qDebug() << "ERRO! Não foi possível cadastrar novo cliente:" << query.lastError().text();
        return false;
    }

    qDebug() << "Cadastro do cliente foi um sucesso!!";

    return true;
}

bool banco_de_dados::inserir_novo_vendedor(QString nome, int cod, QString cargo, double salario_base, double percentual_comissao){
    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    query.prepare("INSERT INTO tb_vendedor (nome, cod, cargo, salario_base, percentual_comissao) VALUES (:nome, :cod, :cargo, :salario_base, :percentual_comissao)");
    query.bindValue(":nome", nome);
    query.bindValue(":cod", cod);
    query.bindValue(":cargo", cargo);
    query.bindValue(":salario_base", salario_base);
    query.bindValue(":percentual_comissao", percentual_comissao);

    if(!query.exec()){
        qDebug() << "ERRO! nao foi possivel cadastrar novo vendedor: " << query.lastError().text();
        return false;
    }

    qDebug() << "Cadastro do vendedors foi um sucesso!!";

    return true;
}

bool banco_de_dados::inserir_estoque(QString cod, int qtd, int numeracao) {
    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    query.prepare("SELECT qtd FROM tb_estoque WHERE cod = :cod AND numeracao = :numeracao");
    query.bindValue(":cod", cod);
    query.bindValue(":numeracao", numeracao);

    if (!query.exec()) {
        qDebug() << "Erro ao verificar o estoque: " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int qtd_existente = query.value(0).toInt();
        int nova_qtd = qtd_existente + qtd;

        query.prepare("UPDATE tb_estoque SET qtd = :nova_qtd WHERE cod = :cod AND numeracao = :numeracao");
        query.bindValue(":nova_qtd", nova_qtd);
        query.bindValue(":cod", cod);
        query.bindValue(":numeracao", numeracao);

        if (!query.exec()) {
            qDebug() << "Erro ao atualizar o estoque: " << query.lastError().text();
            return false;
        }

        qDebug() << "Quantidade atualizada no estoque com sucesso!";
        return true;
    } else {
        query.prepare("INSERT INTO tb_estoque (cod, qtd, numeracao) VALUES (:cod, :qtd, :numeracao)");
        query.bindValue(":cod", cod);
        query.bindValue(":qtd", qtd);
        query.bindValue(":numeracao", numeracao);

        if (!query.exec()) {
            qDebug() << "Erro ao inserir produto no estoque: " << query.lastError().text();
            return false;
        }

        qDebug() << "Produto inserido no estoque com sucesso!";
        return true;
    }
}

bool banco_de_dados::remover_do_estoque(int cod, int qtd, int numeracao){
    QSqlDatabase d = QSqlDatabase::database("CENTRAL_CALCADOS");
    QSqlQuery query(d);

    qDebug() << "Valores recebidos -> Cod:" << cod << ", Numeracao:" << numeracao;

    query.prepare("SELECT qtd FROM tb_estoque WHERE cod = :cod AND numeracao = :numeracao");
    query.bindValue(":cod", cod);
    query.bindValue(":numeracao", numeracao);

    if (!query.exec()) {
        qDebug() << "Erro ao verificar o estoque:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int qtd_existente = query.value(0).toInt();

        if (qtd > qtd_existente) {
            qDebug() << "Quantidade a remover excede o estoque disponível.";
            return false;
        }

        int nova_qtd = qtd_existente - qtd;

        if (nova_qtd == 0) {
            query.prepare("DELETE FROM tb_estoque WHERE cod = :cod AND numeracao = :numeracao");
        } else {
            query.prepare("UPDATE tb_estoque SET qtd = :nova_qtd WHERE cod = :cod AND numeracao = :numeracao");
            query.bindValue(":nova_qtd", nova_qtd);
        }

        query.bindValue(":cod", cod);
        query.bindValue(":numeracao", numeracao);

        if (!query.exec()) {
            qDebug() << "Erro ao atualizar o estoque:" << query.lastError().text();
            return false;
        }

        qDebug() << "Produto removido do estoque com sucesso.";
        return true;
    }

    qDebug() << "Produto não encontrado no estoque.";
    return false;
}
