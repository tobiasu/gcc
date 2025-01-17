/* { dg-do compile } */
/* { dg-options "-O2 -fopenmp -fvect-cost-model=cheap -fdump-tree-vect-details" } */
/* { dg-additional-options "-msse2" { target { i?86-*-* x86_64-*-* } } } */
/* { dg-additional-options "-mavx" { target avx } } */
/* { dg-final { scan-tree-dump-times "vectorized \[1-9]\[0-9]* loops in function" 5 "vect" { target i?86-*-* x86_64-*-* aarch64-*-* } } } */

int a[10000][128];

void
foo (void)
{
  #pragma omp for simd schedule (simd: dynamic, 32) collapse(2)
  for (int i = 0; i < 10000; i++)
    for (int j = 0; j < 128; j++)
      a[i][j] += 3;
}

void
bar (void)
{
  #pragma omp parallel for simd schedule (simd: dynamic, 32) collapse(2)
  for (int i = 0; i < 10000; i++)
    for (int j = 0; j < 128; j++)
      a[i][j] += 3;
}

void
baz (void)
{
  #pragma omp distribute parallel for simd schedule (simd: dynamic, 32) collapse(2)
  for (int i = 0; i < 10000; i++)
    for (int j = 0; j < 128; j++)
      a[i][j] += 3;
}

void
qux (void)
{
  #pragma omp distribute simd dist_schedule (static, 128) collapse(2)
  for (int i = 0; i < 10000; i++)
    for (int j = 0; j < 128; j++)
      a[i][j] += 3;
}

void
corge (void)
{
  #pragma omp taskloop simd collapse(2)
  for (int i = 0; i < 10000; i++)
    for (int j = 0; j < 128; j++)
      a[i][j] += 3;
}
