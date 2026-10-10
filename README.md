# C 语言零基础课程 · 学习工作区

> 本工作区用于「一课一练」式 C 语言学习：每课交付 **讲义 + 示例代码 + 作业**，
> 你完成作业后通知我批改，批改通过才进入下一课。

---

## 一、环境信息（已配好并自检通过）

| 项目 | 状态 |
| --- | --- |
| 操作系统 | macOS 27.0.1（Apple Silicon / arm64） |
| 编译器 | Apple clang 21.0.0（`/usr/bin/cc`、`/usr/bin/clang`） |
| 调试器 | LLDB（`/usr/bin/lldb`） |
| 代码补全引擎 | clangd（`/usr/bin/clangd`） |
| 编辑器 | Visual Studio Code + `code` 命令行 |
| 编译标准 | **C17**（`-std=c17`），警告全开 `-Wall -Wextra -Wpedantic` |

已确认可编译、可运行：

```
cc -std=c17 -Wall -Wextra -Wpedantic -g -O0 smoke.c -o smoke && ./smoke
```

---

## 二、目录结构

```
c-learning/
├── .vscode/                 # VSCode 配置（语法提示、编译任务、调试）
│   ├── settings.json
│   ├── tasks.json           # 5 个一键任务
│   ├── launch.json          # F5 调试配置
│   ├── c_cpp_properties.json
│   └── extensions.json
├── lessons/                 # 课程目录，每课一个文件夹
│   └── lesson01/
│       ├── lesson01-lecture.md      # 讲义
│       ├── lesson01-errors.md       # 常见报错速查
│       ├── examples/                # 示例代码（可以直接跑、随便改）
│       └── homework/                # 作业（在这里写你的答案）
│           ├── lesson01-homework.md   # 本课题目与要求
│           ├── taskN_*.c              # 你的作业代码
│           └── lesson01-questions.md  # ★ 我的疑问（和作业一起提交）
├── reports/                 # 批改报告 + 点评
├── build/                   # 编译产物（已加入 .gitignore）
└── .gitignore
```

**命名约定（每课都带课号前缀，这样文件名不会"重名"）**

| 内容 | 路径 | 说明 |
| --- | --- | --- |
| 讲义 | `lessons/lessonNN/lessonNN-lecture.md` | |
| 报错速查 | `lessons/lessonNN/lessonNN-errors.md` | |
| 示例代码 | `lessons/lessonNN/examples/NN_主题.c` | 已带 NN 前缀 |
| 作业题目 | `lessons/lessonNN/homework/lessonNN-homework.md` | |
| 作业代码 | `lessons/lessonNN/homework/taskN_题目.c` | 题目名各不相同 |
| 我的疑问 | `lessons/lessonNN/homework/lessonNN-questions.md` | |
| 批改报告 | `reports/lessonNN-review.md` | |

> **为什么每个文件都带 `lessonNN-` 前缀？**
> 因为它们分散在不同目录里，但 VSCode 标签页、搜索结果是按**文件名**显示的。
> 全都叫 `lecture.md` / `README.md` 时，你根本分不清哪个是第几课。
> 带上课号前缀，一眼就能认出来 —— 这是工程上的通行做法（也适用于你自己的项目）。

---

## 三、VSCode 怎么用（重点，先记这 3 个键）

> 用 VSCode 打开本文件夹：`File → Open Folder…` 选择 `c-learning`。
> 打开某个 `.c` 文件后，以下操作都是针对**当前打开的那个文件**。

| 操作 | 快捷键 / 入口 | 说明 |
| --- | --- | --- |
| **编译**当前文件 | `⌘ + ⇧ + B` | 用默认构建任务编译，错误会直接标在代码行上 |
| **编译并运行** | `⌘ + ⇧ + P` → `Tasks: Run Task` → **② 编译并运行当前文件** | 需要键盘输入的程序就用这个 |
| **调试**（打断点、单步） | `F5` | 会自动先编译，再启动调试 |
| 单步跳过 / 单步进入 / 继续 | `F10` / `F11` / `F5` | 调试时用 |
| 加断点 | 行号左侧点一下（红点） | 最有效的学习工具 |
| 所有任务 | `⌘ + ⇧ + P` → `Tasks: Run Task` | 见下方任务列表 |

**5 个一键任务**

1. `① 编译当前文件`（默认构建任务，`⌘⇧B`）
2. `② 编译并运行当前文件` —— 要输入数据时用这个
3. `③ 只运行当前文件（不重新编译）`
4. `④ 严格模式编译（当成考试批改）` —— 任何警告都当错误，作业自检用
5. `⑤ 清理 build 目录`

