#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

class Graphe
{
private:
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;

public:
    Graphe(std::string FichierTopo, std::string FichierPond)
    {
        /// Lecture du FichierTopo
        std::ifstream a{FichierTopo};

        int orientation;
        a >> orientation;

        int ordre;
        a >> ordre;

        int x,y,id1,num;
        for(int i=0; i<ordre; ++i)
        {
            a >> num >> id1 >> x >> y;
            m_sommets.push_back( new Sommet{num,id1,x,y});
        }

        int taille;
        a >> taille;

        int id2,ex1,ex2;
        for(int j=0;j<taille;++j)
        {
            a >> id2 >> ex1 >> ex2;
            m_aretes.push_back( new Arete{id2,ex1,ex2});
        }



        for(int j=0;j<ordre)

        /// Lecture du FichierPond
        std::ifstream b{FichierPond};
    }

};

#endif // GRAPHE_H_INCLUDED
