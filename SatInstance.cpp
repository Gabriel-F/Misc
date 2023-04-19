
#include "SatInstance.h"

using namespace std;


/*
SatInstance::SatInstance(int variaveis, int clausulas)
{
    clausula_atual_=0;
    assinalamento_das_variaveis_=new int[variaveis+1];
    inicio_das_clausulas_ =new int[clausulas+1];
    numero_de_lit_clausula_=new int[clausulas+1];
    clausulas_= new int[20*clausulas];
    clausulas_usando_literais_.reserve(2*(variaveis+1));
    numero_de_lit_clausula_[clausula_atual_]=0;
}*/

void SatInstance::AdicionaClausula(){
    int proxima_clausula=clausula_atual_+1;
    inicio_das_clausulas_[proxima_clausula]=inicio_das_clausulas_[clausula_atual_]+numero_de_lit_clausula_[clausula_atual_];
    numero_de_lit_clausula_[proxima_clausula]=0;
    clausula_atual_=proxima_clausula;

}

void SatInstance::AdicionaLiteral(int literal){
   int posicao_prox_literal;
   cout<<"clausula_atual_  ==  "<<clausula_atual_<<endl;  //deveria ser 0, deu 1
   posicao_prox_literal=inicio_das_clausulas_[clausula_atual_] + numero_de_lit_clausula_[clausula_atual_];
   cout<<posicao_prox_literal<<endl;
   clausulas_[posicao_prox_literal]=literal;  //tinha lixo em posicao_prox_literal
   numero_de_lit_clausula_[clausula_atual_]++;
   clausulas_usando_literais_[literal].push_back(clausula_atual_);
   //cout<<"BUG literal="<<literal<<"  clausula="<<clausula_atual_<<endl;
}



SatInstance::SatInstance(string& filename)
{
    int i;
    ifstream dimacs(filename);
    char buffer[200];
    dimacs.getline(buffer, 200, '\n');
    string cabecalho(buffer);
    trata_linha_cabecalho_(cabecalho);
    while (dimacs.getline(buffer, 200, '\n'))
    {
        //dimacs.getline(buffer, 200, '\n');
        string s(buffer);
        //cout<<"adiciona clausula vazia"<<endl;
        trata_linha_clausula_(s);
        
        
    }
}

int SatInstance::trata_linha_clausula_(string & linha)
{
    cout<<"adiciona clausula vazia"<<endl;
    AdicionaClausula();
    istringstream in(linha);
    int lit_dimacs, nosso_lit;
    cout<<linha<<endl;
    while (in >> lit_dimacs)
        {
            cout<<lit_dimacs<<endl;
            if (lit_dimacs == 0)
                break;
            if (lit_dimacs>0)
                {nosso_lit=2*lit_dimacs;
                //AdicionaLiteral(nosso_lit); 
                }
            else if (lit_dimacs<0)
                {nosso_lit=-2*lit_dimacs+1;
                //AdicionaLiteral(nosso_lit); 
                }
            else if (lit_dimacs == 0)
                break;
            cout <<"antes adiciona literal ="<< nosso_lit << endl;
            AdicionaLiteral(nosso_lit);  //positivo: *2 negativo *-2+1 aula
            cout <<"depois adiciona literal ="<< nosso_lit << endl;
        }
    return 0;
}

int SatInstance::trata_linha_cabecalho_(string & linha)
{
    istringstream in(linha);
    int num_variaveis, num_clausulas;
    string word;
    in >> word; //cout<<"string discarded ="<<word<<endl;
    in >> word; //cout<<"string discarded ="<<word<<endl;
    in >> num_variaveis; cout<<"number of variables is ="<<num_variaveis<<endl;
    in >> num_clausulas; cout<<"number of clauses is ="<<num_clausulas<<endl;  
    num_variaveis_=num_variaveis;
    clausula_atual_=0;
    cout<<"clausula_atual_  ==  "<<clausula_atual_<<endl;  //deveria ser 0, deu 1
    assinalamento_das_variaveis_=new int[num_variaveis+1];
    inicio_das_clausulas_ =new int[num_clausulas+1];  //uma posição de inicio por clausula
    inicio_das_clausulas_[0]=0; //conserto feio
    inicio_das_clausulas_[1]=0; //conserto feio
    numero_de_lit_clausula_=new int[num_clausulas+1]; //um contador de literais por clausula
    clausulas_= new int[20*num_clausulas];
    //clausulas_usando_literais_.reserve(2*(num_variaveis+1));  //nao funciona, dá bug
    clausulas_usando_literais_.resize(2*(num_variaveis+1)); //funciona
    numero_de_lit_clausula_[clausula_atual_]=0; //clausula atual tem 0 literais, nenhum foi lido
    numero_de_lit_clausula_[0]=0; //conserto feio
    numero_de_lit_clausula_[1]=0; //conserto feio

cout<<"clausula_atual_  ==  "<<clausula_atual_<<endl;  //deveria ser 0, deu 1

    return 0;
}


void SatInstance::print()
{
for (int i=1; i<=clausula_atual_; i++)
    {
    cout <<"clausula "<<i;
    cout <<" inicio="<<inicio_das_clausulas_[i];
    cout<<" numero_de_literais="<<numero_de_lit_clausula_[i]<<endl;
    }
for (int c=1; c<=clausula_atual_; c++)
    {
    cout<<"clausula "<<c<<endl;
    for (int l=0; l<numero_de_lit_clausula_[c]; l++)
        {
            cout<<clausulas_[(l+inicio_das_clausulas_[c])]<<"  ";
        }
        cout<<endl;
    }
for (int l=2; l<(2*(num_variaveis_+1)); l++) //for nas listas
    {
        cout<<"literal "<<l<<" aparece nas clausulas"<<endl;
        for(    list<int>::iterator iter = clausulas_usando_literais_[l].begin(); //for em cada lista, com iterador
                iter != clausulas_usando_literais_[l].end(); 
                iter++)
        {
        cout<<*iter<<" ";
        }
        cout<<endl;
    }
}


