#include <stdio.h>

double stepen(double, int);
int fib(int);

int main() {
  int i;
  int d=0;
  
  for (i = 0; i <= 20; i++){
    printf("2^%d = %g\n",i, stepen(2.0,i));
    printf("fib(%d) = %d\n",i, fib(i));
  }
  return 0;
}
