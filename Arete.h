#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>


class Arete
{
private:
    int m_id;
    int m_ex1,m_ex2;
    int m_poids;

public:
    Arete(int id, int ex1, int ex2, int poids):m_id{id}, m_ex1{ex1}, m_ex2{ex2}, m_poids{poids}{};
    void afficherAreteConsole()
    {
        std::cout << " \tArete : " << m_id << ", relie le sommet " << m_ex1 << " et le sommet " << m_ex2;
    }
};

#endif // ARETE_H_INCLUDED
