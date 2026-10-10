# 第 6 课 · 作业

> **提交方式**：4 个文件都写完后，对我说一句「**批改第 6 课**」。
> 在你提交之前，我**不会**给参考答案，也**不会**准备第 7 课。
>
> **统一硬性标准（都适用）**
> 1. 用 `⌘⇧B` 编译：**0 error、0 warning**（自检请用任务「④ 严格模式编译」再跑一次）；
> 2. 每个文件**顶部注释**：文件名 + 题目编号 + 完成日期 + 一句话说明；
> 3. 缩进 4 空格、变量名见名知意、关键步骤写注释；
> 4. 只写英文标点（中文只出现在双引号内和注释里）；
> 5. 要 `scanf` 的变量，声明时就给初值；
> 6. **把真实运行输出原样粘贴进文件注释**，粘完**和基准表逐字符比对一遍**。
>
> **本课额外要求（函数专项）**
> - **函数原型写在文件开头**，函数定义写在 `main` 之后（练习"声明与定义分离"）；
> - **一个函数只做一件事**，名字要能说明它在干嘛（返回真假的用 `isXxx` 命名）；
> - **不许用全局变量** —— 数据从参数进，结果从返回值出。

---

## 必做 1 ⭐⭐⭐ 写 5 个函数并测试

**文件**：[task1_functions.c](task1_functions.c)

**任务**：写下面 5 个函数，然后在 `main` 里按基准表调用它们。

| 函数 | 功能 | 提示 |
| --- | --- | --- |
| `int maxOfThree(int a, int b, int c)` | 返回三个数里的最大值 | 先假设 `a` 最大，再逐个比 |
| `int sumTo(int n)` | 返回 1+2+…+n | 用**循环**（第 5 课的累加器） |
| `int isLeap(int year)` | 闰年返回 1，否则 0 | 第 3 课的闰年表达式 |
| `int daysInMonth(int year, int month)` | 返回该月天数；**月份不合法返回 -1** | **在函数里调用 `isLeap(year)`**（函数调用函数！） |
| `double averageOfTwo(double a, double b)` | 返回两数平均值 | 注意参数是 `double` |

**`daysInMonth` 的规则**：

- 1、3、5、7、8、10、12 月 → 31 天
- 4、6、9、11 月 → 30 天
- 2 月 → **调用 `isLeap`** 判断是 29 还是 28 天
- 其他月份 → 返回 **-1**（表示不合法）

**`main` 里必须按这个顺序调用并打印（格式一字不差）**

**我的实测基准表（我会逐字符验证）**

| 调用 | 我实测的标准输出 |
| --- | --- |
| `maxOfThree(3, 9, 5)` | `maxOfThree(3, 9, 5)  = 9` |
| `sumTo(100)` | `sumTo(100)            = 5050` |
| `isLeap(1900)` | `isLeap(1900)          = 0` |
| `isLeap(2000)` | `isLeap(2000)          = 1` |
| `isLeap(2024)` | `isLeap(2024)          = 1` |
| `daysInMonth(2024, 2)` | `daysInMonth(2024, 2)  = 29` |
| `daysInMonth(2023, 2)` | `daysInMonth(2023, 2)  = 28` |
| **`daysInMonth(2024, 13)`** | `daysInMonth(2024, 13) = -1` |
| `averageOfTwo(3, 4)` | `averageOfTwo(3, 4)    = 3.50` |

> 💡 上面每一行标签后面的空格数**是有讲究的**（用 `%-20s` 之类的宽度控制最省事，
> 也可以手数 —— 但记得粘完输出后逐字符比对）。

**我会检查什么**

- 9 行输出逐字符一致；
- **`daysInMonth` 是否真的调用了 `isLeap`**（而不是把闰年判断抄一遍）；
- 原型是否写在文件开头、定义是否在 `main` 之后；
- 有没有用全局变量；
- 0 错误 0 警告。

---

## 必做 2 ⭐⭐⭐ 改错题（2 error + 2 warning + **3 个零警告错误**）

**文件**：[task2_fixme.c](task2_fixme.c)

下面这段代码有 **6 个问题**（原型已经给好了，不用你补）：

- **2 个 error**
- **2 个 warning**（⚠️ 其中**一个会被 error 挡住**，改完 error 才会出现）
- **3 个编译器完全不报错、但结果是错的** ⚠️ **本课重点**

