/*
 * ============================================================
 *  07_qa_all_types.c —— 第 2 课 · 答疑示例
 *  【疑问 1 的答案】C 语言到底有多少种基本数据类型？格式符是什么？
 * ============================================================
 *  这个程序会打印出本机（Apple clang / macOS arm64）所有基本类型的
 *  字节数、格式符和取值范围。全部数据都是 sizeof 和 limits.h 实测得来。
 *
 *  编译：cc -std=c17 -Wall -Wextra -Wpedantic -Werror 07_qa_all_types.c -o 07_qa_all_types
 * ============================================================
 */

#include <stdio.h>
#include <limits.h>     /* INT_MAX、SCHAR_MIN 这些"极限值"住在这里 */
#include <stdint.h>     /* int8_t、int32_t 这些"定长类型"住在这里 */
#include <stdbool.h>    /* 想要 bool / true / false 就得包含它（C99 起） */

int main(void)
{
    printf("类型                 字节  格式符      取值范围 / 示例\n");
    printf("-----------------------------------------------------------------\n");

    /* ── 1. 布尔型 ─────────────────────────────────────────── */
    printf("_Bool / bool         %zu   %%d          true=%d, false=%d\n",
           sizeof(bool), (int)true, (int)false);

    /* ── 2. 字符型（3 兄弟：char 的符号性由实现决定）────────── */
    printf("char                 %zu   %%c %%d       '%c' = %d\n",
           sizeof(char), 'A', 'A');
    printf("signed char          %zu   %%hhd        %d ~ %d\n",
           sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char        %zu   %%hhu        %u ~ %u\n",
           sizeof(unsigned char), 0u, UCHAR_MAX);

    /* ── 3. 短整型 ─────────────────────────────────────────── */
    printf("short                %zu   %%hd         %d ~ %d\n",
           sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short       %zu   %%hu         %u ~ %u\n",
           sizeof(unsigned short), 0u, USHRT_MAX);

    /* ── 4. 整型（最常用）──────────────────────────────────── */
    printf("int                  %zu   %%d          %d ~ %d\n",
           sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int         %zu   %%u          %u ~ %u\n",
           sizeof(unsigned int), 0u, UINT_MAX);

    /* ── 5. 长整型 ─────────────────────────────────────────── */
    printf("long                 %zu   %%ld         %ld ~ %ld\n",
           sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long        %zu   %%lu         %lu ~ %lu\n",
           sizeof(unsigned long), 0ul, ULONG_MAX);
    printf("long long            %zu   %%lld        %lld ~ %lld\n",
           sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("unsigned long long   %zu   %%llu        %llu\n",
           sizeof(unsigned long long), ULLONG_MAX);

    /* ── 6. 浮点型 ─────────────────────────────────────────── */
    printf("float                %zu   %%f          %.5f\n", sizeof(float), 3.14159f);
    printf("double               %zu   %%f          %.5f\n", sizeof(double), 3.14159);
    printf("long double          %zu   %%Lf         %.5Lf\n", sizeof(long double), 3.14159L);

    /* ── 7. 定长类型：跨平台写代码时推荐用它们 ─────────────── */
    printf("\n--- 定长类型（stdint.h）---\n");
    printf("int8_t    %zu 字节   格式符 %%hhd    （=%d 位有符号）\n", sizeof(int8_t), 8);
    printf("int16_t   %zu 字节   格式符 %%hd     （=%d 位有符号）\n", sizeof(int16_t), 16);
    printf("int32_t   %zu 字节   格式符 %%d      （=%d 位有符号）\n", sizeof(int32_t), 32);
    printf("int64_t   %zu 字节   格式符 %%lld    （=%d 位有符号）\n", sizeof(int64_t), 64);
    printf("uint32_t  %zu 字节   格式符 %%u\n", sizeof(uint32_t));
    printf("size_t    %zu 字节   格式符 %%zu     （sizeof 的结果就是它）\n", sizeof(size_t));

    /* ── 8. 常见疑问：C 里有 byte 和 boolean 吗？───────────── */
    printf("\n--- 几个容易混淆的名字 ---\n");
    printf("byte   ：C 语言没有这个类型（那是 Java / C# 的叫法）。\n");
    printf("          C 里想表达\"1 字节无符号\"就用 unsigned char 或 uint8_t。\n");
    printf("boolean：C 语言原本没有；C99 起有了 _Bool，\n");
    printf("          包含 <stdbool.h> 后就能写 bool / true / false。\n");
    printf("String ：C 语言也没有 String 类型，字符串是\"char 数组\"（第 8 课讲）。\n");

    return 0;
}
