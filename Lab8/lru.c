#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int pageno;
} ref_page;

int main(int argc, char *argv[]){
    int CACHE_SIZE = atoi(argv[1]);
    ref_page cache[CACHE_SIZE];
    char pageCache[100];
    int i;
    int totalFaults = 0;

    for (i = 0; i < CACHE_SIZE; i++){
        cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
        int page_num = atoi(pageCache);
        /*
        Page Replacement Implementation Goes Here
        */

       printf("%d\n", page_num);
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;
}
