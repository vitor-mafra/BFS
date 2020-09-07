#ifndef JOGODOPULO_H
#define JOGODOPULO_H

#include <iostream>
#include <vector>
#include "CasaTabuleiro.h"

class JogoDoPulo{
    public:
    std::vector<CasaTabuleiro> tabuleiro;

    JogoDoPulo();
    //~JogoDoPulo();

    void adicionaCasa(int x, int y, int numPulos, bool casaFinal, char jogadorPresente);
    void montaTabuleiro(int xMax, int yMax);
    void joga(std::vector<CasaTabuleiro*> posicaoAtual);
};

#endif // JOGODOPULO_H