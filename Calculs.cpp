#include <iostream>
#include <vector>
#include "Calculs.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <math.h>
#include <queue>
#include <fstream>

///Centralité de degré, indices normalisé et non normalisés
std::vector<std::pair<float,float>> CentraliteDegresNormalise(Graphe &g)
{
    int idSommet;
    float idC;
    std::vector<std::pair<float,float>> vecNorm;
    int ordre = g.getOrdre();

    for(int i=0; i<ordre; ++i)
    {
        idSommet = g.getId()[i];
        idC = ( g.getDegs()[i] ) / ( ordre-1 );

        vecNorm.push_back(std::make_pair(idSommet, idC));
    }

    return vecNorm;
}
std::vector< std::pair<float,float> > CentraliteDegresNonNormalise(Graphe &g)
{
    std::vector<std::pair<float,float>> vecNonNorm;
    int ordre = g.getOrdre();

    for(int i=0; i<ordre; ++i)
        vecNonNorm.push_back(std::make_pair(g.getId()[i],   g.getDegs()[i] ));

    return vecNonNorm;
}
///Centralité de vecteur propre
std::vector<float> CentraliteVecteurPropre(Graphe &g)
{
    float lambda = 0;
    float ancienLambda;
    float somme = 0;
    int ordre = g.getOrdre();
    std::vector<float> Cvp;
    std::vector<float> c;
    for(int i=0; i<ordre; ++i)
    {
        Cvp.push_back(1);
        c.push_back(0);
    }


    do
    {
        for(int i=0; i<ordre; ++i)
            c[i] = 0;
        for(int i=0; i< ordre ; ++i)///Pour chaque sommet
        {
            int nbVoisins = ( g.getVecVoisins()[i] ).size();
            for(int j=0; j<nbVoisins; ++j) /// Faire la somme des indices de ses voisins
            {
                Sommet* Voisin = ((g.getVecVoisins()[i])[j].first);
                int numVoisin = Voisin->getId();
                c[i] = c[i] + Cvp[numVoisin];
            }
        }

        for(int i=0 ; i<ordre; ++i)
        {
            somme = somme + c[i]*c[i];
        }
        ancienLambda = lambda;
        lambda = pow(somme,0.5);

        for(int i=0; i<ordre; ++i)
        {
            Cvp[i] = c[i] / lambda;
        }
    }
    while( (lambda - ancienLambda) > 0.01);

    return Cvp;
}
///Centralité de proximité
std::pair<float,float> CentraliteProximite(int sommetInit, Graphe &g)
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

    for(int i=0; i< g.getOrdre(); ++i)
    {
        sommeDist += dist[i];
    }

    Cp_NonNorm = 1/sommeDist;

    Cp_Norm = (g.getOrdre() -1) / sommeDist;

    return std::make_pair(Cp_Norm,Cp_NonNorm);
};


///Centralité d'intermediarité



///Affichage des Indices
void affichageConsole(Graphe &g)
{
    std::vector<std::pair<float,float>> degNorm = CentraliteDegresNormalise(g);
    std::vector<std::pair<float,float>> degNonNorm = CentraliteDegresNormalise(g);
    std::vector<float> Cvp = CentraliteVecteurPropre(g);

    std::cout << "======Centralite de degre=============\n";
    for(int j=0; j<g.getOrdre(); ++j)
        std::cout << "\tSommet " << g.getNoms()[degNorm[j].first] << ", indice Normalise = " << degNorm[j].second << ", indice Non Normalise = " << degNonNorm[j].second << std::endl;

    std::cout << "======Centralite de vecteur propre======\n";
    for(int i=0; i<g.getOrdre(); ++i)
    {
        std::cout << "\tSommet " << g.getNoms()[i] << ", indice = " << Cvp[i] << std::endl;
    }

    std::cout << "======Centralite de Proximite==========\n";
    for(int i=0; i<g.getOrdre();++i)
    {
        std::pair<float,float> Cp = CentraliteProximite(i,g);
        std::cout << "\tSommet " << g.getNoms()[i] << ", indice Normalise = " << Cp.first << ", indice Non Normalise = " << Cp.second << std::endl;
    }
}


void SauvegardeFichier(Graphe &g)
{
    std::vector<std::pair<float,float>> degNorm = CentraliteDegresNormalise(g);
    std::vector<std::pair<float,float>> degNonNorm = CentraliteDegresNormalise(g);
    std::vector<float> Cvp = CentraliteVecteurPropre(g);
    std::ofstream ofs("Indices.txt");

    ofs << "Indice du sommet | Centralite de degre | Centralite de vecteur propre | Centralite de proximite | Centralite d'intermediarite" << std::endl;
    ofs << "A chaque fois : indice Normalisé puis Non Normalisé" << std::endl;

    for(int i=0; i< g.getOrdre();++i)
    {
        std::pair<float,float> Cp = CentraliteProximite(i,g);
        ofs << g.getId()[i] <<" | "<< degNorm[i].second <<"  "<< degNonNorm[i].second <<" | "<< Cvp[i] <<" | "<< Cp.first <<"   "<< Cp.second << std::endl;
    }
}
