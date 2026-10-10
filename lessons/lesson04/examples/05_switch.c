/*
 * ============================================================
 *  05_switch.c —— 第 4 课 · 示例 5：switch / case
 * ============================================================
 *  switch 适合"一个值 vs 一串【确定的整数】"的场景。
 *  它比 if-else 链更整齐，但有三个硬性限制：
 *      1. 只能判断【相等】，不能写范围（不能 case >= 60）
 *      2. case 后面只能是【整数常量】（不能是变量、不能是 double、不能是字符串）
 *      3. 【千万别忘 break】—— 忘了会"贯穿"到下一个 case
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    int day = 3;

    /* ── 基本用法 ─────────────────────────────────────────── */
    printf("day = %d\n", day);
    switch (day) {
        case 1:
            printf("星期一\n");
            break;                      /* ⚠️ 每个 case 后面都要 break */
        case 2:
            printf("星期二\n");
            break;
        case 3:
            printf("星期三\n");
            break;
        case 4:
            printf("星期四\n");
            break;
        default:                        /* 兜底：以上都不匹配时 */
            printf("不在 1~4 范围内\n");
            break;
    }

    /* ── 忘记 break 的真实后果：贯穿（fallthrough）────────── */
    printf("\n--- 忘记 break 会怎样 ---\n");
    switch (day) {
        case 3:
            printf("星期三\n");          /* 这里没有 break！ */
        case 4:
            printf("星期四  <- 也被执行了\n");
            break;
        default:
            break;
    }
    printf("原因：case 命中后，程序会一直往下执行，直到遇到 break 或 switch 结束。\n");
    printf("⚠️ 而且编译器默认【不会警告】这件事（要显式打开 -Wimplicit-fallthrough）。\n");

    /* ── fallthrough 的【正当用法】：多个 case 共享同一段代码 ── */
    printf("\n--- 正当用法：多个 case 共享代码 ---\n");
    int month = 4;
    int days = 0;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days = 31;                  /* 这些月份都是 31 天，故意贯穿 */
            break;
        case 4: case 6: case 9: case 11:
            days = 30;
            break;
        case 2:
            days = 28;                  /* 平年 2 月；闰年 29 天（作业里你会处理） */
            break;
        default:
            days = -1;                  /* 用 -1 表示"月份不合法" */
            break;
    }

    if (days > 0) {
        printf("%d 月有 %d 天\n", month, days);
    } else {
        printf("月份 %d 不合法\n", month);
    }

    /* ── 对比：同样的逻辑用 if-else 写要长很多 ─────────────
        if (month == 1 || month == 3 || month == 5 || month == 7 ||
            month == 8 || month == 10 || month == 12) { days = 31; }
        else if (...) { ... }
       用 switch 的"共享 case"更整齐。 */

    /* ── switch 也支持字符（因为 char 本质是整数）────────── */
    printf("\n--- switch 也能判断字符 ---\n");
    char grade = 'B';
    switch (grade) {
        case 'A':
            printf("优秀\n");
            break;
        case 'B':
            printf("良好\n");
            break;
        case 'C':
            printf("及格\n");
            break;
        default:
            printf("未知等级\n");
            break;
    }

    return 0;
}
