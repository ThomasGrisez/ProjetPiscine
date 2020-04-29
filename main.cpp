#include <iostream>
#include "Sommet.h"
#include "Arete.h"
#include "Graphe.h"
#include "Calculs.h"
#include "proximite.h"

void menu()
{
    std::string topo="t.txt",pond="p.txt";
    int choix;
    while(choix!=7)
    {
        do
        {
            std::cout << "===========================================\n";
            std::cout << "Que voulez vous faire?\n" ;
            std::cout << "1.Charger un graphe\n";
            std::cout << "2.Afficher dans la console\n";
            std::cout << "3.Afficher au format SVG\n";
            std::cout << "4.Modifier le poids d'une arete du graphe\n";
            std::cout << "5.Calculer, afficher et sauvegarder les differents indices de centralite\n";
            std::cout << "6.Tester la vulnerabilite du graphe\n";
            std::cout << "7.Quitter\n";
            std::cin >> choix;
        }
        while(choix < 1 || choix > 7);
        switch(choix)
        {
        case 1:
            {
                std::cout << "Indiquer le fichier de topologie a utiliser : ";
                std::cin >> topo;
                std::cout << "Indiquer le fichier de ponderation a utiliser : ";
                std::cin >> pond;
            }
            break;
        case 2:
            {
                Graphe g{ topo, pond };
                g.afficherGrapheConsole();
            }
            break;
        case 3:
            {
                Graphe g{ topo, pond };
                g.afficherGrapheSvg();
            }
            break;
        case 4:
            {
                Graphe g{ topo, pond };
                g.ModifierPonderation();
            }
            break;
        case 5:
            {
                Graphe g{ topo, pond };
                CentraliteDegresNormalise(g);
                CentraliteDegresNonNormalise(g);
                CentraliteVecteurPropre(g);
                std::cout << "======Centralite de proximite=======\n";
                for(size_t i=0;i < g.getOrdre();++i)
                {
                    CentraliteProximite(i,g);
                }

            }
            break;
        case 6:
            {
                Graphe g{topo, pond};
                vulnerabilite(g)
            }
            break;
        case 7:
            exit(0);
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}
