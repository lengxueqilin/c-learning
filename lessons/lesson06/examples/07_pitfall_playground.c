/*
 * ============================================================
 *  07_pitfall_playground.c —— 第 6 课 · 陷阱演练场
 * ============================================================
 *  用法：下面每个陷阱都被注释掉了，所以现在能正常编译。
 *        想看真实后果，删掉某一行的 // ，保存，然后编译运行。
 *        ⚠️ 第 6 条（递归没基准情形）会直接崩溃，注意看退出码。
 *
 *  本课 7 大陷阱（真实报错原文见 lesson06-errors.md）：
 *    1. 函数定义在 main 之后，却忘了写原型 → error
 *    2. 非 void 函数忘了 return → warning
 *    3. 调用时参数个数 / 类型不对 → error
 *    4. 在函数里改形参，以为能改外面 → 【零警告】逻辑错误（值传递）
 *    5. 函数重定义（同名函数写了两遍）→ error
 *    6. 递归没有基准情形 → 运行时崩溃（段错误）
 *    7. 声明了 static 函数却不调用 → warning
 * ============================================================
 */

#include <stdio.h>

/* ── 陷阱 1：忘了写原型 ───────────────────────────────────
   如果 main 里调用 lateFunction()，但它的定义在 main 下面、
   上面又没有原型 → 编译报错：
       error: call to undeclared function 'lateFunction'
   （C99 之前这只是警告，还会"猜"一个返回类型 —— 那是老代码的灾难来源）
*/

/* ── 陷阱 2：非 void 函数忘了 return ─────────────────────
   删掉下面那个 return 就会警告：
       warning: non-void function does not return a value
*/
int addOne(int n)
{
    return n + 1;
}

/* ── 陷阱 5：重定义（同一个函数写两遍）───────────────────
   int addOne(int n) { return n + 2; }     ← error: redefinition of 'addOne'
*/

/* ── 陷阱 7：static 函数写了却不用 ───────────────────────
   static int helper(void) { return 42; }   ← warning: unused function 'helper'
   （普通函数不会警告，因为"别的文件可能要用它"）
*/

/* ── 陷阱 4：改形参改不了外面（值传递）────────────────── */
void tryToDouble(int n)
{
    n = n * 2;                      /* 改的是副本！外面不会有任何变化 */
    printf("  函数里：n = %d（看着变了）\n", n);
}

/* ── 陷阱 6 的"反面教材"：没有基准情形的递归 ─────────────
   void boom(int n) { boom(n + 1); }   ← 永远不返回，栈被撑爆 → 段错误
   实测退出码 139（Segmentation fault: 11）
*/

int main(void)
{
    printf("这一行是正常的\n");

    /* ── 陷阱 3：参数个数 / 类型不对 ─────────────────────── */
    // printf("%d\n", addOne());          /* error: too few arguments */
    // printf("%d\n", addOne(1, 2));      /* error: too many arguments */

    /* ── 陷阱 4：值传递 ──────────────────────────────────── */
    int v = 21;
    printf("\n陷阱 4：值传递\n");
    printf("  调用前：v = %d\n", v);
    tryToDouble(v);
    printf("  调用后：v = %d   <- 完全没变！这就是值传递\n", v);

    /* ── 陷阱 6：递归没有基准情形（千万别真跑）────────────
       void boom(int n) { boom(n + 1); }
       int main(void) { boom(0); }        ← 段错误
       现实中的同类 bug：递归忘了写 if (n <= 1) return 1;
    */

    /* ── 想真正改外面的值，只有两条路 ─────────────────────
       ① 接收返回值：v = addOne(v);
       ② 用指针传地址（第 9 课）：void f(int *p) { *p = ...; }
    */
    v = addOne(v);
    printf("\n正确姿势（接收返回值）：v = addOne(v) → %d\n", v);

    return 0;
}
