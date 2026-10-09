/*
 * ============================================================
 *  02_types.c —— 第 2 课 · 示例 2：三种基本数据类型 + sizeof
 * ============================================================
 *  为什么要分类型？因为内存里的 0 和 1 本身没有含义，
 *  是"类型"决定了：这段内存占几个字节、该怎么解释它、能表示多大范围。
 *
 *  int     整数        例如 42、-7、0
 *  double  小数（双精度）例如 1.75、-3.14      日常算小数就用它
 *  float   小数（单精度）例如 62.5f            占空间小、精度低，字面量要加 f
 *  char    单个字符     例如 'A'、'7'、'!'      注意是单引号！
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    int    students = 42;        /* 整数 */
    double height   = 1.75;      /* 小数，默认就是 double */
    float  weight   = 62.5f;     /* 加了 f 才是 float，不加 f 编译器会当成 double */
    char   grade    = 'A';       /* 单个字符，必须用单引号 */

    printf("students = %d\n", students);
    printf("height   = %f\n", height);
    printf("weight   = %f\n", weight);
    printf("grade    = %c\n", grade);

    /* ── 有趣的一幕：同一个 char，用两种格式符看它 ─────────── */
    printf("grade 当成字符看是 %c，当成整数看是 %d\n", grade, grade);
    /* 上面那个整数就是 ASCII 编码：'A' 是 65，'a' 是 97，'0' 是 48 */

    /* ── sizeof：问编译器"这个东西占几个字节" ───────────────── */
    printf("\n--- 各种类型占多少字节（本机实测）---\n");
    printf("sizeof(char)   = %zu 字节\n", sizeof(char));
    printf("sizeof(int)    = %zu 字节\n", sizeof(int));
    printf("sizeof(float)  = %zu 字节\n", sizeof(float));
    printf("sizeof(double) = %zu 字节\n", sizeof(double));

    /* ── sizeof 也能直接量变量和字面量 ────────────────────── */
    printf("\n--- 量变量和字面量 ---\n");
    printf("sizeof(students) = %zu  (变量 students)\n", sizeof(students));
    printf("sizeof(height)   = %zu  (变量 height)\n", sizeof(height));
    printf("sizeof(1.75)     = %zu  (小数默认是 double)\n", sizeof(1.75));
    printf("sizeof(1.75f)    = %zu  (加 f 才是 float)\n", sizeof(1.75f));
    printf("sizeof(42)       = %zu  (整数默认是 int)\n", sizeof(42));

    return 0;
}
