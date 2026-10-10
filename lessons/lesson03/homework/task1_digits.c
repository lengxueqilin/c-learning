/*
 * ============================================================
 *  文件：task1_digits.c
 *  题目：第 3 课作业 3-1（必做 ⭐⭐）拆位与整除
 *  完成：2026-10-10
 *  说明：读入一个三位正整数（100 ~ 999），把它拆开并做整除判断。
 * ============================================================
 *  要求（详见同目录 lesson03-homework.md）：
 *    · 读入一个三位正整数（100~999）；
 *    · 输出 8 行，标签宽 16 左对齐，数值宽 3 右对齐，中间是 " = "；
 *    · 标签和顺序必须是：number / hundreds digit / tens digit / ones digit /
 *      sum of digits / divisible by 2 / divisible by 3 / ones is even
 *    · 后 4 行是比较运算的结果（0 或 1），不能手写死；
 *    · 编译必须 0 error、0 warning。
 *
 *  输入 483 时的期望输出（共 22 字符宽，我已实测）：
 *
 *      number           = 483
 *      hundreds digit   =   4
 *      tens digit       =   8
 *      ones digit       =   3
 *      sum of digits    =  15
 *      divisible by 2   =   0
 *      divisible by 3   =   1
 *      ones is even     =   0
 *
 *  提示：拆位口诀 —— 先 / 砍掉尾巴，再 % 取出新尾巴。
 *        先把 483 在纸上拆一遍，再写代码。
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    int number = 0;
    printf("请输入一个三位正整数：");
    scanf("%d", &number);
    printf("\n");

    // 定义 3 个变量存拆位的数据
    int ones, tens, hundreds;
    ones = number % 10;
    tens = number / 10 % 10;
    hundreds = number / 10 / 10;

    printf("%-16s = %3d\n", "number", number);
    printf("%-16s = %3d\n", "hundreds digit", hundreds);
    printf("%-16s = %3d\n", "tens digit", tens);
    printf("%-16s = %3d\n", "ones digit", ones);
    printf("%-16s = %3d\n", "sum of digits", ones + tens + hundreds);
    printf("%-16s = %3d\n", "divisible by 2", number % 2 == 0);
    printf("%-16s = %3d\n", "divisible by 3", number % 3 == 0);
    printf("%-16s = %3d\n", "ones is even", ones % 2 == 0);

    return 0;
}
