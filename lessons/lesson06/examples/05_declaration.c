/*
 * ============================================================
 *  05_declaration.c —— 第 6 课 · 示例 5：声明与定义
 * ============================================================
 *  C 编译器是【从上往下读】的。所以：
 *      函数定义写在调用之前   →  直接能用
 *      函数定义写在调用之后   →  必须先写一行【函数原型】告诉编译器它的存在
 *
 *  函数原型 = 把函数定义的"第一行"抄一遍，末尾加分号：
 *      int maxOfThree(int a, int b, int c);      ← 原型（声明）
 *      int maxOfThree(int a, int b, int c) { … } ← 定义
 *
 *  为什么要这样？因为编译器读到调用处时，必须知道：
 *      这个函数叫什么？要传几个参数？返回什么类型？
 *  原型就提供了这些信息，函数体可以晚点再给。
 * ============================================================
 */

#include <stdio.h>

/* ── 函数原型（声明）：只告诉编译器"有这么个东西"───────── */
int maxOfThree(int a, int b, int c);
int factorial(int n);
void printSeparator(void);

int main(void)
{
    printSeparator();
    printf("maxOfThree(3, 9, 5) = %d\n", maxOfThree(3, 9, 5));
    printf("factorial(5)        = %d\n", factorial(5));
    printSeparator();

    /* 有了原型，编译器在 main 里就能正确检查：
     *     参数个数对不对？类型对不对？返回值能不能这么用？ */

    return 0;
}

/* ============================================================
 *  下面是函数【定义】—— 放在 main 之后
 *  （如果没有上面的原型，编译就会失败，见陷阱演练场）
 * ============================================================ */

int maxOfThree(int a, int b, int c)
{
    int m = a;
    if (b > m) {
        m = b;
    }
    if (c > m) {
        m = c;
    }
    return m;
}

int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

void printSeparator(void)
{
    printf("========================================\n");
}
