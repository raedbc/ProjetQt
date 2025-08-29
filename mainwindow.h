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

    void on_bt_ajouter_client_clicked();

    void on_bt_modifier_client_clicked();

    void on_bt_supprimer_client_clicked();

    void on_bt_refresh_client_clicked();

    void on_tableView_client_clicked(const QModelIndex &index);

    void remplir_comboBox_id_livreur();

    void remplir_comboBox_id_client();

    void on_bt_ajouter_commande_clicked();

    void on_bt_modifier_commande_clicked();

    void on_bt_supprimer_commande_clicked();

    void on_tableView_commande_clicked(const QModelIndex &index);

    void on_bt_chercher_commande_clicked();

    void on_bt_trier_commande_clicked();

    void on_bt_refresh_commande_clicked();

    void on_bt_chercher_client_clicked();

    void on_bt_trier_client_clicked();

    void on_bt_stat_commande_clicked();

    void on_bt_stat_client_clicked();

    void on_bt_pdf_client_clicked();

    void on_bt_pdf_commande_clicked();

    void on_bt_historique_clicked();
    void addToHistory(const QString &action, const QString &id);

    void on_bt_qrCode_clicked();

private:
    Ui::MainWindow *ui;
    clients c;
    commandes co;
};
#endif // MAINWINDOW_H
