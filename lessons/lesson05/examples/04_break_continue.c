/*
 * ============================================================
 *  04_break_continue.c —— 第 5 课 · 示例 4：break 与 continue
 * ============================================================
 *  break    ：立刻结束【整个循环】（跳出这一层）
 *  continue ：跳过【本次】剩下的语句，直接进入下一轮
 *
 *  ⚠️ 两个必须记住的点：
 *     1. 嵌套循环里，break 只跳出【一层】，不是全部！
 *     2. 循环里的 break 和 switch 里的 break【作用范围不同】（见文末）
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    /* ── break：找到就收工 ────────────────────────────────── */
    printf("找到第一个能被 7 整除的数：");
    for (int i = 1; i <= 100; i++) {
        if (i % 7 == 0) {
            printf("%d\n", i);
            break;                  /* 整个循环立刻结束 */
        }
    }

    /* ── continue：跳过本次，继续下一轮 ───────────────────── */
    printf("只打印奇数（偶数被 continue 跳过）：");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;               /* 跳过下面的 printf，直接 i++ */
        }
        printf("%d ", i);
    }
    printf("\n");

    /* ── 同一个问题，两者对比 ─────────────────────────────── */
    printf("\nbreak    at 5 ：");
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            break;                  /* 5 及以后全都不打印 */
        }
        printf("%d ", i);
    }
    printf("\n");

    printf("continue at 5 ：");
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            continue;               /* 只跳过 5，后面的继续 */
        }
        printf("%d ", i);
    }
    printf("\n");

    /* ── ⚠️ 重点：嵌套循环里，break 只跳出【一层】────────── */
    printf("\n--- 嵌套循环里的 break（只跳一层）---\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 5; j++) {
            if (j == 3) {
                break;              /* 只结束内层 j 循环 */
            }
            printf("(%d,%d) ", i, j);
        }
        printf(" <- 内层在 j=3 时 break 了，但外层 i=%d 还在继续\n", i);
    }
    printf("结论：break 只跳出【离它最近的那一层】循环。\n");

    /* 如果真的要跳出两层怎么办？—— 用一个"标志变量"控制外层： */
    printf("\n--- 想跳出两层：用标志变量 ---\n");
    int found = 0;                  /* 标志变量 */
    for (int i = 1; i <= 3 && !found; i++) {           /* 外层条件里检查标志 */
        for (int j = 1; j <= 3; j++) {
            if (i * j == 4) {
                printf("找到 i=%d, j=%d，两层都跳出\n", i, j);
                found = 1;          /* 立起标志 */
                break;              /* 先跳内层 */
            }
        }
    }

    /* ── ⚠️ 循环的 break vs switch 的 break ───────────────── */
    printf("\n--- 循环里的 break 会不会被 switch 的 break 带出去？---\n");
    for (int i = 1; i <= 3; i++) {
        printf("外层第 %d 轮：", i);
        switch (i) {
            case 2:
                printf("switch 命中 case 2，执行 break；");
                break;              /* 这个 break 只结束 switch！ */
            default:
                printf("switch 走 default；");
                break;
        }
        printf("【循环还在继续】\n");
    }
    printf("结论：switch 里的 break 只结束 switch，不会结束外面那层循环。\n");
    printf("      这和第 4 课学的是同一个 break —— 它结束【最近的那个可以跳出的结构】。\n");

    return 0;
}
