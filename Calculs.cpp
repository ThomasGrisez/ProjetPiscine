#include <iostream>
#include <vector>
#include "Calculs.h"
#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <math.h>
#include <queue>
#include <fstream>

///Centralité de degré
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

    ///Arrondi des valeurs
    for(size_t i=0; i<Cvp.size(); ++i)
    {
        int entier = (int)((0.0005 + Cvp[i]) * 1000.0);
        Cvp[i]= (float)entier / 1000.0;
    }
    return Cvp;
}
///Centralité de proximité
std::pair<float,float> CentraliteProximite(int sommetInit, Graphe &g)
{
    ///Comparaison pour le plus court chemin
    auto cmp = [] (std::pair<Sommet*,int> a, std::pair<Sommet*,int> b)
    {
        return b.second < a.second;
    } ;
    ///file de priorité
    std::priority_queue < std::pair<Sommet*,int>,std::vector< std::pair<Sommet*,int> >,decltype(cmp) > file(cmp);
    /// pour le marquage
    std::vector<int> couleurs(g.getOrdre(),0);
    ///pour les predecesseurs
    std::vector<int> preds(g.getOrdre(),-1);
    ///pour les distances
    std::vector<int> dist (g.getOrdre(),-1);

    ///etape initiale, on enfile le sommet initial
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

    ///Arrondi des valeurs
    int entier1,entier2;

    entier1 = (int)((0.0005 + Cp_Norm) * 1000.0);
    entier2 = (int)((0.0005 + Cp_NonNorm) * 1000.0);

    Cp_Norm = (float)entier1 / 1000.0;
    Cp_NonNorm = (float)entier2 / 1000.0;

    if(Cp_Norm < 0)
        Cp_Norm = 0;
    if(Cp_NonNorm < 0)
        Cp_NonNorm = 0;


    return std::make_pair(Cp_Norm,Cp_NonNorm);
}
///Centralité de proximité Globale
float ProximiteGlobale(Graphe &g)
{
    std::vector<std::pair<float,float>> Cp;
    float CpGlob;
    float maxCp = 0;
    float n = g.getOrdre();
    float somme = 0;
    float deno;

    for(int i=0; i<n; ++i)
        Cp.push_back(CentraliteProximite(i,g));

    for(int i=0; i<n; ++i)
    {
        if(maxCp < Cp[i].first)
            maxCp = Cp[i].first;
    }

    for(int i=0; i<n; ++i)
        somme += maxCp - Cp[i].first;

    CpGlob = somme / ((n*n - 3*n +2)/(2*n - 3));

    ///Arrondi des valeurs
    int entier = (int)((0.0005 + CpGlob) * 1000.0);
    CpGlob= (float)entier / 1000.0;

    return CpGlob;
}
///BFS
std::vector<int> BFS(int num_s0,Graphe &g)
{
    /// déclaration de la file
    std::queue <Sommet*> file;

    /// pour le marquage
    std::vector<int> couleurs(g.getOrdre(),0);
    ///pour noter les prédécesseurs : on note les numéros des prédécesseurs (on pourrait stocker des pointeurs sur ...)
    std::vector<int> preds(g.getOrdre(),-1);

    ///étape initiale : on enfile et on marque le sommet initial
    file.push(g.getVecSommets()[num_s0]);
    couleurs[num_s0]=1;

    Sommet*s;
    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        s = file.front();
        std::vector<Sommet*> succ;
        succ = s->getVecVoisin();

        for(size_t i=0; i< succ.size(); ++i)
        {
            if(couleurs[ succ[i]->getId() ] == 0)
            {
                couleurs[ succ[i]->getId() ] = 1;
                preds[ succ[i]->getId() ] = s->getId();
                file.push(succ[i]);
            }
        }
        file.pop();
    }

    return preds;
}
///Test de connexité
void TestConnexite(Graphe &g)
{
    size_t num=0;
    bool test;
    int ncc=0;
    ///pour noter les numéros de CC
    std::vector<int> cc(g.getOrdre(),-1);
    do
    {
        cc[num]=num;
        std::cout<<std::endl<<"Composante connexe numero "<<ncc<<" : "<< "Sommet " << num <<" ";
        ncc++;
        ///lancement d'un BFS sur le sommet num
        std::vector<int> arbre_BFS=BFS(num,g);
        ///affichage des sommets decouverts lors du parcours (ceux qui ont un predecesseur
        for(size_t i=0; i<arbre_BFS.size(); ++i)
        {
            if ((i!=num)&&(arbre_BFS[i]!=-1))
            {
                cc[i]=num;
                std::cout<< "Sommet " << i <<" ";
            }
        }
        ///recherche d'un sommet non exploré
        ///pour relancer un BFS au prochain tour
        test=false;
        for(int i=0; i<g.getOrdre(); ++i)
        {
            if (cc[i]==-1)
            {
                num=i;
                test=true;
                break;
            }
        }
    }
    while(test==true);
    std::cout<<std::endl;
}
///Affichage des Indices
void affichageConsole(Graphe &g)
{
    std::vector<std::pair<float,float>> degNorm = CentraliteDegresNormalise(g);
    std::vector<std::pair<float,float>> degNonNorm = CentraliteDegresNonNormalise(g);
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
    for(int i=0; i<g.getOrdre(); ++i)
    {
        std::pair<float,float> Cp = CentraliteProximite(i,g);
        std::cout << "\tSommet " << g.getNoms()[i] << ", indice Normalise = " << Cp.first << ", indice Non Normalise = " << Cp.second << std::endl;
    }
}
///Affichage des Indices SVG
void affichageIndiceSVG(Svgfile &out,Graphe &g)
{
    std::vector<std::pair<float,float>> degNorm = CentraliteDegresNormalise(g);
    std::vector<float> Cvp = CentraliteVecteurPropre(g);

    Sommet*s;
    int x,y;
    std::string couleur = "blue";
    float degMax = 0;
    for(int i =0; i<g.getOrdre(); ++i)
    {
        if(degMax <= degNorm[i].second)
            degMax = degNorm[i].second;
    }

    for(int i=0; i<g.getOrdre(); ++i)
    {
        if(degNorm[i].second < 0.25*degMax)
            couleur = "white";
        if(degNorm[i].second >= 0.25*degMax)
            couleur = "yellow";
        if(degNorm[i].second >= 0.50*degMax)
            couleur = "orange";
        if(degNorm[i].second >= 0.75*degMax)
            couleur = "red";

        s = g.getVecSommets()[i];
        x = s->getX()*100;
        y = s->getY()*100;
        out.addDisk(x,y,6,"black");
        out.addDisk(x,y,5,couleur);
        out.addText(x+12,y-20,degNorm[i].second,"green");
        out.addText(x+12,y-32,Cvp[i],"red");
        std::pair<float,float> Cp = CentraliteProximite(i,g);
        out.addText(x+12,y-44,Cp.first,"blue");
    }
}
///Vulnerabilite
void Vulnerabilite(Graphe &a,Graphe &b)
{
    std::vector<std::pair<float,float>> degNormA= CentraliteDegresNormalise(a);
    std::vector<float> CvpA= CentraliteVecteurPropre(a);
    std::vector<std::pair<float,float>> degNormB= CentraliteDegresNormalise(b);
    std::vector<float> CvpB= CentraliteVecteurPropre(b);
    float CpGlobA = ProximiteGlobale(a);
    float CpGlobB = ProximiteGlobale(b);

    std::cout << "======Comparaison des Indices Normalise======\n";
    std::cout << "Centralite de degres Normalise\n";
    for(int i=0; i<a.getOrdre(); ++i)
    {
        std::cout << "\tSommet " << a.getNoms()[i] << ", Avant : " << degNormA[i].second << ", Apres : " << degNormB[i].second << ", Difference : " << degNormA[i].second - degNormB[i].second << std::endl;
    }
    std::cout << "======Centralite de Vecteur propre====\n";
    for(int i=0; i<a.getOrdre(); ++i)
    {
        std::cout << "\tSommet " << a.getNoms()[i] << ", Avant : " << CvpA[i] << ", Apres : " << CvpB[i] << ", Difference : " << CvpA[i] - CvpB[i] << std::endl;
    }
    std::cout << "======Centralite de proximite=========\n";
    for(int i=0; i<a.getOrdre(); ++i)
    {
        std::pair<float,float> CpA = CentraliteProximite(i,a);
        std::pair<float,float> CpB = CentraliteProximite(i,b);
        std::cout << "\tSommet " << a.getNoms()[i] << ", Avant : " << CpA.first << ", Apres : " << CpB.first << ", Difference : " << CpA.first - CpB.first << std::endl;
    }
    std::cout << "======Centralite de proximite Globale=========\n";
    std::cout << "\tGraphe complet : " << CpGlobA << std::endl;
    std::cout << "\tGraphe Modifie : " << CpGlobB << std::endl;
    std::cout << "\tDifference (Graphe complet - Graphe Modifie) : " << CpGlobA - CpGlobB << std::endl;
}
///Sauvegarde Fichier des indices
void SauvegardeFichier(Graphe &g)
{
    std::vector<std::pair<float,float>> degNorm = CentraliteDegresNormalise(g);
    std::vector<std::pair<float,float>> degNonNorm = CentraliteDegresNormalise(g);
    std::vector<float> Cvp = CentraliteVecteurPropre(g);
    std::ofstream ofs("Indices.txt");

    ofs << "Indice du sommet | Centralite de degre | Centralite de vecteur propre | Centralite de proximite" << std::endl;
    ofs << "A chaque fois : indice Normalisé puis Non Normalisé" << std::endl;

    for(int i=0; i< g.getOrdre(); ++i)
    {
        std::pair<float,float> Cp = CentraliteProximite(i,g);
        ofs << g.getId()[i] <<" | "<< degNorm[i].second <<"  "<< degNonNorm[i].second <<" | "<< Cvp[i] <<" | "<< Cp.first <<"   "<< Cp.second << std::endl;
    }
}
