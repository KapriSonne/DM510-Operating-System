#include <stdio.h>
#include <inttypes.h>

float power(float x, uint32_t exp);
float power(float x, uint32_t exp)
{

float result;
/* base case */
if (exp == 0)
  return 1.0;
  // '>>' is a logical rightshift
  result = power(x, exp >> 1);
  result = result * result;
  // '&' is a binary logical 'and'
if (exp & 1)
  result = result * x;
  return result;
}

int main(int argc, char **argv)
{
  float p;
  p = power(10.0, 5);
  printf("p = %f\n", p);
  return 0;
}
