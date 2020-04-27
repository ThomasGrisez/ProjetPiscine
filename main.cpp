#include <iostream>
#include "Sommet.h"
#include "Arete.h"
#include "Graphe.h"

int main()
{
    Graphe g{"Topologie.txt","Ponderation.txt"};

    g.afficherGrapheConsole();

    return 0;
}
