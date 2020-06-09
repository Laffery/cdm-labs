#include "common.h"
#include <iostream>

using namespace Minisat;

bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var var[1000];
    int stone[1000][2];
    memset(stone,0,sizeof(stone));
    int i, j;
    for(i = 1; i<=m; ++i){
        var[i] = solver.newVar();
	for(j = 0; j<2; ++j){
	    (stone[button[i-1][j]][0] ? stone[button[i-1][j]][1] :
		stone[button[i-1][j]][0]) = i;
	}//find all buttons that control each stone
    }
    
    for(i = 1; i <= n;++i){
	int v1 = stone[i][0];
	int v2 = stone[i][1];
	if(states[i-1]){
	/* stone i is above,
	 * if 2vars control  this stone, must keep same;
	 * if 1var  controls this stone, must keep 0.
	 */
	    if(v2){//2vars control this stone
		solver.addClause( mkLit(var[v1]),~mkLit(var[v2]));
		solver.addClause(~mkLit(var[v1]), mkLit(var[v2]));
	    }
	    else
		solver.addClause(~mkLit(var[v1]));
	}
	else{
	/*
	 * stone i is below,
	 * if 2vars control  this stone, must keep diff;
	 * if 1var  controls this stone, must keep 1.
	 */
	    if(v2){
		solver.addClause( mkLit(var[v1]), mkLit(var[v2]));
		solver.addClause(~mkLit(var[v1]),~mkLit(var[v2]));
	    }
	    else
		solver.addClause( mkLit(var[v1]));
	}
    }

    //solve SAT problem
    auto sat = solver.solve();
    if(sat)
    {
        for(i = 1; i <= m; ++i)
            answer[i-1] = (solver.modelValue(var[i]) == l_True);
        return true;
    }
    return false;
}
