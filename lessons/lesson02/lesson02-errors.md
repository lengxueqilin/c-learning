# 第 2 课 · 常见报错速查（真实原文对照）

> 本页所有报错信息都是**在你自己的电脑上实测粘贴下来的**（Apple clang 21 / macOS arm64），
> 所以你看到的字**一模一样**。
>
> 第 2 课开始，报错的"性格"变了：第 1 课主要是**语法错**（缺分号、引号不配对），
> 第 2 课出现了大量**"能编译、但有警告、结果却是错的"**情况 —— 这类才是真正危险的。

---

## 一、本课报错的三个关键词（先记住它们）

| 关键词 | 出现在哪 | 意味着 |
| --- | --- | --- |
| `-Wformat` | 编译警告 | **格式符和变量类型对不上** —— 本课最高频 |
| `-Wuninitialized` | 编译警告 | **变量没初始化就用了** |
| `Segmentation fault: 11` | 运行时崩溃 | 常见元凶：**`scanf` 忘了 `&`** |

> 还有一类**编译器完全不管**的错误：**整数除法**。它不报错、不警告，就是默默算错
> —— 见本页第七节。**这类错误只能靠你自己懂原理来避免。**

---

## 二、`scanf` 忘记写 `&` ⚠️ 会崩溃

**真实编译警告：**

```text
p1.c:2:65: warning: format specifies type 'int *' but the argument has type 'int' [-Wformat]
    2 | int main(void) { int n = 0; printf("请输入："); scanf("%d", n); printf("n=%d\n", n); return 0; }
      |                                                        ~~   ^
1 warning generated.
```

**真实运行结果：**

```text
Segmentation fault: 11
[退出码 139]
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "`%d` 要求的是一个 `int *`（整数的**地址**），你给了我一个 `int`（整数的**值**）" |
| **原因** | `scanf` 需要知道"数据放到哪里去"，所以要给它**地址**（`&n`），不是值（`n`） |
| **怎么改** | `scanf("%d", &n);` —— 变量前面补 `&` |
| **为什么危险** | 编译只是**警告**（不加 `-Werror` 就能过），运行起来直接**段错误崩溃**（退出码 139） |
| **记忆法** | `printf` 是**拿值**给人看（不需要 `&`）；`scanf` 是**按地址**送数据进去（必须要 `&`） |

> 💡 **一句话解释 `&`**：`&n` 读作"n 的地址"。
> 你可以先把它当成一张"**地址贴纸**"——告诉 `scanf` 数据该往哪个盒子送。
> 它背后的原理（指针）第 9 课专门讲，现在只要记住"**scanf 的变量前面必须有 &**"就够了。

---

## 三、`printf` 的格式符和类型对不上（`-Wformat`）

### 3.1 用 `%d` 打印 `double`

**真实警告：**

```text
p2.c:2:53: warning: format specifies type 'int' but the argument has type 'double' [-Wformat]
    2 | int main(void) { double price = 9.9; printf("%d\n", price); return 0; }
      |                                              ~~     ^~~~~
      |                                              %f
1 warning generated.
```

**怎么改**：看编译器给的提示 —— 它直接在下面标了 `%f`，把 `%d` 改成 `%f`（或 `%.2f`）。

### 3.2 用 `%f` 打印 `int`

**真实警告：**

```text
p3.c:2:44: warning: format specifies type 'double' but the argument has type 'int' [-Wformat]
    2 | int main(void) { int n = 7; printf("%f\n", n); return 0; }
      |                                     ~~     ^
      |                                     %d
1 warning generated.
```

**怎么改**：按提示把 `%f` 改成 `%d`。

### 3.3 第 2 课最容易被忽略的一条：`scanf` 读 `double` 要用 `%lf`

**真实警告：**

```text
s1.c:2:73: warning: format specifies type 'float *' but the argument has type 'double *' [-Wformat]
    2 | ... scanf("%f", &d); ...
      |              ~~   ^~
      |              %lf
1 warning generated.
```

**真实运行结果（更可怕的地方）：**

```text
输入小数：d=0.000000      ← 你输入了 3.14，但 d 完全没被写进去！
```

| 项目 | 内容 |
| --- | --- |
| **原因** | `%f` 对应的是 `float`（4 字节），而 `double` 是 8 字节，长度不匹配 → 读不进去 |
| **怎么改** | `scanf("%lf", &d);` （`l` 表示 long，这里指"双精度"） |
| **关键区别** | **`printf` 里 `%f` 就能打 `double`；`scanf` 里读 `double` 必须写 `%lf`** |
| **记忆法** | "输出随便，输入严格" —— `scanf` 对类型长度的要求比 `printf` 严格得多 |

### 格式符对照表（本课核心，建议抄一遍）

| 类型 | `printf` 输出用 | `scanf` 输入用 | 备注 |
| --- | --- | --- | --- |
| `int` | `%d` | `%d` | 最常用 |
| `double` | `%f`（或 `%.2f`） | **`%lf`** | ⚠️ 输入输出不一样！ |
| `float` | `%f` | `%f` | 字面量要加 `f` |
| `char` | `%c` | `%c` | 单引号 |
| `char` 当整数看 | `%d` | — | 能打印出 ASCII 编码 |
| 字符串（一段文字） | `%s` | `%s` | 第 8 课细讲 |
| `sizeof` 的结果 | `%zu` | — | `size_t` 类型专用 |

---

## 四、变量没初始化就使用（`-Wuninitialized`）

**真实警告：**

```text
p4.c:2:46: warning: variable 'garbage' is uninitialized when used here [-Wuninitialized]
    2 | int main(void) { int garbage; printf("%d\n", garbage); return 0; }
      |                                              ^~~~~~~
