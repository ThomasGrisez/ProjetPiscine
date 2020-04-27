#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

class Sommet
{
private:
    int m_num;
    int m_id;
    int m_x,m_y;

public:
    Sommet(int num, int id, int x, int y) : m_num{num}, m_id{id}, m_x{x}, m_y{y};
    int getNum(){return m_num;}
    int getId(){return m_id;}
    int getX(){return m_x;}
    int getY(){return m_y;}

};
#endif // SOMMET_H_INCLUDED