```c
#include <stdio.h>

/* 函数原型（已给出，不用你补） */
int add(int a, int b);
void printAndReturn(int n);
int addOne(int n);
void tryDouble(int n);
double average(int sum, int count);
int maxOf(int a, int b);

int main(void)
{
    int n = 21;

    tryDouble(n);
    printf("调用后 n = %d\n", n);

    printf("add(3, 4) = %d\n", add(3));

    printAndReturn(10);

    printf("addOne(5) = %d\n", addOne(5));

    int sum = 176, count = 5;
    printf("average = %.2f\n", average(sum, count));

    printf("maxOf(3, 9) = %d\n", maxOf(3, 9));

    return 0;
}

int add(int a, int b)
{
    return a + b;
}

void printAndReturn(int n)
{
    printf("n = %d\n", n);
    return n;
}

int addOne(int n)
{
    int result = n + 1;
}

void tryDouble(int n)
{
    n = n * 2;
}

double average(int sum, int count)
{
    return sum / count;
}

int maxOf(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return a;
}
```

**要求**

1. 把改正后的**完整代码**写进 `task2_fixme.c`，编译 **0 error 0 warning**；
2. 在「错误分析」区**逐条写出 6 个问题**，每条包含：
   - 位置：**`原题第 N 行（我的文件第 M 行）`**
   - 类型：`error` / `warning` / **零警告逻辑错误**
   - 用你自己的话说清"为什么错、错在哪"
3. **明确标出 3 个"编译器不报错但结果是错的"分别是哪几条**；
4. 运行验证，程序输出必须是（我实测的标准）：

```text
调用后 n = 42
add(3, 4) = 7
n = 10
addOne(5) = 6
average = 35.20
maxOf(3, 9) = 9
```

> ⚠️ **注意第一行**：要求输出 `调用后 n = 42`。
> 但 `tryDouble(n)` 是值传递，**它永远改不了 `n`** ——
> 你需要换一种做法让 `n` 真的变成 42（想想本课第 5 节的"两条路"）。

**提示（不给答案，给方向）**

| 问题 | 提示 |
| --- | --- |
| 第 1 处 | `add(3)` 只给了一个参数，但函数要两个 |
| 第 2 处 | `printAndReturn` 是 `void`，里面却 `return n;` |
| 第 3 处 | `addOne` 声明返回 `int`，但函数里……（这个警告会被 error 挡住，改完再编译就看到了） |
| 第 4 处 | 值传递：函数改了形参，外面不会变 |
| 第 5 处 | 函数内部的整数除法（第 3 课的坑换了个地方） |
| 第 6 处 | `maxOf` 的第二个 `return` —— 复制粘贴时忘了改？ |

**我会检查什么**

- 6 处是否全部正确处理，两套行号是否准确；
- 错误分析能否分清 **error / warning / 零警告** 三类，**并指出哪个 warning 起初看不到**；
- 上面 6 行输出是否**一字不差**（尤其 `调用后 n = 42` 和 `average = 35.20`）；
- **原型是否和定义保持一致**（改函数签名时别忘了同步改原型）；
- 0 错误 0 警告。

---

## 必做 3 ⭐⭐⭐⭐ 把前几课的逻辑"函数化"

**文件**：[task3_reuse.c](task3_reuse.c)

**任务**：把第 5 课挤在 `main` 里的逻辑，**逐个包成函数**，然后在 `main` 里调用它们。

| 函数 | 功能 | 来源 |
| --- | --- | --- |
| `int isPrime(int n)` | 是质数返回 1 | 第 5 课 |
| `int digitSum(int n)` | 各位数字之和 | 第 5 课 |
| `int reverseNumber(int n)` | 反转数字（100 → 1） | 第 5 课 |
| `int countPrimes(int from, int to)` | 统计区间内质数个数 | **在函数里调用 `isPrime`** |
| `int factorial(int n)` | n! | 本课示例 |

**`main` 里必须按这个顺序调用并打印（格式一字不差）**

**我的实测基准表（我会逐字符验证）**

| 调用 | 我实测的标准输出 |
| --- | --- |
| `isPrime(2)` | `isPrime(2)           = 1` |
| `isPrime(1)` | `isPrime(1)           = 0` |
| `isPrime(97)` | `isPrime(97)          = 1` |
| `isPrime(91)` | `isPrime(91)          = 0` |
| `digitSum(12345)` | `digitSum(12345)      = 15` |
| `reverseNumber(12345)` | `reverseNumber(12345) = 54321` |
| **`reverseNumber(100)`** | `reverseNumber(100)   = 1` |
| `countPrimes(2, 100)` | `countPrimes(2, 100)  = 25` |
| `factorial(10)` | `factorial(10)        = 3628800` |

