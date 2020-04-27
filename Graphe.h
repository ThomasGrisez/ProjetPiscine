#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include "Arete.h"

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;

public:
    Graphe(std::string FichierTopo, std::string FichierPond)
    {
        /// Lecture du FichierTopo
        std::ifstream a{FichierTopo};
        /// Lecture du FichierPond
        std::ifstream b{FichierPond};

        int orientation;
        a >> orientation;

        int ordre;
        a >> ordre;

        int x,y,num;
        std::string id_sommet;
        for(int i=0; i<ordre; ++i)
        {
            a >> num >> id_sommet>> x >> y;
            m_sommets.push_back( new Sommet{num,id_sommet,x,y} );
        }

        int tailletopo;
        a >> tailletopo;

        int taillepond;
        b >> taillepond;

        if(taillepond == tailletopo) /// Si la taille dans le fichier Topologie est égale à la taille dans le fichier Pondération
        {
            int ex1,ex2,poids;
            int id_arete_topo, id_arete_pond;
            for(int j=0; j<taillepond; ++j)
            {
                b >> id_arete_pond >> poids;
                a >> id_arete_topo >> ex1 >> ex2;
                m_aretes.push_back( new Arete{id_arete_topo,ex1,ex2,poids} );
            }
        }
        else
        {
            std::cout << "Probleme dans les fichiers, les tailles des graphes ne sont egales\n";
        }
    }

    ~Graphe()
    {
        for( auto s: m_sommets)
            delete s;
        for( auto a: m_aretes)
            delete a;
    }

   void afficherGrapheConsole()
   {
       std::cout << "Graphe :\n";
       std::cout << "Ordre : " << m_sommets.size() << "\n";
       std::cout << "Liste des sommets :\n";
       for(auto s: m_sommets)
       {
           s->afficherSommetConsole();
           std::cout<<"\n";
       }
       std::cout << "Liste des aretes :\n";
       for(auto a: m_aretes)
       {
           a->afficherAreteConsole();
           std::cout<<"\n";
       }
   }
};

#endif // GRAPHE_H_INCLUDED
