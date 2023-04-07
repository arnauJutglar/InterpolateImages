//
//  main.c
//  interpola_imatges
//
//  Created by Arnau Jutglar Puig on 25/01/2022.
//  Copyright © 2022 Arnau Jutglar Puig. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "header.h"


int main(void) {
    int n, m, i, j, counter=0;
    int A11, A12, A21, A22;
    int **I, **B, **F;
    FILE *fin;
    char s1[20];
    
    printf("Input file: ");
    scanf("%s", s1);
    fin = fopen(s1, "r");
    
    printf("m n ");
    scanf(" %d %d", &m, &n);
    printf("m = %d, n = %d \n", m, n);
    
    
    while (counter < 13) {
        // Dynamic memory
        I = (int **) calloc(m, sizeof(int *));
        if (I == NULL) {
            printf("Out of memmory.");
            exit(1);
        }
        for (i=0; i < m; i++) {
            I[i] = (int *) calloc(n, sizeof(int));
            if (I[i] == NULL) {
                printf("Out of memmory.");
                exit(1);
            }
        }
        
        B = (int **) calloc(3, sizeof(int *));
        if (B == NULL) {
            printf("Out of memmory.");
            exit(1);
        }
        for (i=0; i < 3; i++) {
            B[i] = (int *) calloc(3, sizeof(int));
            if (B[i] == NULL) {
                printf("Out of memmory.");
                exit(1);
            }
        }
        
        F = (int **) calloc(m + (int) ceil(m/2.), sizeof(int *));
        if (F == NULL) {
            printf("Out of memmory.");
            exit(1);
        }
        for (i=0; i < m + (int) ceil(m/2.); i++) {
            F[i] = (int *) calloc(n + (int) ceil(n/2.), sizeof(int));
            if (F[i] == NULL) {
                printf("Out of memmory.");
                exit(1);
            }
        }
        
        printf("Size of output matrix: (%d,%d). \n", m + (int) ceil(m/2.), n + (int) ceil(n/2.));
        
        // Read matrix
        for (j=0; j < m; j++) {
            for (i=0; i < n; i++) {
                fscanf(fin, " %d", &I[j][i]);
            }
        }
        
        fclose(fin);
                
        // Create the new image
        for (j=0; j < m/2; j++) {
            for (i=0; i < n/2; i++) {
                A11 = I[2*j][2*i];
                A12 = I[2*j][2*i +1];
                A21 = I[2*j +1][2*i];
                A22 = I[2*j +1][2*i +1];
                
                
                interpolates(A11, A12, A21, A22, B);
                adds(F, B, j, i);
            }
            
            // Adds last column if n is odd
            if (n % 2 == 1) {
                A11 = I[2*j][2*i -1];
                A12 = I[2*j][2*i];
                A21 = I[2*j +1][2*i -1];
                A22 = I[2*j +1][2*i];

                interpolates(A11, A12, A21, A22, B);
                addsCol(F, B, j, i);
            }
        }
        
        // Adds last row if m is odd
        if (m % 2 == 1) {
            for (i=0; i < n/2; i++) {
                A11 = I[2*j-1][2*i];
                A12 = I[2*j-1][2*i +1];
                A21 = I[2*j][2*i];
                A22 = I[2*j][2*i +1];
                
                interpolates(A11, A12, A21, A22, B);
                addsRow(F, B, j, i);
            }
            
            // Adds last edge if both m and n are odd
            if (n % 2 == 1) {
                A11 = I[2*j-1][2*i-1];
                A12 = I[2*j-1][2*i];
                A21 = I[2*j][2*i -1];
                A22 = I[2*j][2*i];

                interpolates(A11, A12, A21, A22, B);
                addsCorner(F, B, j, i);
            }
        }
        
        fin = fopen(s1, "w");
        writes(F, m + (int) ceil(m/2.), n + (int) ceil(n/2.), fin);
        fclose(fin);
        
        // Rearrange:
        m = m + (int) ceil(m/2.);
        n = n + (int) ceil(n/2.);
        fin = fopen(s1, "r");
        counter++;
    }
    
    printf("Done. \n");
    
    return 0;
}


