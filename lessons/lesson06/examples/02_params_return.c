/*
 * ============================================================
 *  02_params_return.c —— 第 6 课 · 示例 2：参数与返回值
 * ============================================================
 *  参数（parameter）：函数从外面"拿进来"的数据
 *  返回值（return value）：函数"送出去"给调用者的结果
 *
 *  ⚠️ 一条重要限制：一个函数【只能返回一个值】。
 *     想返回两个？（比如交换）—— 要么用结构体（第 11 课），
 *     要么用指针（第 9 课）。第 4 节你会亲眼看到这个限制。
 * ============================================================
 */

#include <stdio.h>

/* ── 一个参数、一个返回值 ─────────────────────────────── */
int square(int n)
{
    return n * n;
}

/* ── 两个参数 ─────────────────────────────────────────── */
int add(int a, int b)
{
    return a + b;
}

int maxOf(int a, int b)
{
    return a > b ? a : b;           /* 第 4 课的三目运算符 */
}

/* ── 返回 double：注意整数除法陷阱依然存在 ─────────────── */
double average(int sum, int count)
{
    return (double)sum / count;     /* 不加 (double) 就是整数除法 */
}

/* ── 用 int 返回"真/假"（0 或 1）─────────────────────── */
int isEven(int n)
{
    return n % 2 == 0;
}

/* ── 把第 5 课的质数判断包成函数 ─────────────────────── */
int isPrime(int n)
{
    if (n < 2) {
        return 0;                   /* 提前 return：函数立刻结束 */
    }
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return 0;               /* 找到因子，立刻返回"不是" */
        }
    }
    return 1;                       /* 全部试完都没找到 → 是质数 */
}

/* ── void：明确表示"没有返回值" ──────────────────────── */
void printTitle(void)
{
    printf("=== 参数与返回值 ===\n");
}

int main(void)
{
    printTitle();

    printf("square(7)       = %d\n", square(7));
    printf("add(3, 4)       = %d\n", add(3, 4));
    printf("maxOf(3, 9)     = %d\n", maxOf(3, 9));
    printf("average(176, 5) = %.2f\n", average(176, 5));

    printf("isEven(42)      = %d\n", isEven(42));
    printf("isPrime(97)     = %d\n", isPrime(97));
    printf("isPrime(91)     = %d\n", isPrime(91));

    /* ── 函数可以嵌在表达式里，因为它"是一个值" ──────────── */
    printf("\n函数可以当值用：maxOf(add(1,2), square(2)) = %d\n",
           maxOf(add(1, 2), square(2)));

    /* ── 关于 return 的两件事 ──────────────────────────────
     * 1. 返回一个值给调用者；
     * 2. 【立刻结束整个函数】—— 后面即使还有代码也不会执行。
     *
     * 所以 isPrime 里那个"找到因子就 return 0"，
     * 等价于第 5 课写的 "isPrime = 0; break;"，但更简洁。
     */

    return 0;
}
