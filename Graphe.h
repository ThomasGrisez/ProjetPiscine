#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include "Sommet.h"
#include "Arete.h"
#include "svgfile.h"
#include "Sommet.h"
#include <algorithm>

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;///Vecteur de pointeurs sur Sommet
    std::vector<Arete*> m_aretes;///Vecteur de pointeurs sur Arete
    std::vector<std::pair<int,int>> m_pair; ///vecteur de paires contenant l' id d une arete et son poids
    int m_orient;///Orientation du graphe

public:
    Graphe(std::string FichierTopo, std::string FichierPond)
    {
        /// Lecture du FichierTopo
        std::ifstream a{FichierTopo};
        /// Lecture du FichierPond
        std::ifstream b{FichierPond};

        a >> m_orient;

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

        int ex1,ex2,poids;
        int id_arete_topo, id_arete_pond;
        for(int j=0; j<taillepond; ++j)
        {
            b >> id_arete_pond >> poids;
            a >> id_arete_topo >> ex1 >> ex2;
            m_aretes.push_back( new Arete{id_arete_topo,ex1,ex2,poids} );

            m_pair.push_back(std::make_pair(id_arete_pond,poids));

            m_sommets[ex1]->ajouterVoisin(std::make_pair(m_sommets[ex2],poids));
            m_sommets[ex1]->ajouterVecVoisin(m_sommets[ex2]);
            m_sommets[ex2]->ajouterVoisin(std::make_pair(m_sommets[ex1],poids));
            m_sommets[ex2]->ajouterVecVoisin(m_sommets[ex1]);
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
        if(m_orient == 0)
            std::cout << "Graphe non oriente\n";
        else
            std::cout << "Graphe oriente\n";
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

    void afficherGrapheSvg(Svgfile &out)
    {

        out.addGrid();
        out.addRect(700,100,1000,100,1000,280,700,280,"lightgray",2,"black");
        out.addText(715,115, "Centralite de degre normalise", "green");
        out.addText(715,135,"Centralite de vecteur propre","red");
        out.addText(715,155,"Centralite de proximite normalise","blue");
        out.addText(715,175,"La couleur du sommets depend ","black");
        out.addText(715,195,"de son degre :","black");
        out.addText(715,215,"Superieur a 75% du degre max","red");
        out.addText(715,235,"Superieur a 50% du degre max","orange");
        out.addText(715,255,"Superieur a 25% du degre max","yellow");
        out.addText(715,275,"Inferieur a 25% du degre max","white");

        for(size_t i=0; i<m_sommets.size(); ++i)
            out.addText(m_sommets[i]->getX()*100, (m_sommets[i]->getY()*100)-20, m_sommets[i]->getNom(), "black");

        for(size_t i=0; i<m_aretes.size(); ++i)
        {
            int x1= m_sommets[m_aretes[i]->getEx1()]->getX()*100;
            int y1= m_sommets[m_aretes[i]->getEx1()]->getY()*100;
            int x2= m_sommets[m_aretes[i]->getEx2()]->getX()*100;
            int y2= m_sommets[m_aretes[i]->getEx2()]->getY()*100;
            out.addText((x1+x2)/2+5, (y1+y2)/2-10, m_aretes[i]->getPoids(), "purple");
            out.addLine(x1,y1,x2,y2,"black");
        }
    }

    void ModifierPonderation()
    {
        std::string fichier;
        int numArete,poidsArete;
        std::cout << "Indiquez le fichier dans lequel faire la modification : ";
        std::cin >> fichier;
        std::cout << "Aretes disponibles :\n";
        for(size_t i=0; i<m_aretes.size(); ++i)
            std::cout << "Arete " << m_aretes[i]->getId() << ", relie les sommets " << m_aretes[i]->getEx1() << " et " << m_aretes[i]->getEx2() << std::endl;
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

    void SuppArete()
    {
        int nbAretes,numArete;
        std::vector<int> arete;
        std::cout << "Combien d'arete voulez-vous supprimer ?\n";
        std::cin >> nbAretes;
        std::cout << "Aretes disponibles :\n";
        for(size_t i=0; i<m_aretes.size(); ++i)
            std::cout << "Arete " << m_aretes[i]->getId() << ", relie les sommets " << m_aretes[i]->getEx1() << " et " << m_aretes[i]->getEx2() << std::endl;
        for(int i=0; i<nbAretes; ++i)
        {
            std::cout << "Indiquez l'arete a supprimer : ";
            std::cin >> numArete;
            arete.push_back(numArete);
        }
        std::vector<Arete*> vecAretes = m_aretes;

        ///On met les elements du vecteur dans l'ordre decroissant
        std::sort(arete.begin(), arete.end());
        std::reverse(arete.begin(), arete.end());

        for(int i=0; i<nbAretes; ++i)
            vecAretes.erase(vecAretes.begin() + arete[i]);

        ///Sauvegarde des graphes avec aretes supprimées
        std::ofstream a("TopoAvecAreteSupprimee.txt");
        std::ofstream b("PondAvecAreteSupprimee.txt");

        a << m_orient << std::endl;
        a << m_sommets.size() << std::endl;

        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            a << m_sommets[i]->getId() << " " << m_sommets[i]->getNom() << " " << m_sommets[i]->getX() << " " << m_sommets[i]->getY() << std::endl;
        }
        a << vecAretes.size() << std::endl;
        for(size_t i=0; i<vecAretes.size(); ++i)
        {
            a << i << " " << vecAretes[i]->getEx1() << " " << vecAretes[i]->getEx2() << std::endl;
        }

        b << vecAretes.size() << std::endl;
        for(size_t i=0; i<vecAretes.size(); ++i)
        {
            b << i << " " << vecAretes[i]->getPoids() << std::endl;
        }
    }

    std::vector<float> getDegs()
    {
        std::vector<float> a;
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            a.push_back(m_sommets[i]->getDeg());
        }
        return a;
    }

    int getOrdre()
    {
        return m_sommets.size();
    }

    int getTaille()
    {
        return m_aretes.size();
    }

    std::vector<int> getId()
    {
        std::vector<int> a;
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            a.push_back(m_sommets[i]->getId());
        }
        return a;
    }

    std::vector<std::string> getNoms()
    {
        std::vector<std::string> a;
        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            a.push_back(m_sommets[i]->getNom());
        }
        return a;
    }

    std::vector<std::vector<std::pair<Sommet*,int>>> getVecVoisins()
    {
        std::vector<std::vector<std::pair<Sommet*,int>>> a;

        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            a.push_back(m_sommets[i]->getVoisins());
        }
        return a;
    }

    std::vector<Sommet*> getVecSommets()
    {
        return m_sommets;
    }
};

#endif // GRAPHE_H_INCLUDED
