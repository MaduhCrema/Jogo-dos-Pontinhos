#include <iostream>
#include "pontinhos.hpp"
#include "matriz.hpp"
#include "objetojs.hpp"
#include <algorithm>
#include <string.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "pontinhos_helper.hpp"

int main(int argc, char **argv){
    int linhas_pontinhos = atoi(argv[1]);
    int colunas_pontinhos = atoi(argv[2]);
    int size_AL = atoi(argv[3]);
    //int array_links = atoi(argv[4]);
    int size_SQ = atoi(argv[5]);
    //int array_squares = atoi(argv[6]);

    std::vector<int> array_links, array_squares;
    char** percorre = (char**) malloc(sizeof(char*));
    
    int aux = 5;
    while(strcmp(argv[aux], "],") != 0){
        array_links.push_back(atoi(argv[aux]));
        aux++;
    }

    int count = 0;
    // for(std::vector<int>::iterator it = array_links.begin(); it != array_links.end(); it++){
    //     std::cout << "array_links[" << count << "] = " << *it << std::endl;
    //     count++;
    // }

    aux += 2;
    if(strcmp(argv[aux], "[]") != 0)
    {
        while((strcmp(argv[aux], "]") != 0)){
            //std::cout << "argv[aux] = " << argv[aux] << std::endl;
            if((strcmp(argv[aux], "[") != 0)){ 
                array_squares.push_back(atoi(argv[aux]));
                aux++;
            }
            else{
                aux++;
            }
        }
    }


    count = 0;
    for(std::vector<int>::iterator it = array_squares.begin(); it != array_squares.end(); it++){
        //std::cout << "array_squares[" << count << "] = " << *it << std::endl;
        count++;
    }

    //ObjetoJS *argumento = new ObjetoJS(linhas_pontinhos, colunas_pontinhos, size_AL, array_links, size_SQ, array_squares);

    Pontinhos *pontinhos = new Pontinhos(linhas_pontinhos, colunas_pontinhos);
    // Matriz<char> *matriz = pontinhos->generateView();
    // matriz->printMatriz();

    par p1, p2, sq;
    std::vector<int>::iterator it = array_links.begin();
    while(it != array_links.end() - 3){
        //std::cout << "cheguei aqui jogada\n";
        p1.linha = *it;
        p1.coluna = *(it+1);        

        p2.linha = *(it+2);
        p2.coluna = *(it+3);

        pontinhos->fazerJogada(-1, p1.linha, p1.coluna, p2.linha, p2.coluna);
        // matriz = pontinhos->generateView();
        // matriz->printMatriz();

        if(it+4 == array_links.end()){
            break;
        }
        else
             it+=4;
    }


    if(array_squares.size() > 0){
        it = array_squares.begin();
        while(it != array_squares.end() - 2){
            sq.linha = *(it);
            sq.coluna = *(it+1);
            int player = *(it+2);

            pontinhos->forcaQuadrado(sq.linha, sq.coluna, player);

            if(it+3 == array_squares.end()){
                break;
            }
            else
                it+=3;
        }
    }

    int status = 0;
    res_minimax IA = PontinhosHelper::minimaxAB(resultado{pontinhos, par{0, 0}, par{0, 0}}, true, INT32_MIN, INT32_MAX);
    std::cout << IA.result.p1_gerador.linha << " " << IA.result.p1_gerador.coluna << " " << IA.result.p2_gerador.linha << " " << IA.result.p2_gerador.coluna << std::endl;

    delete(pontinhos);

    return 0;
}