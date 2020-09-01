/*  
    Algoritmos 1 - Trabalho Pratico 1 (Jogo do Pulo - BFS)

    Vitor de Oliveira Mafra - 2018046831
    UFMG, Setembro de 2020
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "JogoDoPulo.h"
#include "CasaTabuleiro.h"

int main(int argc,  char** argv){

    std::ifstream input(argv[1]);
    std::string linha;

    int tamLinhas, tamColunas, numJogadores;

    // obtendo o tamanho do tabuleiro
    std::getline(input, linha);
    linha = std::string(linha);

    tamLinhas = stoi(linha.substr(0, linha.find(" ")));
    tamColunas = stoi(linha.substr(linha.find(" ") + 1, linha.length()));

    // obtendo o numero de jogadores
    std::getline(input, linha);
    numJogadores = stoi(linha);

    // montando o tabuleiro
    int tabuleiroMatriz[tamLinhas][tamColunas];
    bool casaFinal = false;

    JogoDoPulo *tabuleiro = new JogoDoPulo();

    std::vector<CasaTabuleiro*> posicoesIniciais;

    for (int i = 0; i < tamLinhas; i++){
        std::getline(input, linha);
        for(int j = 0; j < tamColunas; j++){
            // para cada linha do arquivo - ou seja, linha da matriz - consome
            // seu primeiro elemento e o atribui ao prox elemnto da matriz
            tabuleiroMatriz[i][j] = stoi(linha.substr(0, linha.find(" ")));

            if (i == (tamLinhas - 1) && j == (tamColunas - 1)){
                casaFinal = true;
            }

            tabuleiro->adicionaCasa(i, j, tabuleiroMatriz[i][j], casaFinal, '\0');
            // atualiza a linha para que o primeiro elemento seja sempre o prox
            linha = linha.substr(linha.find(" ") + 1, linha.length());
        }
        // sei que em Python o metodo split() faz esse trabalho de forma muito
        // robusta. Nao consegui encontar facilmente algo parecido em C++
    }

    // pegando a posicao inicial de cada jogador
    std::map<int, char> dictJogadores = {
        { 0, 'A' },{ 1, 'B' },{ 2, 'C' },{3, 'D'},{4, 'E'},
            {5, 'F'},{6, 'G'},{7, 'H'},{8, 'I'},{9, 'J'},{10, 'K'}
    };

    for (int k = 0; k < numJogadores; k++){
        std::getline(input, linha);

        int i_inicial = stoi(linha.substr(0, linha.find(" ")));
        int j_inicial = stoi(linha.substr(linha.find(" ") + 1, linha.length()));

        for (int i = 0; i < tabuleiro->tabuleiro.size(); i++){
            if(i_inicial == tabuleiro->tabuleiro.at(i).x && j_inicial == \
                                                tabuleiro->tabuleiro.at(i).y){

                tabuleiro->tabuleiro.at(i).jogadorPresente = dictJogadores[k];
                // guardar a posicao inicial para quando for comecar o jogo
                posicoesIniciais.push_back(&(tabuleiro->tabuleiro.at(i)));

                break;
            }
        }

    }


    // faz as ligacoes do grafo passando os limites do tabuleiro
    tabuleiro->montaTabuleiro((tamLinhas - 1), (tamColunas - 1));
    tabuleiro->joga(posicoesIniciais);

    input.close();

    return 0;
}