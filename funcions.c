//
//  funcions.c
//  interpola_imatges
//
//  Created by Arnau Jutglar Puig on 25/01/2022.
//  Copyright © 2022 Arnau Jutglar Puig. All rights reserved.
//

#include "header.h"

void interpolates(int A11, int A12, int A21, int A22, int **B) {
    int i, j;
    double x=0, y=0, h = 0.5;
        
    for (j=0; j<= 2; j++) {
        x = 0;
        
        for (i=0; i <= 2; i++) {
            // Position (x,y) = (0,0) is B[2][0]
            B[2-j][i] = A11*(1-x)*y + A12*x*y + A21*(1-x)*(1-y) + A22*x*(1-y);
            
            x += h;
        }
        
        y += h;
    }
    
    return;
}

void adds(int **F, int **B, int fila, int col) {
    int i, j;
        
    for (j=0; j <= 2; j++) {
        for (i=0; i <= 2; i++) {
            F[3*fila + j][3*col + i] = B[j][i];
        }
    }
    
    return;
}

void addsCol(int **F, int **B, int fila, int col) {
    int i, j;
            
    // Add 2 latest columns from B
    for (j=0; j <= 2; j++) {
        for (i=0; i <= 1; i++) {
            F[3*fila + j][3*col + i] = B[j][i+1];
        }
    }
        
    return;
}

void addsRow(int **F, int **B, int fila, int col) {
    int i, j;
        
    // Add 2 latest columns from B
    for (j=0; j <= 1; j++) {
        for (i=0; i <= 2; i++) {
            F[3*fila + j][3*col + i] = B[j+1][i];
        }
    }
        
    return;
}

void addsCorner(int **F, int **B, int fila, int col) {
    int i, j;
        
    // Add 2 latest columns from B
    for (j=0; j <= 1; j++) {
        for (i=0; i <= 1; i++) {
            F[3*fila + j][3*col + i] = B[j+1][i+1];
        }
    }
    
    return;
}

void writes(int **F, int m, int n, FILE *fp) {
    int j, i;
    
    for (j=0; j < m; j++) {
        for (i=0; i < n; i++) {
            fprintf(fp, "%d ", F[j][i]);
        }
        fprintf(fp, "\n");
    }
    
    return;
}
