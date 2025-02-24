
/**
 * @file    CSP_Config.h
 * @author  Deadline039
 * @brief   The CSP configuration of STM32G4xx.
 * @version 1.0
 * @date    2025-02-05
 * @note    Generate Automatically.
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __CSP_CONFIG_H
#define __CSP_CONFIG_H

// <e> LPUART1 (Low power universal asynchronous receiver transmitter)

#define LPUART1_ENABLE 0 

#if LPUART1_ENABLE

//   <o> LPUART1_TX Pin
//       <0=>Not Used <1=>PA2 <2=>PB11 <3=>PC1 <4=>PG7 
#define LPUART1_TX_ID 0

#if (LPUART1_TX_ID == 0)
#define LPUART1_TX 0
#elif (LPUART1_TX_ID == 1)
#define LPUART1_TX 1
#define LPUART1_TX_PORT A
#define LPUART1_TX_PIN GPIO_PIN_2
#elif (LPUART1_TX_ID == 2)
#define LPUART1_TX 1
#define LPUART1_TX_PORT B
#define LPUART1_TX_PIN GPIO_PIN_11
#elif (LPUART1_TX_ID == 3)
#define LPUART1_TX 1
#define LPUART1_TX_PORT C
#define LPUART1_TX_PIN GPIO_PIN_1
#elif (LPUART1_TX_ID == 4)
#define LPUART1_TX 1
#define LPUART1_TX_PORT G
#define LPUART1_TX_PIN GPIO_PIN_7
#else   /* LPUART1_TX_ID */
#error "Invalid LPUART1_TX Pin Configuration! "
#endif  /* LPUART1_TX_ID */

//   <o> LPUART1_RX Pin
//       <0=>Not Used <1=>PA3 <2=>PB10 <3=>PC0 <4=>PG8 
#define LPUART1_RX_ID 0

#if (LPUART1_RX_ID == 0)
#define LPUART1_RX 0
#elif (LPUART1_RX_ID == 1)
#define LPUART1_RX 1
#define LPUART1_RX_PORT A
#define LPUART1_RX_PIN GPIO_PIN_3
#elif (LPUART1_RX_ID == 2)
#define LPUART1_RX 1
#define LPUART1_RX_PORT B
#define LPUART1_RX_PIN GPIO_PIN_10
#elif (LPUART1_RX_ID == 3)
#define LPUART1_RX 1
#define LPUART1_RX_PORT C
#define LPUART1_RX_PIN GPIO_PIN_0
#elif (LPUART1_RX_ID == 4)
#define LPUART1_RX 1
#define LPUART1_RX_PORT G
#define LPUART1_RX_PIN GPIO_PIN_8
#else   /* LPUART1_RX_ID */
#error "Invalid LPUART1_RX Pin Configuration! "
#endif  /* LPUART1_RX_ID */

//   <o> LPUART1_CTS Pin
//       <0=>Not Used <1=>PA6 <2=>PB13 <3=>PG5 
#define LPUART1_CTS_ID 0

#if (LPUART1_CTS_ID == 0)
#define LPUART1_CTS 0
#elif (LPUART1_CTS_ID == 1)
#define LPUART1_CTS 1
#define LPUART1_CTS_PORT A
#define LPUART1_CTS_PIN GPIO_PIN_6
#elif (LPUART1_CTS_ID == 2)
#define LPUART1_CTS 1
#define LPUART1_CTS_PORT B
#define LPUART1_CTS_PIN GPIO_PIN_13
#elif (LPUART1_CTS_ID == 3)
#define LPUART1_CTS 1
#define LPUART1_CTS_PORT G
#define LPUART1_CTS_PIN GPIO_PIN_5
#else   /* LPUART1_CTS_ID */
#error "Invalid LPUART1_CTS Pin Configuration! "
#endif  /* LPUART1_CTS_ID */

//   <o> LPUART1_RTS Pin
//       <0=>Not Used <1=>PB1 <2=>PB12 <3=>PG6 
#define LPUART1_RTS_ID 0

#if (LPUART1_RTS_ID == 0)
#define LPUART1_RTS 0
#elif (LPUART1_RTS_ID == 1)
#define LPUART1_RTS 1
#define LPUART1_RTS_PORT B
#define LPUART1_RTS_PIN GPIO_PIN_1
#elif (LPUART1_RTS_ID == 2)
#define LPUART1_RTS 1
#define LPUART1_RTS_PORT B
#define LPUART1_RTS_PIN GPIO_PIN_12
#elif (LPUART1_RTS_ID == 3)
#define LPUART1_RTS 1
#define LPUART1_RTS_PORT G
#define LPUART1_RTS_PIN GPIO_PIN_6
#else   /* LPUART1_RTS_ID */
#error "Invalid LPUART1_RTS Pin Configuration! "
#endif  /* LPUART1_RTS_ID */

//   <e> Enable LPUART1 Interrupt
#define LPUART1_IT_ENABLE 0

#if LPUART1_IT_ENABLE

//   <o> LPUART1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of LPUART1
#define LPUART1_IT_PRIORITY        2
//   <o> LPUART1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of LPUART1
#define LPUART1_IT_SUB             3

//   </e>
#endif /* LPUART1_IT_ENABLE */

//   <e> Enable LPUART1 DMA RX
#define LPUART1_RX_DMA             0

#if LPUART1_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define LPUART1_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define LPUART1_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define LPUART1_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define LPUART1_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define LPUART1_RX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define LPUART1_RX_DMA_BUF_SIZE    256

//     <o> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define LPUART1_RX_DMA_FIFO_SIZE   256

//   </e>

#endif  /* LPUART1_RX_DMA */

//   <e> Enable LPUART1 DMA TX
#define LPUART1_TX_DMA             0

#if LPUART1_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define LPUART1_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define LPUART1_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define LPUART1_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define LPUART1_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define LPUART1_TX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
#define LPUART1_TX_DMA_BUF_SIZE    256

//   </e>

#endif  /* LPUART1_TX_DMA */

#endif  /* LPUART1_ENABLE */
// </e>

// <e> USART1 (Universal asynchronous receiver transmitter)

#define USART1_ENABLE 1

#if USART1_ENABLE

//   <o> USART1_TX Pin
//       <0=>Not Used <1=>PA9 <2=>PB6 <3=>PC4 <4=>PE0 <5=>PG9 
#define USART1_TX_ID 1

#if (USART1_TX_ID == 0)
#define USART1_TX 0
#elif (USART1_TX_ID == 1)
#define USART1_TX 1
#define USART1_TX_PORT A
#define USART1_TX_PIN GPIO_PIN_9
#elif (USART1_TX_ID == 2)
#define USART1_TX 1
#define USART1_TX_PORT B
#define USART1_TX_PIN GPIO_PIN_6
#elif (USART1_TX_ID == 3)
#define USART1_TX 1
#define USART1_TX_PORT C
#define USART1_TX_PIN GPIO_PIN_4
#elif (USART1_TX_ID == 4)
#define USART1_TX 1
#define USART1_TX_PORT E
#define USART1_TX_PIN GPIO_PIN_0
#elif (USART1_TX_ID == 5)
#define USART1_TX 1
#define USART1_TX_PORT G
#define USART1_TX_PIN GPIO_PIN_9
#else   /* USART1_TX_ID */
#error "Invalid USART1_TX Pin Configuration! "
#endif  /* USART1_TX_ID */

//   <o> USART1_RX Pin
//       <0=>Not Used <1=>PA10 <2=>PB7 <3=>PC5 <4=>PE1 
#define USART1_RX_ID 1

#if (USART1_RX_ID == 0)
#define USART1_RX 0
#elif (USART1_RX_ID == 1)
#define USART1_RX 1
#define USART1_RX_PORT A
#define USART1_RX_PIN GPIO_PIN_10
#elif (USART1_RX_ID == 2)
#define USART1_RX 1
#define USART1_RX_PORT B
#define USART1_RX_PIN GPIO_PIN_7
#elif (USART1_RX_ID == 3)
#define USART1_RX 1
#define USART1_RX_PORT C
#define USART1_RX_PIN GPIO_PIN_5
#elif (USART1_RX_ID == 4)
#define USART1_RX 1
#define USART1_RX_PORT E
#define USART1_RX_PIN GPIO_PIN_1
#else   /* USART1_RX_ID */
#error "Invalid USART1_RX Pin Configuration! "
#endif  /* USART1_RX_ID */

//   <o> USART1_CTS Pin
//       <0=>Not Used <1=>PA11 
#define USART1_CTS_ID 0

#if (USART1_CTS_ID == 0)
#define USART1_CTS 0
#elif (USART1_CTS_ID == 1)
#define USART1_CTS 1
#define USART1_CTS_PORT A
#define USART1_CTS_PIN GPIO_PIN_11
#else   /* USART1_CTS_ID */
#error "Invalid USART1_CTS Pin Configuration! "
#endif  /* USART1_CTS_ID */

//   <o> USART1_RTS Pin
//       <0=>Not Used <1=>PA12 
#define USART1_RTS_ID 0

#if (USART1_RTS_ID == 0)
#define USART1_RTS 0
#elif (USART1_RTS_ID == 1)
#define USART1_RTS 1
#define USART1_RTS_PORT A
#define USART1_RTS_PIN GPIO_PIN_12
#else   /* USART1_RTS_ID */
#error "Invalid USART1_RTS Pin Configuration! "
#endif  /* USART1_RTS_ID */

//   <e> Enable USART1 Interrupt
#define USART1_IT_ENABLE 0

#if USART1_IT_ENABLE

//   <o> USART1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART1
#define USART1_IT_PRIORITY        2
//   <o> USART1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART1
#define USART1_IT_SUB             3

//   </e>
#endif /* USART1_IT_ENABLE */

//   <e> Enable USART1 DMA RX
#define USART1_RX_DMA             0

#if USART1_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define USART1_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define USART1_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define USART1_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define USART1_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define USART1_RX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define USART1_RX_DMA_BUF_SIZE    256

//     <o> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define USART1_RX_DMA_FIFO_SIZE   256

//   </e>

#endif  /* USART1_RX_DMA */

//   <e> Enable USART1 DMA TX
#define USART1_TX_DMA             0

#if USART1_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define USART1_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define USART1_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define USART1_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define USART1_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define USART1_TX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
#define USART1_TX_DMA_BUF_SIZE    256

//   </e>

#endif  /* USART1_TX_DMA */

#endif  /* USART1_ENABLE */
// </e>

// <e> USART2 (Universal asynchronous receiver transmitter)

#define USART2_ENABLE 0 

#if USART2_ENABLE

//   <o> USART2_TX Pin
//       <0=>Not Used <1=>PA2 <2=>PA14 <3=>PB3 <4=>PD5 
#define USART2_TX_ID 0

