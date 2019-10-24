#include <stdio.h>

#include <stdlib.h>

void swap(int *i, int*j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

void sort(int n[], int size) {
    int *i;
    int *s;
    int *p;
    int temp;
    
    for (p = &n[0]; p < n+size -1; p++) {
        //printf("%d\n", p);
        s = p;
        for (i = p+1; i < n + size; i++) {
            //printf("%d\n", i);
            
            if (*i < *s) {
                s = i;;
            }
        }
        swap(p, s);
    }
}

int main(int argc, char * argv[]) {
    int numbers[30];
    FILE *numfile = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    int i;
    int count;
    i = 0;
    while ((fscanf(numfile, "%d", &numbers[i])) != EOF) {
        i++;
    }
    count = i;
    sort(numbers, count);
    for (i = 0; i < count; i++) {
        fprintf(out, "%d\n", numbers[i]);
    }
}
