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

public:
    Sommet(int num, std::string id, int x, int y) : m_num{num}, m_id{id}, m_x{x}, m_y{y}{};
    int getNum(){return m_num;}
    std::string getId(){return m_id;}
    int getX(){return m_x;}
    int getY(){return m_y;}

    void afficherSommetConsole()
    {
        std::cout << "\tSommet "<< m_id << "(" << m_num << ")" << " = X : " << m_x << ", Y : " << m_y;
    }

};
#endif // SOMMET_H_INCLUDED