#if (USART2_TX_ID == 0)
#define USART2_TX 0
#elif (USART2_TX_ID == 1)
#define USART2_TX 1
#define USART2_TX_PORT A
#define USART2_TX_PIN GPIO_PIN_2
#elif (USART2_TX_ID == 2)
#define USART2_TX 1
#define USART2_TX_PORT A
#define USART2_TX_PIN GPIO_PIN_14
#elif (USART2_TX_ID == 3)
#define USART2_TX 1
#define USART2_TX_PORT B
#define USART2_TX_PIN GPIO_PIN_3
#elif (USART2_TX_ID == 4)
#define USART2_TX 1
#define USART2_TX_PORT D
#define USART2_TX_PIN GPIO_PIN_5
#else   /* USART2_TX_ID */
#error "Invalid USART2_TX Pin Configuration! "
#endif  /* USART2_TX_ID */

//   <o> USART2_RX Pin
//       <0=>Not Used <1=>PA3 <2=>PA15 <3=>PB4 <4=>PD6 
#define USART2_RX_ID 0

#if (USART2_RX_ID == 0)
#define USART2_RX 0
#elif (USART2_RX_ID == 1)
#define USART2_RX 1
#define USART2_RX_PORT A
#define USART2_RX_PIN GPIO_PIN_3
#elif (USART2_RX_ID == 2)
#define USART2_RX 1
#define USART2_RX_PORT A
#define USART2_RX_PIN GPIO_PIN_15
#elif (USART2_RX_ID == 3)
#define USART2_RX 1
#define USART2_RX_PORT B
#define USART2_RX_PIN GPIO_PIN_4
#elif (USART2_RX_ID == 4)
#define USART2_RX 1
#define USART2_RX_PORT D
#define USART2_RX_PIN GPIO_PIN_6
#else   /* USART2_RX_ID */
#error "Invalid USART2_RX Pin Configuration! "
#endif  /* USART2_RX_ID */

//   <o> USART2_CTS Pin
//       <0=>Not Used <1=>PA0 <2=>PD3 
#define USART2_CTS_ID 0

#if (USART2_CTS_ID == 0)
#define USART2_CTS 0
#elif (USART2_CTS_ID == 1)
#define USART2_CTS 1
#define USART2_CTS_PORT A
#define USART2_CTS_PIN GPIO_PIN_0
#elif (USART2_CTS_ID == 2)
#define USART2_CTS 1
#define USART2_CTS_PORT D
#define USART2_CTS_PIN GPIO_PIN_3
#else   /* USART2_CTS_ID */
#error "Invalid USART2_CTS Pin Configuration! "
#endif  /* USART2_CTS_ID */

//   <o> USART2_RTS Pin
//       <0=>Not Used <1=>PA1 <2=>PD4 
#define USART2_RTS_ID 0

#if (USART2_RTS_ID == 0)
#define USART2_RTS 0
#elif (USART2_RTS_ID == 1)
#define USART2_RTS 1
#define USART2_RTS_PORT A
#define USART2_RTS_PIN GPIO_PIN_1
#elif (USART2_RTS_ID == 2)
#define USART2_RTS 1
#define USART2_RTS_PORT D
#define USART2_RTS_PIN GPIO_PIN_4
#else   /* USART2_RTS_ID */
#error "Invalid USART2_RTS Pin Configuration! "
#endif  /* USART2_RTS_ID */

//   <e> Enable USART2 Interrupt
#define USART2_IT_ENABLE 0

#if USART2_IT_ENABLE

//   <o> USART2 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART2
#define USART2_IT_PRIORITY        2
//   <o> USART2 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART2
#define USART2_IT_SUB             3

//   </e>
#endif /* USART2_IT_ENABLE */

//   <e> Enable USART2 DMA RX
#define USART2_RX_DMA             0

#if USART2_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define USART2_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define USART2_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define USART2_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define USART2_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define USART2_RX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define USART2_RX_DMA_BUF_SIZE    256

//     <o> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define USART2_RX_DMA_FIFO_SIZE   256

//   </e>

#endif  /* USART2_RX_DMA */

//   <e> Enable USART2 DMA TX
#define USART2_TX_DMA             0

#if USART2_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define USART2_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define USART2_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define USART2_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define USART2_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define USART2_TX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
#define USART2_TX_DMA_BUF_SIZE    256

//   </e>

#endif  /* USART2_TX_DMA */

#endif  /* USART2_ENABLE */
// </e>

// <e> USART3 (Universal asynchronous receiver transmitter)

#define USART3_ENABLE 0 

#if USART3_ENABLE

//   <o> USART3_TX Pin
//       <0=>Not Used <1=>PB9 <2=>PB10 <3=>PC10 <4=>PD8 
#define USART3_TX_ID 0

#if (USART3_TX_ID == 0)
#define USART3_TX 0
#elif (USART3_TX_ID == 1)
#define USART3_TX 1
#define USART3_TX_PORT B
#define USART3_TX_PIN GPIO_PIN_9
#elif (USART3_TX_ID == 2)
#define USART3_TX 1
#define USART3_TX_PORT B
#define USART3_TX_PIN GPIO_PIN_10
#elif (USART3_TX_ID == 3)
#define USART3_TX 1
#define USART3_TX_PORT C
#define USART3_TX_PIN GPIO_PIN_10
#elif (USART3_TX_ID == 4)
#define USART3_TX 1
#define USART3_TX_PORT D
#define USART3_TX_PIN GPIO_PIN_8
#else   /* USART3_TX_ID */
#error "Invalid USART3_TX Pin Configuration! "
#endif  /* USART3_TX_ID */

//   <o> USART3_RX Pin
//       <0=>Not Used <1=>PB8 <2=>PB11 <3=>PC11 <4=>PD9 <5=>PE15 
#define USART3_RX_ID 0

#if (USART3_RX_ID == 0)
#define USART3_RX 0
#elif (USART3_RX_ID == 1)
#define USART3_RX 1
#define USART3_RX_PORT B
#define USART3_RX_PIN GPIO_PIN_8
#elif (USART3_RX_ID == 2)
#define USART3_RX 1
#define USART3_RX_PORT B
#define USART3_RX_PIN GPIO_PIN_11
#elif (USART3_RX_ID == 3)
#define USART3_RX 1
#define USART3_RX_PORT C
#define USART3_RX_PIN GPIO_PIN_11
#elif (USART3_RX_ID == 4)
#define USART3_RX 1
#define USART3_RX_PORT D
#define USART3_RX_PIN GPIO_PIN_9
#elif (USART3_RX_ID == 5)
#define USART3_RX 1
#define USART3_RX_PORT E
#define USART3_RX_PIN GPIO_PIN_15
#else   /* USART3_RX_ID */
#error "Invalid USART3_RX Pin Configuration! "
#endif  /* USART3_RX_ID */

//   <o> USART3_CTS Pin
//       <0=>Not Used <1=>PA13 <2=>PB13 <3=>PD11 
#define USART3_CTS_ID 0

#if (USART3_CTS_ID == 0)
#define USART3_CTS 0
#elif (USART3_CTS_ID == 1)
#define USART3_CTS 1
#define USART3_CTS_PORT A
#define USART3_CTS_PIN GPIO_PIN_13
#elif (USART3_CTS_ID == 2)
#define USART3_CTS 1
#define USART3_CTS_PORT B
#define USART3_CTS_PIN GPIO_PIN_13
#elif (USART3_CTS_ID == 3)
#define USART3_CTS 1
#define USART3_CTS_PORT D
#define USART3_CTS_PIN GPIO_PIN_11
#else   /* USART3_CTS_ID */
#error "Invalid USART3_CTS Pin Configuration! "
#endif  /* USART3_CTS_ID */

//   <o> USART3_RTS Pin
//       <0=>Not Used <1=>PB14 <2=>PD12 <3=>PF6 
#define USART3_RTS_ID 0

#if (USART3_RTS_ID == 0)
#define USART3_RTS 0
#elif (USART3_RTS_ID == 1)
#define USART3_RTS 1
#define USART3_RTS_PORT B
#define USART3_RTS_PIN GPIO_PIN_14
#elif (USART3_RTS_ID == 2)
#define USART3_RTS 1
#define USART3_RTS_PORT D
#define USART3_RTS_PIN GPIO_PIN_12
#elif (USART3_RTS_ID == 3)
#define USART3_RTS 1
#define USART3_RTS_PORT F
#define USART3_RTS_PIN GPIO_PIN_6
#else   /* USART3_RTS_ID */
#error "Invalid USART3_RTS Pin Configuration! "
#endif  /* USART3_RTS_ID */

//   <e> Enable USART3 Interrupt
#define USART3_IT_ENABLE 0

#if USART3_IT_ENABLE

//   <o> USART3 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART3
#define USART3_IT_PRIORITY        2
//   <o> USART3 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART3
#define USART3_IT_SUB             3

//   </e>
#endif /* USART3_IT_ENABLE */

//   <e> Enable USART3 DMA RX
#define USART3_RX_DMA             0

#if USART3_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define USART3_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define USART3_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define USART3_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define USART3_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define USART3_RX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define USART3_RX_DMA_BUF_SIZE    256

//     <o> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define USART3_RX_DMA_FIFO_SIZE   256

//   </e>

#endif  /* USART3_RX_DMA */

//   <e> Enable USART3 DMA TX
#define USART3_TX_DMA             0

#if USART3_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define USART3_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define USART3_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define USART3_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define USART3_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define USART3_TX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
#define USART3_TX_DMA_BUF_SIZE    256

//   </e>

#endif  /* USART3_TX_DMA */

#endif  /* USART3_ENABLE */
// </e>

// <e> UART4 (Universal synchronous asynchronous receiver transmitter)

#define UART4_ENABLE 0 

#if UART4_ENABLE

//   <o> UART4_TX Pin
//       <0=>Not Used <1=>PC10 
#define UART4_TX_ID 0

#if (UART4_TX_ID == 0)
#define UART4_TX 0
#elif (UART4_TX_ID == 1)
#define UART4_TX 1
#define UART4_TX_PORT C
#define UART4_TX_PIN GPIO_PIN_10
#else   /* UART4_TX_ID */
#error "Invalid UART4_TX Pin Configuration! "
#endif  /* UART4_TX_ID */

//   <o> UART4_RX Pin
//       <0=>Not Used <1=>PC11 
#define UART4_RX_ID 0

#if (UART4_RX_ID == 0)
#define UART4_RX 0
#elif (UART4_RX_ID == 1)
#define UART4_RX 1
#define UART4_RX_PORT C
#define UART4_RX_PIN GPIO_PIN_11
#else   /* UART4_RX_ID */
#error "Invalid UART4_RX Pin Configuration! "
#endif  /* UART4_RX_ID */

//   <o> UART4_CTS Pin
//       <0=>Not Used <1=>PB7 
#define UART4_CTS_ID 0

#if (UART4_CTS_ID == 0)
#define UART4_CTS 0
#elif (UART4_CTS_ID == 1)
#define UART4_CTS 1
#define UART4_CTS_PORT B
#define UART4_CTS_PIN GPIO_PIN_7
#else   /* UART4_CTS_ID */
#error "Invalid UART4_CTS Pin Configuration! "
#endif  /* UART4_CTS_ID */

