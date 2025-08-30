English | [中文](README-zh_CN.md)

# Countdown
![GitHub Release](https://img.shields.io/github/v/release/Tianming-Wu/Countdown)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Tianming-Wu/Countdown/main.yml)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/Tianming-Wu/Countdown)

[Latest Release](https://github.com/Tianming-Wu/Countdown/releases/latest)

![Running on Ubuntu](https://github.com/user-attachments/assets/dafc5caf-3cbd-4c77-a459-6f04da13829c)


Countdown provides a window on your desktop, counting for a specific date.

By default, it counts to 2025.6.7, the University entrance exam in China.

# Features
- Customizable title, date and graphical effect.
- Auto refresh at 00:00 (current timezone).


# Configuration
Click the '天' character on the bottom right to expand or fold settings panel.

Here you can set the date to count to and whether the window is Translucent (or, transparent) (Requires restart).

Other options can only be edited from `consistent.ini`.
You can find it in the program directory after launching it for the very first time.

## Config
Default config file as this:
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
- `[app]` These are program behaviors.
  - `Animation`*(string)*: Enable window animation.   
  - `TargetDate`*(string)*: Target date, format`yyyy-mm-dd`.
  - `TargetString`*(string)*: The title of the countdown.
  - `Timer`*(bool)*: Enable 12:00 update. On computers that definitely restart everyday (like a classroom computer), disable this can save *a little* power. (has almost no difference on performance)
  - `Translucent`*(bool)*: Window background translucent.
- `[widget]` These are widget graphical effect.
  - `Stylesheet`*(string)*: The stylesheet of the widget.See [Style](#style)


## Style
The default stylesheet in config:
```ini
[widget]
Stylesheet=".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }"
```
The format is acturally qss. Check [Qt Online Help Document (EN)](https://doc.qt.io/qt-6/stylesheet.html), [csdn(1)](https://blog.csdn.net/zwcslj/article/details/140154933) or [csdn(2)](https://blog.csdn.net/martian665/article/details/142520397) for more details.

The base widget's name is `centralwidget`. **Note** that almost all components are children of QWidget, so you should use `.QWidget` instead of `QWidget`selector, as long as you don't want to apply it to *everything*. Check for names in ui file. For a more friendly interaction, try qtcreator or designer.

If you want to customize it without learning qss, give this to AI with your requirements.:
```
Write a qss file which should be in a single line. 
The program is a Qt countdown widget, the background is QWidget centralwidget, Title: QLabel labelName, Content： QLabel label_Day, The main window has a translucent background. 
Example: ".QWidget{ background-color: rgba(255,255,255,180); border-radius: 10px; } .QLabel{ color: black; } .QPushButton:checked{ color: green; }" 
My requirements are...
```

# UI Behaviors
Countdown hovers **15 pixels** from the **top right corner** of your primary display.

It automatically adapts to your scaling (Thanks to the powerful [qt](https://qt.io)).

The geometry (position and size) is currently NOT adjustable.

You cannot move, resize, minimize/maximize or close the window.

The program creates a tray icon, which contains a "config" to your config file (Windows only) and "Quit".


# Known issues
- (Ubuntu) Cannot hide its icon in the task bar.
- (Windows) "Config" tray menu not working.
