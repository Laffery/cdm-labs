#include "common.h"

using namespace z3;

bool func1(int data[4][5], int answer[4])
{
    context con;

    expr a = con.int_const("a");
    expr b = con.int_const("b");
    expr c = con.int_const("c");
    expr d = con.int_const("d");

    solver s(con);

    //TODO : your solution here
    for(int i = 0;i < 4;++i)
    {
	int q = data[i][0];
	int w = data[i][1];
	int e = data[i][2];
	int r = data[i][3];
	int t = data[i][4];
	s.add(q*a + w*b + e*c + r*d == t);
    }

    if(sat == s.check())
    {
        model m = s.get_model();
        answer[0] = m.eval(a).get_numeral_int();
        answer[1] = m.eval(b).get_numeral_int();
        answer[2] = m.eval(c).get_numeral_int();
        answer[3] = m.eval(d).get_numeral_int();

        return true;
    }

    return false;
}

int func2(int data[][2], unsigned n)
{
    context ctx;

    expr a = ctx.int_const("a");
    solver s(ctx);

    //TODO : your solution here
    for(int i = 0;i < (int) n;i++)
    {
	int q = data[i][0];
	int w = data[i][1];
	s.add(a%q == w);
	s.add(a >= q);
    }
	
    if(sat == s.check())
    {
	model m = s.get_model();
	return m.eval(a).get_numeral_int();
    }
    return -1;
}

bool func3(int node_num, int color, int graph[20][20])
{
    int i=0, j=0, k=0;

    context c;
    expr_vector x(c); // x is a vector of expr.

    for ( i = 0; i < node_num; ++i)
        for ( j = 0; j < node_num; ++j)
        {
            std::stringstream x_name;
            x_name << "x_" << i << '_' << j;// every uninterpreted consts need a unique name
            x.push_back(c.int_const(x_name.str().c_str()));// add a new integer consts
        }
    //x[i * node_num + j] denotes the color of edge between node i and node j

    solver s(c);

    //TODO : your solution here
    for(i = 0;i < node_num;++i)
	for(j = i+1;j < node_num;++j){
	    s.add(x[i * node_num + j] <= color);
	    s.add(x[i * node_num + j] > 0);
	}

    for(i = 0;i < node_num;++i)
    {
	for(j = i+1;j < node_num-1;++j){
	    k = i * node_num + j;

	    if(i){
	        s.add(x[k] != x[k-node_num-1]);
	        s.add(x[k] != x[k-node_num]);
	        s.add(x[k] != x[k-node_num+1]);
	    }
	    s.add(x[k] != x[k+1]);
	    s.add(x[k] != x[k+node_num+1]);  
	}
    }

    if(unsat == s.check())
        return false;

    model m = s.get_model();
    
    for(i=0; i<node_num; ++i)
    {
        for( j=i+1; j<node_num; ++j)
        {
            //x[i * node_num + j] denotes the color of edge between node i and node j
            graph[i][j] = m.eval( x[i * node_num + j] ).get_numeral_int();
        }
    }
    return true;
}