//   <o> UART4_RTS Pin
//       <0=>Not Used <1=>PA15 
#define UART4_RTS_ID 0

#if (UART4_RTS_ID == 0)
#define UART4_RTS 0
#elif (UART4_RTS_ID == 1)
#define UART4_RTS 1
#define UART4_RTS_PORT A
#define UART4_RTS_PIN GPIO_PIN_15
#else   /* UART4_RTS_ID */
#error "Invalid UART4_RTS Pin Configuration! "
#endif  /* UART4_RTS_ID */

//   <e> Enable UART4 Interrupt
#define UART4_IT_ENABLE 0

#if UART4_IT_ENABLE

//   <o> UART4 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART4
#define UART4_IT_PRIORITY        2
//   <o> UART4 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART4
#define UART4_IT_SUB             3

//   </e>
#endif /* UART4_IT_ENABLE */

//   <e> Enable UART4 DMA RX
#define UART4_RX_DMA             0

#if UART4_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define UART4_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define UART4_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define UART4_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define UART4_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define UART4_RX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define UART4_RX_DMA_BUF_SIZE    256

//     <o> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define UART4_RX_DMA_FIFO_SIZE   256

//   </e>

#endif  /* UART4_RX_DMA */

//   <e> Enable UART4 DMA TX
#define UART4_TX_DMA             0

#if UART4_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define UART4_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define UART4_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define UART4_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define UART4_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define UART4_TX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
#define UART4_TX_DMA_BUF_SIZE    256

//   </e>

#endif  /* UART4_TX_DMA */

#endif  /* UART4_ENABLE */
// </e>

// <e> UART5 (Universal synchronous asynchronous receiver transmitter)

#define UART5_ENABLE 0 

#if UART5_ENABLE

//   <o> UART5_TX Pin
//       <0=>Not Used <1=>PC12 
#define UART5_TX_ID 0

#if (UART5_TX_ID == 0)
#define UART5_TX 0
#elif (UART5_TX_ID == 1)
#define UART5_TX 1
#define UART5_TX_PORT C
#define UART5_TX_PIN GPIO_PIN_12
#else   /* UART5_TX_ID */
#error "Invalid UART5_TX Pin Configuration! "
#endif  /* UART5_TX_ID */

//   <o> UART5_RX Pin
//       <0=>Not Used <1=>PD2 
#define UART5_RX_ID 0

#if (UART5_RX_ID == 0)
#define UART5_RX 0
#elif (UART5_RX_ID == 1)
#define UART5_RX 1
#define UART5_RX_PORT D
#define UART5_RX_PIN GPIO_PIN_2
#else   /* UART5_RX_ID */
#error "Invalid UART5_RX Pin Configuration! "
#endif  /* UART5_RX_ID */

//   <o> UART5_CTS Pin
//       <0=>Not Used <1=>PB5 
#define UART5_CTS_ID 0

#if (UART5_CTS_ID == 0)
#define UART5_CTS 0
#elif (UART5_CTS_ID == 1)
#define UART5_CTS 1
#define UART5_CTS_PORT B
#define UART5_CTS_PIN GPIO_PIN_5
#else   /* UART5_CTS_ID */
#error "Invalid UART5_CTS Pin Configuration! "
#endif  /* UART5_CTS_ID */

//   <o> UART5_RTS Pin
//       <0=>Not Used <1=>PB4 
#define UART5_RTS_ID 0

#if (UART5_RTS_ID == 0)
#define UART5_RTS 0
#elif (UART5_RTS_ID == 1)
#define UART5_RTS 1
#define UART5_RTS_PORT B
#define UART5_RTS_PIN GPIO_PIN_4
#else   /* UART5_RTS_ID */
#error "Invalid UART5_RTS Pin Configuration! "
#endif  /* UART5_RTS_ID */

//   <e> Enable UART5 Interrupt
#define UART5_IT_ENABLE 0

#if UART5_IT_ENABLE

//   <o> UART5 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART5
#define UART5_IT_PRIORITY        2
//   <o> UART5 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART5
#define UART5_IT_SUB             3

//   </e>
#endif /* UART5_IT_ENABLE */

//   <e> Enable UART5 DMA RX
#define UART5_RX_DMA             0

#if UART5_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define UART5_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define UART5_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define UART5_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define UART5_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define UART5_RX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define UART5_RX_DMA_BUF_SIZE    256

//     <o> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable UART Receive
#define UART5_RX_DMA_FIFO_SIZE   256

//   </e>

#endif  /* UART5_RX_DMA */

//   <e> Enable UART5 DMA TX
#define UART5_TX_DMA             0

#if UART5_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define UART5_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define UART5_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define UART5_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define UART5_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define UART5_TX_DMA_IT_SUB      2

//     <o> The size of Receive buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
#define UART5_TX_DMA_BUF_SIZE    256

//   </e>

#endif  /* UART5_TX_DMA */

#endif  /* UART5_ENABLE */
// </e>

// <e> QUADSPI1 (Quad Serial Peripheral Interface)
#define QUADSPI1_ENABLE  0

#if QUADSPI1_ENABLE

//   <o> QUADSPI1_CLK Pin
//       <0=>PA3<1=>PB10<2=>PE10<3=>PF10
#define QUADSPI1_CLK_ID 0

#if (QUADSPI1_CLK_ID == 0)
#define QUADSPI1_CLK_PORT A
#define QUADSPI1_CLK_PIN GPIO_PIN_3
#elif (QUADSPI1_CLK_ID == 1)
#define QUADSPI1_CLK_PORT B
#define QUADSPI1_CLK_PIN GPIO_PIN_10
#elif (QUADSPI1_CLK_ID == 2)
#define QUADSPI1_CLK_PORT E
#define QUADSPI1_CLK_PIN GPIO_PIN_10
#elif (QUADSPI1_CLK_ID == 3)
#define QUADSPI1_CLK_PORT F
#define QUADSPI1_CLK_PIN GPIO_PIN_10
#else   /* QUADSPI1_CLK_ID */
#error "Invalid QUADSPI1_CLK Pin Configuration! "
#endif  /* QUADSPI1_CLK_ID */

//  <e> QUADSPI1 Use Bank1
#define QUADSPI1_BANK1_ENABLE    0

#if QUADSPI1_BANK1_ENABLE

//   <o> QUADSPI1_BK1_IO0 Pin
//       <0=>Not Used <1=>PB1 <2=>PC1 <3=>PD4 <4=>PE12 <5=>PF8 
#define QUADSPI1_BK1_IO0_ID 0

#if (QUADSPI1_BK1_IO0_ID == 0)
#define QUADSPI1_BK1_IO0 0
#elif (QUADSPI1_BK1_IO0_ID == 1)
#define QUADSPI1_BK1_IO0 1
#define QUADSPI1_BK1_IO0_PORT B
#define QUADSPI1_BK1_IO0_PIN GPIO_PIN_1
#elif (QUADSPI1_BK1_IO0_ID == 2)
#define QUADSPI1_BK1_IO0 1
#define QUADSPI1_BK1_IO0_PORT C
#define QUADSPI1_BK1_IO0_PIN GPIO_PIN_1
#elif (QUADSPI1_BK1_IO0_ID == 3)
#define QUADSPI1_BK1_IO0 1
#define QUADSPI1_BK1_IO0_PORT D
#define QUADSPI1_BK1_IO0_PIN GPIO_PIN_4
#elif (QUADSPI1_BK1_IO0_ID == 4)
#define QUADSPI1_BK1_IO0 1
#define QUADSPI1_BK1_IO0_PORT E
#define QUADSPI1_BK1_IO0_PIN GPIO_PIN_12
#elif (QUADSPI1_BK1_IO0_ID == 5)
#define QUADSPI1_BK1_IO0 1
#define QUADSPI1_BK1_IO0_PORT F
#define QUADSPI1_BK1_IO0_PIN GPIO_PIN_8
#else   /* QUADSPI1_BK1_IO0_ID */
#error "Invalid QUADSPI1_BK1_IO0 Pin Configuration! "
#endif  /* QUADSPI1_BK1_IO0_ID */

//   <o> QUADSPI1_BK1_IO1 Pin
//       <0=>Not Used <1=>PB0 <2=>PB2 <3=>PC2 <4=>PD5 <5=>PE13 <6=>PF9 
#define QUADSPI1_BK1_IO1_ID 0

#if (QUADSPI1_BK1_IO1_ID == 0)
#define QUADSPI1_BK1_IO1 0
#elif (QUADSPI1_BK1_IO1_ID == 1)
#define QUADSPI1_BK1_IO1 1
#define QUADSPI1_BK1_IO1_PORT B
#define QUADSPI1_BK1_IO1_PIN GPIO_PIN_0
#elif (QUADSPI1_BK1_IO1_ID == 2)
#define QUADSPI1_BK1_IO1 1
#define QUADSPI1_BK1_IO1_PORT B
#define QUADSPI1_BK1_IO1_PIN GPIO_PIN_2
#elif (QUADSPI1_BK1_IO1_ID == 3)
#define QUADSPI1_BK1_IO1 1
#define QUADSPI1_BK1_IO1_PORT C
#define QUADSPI1_BK1_IO1_PIN GPIO_PIN_2
#elif (QUADSPI1_BK1_IO1_ID == 4)
#define QUADSPI1_BK1_IO1 1
#define QUADSPI1_BK1_IO1_PORT D
#define QUADSPI1_BK1_IO1_PIN GPIO_PIN_5
#elif (QUADSPI1_BK1_IO1_ID == 5)
#define QUADSPI1_BK1_IO1 1
#define QUADSPI1_BK1_IO1_PORT E
#define QUADSPI1_BK1_IO1_PIN GPIO_PIN_13
#elif (QUADSPI1_BK1_IO1_ID == 6)
#define QUADSPI1_BK1_IO1 1
#define QUADSPI1_BK1_IO1_PORT F
#define QUADSPI1_BK1_IO1_PIN GPIO_PIN_9
#else   /* QUADSPI1_BK1_IO1_ID */
#error "Invalid QUADSPI1_BK1_IO1 Pin Configuration! "
#endif  /* QUADSPI1_BK1_IO1_ID */

//   <o> QUADSPI1_BK1_IO2 Pin
//       <0=>Not Used <1=>PA7 <2=>PC3 <3=>PD6 <4=>PE14 <5=>PF7 
#define QUADSPI1_BK1_IO2_ID 0

