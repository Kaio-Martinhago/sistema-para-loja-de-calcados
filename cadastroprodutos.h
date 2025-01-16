#ifndef CADASTROPRODUTOS_H
#define CADASTROPRODUTOS_H

#include <QDialog>

namespace Ui {
class cadastroprodutos;
}

class cadastroprodutos : public QDialog
{
    Q_OBJECT

public:
    explicit cadastroprodutos(QWidget *parent = nullptr);
    ~cadastroprodutos();

private slots:
    void on_btn_cadastrar_clicked();

private:
    Ui::cadastroprodutos *ui;
};

#endif // CADASTROPRODUTOS_H
