#include <stdio.h>
#include <math.h>
#include <time.h>

unsigned long int fib_iterative(unsigned long int n) {
    unsigned long int curr = 0, prev = 1, temp, i;
    for (i = 0; i < n; i++) {
        temp = curr;
        curr += prev;
        prev = temp;
    }

    return curr;
}

unsigned long int fib_analytic(unsigned long int n) {
   return lround((pow(0.5 + 0.5 * sqrt(5.0), n) -
                  pow(0.5 - 0.5 * sqrt(5.0), n)) /
                 sqrt(5.0));
}

unsigned long int fib_analytic_opt(unsigned long int n) {
   return lround((pow(0.5 + 0.5 * sqrt(5.0), n)) /
                 sqrt(5.0));
}

unsigned long int fib_helper(unsigned long int remaining, long int back_one, long int back_two){
  if (remaining == 0){
    return (back_one + back_two);
  }
  return fib_helper(remaining - 1, back_one + back_two, back_one);
}

unsigned long int fib(unsigned long int n) {
  return fib_helper(n, 1, -1);
}

void run_test(unsigned long int(*f)(unsigned long int)){
  long int r = 0;
  clock_t begin, end;
  begin = clock();
  long int i;
  for (i = 0; i < 0x10000000; i++){
    r = (r + f(i % 40)) % 0x10000;
  }
  end = clock();
  printf("%d ms, validation: %lx\n", (int)(1000 * (end - begin) / CLOCKS_PER_SEC), r);
  for (i = 0; i < 100; i++){
    r = r + f(i);
    printf("%lx %lx\n", i, f(i));
  }
}

main()
{
  printf("recursive fib: ");
  run_test(fib);

  printf("analytic fib: ");
  run_test(fib_analytic);

  printf("analytic opt fib: ");
  run_test(fib_analytic_opt);

  printf("iterative fib: ");
  run_test(fib_iterative);
}

