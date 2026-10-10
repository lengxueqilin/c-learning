# 第 6 课 · 常见报错速查（真实原文对照）

> 所有报错信息都是**在你自己的电脑上实测粘贴下来的**（Apple clang 21 / macOS arm64）。
>
> **第 6 课的特点**：编译器在"函数"这件事上**帮得比较多**（参数个数、返回类型、重定义全能抓），
> 但**最核心的那个坑（值传递）它一个字都不说** —— 见第七节。

---

## 一、本课关键词总览

| 关键词 | 出现在哪 | 严重程度 | 意味着 |
| --- | --- | --- | --- |
| `call to undeclared function` | 编译 error | 低 | 函数定义在调用点之后，而且**没写原型** |
| `too few / too many arguments` | 编译 error | 低 | 参数**个数**不对 |
| `void function should not return a value` | 编译 error | 低 | `void` 函数里写了 `return 值;` |
| `non-void function does not return a value` | 编译 warning | 中 | 声明要返回 `int`，但函数**没写 `return`** |
| `redefinition of 'xxx'` | 编译 error | 低 | 同一个函数写了两遍 |
| `declaration shadows ...` | 编译 warning（要开 `-Wshadow`） | 中 | 内层变量和外层**同名** |
| `all paths ... will call itself` | 编译 warning | **高** | 递归**没有基准情形** |
| **值传递 / 忘记接返回值 / 函数内整数除法** | **无任何提示** | **最高** | 结果悄悄不对 |

---

## 二、函数定义在调用点之后，又忘了写原型（编译 error）

**真实报错：**

```text
f1.c:2:33: error: call to undeclared function 'lateFun'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
    2 | int main(void) { printf("%d\n", lateFun(3)); return 0; }
      |                                 ^
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "调用了一个我没听说过的函数 `lateFun`；C99 起不支持隐式函数声明" |
| **原因** | 编译器从上往下读，读到 `main` 里的调用时，还没见过 `lateFun` 的定义 |
| **怎么改** | 在 `main` **之前**写一行函数原型：`int lateFun(int n);` |
| **为什么要这样设计** | 编译器必须知道"要传几个参数、返回什么类型"才能检查调用是否正确。原型就提供这些信息 |

**⚠️ 一个特别值得警惕的连锁反应（我实测过）**

如果你**整段代码都没写原型**，错误会**爆炸式增长**。我实测一个"5 个函数全在 main 之后、且都没有原型"的文件，
clang 报了 **9 个 error**，其中一半是这种：

```text
error: conflicting types for 'printAndReturn'
error: conflicting types for 'tryDouble'
error: conflicting types for 'average'
```

**为什么？** 因为 C99 之前的隐式声明会**默认假设函数返回 `int`**。
于是编译器先按 `int printAndReturn(...)` 记下来，后来又看到真正的定义是 `void printAndReturn(...)`
—— 前后矛盾，于是报"类型冲突"。

**教训**：
1. **只改第一条 error，然后重新编译**（第 1 课就说过，这里是最典型的例子）；
2. 看到一堆 `conflicting types`，先回头检查**是不是忘了写原型**。

---

## 三、参数个数不对（编译 error）

**真实报错（少了参数）：**

```text
f3a.c:3:38: error: too few arguments to function call, expected 2, have 1
    3 | int main(void) { printf("%d\n", add(3)); return 0; }
      |                                 ~~~  ^
f3a.c:2:5: note: 'add' declared here
    2 | int add(int a, int b) { return a + b; }
      |     ^   ~~~~~~~~~~~~
1 error generated.
```

**真实报错（多了参数）：**

```text
f3b.c:3:43: error: too many arguments to function call, expected 2, have 3
    3 | int main(void) { printf("%d\n", add(3, 4, 5)); return 0; }
      |                                 ~~~       ^
f3b.c:2:5: note: 'add' declared here
    2 | int add(int a, int b) { return a + b; }
      |     ^   ~~~~~~~~~~~~
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "参数太少了/太多了：期望 2 个，实际给了 1/3 个" |
| **好消息** | 这是**函数带来的最大好处之一** —— 编译器能替你检查参数个数了 |
| **`note` 很有用** | 它会告诉你"我在哪里声明的"，直接跳过去看签名 |
| **顺带一提** | 参数**类型**不匹配（如给 `int` 传 `double`）通常只是警告或静默转换，不如个数错误这么严格 |

---

## 四、`return` 相关的三个错误/警告

### 4.1 `void` 函数却返回一个值（编译 error）

**真实报错：**

```text
f9.c:2:18: error: void function 'say' should not return a value [-Wreturn-mismatch]
    2 | void say(void) { return 5; }
      |                  ^      ~
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "`void` 函数不应该返回值" |
| **怎么改** | 要么把返回类型改成 `int`，要么把 `return 5;` 改成 `return;`（或直接删掉） |
| **记法** | `void` = "没有值"。既然没值，就别 return 值 |

### 4.2 声明了返回类型，却忘了写 `return`（编译 warning）

**真实警告：**

```text
f2.c:2:25: warning: unused variable 'r' [-Wunused-variable]
    2 | int addOne(int n) { int r = n + 1; }
      |                         ^
