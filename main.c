
#include <stdbool.h>
#include <stdint.h>

// Reset controller
#define RESETS_REG (*(volatile uint32_t *)0x4000C000)
#define RESETS_RESET_DONE (*(volatile uint32_t *)0x4000C008)

// IO_BANK0_GPIO_control_registers
#define GPIO_CTRL_5 (*(volatile uint32_t *)0x4001402C)
#define GPIO_CTRL_6 (*(volatile uint32_t *)0x40014034)
#define GPIO_CTRL_7 (*(volatile uint32_t *)0x4001403C)
#define GPIO_CTRL_8 (*(volatile uint32_t *)0x40014044)

// SIO registers
#define SIO_GPIO_OUT_SET (*(volatile uint32_t *)0xD0000014)
#define SIO_GPIO_OUT_CLR (*(volatile uint32_t *)0xD0000018)
#define SIO_GPIO_OE_SET (*(volatile uint32_t *)0xD0000024)

// Connection of GPIO and Relay pins
#define RELAY_PIN_1 (1 << 5)
#define RELAY_PIN_2 (1 << 6)
#define RELAY_PIN_3 (1 << 7)
#define RELAY_PIN_4 (1 << 8)

// relay pin mask
#define RELAY_PINS (RELAY_PIN_1 | RELAY_PIN_2 | RELAY_PIN_3 | RELAY_PIN_4)

static inline __attribute__((always_inline)) void light_pattern(uint32_t p) {
  SIO_GPIO_OUT_SET = RELAY_PINS;
  SIO_GPIO_OUT_CLR = ((uint32_t)(p) << 5);
  for (volatile uint32_t i = 0; i < 100000; i++) {
  }
}

int main() {

  // Release IO_BANK0 from reset
  RESETS_REG &= ~(1 << 5);

  // Wait until IO_BANK0 is ready
  while (!(RESETS_RESET_DONE & (1 << 5))) {
  }

  // Select SIO function for GPIO pins
  GPIO_CTRL_5 = 5;
  GPIO_CTRL_6 = 5;
  GPIO_CTRL_7 = 5;
  GPIO_CTRL_8 = 5;

  // Set output HIGH before enabling the output
  // Active-LOW relay: HIGH means OFF
  SIO_GPIO_OUT_SET = RELAY_PINS;

  // Enable GPIO5 as output
  SIO_GPIO_OE_SET = RELAY_PINS;

  while (1) {

    // 1. Sequential Chase
    for (uint32_t i = 0; i < 4; i++) {
      light_pattern(1 << i);
    }

    // 2. Ping-Pong
    for (uint32_t i = 0; i < 4; i++) {
      light_pattern(1 << i);
    }

    for (int32_t i = 2; i >= 0; i--) {
      light_pattern(1 << i);
    }

    // 3. Alternating
    light_pattern((1 << 0) | (1 << 2));
    light_pattern((1 << 1) | (1 << 3));

    // 4. Outside-In
    light_pattern((1 << 0) | (1 << 3));
    light_pattern((1 << 1) | (1 << 2));

    // 5. Fill and Empty
    for (uint32_t i = 0; i <= 4; i++) {
      light_pattern((1 << i) - 1);
    }

    for (int32_t i = 3; i >= 0; i--) {
      light_pattern((1 << i) - 1);
    }

    // 6. Binary Counter
    for (uint32_t count = 0; count < 16; count++) {
      light_pattern(count);
    }
  }
}
