#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->menubar->addAction(ui->actionA_propos);
    ui->bsuivant->hide(); //on cache les boutons
    ui->bprecedent->hide(); //pour pouvoir les afficher quand on ouvre un fichier
    ui->etapesBox->hide();
    image.setAttribute( Qt::WA_QuitOnClose, false ); //si on ferme la fenêtre principale, le widget sera fermé aussi

    //instanction de la classe informationsrecette
    recettes = new informationsrecette; //pas de paramètres

    //instanciation Automate + états
    etaperecette = new QStateMachine(this);
    etatDebut = new QState();
    etatEncours = new QState();
    etatFin = new QState();

    //chaine de caractère pour décrire l'état
    etatDebut->assignProperty(ui->label_etat, "text",QString::fromUtf8("Début de la lecture de la recette"));
    etatEncours->assignProperty(ui->label_etat, "text",QString::fromUtf8("Lecture de la recette en cours"));
    etatFin->assignProperty(ui->label_etat, "text",QString::fromUtf8("Fin de la lecture de la recette"));

    //on ajoute les états à l'automate
    etaperecette->addState(etatDebut);
    etaperecette->addState(etatEncours);
    etaperecette->addState(etatFin);

    //on ajoute des transitions entre les états
    etatDebut->addTransition(ui->bsuivant,SIGNAL(clicked()),etatEncours);
    etatDebut->addTransition(this,SIGNAL(changementfichier()),etatDebut);
    etatDebut->addTransition(this,SIGNAL(versencours(int)),etatEncours);
    etatDebut->addTransition(this,SIGNAL(versfin(int)),etatFin);
    etatDebut->addTransition(ui->bsuivant,SIGNAL(clicked()),etatEncours);
    etatEncours->addTransition(this,SIGNAL(changementfichier()),etatDebut);
    etatEncours->addTransition(ui->bsuivant,SIGNAL(clicked()),etatEncours);
    etatEncours->addTransition(ui->bprecedent,SIGNAL(clicked()),etatEncours);
    etatEncours->addTransition(this,SIGNAL(versdebut(int)),etatDebut);
    etatEncours->addTransition(this,SIGNAL(versfin(int)),etatFin);
    etatFin->addTransition(ui->bprecedent,SIGNAL(clicked()),etatEncours);
    etatFin->addTransition(this,SIGNAL(changementfichier()),etatDebut);
    etatFin->addTransition(this,SIGNAL(versdebut(int)),etatDebut);
    etatFin->addTransition(this,SIGNAL(versencours(int)),etatEncours);

    //tous les connections entre signaux et slots
    connect(ui->actionOuvrir, SIGNAL(triggered(bool)), this, SLOT(ouvrirfichier()));
    connect(ui->actionA_propos, SIGNAL(triggered(bool)), this, SLOT(affichermessage())); 
    connect(etatEncours,SIGNAL(entered()), this,SLOT(afficheretaperecette()));
    connect(ui->bsuivant, SIGNAL(clicked()), this, SLOT(augmenteriteration()));
    connect(ui->bprecedent, SIGNAL(clicked()), this, SLOT(diminueriteration()));
    connect(etatDebut,SIGNAL(entered()), this,SLOT(debutaffichagerecette()));
    connect(etatFin,SIGNAL(entered()), this,SLOT(etatfinal()));
    connect(this, SIGNAL(changementfichier()), ui->etapesBox, SLOT (clear()));
    connect(this, SIGNAL(finecriturejson()), this, SLOT (ecrirerecette()));
    connect(this, SIGNAL(finecriturerecette()), this, SLOT (afficherinformations()));
    connect(ui->etapesBox,SIGNAL(activated(int)),this,SLOT(selectionneretapes(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete recettes; //on désalloue car elle n'hérite d'aucune classe de Qt donc elle pas de parent
}

void MainWindow::affichermessage()
{
    QMessageBox::information(0, "A propos", "Cette application a été developpé par Irfan BOUHENAF et Romain MOLINA");
}

void MainWindow::ouvrirfichier()
{
        // on veut demander à l'utilisateur de sélectionner un fichier JSON
        // grâce à un boite de dialogue
        QString fileName = QFileDialog::getOpenFileName(this,tr("Ouvrir fichier"),
                                                        "",
                                                        tr("Fichier JSON (*.json)"));
        QFile fichier(fileName); //La classe QFile fournit une interface pour lire et écrire dans des fichiers
        QJsonParseError error;
        //Ouverture du fichier en lecture uniquement
        if(fichier.open(QFile::ReadOnly)) {
           //Récupération du contenu du fichier
           QByteArray donnees = fichier.readAll();
           //Interprétation du fichier JSON
           QJsonDocument doc = QJsonDocument::fromJson(donnees, &error);
           if(error.error != QJsonParseError::NoError)
           {
               qCritical() << "Impossible d’interpréter le fichier : " << error.errorString();
           }
           else
           {
               //on affiche la majorité du contenu du fichier JSON sélectionne pour vérifier si c'est bon
               //qDebug() << doc.isObject();

               obj=doc.object();
               //qDebug() << obj;

               //Affiche l'ensemble des données dans le fichier
                qDebug() << donnees;

           }
            //on émet ce signal quand la lecture de la recette dans la console est terminée
           emit finecriturejson();
        }
        else {
            qCritical() << "Impossible de lire le fichier : " << error.errorString();
            QMessageBox::critical(0, "Erreur", "Le fichier n'a pas été ouvert");
        }

}

void MainWindow::ecrirerecette()
{
    //liste d'ingrédients
    QString qIngredients;
    if (etaperecette->isRunning())
    {
        qIngredients.clear();
        //on emet un signal lorsque un fichier à déjà ete ouvert
        //pour remettre l'automate au début
        emit changementfichier();
    }

    for (auto value: obj.value("recipeIngredient").toArray())
    {
        qIngredients += "- ";
        qIngredients += value.toString();
        qIngredients += "\n";
    }

    //on stocke les données dns la classe informationsrecette
    //grâce à des mutateurs
    recettes->setNom(obj.value("name").toString().toStdString());
    recettes->setDescription(obj.value("description").toString().toStdString());
    recettes->setDate(obj.value("datePublished").toString().toStdString());
    recettes->setTemps(obj.value("cookTime").toString().toStdString());
    recettes->setMotcles(obj.value("keywords").toString().toStdString());
    recettes->setLienimage(obj.value("image").toString().toStdString());
    recettes->setTempsprep(obj.value("prepTime").toString().toStdString());
    recettes->setTempstotal(obj.value("totalTime").toString().toStdString());
    recettes->setCategorie(obj.value("recipeCategory").toString().toStdString());
    recettes->setLien((obj.value("url")).toString().toStdString());
    recettes->setIngredients(qIngredients.toStdString());
    recettes->setNbpers((obj.value("recipeYield")).toInt());

    emit finecriturerecette();
}

void MainWindow::afficherinformations()
{
    /*on modifie la valeur des labels pour que les textes du fichier
    JSON ouvert s'affiche grâce à la méthode setText*/
    ui->Ltitle->setText(QString::fromStdString(recettes->getNom()));
    ui->Ldescription2->setText(QString::fromStdString(recettes->getDescription()));
    ui->Lkeyword2->setText(QString::fromStdString(recettes->getMotcles()));
    ui->Ltimecook2->setText(QString::fromStdString(recettes->getTemps()));
    ui->Ldate2->setText(QString::fromStdString(recettes->getDate()));
    ui->Lingredients->setText(QString::fromStdString(recettes->getIngredients()));
    ui->Lprep2->setText(QString::fromStdString(recettes->getTempsprep()));
    ui->Ltotal2->setText(QString::fromStdString(recettes->getTempstotal()));
    ui->Lcategory2->setText(QString::fromStdString(recettes->getCategorie()));
    ui->Llink2->setText("<a href=\""+QString::fromStdString(recettes->getLien())+"\">Cliquez pour voir la recette !</a>" );
    QUrl imageUrl(QString::fromStdString(recettes->getLienimage()));
    ui->Lnbpers->setText(QString("Pour ")+=QString::number(recettes->getNbpers())+=QString(" personnes : "));


    //instanciation
    telechargeimage = new TelechargeFichier(imageUrl, this);

    //Si les données sont vides, on affiche un texte dans les labels
    if (QString::fromStdString(recettes->getDescription())=="")
         ui->Ldescription2->setText("Pas de description");
    if (QString::fromStdString(recettes->getTemps())=="")
         ui->Ltimecook2->setText("Temps de cuisson non renseigné");
    if (QString::fromStdString(recettes->getDate())=="")
         ui->Ldate2->setText("Date de publication non renseignée");
    if (QString::fromStdString(recettes->getMotcles())=="")
         ui->Lkeyword2->setText("Pas de mots clés");
    if (QString::fromStdString(recettes->getIngredients())=="")
         ui->Lkeyword2->setText("Ingrédients non rensignés");
    if (QString::fromStdString(recettes->getTempsprep())=="")
         ui->Lprep2->setText("Temps de préparation non renseigné");
    if (QString::fromStdString(recettes->getTempstotal())=="")
         ui->Ltotal2->setText("Temps total non renseigné");
    if (QString::fromStdString(recettes->getCategorie())=="")
         ui->Lcategory2->setText("Catégorie non renseignée");
    if (QString::fromStdString(recettes->getLien())=="")
         ui->Llink2->setText("Pas de lien");
    if (QString::number(recettes->getNbpers())==0)
         ui->Lnbpers->setText("Nombre de personnes non rensignée");
    if (QString::fromStdString(recettes->getLienimage())=="")
    {
        if (image.isVisible())
            image.close();
        QMessageBox::critical(0, "Erreur", "L'image n'existe pas !"); //on affiche un messge d'erreur quand l'image n'existe pas (càd pas de lien)
    }
    else
    {
        //quand l'image est téléchargé, le slot est déclenché
        connect(telechargeimage, SIGNAL (telecharge()), this, SLOT (afficherimage()));
    }

    //on remplit la QComboBox selon la recette choisie
    for (int i=0; i<obj.value("recipeInstructions").toArray().size();++i)
    {
        QString temp="Etape n° ";
        int i2=i+1;
        temp+=QString::number(i2);
        ui->etapesBox->addItem(temp);
    }

    //si l'automate n'est pas en marche
    if (!etaperecette->isRunning())
    {
        //état initial
        etaperecette->setInitialState(etatDebut);
        //lancement de l'automate
        etaperecette->start();
    }

}

void MainWindow::afficherimage()
{
    //La classe QPixmap est une représentation d'image hors écran.
    QPixmap pixmapImage;
    //on charge une pixmap à partir des données téléchargées
    pixmapImage.loadFromData(telechargeimage->donneetelecharge());
    image.setPixmap(pixmapImage);
    //on change le titre de la fenêtre
    image.setWindowTitle(obj.value("name").toString());
    //si l'ordinateur suporte le SSL (la Couche de sockets sécurisée)
    if(QSslSocket::supportsSsl())
        image.show(); //on affiche l'image télechargée
    else
        QMessageBox::critical(0, "Erreur", "L'image ne veut pas s'ouvrir !");

}

void MainWindow::debutaffichagerecette()
{
    //liste des étapes de la réalisation de la recette
    QString qListeEtapes;
    recettes->setNumpage(obj.value("recipeInstructions").toArray().first().toInt());
    ui->etapesBox->setCurrentIndex(recettes->getNumpage());
    //on affiche les boutons servant pour l'automate
    ui->bsuivant->show();
    ui->bprecedent->show();
    ui->etapesBox->show();
    ui->bsuivant->setEnabled(true);
    ui->bprecedent->setEnabled(false);
    //on remplit la liste d'étapes de la réalisation de la recette grâce à une boucle for
    for (auto value: obj.value("recipeInstructions").toArray())
    {
        qListeEtapes += value.toString();
    }
    //on modifie la donnée membre "page"
    recettes->setPage(qListeEtapes.toStdString());
    //on modifie la donnée membre "etape"
    recettes->setEtape(obj.value("recipeInstructions").toArray().first().toString().toStdString());
    //on affiche sur l'application grâce au label "Letapes" en accèdant au donnée membre "etape"
    ui->Letapes->setText(QString::fromStdString(recettes->getEtape()));

}

void MainWindow::augmenteriteration()
{
    //on parcourt les instructions de la recette
    recettes->setNumpage(recettes->getNumpage()+1);
}

void MainWindow::diminueriteration()
{
    //on parcourt les instructions de la recette
    recettes->setNumpage(recettes->getNumpage()-1);
    //on change d'état quand on atteint la première case du tableau
    if (recettes->getNumpage()==obj.value("recipeInstructions").toArray().first().toInt())
          emit versdebut(recettes->getNumpage());
}

void MainWindow::afficheretaperecette()
{
    if (recettes->getNumpage()>0)
    {
        ui->bprecedent->setEnabled(true);
        //si on n'atteint pas la fin du tableau d'instructions
        if (recettes->getNumpage()!=recettes->getNbpages())
        {
            //on parcourt le tableau de tableau d'instructions de la recette en grâce à son incrémentation
            recettes->setEtape(obj.value("recipeInstructions").toArray()[recettes->getNumpage()].toString().toStdString());
            //on parcourt la liste déroulante
            ui->etapesBox->setCurrentIndex(recettes->getNumpage());
            ui->bsuivant->setEnabled(true);
        }
        else
            emit versfin(recettes->getNumpage()); //signal émis quand on atteint la fin du tableau d'instructions
    }
    ui->Letapes->setText(QString::fromStdString(recettes->getEtape()));
    recettes->setNbpages(obj.value("recipeInstructions").toArray().size());

}

void MainWindow::etatfinal()
{
    //on active le bouton bprecedent
    ui->bprecedent->setEnabled(true);
    //on désactive le bouton bsuivant
    ui->bsuivant->setEnabled(false);
}

void MainWindow::selectionneretapes(int etape)
{

    if(ui->etapesBox->currentIndex()==etape)
    {
        //on change de page en fonction de l'index cliqué
        recettes->setNumpage(etape);
        //on modifie la donnée membre "etape" avec la première case du tableau d'instructions
        recettes->setEtape(obj.value("recipeInstructions").toArray()[etape].toString().toStdString());

        ui->Letapes->setText(QString::fromStdString(recettes->getEtape()));

        if ((etape>0) and (etape<obj.value("recipeInstructions").toArray().size()-1))
            emit versencours(etape); //signal émis quand on est en train de parcourir tableau d'instructions
        //si on est à la dernière case du tableau
        if (etape==obj.value("recipeInstructions").toArray().size()-1)
            emit versfin(etape); //signal émis quand on est à la fin du tableau d'instructions
        //si on est à la dernière cas du tableau
        if (etape==0)
            emit versdebut(etape); //signal émis quand on est au début du tableau d'instructions
    }

}


