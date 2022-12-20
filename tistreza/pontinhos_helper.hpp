#ifndef PONTINHOS_HELPER_HPP
#define PONTINHOS_HELPER_HPP
#include "pontinhos.hpp"
#include <iostream>
#include "matriz.hpp"
#include <set>
#include <iterator>
//class PontinhosHelper{

//public:

namespace PontinhosHelper{

    static Matriz<char>* generateView(Pontinhos *p_grid);
    static std::vector<resultado> gerarFilhos(Pontinhos *pai, int player);
    static res_minimax minimax(resultado position, bool maxPlayer);
    static res_minimax minimaxAB(resultado position, bool maxPlayer, int alpha, int beta);
    static Pontinhos* getPontinhosCopia(Pontinhos *base);
    static int avalJogada(int resultado);
    static res_minimax maxRes(res_minimax r1 , res_minimax r2);
    static res_minimax minRes(res_minimax r1 , res_minimax r2);
    static void clearResultados(std::vector<resultado>& result);
    static bool melhorJogada(resultado resultado_1, resultado resultado_2, Pontinhos *pai);
    static int avalJogada(Pontinhos *resultado);

};

static bool melhorJogada(resultado resultado_1, resultado resultado_2, Pontinhos *pai){

}

static void clearResultados(std::vector<resultado>& result){
    for (std::vector<resultado>::iterator it = result.begin(); it != result.end(); it++){
        delete(it->filho);
    }
}

static res_minimax PontinhosHelper::maxRes(res_minimax r1 , res_minimax r2){
    if(r1.avaliacao > r2.avaliacao)
        return r1;
    else
        return r2;
 }

 static res_minimax PontinhosHelper::minRes(res_minimax r1 , res_minimax r2){
    if(r1.avaliacao < r2.avaliacao)
        return r1;
    else
        return r2;
 }

//};

/* 
ʲ/ᶦ ⁰¹²³⁴⁵⁶⁷⁸⁹⁰¹²³⁴ 
  ⁰   0   1   2   3
  ¹ 0 *---*   *   *
  ²   | D | 
  ³ 1 *---*   *   *
  ⁴             
  ⁵ 2 *   *   *   *
  ⁶         
  ⁷ 3 *   *   *   *

   caracteres colunas = 2 do label da esquerda
            + m dos pontinhos
            + (m-1) * 3 dos tracinhos

    caracteres linhas = 1 label de cima
                        + m dos pontinhos
                        + (m-1) dos tracinhos
*/

//--------------PARECE ESTAR EM ORDEM(ñ mais)-------------
static Matriz<char>* PontinhosHelper::generateView(Pontinhos *p_grid){

    //std::cout << "Linhas e colunas do pontinho que vem no argumento: " << p_grid->getLinhas() << " " << p_grid->getColunas() << "\n";

    //determinacao das dimensoes
    int colunas = 2 + p_grid->getColunas() + (p_grid->getColunas() - 1) * 3;
    int linhas = 1 + 2 * p_grid->getLinhas() - 1;

    //std::cout << "antes da criação da matriz: ->>>>>>> linhas: " << linhas << " colunas: " << colunas << "\n";

    //alocacao da matriz de chars;
    Matriz<char> *view = new Matriz<char>(linhas, colunas); 

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            view->matriz[i][j] = ' ';
        }
    }

    //escrita dos labels e dos pontinhos como *
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){

            //setando os labels na primeira linha
            //linha 0 e coluna - 2 é múltipla de 4 
            if((i == 0) && (((j - 2) % 4) == 0)){
                view->matriz[i][j] = (j - 2)/4 + 0x30;
            }

            //setando os labels na primeira coluna
            //coluna 0 e linha - 1 é par
            if((j == 0) && (((i - 1) % 2) == 0)){
                view->matriz[i][j] = (i - 1)/2 + 0x30;
            }

            //se não vai escrever labels
            if((i != 0) && (j != 0)){

                //escrever os *
                //se a coluna é par e não múltipla de 4 e linha não é par
                if((j % 2 == 0) && (j % 4 != 0) && (i % 2 != 0)){
                    view->matriz[i][j] = '*';
                }
            }

        }
    }

    //escrita das arestas verticais
    //Verificação do direcional B nos pontinhos das (linhas-1) linhas
    for(int i = 0; i < p_grid->getLinhas() - 1; i++){
        for (int j = 0; j < p_grid->getColunas(); j++){

            if(p_grid->getPontinhoAt(i,j).direcionais[B] == 'v'){
                view->matriz[i * 2 + 2][j * 4 + 2] = '|';
            }
        }
    }

    //escrita das arestas horizontais
    //Verificacao do direcional R nos pontinhos das (colunas -1) colunas
    for (int i = 0; i < p_grid->getLinhas(); i++){
        for(int j = 0; j < p_grid->getColunas() - 1; j++){
            if(p_grid->getPontinhoAt(i,j).direcionais[R] == 'v'){
                view->matriz[i * 2 + 1][j * 4 + 3] = '-';
                view->matriz[i * 2 + 1][j * 4 + 4] = '-';
                view->matriz[i * 2 + 1][j * 4 + 5] = '-';
            }
        }
    }

    //escrita dos numerinhos do meio
    for(int i = 0; i < p_grid->getLinhas() - 1; i++){
        for(int j = 0; j < p_grid->getColunas() - 1; j++){

            int aux = p_grid->getQuadradoAt(i, j); 
            if(aux == PLAYER_1){
                view->matriz[(i + 1) * 2][j * 4 + 4] = '1';
            }
            if(aux == PLAYER_2){
                view->matriz[(i + 1) * 2][j * 4 + 4] = '2';
            }
        }
    }

    return view; 
}

