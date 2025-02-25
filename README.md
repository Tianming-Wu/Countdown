# Countdown
![GitHub Release](https://img.shields.io/github/v/release/Tianming-Wu/Countdown)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Tianming-Wu/Countdown/main.yml)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/Tianming-Wu/Countdown)

![Countdown running on Ubuntu](https://github.com/user-attachments/assets/333c1ca7-9940-4a5e-b6e8-74c86bb74100)

Countdown provides a window on your desktop, counting for a specific date.

By default, it counts to 2025.6.7, the University entrance exam in China.

# Behaviors
Countdown hovers 15 pixels from the top right corner of your primary display.

The geometry (position and size) is currently not adjustable.

You cannot move, resize, minimize/maximize or close the window.

The program creates a tray icon. You can quit it there.

# Configure
Click on the '天' character on the bottom right to extend settings panel, and click again to hide it.

Here you can set the date to count to and whether the window is Translucent (or, transparent) (Requires restart).

Other options can only be edited from `consistent.ini`.
You can find it in the program directory after launching it for the very first time.

# Known issues
- Stylesheet for widget doesn't take any effect.
- On linux, it cannot position itself to topright (Wayland, gnome-tweaks:center new windows).
- On linux, it cannot hide its icon in the task bar.
