#include <fstream>
#include "Sommet.h"
#include "Graphe.h"
#include <string>
#include <iostream>
#include <queue>

Sommet::Sommet(std::string nomdufichier)
{
    std::ifstream ifs{nomdufichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomdufichier );

bool orient;

        ifs >> orient;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");
      //l'id
        ifs >> NbreSommet;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");

for (int i=0; i<NbreSommet ; i++)
{


    ifs >> m_indice;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture d'indice du sommet");

    ifs >> m_nom;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture d'indice du sommet");

    ifs >> m_x;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture de coord x du sommet");

    ifs >> m_y;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture de coord y du sommet");


    }
}
Sommet::~Sommet()
{


    for (int i=0;i<m_sommets.size();i++)
        delete &m_sommets;

}

double Sommet::getX()const
{
    return m_x;
}
double Sommet::getY()const
{
    return m_y;
}


std::string Sommet::getNom()const
{
    return m_nom;
}
int Sommet::getIndice()const
{
    return m_indice;
}
void Sommet::saisir(std::string nom,double x,double y,int indice)
{
    m_indice=indice;
    m_x=x;
    m_y=y;
    m_nom=nom;
}

void Sommet::setX(double x)
{
    setX(x);
}
void Sommet::afficher()
{
 if(orient==false)
   std::cout << "Graphe non oriente" <<std::endl;
else
   std::cout << "Graphe oriente" <<std::endl;

    std::cout << "Il y a " << NbreSommet << " sommets :" << std::endl;
    for(unsigned i=0; i<NbreSommet; i++)
    {
      std::cout <<   m_sommets[i]->getIndice() << std::endl;
      std::cout <<  m_sommets[i]->getNom() << std::endl;
      std::cout <<  m_sommets[i]->getX()  <<std::endl;
       std::cout <<   m_sommets[i]->getY()  <<std::endl;
    }
}


void Sommet::setY(double y)
{
    setY(y);
}
