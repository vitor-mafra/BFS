#include "../include/CasaTabuleiro.h"

#include <iostream>

CasaTabuleiro::CasaTabuleiro(int x, int y, int numPulos, bool casaFinal, \
                                                        char jogadorPresente){
    this->x = x;
    this->y = y;
    this->numPulos = numPulos;
    this->casaFinal = casaFinal;
    this->jogadorPresente = jogadorPresente;
    this->ligadaAFinal = false;
}

void CasaTabuleiro::adicionaLigacao(CasaTabuleiro* casa){
    // adiciona ligacao com outras casas
    casasLigadas.push_back(casa);

    if(casa->casaFinal == true){
        this->ligadaAFinal = true;
    }
}