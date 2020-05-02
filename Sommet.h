#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>


class Sommet
{
private:
    int m_id;
    std::string m_nom;
    int m_x,m_y;
    std::vector< std::pair<Sommet*,int> > m_voisins;
    std::vector<Sommet*> m_vecVoisins;

public:
    Sommet(int id, std::string nom, int x, int y) : m_id{id}, m_nom{nom}, m_x{x}, m_y{y}{};
    ~Sommet() = default;
    int getId(){return m_id;}
    std::string getNom(){return m_nom;}
    int getX(){return m_x;}
    int getY(){return m_y;}
    int getDeg(){return m_voisins.size();}
    std::vector< std::pair<Sommet*,int>>& getVoisins(){return m_voisins;}
    std::vector<Sommet*>& getVecVoisin(){return m_vecVoisins;}

    void ajouterVoisin(std::pair<Sommet*,int> a){
            m_voisins.push_back(a);
    }
    void ajouterVecVoisin(Sommet* a){
            m_vecVoisins.push_back(a);
    }

    void afficherSommetConsole()
    {
        std::cout << "\tSommet "<< m_id << ", Nom : " << m_nom << ", X : " << m_x << ", Y : " << m_y ;
        std::cout << "\n\t\tVoisins ==>";
        for(size_t i=0; i<m_voisins.size();++i)
        {
            std::cout << "  Sommet " << m_voisins[i].first->getNom() << " et poids " << m_voisins[i].second;
        }
    }

};
#endif // SOMMET_H_INCLUDED
