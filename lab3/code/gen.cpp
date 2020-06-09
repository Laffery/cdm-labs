#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char answer[100][10000];
char method[100][10000];
unsigned method_len;
unsigned answer_index;

void input_method(const char* file)
{
    method_len = 0;
    memset(method, 0, sizeof(method));
    FILE* input = fopen(file, "r");
    if( input == NULL )
    {
        printf("Open %s error!\n", file);
        exit(-1);
    }

    char* temp = NULL;
    temp = fgets(method[0], 8000, input);
    while(temp)
    {
        method_len++;
        temp = fgets(method[method_len], 8000, input);
    }

    fclose(input);
}

void input_answer()
{
    FILE* input = fopen("lab3.txt", "r");
    if( input == NULL )
    {
        printf("Open lab3.dfy error!\n");
        exit(-1);
    }

    char* temp = NULL;
    unsigned i = 0;
    temp = fgets(answer[0], 8000, input);
    while(temp)
    {
        i++;
        temp = fgets(answer[i], 8000, input);
    }

    fclose(input);
}

void output_method(const char* file)
{
    FILE* output = fopen(file, "w");
    if( output == NULL )
    {
        printf("Write %s error!\n", file);
        exit(-1);
    }

    unsigned i;
    for(i = 0; i < method_len; ++i)
    {
        fprintf(output, "%s", method[i]);
        if(method[i][0]=='/')
        {
            while(answer[answer_index][0] != '#')
            {
                fprintf(output, "\t%s", answer[answer_index]);
                answer_index++;
            }
            answer_index++;
        }
    }

    fclose(output);
}

int main()
{
    input_answer();

    input_method("method1.dfy");
    output_method("answer1.dfy");
    input_method("method2.dfy");
    output_method("answer2.dfy");
    input_method("method3.dfy");
    output_method("answer3.dfy");
    input_method("method4.dfy");
    output_method("answer4.dfy");

    return 0;
}
