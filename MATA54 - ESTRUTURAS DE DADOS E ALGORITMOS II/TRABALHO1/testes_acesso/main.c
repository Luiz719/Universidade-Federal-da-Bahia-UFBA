#include <math.h>
#include "../linearHashing.c"

typedef struct test2Response{
    float meanC;
    float meanS;
}test2Response;


test2Response test2(int multiplier, int p, float alpha_max, int times){
    // Multiplier = componente de n; p = número de páginas, times = número de testes
    int n = multiplier * p;
    int k = ceil(0.2 * n);
    int m = 2;
    float alpha_min = 0.2;
    test2Response mean;
    float meanC = 0, meanS = 0;
    //Coloca a seed do algoritmo de randomização como sendo o tempo do sistema.
    srand(time(0)); 
    for(int j = 0; j < times; j++){
        linearHashing *unit = NewlinearHashing(m, alpha_max, alpha_min, p);
        searchResponse result;
        searchResponse result2;
        float C = 0, S = 0;
        int *keys = randomArray(n+2*k, 32*n);
        for (int i = 0; i < n; i++) {
            Insert(unit, keys[i]);
        }
        int *ids = randomArray(k, n-1);
        int kC[k], kS[k];
        for (int j = 0; j < k; j++) {
            kC[j] = keys[ids[j]]; 
        }
        free(ids);
        for (int j = 0; j < k; j++) {
            kS[j] = keys[n+j]; 
        }
        for (int i = 0; i < k; i++) {
            result = Search(unit, kC[i]);
            result2 = Search(unit, kS[i]);
            if(result.found) C += result.nAccess;
            if(!result2.found) S += result2.nAccess;
        }
        FreelinearHashing(unit);
        free(keys);
        C = C / k;
        meanC += C;
        S = S / k;
        meanS += S;
    }
    meanC = meanC / times;
    meanS = meanS / times;
    mean.meanC = meanC;
    mean.meanS = meanS;
    return mean;
}

int mainTest2(){
    /*formato do File = 1ª linha: Multiplier times;
                linhas restantes: alpha_max p result.meanC result.meanS
                    2-9-> testes do alpha, 9-14-> testes de p*/
    FILE* fptr;
    fptr = fopen("test2.txt", "w");
    if (fptr == NULL) exit(0);
    // Multiplier = componente de n; p = número de páginas, times = número de testes
    int p[5] = {1, 5, 10, 20, 50};
    float alpha_max[8] = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int multiplier = 1000;
    int times = 10;
    fprintf(fptr, "%d %d 0 0\n", multiplier, times);
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 5; j++){
            test2Response result = test2(multiplier, p[j], alpha_max[i], times);
            fprintf(fptr, "%.3f %d %.3f %.3f\n", alpha_max[i], p[j], result.meanC, result.meanS);
        }
    }
    fclose(fptr);
}


int main(){
    mainTest2();
}