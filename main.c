/*
Description:
A program that reads matrix parameters from a file and creates the matrices using random numbers. 
It finds the minimum multiplication chain using exhaustive search, and finds  the newly created matrix.

Created by: Matthew Jungmann and Dario Hipp
Date: 18/10/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE_NAME "test_set_1"
#define OUTPUT_FILE_NAME "test_set_1_sol"

//Declare structs
typedef struct 
{
    int rows;
    int cols;
    int *elements;
} matrices;

//Declare functions
int min_multi_amount(matrices *mat_p, int amount, int c_row, int c_col);
void matrix_multiplication(matrices *mat_p, int matrix_num);


int main(void){
    //Creating file pointer to file
    FILE* infp;
    FILE* outfp;

    int rows, cols, i, j;
    int k = 0;
    int full_elements = 0;
    int num_of_matrix = 0;
    int counter = 0;
    int save_row = 0;
    int save_col = 1;
    int collect_matrix_data[10];
    int min_total = 0;
    char data[10];

    matrices *matrix_ptr;

    //tester
    int print_row = 0;
    int print_col = 1;


    //Open input and output files
    infp = fopen(INPUT_FILE_NAME, "r");
    outfp = fopen(OUTPUT_FILE_NAME, "w");
    
    //Check if files have been opened successfully 
    if(infp == NULL || outfp == NULL){
        printf("Error! File could not be opened.");
        exit(1);
    }

    //Start while - Cycle through the test set line by line
    while(fgets(data, sizeof(data), infp) != NULL){

        //IF NUMBERS HAVE A SPACE IN TEST SET
        rows = atoi(&data[0]);
        cols = atoi(&data[1]);

        //Store matrix information in array
        collect_matrix_data[save_row] = rows;
        collect_matrix_data[save_col] = cols;

        //Save the data of column and row amount
        save_col = save_col + 2;
        save_row = save_row + 2;

        full_elements += (rows * cols);

        //Save max the number of matrix number in data set
        num_of_matrix++;
       
    }//end while


    //Allocate memory for all the strcuts required to fit all info about the matrices
    matrix_ptr = (matrices *)malloc(num_of_matrix * sizeof(matrices));

    //Create array with the correct size for the amount of data for the matrix
    int* matrix_data = calloc((num_of_matrix * 2), sizeof(int));

    //Create an array to store the number of elements in each array
    int* elements_in_mat = calloc(num_of_matrix, sizeof(int));

    for(i = 0; i < (num_of_matrix); i++)
    {
        //Transfer data from the collection array into structs
        (matrix_ptr + i)->rows = collect_matrix_data[k];
        (matrix_ptr + i)->cols = collect_matrix_data[k + 1];

        //Store the number of elements in each matrix into an array
        elements_in_mat[i] += (matrix_ptr + i)->rows * (matrix_ptr + i)->cols;

        k += 2;
    }


    //Generate the numbers in for the new matrices and store them in an array
    for(i = 0; i < num_of_matrix; i++)
    {
        //Allocate memory for array of elements in struct
        (matrix_ptr + i)->elements = malloc(elements_in_mat[i] * sizeof(int));

        //printf("~~New Matrix~~");
        for(j = 0; j < elements_in_mat[i]; j++){
            (matrix_ptr + i)->elements[j] = (rand() % 20) + 1;
        }
    }

    matrix_multiplication(matrix_ptr, num_of_matrix);
    min_total = min_multi_amount(matrix_ptr, -1, matrix_ptr->rows, matrix_ptr->cols);

    //Print out the inital matrices
    for(i = 0; i < num_of_matrix; i++)
    {
        counter = 0;
        printf("~~Matrix %d~~\n", i + 1);
        //Cycle through rows of matrices
        for(j = 0; j < (matrix_ptr + i)->rows; j++){
            printf("|  ");
            //Cycle through columns of matrices
            for(k = 0; k < (matrix_ptr + i)->cols; k++){
                    //Generate random numbers from 1-20
                    printf("%2d ", (matrix_ptr + i)->elements[counter]);
                    counter++;
            }
            printf("  |\n");
        }
        printf("\n\n");
    }

    printf("Mininum: %d", min_total);
        
    //free allocated data
    free(matrix_data);
    free(elements_in_mat);

    //Close input and output files
    fclose(infp);
    fclose(outfp);

    return 0;
}



//Start min_multi_amount
int min_multi_amount(matrices* mat_p, int amount, int c_row, int c_col){
    int i, j, k;
    long minimum = LONG_MAX;
    int curr_ans = 0;
    int final_ans = 0;
    int count = 0;
    
    amount += 1;
    
    curr_ans = c_row * (mat_p + amount)->cols * (mat_p + amount + 1)->cols;
    final_ans += curr_ans;
    printf("Final answer %d: %d\n", amount, final_ans);

    c_col = (mat_p + amount + 1)->cols;
    if(amount < 2)
    {
        final_ans += min_multi_amount(mat_p, amount, c_row, c_col);
    }
    


    return final_ans;
}
//End 

//Start matrix_multiplication
void matrix_multiplication(matrices* mat_p, int matrix_num){
    int i, j, k;
    int array;

    for(i = 1; i < matrix_num; i++)
    {
        array = malloc(sizeof(int) * (mat_p->rows * (mat_p + i)->cols));

        for(j = 0; j < mat_p->rows; j++)
        {
            for(k = 0; k < (mat_p + i)->cols; k++)
            {
                
            }
        }
    }

}
//End