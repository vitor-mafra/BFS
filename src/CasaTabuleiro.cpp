#include "CasaTabuleiro.h"

#include <iostream>

CasaTabuleiro::CasaTabuleiro(int x, int y, int numPulos, bool casaFinal, \
                                                        char jogadorPresente){
    this->x = x;
    this->y = y;
    this->numPulos = numPulos;
    this->casaFinal = casaFinal;
    this->jogadorPresente = jogadorPresente;
}

void CasaTabuleiro::adicionaLigacao(CasaTabuleiro* casa){
    // adiciona ligacao com outras casas
    casasLigadas.push_back(casa);

    //std::cout << "(" << x << "," <<  y << ")" << "->" << "(" << casa->x << "," << casa->y << ")" << std::endl;
}