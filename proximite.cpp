#include <iostream>
#include <vector>
#include "Calculs.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include "proximite.h"
#include <math.h>
#include <queue>

void CentraliteProximite(int sommetInit, Graphe &g)
{

    ///----------------Dijkstra--------------
    int compteur=0;
    ///Comparaison pour le plus court chemin
    auto cmp = [] (std::pair<Sommet*,int> a, std::pair<Sommet*,int> b)
    {
        return b.second < a.second;
    } ;
    ///file de priorité
    std::priority_queue < std::pair<Sommet*,int>,std::vector< std::pair<Sommet*,int> >,decltype(cmp) > file(cmp);
    /// pour le marquage
    std::vector<int> couleurs(g.getOrdre(),0);
    ///pour les pr�d�cesseurs
    std::vector<int> preds(g.getOrdre(),-1);
    ///pour les distances
    std::vector<int> dist (g.getOrdre(),-1);

    ///�tape initiale, on enfile le sommet initial
    dist[sommetInit] = 0;
    file.push ( std::make_pair(g.getVecSommets()[sommetInit], 0) );

    std::pair<Sommet*,int> Pair;

    ///Tant que la file n est pas vide
    while(!file.empty())
    {
        Pair = file.top();
        file.pop();

        while( ( !file.empty() ) && ( couleurs[ Pair.first->getId() ] == 1) )
        {
            Pair = file.top();
            file.pop();
        }
        ///on le marque
        couleurs[Pair.first->getId()] = 1;

        for(auto succ : (Pair.first)->getVoisins() )
        {
            ///Si pas marqu�
            if(couleurs[succ.first->getId() ] == 0)
            {
                ///Si on trouve un meilleur chemin avec ce sommet
                if( (dist[ succ.first->getId() ] == -1) || (Pair.second + succ.second < dist[ succ.first->getId() ]) )
                {
                    ///on actualise la distance et le predecesseur
                    dist[ succ.first->getId() ] = Pair.second + succ.second;
                    preds[ succ.first->getId() ] = Pair.first->getId();
                    ///on le rentre dans la file
                    file.push(std::make_pair( succ.first, dist[ succ.first->getId() ] ));
                }
                if((Pair.second + succ.second == dist[ succ.first->getId() ]))
                {
                    compteur++;
                }
            }
        }
    }
    ///Calcul pour trouver la centralité de proximité
    float Cp_Norm;
    float Cp_NonNorm;
    float sommeDist = 0;

    for(int i=0; i< g.getOrdre();++i)
    {
        sommeDist += dist[i];
    }

    Cp_NonNorm = 1/sommeDist;

    Cp_Norm = (g.getOrdre() -1) / sommeDist;

    Sommet* sommet = g.getVecSommets()[sommetInit];
    std::string nomSommet = sommet->getNom();

    std::cout << "\tSommet " <<  nomSommet << ", indice Normalise = " << Cp_Norm << ", indice Non Normalise = " << Cp_NonNorm << std::endl;
};