// std::vector<resultado> PontinhosHelper::gerarFilhos(Pontinhos *pai, int player){
//     Pontinhos *copia = getPontinhosCopia(pai);

//     std::vector<resultado> filhos;

//     for(int i = 0; i < copia->getLinhas(); i++){
//         for(int j = 0; j < copia->getColunas(); j++){
//             for(int k = R; k <= B; k++){
                
//                 Pontinhos *temp = getPontinhosCopia(copia);
//                 //std::cout << "temp no gerar filhos: " << temp << '\n';

//                 int fechou_quadrado;
//                 if(temp->getGrid()->matriz[i][j].direcionais[k] == 'f'){
//                     if(k == R){

//                         fechou_quadrado = temp->fazerJogada(player, i, j, i, j + 1);
    
//                         if(fechou_quadrado == 1){
//                             std::vector<resultado> temp_filhos = gerarFilhos(temp, player);
//                             for(std::vector<resultado>::iterator it = temp_filhos.begin(); it != temp_filhos.end(); it++){
//                                 it->p1_gerador.linha = i;
//                                 it->p1_gerador.coluna = j;
//                                 it->p2_gerador.linha = i;
//                                 it->p2_gerador.coluna = j + 1;
//                             }
//                             std::vector<resultado>::iterator inicio = temp_filhos.begin(), fim = temp_filhos.end();
                            
//                             filhos.insert(filhos.end(), inicio, fim);
                            
                            
//                         }else{
//                             resultado temp_res; 
//                             temp_res.filho = temp;
//                             temp_res.p1_gerador = {i, j};
//                             temp_res.p2_gerador = {i, j+ 1};
//                             filhos.emplace_back(temp_res);
//                         }
//                     }else{
//                         fechou_quadrado = temp->fazerJogada(player, i, j, i + 1, j);

//                         if(fechou_quadrado == 1){
//                             std::vector<resultado> temp_filhos = gerarFilhos(temp, player);
//                             for(std::vector<resultado>::iterator it = temp_filhos.begin(); it != temp_filhos.end(); it++){
//                                 it->p1_gerador.linha = i;
//                                 it->p1_gerador.coluna = j;
//                                 it->p2_gerador.linha = i + 1;
//                                 it->p2_gerador.coluna = j;
//                             }
//                             std::vector<resultado>::iterator inicio = temp_filhos.begin(), fim = temp_filhos.end();
//                             filhos.insert(filhos.end(), inicio, fim);
                            
                            
//                         }else{
//                             resultado temp_res; 
//                             temp_res.filho = temp;
//                             temp_res.p1_gerador = {i, j};
//                             temp_res.p2_gerador = {i + 1, j};
//                             filhos.emplace_back(temp_res);
//                         }
//                     }

//                 }
                
//                 //delete(temp);
//             }  
//         }
//     }

//     std::cout << "Tamanho do vetor na funcao: " << filhos.size() << "\n";

//     Matriz<char> *view;
//     // int i = 0;
//     // for(std::vector<resultado>::iterator it = filhos.begin(); it != filhos.end(); it++, i++){

//     //     std::cout << "Filho dentro da funcao" << i << "\n"; 
//     //     std::cout << "Linhas e colunas do iterador dentro da funcao: " << it->filho->getLinhas() << " " << it->filho->getColunas() << "\n";
//     //     view = it->filho->generateView();
//     //     view->printMatriz();
//     // }

