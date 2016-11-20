/******************************************************************************
 * Peripheral memory map
 ******************************************************************************/
#define FM3_FLASH_BASE        (0x00000000UL)                 /* Flash Base                             */
#define FM3_PERIPH_BASE       (0x40000000UL)                 /* Peripheral  Base                       */
#define FM3_CM3_BASE          (0xE0100000UL)                 /* CM3 Private                            */

#define FM3_FLASH_IF_BASE     (FM3_PERIPH_BASE + 0x00000UL)  /* Flash interface registers              */
#define FM3_CRG_BASE          (FM3_PERIPH_BASE + 0x10000UL)  /* Clock and reset registers              */
#define FM3_HWWDT_BASE        (FM3_PERIPH_BASE + 0x11000UL)  /* Hardware watchdog registers            */
#define FM3_SWWDT_BASE        (FM3_PERIPH_BASE + 0x12000UL)  /* Software watchdog registers            */
#define FM3_DTIM_BASE         (FM3_PERIPH_BASE + 0x15000UL)  /* Dual timer 1/2 registers               */
#define FM3_MFT0_FRT_BASE     (FM3_PERIPH_BASE + 0x20000UL)  /* Multifunction Timer unit 0 Free Running Timer registers */
#define FM3_MFT0_OCU_BASE     (FM3_PERIPH_BASE + 0x20000UL)  /* Multifunction Timer unit 0 Output Compare Unit registers */
#define FM3_MFT0_WFG_BASE     (FM3_PERIPH_BASE + 0x20000UL)  /* Multifunction Timer unit 0 Waveform Generator and Noise Canceler registers */
#define FM3_MFT0_ICU_BASE     (FM3_PERIPH_BASE + 0x20000UL)  /* Multifunction Timer unit 0 Input Capture Unit registers */
#define FM3_MFT0_ADCMP_BASE   (FM3_PERIPH_BASE + 0x20000UL)  /* Multifunction Timer unit 0 ADC Start Compare Unit registers */
#define FM3_MFT1_FRT_BASE     (FM3_PERIPH_BASE + 0x21000UL)  /* Multifunction Timer unit 1 Free Running Timer registers */
#define FM3_MFT1_OCU_BASE     (FM3_PERIPH_BASE + 0x21000UL)  /* Multifunction Timer unit 1 Output Compare Unit registers */
#define FM3_MFT1_WFG_BASE     (FM3_PERIPH_BASE + 0x21000UL)  /* Multifunction Timer unit 1 Waveform Generator and Noise Canceler registers */
#define FM3_MFT1_ICU_BASE     (FM3_PERIPH_BASE + 0x21000UL)  /* Multifunction Timer unit 1 Input Capture Unit registers */
#define FM3_MFT1_ADCMP_BASE   (FM3_PERIPH_BASE + 0x21000UL)  /* Multifunction Timer unit 1 ADC Start Compare Unit registers */
#define FM3_MFT_PPG_BASE      (FM3_PERIPH_BASE + 0x24000UL)  /* Multifunction Timer PPG registers      */
#define FM3_BT0_PPG_BASE      (FM3_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 PPG registers             */
#define FM3_BT0_PWM_BASE      (FM3_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 PWM registers             */
#define FM3_BT0_RT_BASE       (FM3_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 RT registers              */
#define FM3_BT0_PWC_BASE      (FM3_PERIPH_BASE + 0x25000UL)  /* Base Timer 0 PWC registers             */
#define FM3_BT1_PPG_BASE      (FM3_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 PPG registers             */
#define FM3_BT1_PWM_BASE      (FM3_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 PWM registers             */
#define FM3_BT1_RT_BASE       (FM3_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 RT registers              */
#define FM3_BT1_PWC_BASE      (FM3_PERIPH_BASE + 0x25040UL)  /* Base Timer 1 PWC registers             */
#define FM3_BT2_PPG_BASE      (FM3_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 PPG registers             */
#define FM3_BT2_PWM_BASE      (FM3_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 PWM registers             */
#define FM3_BT2_RT_BASE       (FM3_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 RT registers              */
#define FM3_BT2_PWC_BASE      (FM3_PERIPH_BASE + 0x25080UL)  /* Base Timer 2 PWC registers             */
#define FM3_BT3_PPG_BASE      (FM3_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 PPG registers             */
#define FM3_BT3_PWM_BASE      (FM3_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 PWM registers             */
#define FM3_BT3_RT_BASE       (FM3_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 RT registers              */
#define FM3_BT3_PWC_BASE      (FM3_PERIPH_BASE + 0x250C0UL)  /* Base Timer 3 PWC registers             */
#define FM3_BT4_PPG_BASE      (FM3_PERIPH_BASE + 0x25200UL)  /* Base Timer 4 PPG registers             */
#define FM3_BT4_PWM_BASE      (FM3_PERIPH_BASE + 0x25200UL)  /* Base Timer 4 PWM registers             */
#define FM3_BT4_RT_BASE       (FM3_PERIPH_BASE + 0x25200UL)  /* Base Timer 4 RT registers              */
#define FM3_BT4_PWC_BASE      (FM3_PERIPH_BASE + 0x25200UL)  /* Base Timer 4 PWC registers             */
#define FM3_BT5_PPG_BASE      (FM3_PERIPH_BASE + 0x25240UL)  /* Base Timer 5 PPG registers             */
#define FM3_BT5_PWM_BASE      (FM3_PERIPH_BASE + 0x25240UL)  /* Base Timer 5 PWM registers             */
#define FM3_BT5_RT_BASE       (FM3_PERIPH_BASE + 0x25240UL)  /* Base Timer 5 RT registers              */
#define FM3_BT5_PWC_BASE      (FM3_PERIPH_BASE + 0x25240UL)  /* Base Timer 5 PWC registers             */
#define FM3_BT6_PPG_BASE      (FM3_PERIPH_BASE + 0x25280UL)  /* Base Timer 6 PPG registers             */
#define FM3_BT6_PWM_BASE      (FM3_PERIPH_BASE + 0x25280UL)  /* Base Timer 6 PWM registers             */
#define FM3_BT6_RT_BASE       (FM3_PERIPH_BASE + 0x25280UL)  /* Base Timer 6 RT registers              */
#define FM3_BT6_PWC_BASE      (FM3_PERIPH_BASE + 0x25280UL)  /* Base Timer 6 PWC registers             */
#define FM3_BT7_PPG_BASE      (FM3_PERIPH_BASE + 0x252C0UL)  /* Base Timer 7 PPG registers             */
#define FM3_BT7_PWM_BASE      (FM3_PERIPH_BASE + 0x252C0UL)  /* Base Timer 7 PWM registers             */
#define FM3_BT7_RT_BASE       (FM3_PERIPH_BASE + 0x252C0UL)  /* Base Timer 7 RT registers              */
#define FM3_BT7_PWC_BASE      (FM3_PERIPH_BASE + 0x252C0UL)  /* Base Timer 7 PWC registers             */
#define FM3_BTIOSEL03_BASE    (FM3_PERIPH_BASE + 0x25100UL)  /* Base Timer I/O selector channel 0 - channel 3 registers */
#define FM3_BTIOSEL47_BASE    (FM3_PERIPH_BASE + 0x25300UL)  /* Base Timer I/O selector channel 4 - channel 7 registers */
#define FM3_SBSSR_BASE        (FM3_PERIPH_BASE + 0x25FFCUL)  /* Software based Simulation Startup (Base Timer) register */
#define FM3_QPRC0_BASE        (FM3_PERIPH_BASE + 0x26000UL)  /* Quad position and revolution counter channel 0 registers */
#define FM3_QPRC1_BASE        (FM3_PERIPH_BASE + 0x26040UL)  /* Quad position and revolution counter channel 1 registers */
#define FM3_ADC0_BASE         (FM3_PERIPH_BASE + 0x27000UL)  /* 12-bit ADC unit 0 registers            */
#define FM3_ADC1_BASE         (FM3_PERIPH_BASE + 0x27100UL)  /* 12-bit ADC unit 1 registers            */
#define FM3_ADC2_BASE         (FM3_PERIPH_BASE + 0x27200UL)  /* 12-bit ADC unit 2 registers            */
#define FM3_CRTRIM_BASE       (FM3_PERIPH_BASE + 0x2E000UL)  /* CR trimming registers                  */
#define FM3_EXTI_BASE         (FM3_PERIPH_BASE + 0x30000UL)  /* External interrupt registers           */
#define FM3_INTREQ_BASE       (FM3_PERIPH_BASE + 0x31000UL)  /* Interrupt request read registers       */
#define FM3_GPIO_BASE         (FM3_PERIPH_BASE + 0x33000UL)  /* General purpose I/O registers          */
#define FM3_LVD_BASE          (FM3_PERIPH_BASE + 0x35000UL)  /* Low voltage detection registers        */
#define FM3_USBCLK_BASE       (FM3_PERIPH_BASE + 0x36000UL)  /* USB clock registers                    */
#define FM3_CANPRES_BASE      (FM3_PERIPH_BASE + 0x37000UL)  /* CAN prescaler register                 */
#define FM3_MFS0_UART_BASE    (FM3_PERIPH_BASE + 0x38000UL)  /* UART asynchronous channel 0 registers  */
#define FM3_MFS0_CSIO_BASE    (FM3_PERIPH_BASE + 0x38000UL)  /* UART synchronous channel 0 registers   */
#define FM3_MFS0_LIN_BASE     (FM3_PERIPH_BASE + 0x38000UL)  /* UART LIN channel 0 registers           */
#define FM3_MFS0_I2C_BASE     (FM3_PERIPH_BASE + 0x38000UL)  /* I2C channel 0 registers                */
#define FM3_MFS1_UART_BASE    (FM3_PERIPH_BASE + 0x38100UL)  /* UART asynchronous channel 1 registers  */
#define FM3_MFS1_CSIO_BASE    (FM3_PERIPH_BASE + 0x38100UL)  /* UART synchronous channel 1 registers   */
#define FM3_MFS1_LIN_BASE     (FM3_PERIPH_BASE + 0x38100UL)  /* UART LIN channel 1 registers           */
#define FM3_MFS1_I2C_BASE     (FM3_PERIPH_BASE + 0x38100UL)  /* I2C channel 1 registers                */
#define FM3_MFS2_UART_BASE    (FM3_PERIPH_BASE + 0x38200UL)  /* UART asynchronous channel 2 registers  */
#define FM3_MFS2_CSIO_BASE    (FM3_PERIPH_BASE + 0x38200UL)  /* UART synchronous channel 2 registers   */
#define FM3_MFS2_LIN_BASE     (FM3_PERIPH_BASE + 0x38200UL)  /* UART LIN channel 2 registers           */
#define FM3_MFS2_I2C_BASE     (FM3_PERIPH_BASE + 0x38200UL)  /* I2C channel 2 registers                */
#define FM3_MFS3_UART_BASE    (FM3_PERIPH_BASE + 0x38300UL)  /* UART asynchronous channel 3 registers  */
#define FM3_MFS3_CSIO_BASE    (FM3_PERIPH_BASE + 0x38300UL)  /* UART synchronous channel 3 registers   */
#define FM3_MFS3_LIN_BASE     (FM3_PERIPH_BASE + 0x38300UL)  /* UART LIN channel 3 registers           */
#define FM3_MFS3_I2C_BASE     (FM3_PERIPH_BASE + 0x38300UL)  /* I2C channel 3 registers                */
#define FM3_MFS4_UART_BASE    (FM3_PERIPH_BASE + 0x38400UL)  /* UART asynchronous channel 4 registers  */
#define FM3_MFS4_CSIO_BASE    (FM3_PERIPH_BASE + 0x38400UL)  /* UART synchronous channel 4 registers   */
#define FM3_MFS4_LIN_BASE     (FM3_PERIPH_BASE + 0x38400UL)  /* UART LIN channel 4 registers           */
#define FM3_MFS4_I2C_BASE     (FM3_PERIPH_BASE + 0x38400UL)  /* I2C channel 4 registers                */
#define FM3_MFS5_UART_BASE    (FM3_PERIPH_BASE + 0x38500UL)  /* UART asynchronous channel 5 registers  */
#define FM3_MFS5_CSIO_BASE    (FM3_PERIPH_BASE + 0x38500UL)  /* UART synchronous channel 5 registers   */
#define FM3_MFS5_LIN_BASE     (FM3_PERIPH_BASE + 0x38500UL)  /* UART LIN channel 5 registers           */
#define FM3_MFS5_I2C_BASE     (FM3_PERIPH_BASE + 0x38500UL)  /* I2C channel 5 registers                */
#define FM3_MFS6_UART_BASE    (FM3_PERIPH_BASE + 0x38600UL)  /* UART asynchronous channel 6 registers  */
#define FM3_MFS6_CSIO_BASE    (FM3_PERIPH_BASE + 0x38600UL)  /* UART synchronous channel 6 registers   */
#define FM3_MFS6_LIN_BASE     (FM3_PERIPH_BASE + 0x38600UL)  /* UART LIN channel 6 registers           */
#define FM3_MFS6_I2C_BASE     (FM3_PERIPH_BASE + 0x38600UL)  /* I2C channel 6 registers                */
#define FM3_MFS7_UART_BASE    (FM3_PERIPH_BASE + 0x38700UL)  /* UART asynchronous channel 7 registers  */
#define FM3_MFS7_CSIO_BASE    (FM3_PERIPH_BASE + 0x38700UL)  /* UART synchronous channel 7 registers   */
#define FM3_MFS7_LIN_BASE     (FM3_PERIPH_BASE + 0x38700UL)  /* UART LIN channel 7 registers           */
#define FM3_MFS7_I2C_BASE     (FM3_PERIPH_BASE + 0x38700UL)  /* I2C channel 7 registers                */
#define FM3_CRC_BASE          (FM3_PERIPH_BASE + 0x39000UL)  /* CRC registers                          */
#define FM3_WC_BASE           (FM3_PERIPH_BASE + 0x3A000UL)  /* Watch counter registers                */
#define FM3_EXBUS_BASE        (FM3_PERIPH_BASE + 0x3F000UL)  /* External bus interface registers       */
#define FM3_USB0_BASE         (FM3_PERIPH_BASE + 0x42100UL)  /* USB channel 0 registers                */
#define FM3_DMAC_BASE         (FM3_PERIPH_BASE + 0x60000UL)  /* DMA controller                         */
#define FM3_CAN0_BASE         (FM3_PERIPH_BASE + 0x62000UL)  /* CAN channel 0 registers                */
#define FM3_CAN1_BASE         (FM3_PERIPH_BASE + 0x63000UL)  /* CAN channel 1 registers                */
