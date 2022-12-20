#ifndef OBJETOJS_HPP
#define OBJETOJS_HPP

#include "pontinhos.hpp"
#include <vector>

class ObjetoJS{
private:
    int linhas;
    int colunas;
    int size_AL; 
    int size_SQ;

public:
    std::vector<int> array_links;
    std::vector<int> array_squares;
    ObjetoJS(int linhas, int colunas, int size_AL, std::vector<int> array_links, int size_SQ, std::vector<int> array_squares);
    //~ObjetoJS();
};

#endif