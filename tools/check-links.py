#!/usr/bin/env python3
"""检查工作区内所有 md 文件的相对链接是否有效。

用法（在 c-learning 根目录下）：
    python3 tools/check-links.py

背景：写作业 README 时，我两次把 `[taskN.c](homework/taskN.c)` 写成非相对路径，
      但那个 md 本身就在 homework/ 目录里 —— 这个脚本用来兜住这类错误。
"""
import re
import sys
from pathlib import Path

root = Path(__file__).resolve().parent.parent
bad_total = 0

for path in sorted(root.rglob("*.md")):
    if ".git" in path.parts or "build" in path.parts:
        continue
    text = path.read_text(encoding="utf-8")
    for _, link in re.findall(r"\[([^\]]+)\]\(([^)#]+)\)", text):
        if link.startswith(("http://", "https://", "#")):
            continue
        if not (path.parent / link).resolve().exists():
            print(f"❌ {path.relative_to(root)} → {link}")
            bad_total += 1

if bad_total:
    print(f"\n共 {bad_total} 处失效链接")
    sys.exit(1)
print("✅ 全部链接有效")
