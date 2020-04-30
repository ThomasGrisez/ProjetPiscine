#include <iostream>
#include "Sommet.h"
#include "Arete.h"
#include "Graphe.h"
#include "Calculs.h"
#include "vulnerabilite.h"
<<<<<<< HEAD

//test de la connexite
=======

>>>>>>> master
    void vulnerabilite(int sommetInit, Graphe &g)
    {
            ///Comparaison pour le plus court chemin
            auto cmp = [] (std::pair<Sommet*,int> a, std::pair<Sommet*,int> b) { return b.second < a.second;} ;
            ///file de prioritï¿½
            std::priority_queue < std::pair<Sommet*,int>,std::vector< std::pair<Sommet*,int> >,decltype(cmp) > file(cmp);
            /// pour le marquage
            std::vector<int> couleurs((int)m_sommets.size(),0);
            ///pour les prï¿½dï¿½cesseurs
            std::vector<int> preds((int)m_sommets.size(),-1);
            ///pour les distances
            std::vector<int> dist ((int)m_sommets.size(),-1);

            ///ï¿½tape initiale, on enfile le sommet initial
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
                    ///Si pas marquï¿½
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

            for(int i=0;i<dist.size();++i)
            {
                std::vector<int> Nonconnexe;
                if dist[i]==1
                    Nonconnexe.push_back(1);
                std::cout<<"il y a "<<Nonconnexe.size()<<" vecteurs non reliï¿½ au reste du graphe suite ï¿½ la supression d'arete";
            }


    }

<<<<<<< HEAD

//comparaison centralite de degré
Graphe Comparaison degre( &graphe,&graphe1)
{   int idSommet;
    float idC;
    std::vector<std::pair<float,float>> vecNorm;
    int ordre = g.getOrdre();

    for(int i=0; i<ordre; ++i)
    {
        idSommet = g.getId()[i];
        idC = ( g.getDegs()[i] ) / ( ordre-1 );

        vecNorm.push_back(std::make_pair(idSommet, idC));
    }

{   int idSommet1;
    float idC1;
    std::vector<std::pair<float,float>> vecNorm1;
    int ordre1 = g1.getOrdre();

    for(int i=0; i<ordre1; ++i)
    {
        idSommet1 = g1.getId()[i];
        idC1 = ( g1.getDegs()[i] ) / ( ordre-1 );

        vecNorm1.push_back(std::make_pair(idSommet, idC));
    }
     std::cout << "======Comparaison indice degre normalise apres modification======\n";
    for(int j=0; j<ordre; ++j)
    {
        std::cout << "\tSommet " << vecNorm[j].first << ", indice = " << vecNorm[j].second <<
         ", indice actualisé = "<< vecNorm1[j].second << ", soit une difference de"<<
         vecNorm[j].second- vecNorm1[j].second  std::endl;
    }

}

=======
};

>>>>>>> master
