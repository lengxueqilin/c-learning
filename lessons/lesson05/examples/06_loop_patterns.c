/*
 * ============================================================
 *  06_loop_patterns.c —— 第 5 课 · 示例 6：四个经典循环模式
 * ============================================================
 *  这四个"套路"你必须熟到能默写，因为它们会反复出现在各种题目里：
 *      模式 1：一边遍历一边更新最值（最大 / 最小）
 *      模式 2：数位拆解（while + % 和 /）—— 第 3 课的零件正式组装
 *      模式 3：数二进制里有多少个 1
 *      模式 4：判断质数（break 的经典用法）
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    /* ── 模式 1：一边"遍历"一边更新最值 ──────────────────── */
    printf("=== 模式 1：求最大值 / 最小值 / 平均值 ===\n");

    int max = -1;                   /* 技巧：最小值初始化成一个"肯定比所有数据都小"的值 */
    int min = 101;                  /*       最大值初始化成一个"肯定比所有数据都大"的值 */
    int count = 0;
    int sum = 0;

    /* 数组要第 7 课才学，这里用一个公式"造"出 10 个数据来演示 */
    for (int i = 1; i <= 10; i++) {
        int value = (i * 37) % 100;             /* 37, 74, 11, 48, 85, 22, 59, 96, 33, 70 */
        printf("  第 %2d 个数据 = %2d\n", i, value);

        if (value > max) { max = value; }       /* 比最大还大 → 更新 */
        if (value < min) { min = value; }       /* 比最小还小 → 更新 */
        sum += value;                           /* 累加 */
        count++;                                /* 计数 */
    }
    printf("  个数 = %d，总和 = %d，最大 = %d，最小 = %d，平均 = %.2f\n",
           count, sum, max, min, (double)sum / count);

    /* ── 模式 2：数位拆解（顺带做反转）───────────────────── */
    printf("\n=== 模式 2：数位拆解 + 数字反转 ===\n");
    int n = 12345;
    int original = n;               /* 备份！因为下面的循环会把 n 改掉 */
    int digits = 0;
    int digitSum = 0;
    int reversed = 0;

    while (n > 0) {
        int digit = n % 10;                 /* ① 取出最后一位 */
        digitSum += digit;                  /* ② 累加各位数字 */
        reversed = reversed * 10 + digit;   /* ③ 关键一步：把结果"往左推一格"再放新位 */
        n /= 10;                            /* ④ 砍掉最后一位 */
        digits++;
    }
    printf("  原数 = %d\n", original);
    printf("  位数 = %d\n", digits);
    printf("  各位数字之和 = %d\n", digitSum);
    printf("  反转后的数 = %d\n", reversed);

    /* reversed = reversed * 10 + digit 为什么能反转？
     *   第1轮：0 * 10 + 5 = 5
     *   第2轮：5 * 10 + 4 = 54
     *   第3轮：54 * 10 + 3 = 543      ← 每轮把旧结果"左移一位"，再把新数字放到个位
     *   第4轮：543 * 10 + 2 = 5432
     *   第5轮：5432 * 10 + 1 = 54321
     */

    /* ── 模式 3：数二进制里有多少个 1 ─────────────────────── */
    printf("\n=== 模式 3：二进制里 1 的个数 ===\n");
    int m = 13;
    int temp = m;
    int ones = 0;

    while (temp > 0) {
        if (temp % 2 == 1) {        /* 取出最低位，看是不是 1 */
            ones++;
        }
        temp /= 2;                  /* 右移一位（等价于除以 2） */
    }
    printf("  %d 的二进制是 1101，其中有 %d 个 1\n", m, ones);
    printf("  （这个思路以后做位运算时还会遇到，选修课会讲）\n");

    /* ── 模式 4：判断质数（break 的经典用法）─────────────── */
    printf("\n=== 模式 4：判断质数 ===\n");

    int candidate = 97;
    int isPrime = 1;                /* 先"假设"是质数，发现因子就推翻 */

    if (candidate < 2) {
        isPrime = 0;                /* 0 和 1 都不是质数 */
    }
    for (int d = 2; d * d <= candidate; d++) {   /* 只需试到 √n（用 d*d <= n 避免开方）*/
        if (candidate % d == 0) {
            printf("  %d 能被 %d 整除，立刻 break（不用再试了）\n", candidate, d);
            isPrime = 0;
            break;
        }
    }
    if (isPrime) {
        printf("  %d 是质数\n", candidate);
    } else {
        printf("  %d 不是质数\n", candidate);
    }

    candidate = 91;                 /* 91 = 7 × 13 */
    isPrime = 1;
    for (int d = 2; d * d <= candidate; d++) {
        if (candidate % d == 0) {
            printf("  %d 能被 %d 整除，立刻 break（不用再试了）\n", candidate, d);
            isPrime = 0;
            break;
        }
    }
    printf("  %d %s质数\n", candidate, isPrime ? "是" : "不是");

    return 0;
}
