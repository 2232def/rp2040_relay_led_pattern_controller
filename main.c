#include <stdbool.h>
#include <stdint.h>

// Reset controller
#define RESETS_REG (*(volatile uint32_t *)0x4000C000)

#define RESETS_RESET_DONE (*(volatile uint32_t *)0x4000C008)

// IO_BANK0
#define GPIO5_CTRL (*(volatile uint32_t *)0x4001402C)

// SIO registers
#define SIO_GPIO_OUT_SET (*(volatile uint32_t *)0xD0000014)

#define SIO_GPIO_OUT_CLR (*(volatile uint32_t *)0xD0000018)

#define SIO_GPIO_OE_SET (*(volatile uint32_t *)0xD0000024)

#define RELAY_PIN (1 << 5)

__attribute__((section(".boot2"))) void trail(void) {
  // Release IO_BANK0 from reset
  RESETS_REG &= ~(1 << 5);

  // Wait until IO_BANK0 is ready
  while (!(RESETS_RESET_DONE & (1 << 5))) {
  }

  // Select SIO function for GPIO5
  GPIO5_CTRL = 5;

  // Set output HIGH before enabling the output
  // Active-LOW relay: HIGH means OFF
  SIO_GPIO_OUT_SET = RELAY_PIN;

  // Enable GPIO5 as output
  SIO_GPIO_OE_SET = RELAY_PIN;

  while (1) {
    // LOW: Relay ON
    SIO_GPIO_OUT_CLR = RELAY_PIN;

    for (volatile uint32_t i = 0; i < 100000; i++) {
    }

    // HIGH: Relay OFF
    SIO_GPIO_OUT_SET = RELAY_PIN;

    for (volatile uint32_t i = 0; i < 100000; i++) {
    }
  }
}
