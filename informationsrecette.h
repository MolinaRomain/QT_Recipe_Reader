/*! \mainpage My Personal Index Page
 * Voici la page d'accueil du projet QT fait par BOUHENAF Irfan et MOLINA Romain, en espérant que vous passiez un bon moment ainsi qu'une bonne lecture
 *
 */

#ifndef INFORMATIONSRECETTE_H
#define INFORMATIONSRECETTE_H
#include <string>
/**
* \file  informationsrecette.h
* \author { Irfan BOUHENAF, Romain MOLINA }
*/
/**
 * \brief      Cette classe sert à stocker les données contenues dans les fichiers JSON
 */
class informationsrecette
{
private:
    /**
     * Nom de la recette
     */
    std::string nom;
    /**
     * Une description de la recette
     */
    std::string description;
    /**
     * temps de cuisson pour la recette
     */
    std::string temps;
    /**
     * Date de sortie de la recette
     */
    std::string date;
    /**
     * Mots clés de la recette
     */
    std::string motcles;
    /**
     * lien d'une image montrant la recette
     */
    std::string lienimage;
    /**
     * Ingrédients de la recette
     */
    std::string ingredients;
    /**
     * Nombre de pages de la recette
     */

    size_t nbpages;
    /**
     * Temps de préparation 
     */

    std::string tempsprep;
    /**
     * Temps total
     */

    std::string tempstotal;
    /**
     * Catégorie de la recette
     */

    std::string categorie;
    /**
     * Lien de la recette
     */

    std::string lien;
    /**
     * Liste contenant les instructions à faire pour la réalisation de la recette
     */

    std::string page;
    /**
     * Nombre de personnes pour la recette
     */


    int nbpers;
    /**
     * étape de la réalisation de la recette
     */

    std::string etape;
    /**
     * Numéro de la page
     */

    int numpage;




public:
    
