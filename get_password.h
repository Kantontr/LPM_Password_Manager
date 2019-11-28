#ifndef GET_PASSWORD_H
#define GET_PASSWORD_H

#include <QDialog>

namespace Ui {
class Get_Password;
}

class Get_Password : public QDialog
{
    Q_OBJECT

public:
    explicit Get_Password(QWidget *parent = nullptr);
    ~Get_Password();

private Q_SLOTS :
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Get_Password *ui;
};

#endif // GET_PASSWORD_H
