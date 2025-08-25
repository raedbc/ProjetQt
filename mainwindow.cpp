#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QTextStream>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lors du l'éxuection   , lire une seul fois

//client
    ui->tableView_client->setModel(c.afficher());

    QIntValidator *intValidator = new QIntValidator(0, 100000000, this); // Only allows integers from 0 to 100000
    ui->telephone_client->setValidator(intValidator);
    ui->prix_commande->setValidator(intValidator);

    QRegularExpression charRegex("[a-zA-Z]*");
    QRegularExpressionValidator* charValidator = new QRegularExpressionValidator(charRegex, this);
    ui->nom_client->setValidator(charValidator);
    ui->prenom_client->setValidator(charValidator);

ui->id_client->hide();
ui->id_commande->hide();

    //commande
ui->tableView_commande->setModel(co.afficher());

ui->date_commande->setDate(QDate::currentDate());

remplir_comboBox_id_livreur();
remplir_comboBox_id_client();
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
    //Etape1:récuperation du donné mel ui
    QString nom=ui->nom_client->text();
    QString prenom=ui->prenom_client->text();
    QString email=ui->email_client->text();
    QString telephone=ui->telephone_client->text();
    QString delegation=ui->delegation_client->text();
    QString gouvernorat=ui->gouvernorat_client->text();
    QDate naissance=ui->naissance_client->date();
    QString sexe=ui->sexe_client->currentText();
    QString role=ui->role_client->currentText();
    QString adresse=ui->adresse_client->text();
    //Etape2:Controle de saisie
if(nom==""||prenom==""||email==""||telephone==""||delegation==""||gouvernorat=="")
{
    QMessageBox::information(nullptr, QObject::tr(""),
                QObject::tr("Tu dois remplir tous les champs."), QMessageBox::Cancel);
return;
}
if(telephone.length()!=8)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                QObject::tr("Le numero de telephone doit etre 8 chiffre."), QMessageBox::Cancel);
return;
}

QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");//aa@aa.aa
// Check if the email is valid
if (!emailRegex.match(email).hasMatch()) {
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("L'adresse email est invalide"), QMessageBox::Cancel);
    return;
}

    //Etape3:Appel du fonction Ajout
clients c(nom, prenom, email, telephone, adresse, naissance, gouvernorat, delegation, role, sexe);
bool test=c.ajouter();
    //Etape4:Affichage du Message Ajout avec succes ou echoue !
if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Ajout avec succées"), QMessageBox::Cancel);

    ui->tableView_client->setModel(c.afficher());
ui->nom_client->clear();
ui->prenom_client->clear();
ui->telephone_client->clear();
ui->email_client->clear();
ui->adresse_client->clear();
ui->delegation_client->clear();
ui->gouvernorat_client->clear();
ui->naissance_client->clear();
ui->sexe_client->setCurrentIndex(0);
ui->id_client->clear();

remplir_comboBox_id_client();
}
else
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Ajout échoué"), QMessageBox::Cancel);
}
}



void MainWindow::on_bt_modifier_client_clicked()
{
    //Etape1:récuperation du donné mel ui
    QString nom=ui->nom_client->text();
    QString prenom=ui->prenom_client->text();
    QString email=ui->email_client->text();
    QString telephone=ui->telephone_client->text();
    QString delegation=ui->delegation_client->text();
    QString gouvernorat=ui->gouvernorat_client->text();
    QDate naissance=ui->naissance_client->date();
    QString sexe=ui->sexe_client->currentText();
    QString role=ui->role_client->currentText();
    QString adresse=ui->adresse_client->text();
    int id_client=ui->id_client->text().toInt();
    //Etape2:Controle de saisie
if(nom==""||prenom==""||email==""||telephone==""||delegation==""||gouvernorat=="")
{
    QMessageBox::information(nullptr, QObject::tr(""),
                QObject::tr("Tu dois remplir tous les champs."), QMessageBox::Cancel);
return;
}
if(telephone.length()!=8)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                QObject::tr("Le numero de telephone doit etre 8 chiffre."), QMessageBox::Cancel);
return;
}

QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");//aa@aa.aa
// Check if the email is valid
if (!emailRegex.match(email).hasMatch()) {
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("L'adresse email est invalide"), QMessageBox::Cancel);
    return;
}

    //Etape3:Appel du fonction Ajout
clients c(id_client,nom, prenom, email, telephone, adresse, naissance, gouvernorat, delegation, role, sexe);
bool test=c.modifier();
    //Etape4:Affichage du Message Modification avec succes ou echoue !
if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Modification avec succées"), QMessageBox::Cancel);

    ui->tableView_client->setModel(c.afficher());