p4.c:2:29: note: initialize the variable 'garbage' to silence this warning
    2 | int main(void) { int garbage; printf("%d\n", garbage); return 0; }
      |                             ^
      |                              = 0
1 warning generated.
```

**真实运行结果：**

```text
-75431720          ← 每次运行可能都不一样，这叫"垃圾值"
[退出码 0]         ← 程序"成功"结束了，但结果毫无意义
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "变量 `garbage` 在被使用前没有初始化" + `note` 直接告诉你怎么改 |
| **原因** | 声明变量只是"申请了一块内存"，**并没有清空它**，里面是这块地上一任留下的数据 |
| **怎么改** | 声明时就给初值：`int garbage = 0;` |
| **要养成的习惯** | **所有的变量，声明时就给初值。** 尤其是要交给 `scanf` 的变量 |
| **为什么危险** | 退出码是 0（看起来一切正常），值却是随机的 —— 这类 bug 最难查 |

---

## 五、`char` 用了双引号

**真实报错（这是 error，不是警告，编译直接失败）：**

```text
p5.c:2:23: error: incompatible pointer to integer conversion initializing 'char' with an expression of type 'char[2]' [-Wint-conversion]
    2 | int main(void) { char bad = "A"; printf("%c\n", bad); return 0; }
      |                       ^     ~~~
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "把一个 `char[2]`（两个字符的数组）塞进一个 `char` 里，类型不兼容" |
| **原因** | `'A'` 是**一个字符**；`"A"` 是**一段字符串**（本质是字符数组，末尾还藏着一个结束符，所以长度是 2） |
| **怎么改** | 单引号 `'A'` |
| **⚠️ 特别提醒** | 这也是**中文标点检查**的一部分：中文引号 `‘’` 和英文单引号 `'` 长得像但完全不同，VSCode 里可能一眼看不出 |

---

## 六、把小数塞进 `int`（`-Wliteral-conversion`）

**真实警告：**

```text
p6.c:2:30: warning: implicit conversion from 'double' to 'int' changes value from 3.9 to 3 [-Wliteral-conversion]
    2 | int main(void) { int wrong = 3.9; printf("%d\n", wrong); return 0; }
      |                      ~~~~~   ^~~
1 warning generated.
```

**真实运行结果：**

```text
3                  ← 不是 4！是"直接砍掉"，不是四舍五入
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "从 double 到 int 的隐式转换把 3.9 变成了 3" |
| **怎么改** | 想存小数就用 `double`；真要取整，想清楚是"砍掉"还是"四舍五入" |
| **记住** | **C 的类型转换默认是"砍掉小数"，不是四舍五入** |

---

## 七、⚠️ 编译器完全不管的错误：整数除法

这一类**必须靠你自己懂**，因为编译器一句话都不会说：

```text
★ 错误示范（编译 0 错误 0 警告，结果却是错的）

     7 / 2   = 3        你以为 3.5，其实小数被直接砍掉了
```

**真实运行输出（本课示例 05 实测）：**

```text
陷阱验证：
  7 / 2     = 3      ← 整数运算，小数被砍掉
  7 / 2.0   = 3.50    ← 有一个是小数，结果就是小数
  7.0 / 2   = 3.50    ← 反过来也一样
```

| 项目 | 内容 |
| --- | --- |
| **规则** | **整数 ÷ 整数 = 整数**（小数部分直接砍掉，不四舍五入） |
| **怎么改** | 让参与运算的至少一边是小数：`sum / 3.0`、`7.0 / 2` |
| **最容易上当的地方** | 求平均分、求百分比、求比例 |
| **为什么危险** | 0 错误 0 警告，程序跑得好好的，**答案就是错的** |

> 🎯 **本课最重要的一句话**：
> **"编译通过"和"结果正确"是两件完全不同的事。**
> 第 1 课你在学第一件，第 2 课开始，你要开始在意第二件。

---

## 八、报错速查小结（打印出来贴桌边）

| 你看到的 | 90% 的原因是 | 一句话修法 |
| --- | --- | --- |
| `-Wformat` + `int *` / `int` | `scanf` 少了 `&` | 变量前加 `&` |
| `-Wformat` + type 不匹配 | `%d` / `%f` / `%c` 用错了 | 看编译器下面的提示，它直接给了正确格式符 |
| `Segmentation fault: 11` | 十有八九是 `scanf` 忘了 `&` | 检查所有 `scanf` |
| `-Wuninitialized` | 变量没给初值 | `int x = 0;` |
| `-Wint-conversion` | `char` 用了双引号 | 换单引号 |
| `-Wliteral-conversion` | 把小数塞进了 `int` | 用 `double` 接住它 |
| **什么都不报，但答案是错的** | **整数除法** | 把除数写成 `3.0` |