f2.c:2:36: warning: non-void function does not return a value [-Wreturn-type]
    2 | int addOne(int n) { int r = n + 1; }
      |                                    ^
2 warnings generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "这个函数声明要返回 `int`，但它没有返回任何值" |
| **后果** | 调用者拿到的返回值是**不确定的垃圾值**（第 2 课见过这个概念） |
| **怎么改** | 补上 `return r;` |
| **注意** | 通常会有**两个**警告一起出现（还有一个"变量算了没用"），它们指向同一个问题 |

### 4.3 ⚠️ `error` 会挡住 `-Wreturn-type` 警告（实测）

**这是第 2 课学过的现象，在函数这一课又出现了一次。**

我实测过：一个文件里同时有"参数个数 error"和"忘记 return"，
**第一次编译只会看到 error + `unused variable` 警告，
那个 `non-void function does not return a value` 警告不会出现**；
等你把 error 修完、重新编译，它才冒出来。

```text
--- 第一次编译 ---
error: too few arguments to function call, expected 2, have 1
error: void function 'printAndReturn' should not return a value
warning: unused variable 'result'          ← 只有这一个警告

--- 把两个 error 修掉后再编译 ---
warning: unused variable 'result'
warning: non-void function does not return a value   ← 它现在才出现！
```

**所以那条纪律要再说一遍：改一点、编译一次。**
指望一次编译看全所有问题，是不可能的。

---

## 五、函数重定义（编译 error）

**真实报错：**

```text
f5.c:3:5: error: redefinition of 'twice'
    3 | int twice(int n) { return n + n; }
      |     ^
f5.c:2:5: note: previous definition is here
    2 | int twice(int n) { return n * 2; }
      |     ^
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "`twice` 被重复定义了" + note 指出上一次定义在哪 |
| **原因** | 同一个名字的**函数体**写了两遍（注意：**声明**可以写多遍，**定义**只能一次） |
| **怎么改** | 删掉一个；如果两个都想保留，改名字（如 `twice` 和 `doubleIt`） |
| **常见场景** | 复制粘贴函数时忘了改名字；或者把同一个函数从别处粘了两遍 |

---

## 六、遮蔽（shadow）：内层变量和外层同名

**真实报错（要开 `-Wshadow` 才会出现，我们的标准是开着的）：**

```text
03_scope.c:69:13: error: declaration shadows a local variable [-Werror,-Wshadow]
   69 |         int x = 2;                  /* 这是另一个 x */
      |             ^
03_scope.c:66:9: note: previous declaration is here
   66 |     int x = 1;
       |         ^
1 error generated.
```

```text
03_scope.c:35:21: error: declaration shadows a variable in the global scope [-Werror,-Wshadow]
   35 | void shadowDemo(int sharedValue)
      |                     ^
03_scope.c:19:5: note: previous declaration is here
   19 | int sharedValue = 100;
      |     ^
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "这个声明遮蔽（shadow）了外层的变量" |
| **为什么危险** | 内外两个同名变量是"我改的到底是哪个"搞混的头号原因，而且**找 bug 极难** |
| **怎么改** | 换个名字。**我们的纪律：同一个作用域链上不许出现同名变量** |
| **注意** | `-Wshadow` **不在** `-Wall -Wextra` 里，需要显式打开。我们的「④ 严格模式编译」任务里没有它，但我在批改时会用它 |

---

## 七、⚠️ 值传递：编译器**一个字都不说**（本课最重要）

```c
void tryToDouble(int n)
{
    n = n * 2;              /* 改的是【副本】 */
}

int main(void)
{
    int v = 21;
    tryToDouble(v);
    printf("v = %d\n", v);   /* 输出 21，不是 42 —— 而且零警告！ */
}
```

**真实实验结果：**

```text
调用前：v = 21
  函数里：n = 42（看着变了）
调用后：v = 21   <- 完全没变！这就是值传递
```

| 项目 | 内容 |
| --- | --- |
| **人话** | —— 编译器**什么都不说**，因为这段代码语法完全正确 |
| **原因** | C 的函数传参永远是**值传递**：函数拿到的是实参的**一份拷贝** |
| **后果** | 你以为函数改了外面的变量，其实只改了副本 |
| **怎么改（两条路）** | ① **接收返回值**：`v = doubleIt(v);`（本课的做法）<br>② **传地址**：用指针（第 9 课） |
| **为什么值传递要这样设计** | ① 简单、安全（函数不可能偷偷改你的变量）；② 效率（拷贝小数据很快） |
| **什么时候情况不同** | **数组**是个例外（第 7 课讲）—— 传数组时函数能改到原数组 |