ui->nom_client->clear();
ui->prenom_client->clear();
ui->telephone_client->clear();
ui->email_client->clear();
ui->adresse_client->clear();
ui->delegation_client->clear();
ui->gouvernorat_client->clear();
ui->naissance_client->clear();
ui->sexe_client->setCurrentIndex(0);
ui->id_client->clear();
}
else
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Modification échoué"), QMessageBox::Cancel);
}
}


void MainWindow::on_bt_supprimer_client_clicked()
{
    int id_client=ui->id_client->text().toInt();
    if(id_client==0)
    {
        QMessageBox::critical(nullptr, QObject::tr(""),
                              QObject::tr("Tu dois choisir une ligne d'apres le tableau"), QMessageBox::Cancel);
    }
    else
    {
bool test=c.supprimer(id_client);
if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Suppression avec succées"), QMessageBox::Cancel);
    ui->tableView_client->setModel(c.afficher());

ui->nom_client->clear();
ui->prenom_client->clear();
ui->telephone_client->clear();
ui->email_client->clear();
ui->adresse_client->clear();
ui->delegation_client->clear();
ui->gouvernorat_client->clear();
ui->naissance_client->clear();
ui->sexe_client->setCurrentIndex(0);
ui->id_client->clear();

remplir_comboBox_id_client();
}
else
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Suppression échoué"), QMessageBox::Cancel);
}
    }}

void MainWindow::on_bt_refresh_client_clicked()
{
    ui->tableView_client->setModel(c.afficher());
    ui->choix_client->setCurrentIndex(0);
    ui->chercher_client->clear();
    ui->ordre_client->setCurrentIndex(0);

}

void MainWindow::on_tableView_client_clicked(const QModelIndex &index)
{
    //etape1: numero du ligne ! clicked !
    QAbstractItemModel* model = ui->tableView_client->model();

        int row = index.row();
    //etape2:  table du format matrice , recuperation du donne
        QString id_client = model->data(model->index(row, 0)).toString();
        QString nom = model->data(model->index(row, 1)).toString();
        QString prenom = model->data(model->index(row, 2)).toString();
        QString email = model->data(model->index(row, 3)).toString();
        QString  telephone= model->data(model->index(row, 4)).toString();
        QString adresse = model->data(model->index(row, 5)).toString();
        QDate naissance = model->data(model->index(row, 6)).toDate();
        QString gouvernorat = model->data(model->index(row, 7)).toString();
        QString delegation = model->data(model->index(row, 8)).toString();
        QString role = model->data(model->index(row, 9)).toString();
        QString sexe = model->data(model->index(row, 10)).toString();

        //etape3: insertion dans ui  ( lineEdit , comboBox)

        ui->id_client->setText(id_client);
        ui->nom_client->setText(nom);
        ui->prenom_client->setText(prenom);
        ui->email_client->setText(email);
        ui->telephone_client->setText(telephone);
        ui->adresse_client->setText(adresse);
        ui->gouvernorat_client->setText(gouvernorat);
        ui->delegation_client->setText(delegation);
        ui->naissance_client->setDate(naissance);
        ui->role_client->setCurrentText(role);
        ui->sexe_client->setCurrentText(sexe);

}

void MainWindow::remplir_comboBox_id_livreur()
{
    ui->id_livreur_commande->clear();
    QList<int> liste = co.ListeIdLivreur();
    for (int i = 0; i < liste.length(); i++)
    {
        ui->id_livreur_commande->addItem(QString::number(liste[i]));
    }
}
void MainWindow::remplir_comboBox_id_client()
{
    ui->id_client_commande->clear();
    QList<int> liste = co.ListeIdClient();
    for (int i = 0; i < liste.length(); i++)
    {
        ui->id_client_commande->addItem(QString::number(liste[i]));
    }
}


void MainWindow::on_bt_ajouter_commande_clicked()
{
int id_client=ui->id_client_commande->currentText().toInt();
int id_livreur=ui->id_livreur_commande->currentText().toInt();
QDate date_commande=ui->date_commande->date();
QString statut=ui->statut_commande->currentText();
QString nom_produit=ui->nom_commande->text();
QString type_produit=ui->type_commande->text();
int prix=ui->prix_commande->text().toInt();

if(nom_produit =="" || type_produit==""||prix==0)
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Tu dois remplir tous les champs"), QMessageBox::Cancel);
}
if(date_commande<QDate::currentDate())
   {
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("La date du commande ne peut pas etre au passé"), QMessageBox::Cancel);
}

commandes co(id_client, id_livreur, date_commande, statut, nom_produit, type_produit, prix);
bool test=co.ajouter();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Ajout avec succées"), QMessageBox::Cancel);
    ui->tableView_commande->setModel(co.afficher());

