#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    srand(time(NULL));
    for(int i = 0; i < 64; i++) {
        printf("%d ", rand()%2);
    }
}

