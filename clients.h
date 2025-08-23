#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class clients
{
public:
    clients();
    clients( QString nom,QString prenom,QString email,QString telephone,QString adresse,QDate date_naissance,QString gourvernorat,QString delegation,QString role,QString sexe);
clients(int id_client, QString nom,QString prenom,QString email,QString telephone,QString adresse,QDate date_naissance,QString gourvernorat,QString delegation,QString role,QString sexe);

int getIdClient()
{return id_client;}
void setIdClient(int id_client)
{this->id_client=id_client;}

QString getNom()
{return nom;}
void setNom(QString nom)
{this->nom=nom;}

QString getPrenom()
{return prenom;}
void setPrenom(QString prenom)
{this->prenom=prenom;}

QString getEmail()
{return email;}
void setEmail(QString email)
{this->email=email;}

QString getTelephone()
{return telephone;}
void setIdClient(QString telephone)
{this->telephone=telephone;}

QString getAdresse()
{return adresse;}
void setAdresse(QString adresse)
{this->adresse=adresse;}

QDate getDateNaissance()
{return date_naissance;}
void setIdClient(QDate date_naissance)
{this->date_naissance=date_naissance;}

QString getGourvernorat()
{return gourvernorat;}
void setGourvernorat(QString gourvernorat)
{this->gourvernorat=gourvernorat;}

QString getDelegation()
{return delegation;}
void setDelegation(QString delegation)
{this->delegation=delegation;}

QString getRole()
{return role;}
void setRole(QString role)
{this->role=role;}

QString getSEXE()
{return sexe;}
void setSexe(QString sexe)
{this->sexe=sexe;}


bool ajouter();
bool modifier();
bool supprimer(int id_client);
QSqlQueryModel* afficher();

QSqlQueryModel* chercher(QString column,QString text);
QSqlQueryModel* tri(QString column,QString ordre);

 private:
int id_client;
QString nom,prenom,email,telephone,adresse,gourvernorat,delegation,sexe,role;
QDate date_naissance;

};

#endif // CLIENTS_H
