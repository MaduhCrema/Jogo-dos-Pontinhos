// g++ testeminimax.cpp pontinhos.cpp -o minimax
#include <iostream>
#include "matriz.hpp"
#include <vector>
#include "pontinhos_helper.hpp"
#include "pontinhos.hpp"

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        std::cout << "Por favor especifique as dimensões através dos parâmetros de execução.\n";
        exit(1);
    }

    int linhas_pontinhos = atoi(argv[1]);
    int colunas_pontinhos = atoi(argv[2]);
    int jl1, jc1, jl2, jc2;

    Pontinhos *pontinhos = new Pontinhos(linhas_pontinhos, colunas_pontinhos);
    Matriz<char> *matriz = pontinhos->generateView();
   
    int aux = 0, player = 0;
    int status = 0;
    while((status == 0) || (status == 1)){
        
        if(aux % 2 == 0){
            player = PLAYER_1;
        }else{
            player = PLAYER_2;  
        }

        //system("clear");
        matriz->printMatriz();
        std::cout << "---------------PLAYER'S "<< abs(player) << " TURN------------------\n";
        std::cout << "Tamanho de pontinhos = " << sizeof(Pontinhos) << std::endl;
        if(player == PLAYER_1){
            std::cout << "Informe a jogada que deseja realizar (l1, c1, l2, c2)\n";
            std::cin >> jl1 >> jc1 >> jl2 >> jc2;
            while(((abs(jl1 - jl2) > 1) || (abs(jc1 - jc2)) > 1) || ((jl1 != jl2) && (jc1 != jc2))){
               std::cout << "Jogada inválida, você deve conectar apenas dois pontos na horizontal ou vertical" << std::endl;
               std::cout << "Informe a jogada que deseja realizar (l1, c1, l2, c2)\n";
              std::cin >> jl1 >> jc1 >> jl2 >> jc2;
            }
            status = pontinhos->fazerJogada(player, jl1, jc1, jl2, jc2);
        }else{
            //res_minimax temp = PontinhosHelper::minimax({pontinhos, {0, 0}, {0, 0}}, true);
            //res_minimax temp = PontinhosHelper::minimax({pontinhos, {0, 0}, {0, 0}}, true);

            res_minimax temp = PontinhosHelper::minimaxAB({pontinhos, {0, 0}, {0, 0}}, true, INT32_MIN, INT32_MAX);
            //std::cout << "jogada: " << temp.result.p1_gerador.linha << " " << temp.result.p1_gerador.coluna 
            //        << " " << temp.result.p2_gerador.linha << " " << temp.result.p2_gerador.coluna << "\n" ;


            status = pontinhos->fazerJogada(player, temp.result.p1_gerador.linha, temp.result.p1_gerador.coluna, 
                                    temp.result.p2_gerador.linha, temp.result.p2_gerador.coluna); 
        }
        //std::cout << "status = " << status << std::endl;
        std::cout << "\n";
        matriz = pontinhos->generateView();
        matriz->printMatriz();
        while(status == 1){
            if(player == PLAYER_1){
                std::cout << "Você fechou um quadrado!! Jogue novamente.\n";
                std::cout << "Informe a jogada que deseja realizar (l1, c1, l2, c2)\n";
                std::cin >> jl1 >> jc1 >> jl2 >> jc2;
                status = pontinhos->fazerJogada(player, jl1, jc1, jl2, jc2);
                matriz = pontinhos->generateView();
                matriz->printMatriz();
            }
            else{
                std::cout << "A IA fechou um quadrado e irá jogar novamente. \n";
                //res_minimax temp = PontinhosHelper::minimax({pontinhos, {0, 0}, {0, 0}}, true);
                res_minimax temp = PontinhosHelper::minimaxAB({pontinhos, {0, 0}, {0, 0}}, true, INT32_MIN, INT32_MAX);

                status = pontinhos->fazerJogada(player, temp.result.p1_gerador.linha, temp.result.p1_gerador.coluna, 
                                    temp.result.p2_gerador.linha, temp.result.p2_gerador.coluna);
                matriz = pontinhos->generateView();
                matriz->printMatriz();
            }
        }

        if(status == PLAYER_1){
            std::cout << "Player 1 venceu!\n";
        }
        if(status == PLAYER_2){
            std::cout << "Player 2 venceu!\n";
        }

        aux++;
    }
    delete (matriz);

    return 0;
    // std::vector<resultado> filhos;
    // Pontinhos *pontinhos = new Pontinhos(3, 3);
    // pontinhos->fazerJogada(-1, 0, 0, 0, 1);
    // Matriz<char> *view = pontinhos->generateView();
    // std::cout << "-----------Primeira jogada-----------\n";

    // view->printMatriz();

    // res_minimax temp = PontinhosHelper::minimax({pontinhos, {0, 0}, {0, 0}}, true);

    // pontinhos->fazerJogada(-2, temp.result.p1_gerador.linha, temp.result.p1_gerador.coluna, 
    //                         temp.result.p2_gerador.linha, temp.result.p2_gerador.coluna);

    // view = pontinhos->generateView();
    // std::cout << "-----------Segunda jogada-----------\n";
    // view->printMatriz();
}