    /**
     * \fn informationsrecette()
     * \brief Constructeur de l'objet
     */
    informationsrecette();
    /**
     * \fn ~informationsrecette()
     * \brief      Détruit l'object.
     */
    ~informationsrecette();
    /**
     * \fn std::string getNom() const
     * \brief      Récupere le nom
     *
     * \return     Le nom.
     */
    std::string getNom() const;
    /**
     * \fn         void setNom(const std::string &value)
     * \brief      Change le nom
     *
     * \param[in]  value  La valeur
     */
    void setNom(const std::string &value);
    /**
     * \fn         std::string getTemps() const
     * \brief      Récupere le temps.
     *
     * \return     Le temps.
     */
    std::string getTemps() const;
    /**
     * \fn         void setTemps(const std::string &value)
     * \brief      Change la valeur du temps
     *
     * \param[in]  value  La valeur
     */
    void setTemps(const std::string &value);
    /**
     * \fn         std::string getDescription() const
     * \brief      Récupere la description
     *
     * \return     La description.
     */
    std::string getDescription() const;
    /**
     * \fn         void setDescription(const std::string &value)
     * \brief      Change la description
     *
     * \param[in]  value  La valeur
     */
    void setDescription(const std::string &value);
    /**
     * \fn         std::string getMotcles() const
     * \brief      Récupere les motclé
     *
     * \return     Les motcles.
     */
    std::string getMotcles() const;
    /**
     *\fn          void setMotcles(const std::string &value)
     * \brief      Change les motclés
     *
     * \param[in]  value  La valeur
     */
    void setMotcles(const std::string &value);
    /**
     * \fn         std::string getLienimage() const
     * \brief      Recupere le lien de l'image.
     *
     * \return     Le lien de l'image
     */
    std::string getLienimage() const;
    /**
     * \fn         void setLienimage(const std::string &value)
     * \brief      Change le lien de l'image
     *
     * \param[in]  value  La valeur
     */
    void setLienimage(const std::string &value);
    /**
     * \fn         std::string getDate() const
     * \brief      Récupere la date
     *
     * \return     La date.
     */
    std::string getDate() const;
    /**
     * \fn         void setDate(const std::string &value);
     * \brief      Change la date
     *
     * \param[in]  La valeur
     */
    void setDate(const std::string &value);
    /**
     * \fn         std::string getIngredients() const
     * \brief      Récupere les ingrédients
     *
     * \return     Les ingredients.
     */
    std::string getIngredients() const;
    /**
     * \fn         void setIngredients(const std::string &value)
     * \brief      Change les incrédients
     *
     * \param[in]  value  La valeur
     */
    void setIngredients(const std::string &value);
    /**
     * \fn         int getNbpages() const
     * \brief      Recupere le nombres de pages
     *
     * \return     Le nombre de pages.
     */
    int getNbpages() const;
    /**
     * \fn         void setNbpages(int value)
     * \brief      Change le nombre de pages
     *
     * \param[in]  value  La valeur
     */
    void setNbpages(int value);
    /**
     * \fn         std::string getTempsprep() const
     * \brief      Recupère le temps de préparation
     *
     * \return     Le temps de préparation
     */
    std::string getTempsprep() const;
    /**
     * \fn         void setTempsprep(const std::string &value)
     * \brief      Change le temps de préparation
     *
     * \param[in]  value  La valeur
     */
    void setTempsprep(const std::string &value);
    /**
     * \fn         std::string getTempstotal() const
     * \brief      Recupère le temps total
     *
     * \return     Le temps total.
     */
    std::string getTempstotal() const;
    /**
     * \fn         void setTempstotal(const std::string &value)
     * \brief      Change le temps total
     *
     * \param[in]  value  la valeur
     */
    void setTempstotal(const std::string &value);
    /**
     * \fn         std::string getCategorie() const
     * \brief      Récupère la catégorie
     *
     * \return     La catégorie.
     */
    std::string getCategorie() const;
    /**
     * \fn         void setCategorie(const std::string &value)
     * \brief      Change la catégorie
     *
     * \param[in]  value  La valeur 
     */
    void setCategorie(const std::string &value);
    /**
     * \fn         std::string getLien() const
     * \brief      Récupère le lien
     *
     * \return     Le lien.
     */
    std::string getLien() const;
    /**
     * \fn         void setLien(const std::string &value)
     * \brief      Change le lien.
     *
     * \param[in]  value  La valeur
     */
    void setLien(const std::string &value);
    /**
     * \fn         std::string getPage() const
     * \brief      Récupère la liste  d'étapes de réalisation de la recette
     *
     * \return     La liste.
     */
    std::string getPage() const;
    /**
     * \fn         void setPage(const std::string &value)
     * \brief      Change la liste  d'étapes de réalisation de la recette
     *
     * \param[in]  value  La valeur
     */
    void setPage(const std::string &value);
    /**
     * \fn         int getNbpers() const
     * \brief      Recupère le nombre de personnes
     *
     * \return     le nombre de personne.
     */
    int getNbpers() const;
    /**
     * \fn         void setNbpers(int value)
     * \brief      Change le nombre de personne
     *
     * \param[in]  value  La  valeur
     */
    void setNbpers(int value);
    /**
     * \fn         std::string getEtape() const
     * \brief      Récupère une étape de la réalisation de la recette
     *
     * \return     l'étape
     */
    std::string getEtape() const;
    /**
     * \fn         void setEtape(const std::string &value)
     * \brief      Change une étape de la réalisation de la recette
     *
     * \param[in]  value  La  valeur
     */
    void setEtape(const std::string &value);
    /**
     * \fn         int getNumpage() const
     * \brief      Recupère le numéro de la page
     *
     * \return     le numéro de la page.
     */
    int getNumpage() const;
    /**
     * \fn         void setNumpage (int value)
     * \brief      Change le numéro de la page
     *
     * \param[in]  value  La  valeur
     */
    void setNumpage(int value);
};

#endif // INFORMATIONSRECETTE_H