#if (QUADSPI1_BK1_IO2_ID == 0)
#define QUADSPI1_BK1_IO2 0
#elif (QUADSPI1_BK1_IO2_ID == 1)
#define QUADSPI1_BK1_IO2 1
#define QUADSPI1_BK1_IO2_PORT A
#define QUADSPI1_BK1_IO2_PIN GPIO_PIN_7
#elif (QUADSPI1_BK1_IO2_ID == 2)
#define QUADSPI1_BK1_IO2 1
#define QUADSPI1_BK1_IO2_PORT C
#define QUADSPI1_BK1_IO2_PIN GPIO_PIN_3
#elif (QUADSPI1_BK1_IO2_ID == 3)
#define QUADSPI1_BK1_IO2 1
#define QUADSPI1_BK1_IO2_PORT D
#define QUADSPI1_BK1_IO2_PIN GPIO_PIN_6
#elif (QUADSPI1_BK1_IO2_ID == 4)
#define QUADSPI1_BK1_IO2 1
#define QUADSPI1_BK1_IO2_PORT E
#define QUADSPI1_BK1_IO2_PIN GPIO_PIN_14
#elif (QUADSPI1_BK1_IO2_ID == 5)
#define QUADSPI1_BK1_IO2 1
#define QUADSPI1_BK1_IO2_PORT F
#define QUADSPI1_BK1_IO2_PIN GPIO_PIN_7
#else   /* QUADSPI1_BK1_IO2_ID */
#error "Invalid QUADSPI1_BK1_IO2 Pin Configuration! "
#endif  /* QUADSPI1_BK1_IO2_ID */

//   <o> QUADSPI1_BK1_IO3 Pin
//       <0=>Not Used <1=>PA6 <2=>PC4 <3=>PD7 <4=>PE15 <5=>PF6 
#define QUADSPI1_BK1_IO3_ID 0

#if (QUADSPI1_BK1_IO3_ID == 0)
#define QUADSPI1_BK1_IO3 0
#elif (QUADSPI1_BK1_IO3_ID == 1)
#define QUADSPI1_BK1_IO3 1
#define QUADSPI1_BK1_IO3_PORT A
#define QUADSPI1_BK1_IO3_PIN GPIO_PIN_6
#elif (QUADSPI1_BK1_IO3_ID == 2)
#define QUADSPI1_BK1_IO3 1
#define QUADSPI1_BK1_IO3_PORT C
#define QUADSPI1_BK1_IO3_PIN GPIO_PIN_4
#elif (QUADSPI1_BK1_IO3_ID == 3)
#define QUADSPI1_BK1_IO3 1
#define QUADSPI1_BK1_IO3_PORT D
#define QUADSPI1_BK1_IO3_PIN GPIO_PIN_7
#elif (QUADSPI1_BK1_IO3_ID == 4)
#define QUADSPI1_BK1_IO3 1
#define QUADSPI1_BK1_IO3_PORT E
#define QUADSPI1_BK1_IO3_PIN GPIO_PIN_15
#elif (QUADSPI1_BK1_IO3_ID == 5)
#define QUADSPI1_BK1_IO3 1
#define QUADSPI1_BK1_IO3_PORT F
#define QUADSPI1_BK1_IO3_PIN GPIO_PIN_6
#else   /* QUADSPI1_BK1_IO3_ID */
#error "Invalid QUADSPI1_BK1_IO3 Pin Configuration! "
#endif  /* QUADSPI1_BK1_IO3_ID */

//   <o> QUADSPI1_BK1_NCS Pin
//       <0=>Not Used <1=>PA2 <2=>PB11 <3=>PD3 <4=>PE11 
#define QUADSPI1_BK1_NCS_ID 0

#if (QUADSPI1_BK1_NCS_ID == 0)
#define QUADSPI1_BK1_NCS 0
#elif (QUADSPI1_BK1_NCS_ID == 1)
#define QUADSPI1_BK1_NCS 1
#define QUADSPI1_BK1_NCS_PORT A
#define QUADSPI1_BK1_NCS_PIN GPIO_PIN_2
#elif (QUADSPI1_BK1_NCS_ID == 2)
#define QUADSPI1_BK1_NCS 1
#define QUADSPI1_BK1_NCS_PORT B
#define QUADSPI1_BK1_NCS_PIN GPIO_PIN_11
#elif (QUADSPI1_BK1_NCS_ID == 3)
#define QUADSPI1_BK1_NCS 1
#define QUADSPI1_BK1_NCS_PORT D
#define QUADSPI1_BK1_NCS_PIN GPIO_PIN_3
#elif (QUADSPI1_BK1_NCS_ID == 4)
#define QUADSPI1_BK1_NCS 1
#define QUADSPI1_BK1_NCS_PORT E
#define QUADSPI1_BK1_NCS_PIN GPIO_PIN_11
#else   /* QUADSPI1_BK1_NCS_ID */
#error "Invalid QUADSPI1_BK1_NCS Pin Configuration! "
#endif  /* QUADSPI1_BK1_NCS_ID */

#endif  /* QUADSPI1_BANK1_ENABLE */
// </e>

//  <e> QUADSPI1 Use Bank2
#define QUADSPI1_BANK2_ENABLE    0

#if QUADSPI1_BANK2_ENABLE

//   <o> QUADSPI1_BK2_IO0 Pin
//       <0=>Not Used <1=>PB1 <2=>PC1 <3=>PD4 <4=>PE12 <5=>PF8 
#define QUADSPI1_BK2_IO0_ID 0

#if (QUADSPI1_BK2_IO0_ID == 0)
#define QUADSPI1_BK2_IO0 0
#elif (QUADSPI1_BK2_IO0_ID == 1)
#define QUADSPI1_BK2_IO0 1
#define QUADSPI1_BK2_IO0_PORT B
#define QUADSPI1_BK2_IO0_PIN GPIO_PIN_1
#elif (QUADSPI1_BK2_IO0_ID == 2)
#define QUADSPI1_BK2_IO0 1
#define QUADSPI1_BK2_IO0_PORT C
#define QUADSPI1_BK2_IO0_PIN GPIO_PIN_1
#elif (QUADSPI1_BK2_IO0_ID == 3)
#define QUADSPI1_BK2_IO0 1
#define QUADSPI1_BK2_IO0_PORT D
#define QUADSPI1_BK2_IO0_PIN GPIO_PIN_4
#elif (QUADSPI1_BK2_IO0_ID == 4)
#define QUADSPI1_BK2_IO0 1
#define QUADSPI1_BK2_IO0_PORT E
#define QUADSPI1_BK2_IO0_PIN GPIO_PIN_12
#elif (QUADSPI1_BK2_IO0_ID == 5)
#define QUADSPI1_BK2_IO0 1
#define QUADSPI1_BK2_IO0_PORT F
#define QUADSPI1_BK2_IO0_PIN GPIO_PIN_8
#else   /* QUADSPI1_BK2_IO0_ID */
#error "Invalid QUADSPI1_BK2_IO0 Pin Configuration! "
#endif  /* QUADSPI1_BK2_IO0_ID */

//   <o> QUADSPI1_BK2_IO1 Pin
//       <0=>Not Used <1=>PB0 <2=>PB2 <3=>PC2 <4=>PD5 <5=>PE13 <6=>PF9 
#define QUADSPI1_BK2_IO1_ID 0

#if (QUADSPI1_BK2_IO1_ID == 0)
#define QUADSPI1_BK2_IO1 0
#elif (QUADSPI1_BK2_IO1_ID == 1)
#define QUADSPI1_BK2_IO1 1
#define QUADSPI1_BK2_IO1_PORT B
#define QUADSPI1_BK2_IO1_PIN GPIO_PIN_0
#elif (QUADSPI1_BK2_IO1_ID == 2)
#define QUADSPI1_BK2_IO1 1
#define QUADSPI1_BK2_IO1_PORT B
#define QUADSPI1_BK2_IO1_PIN GPIO_PIN_2
#elif (QUADSPI1_BK2_IO1_ID == 3)
#define QUADSPI1_BK2_IO1 1
#define QUADSPI1_BK2_IO1_PORT C
#define QUADSPI1_BK2_IO1_PIN GPIO_PIN_2
#elif (QUADSPI1_BK2_IO1_ID == 4)
#define QUADSPI1_BK2_IO1 1
#define QUADSPI1_BK2_IO1_PORT D
#define QUADSPI1_BK2_IO1_PIN GPIO_PIN_5
#elif (QUADSPI1_BK2_IO1_ID == 5)
#define QUADSPI1_BK2_IO1 1
#define QUADSPI1_BK2_IO1_PORT E
#define QUADSPI1_BK2_IO1_PIN GPIO_PIN_13
#elif (QUADSPI1_BK2_IO1_ID == 6)
#define QUADSPI1_BK2_IO1 1
#define QUADSPI1_BK2_IO1_PORT F
#define QUADSPI1_BK2_IO1_PIN GPIO_PIN_9
#else   /* QUADSPI1_BK2_IO1_ID */
#error "Invalid QUADSPI1_BK2_IO1 Pin Configuration! "
#endif  /* QUADSPI1_BK2_IO1_ID */

//   <o> QUADSPI1_BK2_IO2 Pin
//       <0=>Not Used <1=>PA7 <2=>PC3 <3=>PD6 <4=>PE14 <5=>PF7 
#define QUADSPI1_BK2_IO2_ID 0

#if (QUADSPI1_BK2_IO2_ID == 0)
#define QUADSPI1_BK2_IO2 0
#elif (QUADSPI1_BK2_IO2_ID == 1)
#define QUADSPI1_BK2_IO2 1
#define QUADSPI1_BK2_IO2_PORT A
#define QUADSPI1_BK2_IO2_PIN GPIO_PIN_7
#elif (QUADSPI1_BK2_IO2_ID == 2)
#define QUADSPI1_BK2_IO2 1
#define QUADSPI1_BK2_IO2_PORT C
#define QUADSPI1_BK2_IO2_PIN GPIO_PIN_3
#elif (QUADSPI1_BK2_IO2_ID == 3)
#define QUADSPI1_BK2_IO2 1
#define QUADSPI1_BK2_IO2_PORT D
#define QUADSPI1_BK2_IO2_PIN GPIO_PIN_6
#elif (QUADSPI1_BK2_IO2_ID == 4)
#define QUADSPI1_BK2_IO2 1
#define QUADSPI1_BK2_IO2_PORT E
#define QUADSPI1_BK2_IO2_PIN GPIO_PIN_14
#elif (QUADSPI1_BK2_IO2_ID == 5)
#define QUADSPI1_BK2_IO2 1
#define QUADSPI1_BK2_IO2_PORT F
#define QUADSPI1_BK2_IO2_PIN GPIO_PIN_7
#else   /* QUADSPI1_BK2_IO2_ID */
#error "Invalid QUADSPI1_BK2_IO2 Pin Configuration! "
#endif  /* QUADSPI1_BK2_IO2_ID */

//   <o> QUADSPI1_BK2_IO3 Pin
//       <0=>Not Used <1=>PA6 <2=>PC4 <3=>PD7 <4=>PE15 <5=>PF6 
#define QUADSPI1_BK2_IO3_ID 0

