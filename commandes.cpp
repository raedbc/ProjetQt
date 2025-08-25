#include "commandes.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <qDebug>
commandes::commandes()
{
    this->id_commande = 0;
     this->id_client  = 0;
     this->id_livreur  =0;
     this-> date_commande =QDate::currentDate();
     this-> statut ="";
     this-> nom_produit ="";
      this->type_produit ="";
     this->prix_totale  =0;
}
commandes::commandes(int id_commande,int id_client,int id_livreur,QDate date_commande,QString statut,QString nom_produit,QString type_produit,int prix_totale)
{
    this->id_commande = id_commande;
     this->id_client  = id_client;
     this->id_livreur  =id_livreur;
     this-> date_commande =date_commande;
     this-> statut =statut;
     this-> nom_produit =nom_produit;
      this->type_produit =type_produit;
     this->prix_totale  =prix_totale;

}

commandes::commandes(int id_client,int id_livreur,QDate date_commande,QString statut,QString nom_produit,QString type_produit,int prix_totale)
{
     this->id_client  = id_client;
     this->id_livreur  =id_livreur;
     this-> date_commande =date_commande;
     this-> statut =statut;
     this-> nom_produit =nom_produit;
      this->type_produit =type_produit;
     this->prix_totale  =prix_totale;
}

bool commandes::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO COMMANDES (id_client,id_livreur,date_commande,statut,nom_produit,type_produit,prix_totale)"
              "VALUES (:id_client,:id_livreur,:date_commande,:statut,:nom_produit,:type_produit,:prix_totale)");

query.bindValue(":id_client",id_client);
query.bindValue(":id_livreur",id_livreur);
query.bindValue(":date_commande",date_commande);
query.bindValue(":statut",statut);
query.bindValue(":nom_produit",nom_produit);
query.bindValue(":type_produit",type_produit);
query.bindValue(":prix_totale",prix_totale);

return query.exec();

}

bool commandes::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE COMMANDES SET id_client=:id_client,"
                  "id_livreur=:id_livreur,date_commande=:date_commande,"
                  "statut=:statut,nom_produit=:nom_produit,type_produit=:type_produit,"
                  "prix_totale=:prix_totale WHERE ID_COMMANDE=:id_commande");

    query.bindValue(":id_client",id_client);
    query.bindValue(":id_livreur",id_livreur);
    query.bindValue(":date_commande",date_commande);
    query.bindValue(":statut",statut);
    query.bindValue(":nom_produit",nom_produit);
    query.bindValue(":type_produit",type_produit);
    query.bindValue(":prix_totale",prix_totale);
    query.bindValue(":id_commande",id_commande);


    return query.exec();

}
bool commandes::supprimer(int id_commande)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDES WHERE ID_COMMANDE=:id_commande");
    query.bindValue(":id_commande",id_commande);
    return query.exec();
}


QSqlQueryModel* commandes::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM COMMANDES");
return model;
}

QSqlQueryModel* commandes::chercher(QString column,QString text)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM COMMANDES WHERE "+column+ " LIKE '%"+text+"%'");// WHERE NOM_PRODUIT LIKE '%PC%'
return model;
}

QSqlQueryModel* commandes::tri(QString column,QString ordre)
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM COMMANDES  ORDER BY "+column+" "+ordre);// ORDER BY column ASC
return model;
}

QList<int> commandes::ListeIdClient()
{
QList<int> list;
QSqlQuery query;
query.prepare("SELECT ID_CLIENT FROM CLIENTS");
if(query.exec())
{
 while(query.next())
 {
int id_client=query.value(0).toInt();//id_client=1;
list.append(id_client);

 }
}
return list;


}

QList<int> commandes::ListeIdLivreur()
{
QList<int> list;
QSqlQuery query;
query.prepare("SELECT ID_LIVREUR FROM LIVREURS");
if(query.exec())
{
 while(query.next())
 {
int id_livreur=query.value(0).toInt();//id_livreur=1;
list.append(id_livreur);

 }
}
return list;


}


QMap<QString, int> commandes::statistiquesParStatut() {
    QMap<QString, int> StatutStats;

    QSqlQuery query;
    query.prepare("SELECT STATUT, COUNT(*) as count FROM COMMANDES GROUP BY STATUT");
    if (query.exec()) {
        while (query.next()) {
            QString statut = query.value(0).toString();//En attente
            int count = query.value(1).toInt();//2
            StatutStats[statut] = count;
        }
    }

    return StatutStats;
}
