# 第 4 课 · 常见报错速查（真实原文对照）

> 所有报错信息都是**在你自己的电脑上实测粘贴下来的**（Apple clang 21 / macOS arm64）。
>
> **第 4 课有个好消息**：`if` 一出现，编译器就多了一层保护 ——
> 第 3 课那个"`=` 写成 `==` 却零警告"的大坑，**在 `if` 的条件里终于会被抓住了**（见第二节）。

---

## 一、本课关键词总览

| 关键词 | 出现在哪 | 严重程度 | 意味着 |
| --- | --- | --- | --- |
| `-Wparentheses`（赋值当条件） | 编译 warning | 中 | `if (x = 5)` —— 你是不是想写 `==`？ |
| `-Wempty-body` | 编译 warning | 中 | `if (x > 0);` —— 多打了一个分号，if 后面是空语句 |
| `chained comparison ... [-Wparentheses]` | **编译 error（默认就报！）** | 低（抓得住） | `a < b < c` 不是数学写法 |
| `statement requires expression of integer type` | 编译 error | 低 | 对 `double` 用了 `switch` |
| `duplicate case value` | 编译 error | 低 | 同一个 `switch` 里 case 重复 |
| `expression is not an integer constant expression` | 编译 error | 低 | `case` 后面写了变量 |
| **什么都没有** ⚠️ | —— | **最高** | `switch` 忘记 `break`、浮点用 `==`、悬挂 `else` |

---

## 二、⭐ 悬念揭晓：`if (x = 5)` 终于会被抓住了

第 3 课我们实测过：`printf("%d", x = 5)` **一句警告都没有**，结果悄悄错掉。
但**同样一个 `=`，放进 `if` 的条件里，clang 立刻警告**：

**真实警告：**

```text
q1.c:2:35: warning: using the result of an assignment as a condition without parentheses [-Wparentheses]
    2 | int main(void) { int x = 3; if (x = 5) { printf("进来了，x=%d\n", x); } return 0; }
      |                                 ~~^~~
q1.c:2:35: note: place parentheses around the assignment to silence this warning
    2 | int main(void) { int x = 3; if (x = 5) { printf("进来了，x=%d\n", x); } return 0; }
      |                                   ^
      |                                 (    )
q1.c:2:35: note: use '==' to turn this assignment into an equality comparison
    2 | int main(void) { int x = 3; if (x = 5) { printf("进来了，x=%d\n", x); } return 0; }
      |                                   ^
      |                                   ==
1 warning generated.
```

**真实运行结果：**

```text
进来了，x=5
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "你在一段条件里用了赋值表达式，而且没加括号" |
| **clang 给了两条出路** | ① 加括号 `(x = 5)` 表示"我就是要赋值"；② 改成 `==` 表示"我其实想比较" |
| **为什么第 3 课抓不住、这里抓得住** | 因为 **`if` 的括号是一个"条件位置"**，C 语法在这里特殊对待；而 `printf` 的参数列表是普通表达式，怎么写都合法 |
| **⚠️ 双括号是个陷阱** | 写成 `if ((x = 5))`，警告**就消失了**，但**依然是赋值**！实测仍然输出 `x=5` |

**所以记住三句话**：

1. **看到 `-Wparentheses` 提到 assignment，99% 是你想写 `==`** —— 去改，别加括号消警告；
2. **别用双括号来"消警告"** —— 那是告诉编译器"我知道我在赋值"，通常你并不知道；
3. 真的需要在条件里赋值（很少见，如 `while ((c = getchar()) != EOF)`），
   那就加括号，并**在注释里说明为什么**。

---

## 三、`if` 后面多打一个分号：空语句体（`-Wempty-body`）

**真实警告：**

```text
q2.c:2:39: warning: if statement has empty body [-Wempty-body]
    2 | int main(void) { int x = 3; if (x > 0); { printf("x 是正数\n"); } return 0; }
      |                                       ^
q2.c:2:39: note: put the semicolon on a separate line to silence this warning
1 warning generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "这个 if 的语句体是空的" |
| **原因** | `if (x > 0);` 里的那个 `;` 本身就是 if 的"语句体"（一条空语句） |
| **后果** | 后面的大括号块 **变成无条件执行的普通代码块** —— 不管条件真假都会跑 |
| **怎么改** | 删掉那个分号 |
| **记住** | **`if (...)` 后面永远不要出现裸分号**；`while`、`for` 同理（第 5 课还会遇到） |

