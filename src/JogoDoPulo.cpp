#include "JogoDoPulo.h"

// Definindo os construtores
JogoDoPulo::JogoDoPulo(){
    // o construtor de um vetor ja inicializa um vetor vazio. Portanto, nao eh
    // necessario inicializar um tabuleiro vazio
}


void JogoDoPulo::adicionaCasa(int x, int y, int numPulos, bool casaFinal, char jogadorPresente){
    // Cria um objeto do tipo casa
    CasaTabuleiro *casa = new CasaTabuleiro(x, y, numPulos, casaFinal, jogadorPresente);

    // entao, adiciona ele ao vetor
    tabuleiro.push_back(*casa);

}


void JogoDoPulo::montaTabuleiro(int xMax, int yMax){
    // para cada vetor da lista de casas
    for (int aux = 0; aux < tabuleiro.size(); aux++){
        // verifica se existe uma ligacao
        if(tabuleiro.at(aux).numPulos != 0){
            // verifica se ligacao na direcao +y eh possivel
            if (tabuleiro.at(aux).y + tabuleiro.at(aux).numPulos <= yMax){
                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux + tabuleiro.at(aux).numPulos)));

            }
            // verifica se ligacao na direcaco -y eh possivel
            if (tabuleiro.at(aux).y - tabuleiro.at(aux).numPulos >= 0){
                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux - tabuleiro.at(aux).numPulos)));

            }
            // verifica se a ligacao na direxao +x eh possivel
            if (tabuleiro.at(aux).x + tabuleiro.at(aux).numPulos <= xMax){
                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux + tabuleiro.at(aux).numPulos)));

            }
            // verifica se a ligacao na direxao -x eh possivel
            if (tabuleiro.at(aux).x - tabuleiro.at(aux).numPulos >= 0){
                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux - tabuleiro.at(aux).numPulos)));

            }
        }
    }
}


void JogoDoPulo::joga(std::vector<CasaTabuleiro*> posicoesIniciais){
    
}