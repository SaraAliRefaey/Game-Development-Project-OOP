#  CS213 Modular Board Game Engine: The 13 Game Challenge 

## Project Overview

This repository showcases the result of the **Object-Oriented Programming (OOP)** assignment for the CS213 course. The project involves building a robust, **modular game engine** in C++ capable of hosting **thirteen diverse Tic-Tac-Toe variants** within a single application.

The primary focus was the rigorous application of core OOP principles, particularly the **Open/Closed Principle (OCP)**, to ensure a highly scalable and maintainable codebase.

## ⚙️ Architectural Design & OOP Implementation

The entire system is engineered using a flexible inheritance model, allowing for easy expansion without altering the foundational code.

| Component | Role | OOP Principle Applied |
| :--- | :--- | :--- |
| **Base Classes** | (`Board`, `Player`, `GameManager`) define the common interfaces and abstract methods that all games must adhere to. | **Abstraction, Inheritance** |
| **Derived Classes** | (`PyramidBoard`, `NumericalGameManager`, etc.) inherit from the bases and implement the unique rules, winning conditions, and state management for each specific variant. | **Open/Closed Principle (OCP)** |
| **Main Application** | Handles user interaction via a menu and uses **Polymorphism** to dynamically run the selected game variant regardless of its specific ruleset. | **Polymorphism** |

### Quality & Documentation Requirements
* **Doxygen Documentation:** Comprehensive HTML documentation was generated using Doxygen for the entire codebase.
* **Code Review:** A formal code review process was implemented, requiring detailed reports on code quality, errors, and adherence to standards.

## 🧠 Advanced Features: AI & Strategy

* **Intelligent AI:** Development of an intelligent computer opponent utilizing **Min-Max** or **Backtracking** algorithms to determine optimal moves (Individual Bonus Task).
* **Random Player:** A baseline random player is available for all game types.

## 🎮 The Complete Game Collection (13 Variants)

The engine successfully manages a wide spectrum of game complexities:

### I. Standard 3x3 Grid (Rule Twists)
| Game | Core Mechanic |
| :--- | :--- |
| **Misère XO** | The opposite game; getting three-in-a-row results in a **loss**. |
| **Numerical XO** | Players use odd/even numbers; the winner forms a line summing exactly to **15**. |
| **Word XO** | Players place letters; the winner is the first to form a valid **three-letter word**. |
| **Infinity XO** | Marks are dynamically removed; the **oldest mark disappears** after every three moves. |
| **SUS Game** | Focus on maximizing score by creating the "S-U-S" sequence. |
| **Memory XO (Bonus)** | Marks become **hidden** immediately after being placed, challenging player memory. |

### II. Large, Movement & Obstacle Boards
| Game | Core Mechanic |
| :--- | :--- |
| **Four in a Row** | Classic connection game on a **$6 \times 7$** board. |
| **Obstacles XO** | Played on a **$6 \times 6$** grid where **random obstacle cells** (`#`) are added periodically. |
| **Five XO ($5 \times 5$)** | Larger board variant where the goal is to maximize the number of three-in-a-row sequences. |
| **$4 \times 4$ Moving XO** | Players start with tokens and must **move** them one step to achieve three-in-a-row. |

### III. Unique Shapes & Meta-Game
| Game | Core Mechanic |
| :--- | :--- |
| **Pyramid XO** | Played on a pyramid-shaped board ($5, 3, 1$ rows). |
| **Diamond XO** | Played on a diamond-shaped grid, requiring the **simultaneous completion** of both a three-mark line and a four-mark line. |
| **Ultimate Tic Tac Toe (Bonus)** | A **meta-game** where winning three $3 \times 3$ sub-boards in a row wins the main game. |

## 📦 Deliverables & Submission

The final submission consists of:
* **One Integrated C++ Application:** Containing all game implementations and the menu system.
* **Adherence to Standards:** Strict compliance with the Open/Closed Principle (OCP).

## 👥 Team Members

| Name | ID |
| :--- | :--- |
| Haneen Fouad Abo Al-Yazid | 20240175 |
| Sara Ali Refaey Abdelhamed | 20242148 |
| Sarah Mohamed Salah El-Din | 20242150 |
| Nawal Mahmoud Abdel Aleem | 20242375 |
