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
    void CentraliteProximite(int num_s0,int fin, Graphe &g)
    {

        ///----------------Dijkstra--------------
            int compteur=0;
            ///Comparaison pour le plus court chemin
            auto cmp = [] (std::pair<Sommet*,int> a, std::pair<Sommet*,int> b) { return b.second < a.second;} ;
            ///file de priorité
            std::priority_queue < std::pair<Sommet*,int>,std::vector< std::pair<Sommet*,int> >,decltype(cmp) > file(cmp);
            /// pour le marquage
            std::vector<int> couleurs((int)m_sommets.size,0);       ///Il est tard je bug, si j'ai bien compris m_sommet c'est l'ordre mais en remplaçant tous les
            ///pour les prédécesseurs                                  m_sommets par des g.getOrdre() je bloquais un peu plus loin...
            std::vector<int> preds((int)m_sommets.size,-1);
            ///pour les distances
            std::vector<int> dist ((int)m_sommets.size,-1);

            ///étape initiale, on enfile le sommet initial
            dist[num_s0] = 0;
            file.push ( std::make_pair(m_sommets[num_s0], 0) ); /// JE BLOQUAIS ICI (Majuscules pour que vous loupiez pas la ligne même si elle est juste en dessous)
                                                                ///C'est juste que je capte pas à quoi correspond le m_sommet[num_s0] voili voilou
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
                    ///Si pas marqué
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
                        if((Pair.second + succ.second == dist[ succ.first->getId() ]))    //
                        {
                            compteur++;
                        }
                    }
                }
            }
        ///Calcul pour trouver la centralité de proximité
        std::vector<float> valeurNonNorm;
        std::vector<float> valeurNorm;
    int idSommet;
    float idCP_Norm;
    float idCP_NonNorm;
    std::vector<std::pair<float,float>> vecNorm;
    std::vector<std::pair<float,float>> vecNonNorm;
    int ordre = g.getOrdre();

    for(int i=0; i<ordre; ++i)
    {
        idSommet = g.getId()[i];
        idCP_Norm = ( g.getDegs()[i] - 1 ) / ( compteur );
        idCP_NonNorm = 1/compteur;
        vecNorm.push_back(std::make_pair(idSommet, idCP_Norm));
        vecNonNorm.push_back(std::make_pair(idSommet, idCP_NonNorm));
    }

    std::cout << "======Centralite de Proximite Normalisee======\n";
    for(int j=0; j<ordre; ++j)
        std::cout << "\tSommet " << vecNorm[j].first << ", indice = " << vecNorm[j].second << std::endl;

    std::cout << "======Centralite de Proximite Non Normalisee======\n";
    for(int j=0; j<ordre; ++j)
        std::cout << "\tSommet " << vecNonNorm[j].first << ", indice = " << vecNonNorm[j].second << std::endl;
    };

*/

