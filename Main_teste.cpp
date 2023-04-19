
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

// defined std::cout
#include <iostream>

#include "SatInstance.h"

using namespace std;

void create_dimacs(string &);
int process_dimacs_file(string& filename, Minisat::Solver &S);
int trata_linha_clausula(string & linha, Minisat::Solver &S);
int trata_linha_cabecalho(string & linha, Minisat::Solver &S);

vector<Minisat::Var> vecVar;


int main()
{
	Minisat::Solver S;

    string s("in.txt");
    //create_dimacs(s);
    SatInstance sat_instance(s);

    process_dimacs_file(s, S);
    sat_instance.print();
	
		cout << "here"<< endl;
	Minisat::lbool ret = Minisat::l_Undef;
	Minisat::vec<Minisat::Lit> dummy;

	ret = S.solveLimited(dummy);
 	printf(ret == Minisat::l_True ? "SATISFIABLE\n" : ret == Minisat::l_False ? "UNSATISFIABLE\n" : "INDETERMINATE\n");
    if(ret == Minisat::l_True){
		 std::cout << "Assignment: " << endl;
		 for(int i=0;i<vecVar.size();i++){
			 cout << i+1 << ": " << Minisat::toInt(S.modelValue(vecVar[i])) << endl;
		 }
		cout << endl;
	}
	
	return 0;
}


void create_dimacs(string & filename)
{
    ofstream odimacs(filename);
    odimacs<<"P cnf 6 7"<<endl;
    odimacs<<"1 2 0"<<endl;
    odimacs<<"2 3 0"<<endl;
    odimacs<<"-1 -4 5 0"<<endl;
    odimacs<<"-1 4 6 0"<<endl;
    odimacs<<"-1 -5 6 0"<<endl;
    odimacs<<"-1 -4 -6 0"<<endl;
    odimacs<<"-1 -5 -6 0"<<endl;
    odimacs.close();

}


int process_dimacs_file(string& filename, Minisat::Solver &S)
{
    int i;
    ifstream dimacs(filename);
    char buffer[200];
    dimacs.getline(buffer, 200, '\n');
    string cabecalho(buffer);
    trata_linha_cabecalho(cabecalho, S);
    while (dimacs.getline(buffer, 200, '\n'))
    {
        //dimacs.getline(buffer, 200, '\n');
        string s(buffer);
        cout<<"adiciona clausula vazia"<<endl;
        trata_linha_clausula(s, S);
        
        
    }
	

    return 0;
}

int trata_linha_clausula(string & linha, Minisat::Solver &S)
{
    istringstream in(linha);
    int j;
	Minisat::vec<Minisat::Lit> lits;
    while (in >> j)
        {
            if (j == 0)
                break;
            cout <<"adiciona literal ="<< j << endl;
			cout << vecVar.size() << endl;
			Minisat::Lit lit;
			if(j > 0)
				lit = Minisat::mkLit(vecVar[abs(j)-1]);
			else 
				lit = ~Minisat::mkLit(vecVar[abs(j)-1]);
			
			cout << "added" << j << endl;
			lits.push(lit);
			
        }
		S.addClause_(lits);
		lits.clear();
		cout << "clause added" << endl;
    return 0;
}

int trata_linha_cabecalho(string & linha, Minisat::Solver &S)
{
    istringstream in(linha);
    int j;
	int nvar;
    string word;
    in >> word; //cout<<"string discarded ="<<word<<endl;
    in >> word; //cout<<"string discarded ="<<word<<endl;
    in >> nvar; cout<<"number of variables is ="<<nvar<<endl;
    in >> j; //cout<<"number of clauses is ="<<j<<endl;  
	
	for(int i=0;i<nvar;i++){
		vecVar.push_back(S.newVar());
		cout <<"Added" << i << endl;
	}
    return 0;
}



