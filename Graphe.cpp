    #include "graphe.h"
#include <fstream>
#include <string>
#include <iostream>
#include <queue>

#define INFINI 999


//constructeur du graphe avec lecture de fichier
Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;      //on récupère l'ordre
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int num;       //l'id
    for (int i=0; i<ordre; ++i)
    {
        ifs >> num;
        m_sommets.push_back( new Sommet{num} );
    }

    ifs >> m_taille;    //la taille du graphe
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");



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
    }
}


/// Destructeur du réseau. Les stations ont été allouées dynamiquement
/// lors de la création d'une instance Graphe, le réseau est responsable de leur libération
Graphe::~Graphe()
{
    for (auto s : m_sommets)
        delete s;
}

//affiche le graphe
void Graphe::afficher()
{
    std::cout << "Il y a " << m_sommets.size() << " sommets :" << std::endl;
    for(unsigned i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficherSommet();
    }
}

//affiche le chemin le plus court de depart a arrivee
void Graphe::afficherCheminPlusCourt(int num, std::vector<int>& poids)
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

//Algo principal de l'algo, reçoit le depart et l'arrivee
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
        do      //on récupére le plus proche si il n'est pas deja marque
        {
            plusProche = file.top();
            file.pop();
        }while(plusProche.first->getMarquage()==1&&!file.empty());

        plusProche.first->setMarquage(true);       //on le marque comme visité
        for(int i=0; i<plusProche.first->getDegre(); i++)
        {
            s_adjacent = plusProche.first->getAdjacent(i);
            if(s_adjacent->getDistance()>plusProche.second+plusProche.first->getPoids(i)&& s_adjacent->getMarquage()==0)      //si sa distance supérieure à la distance du predecesseur + poids entre les deux
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

void Graphe::trouverDepartArrivee(int *depart, int *arrivee) //dans le cas où les ids ne commencent pas par 0
{
    for(unsigned i=0; i<m_sommets.size(); i++)
    {
        if(m_sommets[i]->getId()== *depart)
            *depart = i;
        if(m_sommets[i]->getId()== *arrivee)
            *arrivee = i;
    }
}
