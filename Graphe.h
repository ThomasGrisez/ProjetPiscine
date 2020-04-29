#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include "Sommet.h"
#include "Arete.h"
#include "svgfile.h"
#include "Sommet.h"

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    std::vector<std::pair<int,int>> m_pair;

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

                m_pair.push_back(std::make_pair(id_arete_pond,poids));

                m_sommets[ex1]->ajouterVoisin(std::make_pair(m_sommets[ex2],poids));
                m_sommets[ex2]->ajouterVoisin(std::make_pair(m_sommets[ex1],poids));
            }
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
        std::cout << "=========================GRAPHE=============================\n";
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

    void afficherGrapheSvg()
    {
        Svgfile out;

        out.addGrid();
        //std::string rouge=makeRGB(255,0,0); ///Bon il est tard et je suis défoncé, faut juste faire une variable qui va servir de rouge de référence pour faire le dégradé
        //std::string bleu=makeRGB(0,0,255);///Idem pour le bleu

        for(size_t i=0; i<m_sommets.size();++i)
        {
            out.addDisk(m_sommets[i]->getX()*100, m_sommets[i]->getY()*100, 5, "blue");
            out.addText(m_sommets[i]->getX()*100, (m_sommets[i]->getY()*100)-20, m_sommets[i]->getNom(), "black");
        }
        for(size_t i=0; i<m_aretes.size();++i)
        {
            int x1= m_sommets[m_aretes[i]->getEx1()]->getX()*100;
            int y1= m_sommets[m_aretes[i]->getEx1()]->getY()*100;
            int x2= m_sommets[m_aretes[i]->getEx2()]->getX()*100;
            int y2= m_sommets[m_aretes[i]->getEx2()]->getY()*100;
            out.addText((x1+x2)/2+5, (y1+y2)/2-10, m_aretes[i]->getPoids(), "red");
            out.addLine(x1,y1,x2,y2,"black");
        }
    }

    void ModifierPonderation()
    {
        std::string fichier;
        int numArete,poidsArete;
        std::cout << "Indiquez le fichier dans lequel faire la modification : ";
        std::cin >> fichier;
        std::cout << "Indiquez l'arete a modifier : ";
        std::cin >> numArete;
        std::cout << "Indiquez le nouveau poids : ";
        std::cin >> poidsArete;

        for(size_t i=0 ; i<m_pair.size(); ++i)
        {
            if(m_pair[i].first == numArete)
                m_pair[i].second = poidsArete;
        }

        std::ofstream ofs (fichier);

        ofs << m_pair.size() << std::endl;

        for(size_t j=0; j<m_pair.size(); ++j)
        {
            ofs << m_pair[j].first << " " << m_pair[j].second << std::endl;
        }
    }

    std::vector<float> getDegs()
    {
        std::vector<float> a;
        for(size_t i=0;i<m_sommets.size();++i)
        {
            a.push_back(m_sommets[i]->getDeg());
        }
        return a;
    }

    int getOrdre(){return m_sommets.size();}
    int getTaille(){return m_aretes.size();}
    std::vector<int> getId()
    {
        std::vector<int> a;
        for(size_t i=0;i<m_sommets.size();++i)
        {
            a.push_back(m_sommets[i]->getId());
        }
        return a;
    }

    std::vector<std::string> getNoms()
    {
        std::vector<std::string> a;
        for(size_t i=0;i<m_sommets.size();++i)
        {
            a.push_back(m_sommets[i]->getNom());
        }
        return a;
    }

    std::vector<std::vector<std::pair<Sommet*,int>>> getVecVoisins()
    {
        std::vector<std::vector<std::pair<Sommet*,int>>> a;

        for(size_t i=0; i<m_sommets.size();++i)
        {
            a.push_back(m_sommets[i]->getVoisins());
        }
        return a;
    }

    std::vector<Sommet*> getVecSommets(){return m_sommets;}
};

#endif // GRAPHE_H_INCLUDED
