# 🤖 Line Follower Robot — PIC16F887

An autonomous line-following robot built around the **PIC16F887** microcontroller. The robot uses two IR obstacle-avoidance sensors to detect a black line on a white surface and steers itself to stay on course by independently controlling two DC motors.
We use a powerbank as the power source in this project. 



## 🧠 How It Works

Two IR sensors are mounted at the front of the chassis, straddling the line. Each sensor outputs:

| Surface | Output |
|---------|--------|
| Black   | `0`    |
| White   | `1`    |

The microcontroller reads both sensors in a continuous loop and drives the motors according to four states:

| Left Sensor (S1) | Right Sensor (S2) | Action         |
|:-----------------:|:-----------------:|----------------|
| 1                | 1                 | Move Forward   |
| 0                | 1                 | Turn Left      |
| 1                | 0                 | Turn Right     |
| 0                | 0                 | Stop           |

The **L293D** H-bridge IC sits between the PIC16F887 and the DC motors, boosting the microcontroller's output current to the level the motors require. An **LM016 LCD** displays the current motion state in real time, and two **LEDs** indicate left/right turns.

---

## 🔧 Hardware

| Component | Description |
|-----------|-------------|
| PIC16F887 | 40-pin PIC microcontroller (main controller) |
| L293D | Dual H-bridge motor driver IC |
| DC Motor × 2 | Drive the rear wheels |
| IR Obstacle Avoidance Sensor × 2 | Detect the black line |
| LM016 LCD | Displays motion state |
| Potentiometer | Adjusts LCD contrast |
| LED × 2 | Turn indicators |
| 3-wheel toy car chassis | Mechanical platform |
| 9 V Battery | Power supply |
| Breadboard + power supply module | Prototyping |

---

## 📐 Circuit / Pin Map

```
PORTA (inputs)
  RA0 ── Left IR sensor output
  RA1 ── Right IR sensor output

PORTC (LCD)
  RC0 ── LCD RS
  RC1 ── LCD EN
  RC2-RC5 ── LCD D4-D7

PORTD (outputs)
  RD1 ── Left-turn LED
  RD2 ── Right-turn LED
  RD4 ── Motor 1 IN1
  RD5 ── Motor 1 IN2
  RD6 ── Motor 2 IN1
  RD7 ── Motor 2 IN2
```

---

## 💻 Software

- **IDE / Compiler:** [MikroC Pro for PIC](https://www.mikroe.com/mikroc-pro-for-pic)
- **Simulation:** [Proteus Design Suite](https://www.labcenter.com/)
- **Language:** C (MikroC dialect)

### Logic Summary

```
while(1):
  S1=1, S2=1  →  Both motors forward   →  LCD: "MOVING FORWARD"
  S1=0, S2=1  →  Left motor stop       →  LCD: "TURNING LEFT"
  S1=1, S2=0  →  Right motor stop      →  LCD: "TURNING RIGHT"
  S1=0, S2=0  →  Both motors stop      →  LCD: "STOPPED"
```

The `lcd()` helper function only writes to the display when the state actually changes, avoiding unnecessary clearing and flickering.

---

## 📁 Repository Structure

```
line-follower-pic16f887/
├── src/
│   └── main.c          # MikroC source code
├── docs/
│   └── simulation.png  # Proteus simulation screenshot
└── README.md
```

---

## 🚀 Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/line-follower-pic16f887.git
   ```
2. Open `src/main.c` in **MikroC Pro for PIC**.
3. Set the target device to **PIC16F887** and the oscillator frequency to match your hardware.
4. Compile and flash the `.hex` output to the microcontroller.
5. *(Optional)* Load the Proteus project from `docs/` to simulate before flashing.

---

## 📖 Project Overview

| Item | Detail |
|------|--------|
| Platform | PIC16F887 |
| Motor Driver | L293D (dual H-bridge) |
| Sensing | 2× IR obstacle-avoidance modules |
| Display | LM016 16×2 LCD |
| Power | 9 V battery |
| Simulation tool | Proteus |

---

## 📜 License

This project is released under the [MIT License](LICENSE).
