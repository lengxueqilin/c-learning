/*
 * ============================================================
 *  文件：task1_loop_stats.c
 *  题目：第 5 课作业 5-1（必做 ⭐⭐⭐）哨兵值循环：统计一列数字
 *  完成：2026-10-10
 *  说明：不断地读入整数，直到读入 0 为止，然后输出统计结果。
 * ============================================================
 *  要求（详见同目录 lesson05-homework.md）：
 *    · 不断读入整数，直到读入 0 为止（0 是"哨兵值"，只作结束标志，不参与统计）
 *    · 用 while + break 实现
 *    · 输出 5 行（顺序、标签、格式必须一致）：
 *          count   = 个数
 *          sum     = 总和
 *          max     = 最大值
 *          min     = 最小值
 *          average = 平均值（保留 2 位小数）
 *    · 如果一个数据都没有（第一个就是 0），只输出一行：没有输入任何数据
 *    · 编译必须 0 error、0 warning。
 *
 *  ⚠️ 提示：max / min 初始化成 0 是错的（遇到全负数就会错）。
 *            想想怎么初始化才稳妥？基准表里有一组全是负数的数据。
 *
 *  ⭐ 请把你实测的输出原样贴在这里（至少包含 23 7 99 42 5 0 和 -3 -8 0 两组）：
 *
 *      请输入整数（输入 0 结束）：23 7 99 42 5 0
 *      count   = 5
 *      sum     = 176
 *      max     = 99
 *      min     = 5
 *      average = 35.20
 *      请输入整数（输入 0 结束）：0
 *      没有输入任何数据
 *      请输入整数（输入 0 结束）：5 0
 *      count   = 1
 *      sum     = 5
 *      max     = 5
 *      min     = 5
 *      average = 5.00
 *      请输入整数（输入 0 结束）：-3 -8 0
 *      count   = 2
 *      sum     = -11
 *      max     = -3
 *      min     = -8
 *      average = -5.50
 *      请输入整数（输入 0 结束）：10 20 30 0
 *      count   = 3
 *      sum     = 60
 *      max     = 30
 *      min     = 10
 *      average = 20.00
 *      请输入整数（输入 0 结束）：7 -7 0
 *      count   = 2
 *      sum     = 0
 *      max     = 7
 *      min     = -7
 *      average = 0.00
 *
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    int number = 0;
    int count = 0;
    int sum = 0;
    int min = 0;
    int max = 0;
    int first = 1;
    printf("请输入整数（输入 0 结束）：");

    while (1)
    {
        scanf("%d", &number);
        if (number == 0)
        {
            break;
        }
        count++;
        sum += number;
        if (first == 1)
        {
            min = number;
            max = number;
            first = 0;
        }
        else
        {
            if (number > max)
            {
                max = number;
            }
            if (number < min)
            {
                min = number;
            }
        }
    }

    if (count == 0)
    {
        printf("没有输入任何数据\n");
    }
    else
    {
        printf("%-7s = %d\n", "count", count);
        printf("%-7s = %d\n", "sum", sum);
        printf("%-7s = %d\n", "max", max);
        printf("%-7s = %d\n", "min", min);
        printf("%-7s = %.2f\n", "average", (double)sum / count);
    }

    return 0;
}
