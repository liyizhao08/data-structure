#include <stdio.h>
#include <time.h>

/* 防止编译器把"没被用到的计算"优化掉 */
static volatile long sink;

/* O(n)：循环 n 次 */
static long sum_n(int n)
{
    long s = 0;
    for (int i = 1; i <= n; i++) s += i;
    return s;
}

/* O(n^2)：外层 n 次，内层 n 次，共 n*n 次 */
static long count_pairs(int n)
{
    long c = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c++;
    return c;
}

int main(void)
{
    printf("%-8s %-14s %-14s %-12s %s\n",
           "n", "O(n)次数", "O(n^2)次数", "O(n)时间", "O(n^2)时间");
    printf("--------------------------------------------------------------\n");

    for (int n = 10000; n <= 40000; n *= 2) {
        clock_t t0 = clock();
        sink += sum_n(n);
        clock_t t1 = clock();
        sink += count_pairs(n);
        clock_t t2 = clock();

        printf("%-8d %-14ld %-14ld %-12.5f %.5f\n",
               n, (long)n, (long)n * n,
               (double)(t1 - t0) / CLOCKS_PER_SEC,
               (double)(t2 - t1) / CLOCKS_PER_SEC);
    }

    printf("\n结论：n 翻倍时，O(n) 的次数翻倍，O(n^2) 的次数变成 4 倍。\n");
    return 0;
}