#if (QUADSPI1_BK2_IO3_ID == 0)
#define QUADSPI1_BK2_IO3 0
#elif (QUADSPI1_BK2_IO3_ID == 1)
#define QUADSPI1_BK2_IO3 1
#define QUADSPI1_BK2_IO3_PORT A
#define QUADSPI1_BK2_IO3_PIN GPIO_PIN_6
#elif (QUADSPI1_BK2_IO3_ID == 2)
#define QUADSPI1_BK2_IO3 1
#define QUADSPI1_BK2_IO3_PORT C
#define QUADSPI1_BK2_IO3_PIN GPIO_PIN_4
#elif (QUADSPI1_BK2_IO3_ID == 3)
#define QUADSPI1_BK2_IO3 1
#define QUADSPI1_BK2_IO3_PORT D
#define QUADSPI1_BK2_IO3_PIN GPIO_PIN_7
#elif (QUADSPI1_BK2_IO3_ID == 4)
#define QUADSPI1_BK2_IO3 1
#define QUADSPI1_BK2_IO3_PORT E
#define QUADSPI1_BK2_IO3_PIN GPIO_PIN_15
#elif (QUADSPI1_BK2_IO3_ID == 5)
#define QUADSPI1_BK2_IO3 1
#define QUADSPI1_BK2_IO3_PORT F
#define QUADSPI1_BK2_IO3_PIN GPIO_PIN_6
#else   /* QUADSPI1_BK2_IO3_ID */
#error "Invalid QUADSPI1_BK2_IO3 Pin Configuration! "
#endif  /* QUADSPI1_BK2_IO3_ID */

//   <o> QUADSPI1_BK2_NCS Pin
//       <0=>Not Used <1=>PA2 <2=>PB11 <3=>PD3 <4=>PE11 
#define QUADSPI1_BK2_NCS_ID 0

#if (QUADSPI1_BK2_NCS_ID == 0)
#define QUADSPI1_BK2_NCS 0
#elif (QUADSPI1_BK2_NCS_ID == 1)
#define QUADSPI1_BK2_NCS 1
#define QUADSPI1_BK2_NCS_PORT A
#define QUADSPI1_BK2_NCS_PIN GPIO_PIN_2
#elif (QUADSPI1_BK2_NCS_ID == 2)
#define QUADSPI1_BK2_NCS 1
#define QUADSPI1_BK2_NCS_PORT B
#define QUADSPI1_BK2_NCS_PIN GPIO_PIN_11
#elif (QUADSPI1_BK2_NCS_ID == 3)
#define QUADSPI1_BK2_NCS 1
#define QUADSPI1_BK2_NCS_PORT D
#define QUADSPI1_BK2_NCS_PIN GPIO_PIN_3
#elif (QUADSPI1_BK2_NCS_ID == 4)
#define QUADSPI1_BK2_NCS 1
#define QUADSPI1_BK2_NCS_PORT E
#define QUADSPI1_BK2_NCS_PIN GPIO_PIN_11
#else   /* QUADSPI1_BK2_NCS_ID */
#error "Invalid QUADSPI1_BK2_NCS Pin Configuration! "
#endif  /* QUADSPI1_BK2_NCS_ID */

#endif  /* QUADSPI1_BANK2_ENABLE */
// </e>

//   <e> Enable QUADSPI1 Interrupt
#define QUADSPI1_IT_ENABLE 0

#if QUADSPI1_IT_ENABLE

//   <o> QUADSPI1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of QUADSPI1
#define QUADSPI1_IT_PRIORITY        2
//   <o> QUADSPI1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of QUADSPI1
#define QUADSPI1_IT_SUB             3

//   </e>
#endif /* QUADSPI1_IT_ENABLE */

//   <e> Enable QUADSPI1 DMA 
#define QUADSPI1_DMA             0

#if QUADSPI1_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define QUADSPI1_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define QUADSPI1_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define QUADSPI1_DMA_PRIORITY    1

//     <o> DMA  Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define QUADSPI1_DMA_IT_PRIORITY 2

//     <o> DMA  Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define QUADSPI1_DMA_IT_SUB      2

//  <o> Direction
//   <DMA_MEMORY_TO_PERIPH=> Transmit
//   <DMA_PERIPH_TO_MEMORY=> Receive
#define QUADSPI1_DMA_DIRECTION DMA_MEMORY_TO_PERIPH

//   </e>

#endif  /* QUADSPI1_DMA */

#endif  /* QUADSPI1_ENABLE */
// </e>

// <e> SPI1 (Serial Peripheral Interface)
#define SPI1_ENABLE  0

#if SPI1_ENABLE

//   <o> SPI1_MISO Pin
//       <0=>Not Used <1=>PA6 <2=>PB4 <3=>PG3 
#define SPI1_MISO_ID 0

#if (SPI1_MISO_ID == 0)
#define SPI1_MISO 0
#elif (SPI1_MISO_ID == 1)
#define SPI1_MISO 1
#define SPI1_MISO_PORT A
#define SPI1_MISO_PIN GPIO_PIN_6
#elif (SPI1_MISO_ID == 2)
#define SPI1_MISO 1
#define SPI1_MISO_PORT B
#define SPI1_MISO_PIN GPIO_PIN_4
#elif (SPI1_MISO_ID == 3)
#define SPI1_MISO 1
#define SPI1_MISO_PORT G
#define SPI1_MISO_PIN GPIO_PIN_3
#else   /* SPI1_MISO_ID */
#error "Invalid SPI1_MISO Pin Configuration! "
#endif  /* SPI1_MISO_ID */

//   <o> SPI1_MOSI Pin
//       <0=>Not Used <1=>PA7 <2=>PB5 <3=>PG4 
#define SPI1_MOSI_ID 0

#if (SPI1_MOSI_ID == 0)
#define SPI1_MOSI 0
#elif (SPI1_MOSI_ID == 1)
#define SPI1_MOSI 1
#define SPI1_MOSI_PORT A
#define SPI1_MOSI_PIN GPIO_PIN_7
#elif (SPI1_MOSI_ID == 2)
#define SPI1_MOSI 1
#define SPI1_MOSI_PORT B
#define SPI1_MOSI_PIN GPIO_PIN_5
#elif (SPI1_MOSI_ID == 3)
#define SPI1_MOSI 1
#define SPI1_MOSI_PORT G
#define SPI1_MOSI_PIN GPIO_PIN_4
#else   /* SPI1_MOSI_ID */
#error "Invalid SPI1_MOSI Pin Configuration! "
#endif  /* SPI1_MOSI_ID */

//   <o> SPI1_NSS Pin
//       <0=>Not Used <1=>PA4 <2=>PA15 <3=>PG5 
#define SPI1_NSS_ID 0

#if (SPI1_NSS_ID == 0)
#define SPI1_NSS 0
#elif (SPI1_NSS_ID == 1)
#define SPI1_NSS 1
#define SPI1_NSS_PORT A
#define SPI1_NSS_PIN GPIO_PIN_4
#elif (SPI1_NSS_ID == 2)
#define SPI1_NSS 1
#define SPI1_NSS_PORT A
#define SPI1_NSS_PIN GPIO_PIN_15
#elif (SPI1_NSS_ID == 3)
#define SPI1_NSS 1
#define SPI1_NSS_PORT G
#define SPI1_NSS_PIN GPIO_PIN_5
#else   /* SPI1_NSS_ID */
#error "Invalid SPI1_NSS Pin Configuration! "
#endif  /* SPI1_NSS_ID */

//   <o> SPI1_SCK Pin
//       <0=>PA5<1=>PB3<2=>PG2
#define SPI1_SCK_ID 0

#if (SPI1_SCK_ID == 0)
#define SPI1_SCK_PORT A
#define SPI1_SCK_PIN GPIO_PIN_5
#elif (SPI1_SCK_ID == 1)
#define SPI1_SCK_PORT B
#define SPI1_SCK_PIN GPIO_PIN_3
#elif (SPI1_SCK_ID == 2)
#define SPI1_SCK_PORT G
#define SPI1_SCK_PIN GPIO_PIN_2
#else   /* SPI1_SCK_ID */
#error "Invalid SPI1_SCK Pin Configuration! "
#endif  /* SPI1_SCK_ID */

//   <e> Enable SPI1 Interrupt
#define SPI1_IT_ENABLE 0

#if SPI1_IT_ENABLE

//   <o> SPI1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of SPI1
#define SPI1_IT_PRIORITY        2
//   <o> SPI1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of SPI1
#define SPI1_IT_SUB             3

//   </e>
#endif /* SPI1_IT_ENABLE */

//   <e> Enable SPI1 DMA TX
#define SPI1_TX_DMA             0

#if SPI1_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI1_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI1_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI1_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI1_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI1_TX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI1_TX_DMA */

//   <e> Enable SPI1 DMA RX
#define SPI1_RX_DMA             0

#if SPI1_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI1_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI1_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI1_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI1_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI1_RX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI1_RX_DMA */

#endif  /* SPI1_ENABLE */
// </e>

// <e> SPI2 (Serial Peripheral Interface)
#define SPI2_ENABLE  0

#if SPI2_ENABLE

//   <o> SPI2_MISO Pin
//       <0=>Not Used <1=>PA10 <2=>PB14 
#define SPI2_MISO_ID 0

#if (SPI2_MISO_ID == 0)
#define SPI2_MISO 0
#elif (SPI2_MISO_ID == 1)
#define SPI2_MISO 1
#define SPI2_MISO_PORT A
#define SPI2_MISO_PIN GPIO_PIN_10
#elif (SPI2_MISO_ID == 2)
#define SPI2_MISO 1
#define SPI2_MISO_PORT B
#define SPI2_MISO_PIN GPIO_PIN_14
#else   /* SPI2_MISO_ID */
#error "Invalid SPI2_MISO Pin Configuration! "
#endif  /* SPI2_MISO_ID */

//   <o> SPI2_MOSI Pin
//       <0=>Not Used <1=>PA11 <2=>PB15 
#define SPI2_MOSI_ID 0

#if (SPI2_MOSI_ID == 0)
#define SPI2_MOSI 0
#elif (SPI2_MOSI_ID == 1)
#define SPI2_MOSI 1
#define SPI2_MOSI_PORT A
#define SPI2_MOSI_PIN GPIO_PIN_11
#elif (SPI2_MOSI_ID == 2)
#define SPI2_MOSI 1
#define SPI2_MOSI_PORT B
#define SPI2_MOSI_PIN GPIO_PIN_15
#else   /* SPI2_MOSI_ID */
#error "Invalid SPI2_MOSI Pin Configuration! "
#endif  /* SPI2_MOSI_ID */

//   <o> SPI2_NSS Pin
//       <0=>Not Used <1=>PB12 <2=>PD15 <3=>PF0 
#define SPI2_NSS_ID 0

#if (SPI2_NSS_ID == 0)
#define SPI2_NSS 0
#elif (SPI2_NSS_ID == 1)
#define SPI2_NSS 1
#define SPI2_NSS_PORT B
#define SPI2_NSS_PIN GPIO_PIN_12
#elif (SPI2_NSS_ID == 2)
#define SPI2_NSS 1
#define SPI2_NSS_PORT D
#define SPI2_NSS_PIN GPIO_PIN_15
#elif (SPI2_NSS_ID == 3)
#define SPI2_NSS 1
#define SPI2_NSS_PORT F
#define SPI2_NSS_PIN GPIO_PIN_0
#else   /* SPI2_NSS_ID */
#error "Invalid SPI2_NSS Pin Configuration! "
#endif  /* SPI2_NSS_ID */

