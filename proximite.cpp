#include <iostream>
#include <vector>
#include "Calculs.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include "proximite.h"
#include <math.h>
#include <queue>
/*
    void Dijkstra(int num_s0,int fin)
    {
            ///Comparaison pour le plus court chemin
            auto cmp = [] (std::pair<Sommet*,int> a, std::pair<Sommet*,int> b) { return b.second < a.second;} ;
            ///file de priorit�
            std::priority_queue < std::pair<Sommet*,int>,std::vector< std::pair<Sommet*,int> >,decltype(cmp) > file(cmp);
            /// pour le marquage
            std::vector<int> couleurs((int)m_sommets.size(),0);
            ///pour les pr�d�cesseurs
            std::vector<int> preds((int)m_sommets.size(),-1);
            ///pour les distances
            std::vector<int> dist ((int)m_sommets.size(),-1);

            ///�tape initiale, on enfile le sommet initial
            dist[num_s0] = 0;
            file.push ( std::make_pair(m_sommets[num_s0], 0) );

            std::pair<Sommet*,int> Pair;

            ///Tant que la file n est pas vide
            while(!file.empty())
            {
                Pair = file.top();
                file.pop();

                while( ( !file.empty() ) && ( couleurs[ Pair.first->getNum() ] == 1) )
                {
                    Pair = file.top();
                    file.pop();
                }
                ///on le marque
                couleurs[Pair.first->getNum()] = 1;

                for(auto succ : (Pair.first)->getSuccesseurs() )
                {
                    ///Si pas marqu�
                    if(couleurs[succ.first->getNum() ] == 0)
                    {
                        ///Si on trouve un meilleur chemin avec ce sommet
                        if( (dist[ succ.first->getNum() ] == -1) || (Pair.second + succ.second < dist[ succ.first->getNum() ]) )
                        {
                            ///on actualise la distance et le predecesseur
                            dist[ succ.first->getNum() ] = Pair.second + succ.second;
                            preds[ succ.first->getNum() ] = Pair.first->getNum();
                            ///on le rentre dans la file
                            file.push(std::make_pair( succ.first, dist[ succ.first->getNum() ] ));
                        }
                    }
                }
            }
            ///Affichage Parcours + R�sultat
            std::cout << fin;
            for(auto p = preds[fin]; p != -1; p = preds[p])
            {
                std::cout << "<--" << p;
            }
            std::cout << " : longueur " << dist[fin]-dist[preds[fin]];
            for(auto p = preds[fin]; p != -1; p = preds[p])
            {
                if( dist[p]!= 0)
                {std::cout << "+" << dist[p]-dist[preds[p]];}
            }
            std::cout << "="<<dist[fin];

    }

};*/
