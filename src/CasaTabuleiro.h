#ifndef CASATABULEIRO_H
#define CASATABULEIRO_H

#include <vector>

class CasaTabuleiro{
    public:
    int x, y; // Posicao da casa no tabuleiro
    int numPulos;
    bool casaFinal; // Limite do tabuleiro e objetivo do jogo
    char jogadorPresente;
    // vetor com todas as ligacoes que aquela casa faz
    std::vector<CasaTabuleiro*> casasLigadas;

    // Construtor
    CasaTabuleiro(int x, int y, int numPulos, bool casaFinal, char jogadorPresente);

    void adicionaLigacao(CasaTabuleiro* casa);
};


#endif // CASATABULEIRO_H