#ifndef CADASTROVENDEDOR_H
#define CADASTROVENDEDOR_H

#include <QDialog>

namespace Ui {
class cadastrovendedor;
}

class cadastrovendedor : public QDialog
{
    Q_OBJECT

public:
    explicit cadastrovendedor(QWidget *parent = nullptr);
    ~cadastrovendedor();

private slots:
    void on_btn_cadastrar_vend_clicked();

private:
    Ui::cadastrovendedor *ui;
};

#endif // CADASTROVENDEDOR_H
