#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>

namespace Ui {
class Add_User;
}

class Add_User : public QDialog
{
    Q_OBJECT

public:
    explicit Add_User(QWidget *parent = nullptr);
    ~Add_User();

private Q_SLOTS :
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Add_User *ui;
};

#endif // ADD_USER_H