ui->prix_commande->clear();
ui->nom_commande->clear();
ui->type_commande->clear();
ui->id_commande->clear();

}
else
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Ajout échoué"), QMessageBox::Cancel);
}
}

void MainWindow::on_bt_modifier_commande_clicked()
{
int id_client=ui->id_client_commande->currentText().toInt();
int id_livreur=ui->id_livreur_commande->currentText().toInt();
QDate date_commande=ui->date_commande->date();
QString statut=ui->statut_commande->currentText();
QString nom_produit=ui->nom_commande->text();
QString type_produit=ui->type_commande->text();
int prix=ui->prix_commande->text().toInt();
int id_commande=ui->id_commande->text().toInt();

if(nom_produit =="" || type_produit==""||prix==0)
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Tu dois remplir tous les champs"), QMessageBox::Cancel);
    return;
}
if(date_commande<QDate::currentDate())
   {
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("La date du commande ne peut pas etre au passé"), QMessageBox::Cancel);
    return;
}

commandes co(id_commande,id_client, id_livreur, date_commande, statut, nom_produit, type_produit, prix);
bool test=co.modifier();

if(test)
{
    QMessageBox::information(nullptr, QObject::tr(""),
                          QObject::tr("Modification avec succées"), QMessageBox::Cancel);
    ui->tableView_commande->setModel(co.afficher());

ui->prix_commande->clear();
ui->nom_commande->clear();
ui->type_commande->clear();
ui->id_commande->clear();

}
else
{
    QMessageBox::critical(nullptr, QObject::tr(""),
                          QObject::tr("Modification échoué"), QMessageBox::Cancel);
}
}

void MainWindow::on_bt_supprimer_commande_clicked()
{
    int id_commande=ui->id_commande->text().toInt();
    if(id_commande==0)
    {
        QMessageBox::critical(nullptr, QObject::tr(""),
                              QObject::tr("Tu dois choisir une ligne d'apres le tableau"), QMessageBox::Cancel);
        return;
    }
    else
    {
    bool test=co.supprimer(id_commande);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr(""),
                              QObject::tr("Suppression avec succées"), QMessageBox::Cancel);
        ui->tableView_commande->setModel(co.afficher());

    ui->prix_commande->clear();
    ui->nom_commande->clear();
    ui->type_commande->clear();
    ui->id_commande->clear();
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr(""),
                              QObject::tr("Suppression échoué"), QMessageBox::Cancel);
    }
    }
}

void MainWindow::on_tableView_commande_clicked(const QModelIndex &index)
{
    //etape1: numero du ligne ! clicked !
    QAbstractItemModel* model = ui->tableView_commande->model();

        int row = index.row();
    //etape2:  table du format matrice , recuperation du donne
        QString id_commande= model->data(model->index(row, 0)).toString();
        QString id_client = model->data(model->index(row, 1)).toString();
        QString id_livreur = model->data(model->index(row, 2)).toString();
        QDate date_commande = model->data(model->index(row, 3)).toDate();
        QString statut = model->data(model->index(row, 4)).toString();
        QString  nom_produit= model->data(model->index(row, 5)).toString();
        QString type_produit = model->data(model->index(row, 6)).toString();
        QString prix_totale = model->data(model->index(row, 7)).toString();

        //etape3: insertion dans ui  ( lineEdit , comboBox)

        ui->id_client_commande->setCurrentText(id_client);
        ui->id_livreur_commande->setCurrentText(id_livreur);
        ui->date_commande->setDate(date_commande);
        ui->statut_commande->setCurrentText(statut);
        ui->nom_commande->setText(nom_produit);
        ui->type_commande->setText(type_produit);
        ui->prix_commande->setText(prix_totale);
        ui->id_commande->setText(id_commande);

}

void MainWindow::on_bt_chercher_commande_clicked()
{
    QString text=ui->chercher_commande->text();
    QString choix=ui->choix_commande->currentText();

    ui->tableView_commande->setModel(co.chercher(choix,text));
}

void MainWindow::on_bt_trier_commande_clicked()
{
    QString ordre=ui->ordre_commande->currentText();
    QString choix=ui->choix_commande->currentText();
    if(ordre=="ASCENDANT")
    ui->tableView_commande->setModel(co.tri(choix,"ASC"));
    else
        ui->tableView_commande->setModel(co.tri(choix,"DESC"));


}

void MainWindow::on_bt_refresh_commande_clicked()
{
    ui->choix_commande->setCurrentIndex(0);
    ui->chercher_commande->clear();
    ui->ordre_commande->setCurrentIndex(0);

    ui->tableView_commande->setModel(co.afficher());

}

