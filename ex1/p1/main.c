#include <stdio.h>
#include <stdlib.h>

int main()
{
  int id;

  if (scanf("%d", &id) != 1)
  {
    printf("Input error:\n");
    return EXIT_FAILURE;
  }

  int t, sum = 0, remainder;

  t = id;
  while (t != 0)
  {
    remainder = t % 10;
    sum = sum + remainder;
    t = t / 10;
  }

  int magic_x = sum % 4;
  int draft_variant_num = magic_x + 1;
  int variant_num = (draft_variant_num % 4) + 1;
  printf("draft: %d, variant: %d\n", draft_variant_num, variant_num);

  return EXIT_SUCCESS;
}