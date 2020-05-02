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
    while(choix!=8)
    {
        do
        {
            std::cout << "===========================================\n";
            std::cout << "Que voulez vous faire?\n" ;
            std::cout << "1.Charger un graphe\n";
            std::cout << "2.Afficher dans la console\n";
            std::cout << "3.Afficher au format SVG\n";
            std::cout << "4.Modifier le poids d'une arete du graphe\n";
            std::cout << "5.Supprimer une arete du graphe\n";
            std::cout << "6.Calculer, afficher et sauvegarder les differents indices de centralite\n";
            std::cout << "7.Vulnerabilite du graphe\n";
            std::cout << "8.Quitter\n";
            std::cin >> choix;
        }
        while(choix < 1 || choix > 8);
        switch(choix)
        {
        case 1:///Charger Fichiers
        {
            std::cout << "Indiquer le fichier de topologie a utiliser : ";
            std::cin >> topo;
            std::cout << "Indiquer le fichier de ponderation a utiliser : ";
            std::cin >> pond;
        }
        break;
        case 2:///Affichage Console
        {
            int chx;
            std::cout << "1.Afficher le graphe complet.\n2.Aficher le graphe avec arete(s) supprimee(s).\n";
            std::cin >> chx;
            if(chx == 1)
            {
                Graphe g{topo,pond};
                g.afficherGrapheConsole();
            }
            else
            {
                Graphe g{"TopoAvecAreteSupprimee.txt","PondAvecAreteSupprimee.txt"};
                g.afficherGrapheConsole();
            }
        }
        break;
        case 3:///Affichage SVG
        {
            Svgfile out;
            int chx;
            std::cout << "1.Afficher le graphe complet.\n2.Aficher le graphe avec arete(s) supprimee(s).\n";
            std::cin >> chx;
            if(chx == 1)
            {
                Graphe g{topo,pond};
                g.afficherGrapheSvg(out);
                affichageIndiceSVG(out,g);
            }
            else
            {
                Graphe g{"TopoAvecAreteSupprimee.txt","PondAvecAreteSupprimee.txt"};
                g.afficherGrapheSvg(out);
                affichageIndiceSVG(out,g);
            }
        }
        break;
        case 4:///Modifier Poids Arete
        {
            Graphe g{ topo, pond };
            g.ModifierPonderation();
        }
        break;
        case 5:///Supprimer  Arete
        {
            Graphe g{ topo, pond };
            g.SuppArete();
        }
        break;
        case 6:///Affichage Indice Console et Sauvegarde/// rajouter avec aretes suppr
        {
            int chx;
            std::cout << "1.Pour le graphe complet\n2.Pour le graphe avec aretes supprimees\n";
            std::cin >> chx;
            if(chx == 1)
            {
                Graphe g{ topo, pond };
                affichageConsole(g);
                SauvegardeFichier(g);
            }
            if(chx == 2)
            {
                Graphe g{"TopoAvecAreteSupprimee.txt","PondAvecAreteSupprimee.txt"};
                affichageConsole(g);
                SauvegardeFichier(g);
            }

        }
        break;
        case 7:///Vulnerabilite
        {
            int chx;
            std::cout << "1.Tester la connexite du graphe complet.\n2.Tester la connexite du graphe avec arete(s) supprimee(s).\n3.Comparer les indices de centralite avant et apres la suppression d'aretes\n";
            std::cin >> chx;
            if(chx == 1)
            {
                Graphe g{topo,pond};
                TestConnexite(g);
            }
            if(chx == 2)
            {
                Graphe g{"TopoAvecAreteSupprimee.txt","PondAvecAreteSupprimee.txt"};
                TestConnexite(g);
            }
            if(chx == 3)
            {
                Graphe a{topo,pond};
                Graphe b{"TopoAvecAreteSupprimee.txt","PondAvecAreteSupprimee.txt"};
                Vulnerabilite(a,b);
            }
        }
        break;
        case 8:///Quitter
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
