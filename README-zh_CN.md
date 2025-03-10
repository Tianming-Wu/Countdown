[English](README.md) | 中文

# Countdown
![GitHub Release](https://img.shields.io/github/v/release/Tianming-Wu/Countdown)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Tianming-Wu/Countdown/main.yml)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/Tianming-Wu/Countdown)

[最新版本](https://github.com/Tianming-Wu/Countdown/releases/latest)

![Running on Ubuntu](https://github.com/user-attachments/assets/dafc5caf-3cbd-4c77-a459-6f04da13829c)


Countdown 提供一个到特定日期的倒计时牌。

默认日期是 2025.6.7，中国2025高考。

# 特性
- 可调的标题，日期和视觉效果。
- 半夜12点（当前时区）自动更新。

# 配置
点击右下角的‘天’字来折叠或展开设置面板。

在这里你可以设置要倒计时的日期，以及窗口是否透明（需要重启）。

其他的选项需要在 `consistent.ini`中编辑。
你可以在第一次启动程序之后，在程序所在目录中找到它。

## 配置文件
默认配置文件如下：
```ini
[app]
Animation=true
TargetDate=2025-06-07
TargetString=距离高考还剩：
Timer=true
Translucent=true

[widget]
Stylesheet=".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }"
```
- `[app]` 这些配置是程序行为。
  - `Animation`*(string)*: 启用窗口动画效果。   
  - `TargetDate`*(string)*: 目标日期。格式为`yyyy-mm-dd`。
  - `TargetString`*(string)*: 倒计时牌的标题。
  - `Timer`*(bool)*: 启用12点更新。在如学校电脑等过夜必定关机的电脑上可以启用以省一点点电。（对性能影响非常小）
  - `Translucent`*(bool)*: 窗口背景透明。
- `[widget]` 这些配置是窗口视觉属性。
  - `Stylesheet`*(string)*: 这是窗口的样式表。见[样式](#样式)

## 样式
配置中的默认样式表：
```ini
[widget]
Stylesheet=".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }"
```
文件格式为qss。可以查看 [Qt Online Help Document (EN)](https://doc.qt.io/qt-6/stylesheet.html), [csdn(1)](https://blog.csdn.net/zwcslj/article/details/140154933) 或 [csdn(2)](https://blog.csdn.net/martian665/article/details/142520397) 。

基础部件名为 `centralwidget`。 **注意**几乎所有部件都是QWidget的子类，所以你应该用`.QWidget` 而不是 `QWidget` 选择器，如果你不想在所有部件上都应用它。你可以在ui文件中找到各部件名称。如果你想要更好的交互式查看，试试qtcreator或者designer。

如果你想自定义但是不想学qss，将以下提示词和你的要求一起给AI：

```
帮我写一个qss文件，要求包含在一行以内。
程序是一个Qt倒计时牌，背景 QWidget centralwidget, 标题 QLabel labelName, 内容为 QLabel label_Day, 主窗口背景可以透明。
示例文件: ".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }" 
我的要求是……
```


# UI 行为
Countdown 定位于主显示器屏幕**右上角**，边距**15px**。

程序有缩放适配（感谢强大好用的[qt](https://qt.io)）。

程序的几何属性(geometry)（坐标和尺寸）暂时不可调整。

你不可以移动，缩放，最小化/最大化或关闭窗口。

程序会创建一个托盘图标，包含一个"Config"菜单用于定位到你的配置文件（仅Windows系统）和"Quit"用于退出。


# 已知问题
- (Ubuntu) 任务栏窗口图标无法隐藏。
- (Windows) 配置文件链接暂时失效。