//   <o> SPI2_SCK Pin
//       <0=>PB13<1=>PF1<2=>PF9<3=>PF10
#define SPI2_SCK_ID 0

#if (SPI2_SCK_ID == 0)
#define SPI2_SCK_PORT B
#define SPI2_SCK_PIN GPIO_PIN_13
#elif (SPI2_SCK_ID == 1)
#define SPI2_SCK_PORT F
#define SPI2_SCK_PIN GPIO_PIN_1
#elif (SPI2_SCK_ID == 2)
#define SPI2_SCK_PORT F
#define SPI2_SCK_PIN GPIO_PIN_9
#elif (SPI2_SCK_ID == 3)
#define SPI2_SCK_PORT F
#define SPI2_SCK_PIN GPIO_PIN_10
#else   /* SPI2_SCK_ID */
#error "Invalid SPI2_SCK Pin Configuration! "
#endif  /* SPI2_SCK_ID */

//   <e> Enable SPI2 Interrupt
#define SPI2_IT_ENABLE 0

#if SPI2_IT_ENABLE

//   <o> SPI2 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of SPI2
#define SPI2_IT_PRIORITY        2
//   <o> SPI2 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of SPI2
#define SPI2_IT_SUB             3

//   </e>
#endif /* SPI2_IT_ENABLE */

//   <e> Enable SPI2 DMA TX
#define SPI2_TX_DMA             0

#if SPI2_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI2_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI2_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI2_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI2_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI2_TX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI2_TX_DMA */

//   <e> Enable SPI2 DMA RX
#define SPI2_RX_DMA             0

#if SPI2_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI2_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI2_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI2_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI2_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI2_RX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI2_RX_DMA */

#endif  /* SPI2_ENABLE */
// </e>

// <e> SPI3 (Serial Peripheral Interface)
#define SPI3_ENABLE  0

#if SPI3_ENABLE

//   <o> SPI3_MISO Pin
//       <0=>Not Used <1=>PB4 <2=>PC11 
#define SPI3_MISO_ID 0

#if (SPI3_MISO_ID == 0)
#define SPI3_MISO 0
#elif (SPI3_MISO_ID == 1)
#define SPI3_MISO 1
#define SPI3_MISO_PORT B
#define SPI3_MISO_PIN GPIO_PIN_4
#elif (SPI3_MISO_ID == 2)
#define SPI3_MISO 1
#define SPI3_MISO_PORT C
#define SPI3_MISO_PIN GPIO_PIN_11
#else   /* SPI3_MISO_ID */
#error "Invalid SPI3_MISO Pin Configuration! "
#endif  /* SPI3_MISO_ID */

//   <o> SPI3_MOSI Pin
//       <0=>Not Used <1=>PB5 <2=>PC12 
#define SPI3_MOSI_ID 0

#if (SPI3_MOSI_ID == 0)
#define SPI3_MOSI 0
#elif (SPI3_MOSI_ID == 1)
#define SPI3_MOSI 1
#define SPI3_MOSI_PORT B
#define SPI3_MOSI_PIN GPIO_PIN_5
#elif (SPI3_MOSI_ID == 2)
#define SPI3_MOSI 1
#define SPI3_MOSI_PORT C
#define SPI3_MOSI_PIN GPIO_PIN_12
#else   /* SPI3_MOSI_ID */
#error "Invalid SPI3_MOSI Pin Configuration! "
#endif  /* SPI3_MOSI_ID */

//   <o> SPI3_NSS Pin
//       <0=>Not Used <1=>PA4 <2=>PA15 
#define SPI3_NSS_ID 0

#if (SPI3_NSS_ID == 0)
#define SPI3_NSS 0
#elif (SPI3_NSS_ID == 1)
#define SPI3_NSS 1
#define SPI3_NSS_PORT A
#define SPI3_NSS_PIN GPIO_PIN_4
#elif (SPI3_NSS_ID == 2)
#define SPI3_NSS 1
#define SPI3_NSS_PORT A
#define SPI3_NSS_PIN GPIO_PIN_15
#else   /* SPI3_NSS_ID */
#error "Invalid SPI3_NSS Pin Configuration! "
#endif  /* SPI3_NSS_ID */

//   <o> SPI3_SCK Pin
//       <0=>PB3<1=>PC10<2=>PG9
#define SPI3_SCK_ID 0

#if (SPI3_SCK_ID == 0)
#define SPI3_SCK_PORT B
#define SPI3_SCK_PIN GPIO_PIN_3
#elif (SPI3_SCK_ID == 1)
#define SPI3_SCK_PORT C
#define SPI3_SCK_PIN GPIO_PIN_10
#elif (SPI3_SCK_ID == 2)
#define SPI3_SCK_PORT G
#define SPI3_SCK_PIN GPIO_PIN_9
#else   /* SPI3_SCK_ID */
#error "Invalid SPI3_SCK Pin Configuration! "
#endif  /* SPI3_SCK_ID */

//   <e> Enable SPI3 Interrupt
#define SPI3_IT_ENABLE 0

#if SPI3_IT_ENABLE

//   <o> SPI3 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of SPI3
#define SPI3_IT_PRIORITY        2
//   <o> SPI3 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of SPI3
#define SPI3_IT_SUB             3

//   </e>
#endif /* SPI3_IT_ENABLE */

//   <e> Enable SPI3 DMA TX
#define SPI3_TX_DMA             0

#if SPI3_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI3_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI3_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI3_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI3_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI3_TX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI3_TX_DMA */

//   <e> Enable SPI3 DMA RX
#define SPI3_RX_DMA             0

#if SPI3_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI3_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI3_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI3_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI3_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI3_RX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI3_RX_DMA */

#endif  /* SPI3_ENABLE */
// </e>

// <e> SPI4 (Serial Peripheral Interface)
#define SPI4_ENABLE  0

#if SPI4_ENABLE

//   <o> SPI4_MISO Pin
//       <0=>Not Used <1=>PE5 <2=>PE13 
#define SPI4_MISO_ID 0

#if (SPI4_MISO_ID == 0)
#define SPI4_MISO 0
#elif (SPI4_MISO_ID == 1)
#define SPI4_MISO 1
#define SPI4_MISO_PORT E
#define SPI4_MISO_PIN GPIO_PIN_5
#elif (SPI4_MISO_ID == 2)
#define SPI4_MISO 1
#define SPI4_MISO_PORT E
#define SPI4_MISO_PIN GPIO_PIN_13
#else   /* SPI4_MISO_ID */
#error "Invalid SPI4_MISO Pin Configuration! "
#endif  /* SPI4_MISO_ID */

//   <o> SPI4_MOSI Pin
//       <0=>Not Used <1=>PE6 <2=>PE14 
#define SPI4_MOSI_ID 0

#if (SPI4_MOSI_ID == 0)
#define SPI4_MOSI 0
#elif (SPI4_MOSI_ID == 1)
#define SPI4_MOSI 1
#define SPI4_MOSI_PORT E
#define SPI4_MOSI_PIN GPIO_PIN_6
#elif (SPI4_MOSI_ID == 2)
#define SPI4_MOSI 1
#define SPI4_MOSI_PORT E
#define SPI4_MOSI_PIN GPIO_PIN_14
#else   /* SPI4_MOSI_ID */
#error "Invalid SPI4_MOSI Pin Configuration! "
#endif  /* SPI4_MOSI_ID */

//   <o> SPI4_NSS Pin
//       <0=>Not Used <1=>PE3 <2=>PE4 <3=>PE11 
#define SPI4_NSS_ID 0

#if (SPI4_NSS_ID == 0)
#define SPI4_NSS 0
#elif (SPI4_NSS_ID == 1)
#define SPI4_NSS 1
#define SPI4_NSS_PORT E
#define SPI4_NSS_PIN GPIO_PIN_3
#elif (SPI4_NSS_ID == 2)
#define SPI4_NSS 1
#define SPI4_NSS_PORT E
#define SPI4_NSS_PIN GPIO_PIN_4
#elif (SPI4_NSS_ID == 3)
#define SPI4_NSS 1
#define SPI4_NSS_PORT E
#define SPI4_NSS_PIN GPIO_PIN_11
#else   /* SPI4_NSS_ID */
#error "Invalid SPI4_NSS Pin Configuration! "
#endif  /* SPI4_NSS_ID */

//   <o> SPI4_SCK Pin
//       <0=>PE2<1=>PE12
#define SPI4_SCK_ID 0

#if (SPI4_SCK_ID == 0)
#define SPI4_SCK_PORT E
#define SPI4_SCK_PIN GPIO_PIN_2
#elif (SPI4_SCK_ID == 1)
#define SPI4_SCK_PORT E
#define SPI4_SCK_PIN GPIO_PIN_12
#else   /* SPI4_SCK_ID */
#error "Invalid SPI4_SCK Pin Configuration! "
#endif  /* SPI4_SCK_ID */

//   <e> Enable SPI4 Interrupt
#define SPI4_IT_ENABLE 0

#if SPI4_IT_ENABLE

//   <o> SPI4 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of SPI4
#define SPI4_IT_PRIORITY        2
//   <o> SPI4 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of SPI4
#define SPI4_IT_SUB             3

//   </e>
#endif /* SPI4_IT_ENABLE */

//   <e> Enable SPI4 DMA TX
#define SPI4_TX_DMA             0

#if SPI4_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI4_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI4_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI4_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI4_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI4_TX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI4_TX_DMA */

//   <e> Enable SPI4 DMA RX
#define SPI4_RX_DMA             0

#if SPI4_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define SPI4_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define SPI4_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define SPI4_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define SPI4_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define SPI4_RX_DMA_IT_SUB      2

//   </e>

#endif  /* SPI4_RX_DMA */

#endif  /* SPI4_ENABLE */
// </e>

// <e> I2C1 (Inter-integrated Circuit Interface)
#define I2C1_ENABLE  0

#if I2C1_ENABLE

//   <o> I2C1_SCL Pin
//       <0=>PA13<1=>PA15<2=>PB8<3=>PB6
#define I2C1_SCL_ID 0

#if (I2C1_SCL_ID == 0)
#define I2C1_SCL_PORT A
#define I2C1_SCL_PIN GPIO_PIN_13
#elif (I2C1_SCL_ID == 1)
#define I2C1_SCL_PORT A
#define I2C1_SCL_PIN GPIO_PIN_15
#elif (I2C1_SCL_ID == 2)
#define I2C1_SCL_PORT B
#define I2C1_SCL_PIN GPIO_PIN_8
#elif (I2C1_SCL_ID == 3)
#define I2C1_SCL_PORT B
#define I2C1_SCL_PIN GPIO_PIN_6
#else   /* I2C1_SCL_ID */
#error "Invalid I2C1_SCL Pin Configuration! "
#endif  /* I2C1_SCL_ID */

