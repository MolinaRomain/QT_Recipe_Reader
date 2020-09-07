#ifndef TELECHARGEFICHIER_H
#define TELECHARGEFICHIER_H
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


/**
 * \brief      Cette classe permet de télécharger une image grâce a un lien internet
 */
class TelechargeFichier : public QObject
{
 Q_OBJECT
 public:
  /**
   * \brief      Constructeur
   *
   * \param[in]  imageUrl  L'url d'une image
     * \param      parent    Le parent (la fenêtre)
   */
      explicit TelechargeFichier(QUrl imageUrl, QObject *parent = 0);
    /**
     * \brief      Destructeur virtuel
    */
      virtual ~TelechargeFichier();
    /**
     * \brief      { Fonction qui retourne un tableau d'octets }
     *
     * \return     Un tableau d'octets contenant les données téléchargés
    */
      QByteArray donneetelecharge() const;

 signals:
  /**
   * \brief      { function_description }
  */
        void telecharge();

 private slots:
  /**
   * \brief      { function_description }
   *
     * \param      pReply  Les données
  */
        void fichiertelecharge(QNetworkReply* donnees);

 private:
  /**
   * { item_description }
  */
      QNetworkAccessManager web;
    /**
     * { item_description }
    */
      QByteArray b_donneetelecharge;
};

#endif // TELECHARGEFICHIER_H
