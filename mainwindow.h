#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clients.h"
#include "commandes.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_go_to_client_clicked();

    void on_bt_go_to_commande_2_clicked();

private:
    Ui::MainWindow *ui;
    clients c;
    commandes co;
};
#endif // MAINWINDOW_H