//   <o> I2C1_SDA Pin
//       <0=>PA14<1=>PB7<2=>PB9
#define I2C1_SDA_ID 0

#if (I2C1_SDA_ID == 0)
#define I2C1_SDA_PORT A
#define I2C1_SDA_PIN GPIO_PIN_14
#elif (I2C1_SDA_ID == 1)
#define I2C1_SDA_PORT B
#define I2C1_SDA_PIN GPIO_PIN_7
#elif (I2C1_SDA_ID == 2)
#define I2C1_SDA_PORT B
#define I2C1_SDA_PIN GPIO_PIN_9
#else   /* I2C1_SDA_ID */
#error "Invalid I2C1_SDA Pin Configuration! "
#endif  /* I2C1_SDA_ID */

//   <e> Enable I2C1 Interrupt
#define I2C1_IT_ENABLE 0

#if I2C1_IT_ENABLE

//   <o> I2C1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of I2C1
#define I2C1_IT_PRIORITY        2
//   <o> I2C1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of I2C1
#define I2C1_IT_SUB             3

//   </e>
#endif /* I2C1_IT_ENABLE */

//   <e> Enable I2C1 DMA TX
#define I2C1_TX_DMA             0

#if I2C1_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C1_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C1_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C1_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C1_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C1_TX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C1_TX_DMA */

//   <e> Enable I2C1 DMA RX
#define I2C1_RX_DMA             0

#if I2C1_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C1_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C1_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C1_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C1_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C1_RX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C1_RX_DMA */

#endif  /* I2C1_ENABLE */
// </e>

// <e> I2C2 (Inter-integrated Circuit Interface)
#define I2C2_ENABLE  0

#if I2C2_ENABLE

//   <o> I2C2_SCL Pin
//       <0=>PA9<1=>PC4<2=>PF6
#define I2C2_SCL_ID 0

#if (I2C2_SCL_ID == 0)
#define I2C2_SCL_PORT A
#define I2C2_SCL_PIN GPIO_PIN_9
#elif (I2C2_SCL_ID == 1)
#define I2C2_SCL_PORT C
#define I2C2_SCL_PIN GPIO_PIN_4
#elif (I2C2_SCL_ID == 2)
#define I2C2_SCL_PORT F
#define I2C2_SCL_PIN GPIO_PIN_6
#else   /* I2C2_SCL_ID */
#error "Invalid I2C2_SCL Pin Configuration! "
#endif  /* I2C2_SCL_ID */

//   <o> I2C2_SDA Pin
//       <0=>PA8<1=>PF0<2=>PA10
#define I2C2_SDA_ID 0

#if (I2C2_SDA_ID == 0)
#define I2C2_SDA_PORT A
#define I2C2_SDA_PIN GPIO_PIN_8
#elif (I2C2_SDA_ID == 1)
#define I2C2_SDA_PORT F
#define I2C2_SDA_PIN GPIO_PIN_0
#elif (I2C2_SDA_ID == 2)
#define I2C2_SDA_PORT A
#define I2C2_SDA_PIN GPIO_PIN_10
#else   /* I2C2_SDA_ID */
#error "Invalid I2C2_SDA Pin Configuration! "
#endif  /* I2C2_SDA_ID */

//   <e> Enable I2C2 Interrupt
#define I2C2_IT_ENABLE 0

#if I2C2_IT_ENABLE

//   <o> I2C2 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of I2C2
#define I2C2_IT_PRIORITY        2
//   <o> I2C2 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of I2C2
#define I2C2_IT_SUB             3

//   </e>
#endif /* I2C2_IT_ENABLE */

//   <e> Enable I2C2 DMA TX
#define I2C2_TX_DMA             0

#if I2C2_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C2_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C2_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C2_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C2_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C2_TX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C2_TX_DMA */

//   <e> Enable I2C2 DMA RX
#define I2C2_RX_DMA             0

#if I2C2_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C2_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C2_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C2_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C2_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C2_RX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C2_RX_DMA */

#endif  /* I2C2_ENABLE */
// </e>

// <e> I2C3 (Inter-integrated Circuit Interface)
#define I2C3_ENABLE  0

#if I2C3_ENABLE

//   <o> I2C3_SCL Pin
//       <0=>PA8<1=>PC8<2=>PA10<3=>PF3<4=>PG7
#define I2C3_SCL_ID 0

#if (I2C3_SCL_ID == 0)
#define I2C3_SCL_PORT A
#define I2C3_SCL_PIN GPIO_PIN_8
#elif (I2C3_SCL_ID == 1)
#define I2C3_SCL_PORT C
#define I2C3_SCL_PIN GPIO_PIN_8
#elif (I2C3_SCL_ID == 2)
#define I2C3_SCL_PORT A
#define I2C3_SCL_PIN GPIO_PIN_10
#elif (I2C3_SCL_ID == 3)
#define I2C3_SCL_PORT F
#define I2C3_SCL_PIN GPIO_PIN_3
#elif (I2C3_SCL_ID == 4)
#define I2C3_SCL_PORT G
#define I2C3_SCL_PIN GPIO_PIN_7
#else   /* I2C3_SCL_ID */
#error "Invalid I2C3_SCL Pin Configuration! "
#endif  /* I2C3_SCL_ID */

//   <o> I2C3_SDA Pin
//       <0=>PB5<1=>PC9<2=>PC11<3=>PF4<4=>PG8
#define I2C3_SDA_ID 0

#if (I2C3_SDA_ID == 0)
#define I2C3_SDA_PORT B
#define I2C3_SDA_PIN GPIO_PIN_5
#elif (I2C3_SDA_ID == 1)
#define I2C3_SDA_PORT C
#define I2C3_SDA_PIN GPIO_PIN_9
#elif (I2C3_SDA_ID == 2)
#define I2C3_SDA_PORT C
#define I2C3_SDA_PIN GPIO_PIN_11
#elif (I2C3_SDA_ID == 3)
#define I2C3_SDA_PORT F
#define I2C3_SDA_PIN GPIO_PIN_4
#elif (I2C3_SDA_ID == 4)
#define I2C3_SDA_PORT G
#define I2C3_SDA_PIN GPIO_PIN_8
#else   /* I2C3_SDA_ID */
#error "Invalid I2C3_SDA Pin Configuration! "
#endif  /* I2C3_SDA_ID */

//   <e> Enable I2C3 Interrupt
#define I2C3_IT_ENABLE 0

#if I2C3_IT_ENABLE

//   <o> I2C3 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of I2C3
#define I2C3_IT_PRIORITY        2
//   <o> I2C3 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of I2C3
#define I2C3_IT_SUB             3

//   </e>
#endif /* I2C3_IT_ENABLE */

//   <e> Enable I2C3 DMA TX
#define I2C3_TX_DMA             0

#if I2C3_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C3_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C3_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C3_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C3_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C3_TX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C3_TX_DMA */

//   <e> Enable I2C3 DMA RX
#define I2C3_RX_DMA             0

#if I2C3_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C3_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C3_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C3_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C3_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C3_RX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C3_RX_DMA */

#endif  /* I2C3_ENABLE */
// </e>

// <e> I2C4 (Inter-integrated Circuit Interface)
#define I2C4_ENABLE  0

#if I2C4_ENABLE

//   <o> I2C4_SCL Pin
//       <0=>PB6<1=>PC6<2=>PF14<3=>PG3<4=>PA13
#define I2C4_SCL_ID 0

#if (I2C4_SCL_ID == 0)
#define I2C4_SCL_PORT B
#define I2C4_SCL_PIN GPIO_PIN_6
#elif (I2C4_SCL_ID == 1)
#define I2C4_SCL_PORT C
#define I2C4_SCL_PIN GPIO_PIN_6
#elif (I2C4_SCL_ID == 2)
#define I2C4_SCL_PORT F
#define I2C4_SCL_PIN GPIO_PIN_14
#elif (I2C4_SCL_ID == 3)
#define I2C4_SCL_PORT G
#define I2C4_SCL_PIN GPIO_PIN_3
#elif (I2C4_SCL_ID == 4)
#define I2C4_SCL_PORT A
#define I2C4_SCL_PIN GPIO_PIN_13
#else   /* I2C4_SCL_ID */
#error "Invalid I2C4_SCL Pin Configuration! "
#endif  /* I2C4_SCL_ID */

//   <o> I2C4_SDA Pin
//       <0=>PB7<1=>PC7<2=>PF15<3=>PG4
#define I2C4_SDA_ID 0

#if (I2C4_SDA_ID == 0)
#define I2C4_SDA_PORT B
#define I2C4_SDA_PIN GPIO_PIN_7
#elif (I2C4_SDA_ID == 1)
#define I2C4_SDA_PORT C
#define I2C4_SDA_PIN GPIO_PIN_7
#elif (I2C4_SDA_ID == 2)
#define I2C4_SDA_PORT F
#define I2C4_SDA_PIN GPIO_PIN_15
#elif (I2C4_SDA_ID == 3)
#define I2C4_SDA_PORT G
#define I2C4_SDA_PIN GPIO_PIN_4
#else   /* I2C4_SDA_ID */
#error "Invalid I2C4_SDA Pin Configuration! "
#endif  /* I2C4_SDA_ID */

//   <e> Enable I2C4 Interrupt
#define I2C4_IT_ENABLE 0

#if I2C4_IT_ENABLE

//   <o> I2C4 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of I2C4
#define I2C4_IT_PRIORITY        2
//   <o> I2C4 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of I2C4
#define I2C4_IT_SUB             3

//   </e>
#endif /* I2C4_IT_ENABLE */

//   <e> Enable I2C4 DMA TX
#define I2C4_TX_DMA             0

#if I2C4_TX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C4_TX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C4_TX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C4_TX_DMA_PRIORITY    1

//     <o> DMA TX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C4_TX_DMA_IT_PRIORITY 2

//     <o> DMA TX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C4_TX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C4_TX_DMA */

//   <e> Enable I2C4 DMA RX
#define I2C4_RX_DMA             0

#if I2C4_RX_DMA

//     <o> Number <1-2>
//     <i>  Selects DMA Number
#define I2C4_RX_DMA_NUMBER      1

//     <o> Channel <1-8>
//     <i>  Selects DMA Channel
#define I2C4_RX_DMA_CHANNEL     1

//     <o> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
#define I2C4_RX_DMA_PRIORITY    1

//     <o> DMA RX Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
#define I2C4_RX_DMA_IT_PRIORITY 2

//     <o> DMA RX Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
#define I2C4_RX_DMA_IT_SUB      2

//   </e>

#endif  /* I2C4_RX_DMA */

#endif  /* I2C4_ENABLE */
// </e>

// <e> FDCAN1 (Controller Area Network)
#define FDCAN1_ENABLE  1

#if FDCAN1_ENABLE

//   <o> FDCAN1_RX Pin
//       <0=>PA11<1=>PB8<2=>PD0
#define FDCAN1_RX_ID 0

