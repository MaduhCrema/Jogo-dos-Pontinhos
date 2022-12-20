#ifndef OBJETOJS_CPP
#define OBJETOJS_CPP

#include "objetojs.hpp"

// construtor da classe
ObjetoJS::ObjetoJS(int linhas, int colunas, int size_AL, std::vector<int> array_links, int size_SQ, std::vector<int> array_squares){
    this->linhas = linhas;
    this->colunas = colunas;
    this->size_AL = size_AL;
    this->array_links = array_links;
    this->size_SQ = size_SQ;
    this->array_squares = array_squares;
}

#endif