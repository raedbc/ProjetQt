#ifndef COMMANDES_H
#define COMMANDES_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class commandes
{
public:
    commandes();
    commandes(int id_commande,int id_client,int id_livreur,QDate date_commande,QString statut,QString nom_produit,QString type_produit,int prix_totale);
    commandes(int id_client,int id_livreur,QDate date_commande,QString statut,QString nom_produit,QString type_produit,int prix_totale);

    // Getters
      int getIdCommande() const { return id_commande; }
      int getIdClient() const { return id_client; }
      int getIdLivreur() const { return id_livreur; }
      QDate getDateCommande() const { return date_commande; }
      QString getStatut() const { return statut; }
      QString getNomProduit() const { return nom_produit; }
      QString getTypeProduit() const { return type_produit; }
      double getPrixTotale() const { return prix_totale; }

      // Setters
      void setIdCommande(int id) { id_commande = id; }
      void setIdClient(int id) { id_client = id; }
      void setIdLivreur(int id) { id_livreur = id; }
      void setDateCommande(QDate date) { date_commande = date; }
      void setStatut(QString s) { statut = s; }
      void setNomProduit(QString nom) { nom_produit = nom; }
      void setTypeProduit(QString type) { type_produit = type; }
      void setPrixTotale(double prix) { prix_totale = prix; }

    bool ajouter();
    bool modifier();
    bool supprimer(int id_commande);
    QSqlQueryModel* afficher();

    QSqlQueryModel* chercher(QString column,QString text);
    QSqlQueryModel* tri(QString column,QString ordre);

    QList<int> ListeIdLivreur();
    QList<int> ListeIdClient();
    QMap<QString, int> statistiquesParStatut() ;


private:
 int id_client,id_commande,id_livreur,prix_totale;
 QString statut,nom_produit,type_produit;
 QDate date_commande;
};

#endif // COMMANDES_H
