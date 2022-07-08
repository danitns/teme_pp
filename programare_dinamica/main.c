///Tanase Iosif Daniel, grupa 161, problema 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LEN 30

void citire(char** s, char** t, const char* nf)
{
    /// deschidere fisier
    FILE *f = fopen(nf, "r");
    if(f == NULL)
    {
        printf("Eroare deschidere fisier citire");
        return;
    }

    /// alocare memorie
    *s = (char *)malloc(LEN * sizeof(char));
    *t = (char *)malloc(LEN * sizeof(char));

    /// citire din fisier
    assert(fgets(*s, LEN, f) != NULL);
    assert(fgets(*t, LEN, f) != NULL);

    ///inchidere fisier
    fclose(f);
}

int subsir_comun(char* s, char* t)
{
    FILE *out = fopen("date.out", "a+");
    if(out == NULL)
    {
        printf("eroare deschidere fisier out");
        return 1;
    }

    /// eliminare '\n' de pe ultima pozitie
    if(s[strlen(s) - 1] == '\n')
        s[strlen(s) - 1] = '\0';
    if(t[strlen(t) - 1] == '\n')
        t[strlen(t) - 1] = '\0';

    fprintf(out, "%s\n", s);
    fprintf(out, "%s\n", t);
    fprintf(out, "\n");

    const unsigned int size_of_s = strlen(s) + 1;
    const unsigned int size_of_t = strlen(t) + 1;

    int** matrice;
    matrice = (int **)malloc(size_of_s * sizeof(int *));
    for(int i = 0; i < size_of_s; i++)
        matrice[i] = (int*)calloc(size_of_t, sizeof(int));

    ///formam matricea cu lungimea maxima a unui subsir
    for(int i = 1; i < size_of_s; i++)
        for(int j = 1; j < size_of_t; j++)
        {
            if(s[i-1] == t[j-1])
                matrice[i][j] = 1 + matrice[i-1][j-1];
            else
            {
                if(matrice[i-1][j] > matrice[i][j-1])
                    matrice[i][j] = matrice[i-1][j];
                else
                    matrice[i][j] = matrice[i][j-1];
            }

        }

    int i = (int)size_of_s - 1;
    int j = (int)size_of_t - 1;
    int k = 0, l = 0;
    char* s_lcs;
    char* t_lcs;

    s_lcs = (char *)malloc(LEN * sizeof(char));
    t_lcs = (char *)malloc(LEN * sizeof(char));

    ///reconstituim solutia
    while(i > 0 && j > 0)
    {
        if(matrice[i][j] == matrice[i-1][j-1])
        {
            s_lcs[k++] = s[i-1];
            t_lcs[l++] = t[j-1];
            i--;
            j--;
        }
        else if(matrice[i][j] == matrice[i-1][j])
        {
            s_lcs[k++] = s[i-1];
            t_lcs[l++] = '-';
            i--;
        }
        else if(matrice[i][j] == matrice[i][j-1])
        {
            t_lcs[l++] = t[j-1];
            s_lcs[k++] = '-';
            j--;
        }
        else if(matrice[i][j] == matrice[i-1][j-1] + 1)
        {
            s_lcs[k++] = s[i - 1];
            t_lcs[l++] = t[j - 1];
            i--;
            j--;
        }

    }

    while(i > 0)
    {
        s_lcs[k++] = s[i - 1];
        t_lcs[l++] = '-';
        i--;
    }

    while(j > 0)
    {
        s_lcs[k++] = '-';
        t_lcs[l++] = t[j - 1];
        j--;
    }

    s_lcs[k] = '\0';
    t_lcs[l] = '\0';

    s_lcs = strrev(s_lcs);
    t_lcs = strrev(t_lcs);

    int nr_operatii = 0;
    for(i = 0; i < strlen(s_lcs); i++)
    {
        if(s_lcs[i] == t_lcs[i])
            fprintf(out, "pastram %c\n", s_lcs[i]);
        else if(s_lcs[i] == '-')
        {
            fprintf(out, "inseram %c\n",  t_lcs[i]);
            nr_operatii ++;
        }
        else if(t_lcs[i] == '-')
        {
            fprintf(out, "stergem %c\n", s_lcs[i]);
            nr_operatii++;
        }
        else if(s_lcs != t_lcs)
        {
            fprintf(out, "inlocuim %c - %c\n", s_lcs[i], t_lcs[i]);
            nr_operatii++;
        }

    }
    fprintf(out, "Nr operatii: %d\n\n\n", nr_operatii);

    free(s_lcs);
    free(t_lcs);
    fclose(out);

    return nr_operatii;
}

void verificare()
{
    assert(subsir_comun("carte", "antet") == 3);
    assert(subsir_comun("operatii", "cuvant") == 7);
    assert(subsir_comun("aaa", "bbb") == 3);
}

int main()
{
    FILE *out = fopen("date.out", "w");
    if(out == NULL)
    {
        printf("eroare deschidere fisier main");
        return 1;
    }


//    char *s , *t;
//    citire(&s, &t, "date.in");
//
//    subsir_comun(s, t);
//
//    /// eliberare memorie
//    free(s);
//    free(t);

    verificare();

    fclose(out);
    return 0;
}
