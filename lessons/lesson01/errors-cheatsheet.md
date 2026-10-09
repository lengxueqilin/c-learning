# 第 1 课 · 常见报错速查（真实原文对照）

> 本页所有报错信息都是**在你自己的电脑上实测截图般粘贴下来的**（Apple clang 21 / macOS arm64），
> 不是网上抄的，所以你看到的字**一模一样**。
>
> 用法：**先自己试着读报错，读不懂再来查这里。**

---

## 一、先学会"怎么读报错"——4 步法

看到一片红字就慌，是新手最大的时间浪费。按这 4 步走：

```
no_include.c:3:5: error: call to undeclared library function 'printf' ...
└─────┬────┘ └┬┘└┬┘ └──┬──┘ └──────────────┬───────────────────────┘
   ①哪个文件  ②行 ③列   ④严重程度        ⑤人话描述
```

| 步 | 看什么 | 你要做的 |
| --- | --- | --- |
| ① | **文件名** | 确认是不是你正在改的那个文件（改错文件是常见坑） |
| ② | **行号** | 直接跳过去。⚠️ 但真正的问题常常在**上一行**（比如漏分号） |
| ③ | 列号 | 大致位置，配合下面的 `^` 箭頭看它指到哪个字符 |
| ④ | `error` / `warning` | `error` 必须改，不改编译不过；`warning` 能跑但**必须改**（我们的标准） |
| ⑤ | 描述关键词 | 不用全懂，抓关键词就行：`expected ';'`、`undeclared`、`unterminated` |

**再看箭头和补充信息**：

- 报错下面那行带 `^` 的代码，就是编译器认为出问题的**那一个字符**；
- 有时还会跟一行 `note:`，那是**最有用的提示**，比如
  `note: did you mean 'printf'?` —— 编译器直接在告诉你正确答案。

**还有个铁律**：**只解决第一条 error。**
后面的报错常常是第一条引起的"连锁反应"。改一个、重编译一次，是正确节奏。

---

## 二、本课实测报错表

### ❶ 少写分号

**真实报错：**

