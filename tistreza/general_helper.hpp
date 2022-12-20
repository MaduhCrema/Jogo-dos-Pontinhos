#ifndef GENERAL_HELPER_HPP
#define GENERAL_HELPER_HPP

class GeneralHelper{

public:
    template <typename datatype> static datatype** alocarMatriz(int linhas, int colunas);
    template <typename datatype> static void liberarMatriz(datatype **M);
    template <typename datatype> static void printMatriz(datatype **M, int linhas, int colunas);
};

template <typename datatype>
datatype** GeneralHelper::alocarMatriz(int linhas, int colunas){

    datatype **M;

    M = (datatype**)malloc(sizeof(datatype*) * linhas);
    M[0] = (datatype*)malloc(linhas * colunas * sizeof(datatype));

    for(int i = 1; i < linhas; i++){
        M[i] = M[0] + i * colunas;
    }

    return M;
}

template <typename datatype> 
void GeneralHelper::liberarMatriz(datatype **M){
    free(M[0]);
    free(M);
}

template <typename datatype>
void GeneralHelper::printMatriz(datatype **M, int linhas, int colunas){

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            std::cout << M[i][j];
        }
        std::cout << std::endl;
    }
}

#endif