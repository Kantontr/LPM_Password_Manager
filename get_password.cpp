#include "get_password.h"
#include "ui_get_password.h"
#include "utility.h"
#include "class_users.h"

Get_Password::Get_Password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Get_Password)
{
    ui->setupUi(this);

    ui->lineEdit->setEchoMode(QLineEdit::Password);
    QWidget::setWindowTitle("Wprowadz haslo");
}

Get_Password::~Get_Password()
{
    delete ui;
}

void Get_Password::on_pushButton_clicked()
{

    Passwords->password = ui->lineEdit->text().toStdString();
    Get_Password::close();

}

void Get_Password::on_pushButton_2_clicked()
{
    exit(0);
}