#if (FDCAN1_RX_ID == 0)
#define FDCAN1_RX_PORT A
#define FDCAN1_RX_PIN GPIO_PIN_11
#elif (FDCAN1_RX_ID == 1)
#define FDCAN1_RX_PORT B
#define FDCAN1_RX_PIN GPIO_PIN_8
#elif (FDCAN1_RX_ID == 2)
#define FDCAN1_RX_PORT D
#define FDCAN1_RX_PIN GPIO_PIN_0
#else   /* FDCAN1_RX_ID */
#error "Invalid FDCAN1_RX Pin Configuration! "
#endif  /* FDCAN1_RX_ID */

//   <o> FDCAN1_TX Pin
//       <0=>PA12<1=>PB9<2=>PD1
#define FDCAN1_TX_ID 0

#if (FDCAN1_TX_ID == 0)
#define FDCAN1_TX_PORT A
#define FDCAN1_TX_PIN GPIO_PIN_12
#elif (FDCAN1_TX_ID == 1)
#define FDCAN1_TX_PORT B
#define FDCAN1_TX_PIN GPIO_PIN_9
#elif (FDCAN1_TX_ID == 2)
#define FDCAN1_TX_PORT D
#define FDCAN1_TX_PIN GPIO_PIN_1
#else   /* FDCAN1_TX_ID */
#error "Invalid FDCAN1_TX Pin Configuration! "
#endif  /* FDCAN1_TX_ID */

//   <e> Enable FDCAN1 IT0 Interrupt
#define FDCAN1_IT0_IT_ENABLE 1

#if FDCAN1_IT0_IT_ENABLE

//   <o> FDCAN1 IT0 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of FDCAN1 IT0
#define FDCAN1_IT0_IT_PRIORITY        5
//   <o> FDCAN1 IT0 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of FDCAN1 IT0
#define FDCAN1_IT0_IT_SUB             0

//   </e>
#endif /* FDCAN1_IT0_IT_ENABLE */

//   <e> Enable FDCAN1 IT1 Interrupt
#define FDCAN1_IT1_IT_ENABLE 0

#if FDCAN1_IT1_IT_ENABLE

//   <o> FDCAN1 IT1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of FDCAN1 IT1
#define FDCAN1_IT1_IT_PRIORITY        2
//   <o> FDCAN1 IT1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of FDCAN1 IT1
#define FDCAN1_IT1_IT_SUB             3

//   </e>
#endif /* FDCAN1_IT1_IT_ENABLE */

#endif  /* FDCAN1_ENABLE */
// </e>

// <e> FDCAN2 (Controller Area Network)
#define FDCAN2_ENABLE  1

#if FDCAN2_ENABLE

//   <o> FDCAN2_RX Pin
//       <0=>PB5<1=>PB12
#define FDCAN2_RX_ID 0

#if (FDCAN2_RX_ID == 0)
#define FDCAN2_RX_PORT B
#define FDCAN2_RX_PIN GPIO_PIN_5
#elif (FDCAN2_RX_ID == 1)
#define FDCAN2_RX_PORT B
#define FDCAN2_RX_PIN GPIO_PIN_12
#else   /* FDCAN2_RX_ID */
#error "Invalid FDCAN2_RX Pin Configuration! "
#endif  /* FDCAN2_RX_ID */

//   <o> FDCAN2_TX Pin
//       <0=>PB6<1=>PB13
#define FDCAN2_TX_ID 0

#if (FDCAN2_TX_ID == 0)
#define FDCAN2_TX_PORT B
#define FDCAN2_TX_PIN GPIO_PIN_6
#elif (FDCAN2_TX_ID == 1)
#define FDCAN2_TX_PORT B
#define FDCAN2_TX_PIN GPIO_PIN_13
#else   /* FDCAN2_TX_ID */
#error "Invalid FDCAN2_TX Pin Configuration! "
#endif  /* FDCAN2_TX_ID */

//   <e> Enable FDCAN2 IT0 Interrupt
#define FDCAN2_IT0_IT_ENABLE 1

#if FDCAN2_IT0_IT_ENABLE

//   <o> FDCAN2 IT0 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of FDCAN2 IT0
#define FDCAN2_IT0_IT_PRIORITY        5
//   <o> FDCAN2 IT0 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of FDCAN2 IT0
#define FDCAN2_IT0_IT_SUB             1

//   </e>
#endif /* FDCAN2_IT0_IT_ENABLE */

//   <e> Enable FDCAN2 IT1 Interrupt
#define FDCAN2_IT1_IT_ENABLE 0

#if FDCAN2_IT1_IT_ENABLE

//   <o> FDCAN2 IT1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of FDCAN2 IT1
#define FDCAN2_IT1_IT_PRIORITY        5
//   <o> FDCAN2 IT1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of FDCAN2 IT1
#define FDCAN2_IT1_IT_SUB             1

//   </e>
#endif /* FDCAN2_IT1_IT_ENABLE */

#endif  /* FDCAN2_ENABLE */
// </e>

// <e> FDCAN3 (Controller Area Network)
#define FDCAN3_ENABLE  1

#if FDCAN3_ENABLE

//   <o> FDCAN3_RX Pin
//       <0=>PA8<1=>PB3
#define FDCAN3_RX_ID 1

#if (FDCAN3_RX_ID == 0)
#define FDCAN3_RX_PORT A
#define FDCAN3_RX_PIN GPIO_PIN_8
#elif (FDCAN3_RX_ID == 1)
#define FDCAN3_RX_PORT B
#define FDCAN3_RX_PIN GPIO_PIN_3
#else   /* FDCAN3_RX_ID */
#error "Invalid FDCAN3_RX Pin Configuration! "
#endif  /* FDCAN3_RX_ID */

//   <o> FDCAN3_TX Pin
//       <0=>PA15<1=>PB4
#define FDCAN3_TX_ID 1

#if (FDCAN3_TX_ID == 0)
#define FDCAN3_TX_PORT A
#define FDCAN3_TX_PIN GPIO_PIN_15
#elif (FDCAN3_TX_ID == 1)
#define FDCAN3_TX_PORT B
#define FDCAN3_TX_PIN GPIO_PIN_4
#else   /* FDCAN3_TX_ID */
#error "Invalid FDCAN3_TX Pin Configuration! "
#endif  /* FDCAN3_TX_ID */

//   <e> Enable FDCAN3 IT0 Interrupt
#define FDCAN3_IT0_IT_ENABLE 1

#if FDCAN3_IT0_IT_ENABLE

//   <o> FDCAN3 IT0 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of FDCAN3 IT0
#define FDCAN3_IT0_IT_PRIORITY        5
//   <o> FDCAN3 IT0 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of FDCAN3 IT0
#define FDCAN3_IT0_IT_SUB             2

//   </e>
#endif /* FDCAN3_IT0_IT_ENABLE */

//   <e> Enable FDCAN3 IT1 Interrupt
#define FDCAN3_IT1_IT_ENABLE 0

#if FDCAN3_IT1_IT_ENABLE

//   <o> FDCAN3 IT1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of FDCAN3 IT1
#define FDCAN3_IT1_IT_PRIORITY        5
//   <o> FDCAN3 IT1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of FDCAN3 IT1
#define FDCAN3_IT1_IT_SUB             2

//   </e>
#endif /* FDCAN3_IT1_IT_ENABLE */

#endif  /* FDCAN3_ENABLE */
// </e>

//------------- <<< end of configuration section >>> -----------------------

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Enable the clock of GPIO. */
#define _CSP_GPIO_PORT(x)          GPIO##x
#define CSP_GPIO_PORT(x)           _CSP_GPIO_PORT(x)
#define _CSP_GPIO_CLK_ENABLE(x)    __HAL_RCC_GPIO##x##_CLK_ENABLE()
#define CSP_GPIO_CLK_ENABLE(x)     _CSP_GPIO_CLK_ENABLE(x)

/* Pasting the DMA Channel. */
#define _CSP_DMA_CHANNEL(x, y)      DMA##x##_Channel##y
#define CSP_DMA_CHANNEL(x, y)       _CSP_DMA_CHANNEL(x, y)

/* Pasting the DMA Channel IRQn and IRQHandler. */
#define _CSP_DMA_CHANNEL_IRQn(x, y) DMA##x##_Channel##y##_IRQn
#define CSP_DMA_CHANNEL_IRQn(x, y)  _CSP_DMA_CHANNEL_IRQn(x, y)

#define _CSP_DMA_CHANNEL_IRQ(x, y) DMA##x##_Channel##y##_IRQHandler
#define CSP_DMA_CHANNEL_IRQ(x, y)  _CSP_DMA_CHANNEL_IRQ(x, y)

/* Set DMA Priority */
#define CSP_DMA_PRIORITY(x)        ((x) << DMA_CCR_PL_Pos)

/* Enable the clock of DMA. */
#define _CSP_DMA_CLK_ENABLE(x)     do {__HAL_RCC_DMAMUX1_CLK_ENABLE(); __HAL_RCC_DMA##x##_CLK_ENABLE();} while(0)
#define CSP_DMA_CLK_ENABLE(x)      _CSP_DMA_CLK_ENABLE(x)

/* CSP memory management functions. */
#define CSP_MALLOC(x)              malloc(x)
#define CSP_FREE(x)                free(x)
#define CSP_REALLOC(p, x)          realloc(p, x)
#include <stdlib.h>

/* Devices Family header files.  */
#include "stm32g4xx_hal.h"


#if (LPUART1_ENABLE || USART1_ENABLE || USART2_ENABLE || USART3_ENABLE || UART4_ENABLE || UART5_ENABLE)
#include "../UART_STM32G4xx.h"
#endif  /* (LPUART1_ENABLE || USART1_ENABLE || USART2_ENABLE || USART3_ENABLE || UART4_ENABLE || UART5_ENABLE) */

#if (I2C1_ENABLE || I2C2_ENABLE || I2C3_ENABLE || I2C4_ENABLE)
#include "../I2C_STM32G4xx.h"
#endif  /* (I2C1_ENABLE || I2C2_ENABLE || I2C3_ENABLE || I2C4_ENABLE) */
    
#if (QUADSPI1_ENABLE)
#include "../QSPI_STM32G4xx.h"
#endif  /* (QUADSPI1_ENABLE) */

#if (SPI1_ENABLE || SPI2_ENABLE || SPI3_ENABLE || SPI4_ENABLE)
#include "../SPI_STM32G4xx.h"
#endif  /* (SPI1_ENABLE || SPI2_ENABLE || SPI3_ENABLE || SPI4_ENABLE) */

#if (FDCAN1_ENABLE || FDCAN2_ENABLE || FDCAN3_ENABLE)
#include "../CAN_STM32G4xx.h"
#endif  /* (FDCAN1_ENABLE || FDCAN2_ENABLE || FDCAN3_ENABLE) */

#if (RTC_ENABLE)
#include "../RTC_STM32G4xx.h"
#endif /* RTC_ENABLE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CSP_CONFIG_H */

