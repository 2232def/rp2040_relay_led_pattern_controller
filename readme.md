# Diwali LED Pattern Demo: Shrike Lite (RP2040) with Relay Switching

## About

A small Diwali lighting project. A Vicharak Shrike Lite (RP2040) switches groups of LEDs on and off through a 4-channel relay module to create different light patterns.

## Video/photos 




## Hardware

| Component | Details |
|---|---|
| Microcontroller | Vicharak Shrike Lite (RP2040) |
| Relay module | 4-channel, 5 V coil (CYX-3FC T73), contacts rated 10 A at 24 V DC |
| Orange LEDs | 5 |
| Yellow LEDs | 12 |
| White LEDs | 6 |
| Resistors | Current-limiting, values below |
| Power supply | 12 V DC adapter (LED supply) |
| Relay coil supply | 5 V |
| Other | Jumper wires, breadboard or PCB |

## Resistor Values

Calculated for a 12 V supply with 3 LEDs per series string. Each string has its own resistor.

| LED colour | LEDs per string | Resistor |
|---|---|---|
| Orange | 3 (and 2 for the last string) | 330 Ω (3 LEDs), 390 Ω (2 LEDs) |
| Yellow | 3 | 330 Ω |
| White | 3 | 120 Ω (150 Ω for a gentler start) |

Formula: `R = (Vsupply - N x Vf) / I`

## Connections

**Power**
- 12 V supply goes to the relay **COM** terminals.
- Relay **NO** terminals feed the LED strings (resistor first, then LEDs).
- All grounds are common: adapter GND, Shrike Lite GND, relay module GND and the LED strings' return.

**Connection diagram**

Control side (3.3 V signals from the Shrike Lite):

```
Shrike Lite              Relay module
-----------              ------------
GPIO 5  -------------->  IN1
GPIO 6  -------------->  IN2
GPIO 7  -------------->  IN3
GPIO 8  -------------->  IN4
GND     -------------->  GND
                  5 V -> VCC (relay coil supply)
```

LED side (repeat for each relay channel):

```
                                +--[R]--LED--LED--LED--+
+12 V ----> COM    NO ----------+                       +----> GND (common)
                                +--[R]--LED--LED--LED--+
```

Each string has its own resistor, placed before the LEDs. The long leg (anode) of every LED faces the resistor side.

## What I Learned

Building this project taught me a lot about LEDs, their voltage ranges and how they behave in a circuit.

still improving this project 
