#include "../linearHashing.c"
#include <stdio.h>
#define INITIAL_PAGES 2
#define ALPHA_MAX 0.85
#define PAGE_SIZE 10

float get_alpha(linearHashing *unit){
    float alpha = (float) unit->nKeys;
    alpha /= (unit->nPages*unit->page_size);

    return alpha;
}

float mean_pages(linearHashing *unit){
    float sum_pages = (float) unit->nPages;
    int total_lists=(1 << unit->l)*unit->m+unit->N;
    
    return sum_pages/total_lists;
}


int main(){
    linearHashing *lh = NewlinearHashing(INITIAL_PAGES, ALPHA_MAX, 0, PAGE_SIZE);
    int buff;
    while(scanf("%i", &buff) != EOF){
        Insert(lh, buff);
        printf("%.4f %.4f %i\n", get_alpha(lh), mean_pages(lh), maxListSize(lh));
    }
}