**对比一下**（这个分号陷阱的另一种表现）：

```c
if (x > 0);          /* ❌ 空语句体：下面的块永远执行 */
if (x > 0) { }       /* ✅ 这才是"什么都不做"，意图明确 */
```

---

## 四、`a < b < c`：数学写法在 C 里**默认就报 error**

**真实报错（注意：不加任何编译选项也会报）：**

```text
q3.c:2:53: error: chained comparison 'X < Y < Z' does not behave the same as a mathematical expression [-Wparentheses]
    2 | int main(void) { int a = 3, b = 5, c = 1; if (a < b < c) { printf("真的？\n"); } return 0; }
      |                                                     ^
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "链式比较 `X < Y < Z` 的行为和数学表达式不一样" |
| **为什么不一样** | C 会先算 `a < b`，得到一个 **0 或 1**，再拿它和 `c` 比：`(a < b) < c` |
| **举例** | `a=3, b=1, c=5`：数学上"3<1<5"是假；但 C 算的是 `(3<1) < 5` = `0 < 5` = **真** |
| **怎么改** | 用逻辑与连接：`a < b && b < c` |
| **好消息** | clang **默认就把它当错误**，你不可能不小心写错 —— 这是编译器在帮你 |

> 💡 **顺带记住这个模式**：想表达"x 在 [0, 100] 之间"，
> 数学写法 `0 <= x <= 100` 在 C 里是错的，要写 `x >= 0 && x <= 100`。
> **作业 1 正好要用到这个。**

---

## 五、`switch` 忘记 `break`（⚠️ **默认一句警告都没有**）

**真实编译结果：零警告。**

**真实运行结果（`x = 2`）：**

```text
二
三
```

| 项目 | 内容 |
| --- | --- |
| **原因** | `case` 命中后，程序**一直往下执行**，直到遇到 `break` 或 `switch` 结束 —— 这叫**贯穿（fallthrough）** |
| **为什么说是"陷阱"** | 编译器**默认不警告**这件事！你只会看到输出多了一行 |
| **想让它警告** | 显式打开 `-Wimplicit-fallthrough` |

**显式打开后的真实警告：**

```text
q4.c:2:65: warning: unannotated fall-through between switch labels [-Wimplicit-fallthrough]
    2 | int main(void) { int x = 1; switch (x) { case 1: printf("一"); case 2: printf("二"); break; default: printf("其他"); } printf("\n"); return 0; }
      |                                                                ^
q4.c:2:65: note: insert '__attribute__((fallthrough));' to silence this warning
q4.c:2:65: note: insert 'break;' to avoid fall-through
```

**两条路**：

```c
/* ① 加 break（99% 的情况你要的是这个） */
case 1:
    printf("一\n");
    break;

/* ② 故意贯穿时，明确"标注"出来，让读代码的人知道这不是 bug */
case 1:
    /* fall through */          /* 或者用 __attribute__((fallthrough)); */
case 2:
    ...
```

**什么时候"故意贯穿"是正当的**：多个 case 共享同一段代码，比如：

```c
case 1: case 3: case 5: case 7: case 8: case 10: case 12:
    days = 31;          /* 这些月份都是 31 天 —— 空 case 连写，是标准写法 */
    break;
```

> **结论：`case` 后面要么有 `break`，要么有注释说明"我是故意的"。**
> 这条纪律能让你少写无数个 bug。

---

## 六、`switch` / `case` 的三个硬限制（都是 error）

### 6.1 `switch` 只能对整数用

```text
q5.c:2:34: error: statement requires expression of integer type ('double' invalid)
    2 | int main(void) { double d = 1.5; switch (d) { case 1: printf("1\n"); break; } return 0; }
      |                                  ^       ~
1 error generated.
```

### 6.2 `case` 不能重复

```text
q6.c:2:77: error: duplicate case value '1'
    2 | int main(void) { int x = 1; switch (x) { case 1: printf("a\n"); break; case 1: printf("b\n"); break; } return 0; }
      |                                                                             ^
