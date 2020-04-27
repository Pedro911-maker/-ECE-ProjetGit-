#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "Sommet.h"
#include <vector>
#include <iostream>
#include <queue>
#include "Graphe.h"


class Sommet
{
    private:

       int m_indice;
       std::string m_nom;
       double m_x;
       double m_y;
       int orient;
       int NbreSommet;


     std::vector<Sommet*>m_sommets;
       std::vector<Sommet*>m_suiv;
    public:

        Sommet(std::string nomdefichier);

        ~Sommet();
        void afficher();

        double getX() const;
        double getY()const;
        void setX(double x);

        void setY(double y);
        void saisir(std::string nom,double x,double y,int indice);
        std::string getNom()const;
        int getIndice()const;
};


#endif// SOMMET_H
