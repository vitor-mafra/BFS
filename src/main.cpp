/*  
    Algoritmos 1 - Trabalho Pratico 1 (Jogo do Pulo - BFS)

    Vitor de Oliveira Mafra - 2018046831
    UFMG, Setembro de 2020
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "../include/JogoDoPulo.h"
#include "../include/CasaTabuleiro.h"

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
    bool casaFinal = false;

    JogoDoPulo *tabuleiro = new JogoDoPulo();

    std::vector<CasaTabuleiro*> posicoesIniciais;

    for (int i = 0; i < tamLinhas; i++){
        std::getline(input, linha);
        for(int j = 0; j < tamColunas; j++){
            // verifica se eh a casa final
            if (i == (tamLinhas - 1) && j == (tamColunas - 1)){
                casaFinal = true;
            }
        // sei que em Python o metodo split() faz esse trabalho de forma muito
        // robusta. Nao consegui encontar facilmente algo | parecido em C++
        //                                                |
        //                                                v
            tabuleiro->adicionaCasa(i, j, stoi(linha.substr(0, linha.find(" "))), casaFinal, '\0');
            // atualiza a linha para que o primeiro elemento seja sempre o prox
            linha = linha.substr(linha.find(" ") + 1, linha.length());
        }

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