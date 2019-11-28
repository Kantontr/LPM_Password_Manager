#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "get_password.h"
#include "utility.h"
#include "class_users.h"
#include "add_user.h"
#include <chrono>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    Get_Password I_password;
    I_password.setModal(true);
    I_password.exec();

    while(!(Passwords->load_passwords())){

        if(!LPM_file_exist(Passwords->file_path_enc) && Passwords->password.size()>0)break;

        QMessageBox::information(this,"Blad","Podales zle haslo!");
        Get_Password I_password;
        I_password.setModal(true);
        I_password.exec();

    }






    ui->setupUi(this);

    QWidget::setWindowTitle("LPM Password Manager v1.2");

    for(int i=0;i<Passwords->active_users;i++){
        ui->listWidget->addItem(Passwords->users[i].name.c_str());
        ui->listWidget_2->addItem(Passwords->users[i].login.c_str());
        ui->listWidget_3->addItem("*************");
        //ui->listWidget_3->addItem(Passwords->users[i].password.c_str());
    }


    time_since_launch = 0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(clock_set()));
    timer->start(1000);


    /*
    while(true){

        Sleep(1000);
        std::chrono::system_clock::time_point now_tmp = std::chrono::system_clock::now();
        time_passed_since_launch = std::chrono::duration_cast<std::chrono::seconds>(now_tmp-now).count();
        ui->label_5->setText(std::to_string(60-time_passed_since_launch).c_str());
        ui->label_5->update();

    }
    */


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clock_set()
{
    int timeout_time = 60;

    if((timeout_time - time_since_launch)<=10){
        ui->label_5->setStyleSheet("color: red");
    }
    else{
        ui->label_5->setStyleSheet("color: black");
    }

    ui->label_5->setText(std::to_string(timeout_time - time_since_launch).c_str());
    ui->label_5->update();
    time_since_launch++;
    if(time_since_launch > timeout_time){

        QMessageBox msgBox;
            msgBox.setText("Upłynął czas nieaktywnosci! Program zostanie wyłączony!");
            msgBox.setWindowTitle("Timeout!");
            msgBox.show();
            QCoreApplication::processEvents();
        Sleep(3000);
        exit(0);
    }
}

void MainWindow::on_pushButton_3_clicked() //dodaj pozycje
{
    time_since_launch = 0;

    int old_active_users = Passwords->active_users;

    Add_User add_user;
    add_user.setModal(true);
    add_user.exec();

    if(old_active_users!=Passwords->active_users){

        ui->listWidget->addItem(Passwords->users[Passwords->active_users-1].name.c_str());
        ui->listWidget_2->addItem(Passwords->users[Passwords->active_users-1].login.c_str());
        ui->listWidget_3->addItem(Passwords->users[Passwords->active_users-1].password.c_str());

    }



}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->listWidget_2->setCurrentRow(currentRow);
    ui->listWidget_3->setCurrentRow(currentRow);

    ui->listWidget->update();
    ui->listWidget_2->update();
    ui->listWidget_3->update();
}

void MainWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
    ui->listWidget->setCurrentRow(currentRow);
    ui->listWidget_3->setCurrentRow(currentRow);

    ui->listWidget->update();
    ui->listWidget_2->update();
    ui->listWidget_3->update();
}

void MainWindow::on_listWidget_3_currentRowChanged(int currentRow)
{
    ui->listWidget_2->setCurrentRow(currentRow);
    ui->listWidget->setCurrentRow(currentRow);

    ui->listWidget->update();
    ui->listWidget_2->update();
    ui->listWidget_3->update();
}

void MainWindow::on_pushButton_clicked() //login copy to clipboard
{
    time_since_launch = 0;

    if(ui->listWidget_2->currentItem()->text().size()>0){
        copy_to_clipboard(ui->listWidget_2->currentItem()->text().toStdString());
    }

}

void MainWindow::on_pushButton_2_clicked()//password copy to clipboard
{
    time_since_launch = 0;

    if(ui->listWidget_3->currentItem()->text().size()>0){
        copy_to_clipboard(Passwords->users[ui->listWidget->currentRow()].password);
    }
}

void MainWindow::on_pushButton_6_clicked() //wyjdz
{

    time_since_launch = 0;

    if(LPM_file_exist(Passwords->file_path)){
        Passwords->file_enc_dec("-d",Passwords->password);
        if(LPM_file_exist(Passwords->file_path)){
            QMessageBox::critical(this,"Error!","Cos poszlo nie tak! NIe mozna ponownie zakodowac pliku z haslami!!!");
        }
        else exit(1);
    }
    else exit(1);
}

void MainWindow::on_pushButton_4_clicked()//usun pozycje
{

    time_since_launch = 0;

    if(ui->listWidget->currentItem()->text().size()>0){

        int current_row = ui->listWidget->currentRow();
        QMessageBox::StandardButton reply;
        std::string command = "Usunac pozycje: ";
        command += Passwords->users[current_row].name;
        command += " ?";

        reply = QMessageBox::question(this, "Usunac pozycje?", command.c_str(),QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            if(Passwords->remove_user(ui->listWidget->currentRow())){
                QMessageBox::information(this,"Sukces!","Usunieto pozycje!");
                ui->listWidget->takeItem(current_row);
                ui->listWidget_2->takeItem(current_row);
                ui->listWidget_3->takeItem(current_row);

            }
            else{
                QMessageBox::critical(this,"Error","Blad! Nie udalo sie usunac uzytkownika!");
            }
        }
    }
    else {
        QMessageBox::information(this,"Blad","Musisz wybrac uzytkownika!");
    }

}
