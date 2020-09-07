#include "informationsrecette.h"

std::string informationsrecette::getMotcles() const
{
    return motcles;
}

void informationsrecette::setMotcles(const std::string &value)
{
    motcles = value;
}

std::string informationsrecette::getLienimage() const
{
    return lienimage;
}

void informationsrecette::setLienimage(const std::string &value)
{
    lienimage = value;
}

std::string informationsrecette::getDate() const
{
    return date;
}

void informationsrecette::setDate(const std::string &value)
{
    date = value;
}

std::string informationsrecette::getIngredients() const
{
    return ingredients;
}

void informationsrecette::setIngredients(const std::string &value)
{
    ingredients = value;
}

int informationsrecette::getNbpages() const
{
    return nbpages;
}

void informationsrecette::setNbpages(int value)
{
    nbpages = value;
}

std::string informationsrecette::getPage() const
{
    return page;
}

void informationsrecette::setPage(const std::string &value)
{
    page = value;
}

std::string informationsrecette::getTempsprep() const
{
    return tempsprep;
}

void informationsrecette::setTempsprep(const std::string &value)
{
    tempsprep = value;
}

std::string informationsrecette::getTempstotal() const
{
    return tempstotal;
}

void informationsrecette::setTempstotal(const std::string &value)
{
    tempstotal = value;
}

std::string informationsrecette::getCategorie() const
{
    return categorie;
}

void informationsrecette::setCategorie(const std::string &value)
{
    categorie = value;
}

std::string informationsrecette::getLien() const
{
    return lien;
}

void informationsrecette::setLien(const std::string &value)
{
    lien = value;
}


int informationsrecette::getNbpers() const
{
    return nbpers;
}

void informationsrecette::setNbpers(int value)
{
    nbpers = value;
}

std::string informationsrecette::getEtape() const
{
    return etape;
}

void informationsrecette::setEtape(const std::string &value)
{
    etape = value;
}

int informationsrecette::getNumpage() const
{
    return numpage;
}

void informationsrecette::setNumpage(int value)
{
    numpage = value;
}

informationsrecette::informationsrecette()
{
    
}

informationsrecette::~informationsrecette()
{
    
}

std::string informationsrecette::getNom() const
{
    return nom;
}

void informationsrecette::setNom(const std::string &value)
{
    nom = value;
}


std::string informationsrecette::getTemps() const
{
    return temps;
}

std::string informationsrecette::getDescription() const
{
    return description;
}

void informationsrecette::setDescription(const std::string &value)
{
    description = value;
}

void informationsrecette::setTemps(const std::string &value)
{
    temps = value;
}