//     return filhos; 
// }

std::vector<resultado> PontinhosHelper::gerarFilhos(Pontinhos *pai, int player){
    Pontinhos *copia = getPontinhosCopia(pai);

    std::vector<resultado> filhos;

    for(int i = 0; i < copia->getLinhas(); i++){
        for(int j = 0; j < copia->getColunas(); j++){
            for(int k = R; k <= B; k++){
                
                Pontinhos *temp = getPontinhosCopia(copia);
                //std::cout << "temp no gerar filhos: " << temp << '\n';

                int fechou_quadrado;
                if(temp->getGrid()->matriz[i][j].direcionais[k] == 'f'){
                    if(k == R){

                        fechou_quadrado = temp->fazerJogada(player, i, j, i, j + 1);
                        resultado temp_res; 
                        temp_res.filho = temp;
                        temp_res.p1_gerador = {i, j};
                        temp_res.p2_gerador = {i, j+ 1};

                        if(fechou_quadrado == 1 || fechou_quadrado == PLAYER_1 || fechou_quadrado == PLAYER_2){
                            temp_res.fechou_quadrado = 1;
                        }else {
                            temp_res.fechou_quadrado = 0;
                        }

                        filhos.emplace_back(temp_res);

                    }else{
                       
                        fechou_quadrado = temp->fazerJogada(player, i, j, i + 1, j);
                        resultado temp_res; 
                        temp_res.filho = temp;
                        temp_res.p1_gerador = {i, j};
                        temp_res.p2_gerador = {i + 1, j};

                        if(fechou_quadrado == 1 || fechou_quadrado == PLAYER_1 || fechou_quadrado == PLAYER_2){
                            temp_res.fechou_quadrado = 1;
                        }else {
                            temp_res.fechou_quadrado = 0;
                        }

                        filhos.emplace_back(temp_res);
                    }

                }
            
            }  
        }
    }

    delete(copia);
    return filhos; 
}



Pontinhos* PontinhosHelper::getPontinhosCopia(Pontinhos *base){

    Pontinhos *temp = new Pontinhos(base->getLinhas(), base->getColunas());

    for(int i = 0; i < base->getLinhas(); i++){
        for(int j = 0; j < base->getColunas(); j++){
            temp->getGrid()->matriz[i][j] = base->getGrid()->matriz[i][j]; 
        }
    }
    
    for(int i = 0; i < base->getLinhas() - 1; i++){
        for(int j = 0; j < base->getColunas() - 1; j++){
            temp->getSquares()->matriz[i][j] = base->getSquares()->matriz[i][j]; 
        }
    }

    return temp;
}

