#include <iostream>
#include "matriz.hpp"
#include <vector>
#include "pontinhos_helper.hpp"
#include "pontinhos.hpp"



int main (){
    Pontinhos *p = new Pontinhos(2, 3);

    p->fazerJogada(-1, 0, 0, 0, 1);
    p->fazerJogada(-1, 0, 0, 1, 0);
    p->fazerJogada(-1, 1, 0, 1, 1);
    //p->fazerJogada(-1, 1, 2, 1, 1);
    p->fazerJogada(-1, 0, 1, 0, 2);
    p->fazerJogada(-1, 0, 2, 1, 2);

    res_minimax rm = PontinhosHelper::minimaxAB(resultado{p, par{0, 0}, par{0, 0}}, true, INT32_MIN, INT32_MAX);
    p->fazerJogada(-2, rm.result.p1_gerador.linha, rm.result.p1_gerador.coluna, rm.result.p2_gerador.linha, rm.result.p2_gerador.coluna);

    Matriz<char> *m = p->generateView();
    m->printMatriz();
}


