// matrixify.c
// Author: Gavin Heaver
// Date: 10/25/24
// Class: COP 3223, Professor Parra
// Purpose: The purpose of this program is to use 1D and 2D array, and organizing memory storage with dynamic memory allocation
// Input: Nothing
// Output: The size of an array, the size of matrices made, size of matrices found, result of adding matrices,
//         and the diagonal sum of added matrix

//Make #includes
#include <stdio.h>
#include <stdlib.h>

//Create one dimensional array function
int *createOneDimensionalArray(int size){
    //Declare the array and pointer
    int *array = malloc(size * sizeof(int));

    //fill the array with initialized values of 1
    for(int i = 0; i < size; i++){
        array[i] = 1;
    }

    //print out how big the size of the array created is
    printf("Array of size %d is created.\n", size);

    //Return pointer to the array
    return array;
}

//create matrix function
int **createMatrix(int rows, int columns){
    //Create the matrix, allocating space for rows
    int **matrix = malloc(rows * sizeof(int*));

    //Allocate space for the columns
    for(int i = 0; i < rows; i++){
        matrix[i] = malloc(columns * sizeof(int));
    }

    //Initalize the values of the matrix to equal 1
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            matrix[i][j] = 1;
        }
    }

    //State that the matrix was created
    printf("Matrix of size (%d, %d) is created.\n", rows, columns);

    //Return pointer to matrix
    return matrix;
}

//adding matrices function
int **addMatrices(int **defaultMatrix, int **readInMatrix, int rows, int cols){
    //Declare the initialize summed matrix
    int **summedMatrix = malloc(rows * sizeof(int*));

    //Make if statement to test if the rows and cols are equal
    if(rows == cols){
        //Allocate space for the columns
        for(int i = 0; i < rows; i++){
            summedMatrix[i] = malloc(cols * sizeof(int));
        }

        //create the summed matrix
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                summedMatrix[i][j] = defaultMatrix[i][j] + readInMatrix[i][j];
            }
        }
        
        //Print out the summed matrix
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                printf("%d ", summedMatrix[i][j]);
            }
            printf("\n");
        }
    }
    //Make else statement if the rows and cols are not equal 
    else {
        //Print that the matrices are not the same size
        printf("Matrices are not of the same size. Cannot add\n");
        summedMatrix = defaultMatrix;
    }

    //Return the summed matrix
    return summedMatrix;
}

//diagonal sum of matrices function
int computeDiagonalSum(int **matrix, int rows, int cols){
    //Declare and initialize variable
    int sum = 0;

    //Make if statement to see if the rows and columns are equal
    if(rows == cols){
        for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    //Add current value to the matrix
                    sum += matrix[i][j];
                    //Move to the next row
                    i++;
                }
            }
        //Print out the diagonal sum
        printf("Diagonal Sum is: %d\n", sum);
    }
    //Make else if statement if the rows and columns aren't equal
    else if (rows != cols){
        //Print out that it isn't a square
        printf("Matrix is not square. Cannot compute diagonal sum\n");
    }

    //Make else statement if everything fails
    if(rows != cols || *matrix == NULL){
        printf("Matrices were not able to be added together\n");
    }

    //return difficulty
    return 4;
}

//read in file function
int readFile(char *fileName){
    //Declare and intialize variables
    int size = 5;
    int rows[2];
    int cols[2];

    //Call create one dimensional array function
    int *array = createOneDimensionalArray(size);

    //Open the file for the first time
    FILE *inp1 = fopen(fileName, "r");

    //Make sure the file opens
    if(inp1 == NULL){
        //State no file open
        printf("There was no file opened.\n");
    }
    else{
        //scan the size of each matrix from the file
        fscanf(inp1, "%d", &rows[0]);
        fscanf(inp1, "%d", &cols[0]);
        fscanf(inp1, "%d", &rows[1]);
        fscanf(inp1, "%d", &cols[1]);
    }

    //Call create matrix function
    int **initializedMatrix = createMatrix(rows[0], cols[0]);
    
    //Create and read in first matrix, allocating for rows
    int **firstMatrix = malloc(rows[0] * sizeof(int*));

    //Allocate space for the columns in the first matrix
    for(int i = 0; i < rows[0]; i++){
        firstMatrix[i] = malloc(cols[0] * sizeof(int));
    }

    //Read in the values of the first matrix
    for(int i = 0; i < rows[0]; i++){
        for(int j = 0; j < cols[0]; j++){
            fscanf(inp1, "%d", &firstMatrix[i][j]);
        }
    }

    //Close the file
    fclose(inp1);

    //Open the file again
    FILE *inp2 = fopen(fileName, "r");

    //Make sure the file opens
    if(inp2 == NULL){
        //State no file open
        printf("There was no file opened.\n");
    }
    else{
        //scan the size of each matrix from the file
        fscanf(inp2, "%d", &rows[0]);
        fscanf(inp2, "%d", &cols[0]);
        fscanf(inp2, "%d", &rows[1]);
        fscanf(inp2, "%d", &cols[1]);
    }
    
    //Create and read in second matrix, allocating for rows
    int **secondMatrix = malloc(rows[1] * sizeof(int*));

    //Allocate space for the columns in the second matrix
    for(int i = 0; i < rows[1]; i++){
        secondMatrix[i] = malloc(cols[1] * sizeof(int));
    }

    //Read in the values of the second matrix
    for(int i = 0; i < rows[1]; i++){
        for(int j = 0; j < cols[1]; j++){
            fscanf(inp2, "%d", &secondMatrix[i][j]);
        }
    }

    //Close the file
    fclose(inp2);

    //print the size of the matrices
    printf("Matrix of size (%d, %d) is found.\n", rows[0], cols[0]);
    printf("Matrix of size (%d, %d) is found.\n", rows[1], cols[1]);

    //Call the add matrix function
    int **summedMatrix = addMatrices(initializedMatrix, firstMatrix, rows[0], cols[0]);
    
    //Call compute diagonal sum function
    computeDiagonalSum(summedMatrix, rows[0], cols[0]);

    //return difficulty
    return 4;
}

//Main function
int main(int argc, char **argv){
    //Call read file function
    readFile(argv[1]);
    
    //return
    return 0;
}