res_minimax PontinhosHelper::minimaxAB(resultado position, bool maxPlayer, int alpha, int beta){
    std::vector<resultado> filhos;
    int player = 0;

    if(maxPlayer)
        player = PLAYER_2;
    else
        player = PLAYER_1;

    filhos = gerarFilhos(position.filho, player);

    //std::cout << "cheguei aqui a\n"; 
    int depth = filhos.size();
    //std::cout << "tamanho do vetor de filhos: " << depth << std::endl;

    // se não tiver gerado filhos, caso base
    if(depth == 0){
        res_minimax res;
        res.result = position;
        res.avaliacao = avalJogada(position.filho->quemGanhou());
                // std::cout << "FOLHAAAAAAAAAAAAAAAA\n";
                // std::cout << "avaliacao na folha: " << res.avaliacao << "\n";   
                // std::cout << "movimento que levou a esse estado: " << res.result.p1_gerador.linha << " "
                //             << res.result.p1_gerador.coluna << " " << res.result.p2_gerador.linha << " "
                //             << res.result.p2_gerador.coluna << "\n";
                //             std::cout << "estado que a folha avaliou: \n";
                // Matriz<char> *m = position.filho->generateView();
                // m->printMatriz();
                // std::cout << std::endl;
        filhos.clear();
        filhos.shrink_to_fit();
        return res;
    }

    if(!maxPlayer){

        //std::cout << "cheguei aqui a\n"; 
        res_minimax current_min; 
        current_min.avaliacao = INT32_MAX;

        for(std::vector<resultado>::iterator it = filhos.begin(); it != filhos.end(); it++){
            
                            
            //se o position.fechou_quadrado retorna falso, chamo com o max 
            //senão, chamo com o min de novo
            bool fechou_quadrado;
            if (it->fechou_quadrado == 1){
                fechou_quadrado = false;
            }else{
                fechou_quadrado = true;
            }

            res_minimax current = minimaxAB((*it), fechou_quadrado, alpha, beta);
            
            if(current.avaliacao < current_min.avaliacao){
                current_min = current; 
                current_min.result.p1_gerador = it->p1_gerador;
                current_min.result.p2_gerador = it->p2_gerador;
            }

            //current_min = minRes(current_min, current);
            
            beta = std::min(beta, current_min.avaliacao);
            //delete(it->filho);
            if(beta <= alpha){
                break;
            }
        }
    
        //filhos.clear();
        //filhos.shrink_to_fit();
                // std::cout << "avaliacao na folha: " << current_min.avaliacao << "\n";   
                // std::cout << "movimento que levou a esse estado: " << current_min.result.p1_gerador.linha << " "
                //             << current_min.result.p1_gerador.coluna << " " << current_min.result.p2_gerador.linha << " "
                //             << current_min.result.p2_gerador.coluna << "\n";
                //             std::cout << "estado que o min avaliou: \n";
                // Matriz<char> *m = current_min.result.filho->generateView();
                // m->printMatriz();
        return current_min;
    }

    else {
        //        std::cout << "cheguei aqui b\n"; 


        res_minimax current_max;
        current_max.avaliacao = INT32_MIN;       
        for(std::vector<resultado>::iterator it = filhos.begin(); it != filhos.end(); it++){


           

            //se o position.fechou_quadrado retorna falso, chamo com o max 
            //senão, chamo com o min de novo
            bool fechou_quadrado;
            if (it->fechou_quadrado == 1){
                fechou_quadrado = true;
            }else{
                fechou_quadrado = false;
            }

            res_minimax current = minimaxAB((*it), fechou_quadrado, alpha, beta);
            //current_max = maxRes(current_max, current);
            if(current_max.avaliacao < current.avaliacao){
                current_max = current;
                current_max.result.p1_gerador = it->p1_gerador;
                current_max.result.p2_gerador = it->p2_gerador;
            }
            
            alpha = std::max(alpha, current_max.avaliacao);
            //delete(it->filho);    
            if(beta <= alpha){
                break;
            }
        }

        //filhos.clear();
        //filhos.shrink_to_fit();
        //std::cout << "current max : " << current_max.avaliacao << "\n";
        //std::cout << "jogada: " << current_max.result.p1_gerador.linha << " " << current_max.result.p1_gerador.coluna 
        //         << " " << current_max.result.p2_gerador.linha << " " << current_max.result.p2_gerador.coluna << "\n" ;
                // std::cout << "avaliacao na folha: " << current_max.avaliacao << "\n";   
                // std::cout << "movimento que levou a esse estado: " << current_max.result.p1_gerador.linha << " "
                //             << current_max.result.p1_gerador.coluna << " " << current_max.result.p2_gerador.linha << " "
                //             << current_max.result.p2_gerador.coluna << "\n";
                //             std::cout << "estado que o min avaliou: \n";
                // Matriz<char> *m = current_max.result.filho->generateView();
                // m->printMatriz();
        return current_max;
    }
}


res_minimax PontinhosHelper::minimax(resultado position, bool maxPlayer){

    int player;
    if (maxPlayer == true)
        player = PLAYER_2;
    else
        player = PLAYER_1;

    std::vector<resultado> filhos = gerarFilhos(position.filho, player);

    for(std::vector<resultado>::iterator it = filhos.begin(); it != filhos.end(); it++){
        Matriz<char> *view  = PontinhosHelper::generateView(it->filho);
        
        std::cout << "jogada: " << it->p1_gerador.linha << " " << it->p1_gerador.coluna << " " << 
                                   it->p2_gerador.linha << " " << it->p2_gerador.coluna << "\n" ;
        view->printMatriz();
        std::cout << "Fechou quadrado :" << it->fechou_quadrado << "\n";
        std::cout << std::endl;
    }

    //caso base
    if (filhos.size() == 0){
        
        
    }


}

static int PontinhosHelper::avalJogada(int resultado){
     if (resultado == -1)
         return -2;
     else if (resultado == -2)
         return 2;
     else
         return resultado;
}

// static int PontinhosHelper::avalJogada(Pontinhos *resultado){
    
//     int ret{0};
//     for(int i = 0; i < resultado->getLinhas() - 1; i++){
//         for(int j = 0; j < resultado->getColunas() - 1; j++){

//             if(resultado->getSquares()->matriz[i][j] == PLAYER_2){
//                 ret++;
//             }
//         }
//     }

//     return ret;
// }



#endif