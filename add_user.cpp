#include "add_user.h"
#include "ui_add_user.h"
#include "class_users.h"
#include "utility.h"

Add_User::Add_User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_User)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Dodaj uzytkownika");
}

Add_User::~Add_User()
{
    delete ui;
}

void Add_User::on_pushButton_clicked() //potwierdz
{
    std::string nazwa,login,haslo;

    if (ui->lineEdit->text().isEmpty() ||  ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty()){
            QMessageBox::critical(this,"Error","Blad! Wymagane sa 3 wartosci! Zmiany nie zostały zachowane.")                                                               ;
            Add_User::close();
    }

    nazwa = ui->lineEdit->text().toStdString();
    login = ui->lineEdit_2->text().toStdString();
    haslo = ui->lineEdit_3->text().toStdString();


    if (Passwords->add_user(nazwa,login,haslo)){
        QMessageBox::information(this,"Sukces!","Sukces! Dodano nową pozycje!");
        Add_User::close();
    }
    else {
        QMessageBox::critical(this,"Error","Blad! Cos poszlo nie tak! Zmiany nie zostały zachowane.")                                                               ;
        Add_User::close();
    }


}

void Add_User::on_pushButton_2_clicked()
{
    Add_User::close();
}
