/****************************************************************************
 * main.c
 *
 *   Aluno: Filipe Ferreira Martins (11911EAU021) <filipe.ferreira.feelt@ufu.br>
 * 
****************************************************************************/

#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>


/* AHB1 Base Addresses ******************************************************/

#define STM32_RCC_BASE       0x40023800     /* 0x40023800-0x40023bff: Reset and Clock control RCC */

/* GPIOC Base Addresses ******************************************************/

#define STM32_GPIOC_BASE     0x40020800     /* 0x48000800-0x48000bff: GPIO Port C */

/* Register Offsets *********************************************************/

#define STM32_RCC_AHB1ENR_OFFSET  0x0030   /* AHB1 Peripheral Clock enable register */


#define STM32_GPIO_MODER_OFFSET   0x0000  /* GPIO port mode register */
#define STM32_GPIO_OTYPER_OFFSET  0x0004  /* GPIO port output type register */
#define STM32_GPIO_PUPDR_OFFSET   0x000c  /* GPIO port pull-up/pull-down register */
#define STM32_GPIO_ODR_OFFSET     0x0014  /* GPIO port output data register */
#define STM32_GPIO_BSRR_OFFSET    0x0018  /* GPIO port bit set/reset register */


/* Register Addresses *******************************************************/

#define STM32_RCC_AHB1ENR        (STM32_RCC_BASE+STM32_RCC_AHB1ENR_OFFSET)

#define STM32_GPIOC_MODER        (STM32_GPIOC_BASE+STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOC_OTYPER       (STM32_GPIOC_BASE+STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR        (STM32_GPIOC_BASE+STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOC_ODR          (STM32_GPIOC_BASE+STM32_GPIO_ODR_OFFSET)
#define STM32_GPIOC_BSRR         (STM32_GPIOC_BASE+STM32_GPIO_BSRR_OFFSET)

/* AHB1 Peripheral Clock enable register */

#define RCC_AHB1ENR_GPIOAEN      (1 << 0)  /* Bit 2:  IO port A clock enable */
#define RCC_AHB1ENR_GPIOBEN      (1 << 1)  /* Bit 2:  IO port B clock enable */
#define RCC_AHB1ENR_GPIOCEN      (1 << 2)  /* Bit 2:  IO port C clock enable */

/* GPIO port mode register */

#define GPIO_MODER_INPUT           (0) /* Input */
#define GPIO_MODER_OUTPUT          (1) /* General purpose output mode */
#define GPIO_MODER_ALT             (2) /* Alternate mode */
#define GPIO_MODER_ANALOG          (3) /* Analog mode */

#define GPIO_MODER_SHIFT(n)        (n << 1)

#define GPIO_MODER_SHIFT(n)        (n << 1)
#define GPIO_MODER_MASK(n)         (3 << GPIO_MODER_SHIFT(n))

/* GPIO port output type register */

#define GPIO_OTYPER_PP             (0) /* 0=Output push-pull */
#define GPIO_OTYPER_OD             (1) /* 1=Output open-drain */

#define GPIO_OT_SHIFT(n)           (n)
#define GPIO_OT_MASK(n)            (1 << GPIO_OT_SHIFT(n))

/* GPIO port pull-up/pull-down register */

#define GPIO_PUPDR_NONE            (0) /* No pull-up, pull-down */
#define GPIO_PUPDR_PULLUP          (1) /* Pull-up */
#define GPIO_PUPDR_PULLDOWN        (2) /* Pull-down */

#define GPIO_PUPDR_SHIFT(n)        (n << 1)
#define GPIO_PUPDR_MASK(n)         (3 << GPIO_PUPDR_SHIFT(n))

/* Configuration */

#define LED_DELAY  50000

int main(int argc, char *argv[])
{
  uint32_t reg;
  uint32_t *preg;

  /* Criar ponteiro para RCC_AHB1ENR*/
  uint32_t *pRCC_AHB1ENR = (uint32_t *)(STM32_RCC_AHB1ENR);
  uint32_t *pGPIOC_MODER = (uint32_t *)(STM32_GPIOC_MODER);
  uint32_t *pGPIOC_PUPDR = (uint32_t *)(STM32_GPIOC_PUPDR);
  uint32_t *pGPIOC_BSRR = (uint32_t *)(STM32_GPIOC_BSRR);

  /* Habilitar o GPIOC no RCC */
  reg = *pRCC_AHB1ENR;
  //reg |= 0x04;          // |= (operação OU)
  reg |= RCC_AHB1ENR_GPIOCEN;        // (1 << 2) 1 deslocado de 2
  *pRCC_AHB1ENR = reg;

  /* Configurar o PC13 como saída, PP(push-pull) Pu(pull-up) e PD(pull-down) desligados */
  reg = *pGPIOC_MODER;
  reg &= ~GPIO_MODER_MASK(13);      // &= (operação AND) ~(operação not)
  reg |= (GPIO_MODER_OUTPUT << GPIO_MODER_SHIFT(13));
  *pGPIOC_MODER = reg; 


  preg = (uint32_t *)(STM32_GPIOC_OTYPER);
  reg = *preg;
  reg &= ~(GPIO_OT_MASK(13));
  reg |= (GPIO_OTYPER_PP << GPIO_OT_SHIFT(13));

  preg = (uint32_t *)(STM32_GPIOC_PUPDR);
  reg = *preg;
  reg &= ~(GPIO_PUPDR_MASK(13));
  reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR_SHIFT(13));
  *pGPIOC_PUPDR = reg;


  while(1)
  {
    /* Código aqui */
    /* Ligar o LED (LOW) */

    /* Delay */
    *pGPIOC_BSRR = GPIO_BSRR_RESET(13);
    for (int i = 0; i < LED_DELAY; i++);

    /* Desligar o LED (HIGH) */
    *pGPIOC_BSRR = GPIO_BSRR_SET(13);
    for (int i = 0; i < LED_DELAY; i++);

    /* Delay */
  };

  /* Nao deveria chegar aqui */

  return EXIT_SUCCESS;
}