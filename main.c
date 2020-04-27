#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>

#include "graphe.h"

///Code réalisé par Alexis Martin et Clément Rozycki TD08 ING2

int main()
{
    try
    {
        bool quitter = false;
        int depart, arrivee, choix;
        Graphe Graphe{"graphe.txt"};
        Graphe.afficher();

        do
        {


            std::cout << "\n\nD'ou partez vous?" << std::endl;
            std::cin >> depart;
            std::cout << "Ou allez vous?" << std::endl;
            std::cin >> arrivee;

            Graphe.trouverDepartArrivee(&depart, &arrivee);
            Graphe.algoDijkstra(depart, arrivee);

            do
            {
                std::cout << "\n\nVoulez vous continuer?\n1.Oui\n2.Non" << std::endl;
                std::cin >> choix;
            }while(choix<1||choix>2);

            if(choix==2)
                quitter = true;

        }while(!quitter);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }

    return 0;
}
