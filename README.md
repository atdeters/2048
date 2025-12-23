# 🔢 42 Rush: Wong Kar-Wai (2048)

Welcome to our **terminal-based (TUI)** implementation of the classic game  
[**2048**](https://github.com/gabrielecirulli/2048) by Gabriele Cirulli — reimagined in C and playable entirely in the terminal.

---

## 📚 About This Project

This project was created as part of a **42 Rush** — a fast-paced, team-based coding challenge  
hosted by [**42 Vienna**](https://www.42vienna.com/en/about-42/) with a strict timeframe:

**Friday 6:42 PM → Sunday 11:42 PM**

The goal? Work as a team, push your limits, experiment with new ideas, and build something completely from scratch under pressure.

For this Rush, our task was to create our own version of **2048**, with the following constraints:

- The game must be written **entirely in C**
- It must be compiled using **GNU Make**
- It must run **inside the terminal**

To make terminal development feasible and expressive, we were allowed to use the  
**ncurses** library for input handling, colors, and window management.

Unlike many Rushes, our group ended up being **three people instead of two**.  
To raise the difficulty accordingly, we decided to implement **all optional bonuses** described in the project sheet.

---

## 🎮 Features & Bonuses

In addition to the mandatory requirements, we implemented the following **bonus features**:

- A **menu system** available before the game starts  
- Support for both **4×4 and 5×5 grids**  
- **Colorized tiles**  
- A persistent **highscore system**, stored in a file  
- Tile values rendered as **ASCII art** instead of plain numbers  

---

## ✨ Extra Ideas Beyond the Sheet

We also introduced several features of our own to further enhance the experience:

- **Theme system**  
  - Instead of hardcoding colors, themes are defined via header files (`.h`)  
  - Themes are selected at **compile time**  
  - All themes can be found and customized in the `themes/` directory  
  - Using AI tools to generate new themes from existing references proved surprisingly effective

- **Fully dynamic window resizing**  
  - The game adapts to the available terminal size at runtime  
  - If the window becomes too small, gameplay is temporarily blocked and the user is prompted to resize  
  - ASCII-art tiles scale dynamically and automatically fall back to plain digits when space is insufficient

- **Persistent in-game menu**  
  - The menu is accessible **at any point during gameplay**  
  - Players can resume, restart, or switch grid sizes mid-session without restarting the program

---

## 🕹️ Gameplay

The game starts with a **4×4 grid** (optionally **5×5**) containing two initial tiles (`2` or `4`).

- Players move tiles **up, down, left, or right**
- All tiles slide as far as possible in the chosen direction
- Tiles with the same value merge, doubling their number
- The objective is to reach **2048**  
  (or a custom value defined via `WIN_VALUE` in the config file)

By default, the game ends once `2048` is reached — a design choice that simplifies visual theming.  
This behavior can be disabled by setting the `END_AT_2048` macro to `false` in the config.

---

## ⌨️ Controls

The game supports multiple input schemes for convenience:

- **Arrow keys**
- **WASD**
- **Vim-style navigation (HJKL)**

**Menu access:**  
- Press `m` at any time to open the menu.  
- Press `ESC` at any time to close the game gracefully.  
All additional navigation keys are displayed directly inside the menu UI.

**Movement keys:**

- **Up:** ,`↑`, `W`, `K`  
- **Down:** `↓`, `S`, `J`  
- **Left:** `←`, `A`, `H`  
- **Right:** `→`, `D`, `L`

---

## ⚠️ Disclaimer for other 42 Students

If you’re currently doing this Rush:

**Please don’t copy our code.**

- You won’t learn anything from it  
- The value lies in **struggling, designing, and debugging yourself**  
- Use this only as inspiration for what *can* be built in a short time

---


## 🙏 Thanks

Thanks to **Gabriele Cirulli** for creating 2048, and to **Veewo Studio** for *1024* and **Asher Vollmer** for *Threes!* — the games that inspired its original design.
This project was demanding, chaotic, and deeply rewarding — exactly what a Rush should be!
