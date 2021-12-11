#define ITERATIONS_PER_RUN 1000
int main() {

    double f1, f2, f3;
    f1 = 0;
    f2 = 0;
    f3 = 0;


    for( int i = 0; i < ITERATIONS_PER_RUN; ) {
        f1 += i;
        f2 *= i;
        f3 = f1 + f2;
    }

}
