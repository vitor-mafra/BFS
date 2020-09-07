#include "../include/JogoDoPulo.h"
#include <queue>
#include <algorithm>
#include <tuple>

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
            // verifica se a ligacao na direcao +y eh possivel
            if (tabuleiro.at(aux).y + tabuleiro.at(aux).numPulos <= yMax){
                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux + tabuleiro.at(aux).numPulos)));

            }
            // verifica se a ligacao na direcao -y eh possivel
            if (tabuleiro.at(aux).y - tabuleiro.at(aux).numPulos >= 0){
                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux - tabuleiro.at(aux).numPulos)));

            }
            // verifica se ligacao na direcao +x eh possivel
            if (tabuleiro.at(aux).x + tabuleiro.at(aux).numPulos <= xMax){
                // determinando o numero de elementos que precisam ser pulados no vetor tabuleiro ate chegar a casa em questao
                int auxFinalDaLinha = yMax - tabuleiro.at(aux).y;
                int auxLinhasPuladas = (tabuleiro.at(aux).numPulos - 1) * (yMax + 1);
                int auxAteACasa = 1 + tabuleiro.at(aux).y;


                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux + auxFinalDaLinha + auxLinhasPuladas + auxAteACasa)));
            }
            // verifica se ligacao na direcao -x eh possivel
            if (tabuleiro.at(aux).x - tabuleiro.at(aux).numPulos >= 0){
                // determinando o numero de elementos que precisam ser voltados no vetor tabuleiro ate chegar a casa em questao
                int auxInicioDaLinha = tabuleiro.at(aux).y;
                int auxLinhasPuladas = (tabuleiro.at(aux).numPulos - 1) * (yMax + 1);
                int auxAteACasa = yMax - tabuleiro.at(aux).y + 1;

                tabuleiro.at(aux).adicionaLigacao(&(tabuleiro.at(aux - auxInicioDaLinha - auxLinhasPuladas - auxAteACasa)));

            }
            
        }
    }
}


void JogoDoPulo::joga(std::vector<CasaTabuleiro*> posicaoAtual){
    // fila que armazena as proximas jogadas
    std::queue<CasaTabuleiro*> filaPrioridade;
    // vetor para armazenar as jogadas que foram feitas
    std::vector<CasaTabuleiro*> jogadas;
    bool acabou = false;
    int rodada = 1;
    bool inseriu = false;
    
    // adiciona a fila as jogadas iniciais
    for (int i = 0; i < posicaoAtual.size(); i++){
        filaPrioridade.push(posicaoAtual.at(i));
    }

    // percorre todas as casas ligadas `aquela, i.e., anda em todas as direcoes possiveis
    while(!filaPrioridade.empty() && !acabou){
        // para cada casa que tenha uma ligacao direta com aquela
        for (int aux = 0; aux < filaPrioridade.front()->casasLigadas.size(); aux++){
            // se nao existir alguem ocupando essa casa, ocupe-a
            if (filaPrioridade.front()->casasLigadas.at(aux)->jogadorPresente == '\0'){
                filaPrioridade.front()->casasLigadas.at(aux)->jogadorPresente = filaPrioridade.front()->jogadorPresente;
                // marca na casa o valor do pulo anterior do jogador que a ocupa
                filaPrioridade.front()->casasLigadas.at(aux)->puloAnterior = filaPrioridade.front()->numPulos;

                // se esse espaco for o final, o jogador ganhou o jogo
                if(filaPrioridade.front()->casasLigadas.at(aux)->casaFinal){
                    std::cout << filaPrioridade.front()->casasLigadas.at(aux)->jogadorPresente << std::endl;
                    std::cout << rodada << std::endl;
                    // esvazia a lista e sai do loop, acabando com a execucao do jogo
                    while(!filaPrioridade.empty()) {
                        filaPrioridade.pop();
                    }
                    acabou = true;
                    break;
                }

                // se nao, adiciona a jogada ao vetor de jogadas, de acordo com sua ordem


                if (jogadas.size() == 0){
                    jogadas.push_back(filaPrioridade.front()->casasLigadas.at(aux));

                } else{
                    int pos = 0;
                    inseriu = false;

                    while(!inseriu){
                        while(jogadas.at(pos)->puloAnterior <= filaPrioridade.front()->casasLigadas.at(aux)->puloAnterior){
                            pos++;
                        }
                        // insere a jogada na ordem - i.e. crescente de acordo com o n do movimento anterior
                        jogadas.insert((jogadas.begin() + pos), filaPrioridade.front()->casasLigadas.at(aux));
                        inseriu = true;
                        break;
                        
                    }
                }
            
             // se for ligada a final, ainda ha chance de vitoria do jogador "atrasado"
            } else if(filaPrioridade.front()->casasLigadas.at(aux)->ligadaAFinal && \
                // desde que ele jogue primeiro que o jogador que ja ocupa essa casa
                filaPrioridade.front()->puloAnterior < filaPrioridade.front()->casasLigadas.at(aux)->puloAnterior){
                std::cout << filaPrioridade.front()->jogadorPresente << std::endl;
                //rodada++;
                std::cout << rodada << std::endl;
                 
            }
        }   

        // passa para o proximo elemento da fila
        filaPrioridade.pop();

        // se a fila ja acabou, mas novas jogadas estao registradas
        if (filaPrioridade.empty() && (jogadas.size() > 0)){
            rodada++;
            // adiciona as jogadas a fila - ja na ordem em que elas devem acontecer
            int iter = jogadas.size();
            for (int i = 0; i < iter; i++){
                filaPrioridade.push(jogadas.front());
                jogadas.erase(jogadas.begin());
            }
        }else if(filaPrioridade.empty() && jogadas.size() == 0){
            std::cout << "SEM VENCEDORES" << std::endl;
            acabou = true;
            break;
        }

    }
    
}
