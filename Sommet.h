#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>


class Sommet
{
private:
    int m_num;
    std::string m_id;
    int m_x,m_y;
    std::vector< std::pair<Sommet*,int> > m_voisins;

public:
    Sommet(int num, std::string id, int x, int y) : m_num{num}, m_id{id}, m_x{x}, m_y{y}{};
    int getNum(){return m_num;}
    std::string getId(){return m_id;}
    int getX(){return m_x;}
    int getY(){return m_y;}
    std::vector< std::pair<Sommet*,int>>& getVoisins(){return m_voisins;}

    void ajouterVoisin(std::pair<Sommet*,int> a){
            m_voisins.push_back(a);
    }

    void afficherSommetConsole()
    {
        std::cout << "\tSommet "<< m_num << ", Nom : " << m_id << ", X : " << m_x << ", Y : " << m_y ;
        std::cout << "\n\t\tVoisins ==>";
        for(size_t i=0; i<m_voisins.size();++i)
        {
            std::cout << "  Sommet " << m_voisins[i].first->getId() << " et poids " << m_voisins[i].second;
        }
    }

};
#endif // SOMMET_H_INCLUDED
