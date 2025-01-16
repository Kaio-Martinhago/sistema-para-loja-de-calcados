#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <iostream>
#include <QDir>
#include <sstream>

class banco_de_dados{
    private:
        QSqlDatabase db;
        QString caminhobanco;
    public:
        banco_de_dados();
        static bool inserir_novo_produto(QString nome, double valor, int cod);
        static bool verificar_codigo_existente(int cod);
        static bool inserir_novo_cliente(const QString &nome, const QString &cpf);
        static bool verificar_cpf_existente(const QString &cpf);
        static bool inserir_novo_vendedor(QString nome, int cod, QString cargo, double salario_base, double percentual_comissao);
        static bool inserir_estoque(QString cod, int qtd, int numeracao);
        static bool remover_do_estoque(int cod, int quantidade, int numeracao);
};

#endif // BANCO_DE_DADOS_H
