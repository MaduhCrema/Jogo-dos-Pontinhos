#ifndef PONTINHOS_CPP
#define PONTINHOS_CPP
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "pontinhos_helper.hpp"
#include "pontinhos.hpp"
#include "matriz.hpp"

int Pontinhos::getLinhas(){
    return this->linhas;    
} 

//std::vector<resultado> Pontinhos::gerarFilhos(){
//    return PontinhosHelper::gerarFilhos(this);
//}

int Pontinhos::getColunas(){
    return this->colunas;
}

Matriz<char>* Pontinhos::generateView(){
    return PontinhosHelper::generateView(this);
}

pontinho Pontinhos::getPontinhoAt(int linha, int coluna){
    return grid->matriz[linha][coluna];
}

Pontinhos::Pontinhos(int linhas, int colunas){

    this->linhas = linhas;
    this->colunas = colunas;

    grid = new Matriz<pontinho>(linhas, colunas);
    squares = new Matriz<int>(linhas - 1, colunas - 1);

    // inicializa todos os direcionais como falso, depois fazemos o tratamento de casos especiais
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            grid->matriz[i][j].direcionais[L] = 'f';
            grid->matriz[i][j].direcionais[T] = 'f';
            grid->matriz[i][j].direcionais[R] = 'f';
            grid->matriz[i][j].direcionais[B] = 'f';
        }
    }

    for(int i = 0; i < linhas; i++){
        grid->matriz[i][0].direcionais[L] = 'n';
        grid->matriz[i][colunas - 1].direcionais[R] = 'n';
    }

    for(int j = 0; j < colunas; j++){
        grid->matriz[0][j].direcionais[T] = 'n';
        grid->matriz[linhas - 1][j].direcionais[B] = 'n';
    }

    for(int i = 0; i < linhas - 1; i++){
        for(int j = 0; j < colunas - 1; j++){
            squares->matriz[i][j] = 0;
        }
    }
}

/* 
ʲ/ᶦ ⁰¹²³⁴⁵⁶⁷⁸⁹⁰¹²³⁴ 
  ⁰   0   1   2   3
  ¹ 0 *---*   *   *
  ²   |00 |01  02
  ³ 1 *---*   *   *
  ⁴    10  11  12
  ⁵ 2 *   *   *   *
  ⁶    20  21  22
  ⁷ 3 *   *   *   *

    pontinhos pivôs -> pontinhos acima e À esquerda
    índice do pivô -> mesmo índice da matriz de quadrados
*/
//matriz closed_squares salva o estado de quadrados fechados



bool Pontinhos::atualizarMatrizQuadrado(int player, int l1, int c1, int l2, int c2){

    bool fechou_quadrado = false;

    std::vector<par> q_adjacentes1, q_adjacentes2;

    //geracao dos quadrados que o ponto toca
    for(int i = 1; i >= 0 ; i--){
        for(int j = 1; j >= 0; j--){

            //verificar se primeiro está no range de quadrados
            if(((l1 - i) >= 0) && ((l1 - i) < (linhas -1))
                && ((c1 - j) >= 0) && ((c1 - j) < (colunas -1))){
                
                q_adjacentes1.push_back((par){l1 - i, c1 - j});
            }

            //verificar se segundo ponto está no range de quadrados
            if(((l2 - i) >= 0) && ((l2 - i) < (linhas -1))
                && ((c2 - j) >= 0) && ((c2 - j) < (colunas -1))){
                
                q_adjacentes2.push_back((par){l2 - i, c2 - j});
            }
        }

    }

    //determinação dos quadrados que os dois pontos tocam
    std::vector<par> intersecoes;
    for (std::vector<par>::iterator it1 = q_adjacentes1.begin(); it1 != q_adjacentes1.end(); it1++){
        for(std::vector<par>::iterator it2 = q_adjacentes2.begin(); it2 != q_adjacentes2.end(); it2++){        
            if((it1->coluna == it2->coluna) && (it1->linha == it2->linha))
                intersecoes.push_back(*it1);
        }
    }

    //atualizacao dos quadrados que os dois pontos tocam
    //vamos pensar que a mágica do tratamento de erro e do usuário inteligente estão atuando,
    //e ninguém jogou onde já tem jogada ou nada do tipo
    for(std::vector<par>::iterator it = intersecoes.begin(); it != intersecoes.end(); it++){

        int *quadrado{&squares->matriz[it->linha][it->coluna]};
        (*quadrado)++;

        if(*quadrado == QUATRO_ARESTAS){
            *quadrado = player;
            fechou_quadrado = true;
            
        }
    }

    return fechou_quadrado;
}