**这一题的意义**：这三行调用就是"函数化的价值"的证明 ——

```c
printf("isPrime(97)          = %d\n", isPrime(97));
printf("countPrimes(2, 100)  = %d\n", countPrimes(2, 100));
printf("factorial(10)        = %d\n", factorial(10));
```

**主流程一眼就能看懂，细节全部藏在函数里。**

**我会检查什么**

- 9 行输出逐字符一致；
- 每个函数是否**只做一件事**（不要把 `isPrime` 和 `digitSum` 混在一个函数里）；
- `countPrimes` 是否真的**调用**了 `isPrime`；
- 有没有用全局变量；
- 0 错误 0 警告。

---

## 选做 4 ⭐⭐⭐⭐⭐ 递归三连（含汉诺塔）

**文件**：[challenge_recursion.c](challenge_recursion.c)

**任务**：写 3 个**递归**函数。

### 4.1 `int gcd(int a, int b)` —— 辗转相除法（递归版）

> 原理：`gcd(a, b) = gcd(b, a % b)`，直到 `b == 0` 时答案是 `a`。
> 这是"递归三要素"最漂亮的例子：**基准情形**是 `b == 0`，**向基准靠近**靠 `a % b` 不断变小。

### 4.2 `void printBinary(int n)` —— 递归打印二进制

> 讲义第 6.3 节讲过原理：**先递归处理高位，回来时再打印这一位**，顺序天然正确。

### 4.3 `int hanoi(int n, char from, char to, char via)` —— 汉诺塔

> 规则：把 n 个盘子从 `from` 柱移到 `to` 柱，`via` 作中转，大盘不能压在小盘上。
> 递归思路（3 行）：
> ① 把上面 n-1 个盘子从 `from` 移到 `via`（用 `to` 中转）
> ② 把第 n 号盘子从 `from` 移到 `to`
> ③ 把 n-1 个盘子从 `via` 移到 `to`（用 `from` 中转）
> **函数返回值是"总共移动了多少步"。**

**我的实测基准表（逐字符验证）**

```text
gcd(48, 18)  = 6
gcd(17, 5)   = 1
gcd(100, 75) = 25
13 的二进制  = 1101
255 的二进制 = 11111111

汉诺塔 3 层（A -> C，B 作中转）：
  第 1 号盘子：A -> C
  第 2 号盘子：A -> B
  第 1 号盘子：C -> B
  第 3 号盘子：A -> C
  第 1 号盘子：B -> A
  第 2 号盘子：B -> C
  第 1 号盘子：A -> C
共 7 步
```

**思考题**（写在注释里，用文字回答）：

> 汉诺塔 n 个盘子需要 `2ⁿ - 1` 步。
> 传说僧侣要搬完 64 个盘子，需要 `2⁶⁴ - 1` 步。
> 如果每秒搬一步，大约需要多少年？（提示：`2⁶⁴` 约等于 `1.8 × 10¹⁹`，
> 一年约 `3.15 × 10⁷` 秒）这个传说想说明什么？

**为什么做这题**：汉诺塔是**"递归思维"的终极展示** ——
用循环写要几十行还容易错，用递归**只要 5 行**。
做完这道题，你会第一次真切体会到"递归不是炫技，而是某些问题的自然表达"。

---

## 提交前自检清单

- [ ] 4 个文件都已保存
- [ ] 每个文件 `⌘⇧B` 编译：**0 错误 0 警告**；并用任务「④ 严格模式编译」再跑一遍
- [ ] 每个文件都**实际运行**过，输出**粘进注释**并和基准表**逐字符比对**
- [ ] `task1`：9 行输出一致；`daysInMonth` 真的调用了 `isLeap`
- [ ] `task2`：6 条错误分析都写了（含两套行号），标出了 **3 个零警告错误**，
      并指出**哪个 warning 起初被 error 挡住了**；6 行输出一字不差
- [ ] `task3`：9 行输出一致；`countPrimes` 真的调用了 `isPrime`
- [ ] `challenge`（若做）：输出逐字符一致；思考题写了
- [ ] **所有函数原型写在文件开头**，定义在 `main` 之后
- [ ] **没有使用任何全局变量**
- [ ] 每个 `if` / `while` / `for` 都加了花括号
- [ ] **这一课的疑问已写进 [lesson06-questions.md](lesson06-questions.md)**

---

**全部完成后**，回来对我说：**「批改第 6 课」** ✅
