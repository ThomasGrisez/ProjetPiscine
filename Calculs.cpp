#include <iostream>
#include <vector>
#include "Calculs.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <math.h>

///Centralité de degré, indices normalisé et non normalisés
void CentraliteDegresNormalise(Graphe &g)
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

    std::cout << "======Indices Normalise======\n";
    for(int j=0; j<ordre; ++j)
        std::cout << "\tSommet " << vecNorm[j].first << ", indice = " << vecNorm[j].second << std::endl;

}
void CentraliteDegresNonNormalise(Graphe &g)
{
    std::vector<std::pair<float,float>> vecNonNorm;
    int ordre = g.getOrdre();

    for(int i=0; i<ordre; ++i)
        vecNonNorm.push_back(std::make_pair(g.getId()[i],   g.getDegs()[i] ));

    std::cout << "======Indices Non Normalise======\n";
    for(int j=0; j<ordre; ++j)
        std::cout << "\tSommet " << vecNonNorm[j].first << ", indice : " << vecNonNorm[j].second << std::endl;
}
///Centralité de vecteur propre
void CentraliteVecteurPropre(Graphe &g)
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
        for(int i=0; i<ordre;++i)
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

    std::cout << "======Indices de vecteur propre======\n";
    for(size_t i=0; i<Cvp.size(); ++i)
    {
        std::cout << "\tSommet " << g.getNoms()[i] << ", indice = " << Cvp[i] << std::endl;
    }

}
///Centralité de proximité



///Centralité d'intermediarité
