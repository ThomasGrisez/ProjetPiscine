#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

class Arete
{
private:
    int m_id;
    int m_ex1,m_ex2;

public:
    Arete(int id, int ex1, int ex2):m_id{id}, m_ex1{ex1}, m_ex2{ex2};
};

#endif // ARETE_H_INCLUDED
