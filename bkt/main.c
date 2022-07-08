///Tanase Iosif Daniel, grupa 161, problema 8
///Problema genereaza labrinturi care parcurg intreaga matrice
///Pentru a crea peretii, am dublat dimensiunea matricei si am creat traseul cu backtracking doar pe pozitiile pare
///Labrintul are si camere goale
///Nu m-am folosit de punctul de iesire. Cat timp valorile coordonatelor sunt pare, labirintul va trece prin acel punct.


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef struct{
   int x;
   int y;
} directie;

#define N 17
#define M 17

int lab[N][M] = {0};
directie D[] = { {0,2}, {2, 0}, {0, -2}, {-2, 0}};

///functie care interschimba pozitiile intr-un vector
void shuffle(directie *dir, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        directie t = dir[j];
        dir[j] = dir[i];
        dir[i] = t;
    }

}

int valid(int lin, int col)
{
    if(lin >= N || col >= M ||  lin < 0 || col < 0 || lab[lin][col] != 0)
        return 0;

    return 1;
}

void print()
{
    FILE *f = fopen("solutii.txt", "a+");

    fprintf(f, "\n");

    for(int i = 0; i < N; i++, fprintf(f,"\n"))
    {

        for(int j = 0; j < M; j++)
            if(lab[i][j] < 0)
                fprintf(f," 1 ");
            else
                fprintf(f, " 0 ");
    }

    fprintf(f, "\n");
    fclose(f);
}

void bkt(int lin, int col, int k)
{
    int lin_nou, col_nou;

    shuffle(D, 4);

    for(int dir = 0; dir < 4; dir++)
    {
        lin_nou = lin + D[dir].x;
        col_nou = col + D[dir].y;
        if(valid(lin_nou, col_nou))
        {
            lab[lin_nou][col_nou] = k;
            bkt(lin_nou, col_nou, k+1);
        }
    }
}

void pereti()
{
    for(int i = 0; i < N; i += 2)
        for(int j = 0; j < M; j += 2)
        {
            if(lab[i+2][j] > (lab[i][j] + 1) && i + 2 < N)
            {
                lab[i+1][j] = -1;
                if(j - 1 >= 0)
                    lab[i+1][j-1] = -1;
                if(j + 1 < M)
                    lab[i+1][j+1] = -1;
            }

            if(lab[i-2][j] > (lab[i][j] + 1) && i >= 2)
            {
                lab[i-1][j] = -1;
                if(j - 1 >= 0)
                    lab[i-1][j-1] = -1;
                if(j + 1 < M)
                    lab[i-1][j+1] = -1;
            }

            if(lab[i][j+2] > (lab[i][j] + 1) && j + 2 < M)
            {
                lab[i][j+1] = -1;
                if(i - 1 >= 0)
                    lab[i-1][j+1] = -1;
                if(i + 1 < M)
                    lab[i+1][j+1] = -1;
            }

            if(lab[i][j-2] > (lab[i][j] + 1) && j >= 2)
            {
                lab[i][j-1] = -1;
                if(i - 1 >= 0)
                    lab[i-1][j-1] = -1;
                if(i + 1 < M)
                    lab[i+1][j-1] = -1;
            }
        }
}

directie verifD[] = { {0,1}, {1, 0}, {0, -1}, {-1, 0}};
int ok = 0;

int verif_valid(int lin, int col)
{
    if(lin >= N || col >= M ||  lin < 0 || col < 0 || lab[lin][col] == -1)
        return 0;

    return 1;
}

/// Pentru verificare am folosit tot un algoritm bkt. Am urmat traseul determinat mai sus, evitand peretii. Daca ajung in punctul dorit, labirintul generat este corect.
void verificare_bkt(int lin, int col, int k, int x, int y)
{
    int lin_nou, col_nou;

    if(ok == 1)
        return;

    if(lin == x && col == y)
    {
        ok = 1;
        return;
    }
    else
        for(int dir = 0; dir < 4; dir++)
        {
            lin_nou = lin + verifD[dir].x;
            col_nou = col + verifD[dir].y;

            if(verif_valid(lin_nou, col_nou))
            {
                int val = lab[lin_nou][col_nou];
                lab[lin_nou][col_nou] = -1;
                verificare_bkt(lin_nou, col_nou, k+1, x, y);
                lab[lin_nou][col_nou] = val;
            }


        }
}

int verificare(int x_intrare, int y_intrare, int x_iesire, int y_iesire)
{
    ok = 0;
    verificare_bkt(x_intrare, y_intrare, 0, x_iesire, y_iesire);
    return ok;
}

int main()
{
    srand(time(NULL));
    /// folosim srand(time(NULL)) pentru a obtine un labirint aleator la fiecare rularare

    int x_intrare = 0, y_intrare = 0;

    FILE *out = fopen("solutii.txt", "w");
    fprintf(out, "%d %d\n", x_intrare, y_intrare);
    fclose(out);

    lab[x_intrare][y_intrare] = 1;
    bkt(x_intrare, y_intrare, 2);

    pereti();

    print();

    assert(verificare(x_intrare, y_intrare, 10, 10) == 1);
    assert(verificare(x_intrare, y_intrare, 8, 12) == 1);
    assert(verificare(x_intrare, y_intrare, 2, 6) == 1);

    return 0;
}
