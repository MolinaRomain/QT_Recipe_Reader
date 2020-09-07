#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "telechargefichier.h"
#include "informationsrecette.h"
#if QT_VERSION >= 0x050100 //on inclut toutes les classes de Qt
#include <QtWidgets> /* tous les widgets de Qt5 */
#else
#include <QtGui> /* tous les widgets de Qt4 */
#endif
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/**
*\file mainwindow.h
*\author { Irfan BOUHENAF, Romain MOLINA }
*/


/**
 * \brief      Cette classe génère la fenêtre princiaple de l'application */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * \brief      Constructeur de l'objet
     *
     * \param      parent  Le parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * \brief      Détruit l'objet
     */
    ~MainWindow();


private:
    /**
     * On utilise Qt designer pour que la disposition des layouts soit optimisée
     */
    Ui::MainWindow *ui;
    /**
     * pointeur sur TelechargeFichier pour afficher l'image avec la fenêtre principale
     */
    TelechargeFichier * telechargeimage;
    /**
     * pointeur sur informationsrecette pour pouvoir stocker les données contenue dans fichiers JSON
     */
    informationsrecette * recettes;
    /**
     * Donnée membre permettant de manipuler les données du fichier Json
     */
    QJsonObject obj;
    /**
     * Widget pour afficher l'image
     */
    QLabel image;
    /**
     * { L'Automate }
     */   
    QStateMachine * etaperecette;
    /**
     * { Etat initial de la machine à états }
     */
    QState * etatDebut;
    /**
     * { Etat quand on parcours le tableau }
     */
    QState * etatEncours;
    /**
     * { Quand on fini de lire les étapes de la réalisation de la recette }
     */
    QState * etatFin;


    signals:
    /**
     * \fn void finecriturejson()
     * \brief affiche les donnéees du fichier dnas la console, émet un signal à la fin
     */
    void finecriturejson();
    /**
     * \fn         void finecriturerecette()
     * \brief      Est émit  à la fin du slot ecrirerecette
     */
    void finecriturerecette();
    /**
     * \fn          void changementetat()
     * \brief      Si on ouvre une autre recette quelque soit l'état de la recette précédent on repasse à l'état du début
     */

    void changementfichier();
    /**
     * \fn         void versencours(int)
     * \brief      On passe de l'étape étatdebut à étatencours ou de étatfin à étatencours
     *
     * \param[in]  <int>  { Position dans le tableau }
     */

    void versencours(int);
    /**
     * \fn         void versfin(int)
     * \brief      Passe de l'étape etatencours à etatfin ou de etatencours à etatfin
     *
     * \param[in]  <int>  { Position dans le tableau }
     */
    void versfin(int);
    /**
     * \fn         void versdebut(int)
     * \brief      On passe de l'étape etatfin à etatdebut ou de etatencours à etatdebut
     *
     * \param[in]  <int>  { Position dans le tableau }
     */
    void versdebut(int);


    public slots:
    /**
     *\fn         void ouvrirfichier()
     *\brief      Permet d'ouvrir un fichier et de lire son contenu dans la console
     */
    void ouvrirfichier();
    /**
     *\fn          void afficherimage()
     * \brief      Permet d'afficher l'image
     */
    void afficherimage();
    /**
     * \fn         void ecrirerecette()
     * \brief      Permet de stocker les données de la recette
     */
    void ecrirerecette();
    /**
     * \fn         void afficherinformations()
     * \brief      Permet d'afficher les informations de la recette qui ont été stockées
     */
    void afficherinformations();
    /**
     * \fn         
     * \brief      Permet d'afficher un message d'information en cliquant sur " A propos"
     */
    void affichermessage();

    /**
     * \brief      Permet d'afficher les étapes de la recette
     */
    void afficheretaperecette();
    /**
     * \brief      Augmenter le nombre d'itérations
     */
    void augmenteriteration();
    /**
     * \brief      Diminuer le nombre d'itérations
     */
    void diminueriteration();
    /**
     * \brief      Fonction déclenchée quand l'état est sur etatDebut
     */
    void debutaffichagerecette();
    /**
     * \brief      { Permet de selectionner la n étape de recettes }
     *
     * \param[in]  <int>  { Permet de choisir l'étape de la recette }
     */
    void selectionneretapes(int);
    /**
     * \brief      { Fonction déclenchée quand l'état est sur etatFin }
     */

    void etatfinal();
};
#endif // MAINWINDOW_H