**编译产物去哪了？**
`build/<相对目录>/<文件名>`。例如编译 `lessons/lesson01/examples/01_hello.c`，
产物是 `build/lessons/lesson01/examples/01_hello`。

**想用终端手敲命令也行**（推荐逐步过渡到你自己的命令）：

```bash
cd /Users/wangjiaxun/Documents/deepseek-harness/learning-workspace/c-learning
cc -std=c17 -Wall -Wextra -Wpedantic -g lessons/lesson01/examples/01_hello.c -o build/hello
./build/hello
```

---

## 四、课程路线图

| 课次 | 主题 | 核心知识点 |
| --- | --- | --- |
| 01 | 认识 C 与第一个程序 | 编译流程、`main`、`printf`、注释、常见报错 |
| 02 | 变量与数据类型 | `int/double/char`、`scanf` 输入、`sizeof`、类型转换 |
| 03 | 运算符与表达式 | 算术/关系/逻辑/自增、优先级、整除与取余 |
| 04 | 分支结构 | `if / else if / else`、`switch`、三目运算符 |
| 05 | 循环结构 | `while / for / do-while`、`break / continue`、嵌套循环 |
| 06 | 函数 | 定义/声明/调用、参数传递、返回值、递归入门 |
| 07 | 数组 | 一维数组、遍历、最值/求和/查找/冒泡排序 |
| 08 | 字符串 | 字符数组、`string.h`、手写 `strlen/strcpy/strcmp` |
| 09 | 指针基础 | 地址与解引用、指针与数组、指针作函数参数 |
| 10 | 指针进阶与动态内存 | 二级指针、`malloc/free`、野指针与内存泄漏 |
| 11 | 结构体与枚举 | `struct`、`typedef`、结构体数组、结构体指针 |
| 12 | 文件操作 | `fopen/fclose`、`fprintf/fscanf`、文本与二进制 |
| 13 | 多文件工程 | 头文件、`#include`、编译链接、Makefile 入门 |
| 14 | 综合项目 | 例如「学生成绩管理系统」（结构体+文件+多文件） |

**选修课（约定在主线之后加讲）**

| 编号 | 主题 | 核心知识点 | 状态 |
| --- | --- | --- | --- |
| 选修 A | 位运算 | `& \| ^ ~ << >>`、判断奇偶、移位乘除 2、位掩码、二进制与十六进制 | 📌 已预约（第 3 课批改时由你提出，主线学完后开讲） |

> 路线图可协商调整：如果你有明确目标（考试、嵌入式、刷算法题…），告诉我，我会改。

---

## 五、学习流程约定

1. 我每轮**只讲一课**，交付：讲义（`lessonNN-lecture.md`）、示例代码（`examples/`）、作业（`lessonNN-homework.md`）、报错速查（`lessonNN-errors.md`）。
2. 交付后**我立即停止**，不会催你、不会轮询你的进度。
3. **学到不懂的地方**，随时写进 `homework/lessonNN-questions.md`（每课都有一份），和作业一起提交。
4. 你做完作业，直接说「**批改第 N 课**」即可。
5. 我批改后输出报告到 `reports/`，含 **得分 + 逐条点评 + 修改建议 + 你的疑问逐条解答**。
6. **达标**才进入下一课；未达标只针对薄弱点补练，不推进新内容。
7. 在你提交作业之前，我**不会**给出参考答案，也**不会**准备下一课。

**关于「我的疑问」文件（`lessonNN-questions.md`）**

- 位置：每课作业目录下，例如 `lessons/lesson01/homework/lesson01-questions.md`；
- 内容：不懂的概念、想不通的写法、对环境的困惑，甚至"我觉得这里很怪"都可以写；
- 写法：推荐「在哪里 + 我不懂的是 + 我自己猜过 + 想学到什么程度」四段式；
  写了"我自己猜过"，我能更准确地知道你卡在哪一步；
- 不止"看不懂"能写 —— "为什么非得这样""我这样写是不是很笨""能不能提前知道"同样欢迎；
- 我会在**批改报告之后**单独一节逐条回答，答完再等你决定是否进入下一课。

**其他约定**

- 本工作区由 Git 管理：我**不执行任何 git 命令**，也不碰 `.git/` 目录；
  版本管理（提交、分支等）由你自己操作，我只维护 `.gitignore`。
- 示例代码随便改、随便跑坏，那是学习的一部分。
- 作业必须是**你自己写的**；不会做可以卡住，卡住的地方正好是要讲的重点。

---

## 六、开始之前

第一课开始前，我会先问你几个问题（目标、基础、节奏、偏好），
以便把讲义深浅、练习题量和术语密度调到适合你的程度。
