// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

// defined std::cout
#include <iostream>

int main(void) {


	Minisat::Solver S;

	Minisat::Var A = S.newVar();
	Minisat::Var B = S.newVar();

	Minisat::Lit LA = Minisat::mkLit(A);
	Minisat::Lit LAn = ~Minisat::mkLit(A);
	Minisat::Lit LB = Minisat::mkLit(B);
	Minisat::Lit LBn = ~Minisat::mkLit(B);

	Minisat::vec<Minisat::Lit> lits;

	lits.push(LA); lits.push(LB);
	S.addClause_(lits);
	lits.clear();
	
	lits.push(LAn); lits.push(LB);
	S.addClause_(lits);
	lits.clear();

	lits.push(LA); lits.push(LBn);
	S.addClause_(lits);
	lits.clear();
	
	
	lits.push(LAn); lits.push(LBn);
	S.addClause_(lits);
	lits.clear();

	Minisat::lbool ret = Minisat::l_Undef;
	Minisat::vec<Minisat::Lit> dummy;

	ret = S.solveLimited(dummy);

	printf(" (A + B) ^ (nA + B) ^ (A + nB) ^ (nA + nB) \n");

	printf(ret == Minisat::l_True ? "SATISFIABLE\n" : ret == Minisat::l_False ? "UNSATISFIABLE\n" : "INDETERMINATE\n");

	Minisat::Solver newS;

	A = newS.newVar();
	B = newS.newVar();

	lits.push(LA); lits.push(LB);
	newS.addClause_(lits);
	lits.clear();
	
	lits.push(LAn); lits.push(LB);
	newS.addClause_(lits);
	lits.clear();

	lits.push(LAn); lits.push(LBn);
	newS.addClause_(lits);
	lits.clear();
	ret = Minisat::l_Undef;

	ret = newS.solveLimited(dummy);

	printf("\n");

	printf(" (A + B) ^ (nA + B) ^ (nA + nB) \n");
	printf(ret == Minisat::l_True ? "SATISFIABLE\n" : ret == Minisat::l_False ? "UNSATISFIABLE\n" : "INDETERMINATE\n");


    std::cout << "Assignment: "
              << "A=" << Minisat::toInt(newS.modelValue(A)) << " "
              << "B=" << Minisat::toInt(newS.modelValue(B)) << std::endl;










    return 0;
}
