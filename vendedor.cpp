#include "vendedor.h"

Vendedor::Vendedor(int id, QString nome, double salario_base, double totalvendas, float comissao)
    : m_id(id), m_nome(nome), m_salario_base(salario_base), m_totalvendas(totalvendas), m_comissao(comissao){};

VendedorJunior::VendedorJunior(int id, QString nome, double salario_base, double totalvendas, float comissao, QString cargo)
    : Vendedor(id, nome, salario_base, totalvendas, comissao), m_cargo(cargo){};

VendedorPleno::VendedorPleno(int id, QString nome, double salario_base, double totalvendas, float comissao, QString cargo)
    : Vendedor(id, nome, salario_base, totalvendas, comissao), m_cargo(cargo){};

VendedorSenior::VendedorSenior(int id, QString nome, double salario_base, double totalvendas, float comissao, QString cargo)
    : Vendedor(id, nome, salario_base, totalvendas, comissao), m_cargo(cargo){};


double VendedorJunior::CalcularSalario(){
    m_salario_final = m_salario_base + (m_totalvendas * 0.01); //0.01 = comissao junior
    return m_salario_final;
}

double VendedorPleno::CalcularSalario(){
    m_salario_final = m_salario_base + (m_totalvendas * 0.03); //0.03 = comissao pleno
    return m_salario_final;
}

double VendedorSenior::CalcularSalario(){
    m_salario_final = m_salario_base + (m_totalvendas * 0.05); //0.05 = comissao senior
    return m_salario_final;
}

float VendedorJunior::getComissao(){return (m_totalvendas * 0.01);}

float VendedorPleno::getComissao(){return (m_totalvendas * 0.03);}

float VendedorSenior::getComissao(){return (m_totalvendas * 0.05);}
