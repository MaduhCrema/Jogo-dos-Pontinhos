#ifndef MATRIZ_HPP
#define MATRIZ_HPP
#include "general_helper.hpp"

template <typename datatype>
class Matriz{
private:

    int linhas;
    int colunas;
    
public:

    datatype **matriz;
    Matriz(int linhas, int colunas);
    ~Matriz();
    int getLinhas();
    int getColunas();
    void printMatriz();

};

template <typename datatype> 
Matriz<datatype>::Matriz(int linhas, int colunas){
    this->linhas = linhas;
    this->colunas = colunas;
    matriz = GeneralHelper::alocarMatriz<datatype>(this->linhas, this->colunas);
}

template <typename datatype>
Matriz<datatype>::~Matriz(){
    GeneralHelper::liberarMatriz<datatype>(matriz);
}

template <typename datatype>
int Matriz<datatype>::getColunas(){
    return this->colunas;
}

template <typename datatype>
int Matriz<datatype>::getLinhas(){
    return this->linhas;
}

template <typename datatype>
void Matriz<datatype>::printMatriz(){
    GeneralHelper::printMatriz<datatype>(matriz, linhas, colunas);
}
#endif