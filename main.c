#include <stdio.h>

double степен(double, int);
int фиб(int);

int main() {
  int i;
  int d=0;
  
  for (i = 0; i <= 20; i++){
    printf("2^%d = %g\n",i, степен(2.0,i));
    printf("fib(%d) = %d\n",i, фиб(i));
  }
  return 0;
}
