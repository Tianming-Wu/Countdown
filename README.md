# Countdown
![GitHub Release](https://img.shields.io/github/v/release/Tianming-Wu/Countdown)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Tianming-Wu/Countdown/main.yml)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/Tianming-Wu/Countdown)

[Latest Release](https://github.com/Tianming-Wu/Countdown/releases/latest)

![Ubuntu](https://github.com/user-attachments/assets/dafc5caf-3cbd-4c77-a459-6f04da13829c)


Countdown provides a window on your desktop, counting for a specific date.

By default, it counts to 2025.6.7, the University entrance exam in China.

# UI Behaviors
Countdown hovers **15 pixels** from the **top right corner** of your primary display.

It automatically adapts to your scaling (Thanks to the powerful [qt](https://qt.io)).

The geometry (position and size) is currently NOT adjustable.

You cannot move, resize, minimize/maximize or close the window.

The program creates a tray icon, which contains a "config" to your config file (Windows only) and "Quit".

# Configuration
Click on the '天' character on the bottom right to expand or fold settings panel.

Here you can set the date to count to and whether the window is Translucent (or, transparent) (Requires restart).

Other options can only be edited from `consistent.ini`.
You can find it in the program directory after launching it for the very first time.

## Style
The default stylesheet in config:
```ini
[widget]
Stylesheet=".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }"
```
The format is acturally qss. Check [Qt Online Help Document (EN)](https://doc.qt.io/qt-6/stylesheet.html), [csdn(1)](https://blog.csdn.net/zwcslj/article/details/140154933) or [csdn(2)](https://blog.csdn.net/martian665/article/details/142520397) for more details.

The base widget's name is `centralwidget`. **Note** that almost all components are children of QWidget, so you should use `.QWidget` instead of `QWidget` if you don't want to adapt it to everything. Check for names in ui file. For a more friendly interaction, try qtcreator or designer.

If you want to customize it without learning qss, give this to AI with your requirements.:
`帮我写一个qss文件，要求包含在一行以内。程序是一个Qt倒计时牌，背景 QWidget centralwidget, 标题 QLabel labelName, 内容为 QLabel label_Day, 主窗口背景透明。示例文件为 ".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }" 我的要求是……`


# Known issues
- (Ubuntu) Cannot hide its icon in the task bar.
