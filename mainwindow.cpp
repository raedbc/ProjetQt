#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//client
    ui->tableView_client->setModel(c.afficher());

    //commande
ui->tableView_commande->setModel(co.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_go_to_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_bt_go_to_commande_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_bt_ajouter_client_clicked()
{
    //Etape1:
    //Etape2:
    //Etape3:
    //Etape4:
}


