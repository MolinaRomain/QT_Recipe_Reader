#include "telechargefichier.h"

TelechargeFichier::TelechargeFichier(QUrl imageUrl, QObject *parent) :
 QObject(parent)
{

     connect( &web, SIGNAL (finished(QNetworkReply*)), this, SLOT (fichiertelecharge(QNetworkReply*)));
     //le signal finished() est émis chaque fois qu'une réponse réseau se termine
     QNetworkRequest requete(imageUrl); //constructeur de classe avec une QUrl pour pouvoir l'utiliser une ligne en dessous
     web.get(requete); //cela permet de récuperer un fichier grâce à son URL (ici imageUrl)
}

TelechargeFichier::~TelechargeFichier() { }

void TelechargeFichier::fichiertelecharge(QNetworkReply* donnee) {
     b_donneetelecharge = donnee->readAll(); //on lit les données de l'image (fonction de la classe QIODevice, QtNeworkReply hérite de cette classe)
     donnee->deleteLater();
     emit telecharge();
}

QByteArray TelechargeFichier::donneetelecharge() const {
    return b_donneetelecharge;
}
