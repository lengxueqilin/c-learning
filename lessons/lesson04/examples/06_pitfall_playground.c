/*
 * ============================================================
 *  06_pitfall_playground.c —— 第 4 课 · 陷阱演练场
 * ============================================================
 *  用法：下面每个陷阱都被注释掉了，所以现在能正常编译。
 *        想看真实后果，删掉某一行的 // ，保存，然后编译运行。
 *        看完记得把 // 加回去。
 *
 *  本课 8 大陷阱（真实报错原文见 lesson04-errors.md）：
 *    1. if (x = 5)     赋值当成条件（clang 会警告，加双括号它就不管了）
 *    2. if (x > 0);    多写一个分号 → 空语句体（clang 会警告）
 *    3. if (a < b < c) 数学写法（clang 默认就报 error！）
 *    4. switch 忘记 break → 贯穿（编译器默认【不警告】）
 *    5. 浮点数用 == 比较（无警告，结果可能出乎意料）
 *    6. 没有 if 的 else（error）
 *    7. case 用变量 / 重复 case / switch 用 double（三个 error）
 *    8. 悬挂 else（缩进骗人）
 * ============================================================
 */

#include <stdio.h>

int main(void)
{
    int x = 3;
    int a = 3, b = 5, c = 1;

    printf("这一行是正常的：x = %d\n\n", x);

    /* ── 陷阱 1：把 = 写进 if 的条件 ─────────────────────── */
    // if (x = 5) { printf("进来了，x 已经变成 %d\n", x); }   /* clang 警告 -Wparentheses */
    // if ((x = 5)) { printf("加双括号就没警告了，x = %d\n", x); }  /* 警告消失，但依然是赋值！ */

    /* ── 陷阱 2：if 后面多写一个分号 ─────────────────────── */
    // if (x > 0);                 /* 这个分号就是 if 的"空语句体" */
    // { printf("x 是正数\n"); }     /* 这段代码永远会执行，与 if 无关 */

    /* ── 陷阱 3：数学写法 a < b < c（clang 默认就报 error）── */
    // if (a < b < c) { printf("三个数递增？\n"); }

    /* ── 陷阱 4：switch 忘记 break ───────────────────────── */
    // switch (x) {
    //     case 3: printf("星期三\n");     /* 少了 break，会继续往下 */
    //     case 4: printf("星期四\n"); break;
    //     default: break;
    // }

    /* ── 陷阱 5：浮点数用 == 比较（无警告）──────────────── */
    // double sum = 0.1 + 0.2;
    // if (sum == 0.3) { printf("相等\n"); }
    // else { printf("居然不相等！sum = %.20f\n", sum); }

    /* ── 陷阱 6：没有 if 的 else ─────────────────────────── */
    // else { printf("孤零零的 else\n"); }

    /* ── 陷阱 7：switch 的三个硬限制 ─────────────────────── */
    // int y = 1;
    // switch (x) { case y: printf("y\n"); break; }          /* error: case 必须是整数常量 */
    // switch (x) { case 1: printf("a\n"); case 1: printf("b\n"); break; }  /* error: 重复 case */
    // double d = 1.5;
    // switch (d) { case 1: printf("1\n"); break; }          /* error: 只能对整数用 switch */

    /* ── 陷阱 8：悬挂 else（缩进骗人，编译器不报警告）────── */
    // if (a == 0)
    //     if (b == 0)
    //         printf("都在原点\n");
    // else
    //     printf("这句 else 其实属于【内层】的 if！\n");
    // 解法：老老实实给每一层都加花括号。

    printf("陷阱 3 示范（正确的写法）：a < b && b < c = %d\n", a < b && b < c);
    printf("  数学里的 a < b < c，在 C 里必须写成 a < b && b < c\n");

    return 0;
}
