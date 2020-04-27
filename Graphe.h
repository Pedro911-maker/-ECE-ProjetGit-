
#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <queue>
#include <vector>
#include "Sommet.h"
#include "Graphe.h"
#include <string>

class Graphe
{
    private:
        int m_orient;
        int m_taille;


    public:
       Graphe();
        ~Graphe();
      void afficher();

        void afficherCheminPlusCourt(int num, std::vector<int>& poids);
        void algoDijkstra(unsigned depart, int arrivee);
        void saisir(std::string nom,double x,double y,int indice);
        void trouverDepartArrivee(int* depart, int* arrivee);
};

#endif// GRAPHE_H
