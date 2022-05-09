Se dau două mulțimi de numere întregi, A și B, cu NA, respectiv NB elemente.
Se cere să se determine o submulțime X a lui A astfel încât expresia
x1*b1 + x2*b2 +…+ xnb*bnb să aibă o valoare maximă.

Date de intrare: fișierul date.in conține:
- pe prima linie două numere naturale NA și NB, cu semnificația din enunț;
- pe a doua linie NA numere întregi, reprezentând elementele mulțimii A;
- pe a treia linie NB numere întregi, reprezentând elementele mulțimii B.
Elementele de pe aceeași linie sunt separate prin câte un spațiu.

Date de ieșire: fișierul date.out valoarea expresiei determinate.

Restricții și precizări:
- NA,NB∈[2,102]
- NA>=NB
- Fiecare element al mulțimiilor ∈[-104,104]

Cod: 
```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void citire(char *nf, int* NA, int* NB, int** A, int** B) {

    FILE *f = fopen(nf, "r");
    if(f == NULL)
    {
        printf("Eroare deschidere fisier\n");
        return;
    }

    fscanf(f, "%d %d", NA, NB);

    *A = (int *)malloc(*NA * sizeof(int));
    *B = (int *)malloc(*NB * sizeof(int));

    for(int i = 0; i < *NA; i++)
        fscanf(f, "%d", &(*A)[i]);
    for(int i = 0; i < *NB; i++)
        fscanf(f, "%d",&(*B)[i]);
    fclose(f);
}

//void afisare(int NA, int NB, int *A, int *B) {
//    for(int i = 0; i < NA; i++)
//        printf("%d ", A[i]);
//    printf("\n");
//    for(int i = 0; i < NB; i++)
//        printf("%d ", B[i]);
//    printf("\n");
//}

int cmp(const void *a, const void *b) {
    int *A = (int *)a;
    int *B = (int *)b;
    return *B - *A;
}

int rezolvare(char *nf) {
    ///declarare si citire
    int NA, NB;
    int *A, *B;
    char *in = (char *)malloc((strlen(nf) + 4) * sizeof(char));
    strcpy(in, nf);
    strcat(in, ".in");
    citire(in, &NA, &NB, &A, &B);

    ///ordonare descrescatoare
    qsort(A, NA, sizeof(A[0]), &cmp);
    qsort(B, NB, sizeof(B[0]), &cmp);
    //afisare(NA, NB, A, B);

    ///calcularea valorii maxime
    int suma = 0;
    for(int i = 0; i < NB; i++)
        suma = suma + A[i] * B[i];

    ///scrierea rezultatului in fisier
    char * out = (char *)malloc((strlen(nf) + 4) * sizeof(char));
    strcpy(out, nf);
    strcat(out, ".out");
    FILE *f = fopen(out, "w");
    fprintf(f, "%d", suma);
    fclose(f);

    ///eliberare memorie
    free(A);
    free(B);
    free(in);
    free(out);

    return suma;
}

void verificare()
{
    assert(rezolvare("date") == 51);
    assert(rezolvare("date1") == 151);
    assert(rezolvare("date2") == 1361);
    assert(rezolvare("date3") == 469);
    assert(rezolvare("date4") == 3200);

}

int main() {
    verificare();
    return 0;
}

```
