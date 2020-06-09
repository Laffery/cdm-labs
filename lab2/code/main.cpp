#include "common.h"

using namespace z3;

static FILE* output_fh;
static int data1[4][5];
static int answer1[4];


static int data2[10][2];
static unsigned num2;

static int data3[2];
static int graph[20][20];

bool func1( int data[4][5], int answer[4] );
int func2( int data[][2], unsigned n );
bool func3( int node_num, int color, int graph[20][20] );

void input_data1()
{
    unsigned i, j;
    for(i=0; i<4; ++i)
    {
        for(j=0; j<5; ++j)
        {
            scanf("%d", &(data1[i][j]) );
        }
    }
    return;
}

void input_data2()
{
    unsigned i;

    scanf("%u", &num2);
    for(i=0; i<num2; ++i)
    {
        scanf("%u %u", &(data2[i][0]), &(data2[i][1]) );
    }
    return;
}

void input_data3()
{
    scanf("%d %d", &(data3[0]), &(data3[1]));
}

void test1()
{
    input_data1();

    bool flag = func1(data1, answer1);
    if(flag)
    {
        fprintf(output_fh, "SAT ");
        unsigned i;
        for( i=0; i<4; ++i)
            fprintf(output_fh, "%d ", answer1[i]);
        fprintf(output_fh, "\n");
    }
    else
    {
        fprintf(output_fh, "UNSAT\n");
    }
    return;
}

void test2()
{
    input_data2();
    int answer2 = func2(data2, num2);
    if(answer2 == -1)
        fprintf(output_fh, "UNSAT\n");
    else
        fprintf(output_fh, "SAT %d\n", answer2);
    return;
}

void test3()
{
    input_data3();
    bool flag = func3(data3[0], data3[1], graph);
    if(flag == false)
        fprintf(output_fh, "UNSAT\n");
    else
    {
        fprintf(output_fh, "SAT\n");
        int i=0, j=0;
        for(i=0; i<data3[0]; ++i)
        {
            for(j=0; j<data3[0]; ++j)
            {
                fprintf(output_fh, "%d ", graph[i][j]);
            }
            fprintf( output_fh, "\n");
        }
    }
    return;
}

int main()
{
    // input test data
    FILE* input_fh = freopen("test.txt", "r", stdin);
    if(input_fh == NULL)
    {
        printf("Open test file error!\n");
        exit(-1);
    }

    output_fh = fopen("answer.txt", "w");
    if(output_fh == NULL)
    {
        printf("Write answer error!\n");
        exit(-1);
    }


    test1();
    test2();
    test3();

    fclose(stdin);
    fclose( output_fh );

    return 0;
}


