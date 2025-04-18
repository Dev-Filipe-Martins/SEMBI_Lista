/****************************************************************************
 * startup.c
 *
 *   Aluno: Filipe Ferreira Martins (11911EAU021) <filipe.ferreira.feelt@ufu.br>
 * 
****************************************************************************/

#include <stdint.h>

// Definição do endereço de início da stack

#define SRAM_START  0x20000000U                   /* Inicio da SRAM CORTEX-M */
#define SRAM_SIZE   (128U * 1024U)                /* Tam. SRAM STM32F411 128K */
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))  /* Final da SRAM STM32F411 */

#define STACK_START SRAM_END                      /* Inicio da Stack */

/****************************************************************************
 * Private Function Prototypes
****************************************************************************/

int main(void);

/* Prototipos de funções para as System Exceptions */
// Vetores de interrupção para Built-in Exceptions

void reset_handler     (void);
void nmi_handler       (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler  (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__ ((weak, alias("default_handler")));
void svc_handler       (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler  (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler    (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler   (void) __attribute__ ((weak, alias("default_handler")));

// irq para diferenciar periférico da cpu
// External Interrupts

void wwdg_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));
void pvd_irqhandler             (void) __attribute__ ((weak, alias("default_handler")));
void tamp_stamp_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void rtc_wkup_irqhandler        (void) __attribute__ ((weak, alias("default_handler")));
void flash_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void rcc_irqhandler             (void) __attribute__ ((weak, alias("default_handler")));
void exti0_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void exti1_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void exti2_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void exti3_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void exti4_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm0_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm1_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm2_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm3_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm4_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm5_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm6_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void adc_irqhandler             (void) __attribute__ ((weak, alias("default_handler")));
void exti9_5_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void t1_brk_t9_irqhandler       (void) __attribute__ ((weak, alias("default_handler")));
void t1_up_t10_irqhandler       (void) __attribute__ ((weak, alias("default_handler")));
void t1_trf_com_t11_irqhandler  (void) __attribute__ ((weak, alias("default_handler")));
void t1_cc_irqhandler           (void) __attribute__ ((weak, alias("default_handler")));
void t2_irqhandler              (void) __attribute__ ((weak, alias("default_handler")));
void t3_irqhandler              (void) __attribute__ ((weak, alias("default_handler")));
void t4_irqhandler              (void) __attribute__ ((weak, alias("default_handler")));
void i2c1_ev_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void i2c1_er_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void i2c2_ev_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void i2c2_er_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void spi1_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));
void spi2_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));
void usart1_irqhandler          (void) __attribute__ ((weak, alias("default_handler")));
void usart2_irqhandler          (void) __attribute__ ((weak, alias("default_handler")));
void exti15_10_irqhandler       (void) __attribute__ ((weak, alias("default_handler")));
void rtc_alarm_irqhandler       (void) __attribute__ ((weak, alias("default_handler")));
void otg_fs_wkup_irqhandler     (void) __attribute__ ((weak, alias("default_handler")));
void dma1_strm7_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void sdio_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));
void t5_irqhandler              (void) __attribute__ ((weak, alias("default_handler")));
void spi3_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm0_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm1_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm2_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm3_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm4_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void otg_fs_irqhandler          (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm5_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm6_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void dma2_strm7_irqhandler      (void) __attribute__ ((weak, alias("default_handler")));
void usart6_irqhandler          (void) __attribute__ ((weak, alias("default_handler")));
void i2c3_ev_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void i2c3_er_irqhandler         (void) __attribute__ ((weak, alias("default_handler")));
void fpu_irqhandler             (void) __attribute__ ((weak, alias("default_handler")));
void spi4_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));
void spi5_irqhandler            (void) __attribute__ ((weak, alias("default_handler")));

/****************************************************************************
 * External Data
****************************************************************************/

/* Variaveis exportadas pelo linker script */

extern uint32_t _sdata;     /* Inicio da seção .data */
extern uint32_t _edata;     /* Fim da seção .data */
extern uint32_t _la_data;   /* Origem da seção .data na FLASH */

extern uint32_t _sbss;      /* Inicio da seção .bss */
extern uint32_t _ebss;      /* Fim da seção .bss */

/****************************************************************************
 * Private Data
****************************************************************************/

/* Tabela de Vetores de Interrupção */

uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
  STACK_START,                            /* 0x0000 0000 */
  (uint32_t)reset_handler,                /* 0x0000 0004 */
  (uint32_t)nmi_handler,                  /* 0x0000 0008 */
  (uint32_t)hardfault_handler,            /* 0x0000 000c */
  (uint32_t)memmanage_handler,            /* 0x0000 0010 */
  (uint32_t)busfault_handler,             /* 0x0000 0014 */
  (uint32_t)usagefault_handler,           /* 0x0000 0018 */
  0,                                      /* 0x0000 001c */
  0,                                      /* 0x0000 0020 */
  0,                                      /* 0x0000 0024 */
  0,                                      /* 0x0000 0028 */
  (uint32_t)svc_handler,                  /* 0x0000 002c */
  (uint32_t)debugmon_handler,             /* 0x0000 0030 */
  0,                                      /* 0x0000 0034 */
  (uint32_t)pendsv_handler,               /* 0x0000 0038 */
  (uint32_t)systick_handler,              /* 0x0000 003c */
  (uint32_t)wwdg_irqhandler,              // 0x0000 0040
  (uint32_t)pvd_irqhandler,               // 0x0000 0044
  (uint32_t)tamp_stamp_irqhandler,        // 0x0000 0048
  (uint32_t)rtc_wkup_irqhandler,          // 0x0000 004C
  (uint32_t)flash_irqhandler,             // 0x0000 0050
  (uint32_t)rcc_irqhandler,               // 0x0000 0054
  (uint32_t)exti0_irqhandler,             // 0x0000 0058
  (uint32_t)exti1_irqhandler,             // 0x0000 005C
  (uint32_t)exti2_irqhandler,             // 0x0000 0060
  (uint32_t)exti3_irqhandler,             // 0x0000 0064
  (uint32_t)exti4_irqhandler,             // 0x0000 0068
  (uint32_t)dma1_strm0_irqhandler,        // 0x0000 006C
  (uint32_t)dma1_strm1_irqhandler,        // 0x0000 0070
  (uint32_t)dma1_strm2_irqhandler,        // 0x0000 0074
  (uint32_t)dma1_strm3_irqhandler,        // 0x0000 0078
  (uint32_t)dma1_strm4_irqhandler,        // 0x0000 007C
  (uint32_t)dma1_strm5_irqhandler,        // 0x0000 0080
  (uint32_t)dma1_strm6_irqhandler,        // 0x0000 0084
  (uint32_t)adc_irqhandler,               // 0x0000 0088
  (uint32_t)exti9_5_irqhandler,           // 0x0000 009C
  (uint32_t)t1_brk_t9_irqhandler,         // 0x0000 00A0
  (uint32_t)t1_up_t10_irqhandler,         // 0x0000 00A4
  (uint32_t)t1_trf_com_t11_irqhandler,    // 0x0000 00A8
  (uint32_t)t1_cc_irqhandler,             // 0x0000 00AC
  (uint32_t)t2_irqhandler,                // 0x0000 00B0
  (uint32_t)t3_irqhandler,                // 0x0000 00B4
  (uint32_t)t4_irqhandler,                // 0x0000 00B8
  (uint32_t)i2c1_ev_irqhandler,           // 0x0000 00BC
  (uint32_t)i2c1_er_irqhandler,           // 0x0000 00C0
  (uint32_t)i2c2_ev_irqhandler,           // 0x0000 00C4
  (uint32_t)i2c2_er_irqhandler,           // 0x0000 00C8
  (uint32_t)spi1_irqhandler,              // 0x0000 00CC
  (uint32_t)spi2_irqhandler,              // 0x0000 00D0
  (uint32_t)usart1_irqhandler,            // 0x0000 00D4
  (uint32_t)usart2_irqhandler,            // 0x0000 00D8
  (uint32_t)exti15_10_irqhandler,         // 0x0000 00E0
  (uint32_t)rtc_alarm_irqhandler,         // 0x0000 00E4
  (uint32_t)otg_fs_wkup_irqhandler,       // 0x0000 00E8
  (uint32_t)dma1_strm7_irqhandler,        // 0x0000 00FC
  (uint32_t)sdio_irqhandler,              // 0x0000 0104
  (uint32_t)t5_irqhandler,                // 0x0000 0108
  (uint32_t)spi3_irqhandler,              // 0x0000 010C
  (uint32_t)dma2_strm0_irqhandler,        // 0x0000 0120
  (uint32_t)dma2_strm1_irqhandler,        // 0x0000 0124
  (uint32_t)dma2_strm2_irqhandler,        // 0x0000 0128
  (uint32_t)dma2_strm3_irqhandler,        // 0x0000 012C
  (uint32_t)dma2_strm4_irqhandler,        // 0x0000 0130
  (uint32_t)otg_fs_irqhandler,            // 0x0000 014C
  (uint32_t)dma2_strm5_irqhandler,        // 0x0000 0150
  (uint32_t)dma2_strm6_irqhandler,        // 0x0000 0154
  (uint32_t)dma2_strm7_irqhandler,        // 0x0000 0158
  (uint32_t)usart6_irqhandler,            // 0x0000 015C
  (uint32_t)i2c3_ev_irqhandler,           // 0x0000 0160
  (uint32_t)i2c3_er_irqhandler,           // 0x0000 0164
  (uint32_t)fpu_irqhandler,               // 0x0000 0184
  (uint32_t)spi4_irqhandler,              // 0x0000 0190
  (uint32_t)spi5_irqhandler,              // 0x0000 0194                                                                          
};

/****************************************************************************
 * Private Functions
****************************************************************************/

void reset_handler(void)
{
  uint32_t i;

  /* Carrega secao data da FLASH para a SRAM */
  /* Copia a secao .data para a RAM */
   
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *pDst = (uint8_t*)&_sdata;                      /* SRAM */
  uint8_t *pSrc = (uint8_t*)&_la_data;                    /* FLASH */
  
  for(i = 0; i < size; i++)
  {
    *pDst++ = *pSrc++;
  }

  /* Preenche a secao .bss com zero */

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t*)&_sbss;
  for(i = 0 ; i < size; i++)
  {
    *pDst++ = 0;
  }

  /* Chama a funcao main() */

  main();
}

void default_handler(void)
{
  while(1){};
}