```text
01_hello.c:21:38: error: expected ';' after expression
   21 |     printf("我忘记写分号了\n")
      |                               ^
      |                               ;
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "表达式后面我期望看到一个分号" |
| **原因** | 这一行结尾漏了 `;` |
| **怎么改** | 在 `)` 后面补上英文 `;`。注意编译器甚至贴心地用 `;` 在下面示意"应该放这儿" |
| **高频陷阱** | 分号是**英文** `;`，不是中文 `；`（见 ❸） |

---

### ❷ 双引号不配对

**真实报错：**

```text
01_hello.c:24:12: warning: missing terminating '"' character [-Winvalid-pp-token]
   24 |     printf("我的引号少了一个\n);
      |            ^
01_hello.c:24:12: error: expected expression
1 warning and 1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "字符串缺少结束的双引号" → "我期望一个表达式" |
| **原因** | 字符串**开了没关**，或关错了位置 |
| **怎么改** | 检查这一行：`"` 必须**成对**出现。数一数这一行的引号是不是偶数个 |
| **看箭头** | 箭头指在**开头的 `"`** 上 —— 因为编译器发现这个引号一直找不到伙伴 |

> 💡 引号不配对时，报错常常"跑偏"到很奇怪的位置（比如报在好几行之后）。
> 一旦看到 `unterminated` / `missing terminating`，**先回头数引号**。

---

### ❸ 用了中文全角分号

**真实报错：**

```text
01_hello.c:27:38: warning: treating Unicode character <U+FF1B> as an identifier character
                           rather than as ';' symbol [-Wunicode-homoglyph]
   27 |     printf("中文分号会报错\n")；
      |                               ^~
01_hello.c:27:38: error: expected ';' after expression
01_hello.c:27:38: error: use of undeclared identifier '；'
1 warning and 2 errors generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "这个 Unicode 字符（U+FF1B）我当成标识符了，它不是分号" → "期望分号" → "不认识的标识符 `；`" |
| **原因** | 用了**中文输入法**打出的全角符号 `；` `（）` `，` `“”` |
| **怎么改** | 切回英文输入法，重打这个符号 |
| **关键词** | 看到 `Unicode character`、`U+FF1B`、`identifier` 这几类字眼，**第一反应就是"中文标点"** |

> ⚠️ 这是中国学生**最高频**的报错，没有之一。
> **根治办法**：写代码时把输入法切换到英文，或者用 VSCode 插件高亮全角字符。
> 中文只出现在**双引号里面**（字符串内容）和**注释里面**，别的地方一律英文符号。

---

### ❹ 函数名大小写写错

**真实报错：**

```text
01_hello.c:30:5: error: call to undeclared function 'Printf';
                 ISO C99 and later do not support implicit function declarations
                 [-Wimplicit-function-declaration]
   30 |     Printf("C 语言区分大小写\n");
      |     ^
   30 |     ^
note: did you mean 'printf'?
/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/_printf.h:34:6: note: 'printf' declared here
   34 | int      printf(const char * __restrict, ...) __printflike(1, 2);
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "调用了一个我没听说过的函数 `Printf`" |
| **原因** | C 语言**区分大小写**，`Printf` ≠ `printf` |
| **怎么改** | 看 `note: did you mean 'printf'?` —— 编译器已经告诉你正确拼写了 |
| **关键词** | `undeclared function` / `implicit function declaration` |

---

### ❺ 变量名以数字开头

**真实报错：**

```text
01_hello.c:33:9: error: expected identifier or '('
   33 |     int 1stNumber = 0;
      |         ^
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "这里我期望一个名字或者左括号" |
| **原因** | 变量名**不能**以数字开头 |
| **怎么改** | 改成 `int firstNumber = 0;` 或 `int num1 = 0;`（数字可以出现在**中间或末尾**） |
| **命名规则预告** | 只能用**字母、数字、下划线**；不能以数字开头；不能用关键字（如 `int`）；区分大小写 |

---

### ❻ 定义了变量却没用（警告，能编译）

**真实输出：**

```text
01_hello.c:36:9: warning: unused variable 'unused' [-Wunused-variable]
   36 |     int unused = 5;
      |         ^~~~~~
1 warning generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "你定义了这个变量，但从来没使用过" |
| **为什么必须管** | 编译能过、程序能跑，**但这几乎总是"我本来想用它却忘了"的征兆**，是 bug 的温床 |
| **怎么改** | 要么真的用上它，要么删掉它。**本课作业的标准：0 警告** |

---

### ❼ 忘了 `#include <stdio.h>`

**真实报错：**

```text
no_include.c:3:5: error: call to undeclared library function 'printf' with type
                 'int (const char *, ...)'; ISO C99 and later do not support
                 implicit function declarations [-Wimplicit-function-declaration]
    3 |     printf("忘了 #include\n");
      |     ^
no_include.c:3:5: note: include the header <stdio.h> or explicitly provide a declaration for 'printf'
1 error generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "我不认识 `printf` 这个函数" |
| **原因** | 缺 `#include <stdio.h>`（`printf` 住在 `stdio.h` 里） |
| **怎么改** | 文件最上面加 `#include <stdio.h>`，**结尾不加分号** |
| **关键词** | `undeclared library function` + `note: include the header <stdio.h>` |

---

### ❽ 没有 `main` 函数（链接阶段报错）

**真实报错：**

```text
Undefined symbols for architecture arm64:
  "_main", referenced from:
      <initial-undefines>
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "找不到 `_main` 这个符号"（`ld` = 链接器） |
| **原因** | 文件里没有 `main` 函数，或者把它拼错了（`Main` / `mian`） |
| **怎么改** | 补上 `int main(void) { ... }` |
| **关键词** | `Undefined symbols`、`ld: symbol(s) not found`、`linker command failed` |
| **重要认知** | 报错里出现 `ld` 或 `linker`，说明你的**语法是通的**，问题在"拼装"阶段 —— 通常是缺 `main`、函数名拼错、或者多文件工程里少链接了 `.o`（第 13 课会讲） |

---

### ❾ 用了中文引号 `“ ”`

**真实报错：**

```text
cn_quote.c:4:12: error: unexpected character <U+201C>
    4 |     printf(“中文引号会报错\n”);
      |            ^
cn_quote.c:4:15: error: use of undeclared identifier '中文引号会报错'
    4 |     printf(“中文引号会报错\n”);
      |             ^~~~~~~~~~~~~~
cn_quote.c:4:38: error: character <U+201D> not allowed in an identifier
    4 |     printf(“中文引号会报错\n”);
      |                             ^
3 errors generated.
```

| 项目 | 内容 |
| --- | --- |
| **人话** | "出现了一个我没见过的字符 U+201C"（那正是中文左引号 `“`） |
| **怎么改** | 换成英文 `"` |
| **关键词** | `unexpected character <U+201C>` / `<U+201D>` |

---

### ❿ 文件名写错 / 文件不存在

**真实报错：**

```text
clang: error: no such file or directory: 'hello_world.c'
clang: error: no input files
```

| 项目 | 内容 |
| --- | --- |
| **原因** | 命令里的文件名或路径写错了，或者你现在不在项目根目录 |
| **怎么改** | 用 `pwd` 看当前目录、用 `ls` 看目录里到底有什么文件；注意**大小写**（macOS 默认不区分大小写，但习惯上要写对，Linux 上区分） |

---

## 三、三条"报错心法"

1. **只改第一条 error，然后重新编译。** 后面的大多是连带的假报错。
2. **`note:` 是宝藏。** `did you mean 'printf'?`、`include the header <stdio.h>`
   这类提示，比你自己猜快 10 倍。
3. **报错信息里的英文不用全会读**，抓三个关键词就够定位：
   `expected`（我期望…但没看到）、`undeclared`（我不认识）、`unterminated`（没结束）。

---

## 四、还没遇到但你会遇到的（先认识一下名字）

| 名字 | 什么时候出现 | 大概意思 |
| --- | --- | --- |
| `segmentation fault`（段错误，退出码 139） | 学了指针之后 | 程序访问了不属于它的内存 |
| `warning: variable set but not used` | 第 2–3 课 | 赋值了但从没读取 |
| `warning: format specifies type 'int' but the argument has type 'double'` | 第 2 课 | `printf` 的格式符和变量类型对不上 |
| `error: 'x' undeclared` | 第 2 课 | 用了没定义的变量名（常是拼写错误） |

> 这些**现在不用管**，等真遇到了再回来看。**遇到报错 → 查表 → 改对 → 记住**，这个循环走三遍，你就比大多数人强了。