bool Pontinhos::acabouJogo(){

    for(int i = 0; i < linhas - 1; i++){
        for(int j = 0; j < colunas - 1; j++){
            if(squares->matriz[i][j] != PLAYER_1 && squares->matriz[i][j] != PLAYER_2){
                return false;
            }
        }
    }

    return true;
}

int Pontinhos::quemGanhou(){

    int p1{0}, p2{0};

    for(int i = 0; i < linhas - 1; i++){
        for(int j = 0; j < colunas - 1; j++){
            if(squares->matriz[i][j] == PLAYER_1){
                p1++;
            }else{
                p2++;
            }
        }
    }

    if(p1 > p2)
        return PLAYER_1; 
    else if (p2 > p1)
        return PLAYER_2;
    else
        return 0;
}

int Pontinhos::fazerJogada(int player, int l1, int c1, int l2, int c2){

        int jl1, jc1, jl2, jc2;

        // verificar validade
        // escreve jogada no grid (atualizar direcionais dos pares ordenados)
        // se a primeira linha for maior que a segunda, deve haver conexão do TOP e BOTTOM, respectivamente, para os pontos
        if((l1 > l2) && (c1 == c2)){
            grid->matriz[l1][c1].direcionais[T] = 'v';
            grid->matriz[l2][c2].direcionais[B] = 'v';
        }

        // se a segunda linha for maior que a primeira, deve haver conexão do BOTTOM e TOP, respectivamente, para os pontos
        else if((l2 > l1) && (c1 == c2)){
            grid->matriz[l1][c1].direcionais[B] = 'v';
            grid->matriz[l2][c2].direcionais[T] = 'v';
        }

        // se a primeira coluna for maior que a segunda, deve haver conexão do LEFT e RIGHT, respectivamente, para os pontos
        else if((c1 > c2) && (l1 == l2)){
            grid->matriz[l1][c1].direcionais[L] = 'v';
            grid->matriz[l2][c2].direcionais[R] = 'v';
        }

        // se a segunda coluna for maior que a primeira, deve haver conexão do RIGHT e LEFT, respectivamente, para os pontos
        else if((c2 > c1) && (l1 == l2)){
            grid->matriz[l1][c1].direcionais[R] = 'v';
            grid->matriz[l2][c2].direcionais[L] = 'v';
        }
    
    

    // verifica se fechou quadrado, para atualizar a matriz de quadrados fechados (se necessário)
        // verifica se fechou quadrado, para atualizar a matriz de quadrados fechados (se necessário)
    return atualizaJogada(player, l1, c1, l2, c2);
}

int Pontinhos:: atualizaJogada(int player, int l1, int c1, int l2, int c2){
    int jl1, jc1, jl2, jc2;
    int status = 0;

    if(atualizarMatrizQuadrado(player, l1, c1, l2, c2)){
        // se fechou, verifica se  o jogo terminou
        if(acabouJogo()){
            status = quemGanhou();            
        }
        else{
            status = 1;
        }
    }
    return status;
}

Matriz<pontinho>* Pontinhos::getGrid(){
    return grid;
}

Matriz<int>* Pontinhos::getSquares(){
    return squares;
}

Pontinhos::~Pontinhos(){
    delete(grid);
    delete(squares);
}


int Pontinhos::getQuadradoAt(int linha, int coluna){
    return squares->matriz[linha][coluna];
}


#endif