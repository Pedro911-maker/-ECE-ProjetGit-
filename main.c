#include "Graphe.h"
#include <fstream>
#include "Sommet.h"
#include <string>
#include <iostream>
#include <queue>




//constructeur du graphe avec lecture de fichier
Graphe::Graphe()
{
 /*   std::ifstream ifs{nomdefichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomdefichier );

        //on r�cup�re l'ordre


    int ordre;       //l'id
        ifs >> ordre;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture ordre du graphe");*/


/*for (int i=0; i<ordre ; i++)
{
    int m_indice;
    ifs >> m_indice;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture d'indice du sommet");
        std::string m_nom;
    ifs >> m_nom;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture d'indice du sommet");
        double m_x;
    ifs >> m_x;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture de coord x du sommet");
    double m_y;
    ifs >> m_y;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture de coord y du sommet");

    saisir(m_nom,m_x,m_y,m_indice);


        }
 /*      for(unsigned i=0; i<m_sommets.size(); i++)
        {
            if(m_sommets[i]->getId()==temporaire)
                m_sommets[i]->ajouterAdjacent(s, temporaire3);
        }
}
   ifs>>m_taille;
   if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

for(int j=0; j<m_taille, j=++)
   {

   }



    int temporaire, temporaire2;
    double temporaire3;
    Sommet* s;
    for(int j=0; j<m_taille; j++)       //chargement des arretes
    {
        ifs >> temporaire;
        ifs >> temporaire2;
        ifs >> temporaire3;
        for(unsigned a=0; a<m_sommets.size(); a++)
        {
            if(m_sommets[a]->getId()==temporaire2)
                s = m_sommets[a];
        }
        for(unsigned i=0; i<m_sommets.size(); i++)
        {
            if(m_sommets[i]->getId()==temporaire)
                m_sommets[i]->ajouterAdjacent(s, temporaire3);
        }
  } */
}


/// Destructeur du r�seau. Les stations ont �t� allou�es dynamiquement
/// lors de la cr�ation d'une instance Graphe, le r�seau est responsable de leur lib�ration
Graphe::~Graphe()
{

}

//affiche le graphe
/*void Graphe::saisir(std::string nom,double x,double y,int indice)
{
    m_indice=indice;
    m_x=x;
    m_y=y;
    m_nom=nom;
}*/
void Graphe::afficher()
{

}
//affiche le chemin le plus court de depart a arrivee
/*void Graphe::afficherCheminPlusCourt(int num, std::vector<int>& poids)
{
    if(m_sommets[num]->getPredecesseur()!=-1)
    {
        int pred;
        for(unsigned i=0; i<m_sommets.size(); i++)
        {
            if(m_sommets[i]->getId()==m_sommets[num]->getPredecesseur())
                pred = i;
        }
        for(int i=0; i<m_sommets[pred]->getDegre(); i++)
        {
            if(m_sommets[pred]->getAdjacent(i)->getId()==m_sommets[num]->getId())
                poids.push_back(m_sommets[pred]->getPoids(i));
        }
        std::cout << m_sommets[num]->getId() << " <---------- ";

        afficherCheminPlusCourt(pred, poids);
    }
    else
    {
        int somme=0;

        std::cout << m_sommets[num]->getId() << " : ";
        for(unsigned i=0; i<poids.size(); i++)
        {
            somme+=poids[i];
            std::cout << poids[i];
            if(i!=poids.size()-1)
                std::cout << " + ";
            else
                std::cout << " = " << somme;
        }
    }

}

auto cmp = [] (std::pair<Sommet*, double> p1, std::pair<Sommet*, double> p2)
{
    return p2.second< p1.second;
};

//Algo principal de l'algo, re�oit le depart et l'arrivee
void Graphe::algoDijkstra(unsigned depart, int arrivee)
{

    for(unsigned i=0; i<m_sommets.size(); i++)  //reset des infos des sommets
    {
        m_sommets[i]->ajouterPredecesseur(-1);
        m_sommets[i]->setMarquage(0);
    }

    Sommet* s_adjacent;
    std::pair<Sommet*, double> plusProche;
    std::vector<int> poids;

    std::priority_queue<std::pair<Sommet*, double>, std::vector<std::pair<Sommet*, double>>, decltype(cmp) > file(cmp);

    m_sommets[depart]->setDistance(0);      //set la distance de depart sur 0
    file.push({m_sommets[depart], 0});      //ajoute a la file
    for(unsigned i=0; i<m_sommets.size(); i++)      //les autres sur infini
    {
        if(i!=depart)
        {
            m_sommets[i]->setDistance(INFINI);
            file.push({m_sommets[i], m_sommets[i]->getDistance()});
        }
    }
    do
    {
        do      //on r�cup�re le plus proche si il n'est pas deja marque
        {
            plusProche = file.top();
            file.pop();
        }while(plusProche.first->getMarquage()==1&&!file.empty());

        plusProche.first->setMarquage(true);       //on le marque comme visit�
        for(int i=0; i<plusProche.first->getDegre(); i++)
        {
            s_adjacent = plusProche.first->getAdjacent(i);
            if(s_adjacent->getDistance()>plusProche.second+plusProche.first->getPoids(i)&& s_adjacent->getMarquage()==0)      //si sa distance sup�rieure � la distance du predecesseur + poids entre les deux
            {

                s_adjacent->setDistance(plusProche.second+plusProche.first->getPoids(i));   //mise a jour de la distance
                file.push({s_adjacent, s_adjacent->getDistance()});
                s_adjacent->ajouterPredecesseur(plusProche.first->getId()); //on ajoute le predecesseur

            }
        }

    }
    while(!file.empty());
    afficherCheminPlusCourt(arrivee, poids);   //on affiche le chemin le plus court
}

void Graphe::trouverDepartArrivee(int *depart, int *arrivee) //dans le cas o� les ids ne commencent pas par 0
{
    for(unsigned i=0; i<m_sommets.size(); i++)
    {
        if(m_sommets[i]->getId()== *depart)
            *depart = i;
        if(m_sommets[i]->getId()== *arrivee)
            *arrivee = i;
    }
}*/