q6.c:2:47: note: previous case defined here
1 error generated.
```

### 6.3 `case` 后面必须是**整数常量**，不能是变量

```text
q10.c:2:54: error: expression is not an integer constant expression
    2 | int main(void) { int x = 1, y = 1; switch (x) { case y: printf("y\n"); break; } return 0; }
      |                                                      ^
1 error generated.
```

| 限制 | 说明 |
| --- | --- |
| ① 只能判**相等** | 不能写 `case >= 60`，**范围判断只能用 `if-else`** |
| ② 只能对**整数**（含 `char`、`enum`） | `double`、字符串都不行 |
| ③ `case` 必须是**编译期常量** | 不能是变量，也不能在运行时算出来 |
| ④ 每个 case 值必须**唯一** | 重复会直接报错 |

> **所以第 4 课作业里**：成绩等级那种"范围判断"必须用 `if-else` 链；
> 而"运算符选择"（`+ - * /`）这种"确定的值"才适合 `switch`。

---

## 七、⚠️ 浮点数用 `==` 比较（零警告，结果骗你）

**真实编译结果：零警告。**

**真实运行结果：**

```text
居然不相等！a = 0.30000000000000004441
```

| 项目 | 内容 |
| --- | --- |
| **原因** | `0.1`、`0.2`、`0.3` 在二进制里都存不精确，`0.1 + 0.2` 得到的是 `0.30000000000000004441`，**不等于** `0.3` |
| **为什么危险** | 程序会走进 `else` 分支，而且**编译器一句警告都没有** |
| **正确写法（容差比较）** | `差值 < 0.000001 && 差值 > -0.000001` |

```c
/* 浮点数"相等"的标准写法 */
double sum = 0.1 + 0.2;
double diff = sum - 0.3;
if (diff < 0.000001 && diff > -0.000001) {
    printf("sum 约等于 0.3\n");
} else {
    printf("sum 和 0.3 差别太大\n");
}
```

> 📌 第 2 课你问过 `%.2f` 为什么不四舍五入 —— 那是同一个根源：
> **二进制浮点数存不准十进制小数**。这次它换了个面孔出现在 `if` 里。
> **涉及金额就一律用整数（以"分"为单位）。**

---

## 八、⚠️ 悬挂 `else`（零警告，缩进骗人）

**真实编译结果：零警告。**

```c
if (a == 0)
    if (b == 0)
        printf("都在原点\n");
else
    printf("这句 else 属于谁？\n");      /* 缩进看着像属于外层，其实属于【内层】 */
```

| 项目 | 内容 |
| --- | --- |
| **C 的规则** | `else` **永远匹配离它最近的那个没有 else 的 `if`** |
| **后果** | 你以为的逻辑和实际执行的完全不同，而且**没有警告** |
| **怎么防** | **每一层都加花括号** —— 这条纪律能 100% 消除悬挂 else |

---

## 九、速查小结（建议打印）

| 你看到的 / 遇到的 | 原因 | 一句话修法 |
| --- | --- | --- |
| `-Wparentheses`（assignment as condition） | `if (x = 5)` | 改成 `==`；**别用双括号消警告** |
| `-Wempty-body` | `if (x > 0);` | 删掉那个分号 |
| `chained comparison ...` | `a < b < c` | 写 `a < b && b < c` |
| `statement requires expression of integer type` | 对 `double` 用 `switch` | `switch` 只能对整数 |
| `duplicate case value` | case 重复 | 合并或改名 |
| `expression is not an integer constant expression` | `case` 用了变量 | `case` 只能写常量 |
| **输出多了几行，零警告** | `switch` 忘记 `break` | 补 `break`，或注释标注"故意贯穿" |
| **该进的分支没进，零警告** | 浮点 `==`、悬挂 `else`、`else if` 顺序错 | 容差比较 / 加花括号 / 从高到低排 |

---

## 十、写完 `if` 之后的自检三问

1. **条件里是不是把 `==` 写成了 `=`？**（看编译器有没有 `-Wparentheses`）
2. **`if` 后面有没有多一个分号？**（`-Wempty-body` 会提醒你）
3. **每个 `switch` 的 `case` 后面，是不是都有 `break` 或"故意贯穿"的注释？**
