#ifndef CALCULS_H_INCLUDED
#define CALCULS_H_INCLUDED

#include "Graphe.h"

void affichageConsole(Graphe &g);
void SauvegardeFichier(Graphe &g);
void TestConnexite(Graphe &g);
void affichageIndiceSVG(Svgfile &out,Graphe &g);

#endif // CALCULS_H_INCLUDED