> 🎯 **这一节的含金量**：它是**第 9 课指针的全部动机**。
> 你现在应该已经能自己回答："既然函数改不了外面的变量，那我想让它改怎么办？"
> —— 答案就是"把地址传进去"。

---

## 八、⚠️ 另外三个零警告陷阱

### 8.1 调用函数却忘了接收返回值

```c
int doubleIt(int n) { return n * 2; }

int v = 21;
doubleIt(v);                 /* ❌ 算了但结果被扔掉 */
printf("v = %d\n", v);       /* 还是 21 */

v = doubleIt(v);             /* ✅ 必须"接回来" */
```

**为什么零警告**：C 允许"丢弃返回值"（很多函数确实不需要返回值，比如 `printf`）。
编译器无法判断你是"故意不要"还是"忘了要"。

### 8.2 函数内部的整数除法（第 3 课的坑换了个地方）

```c
double average(int sum, int count)
{
    return sum / count;              /* ❌ 整数除法，小数被砍掉 */
    /* return (double)sum / count;   ✅ */
}
```

**实测后果**：`average(176, 5)` 会返回 `35.00` 而不是 `35.20`。
**坑在函数里反而更隐蔽** —— 调用者看到参数是 `int`，很容易忘了函数内部也要转换。

### 8.3 返回值写错变量（复制粘贴事故）

```c
int maxOf(int a, int b)
{
    if (a > b) { return a; }
    return a;                        /* ❌ 复制粘贴忘了改，应该是 b */
}
```

**实测后果**：`maxOf(3, 9)` 返回 3。
**零警告**，而且代码"看起来"完全正常 —— 这类 bug 只能靠**测试用例**发现
（这也是为什么每道题我都给你基准表）。

---

## 九、递归的两个问题

### 9.1 递归没有基准情形（clang 竟然会警告！）

**真实警告 + 真实运行结果：**

```text
f6.c:2:18: warning: all paths through this function will call itself [-Winfinite-recursion]
    2 | void boom(int n) { boom(n + 1); }
      |                  ^
1 warning generated.
```

```text
运行结果：退出码 = -11（即 139，Segmentation fault: 11）
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "这个函数的所有路径都会调用它自己" |
| **警告 = 无限递归** | clang 能识别这种**字面上**的无限递归，并给出警告 |
| **运行时** | 每次调用都会占用一块"栈空间"，调用无限次 → **栈被撑爆** → 段错误 |
| **怎么改** | 补上基准情形：`if (n <= 1) { return 1; }` 之类 |
| **注意** | 只有**最明显**的那种（函数体里必定递归）才会被警告。稍微绕一下（如 `if (n>0) f(n+1);`）就不报警告了 |

### 9.2 递归太深（合法但会崩）

```c
int sum(int n) { return n == 0 ? 0 : n + sum(n - 1); }
sum(1000000);        /* 基准情形有，但递归一百万层 → 栈溢出 */
```

**这类问题 clang 不会警告**（因为它"看起来"完全正确）。
现实中的做法：**层数可能很深的递归，改用循环**。

---

## 十、速查小结（建议打印）

| 你看到的 / 遇到的 | 原因 | 一句话修法 |
| --- | --- | --- |
| `call to undeclared function` | 定义在调用点之后，且没原型 | 在 `main` 前加一行原型 |
| 一堆 `conflicting types` | 忘了原型，C99 隐式声明假设返回 `int` | 先补原型，再重新编译 |
| `too few/too many arguments` | 参数个数不对 | 看 `note` 里的签名，补齐/删掉 |
| `void function should not return a value` | `void` 里写了 `return 值` | 改返回类型，或写成 `return;` |
| `non-void function does not return a value` | 忘了 `return` | 补上；注意它可能被 error 挡住 |
| `redefinition of 'xxx'` | 函数体写了两遍 | 删掉一个或改名 |
| `declaration shadows ...` | 内外层变量同名 | 换个名字 |
| `all paths ... will call itself` | 递归没有基准情形 | 补基准情形；否则运行时段错误 |
| **函数改不了外面的变量，零警告** | **值传递** | 接收返回值；或第 9 课用指针 |
| **调用后外面没变，零警告** | **忘了接返回值** | `v = f(v);` |
| **平均分少了小数，零警告** | **函数内整数除法** | `(double)sum / count` |
| **最大值算错，零警告** | 返回值写错变量 | 用测试用例覆盖 |

---

## 十一、写完函数之后的自检五问

1. **函数定义在调用点之后吗？那原型写了吗？**
2. **声明了返回类型（不是 void），函数里每条路径都有 `return` 吗？**
3. **参数个数和类型对得上吗？**（编译器会帮你查，别忽略警告）
4. **我是不是以为函数改了外面的变量？**（值传递！想改就得用返回值或指针）
5. **函数内部有没有"整数除法""返回值写错变量"这类零警告陷阱？**
   （对付这类问题的唯一办法：**写几个测试用例跑一遍**）
