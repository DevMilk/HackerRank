#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// Complete the bomberMan function below.

// Please store the size of the string array to be returned in result_count pointer. For example
// char a[2][6] = {"hello", "world"};
//
// *result_count = 2;
//
// return a;
//
void bomb(char** grid,int a,int b,int r,int c){


    grid[a][b]='.';
    if(a-1>=0)
        grid[a-1][b]='.';
    if(a+1<r && grid[a+1][b]>1)
        grid[a+1][b]='.';
    if(b-1>=0)
        grid[a][b-1]='.';
    if(b+1<c && grid[a][b+1]>1)    
        grid[a][b+1]='.';
}
char** bomberMan(int n, int r,int c, char** grid, int* result_count) {
    int i,j,a=n;
    if(n>4){
        n=4+n%4;
    }
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(grid[i][j]=='O')
                grid[i][j]=2;
        }
    }
    n--;
    int counter=3;
    while(n>0){

        if(counter==3){
         for(i=0;i<r;i++){
            for(j=0;j<c;j++){
                if(grid[i][j]=='.'){
                    grid[i][j]=3;
                }
                else{
                    grid[i][j]--;
                }
            }
        }      
        counter=4;      
        }
        else{
         for(i=0;i<r;i++){
            for(j=0;j<c;j++){
                if(grid[i][j]!='.'){
                    grid[i][j]--;    
                    if(grid[i][j]<=0)
                        bomb(grid,i,j,r,c);
                }
            }
        }
        counter=3;
        }
        n--;
    }


    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(grid[i][j]!='.')
                grid[i][j]='O';
        }
    }


    *result_count=r;
    return grid;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** rcn = split_string(readline());

    char* r_endptr;
    char* r_str = rcn[0];
    int r = strtol(r_str, &r_endptr, 10);

    if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

    char* c_endptr;
    char* c_str = rcn[1];
    int c = strtol(c_str, &c_endptr, 10);

    if (c_endptr == c_str || *c_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = rcn[2];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** grid = malloc(r * sizeof(char*));

    for (int i = 0; i < r; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    int grid_count = r;

    int result_count;
    char** result = bomberMan(n, grid_count, c,grid, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
