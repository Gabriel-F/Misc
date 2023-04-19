
#ifndef SATINSTANCE_H
#define SATINSTANCE_H


#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class SatInstance {
    
    int num_variaveis_;                 //numero de variaveis
    int clausula_atual_;                //clausula atual sendo lida no leitor
    int *assinalamento_das_variaveis_;  //vetor com o assinalamento das variaveis
    int *inicio_das_clausulas_;         //vetor com a posicao de inicio de cada clausula
    int *numero_de_lit_clausula_;       //vetor com o numero de literais de cada clausula
    int *clausulas_;                    //vetor com as clausulas propriamente ditas
    vector< list<int> > clausulas_usando_literais_; //vetor de listas de inteiros
    int trata_linha_clausula_(string & linha);
    int trata_linha_cabecalho_(string & linha);

    public:
        SatInstance (string & filename); //construtor que recebe nome de arquivo
        //SatInstance (int variaveis, int clausulas);
        void AdicionaClausula();
        void AdicionaLiteral(int literal);
        void print();
};

#endif
