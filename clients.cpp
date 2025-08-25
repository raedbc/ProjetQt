#include "clients.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
clients::clients()
{
    this->id_client=0;
    this->nom="";
    this->prenom="";
    this->email="";
    this->telephone="";
    this->adresse="";
    this->date_naissance=QDate::currentDate();
    this->gourvernorat="";
    this->delegation="";
    this->sexe="";
    this->role="";

}
clients::clients(int id_client, QString nom,QString prenom,QString email,QString telephone,QString adresse,QDate date_naissance,QString gourvernorat,QString delegation,QString role,QString sexe)
{
    this->id_client=id_client;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->telephone=telephone;
    this->adresse=adresse;
    this->date_naissance=date_naissance;
    this->gourvernorat=gourvernorat;
    this->delegation=delegation;
    this->sexe=sexe;
    this->role=role;

}
clients::clients(QString nom,QString prenom,QString email,QString telephone,QString adresse,QDate date_naissance,QString gourvernorat,QString delegation,QString role,QString sexe)
{
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->telephone=telephone;
    this->adresse=adresse;
    this->date_naissance=date_naissance;
    this->gourvernorat=gourvernorat;
    this->delegation=delegation;
    this->sexe=sexe;
    this->role=role;

}


bool clients::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO CLIENTS (nom,prenom,email,telephone,adresse,date_de_naissance,gouvernorat,delegation,role,sexe)"
              " VALUES (:nom,:prenom,:email,:telephone,:adresse,:date_naissance,:gouvernorat,:delegation,:role,:sexe)");

query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":email",email);
query.bindValue(":telephone",telephone);
query.bindValue(":adresse",adresse);
query.bindValue(":date_naissance",date_naissance);
query.bindValue(":gouvernorat",gourvernorat);
query.bindValue(":delegation",delegation);
query.bindValue(":role",role);
query.bindValue(":sexe",sexe);


bool test=query.exec();
if(test)
    return true;
else
    return false;


}

bool clients::modifier()
{
QSqlQuery query;
query.prepare("UPDATE CLIENTS SET nom=:nom ,prenom=:prenom,email=:email,telephone=:telephone,adresse=:adresse,"
              "date_de_naissance=:date_naissance,gouvernorat=:gouvernorat,delegation=:delegation,role=:role,sexe=:sexe"
              "   WHERE ID_CLIENT=:id_client");

query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":email",email);
query.bindValue(":telephone",telephone);
query.bindValue(":adresse",adresse);
query.bindValue(":date_naissance",date_naissance);
query.bindValue(":gouvernorat",gourvernorat);
query.bindValue(":delegation",delegation);
query.bindValue(":role",role);
query.bindValue(":sexe",sexe);
query.bindValue(":id_client",id_client);


bool test=query.exec();
if(test)
    return true;
else
    return false;
}

bool clients::supprimer(int id_client)
{
QSqlQuery query;
query.prepare("DELETE FROM CLIENTS WHERE ID_CLIENT=:id_client");
query.bindValue(":id_client",id_client);

bool test=query.exec();
if(test)
    return true;
else
    return false;
}

QSqlQueryModel* clients::afficher()
{
    //creation objet !!
QSqlQueryModel* model=new QSqlQueryModel();
 // appel du requet et inserer le resultat dans la nouvelle objet !!
model->setQuery("SELECT * FROM CLIENTS");

//retour du objet
return model;



}


QSqlQueryModel* clients::chercher(QString column,QString text)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM CLIENTS WHERE "+column+ " LIKE '%"+text+"%'");// WHERE NOM_PRODUIT LIKE '%PC%'
return model;
}

QSqlQueryModel* clients::tri(QString column,QString ordre)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM CLIENTS  ORDER BY "+column+" "+ordre);// ORDER BY column ASC
return model;
}

QMap<QString, int> clients::statistiquesParSexe() {
    QMap<QString, int> SexeStats;

    QSqlQuery query;
    query.prepare("SELECT Sexe, COUNT(*) as count FROM CLIENTS GROUP BY Sexe");
    if (query.exec()) {
        while (query.next()) {
            QString Sexe = query.value(0).toString();//Homme
            int count = query.value(1).toInt();//2
            SexeStats[Sexe] = count;
        }
    }

    return SexeStats;
}