void MainWindow::on_bt_chercher_client_clicked()
{
    QString text=ui->chercher_client->text();
    QString choix=ui->choix_client->currentText();

    ui->tableView_client->setModel(c.chercher(choix,text));
}

void MainWindow::on_bt_trier_client_clicked()
{
    QString ordre=ui->ordre_client->currentText();
    QString choix=ui->choix_client->currentText();
    if(ordre=="ASCENDANT")
    ui->tableView_client->setModel(c.tri(choix,"ASC"));
    else
        ui->tableView_client->setModel(c.tri(choix,"DESC"));
}

void MainWindow::on_bt_stat_commande_clicked()
{
    QMap<QString, int> stats = co.statistiquesParStatut();

            QPieSeries *series = new QPieSeries();
            for (auto it = stats.begin(); it != stats.end(); ++it) {
                series->append(it.key(), it.value());
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des Commandes par Statut");

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            QDialog *chartDialog = new QDialog(this);
            chartDialog->setWindowTitle("Graphique des Statistiques");
            chartDialog->setFixedSize(480, 240);
            QVBoxLayout *layout = new QVBoxLayout();
            layout->addWidget(chartView);
            chartDialog->setLayout(layout);

            chartDialog->exec();
}

void MainWindow::on_bt_stat_client_clicked()
{
    QMap<QString, int> stats = c.statistiquesParSexe();

            QPieSeries *series = new QPieSeries();
            for (auto it = stats.begin(); it != stats.end(); ++it) {
                series->append(it.key(), it.value());
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Statistiques des Clients par Sexe");

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            QDialog *chartDialog = new QDialog(this);
            chartDialog->setWindowTitle("Graphique des Statistiques");
            chartDialog->setFixedSize(480, 240);
            QVBoxLayout *layout = new QVBoxLayout();
            layout->addWidget(chartView);
            chartDialog->setLayout(layout);

            chartDialog->exec();
}

void MainWindow::on_bt_pdf_client_clicked()
{


        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView_client->model()->rowCount();
        const int columnCount = ui->tableView_client->model()->columnCount();

        out << "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
               "<title>%1</title>\n"
               "<style>\n"
               "table {\n"
               "    width: 100%;\n"
               "    border-collapse: collapse;\n"
               "}\n"
               "th, td {\n"
               "    padding: 8px;\n"
               "    text-align: left;\n"
               "    border-bottom: 1px solid #ddd;\n"
               "}\n"
               "tr:nth-child(even) {\n"
               "    background-color: #f2f2f2;\n"
               "}\n"
               "</style>\n"
               "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"
               "<center> <H1>Liste des Clients</H1></center><br/><br/>\n"
               "<img src=\"path/to/your/image.jpg\" alt=\"Description of image\" style=\"max-width: 100%; height: auto;\">\n"
               "<table>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_client->isColumnHidden(column))
            {
                out << QString("<th>%1</th>").arg(ui->tableView_client->model()->headerData(column, Qt::Horizontal).toString());
            }
        }
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr> <td>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView_client->isColumnHidden(column))
                {
                    QString data = ui->tableView_client->model()->data(ui->tableView_client->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }



        QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);//out
        doc.print(&printer);//fileName

    }

void MainWindow::on_bt_pdf_commande_clicked()
{


        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView_commande->model()->rowCount();
        const int columnCount = ui->tableView_commande->model()->columnCount();

        out << "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
               "<title>%1</title>\n"
               "<style>\n"
               "table {\n"
               "    width: 100%;\n"
               "    border-collapse: collapse;\n"
               "}\n"
               "th, td {\n"
               "    padding: 8px;\n"
               "    text-align: left;\n"
               "    border-bottom: 1px solid #ddd;\n"
               "}\n"
               "tr:nth-child(even) {\n"
               "    background-color: #f2f2f2;\n"
               "}\n"
               "</style>\n"
               "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"
               "<center> <H1>Liste des Commandes</H1></center><br/><br/>\n"
               "<img src=\"path/to/your/image.jpg\" alt=\"Description of image\" style=\"max-width: 100%; height: auto;\">\n"
               "<table>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_commande->isColumnHidden(column))
            {
                out << QString("<th>%1</th>").arg(ui->tableView_commande->model()->headerData(column, Qt::Horizontal).toString());
            }
        }
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr> <td>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView_commande->isColumnHidden(column))
                {
                    QString data = ui->tableView_commande->model()->data(ui->tableView_commande->model()->index(row, column)).toString().simplified();
                    out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }



        QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPageSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);//out
        doc.print(&printer);//fileName

    }
