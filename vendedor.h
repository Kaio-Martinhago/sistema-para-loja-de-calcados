#ifndef VENDEDOR_H
#define VENDEDOR_H

#include <iostream>
#include <qstring.h>

class Vendedor{
protected:
    int m_id;
    double m_salario_base;
    double m_salario_final;
    double m_totalvendas;
    float m_comissao;
    QString m_nome;

public:
    Vendedor(int id, QString nome, double salario_base, double totalvendas, float comissao);

    virtual double CalcularSalario() = 0;
    virtual float getComissao() = 0;
    double getSalarioBase();
    void setTotalVendas(double totalvendas);
};

class VendedorJunior : public Vendedor{
protected:
    QString m_cargo = "Junior";
public:
    VendedorJunior(int id, QString nome, double salario_base, double totalvendas, float comissao, QString cargo);
    double CalcularSalario();
    float getComissao();
};

class VendedorPleno : public Vendedor{
protected:
    QString m_cargo = "Pleno";
public:
    VendedorPleno(int id, QString nome, double salario_base, double totalvendas, float comissao, QString cargo);
    double CalcularSalario();
    float getComissao();
};

class VendedorSenior : public Vendedor{
protected:
    QString m_cargo = "Senior";
public:
    VendedorSenior(int id, QString nome, double salario_base, double totalvendas, float comissao, QString cargo);
    double CalcularSalario();
    float getComissao();
};
#endif // VENDEDOR_H


