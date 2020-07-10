#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define isValid(x,y) ((x)> 0 && (y)> 0 && (x)<=n && (y)<=n)
char* readline();
char** split_string(char*);
int max(int num1, int num2);
int min(int num1, int num2);
 
 
//-1 -1; 0 -1; 1 -1;
// -1 0; 0 0;  1 0;
// -1 1; 0 1; 1 1; -> map using x +3*y + 4, x>0 y>0
int directions[9] ;
int decodeYDir(int dirIndex){
    return floor((dirIndex )/3) - 1;
}
int decodeXDir(int dirIndex, int dirY){
    return dirIndex-4-(3*dirY)  ;
}
int maxOfDirection(int dirX, int dirY,int x,int y,int n){
 
     
    int xmax = dirX==1  ?  n-x : (dirX== 0 ? 0 : x-1 );
    int ymax = dirY==1  ?  n-y : (dirY== 0 ? 0 : y-1 )  ;  
    int condition= (dirX==0 || dirY==0);
    return  !isValid(x+dirX,y+dirY) ? 0: (condition ? max(xmax,ymax)   :  min(xmax,ymax));  
}
void updateDirections(int x0, int y0, int x1, int y1){
    int diffX = x1-x0;
    int diffY = y1-y0;
    
    int dirX = diffX == 0 ? 0: (diffX)/abs(diffX);
    int dirY = diffY == 0 ? 0: (diffY)/abs(diffY);
    int map = dirX + 3*dirY + 4; 
    int diff = max(abs(diffX),abs(diffY))-1 ;
    
    if(directions[map]> diff)
        directions[map]= diff;
     
}
int isInDirection(int x0, int y0, int x1, int y1){ 
  
    return (x0==x1 || y0 == y1 || ((double)abs(x0-x1)/abs(y0-y1) == 1));      
}
int queensAttack(int n, int k, int r_q, int c_q, int obstacles_rows, int obstacles_columns, int** obstacles) { 

    int i = 0;

    for( ;i<9;i++)
        directions[i]=n ;
    directions[4]=0;    

    for(i=0;i<k;i++){
        if(isInDirection(c_q,r_q,obstacles[i][1],obstacles[i][0] )) 
            updateDirections(c_q,r_q,obstacles[i][1],obstacles[i][0] );
         
    } 
    int sum = 0; 
     
    for(i=0;i<9;i++){ 
         
        
        int y = decodeYDir(i);
         

        sum+= directions[i] == n ?  maxOfDirection(decodeXDir(i,y),y,c_q,r_q,n):                                             directions[i];
         
    }
    return sum;

} 
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nk = split_string(readline());

    char* n_endptr;
    char* n_str = nk[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* k_endptr;
    char* k_str = nk[1];
    int k = strtol(k_str, &k_endptr, 10);

    if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

    char** r_qC_q = split_string(readline());

    char* r_q_endptr;
    char* r_q_str = r_qC_q[0];
    int r_q = strtol(r_q_str, &r_q_endptr, 10);

    if (r_q_endptr == r_q_str || *r_q_endptr != '\0') { exit(EXIT_FAILURE); }

    char* c_q_endptr;
    char* c_q_str = r_qC_q[1];
    int c_q = strtol(c_q_str, &c_q_endptr, 10);

    if (c_q_endptr == c_q_str || *c_q_endptr != '\0') { exit(EXIT_FAILURE); }

    int** obstacles = malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        *(obstacles + i) = malloc(2 * (sizeof(int)));

        char** obstacles_item_temp = split_string(readline());

        for (int j = 0; j < 2; j++) {
            char* obstacles_item_endptr;
            char* obstacles_item_str = *(obstacles_item_temp + j);
            int obstacles_item = strtol(obstacles_item_str, &obstacles_item_endptr, 10);

            if (obstacles_item_endptr == obstacles_item_str || *obstacles_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(obstacles + i) + j) = obstacles_item;
        }
    }

    int obstacles_rows = k;
    int obstacles_columns = 2;

    int result = queensAttack(n, k, r_q, c_q, obstacles_rows, obstacles_columns, obstacles);

    fprintf(fptr, "%d\n", result);

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

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

/**
 * Find minimum between two numbers.
 */
int min(int num1, int num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}
