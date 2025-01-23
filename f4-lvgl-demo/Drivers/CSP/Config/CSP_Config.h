/**
 * @file    CSP_Config.h
 * @author  Deadline039
 * @brief   The CSP configuration of STM32F4xx.
 * @version 1.0
 * @date    2024-10-22
 * @note    Reference the CMSIS RTE Devices.
 */

//-------- <<< Use Configuration Wizard in Context Menu >>> --------------------

#ifndef __CSP_CONFIG_H
#define __CSP_CONFIG_H

// <e> USART1 (Universal synchronous asynchronous receiver transmitter)
#define USART1_ENABLE 1

//   <o> USART1_TX Pin <0=>Not Used <1=>PA9 <2=>PA15 <3=>PB6
#define USART1_TX_ID  1
#if (USART1_TX_ID == 0)
#define USART1_TX 0
#elif (USART1_TX_ID == 1)
#define USART1_TX      1
#define USART1_TX_PORT A
#define USART1_TX_PIN  GPIO_PIN_9
#elif (USART1_TX_ID == 2)
#define USART1_TX      1
#define USART1_TX_PORT A
#define USART1_TX_PIN  GPIO_PIN_15
#elif (USART1_TX_ID == 3)
#define USART1_TX      1
#define USART1_TX_PORT B
#define USART1_TX_PIN  GPIO_PIN_6
#else
#error "Invalid USART1_TX Pin Configuration!"
#endif

//   <o> USART1_RX Pin <0=>Not Used <1=>PA10 <2=>PB3 <3=>PB7
#define USART1_RX_ID 1
#if (USART1_RX_ID == 0)
#define USART1_RX 0
#elif (USART1_RX_ID == 1)
#define USART1_RX      1
#define USART1_RX_PORT A
#define USART1_RX_PIN  GPIO_PIN_10
#elif (USART1_RX_ID == 2)
#define USART1_RX      1
#define USART1_RX_PORT B
#define USART1_RX_PIN  GPIO_PIN_3
#elif (USART1_RX_ID == 3)
#define USART1_RX      1
#define USART1_RX_PORT B
#define USART1_RX_PIN  GPIO_PIN_7
#else
#error "Invalid USART1_RX Pin Configuration!"
#endif

//   <o> USART1_CTS Pin <0=>Not Used <1=>PA11
#define USART1_CTS_ID 0
#if (USART1_CTS_ID == 0)
#define USART1_CTS 0
#elif (USART1_CTS_ID == 1)
#define USART1_CTS      1
#define USART1_CTS_PORT A
#define USART1_CTS_PIN  GPIO_PIN_11
#else
#error "Invalid USART1_CTS Pin Configuration!"
#endif

//   <o> USART1_RTS Pin <0=>Not Used <1=>PA12
#define USART1_RTS_ID 0
#if (USART1_RTS_ID == 0)
#define USART1_RTS 0
#elif (USART1_RTS_ID == 1)
#define USART1_RTS      1
#define USART1_RTS_PORT A
#define USART1_RTS_PIN  GPIO_PIN_12
#else
#error "Invalid USART1_RTS Pin Configuration!"
#endif

//   <o> USART1 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART1
#define USART1_IT_PRIORITY        2
//   <o> USART1 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART1
#define USART1_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <2=>2 <5=>5
//     <i>  Selects DMA Stream (only Stream 2 or 5 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART1_RX_DMA             0
#define USART1_RX_DMA_NUMBER      2
#define USART1_RX_DMA_STREAM      2
#define USART1_RX_DMA_CHANNEL     4
#define USART1_RX_DMA_PRIORITY    1
#define USART1_RX_DMA_IT_PRIORITY 2
#define USART1_RX_DMA_IT_SUB      2
#define USART1_RX_DMA_BUF_SIZE    256
#define USART1_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART1_TX_DMA             0
#define USART1_TX_DMA_NUMBER      2
#define USART1_TX_DMA_STREAM      7
#define USART1_TX_DMA_CHANNEL     4
#define USART1_TX_DMA_PRIORITY    0
#define USART1_TX_DMA_IT_PRIORITY 1
#define USART1_TX_DMA_IT_SUB      4
#define USART1_TX_DMA_BUF_SIZE    256

// </e>

// <e> USART2 (Universal synchronous asynchronous receiver transmitter)
#define USART2_ENABLE             0

//   <o> USART2_TX Pin <0=>Not Used <1=>PA2 <2=>PD5
#define USART2_TX_ID              1
#if (USART2_TX_ID == 0)
#define USART2_TX 0
#elif (USART2_TX_ID == 1)
#define USART2_TX      1
#define USART2_TX_PORT A
#define USART2_TX_PIN  GPIO_PIN_2
#elif (USART2_TX_ID == 2)
#define USART2_TX      1
#define USART2_TX_PORT D
#define USART2_TX_PIN  GPIO_PIN_5
#else
#error "Invalid USART2_TX Pin Configuration!"
#endif

//   <o> USART2_RX Pin <0=>Not Used <1=>PA3 <2=>PD6
#define USART2_RX_ID 1
#if (USART2_RX_ID == 0)
#define USART2_RX 0
#elif (USART2_RX_ID == 1)
#define USART2_RX      1
#define USART2_RX_PORT A
#define USART2_RX_PIN  GPIO_PIN_3
#elif (USART2_RX_ID == 2)
#define USART2_RX      1
#define USART2_RX_PORT D
#define USART2_RX_PIN  GPIO_PIN_6
#else
#error "Invalid USART2_RX Pin Configuration!"
#endif

//   <o> USART2_CTS Pin <0=>Not Used <1=>PA0 <2=>PD3
#define USART2_CTS_ID 0
#if (USART2_CTS_ID == 0)
#define USART2_CTS 0
#elif (USART2_CTS_ID == 1)
#define USART2_CTS      1
#define USART2_CTS_PORT A
#define USART2_CTS_PIN  GPIO_PIN_0
#elif (USART2_CTS_ID == 2)
#define USART2_CTS      1
#define USART2_CTS_PORT D
#define USART2_CTS_PIN  GPIO_PIN_3
#else
#error "Invalid USART2_CTS Pin Configuration!"
#endif

//   <o> USART2_RTS Pin <0=>Not Used <1=>PA1 <2=>PD4
#define USART2_RTS_ID 0
#if (USART2_RTS_ID == 0)
#define USART2_RTS 0
#elif (USART2_RTS_ID == 1)
#define USART2_RTS      1
#define USART2_RTS_PORT A
#define USART2_RTS_PIN  GPIO_PIN_1
#elif (USART2_RTS_ID == 2)
#define USART2_RTS      1
#define USART2_RTS_PORT D
#define USART2_RTS_PIN  GPIO_PIN_4
#else
#error "Invalid USART2_RTS Pin Configuration!"
#endif

//   <o> USART2 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART2
#define USART2_IT_PRIORITY        2
//   <o> USART2 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART2
#define USART2_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <5=>5 <7=>7
//     <i>  Selects DMA Stream (only Stream 5 or 7 can be used)
//     <o3> Channel <4=>4 <6=>6
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART2_RX_DMA             0
#define USART2_RX_DMA_NUMBER      1
#define USART2_RX_DMA_STREAM      5
#define USART2_RX_DMA_CHANNEL     4
#define USART2_RX_DMA_PRIORITY    0
#define USART2_RX_DMA_IT_PRIORITY 2
#define USART2_RX_DMA_IT_SUB      2
#define USART2_RX_DMA_BUF_SIZE    256
#define USART2_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <6=>6
//     <i>  Selects DMA Stream (only Stream 6 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART2_TX_DMA             0
#define USART2_TX_DMA_NUMBER      1
#define USART2_TX_DMA_STREAM      6
#define USART2_TX_DMA_CHANNEL     4
#define USART2_TX_DMA_PRIORITY    0
#define USART2_TX_DMA_IT_PRIORITY 1
#define USART2_TX_DMA_IT_SUB      4
#define USART2_TX_DMA_BUF_SIZE    256

// </e>

// <e> USART3 (Universal synchronous asynchronous receiver transmitter)
#define USART3_ENABLE             0

//   <o> USART3_TX Pin <0=>Not Used <1=>PB10 <2=>PC10 <3=>PD8
#define USART3_TX_ID              1
#if (USART3_TX_ID == 0)
#define USART3_TX 0
#elif (USART3_TX_ID == 1)
#define USART3_TX      1
#define USART3_TX_PORT B
#define USART3_TX_PIN  GPIO_PIN_10
#elif (USART3_TX_ID == 2)
#define USART3_TX      1
#define USART3_TX_PORT C
#define USART3_TX_PIN  GPIO_PIN_10
#elif (USART3_TX_ID == 3)
#define USART3_TX      1
#define USART3_TX_PORT D
#define USART3_TX_PIN  GPIO_PIN_8
#else
#error "Invalid USART3_TX Pin Configuration!"
#endif

//   <o> USART3_RX Pin <0=>Not Used <1=>PB11 <2=>PC11 <3=>PD9 <4=>PC5
#define USART3_RX_ID 1
#if (USART3_RX_ID == 0)
#define USART3_RX 0
#elif (USART3_RX_ID == 1)
#define USART3_RX      1
#define USART3_RX_PORT B
#define USART3_RX_PIN  GPIO_PIN_11
#elif (USART3_RX_ID == 2)
#define USART3_RX      1
#define USART3_RX_PORT C
#define USART3_RX_PIN  GPIO_PIN_11
#elif (USART3_RX_ID == 3)
#define USART3_RX      1
#define USART3_RX_PORT D
#define USART3_RX_PIN  GPIO_PIN_9
#elif (USART3_RX_ID == 4)
#define USART3_RX      1
#define USART3_RX_PORT C
#define USART3_RX_PIN  GPIO_PIN_5
#else
#error "Invalid USART3_RX Pin Configuration!"
#endif

//   <o> USART3_CTS Pin <0=>Not Used <1=>PB13 <2=>PD11
#define USART3_CTS_ID 0
#if (USART3_CTS_ID == 0)
#define USART3_CTS 0
#elif (USART3_CTS_ID == 1)
#define USART3_CTS      1
#define USART3_CTS_PORT B
#define USART3_CTS_PIN  GPIO_PIN_13
#elif (USART3_CTS_ID == 2)
#define USART3_CTS      1
#define USART3_CTS_PORT D
#define USART3_CTS_PIN  GPIO_PIN_11
#else
#error "Invalid USART3_CTS Pin Configuration!"
#endif

//   <o> USART3_RTS Pin <0=>Not Used <1=>PB14 <2=>PD12
#define USART3_RTS_ID 0
#if (USART3_RTS_ID == 0)
#define USART3_RTS 0
#elif (USART3_RTS_ID == 1)
#define USART3_RTS      1
#define USART3_RTS_PORT B
#define USART3_RTS_PIN  GPIO_PIN_14
#elif (USART3_RTS_ID == 2)
#define USART3_RTS      1
#define USART3_RTS_PORT D
#define USART3_RTS_PIN  GPIO_PIN_12
#else
#error "Invalid USART3_RTS Pin Configuration!"
#endif

//   <o> USART3 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART3
#define USART3_IT_PRIORITY        2
//   <o> USART3 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART3
#define USART3_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1 <4=>4
//     <i>  Selects DMA Stream (only Stream 1 or 4 can be used)
//     <o3> Channel <4=>4 <7=>7
//     <i>  Selects DMA Channel (only Channel 4 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART3_RX_DMA             0
#define USART3_RX_DMA_NUMBER      1
#define USART3_RX_DMA_STREAM      1
#define USART3_RX_DMA_CHANNEL     4
#define USART3_RX_DMA_PRIORITY    0
#define USART3_RX_DMA_IT_PRIORITY 2
#define USART3_RX_DMA_IT_SUB      2
#define USART3_RX_DMA_BUF_SIZE    256
#define USART3_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3 <4=>4
//     <i>  Selects DMA Stream (only Stream 3 or 4 can be used)
//     <o3> Channel <4=>4 <7=>7
//     <i>  Selects DMA Channel (only Channel 4 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART3_TX_DMA             0
#define USART3_TX_DMA_NUMBER      1
#define USART3_TX_DMA_STREAM      3
#define USART3_TX_DMA_CHANNEL     4
#define USART3_TX_DMA_PRIORITY    0
#define USART3_TX_DMA_IT_PRIORITY 1
#define USART3_TX_DMA_IT_SUB      4
#define USART3_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART4 (Universal asynchronous receiver transmitter)
#define UART4_ENABLE              0

//   <o> UART4_TX Pin <0=>Not Used <1=>PA0 <2=>PC10 <3=>PD10 <4=>PA12 <5=>PD1
#define UART4_TX_ID               2
#if (UART4_TX_ID == 0)
#define UART4_TX 0
#elif (UART4_TX_ID == 1)
#define UART4_TX      1
#define UART4_TX_PORT A
#define UART4_TX_PIN  GPIO_PIN_0
#elif (UART4_TX_ID == 2)
#define UART4_TX      1
#define UART4_TX_PORT C
#define UART4_TX_PIN  GPIO_PIN_10
#elif (UART4_TX_ID == 3)
#define UART4_TX      1
#define UART4_TX_PORT D
#define UART4_TX_PIN  GPIO_PIN_10
#elif (UART4_TX_ID == 4)
#define UART4_TX      1
#define UART4_TX_PORT A
#define UART4_TX_PIN  GPIO_PIN_12
#elif (UART4_TX_ID == 5)
#define UART4_TX      1
#define UART4_TX_PORT D
#define UART4_TX_PIN  GPIO_PIN_1
#else
#error "Invalid UART4_TX Pin Configuration!"
#endif

//   <o> UART4_RX Pin <0=>Not Used <1=>PA1 <2=>PC11 <3=>PA11 <4=>PD0
#define UART4_RX_ID 2
#if (UART4_RX_ID == 0)
#define UART4_RX 0
#elif (UART4_RX_ID == 1)
#define UART4_RX      1
#define UART4_RX_PORT A
#define UART4_RX_PIN  GPIO_PIN_1
#elif (UART4_RX_ID == 2)
#define UART4_RX      1
#define UART4_RX_PORT C
#define UART4_RX_PIN  GPIO_PIN_11
#elif (UART4_RX_ID == 3)
#define UART4_RX      1
#define UART4_RX_PORT A
#define UART4_RX_PIN  GPIO_PIN_11
#elif (UART4_RX_ID == 4)
#define UART4_RX      1
#define UART4_RX_PORT D
#define UART4_RX_PIN  GPIO_PIN_0
#else
#error "Invalid UART4_RX Pin Configuration!"
#endif

//   <o> UART4 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART4
#define UART4_IT_PRIORITY        2
//   <o> UART4 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART4
#define UART4_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <2=>2
//     <i>  Selects DMA Stream (only Stream 2 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART4_RX_DMA             0
#define UART4_RX_DMA_NUMBER      1
#define UART4_RX_DMA_STREAM      2
#define UART4_RX_DMA_CHANNEL     4
#define UART4_RX_DMA_PRIORITY    0
#define UART4_RX_DMA_IT_PRIORITY 2
#define UART4_RX_DMA_IT_SUB      2
#define UART4_RX_DMA_BUF_SIZE    256
#define UART4_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <4=>4
//     <i>  Selects DMA Stream (only Stream 4 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART4_TX_DMA             0
#define UART4_TX_DMA_NUMBER      1
#define UART4_TX_DMA_STREAM      4
#define UART4_TX_DMA_CHANNEL     4
#define UART4_TX_DMA_PRIORITY    0
#define UART4_TX_DMA_IT_PRIORITY 1
#define UART4_TX_DMA_IT_SUB      4
#define UART4_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART5 (Universal asynchronous receiver transmitter)
#define UART5_ENABLE             0

//   <o> UART5_TX Pin <0=>Not Used <1=>PC12 <2=>PB6 <3=>PB9 <4=>PB13
#define UART5_TX_ID              1
#if (UART5_TX_ID == 0)
#define UART5_TX 0
#elif (UART5_TX_ID == 1)
#define UART5_TX      1
#define UART5_TX_PORT C
#define UART5_TX_PIN  GPIO_PIN_12
#elif (UART5_TX_ID == 2)
#define UART5_TX      1
#define UART5_TX_PORT B
#define UART5_TX_PIN  GPIO_PIN_6
#elif (UART5_TX_ID == 3)
#define UART5_TX      1
#define UART5_TX_PORT B
#define UART5_TX_PIN  GPIO_PIN_9
#elif (UART5_TX_ID == 4)
#define UART5_TX      1
#define UART5_TX_PORT B
#define UART5_TX_PIN  GPIO_PIN_13
#else
#error "Invalid UART5_TX Pin Configuration!"
#endif

//   <o> UART5_RX Pin <0=>Not Used <1=>PD2 <2=>PB5 <3=>PB8 <4=>PB12
#define UART5_RX_ID 1
#if (UART5_RX_ID == 0)
#define UART5_RX 0
#elif (UART5_RX_ID == 1)
#define UART5_RX      1
#define UART5_RX_PORT D
#define UART5_RX_PIN  GPIO_PIN_2
#elif (UART5_TX_ID == 2)
#define UART5_TX      1
#define UART5_TX_PORT B
#define UART5_TX_PIN  GPIO_PIN_5
#elif (UART5_TX_ID == 3)
#define UART5_TX      1
#define UART5_TX_PORT B
#define UART5_TX_PIN  GPIO_PIN_8
#elif (UART5_TX_ID == 4)
#define UART5_TX      1
#define UART5_TX_PORT B
#define UART5_TX_PIN  GPIO_PIN_12
#else
#error "Invalid UART5_RX Pin Configuration!"
#endif

//   <o> UART5 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART5
#define UART5_IT_PRIORITY        2
//   <o> UART5 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART5
#define UART5_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0
//     <i>  Selects DMA Stream (only Stream 0 can be used)
//     <o3> Channel <4=>4
//     <i>  Selects DMA Channel (only Channel 4 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART5_RX_DMA             0
#define UART5_RX_DMA_NUMBER      1
#define UART5_RX_DMA_STREAM      0
#define UART5_RX_DMA_CHANNEL     4
#define UART5_RX_DMA_PRIORITY    0
#define UART5_RX_DMA_IT_PRIORITY 2
#define UART5_RX_DMA_IT_SUB      2
#define UART5_RX_DMA_BUF_SIZE    256
#define UART5_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <4=>4 <8=>8
//     <i>  Selects DMA Channel (only Channel 4 or 8 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART5_TX_DMA             0
#define UART5_TX_DMA_NUMBER      1
#define UART5_TX_DMA_STREAM      7
#define UART5_TX_DMA_CHANNEL     4
#define UART5_TX_DMA_PRIORITY    0
#define UART5_TX_DMA_IT_PRIORITY 1
#define UART5_TX_DMA_IT_SUB      4
#define UART5_TX_DMA_BUF_SIZE    256

// </e>

// <e> USART6 (Universal synchronous asynchronous receiver transmitter)
#define USART6_ENABLE            0

//   <o> USART6_TX Pin <0=>Not Used <1=>PA11 <2=>PC6 <3=>PG14
#define USART6_TX_ID             2
#if (USART6_TX_ID == 0)
#define USART6_TX 0
#elif (USART6_TX_ID == 1)
#define USART6_TX      1
#define USART6_TX_PORT A
#define USART6_TX_PIN  GPIO_PIN_11
#elif (USART6_TX_ID == 2)
#define USART6_TX      1
#define USART6_TX_PORT C
#define USART6_TX_PIN  GPIO_PIN_6
#elif (USART6_TX_ID == 3)
#define USART6_TX      1
#define USART6_TX_PORT G
#define USART6_TX_PIN  GPIO_PIN_14
#else
#error "Invalid USART6_TX Pin Configuration!"
#endif

//   <o> USART6_RX Pin <0=>Not Used <1=>PA12 <2=>PC7 <3=>PG9
#define USART6_RX_ID 2
#if (USART6_RX_ID == 0)
#define USART6_RX 0
#elif (USART6_RX_ID == 1)
#define USART6_RX      1
#define USART6_RX_PORT A
#define USART6_RX_PIN  GPIO_PIN_12
#elif (USART6_RX_ID == 2)
#define USART6_RX      1
#define USART6_RX_PORT C
#define USART6_RX_PIN  GPIO_PIN_7
#elif (USART6_RX_ID == 3)
#define USART6_RX      1
#define USART6_RX_PORT G
#define USART6_RX_PIN  GPIO_PIN_9
#else
#error "Invalid USART6_RX Pin Configuration!"
#endif

//   <o> USART6_CTS Pin <0=>Not Used <1=>PG13 <2=>PG15
#define USART6_CTS_ID 0
#if (USART6_CTS_ID == 0)
#define USART6_CTS 0
#elif (USART6_CTS_ID == 1)
#define USART6_CTS      1
#define USART6_CTS_PORT G
#define USART6_CTS_PIN  GPIO_PIN_13
#elif (USART6_CTS_ID == 2)
#define USART6_CTS      1
#define USART6_CTS_PORT G
#define USART6_CTS_PIN  GPIO_PIN_15
#else
#error "Invalid USART6_CTS Pin Configuration!"
#endif

//   <o> USART6_RTS Pin <0=>Not Used <1=>PG8 <2=>PG12
#define USART6_RTS_ID 0
#if (USART6_RTS_ID == 0)
#define USART6_RTS 0
#elif (USART6_RTS_ID == 1)
#define USART6_RTS      1
#define USART6_RTS_PORT G
#define USART6_RTS_PIN  GPIO_PIN_8
#elif (USART6_RTS_ID == 2)
#define USART6_RTS      1
#define USART6_RTS_PORT G
#define USART6_RTS_PIN  GPIO_PIN_12
#else
#error "Invalid USART6_RTS Pin Configuration!"
#endif

//   <o> USART6 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of USART6
#define USART6_IT_PRIORITY        2
//   <o> USART6 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of USART6
#define USART6_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <1=>1 <2=>2
//     <i>  Selects DMA Stream (only Stream 1 or 2 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define USART6_RX_DMA             0
#define USART6_RX_DMA_NUMBER      2
#define USART6_RX_DMA_STREAM      1
#define USART6_RX_DMA_CHANNEL     5
#define USART6_RX_DMA_PRIORITY    0
#define USART6_RX_DMA_IT_PRIORITY 2
#define USART6_RX_DMA_IT_SUB      2
#define USART6_RX_DMA_BUF_SIZE    256
#define USART6_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <6=>6 <7=>7
//     <i>  Selects DMA Stream (only Stream 6 or 7 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define USART6_TX_DMA             0
#define USART6_TX_DMA_NUMBER      2
#define USART6_TX_DMA_STREAM      6
#define USART6_TX_DMA_CHANNEL     5
#define USART6_TX_DMA_PRIORITY    0
#define USART6_TX_DMA_IT_PRIORITY 1
#define USART6_TX_DMA_IT_SUB      4
#define USART6_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART7 (Universal asynchronous receiver transmitter)
#define UART7_ENABLE              0

//   <o> UART7_TX Pin <0=>Not Used <1=>PF7 <2=>PE8 <3=>PA15 <4=>PB4
#define UART7_TX_ID               1
#if (UART7_TX_ID == 0)
#define UART7_TX 0
#elif (UART7_TX_ID == 1)
#define UART7_TX      1
#define UART7_TX_PORT F
#define UART7_TX_PIN  GPIO_PIN_7
#elif (UART7_TX_ID == 2)
#define UART7_TX      1
#define UART7_TX_PORT E
#define UART7_TX_PIN  GPIO_PIN_8
#elif (UART7_TX_ID == 3)
#define UART7_TX      1
#define UART7_TX_PORT A
#define UART7_TX_PIN  GPIO_PIN_15
#elif (UART7_TX_ID == 4)
#define UART7_TX      1
#define UART7_TX_PORT B
#define UART7_TX_PIN  GPIO_PIN_4
#else
#error "Invalid UART7_TX Pin Configuration!"
#endif

//   <o> UART7_RX Pin <0=>Not Used <1=>PF6 <2=>PE7 <3=>PA8 <4=>PB3
#define UART7_RX_ID 1
#if (UART7_RX_ID == 0)
#define UART7_RX 0
#elif (UART7_RX_ID == 1)
#define UART7_RX      1
#define UART7_RX_PORT F
#define UART7_RX_PIN  GPIO_PIN_6
#elif (UART7_RX_ID == 2)
#define UART7_RX      1
#define UART7_RX_PORT E
#define UART7_RX_PIN  GPIO_PIN_7
#elif (UART7_RX_ID == 3)
#define UART7_RX      1
#define UART7_RX_PORT A
#define UART7_RX_PIN  GPIO_PIN_8
#elif (UART7_RX_ID == 4)
#define UART7_RX      1
#define UART7_RX_PORT B
#define UART7_RX_PIN  GPIO_PIN_3
#else
#error "Invalid UART7_RX Pin Configuration!"
#endif

//   <o> UART7 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART7
#define UART7_IT_PRIORITY        2
//   <o> UART7 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART7
#define UART7_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3
//     <i>  Selects DMA Stream (only Stream 3 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART7_RX_DMA             0
#define UART7_RX_DMA_NUMBER      1
#define UART7_RX_DMA_STREAM      3
#define UART7_RX_DMA_CHANNEL     5
#define UART7_RX_DMA_PRIORITY    0
#define UART7_RX_DMA_IT_PRIORITY 2
#define UART7_RX_DMA_IT_SUB      2
#define UART7_RX_DMA_BUF_SIZE    256
#define UART7_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1
//     <i>  Selects DMA Stream (only Stream 1 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART7_TX_DMA             0
#define UART7_TX_DMA_NUMBER      1
#define UART7_TX_DMA_STREAM      1
#define UART7_TX_DMA_CHANNEL     5
#define UART7_TX_DMA_PRIORITY    0
#define UART7_TX_DMA_IT_PRIORITY 1
#define UART7_TX_DMA_IT_SUB      4
#define UART7_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART8 (Universal asynchronous receiver transmitter)
#define UART8_ENABLE             0

//   <o> UART8_TX Pin <0=>Not Used <1=>PE1 <2=>PF9
#define UART8_TX_ID              1
#if (UART8_TX_ID == 0)
#define UART8_TX 0
#elif (UART8_TX_ID == 1)
#define UART8_TX      1
#define UART8_TX_PORT E
#define UART8_TX_PIN  GPIO_PIN_1
#elif (UART8_TX_ID == 2)
#define UART8_TX      1
#define UART8_TX_PORT F
#define UART8_TX_PIN  GPIO_PIN_9
#else
#error "Invalid UART8_TX Pin Configuration!"
#endif

//   <o> UART8_RX Pin <0=>Not Used <1=>PE0 <2=>PF8
#define UART8_RX_ID 1
#if (UART8_RX_ID == 0)
#define UART8_RX 0
#elif (UART8_RX_ID == 1)
#define UART8_RX      1
#define UART8_RX_PORT E
#define UART8_RX_PIN  GPIO_PIN_0
#elif (UART8_RX_ID == 2)
#define UART8_RX      1
#define UART8_RX_PORT F
#define UART8_RX_PIN  GPIO_PIN_8
#else
#error "Invalid UART8_RX Pin Configuration!"
#endif

//   <o> UART8 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART8
#define UART8_IT_PRIORITY        2
//   <o> UART8 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART8
#define UART8_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <6=>6
//     <i>  Selects DMA Stream (only Stream 6 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART8_RX_DMA             0
#define UART8_RX_DMA_NUMBER      1
#define UART8_RX_DMA_STREAM      6
#define UART8_RX_DMA_CHANNEL     5
#define UART8_RX_DMA_PRIORITY    0
#define UART8_RX_DMA_IT_PRIORITY 2
#define UART8_RX_DMA_IT_SUB      2
#define UART8_RX_DMA_BUF_SIZE    256
#define UART8_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0
//     <i>  Selects DMA Stream (only Stream 0 can be used)
//     <o3> Channel <5=>5
//     <i>  Selects DMA Channel (only Channel 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART8_TX_DMA             0
#define UART8_TX_DMA_NUMBER      1
#define UART8_TX_DMA_STREAM      0
#define UART8_TX_DMA_CHANNEL     5
#define UART8_TX_DMA_PRIORITY    0
#define UART8_TX_DMA_IT_PRIORITY 1
#define UART8_TX_DMA_IT_SUB      4
#define UART8_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART9 (Universal asynchronous receiver transmitter)
#define UART9_ENABLE             0

//   <o> UART9_TX Pin <0=>Not Used <1=>PD15 <2=>PG1
#define UART9_TX_ID              0
#if (UART9_TX_ID == 0)
#define UART9_TX 0
#elif (UART9_TX_ID == 1)
#define UART9_TX      1
#define UART9_TX_PORT D
#define UART9_TX_PIN  GPIO_PIN_15
#elif (UART9_TX_ID == 2)
#define UART9_TX      1
#define UART9_TX_PORT G
#define UART9_TX_PIN  GPIO_PIN_1
#else
#error "Invalid UART9_TX Pin Configuration!"
#endif

//   <o> UART9_RX Pin <0=>Not Used <1=>PD14 <2=>PG0
#define UART9_RX_ID 0
#if (UART9_RX_ID == 0)
#define UART9_RX 0
#elif (UART9_RX_ID == 1)
#define UART9_RX      1
#define UART9_RX_PORT D
#define UART9_RX_PIN  GPIO_PIN_14
#elif (UART9_RX_ID == 2)
#define UART9_RX      1
#define UART9_RX_PORT G
#define UART9_RX_PIN  GPIO_PIN_0
#else
#error "Invalid UART9_RX Pin Configuration!"
#endif

//   <o> UART9 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART9
#define UART9_IT_PRIORITY        2
//   <o> UART9 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART9
#define UART9_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART9_RX_DMA             0
#define UART9_RX_DMA_NUMBER      1
#define UART9_RX_DMA_STREAM      6
#define UART9_RX_DMA_CHANNEL     5
#define UART9_RX_DMA_PRIORITY    0
#define UART9_RX_DMA_IT_PRIORITY 2
#define UART9_RX_DMA_IT_SUB      2
#define UART9_RX_DMA_BUF_SIZE    256
#define UART9_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0
//     <i>  Selects DMA Stream (only Stream 0 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART9_TX_DMA             0
#define UART9_TX_DMA_NUMBER      1
#define UART9_TX_DMA_STREAM      0
#define UART9_TX_DMA_CHANNEL     5
#define UART9_TX_DMA_PRIORITY    0
#define UART9_TX_DMA_IT_PRIORITY 1
#define UART9_TX_DMA_IT_SUB      4
#define UART9_TX_DMA_BUF_SIZE    256

// </e>

// <e> UART10 (Universal asynchronous receiver transmitter)
#define UART10_ENABLE            0

//   <o> UART10_TX Pin <0=>Not Used <1=>PE3 <2=>PG12
#define UART10_TX_ID             0
#if (UART10_TX_ID == 0)
#define UART10_TX 0
#elif (UART10_TX_ID == 1)
#define UART10_TX      1
#define UART10_TX_PORT E
#define UART10_TX_PIN  GPIO_PIN_3
#elif (UART10_TX_ID == 2)
#define UART10_TX      1
#define UART10_TX_PORT G
#define UART10_TX_PIN  GPIO_PIN_12
#else
#error "Invalid UART10_TX Pin Configuration!"
#endif

//   <o> UART10_RX Pin <0=>Not Used <1=>PE2 <2=>PG11
#define UART10_RX_ID 0
#if (UART10_RX_ID == 0)
#define UART10_RX 0
#elif (UART10_RX_ID == 1)
#define UART10_RX      1
#define UART10_RX_PORT E
#define UART10_RX_PIN  GPIO_PIN_2
#elif (UART10_RX_ID == 2)
#define UART10_RX      1
#define UART10_RX_PORT G
#define UART10_RX_PIN  GPIO_PIN_11
#else
#error "Invalid UART10_RX Pin Configuration!"
#endif

//   <o> UART10 Interrupt Priority <0-15>
//   <i> The Interrupt Priority of UART10
#define UART10_IT_PRIORITY        2
//   <o> UART10 Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of UART10
#define UART10_IT_SUB             3

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0 <3=>3
//     <i>  Selects DMA Stream (only Stream 0 or 3 can be used)
//     <o3> Channel <5=>5 <9=>9
//     <i>  Selects DMA Channel (only Channel 5 or 9 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//     <o7> The size of Receive buf [byte]
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//     <o8> The size of Receive FIFO [byte] (Must be power of 2)
//     <i>  Using FIFO and Buf to implement high reliable USART Receive
//   </e>
#define UART10_RX_DMA             0
#define UART10_RX_DMA_NUMBER      1
#define UART10_RX_DMA_STREAM      6
#define UART10_RX_DMA_CHANNEL     5
#define UART10_RX_DMA_PRIORITY    0
#define UART10_RX_DMA_IT_PRIORITY 2
#define UART10_RX_DMA_IT_SUB      2
#define UART10_RX_DMA_BUF_SIZE    256
#define UART10_RX_DMA_FIFO_SIZE   256

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <7=>7 <3=>5
//     <i>  Selects DMA Stream (only Stream 7 or 5 can be used)
//     <o3> Channel <6=>6 <9=>9
//     <i>  Selects DMA Channel (only Channel 6 or 9 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//     <o7> The size of Send buf [byte]
//     <i>  Write data to Send buf, and sending with thread safety
//   </e>
#define UART10_TX_DMA             0
#define UART10_TX_DMA_NUMBER      1
#define UART10_TX_DMA_STREAM      0
#define UART10_TX_DMA_CHANNEL     5
#define UART10_TX_DMA_PRIORITY    0
#define UART10_TX_DMA_IT_PRIORITY 1
#define UART10_TX_DMA_IT_SUB      4
#define UART10_TX_DMA_BUF_SIZE    256

// </e>

// <e> I2C1 (Inter-integrated Circuit Interface 1)
#define I2C1_ENABLE               0

//   <o> I2C1_SCL Pin <0=>PB6 <1=>PB8
#define I2C1_SCL_PORT_ID          0
#if (I2C1_SCL_PORT_ID == 0)
#define I2C1_SCL_PORT B
#define I2C1_SCL_PIN  GPIO_PIN_6
#elif (I2C1_SCL_PORT_ID == 1)
#define I2C1_SCL_PORT B
#define I2C1_SCL_PIN  GPIO_PIN_8
#else
#error "Invalid I2C1_SCL Pin Configuration!"
#endif

//   <o> I2C1_SDA Pin <0=>PB7 <1=>PB9
#define I2C1_SDA_PORT_ID 0
#if (I2C1_SDA_PORT_ID == 0)
#define I2C1_SDA_PORT B
#define I2C1_SDA_PIN  GPIO_PIN_7
#elif (I2C1_SDA_PORT_ID == 1)
#define I2C1_SDA_PORT B
#define I2C1_SDA_PIN  GPIO_PIN_9
#else
#error "Invalid I2C1_SDA Pin Configuration!"
#endif

//   <e> I2C1 Interrupt
//   <i> Must be enabled when using DMA.
#define I2C1_IT_ENABLE          0
//      <o> I2C1 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of I2C1
#define I2C1_IT_PRIORITY        2
//      <o> I2C1 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of I2C1
#define I2C1_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0 <5=>5
//     <i>  Selects DMA Stream (only Stream 0 or 5 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define I2C1_RX_DMA             0
#define I2C1_RX_DMA_NUMBER      1
#define I2C1_RX_DMA_STREAM      0
#define I2C1_RX_DMA_CHANNEL     1
#define I2C1_RX_DMA_PRIORITY    0
#define I2C1_RX_DMA_IT_PRIORITY 2
#define I2C1_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1 <6=>6 <7=>7
//     <i>  Selects DMA Stream (only Stream 1 or 6 or 7 can be used)
//     <o3> Channel <0=>0 <1=>1
//     <i>  Selects DMA Channel (only Channel 0 or 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define I2C1_TX_DMA             0
#define I2C1_TX_DMA_NUMBER      1
#define I2C1_TX_DMA_STREAM      6
#define I2C1_TX_DMA_CHANNEL     1
#define I2C1_TX_DMA_PRIORITY    0
#define I2C1_TX_DMA_IT_PRIORITY 1
#define I2C1_TX_DMA_IT_SUB      4

// </e>

// <e> I2C2 (Inter-integrated Circuit Interface 2)
#define I2C2_ENABLE             1

//   <o> I2C2_SCL Pin <0=>PF1 <1=>PH4 <2=>PB10
#define I2C2_SCL_PORT_ID        1
#if (I2C2_SCL_PORT_ID == 0)
#define I2C2_SCL_PORT F
#define I2C2_SCL_PIN  GPIO_PIN_1
#elif (I2C2_SCL_PORT_ID == 1)
#define I2C2_SCL_PORT H
#define I2C2_SCL_PIN  GPIO_PIN_4
#elif (I2C2_SCL_PORT_ID == 2)
#define I2C2_SCL_PORT B
#define I2C2_SCL_PIN  GPIO_PIN_10
#else
#error "Invalid I2C2_SCL Pin Configuration!"
#endif

//   <o> I2C2_SDA Pin <0=>PF0 <1=>PH5 <2=>PB11 <3=>PB3 <4=>PB9
#define I2C2_SDA_PORT_ID 1
#if (I2C2_SDA_PORT_ID == 0)
#define I2C2_SDA_PORT F
#define I2C2_SDA_PIN  GPIO_PIN_0
#elif (I2C2_SDA_PORT_ID == 1)
#define I2C2_SDA_PORT H
#define I2C2_SDA_PIN  GPIO_PIN_5
#elif (I2C2_SDA_PORT_ID == 2)
#define I2C2_SDA_PORT B
#define I2C2_SDA_PIN  GPIO_PIN_11
#elif (I2C2_SDA_PORT_ID == 3)
#define I2C2_SDA_PORT B
#define I2C2_SDA_PIN  GPIO_PIN_3
#elif (I2C2_SDA_PORT_ID == 4)
#define I2C2_SDA_PORT B
#define I2C2_SDA_PIN  GPIO_PIN_9
#else
#error "Invalid I2C2_SDA Pin Configuration!"
#endif

//   <e> I2C2 Interrupt
//   <i> Must be enabled when using DMA.
#define I2C2_IT_ENABLE          0
//      <o> I2C2 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of I2C2
#define I2C2_IT_PRIORITY        2
//      <o> I2C2 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of I2C2
#define I2C2_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <2=>2 <3=>3
//     <i>  Selects DMA Stream (only Stream 2 or 3 can be used)
//     <o3> Channel <7=>7
//     <i>  Selects DMA Channel (only Channel 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define I2C2_RX_DMA             0
#define I2C2_RX_DMA_NUMBER      1
#define I2C2_RX_DMA_STREAM      2
#define I2C2_RX_DMA_CHANNEL     7
#define I2C2_RX_DMA_PRIORITY    0
#define I2C2_RX_DMA_IT_PRIORITY 2
#define I2C2_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <7=>7
//     <i>  Selects DMA Stream (only Stream 7 can be used)
//     <o3> Channel <7=>7
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define I2C2_TX_DMA             0
#define I2C2_TX_DMA_NUMBER      1
#define I2C2_TX_DMA_STREAM      7
#define I2C2_TX_DMA_CHANNEL     7
#define I2C2_TX_DMA_PRIORITY    0
#define I2C2_TX_DMA_IT_PRIORITY 1
#define I2C2_TX_DMA_IT_SUB      4

// </e>

// <e> I2C3 (Inter-integrated Circuit Interface 3)
#define I2C3_ENABLE             0

//   <o> I2C3_SCL Pin <0=>PH7 <1=>PA8
#define I2C3_SCL_PORT_ID        0
#if (I2C3_SCL_PORT_ID == 0)
#define I2C3_SCL_PORT H
#define I2C3_SCL_PIN  GPIO_PIN_7
#elif (I2C3_SCL_PORT_ID == 1)
#define I2C3_SCL_PORT A
#define I2C3_SCL_PIN  GPIO_PIN_8
#else
#error "Invalid I2C3_SCL Pin Configuration!"
#endif

//   <o> I2C3_SDA Pin <0=>PH8 <1=>PC9 <2=>PB4 <3=>PB8
#define I2C3_SDA_PORT_ID 0
#if (I2C3_SDA_PORT_ID == 0)
#define I2C3_SDA_PORT H
#define I2C3_SDA_PIN  GPIO_PIN_8
#elif (I2C3_SDA_PORT_ID == 1)
#define I2C3_SDA_PORT C
#define I2C3_SDA_PIN  GPIO_PIN_9
#elif (I2C3_SDA_PORT_ID == 2)
#define I2C3_SDA_PORT B
#define I2C3_SDA_PIN  GPIO_PIN_4
#elif (I2C3_SDA_PORT_ID == 3)
#define I2C3_SDA_PORT B
#define I2C3_SDA_PIN  GPIO_PIN_8
#else
#error "Invalid I2C3_SDA Pin Configuration!"
#endif

//   <e> I2C3 Interrupt
//   <i> Must be enabled when using DMA.
#define I2C3_IT_ENABLE          1
//      <o> I2C3 Interrupt Priority <0-15>
//      <i> The Interrupt Priority of I2C3
#define I2C3_IT_PRIORITY        2
//      <o> I2C3 Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of I2C3
#define I2C3_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <1=>1 <2=>2
//     <i>  Selects DMA Stream (only Stream 1 or 2 can be used)
//     <o3> Channel <1=>1 <3=>3
//     <i>  Selects DMA Channel (only Channel 1 or 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define I2C3_RX_DMA             1
#define I2C3_RX_DMA_NUMBER      1
#define I2C3_RX_DMA_STREAM      2
#define I2C3_RX_DMA_CHANNEL     3
#define I2C3_RX_DMA_PRIORITY    0
#define I2C3_RX_DMA_IT_PRIORITY 2
#define I2C3_RX_DMA_IT_SUB      2

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <4=>4 <5=>5
//     <i>  Selects DMA Stream (only Stream 4 or 5 can be used)
//     <o3> Channel <3=>3 <6=>6
//     <i>  Selects DMA Channel (only Channel 3 or 6 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define I2C3_TX_DMA             1
#define I2C3_TX_DMA_NUMBER      1
#define I2C3_TX_DMA_STREAM      4
#define I2C3_TX_DMA_CHANNEL     3
#define I2C3_TX_DMA_PRIORITY    0
#define I2C3_TX_DMA_IT_PRIORITY 1
#define I2C3_TX_DMA_IT_SUB      4

// </e>

// <e> SPI1 (Serial Peripheral Interface 1)
#define SPI1_ENABLE             0

//   <o> SPI1_MISO Pin <0=>Not Used <1=>PA6 <2=>PB4
#define SPI1_MISO_PORT_ID       1
#if (SPI1_MISO_PORT_ID == 0)
#define SPI1_MISO 0
#elif (SPI1_MISO_PORT_ID == 1)
#define SPI1_MISO      1
#define SPI1_MISO_PORT A
#define SPI1_MISO_PIN  GPIO_PIN_6
#elif (SPI1_MISO_PORT_ID == 2)
#define SPI1_MISO      1
#define SPI1_MISO_PORT B
#define SPI1_MISO_PIN  GPIO_PIN_4
#else
#error "Invalid SPI1_MISO Pin Configuration!"
#endif

//   <o> SPI1_MOSI Pin <0=>Not Used <1=>PA7 <2=>PB5
#define SPI1_MOSI_PORT_ID 1
#if (SPI1_MOSI_PORT_ID == 0)
#define SPI1_MOSI 0
#elif (SPI1_MOSI_PORT_ID == 1)
#define SPI1_MOSI      1
#define SPI1_MOSI_PORT A
#define SPI1_MOSI_PIN  GPIO_PIN_7
#elif (SPI1_MOSI_PORT_ID == 2)
#define SPI1_MOSI      1
#define SPI1_MOSI_PORT B
#define SPI1_MOSI_PIN  GPIO_PIN_5
#else
#error "Invalid SPI1_MOSI Pin Configuration!"
#endif

//   <o> SPI1_SCK Pin <0=>PA5 <1=>PB3
#define SPI1_SCK_PORT_ID 0
#if (SPI1_SCK_PORT_ID == 0)
#define SPI1_SCK_PORT A
#define SPI1_SCK_PIN  GPIO_PIN_5
#elif (SPI1_SCK_PORT_ID == 1)
#define SPI1_SCK_PORT B
#define SPI1_SCK_PIN  GPIO_PIN_3
#else
#error "Invalid SPI1_SCK Pin Configuration!"
#endif

//   <o> SPI1_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15
#define SPI1_NSS_PORT_ID 1
#if (SPI1_NSS_PORT_ID == 0)
#define SPI1_NSS 0
#elif (SPI1_NSS_PORT_ID == 1)
#define SPI1_NSS      1
#define SPI1_NSS_PORT A
#define SPI1_NSS_PIN  GPIO_PIN_4
#elif (SPI1_NSS_PORT_ID == 2)
#define SPI1_NSS      1
#define SPI1_NSS_PORT A
#define SPI1_NSS_PIN  GPIO_PIN_15
#else
#error "Invalid SPI1_NSS Pin Configuration!"
#endif

//   <e> SPI1 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI1_IT_ENABLE          0
//     <o> SPI1 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of SPI1
#define SPI1_IT_PRIORITY        2
//     <o> SPI1 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of SPI1
#define SPI1_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0 <2=>2
//     <i>  Selects DMA Stream (only Stream 0 or 2 can be used)
//     <o3> Channel <3=>3
//     <i>  Selects DMA Channel (only Channel 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI1_RX_DMA             0
#define SPI1_RX_DMA_NUMBER      2
#define SPI1_RX_DMA_STREAM      0
#define SPI1_RX_DMA_CHANNEL     3
#define SPI1_RX_DMA_PRIORITY    0
#define SPI1_RX_DMA_IT_PRIORITY 2
#define SPI1_RX_DMA_IT_SUB      4

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <2=>2 <3=>3 <5=>5
//     <i>  Selects DMA Stream (only Stream 2 or 3 or 5 can be used)
//     <o3> Channel <2=>2 <3=>3
//     <i>  Selects DMA Channel (only Channel 2 or 3 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI1_TX_DMA             0
#define SPI1_TX_DMA_NUMBER      2
#define SPI1_TX_DMA_STREAM      5
#define SPI1_TX_DMA_CHANNEL     3
#define SPI1_TX_DMA_PRIORITY    0
#define SPI1_TX_DMA_IT_PRIORITY 2
#define SPI1_TX_DMA_IT_SUB      2

// </e>

// <e> SPI2 (Serial Peripheral Interface 2)
#define SPI2_ENABLE             0

//   <o> SPI2_MISO Pin <0=>Not Used <1=>PB14 <2=>PC2 <3=>PI2 <4=>PA12
#define SPI2_MISO_PORT_ID       1
#if (SPI2_MISO_PORT_ID == 0)
#define SPI2_MISO 0
#elif (SPI2_MISO_PORT_ID == 1)
#define SPI2_MISO      1
#define SPI2_MISO_PORT B
#define SPI2_MISO_PIN  GPIO_PIN_14
#elif (SPI2_MISO_PORT_ID == 2)
#define SPI2_MISO      1
#define SPI2_MISO_PORT C
#define SPI2_MISO_PIN  GPIO_PIN_2
#elif (SPI2_MISO_PORT_ID == 3)
#define SPI2_MISO      1
#define SPI2_MISO_PORT I
#define SPI2_MISO_PIN  GPIO_PIN_2
#elif (SPI2_MISO_PORT_ID == 4)
#define SPI2_MISO      1
#define SPI2_MISO_PORT A
#define SPI2_MISO_PIN  GPIO_PIN_12
#else
#error "Invalid SPI2_MISO Pin Configuration!"
#endif

//   <o> SPI2_MOSI Pin <0=>Not Used <1=>PB15 <2=>PC3 <3=>PI3 <4=>PA10
#define SPI2_MOSI_PORT_ID 1
#if (SPI2_MOSI_PORT_ID == 0)
#define SPI2_MOSI 0
#elif (SPI2_MOSI_PORT_ID == 1)
#define SPI2_MOSI      1
#define SPI2_MOSI_PORT B
#define SPI2_MOSI_PIN  GPIO_PIN_15
#elif (SPI2_MOSI_PORT_ID == 2)
#define SPI2_MOSI      1
#define SPI2_MOSI_PORT C
#define SPI2_MOSI_PIN  GPIO_PIN_3
#elif (SPI2_MOSI_PORT_ID == 3)
#define SPI2_MOSI      1
#define SPI2_MOSI_PORT I
#define SPI2_MOSI_PIN  GPIO_PIN_3
#elif (SPI2_MOSI_PORT_ID == 4)
#define SPI2_MOSI      1
#define SPI2_MOSI_PORT A
#define SPI2_MOSI_PIN  GPIO_PIN_10
#else
#error "Invalid SPI2_MOSI Pin Configuration!"
#endif

//   <o> SPI2_SCK Pin <0=>PB10 <1=>PB13 <2=>PC7 <3=>PD3 <4=>PI1 <5=>PA9
#define SPI2_SCK_PORT_ID 1
#if (SPI2_SCK_PORT_ID == 0)
#define SPI2_SCK_PORT B
#define SPI2_SCK_PIN  GPIO_PIN_10
#elif (SPI2_SCK_PORT_ID == 1)
#define SPI2_SCK_PORT B
#define SPI2_SCK_PIN  GPIO_PIN_13
#elif (SPI2_SCK_PORT_ID == 2)
#define SPI2_SCK_PORT C
#define SPI2_SCK_PIN  GPIO_PIN_7
#elif (SPI2_SCK_PORT_ID == 3)
#define SPI2_SCK_PORT D
#define SPI2_SCK_PIN  GPIO_PIN_3
#elif (SPI2_SCK_PORT_ID == 4)
#define SPI2_SCK_PORT I
#define SPI2_SCK_PIN  GPIO_PIN_1
#elif (SPI2_SCK_PORT_ID == 5)
#define SPI2_SCK_PORT A
#define SPI2_SCK_PIN  GPIO_PIN_9
#else
#error "Invalid SPI2_SCK Pin Configuration!"
#endif

//   <o> SPI2_NSS Pin <0=>Not Used <1=>PB9 <2=>PB12 <3=>PI0 <4=>PA11
#define SPI2_NSS_PORT_ID 1
#if (SPI2_NSS_PORT_ID == 0)
#define SPI2_NSS 0
#elif (SPI2_NSS_PORT_ID == 1)
#define SPI2_NSS      1
#define SPI2_NSS_PORT B
#define SPI2_NSS_PIN  GPIO_PIN_9
#elif (SPI2_NSS_PORT_ID == 2)
#define SPI2_NSS      1
#define SPI2_NSS_PORT B
#define SPI2_NSS_PIN  GPIO_PIN_12
#elif (SPI2_NSS_PORT_ID == 3)
#define SPI2_NSS      1
#define SPI2_NSS_PORT I
#define SPI2_NSS_PIN  GPIO_PIN_0
#elif (SPI2_NSS_PORT_ID == 4)
#define SPI2_NSS      1
#define SPI2_NSS_PORT A
#define SPI2_NSS_PIN  GPIO_PIN_11
#else
#error "Invalid SPI2_NSS Pin Configuration!"
#endif

//   <e> SPI2 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI2_IT_ENABLE          1
//     <o> SPI2 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of SPI2
#define SPI2_IT_PRIORITY        2
//     <o> SPI2 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of SPI2
#define SPI2_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <3=>3
//     <i>  Selects DMA Stream (only Stream 3 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI2_RX_DMA             1
#define SPI2_RX_DMA_NUMBER      1
#define SPI2_RX_DMA_STREAM      3
#define SPI2_RX_DMA_CHANNEL     0
#define SPI2_RX_DMA_PRIORITY    0
#define SPI2_RX_DMA_IT_PRIORITY 2
#define SPI2_RX_DMA_IT_SUB      4

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <4=>4
//     <i>  Selects DMA Stream (only Stream 4 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI2_TX_DMA             1
#define SPI2_TX_DMA_NUMBER      1
#define SPI2_TX_DMA_STREAM      4
#define SPI2_TX_DMA_CHANNEL     0
#define SPI2_TX_DMA_PRIORITY    0
#define SPI2_TX_DMA_IT_PRIORITY 2
#define SPI2_TX_DMA_IT_SUB      2

// </e>

// <e> SPI3 (Serial Peripheral Interface 3)
#define SPI3_ENABLE             0

//   <o> SPI3_MISO Pin <0=>Not Used <1=>PB4 <2=>PC11
#define SPI3_MISO_PORT_ID       1
#if (SPI3_MISO_PORT_ID == 0)
#define SPI3_MISO 0
#elif (SPI3_MISO_PORT_ID == 1)
#define SPI3_MISO      1
#define SPI3_MISO_PORT B
#define SPI3_MISO_PIN  GPIO_PIN_4
#elif (SPI3_MISO_PORT_ID == 2)
#define SPI3_MISO      1
#define SPI3_MISO_PORT C
#define SPI3_MISO_PIN  GPIO_PIN_11
#else
#error "Invalid SPI3_MISO Pin Configuration!"
#endif

//   <o> SPI3_MOSI Pin <0=>Not Used <1=>PB5 <2=>PC12 <3=>PD6
#define SPI3_MOSI_PORT_ID 1
#if (SPI3_MOSI_PORT_ID == 0)
#define SPI3_MOSI 0
#elif (SPI3_MOSI_PORT_ID == 1)
#define SPI3_MOSI      1
#define SPI3_MOSI_PORT B
#define SPI3_MOSI_PIN  GPIO_PIN_5
#elif (SPI3_MOSI_PORT_ID == 2)
#define SPI3_MOSI      1
#define SPI3_MOSI_PORT C
#define SPI3_MOSI_PIN  GPIO_PIN_12
#elif (SPI3_MOSI_PORT_ID == 3)
#define SPI3_MOSI      1
#define SPI3_MOSI_PORT D
#define SPI3_MOSI_PIN  GPIO_PIN_6
#else
#error "Invalid SPI3_MOSI Pin Configuration!"
#endif

//   <o> SPI3_SCK Pin <0=>PB3 <1=>PB12 <2=>PC10
#define SPI3_SCK_PORT_ID 0
#if (SPI3_SCK_PORT_ID == 0)
#define SPI3_SCK_PORT B
#define SPI3_SCK_PIN  GPIO_PIN_3
#elif (SPI3_SCK_PORT_ID == 1)
#define SPI3_SCK_PORT B
#define SPI3_SCK_PIN  GPIO_PIN_12
#elif (SPI3_SCK_PORT_ID == 2)
#define SPI3_SCK_PORT C
#define SPI3_SCK_PIN  GPIO_PIN_10
#else
#error "Invalid SPI3_SCK Pin Configuration!"
#endif

//   <o> SPI3_NSS Pin <0=>Not Used <1=>PA4 <2=>PA15
#define SPI3_NSS_PORT_ID 1
#if (SPI3_NSS_PORT_ID == 0)
#define SPI3_NSS 0
#elif (SPI3_NSS_PORT_ID == 1)
#define SPI3_NSS      1
#define SPI3_NSS_PORT A
#define SPI3_NSS_PIN  GPIO_PIN_4
#elif (SPI3_NSS_PORT_ID == 2)
#define SPI3_NSS      1
#define SPI3_NSS_PORT A
#define SPI3_NSS_PIN  GPIO_PIN_15
#else
#error "Invalid SPI3_NSS Pin Configuration!"
#endif

//   <e> SPI3 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI3_IT_ENABLE          1
//     <o> SPI3 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of SPI3
#define SPI3_IT_PRIORITY        2
//     <o> SPI3 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of SPI3
#define SPI3_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <0=>0 <2=>2
//     <i>  Selects DMA Stream (only Stream 0 or 2 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI3_RX_DMA             1
#define SPI3_RX_DMA_NUMBER      1
#define SPI3_RX_DMA_STREAM      0
#define SPI3_RX_DMA_CHANNEL     0
#define SPI3_RX_DMA_PRIORITY    0
#define SPI3_RX_DMA_IT_PRIORITY 2
#define SPI3_RX_DMA_IT_SUB      4

//   <e> DMA Tx
//     <o1> Number <1=>1
//     <i>  Selects DMA Number (only DMA1 can be used)
//     <o2> Stream <5=>5 <7=>7
//     <i>  Selects DMA Stream (only Stream 5 or 7 can be used)
//     <o3> Channel <0=>0
//     <i>  Selects DMA Channel (only Channel 0 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI3_TX_DMA             1
#define SPI3_TX_DMA_NUMBER      1
#define SPI3_TX_DMA_STREAM      5
#define SPI3_TX_DMA_CHANNEL     0
#define SPI3_TX_DMA_PRIORITY    0
#define SPI3_TX_DMA_IT_PRIORITY 2
#define SPI3_TX_DMA_IT_SUB      2

// </e>

// <e> SPI4 (Serial Peripheral Interface 4)
#define SPI4_ENABLE             0

//   <o> SPI4_MISO Pin <0=>Not Used <1=>PA11 <2=>PE5 <3=>PE13
#define SPI4_MISO_PORT_ID       2
#if (SPI4_MISO_PORT_ID == 0)
#define SPI4_MISO 0
#elif (SPI4_MISO_PORT_ID == 1)
#define SPI4_MISO      1
#define SPI4_MISO_PORT A
#define SPI4_MISO_PIN  GPIO_PIN_11
#elif (SPI4_MISO_PORT_ID == 2)
#define SPI4_MISO      1
#define SPI4_MISO_PORT E
#define SPI4_MISO_PIN  GPIO_PIN_5
#elif (SPI4_MISO_PORT_ID == 3)
#define SPI4_MISO      1
#define SPI4_MISO_PORT E
#define SPI4_MISO_PIN  GPIO_PIN_13
#else
#error "Invalid SPI4_MISO Pin Configuration!"
#endif

//   <o> SPI4_MOSI Pin <0=>Not Used <1=>PA1 <2=>PE6 <3=>PE14
#define SPI4_MOSI_PORT_ID 2
#if (SPI4_MOSI_PORT_ID == 0)
#define SPI4_MOSI 0
#elif (SPI4_MOSI_PORT_ID == 1)
#define SPI4_MOSI      1
#define SPI4_MOSI_PORT A
#define SPI4_MOSI_PIN  GPIO_PIN_1
#elif (SPI4_MOSI_PORT_ID == 2)
#define SPI4_MOSI      1
#define SPI4_MOSI_PORT E
#define SPI4_MOSI_PIN  GPIO_PIN_6
#elif (SPI4_MOSI_PORT_ID == 3)
#define SPI4_MOSI      1
#define SPI4_MOSI_PORT E
#define SPI4_MOSI_PIN  GPIO_PIN_14
#else
#error "Invalid SPI4_MOSI Pin Configuration!"
#endif

//   <o> SPI4_SCK Pin <0=>PB13 <1=>PE2 <2=>PE12
#define SPI4_SCK_PORT_ID 1
#if (SPI4_SCK_PORT_ID == 0)
#define SPI4_SCK_PORT B
#define SPI4_SCK_PIN  GPIO_PIN_13
#elif (SPI4_SCK_PORT_ID == 1)
#define SPI4_SCK_PORT E
#define SPI4_SCK_PIN  GPIO_PIN_2
#elif (SPI4_SCK_PORT_ID == 2)
#define SPI4_SCK_PORT E
#define SPI4_SCK_PIN  GPIO_PIN_12
#else
#error "Invalid SPI4_SCK Pin Configuration!"
#endif

//   <o> SPI4_NSS Pin <0=>Not Used <1=>PB12 <2=>PE4 <3=>PE11
#define SPI4_NSS_PORT_ID 2
#if (SPI4_NSS_PORT_ID == 0)
#define SPI4_NSS 0
#elif (SPI4_NSS_PORT_ID == 1)
#define SPI4_NSS      1
#define SPI4_NSS_PORT B
#define SPI4_NSS_PIN  GPIO_PIN_12
#elif (SPI4_NSS_PORT_ID == 2)
#define SPI4_NSS      1
#define SPI4_NSS_PORT E
#define SPI4_NSS_PIN  GPIO_PIN_4
#elif (SPI4_NSS_PORT_ID == 3)
#define SPI4_NSS      1
#define SPI4_NSS_PORT E
#define SPI4_NSS_PIN  GPIO_PIN_11
#else
#error "Invalid SPI4_NSS Pin Configuration!"
#endif

//   <e> SPI4 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI4_IT_ENABLE          1
//     <o> SPI4 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of SPI4
#define SPI4_IT_PRIORITY        2
//     <o> SPI4 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of SPI4
#define SPI4_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <0=>0 <3=>3 <4=>4
//     <i>  Selects DMA Stream (only Stream 0 or 3 can be used)
//     <o3> Channel <4=>4 <5=>5
//     <i>  Selects DMA Channel (only Channel 4 or 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI4_RX_DMA             1
#define SPI4_RX_DMA_NUMBER      1
#define SPI4_RX_DMA_STREAM      0
#define SPI4_RX_DMA_CHANNEL     0
#define SPI4_RX_DMA_PRIORITY    0
#define SPI4_RX_DMA_IT_PRIORITY 2
#define SPI4_RX_DMA_IT_SUB      4

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <1=>1 <4=>4
//     <i>  Selects DMA Stream (only Stream 1 or 4 can be used)
//     <o3> Channel <4=>4 <5=>5
//     <i>  Selects DMA Channel (only Channel 4 or 5 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI4_TX_DMA             1
#define SPI4_TX_DMA_NUMBER      1
#define SPI4_TX_DMA_STREAM      5
#define SPI4_TX_DMA_CHANNEL     0
#define SPI4_TX_DMA_PRIORITY    0
#define SPI4_TX_DMA_IT_PRIORITY 2
#define SPI4_TX_DMA_IT_SUB      2

// </e>

// <e> SPI5 (Serial Peripheral Interface 5)
#define SPI5_ENABLE             1

//   <o> SPI5_MISO Pin <0=>Not Used <1=>PA12 <2=>PE5 <3=>PE13 <4=>PF8 <5=>PH7
#define SPI5_MISO_PORT_ID       4
#if (SPI5_MISO_PORT_ID == 0)
#define SPI5_MISO 0
#elif (SPI5_MISO_PORT_ID == 1)
#define SPI5_MISO      1
#define SPI5_MISO_PORT A
#define SPI5_MISO_PIN  GPIO_PIN_12
#elif (SPI5_MISO_PORT_ID == 2)
#define SPI5_MISO      1
#define SPI5_MISO_PORT E
#define SPI5_MISO_PIN  GPIO_PIN_5
#elif (SPI5_MISO_PORT_ID == 3)
#define SPI5_MISO      1
#define SPI5_MISO_PORT E
#define SPI5_MISO_PIN  GPIO_PIN_13
#elif (SPI5_MISO_PORT_ID == 4)
#define SPI5_MISO      1
#define SPI5_MISO_PORT F
#define SPI5_MISO_PIN  GPIO_PIN_8
#elif (SPI5_MISO_PORT_ID == 5)
#define SPI5_MISO      1
#define SPI5_MISO_PORT H
#define SPI5_MISO_PIN  GPIO_PIN_7
#else
#error "Invalid SPI5_MISO Pin Configuration!"
#endif

//   <o> SPI5_MOSI Pin <0=>Not Used <1=>PA10 <2=>PB8 <3=>PE6 <4=>PE14 <5=>PF9
//   <6=>PF11
#define SPI5_MOSI_PORT_ID 5
#if (SPI5_MOSI_PORT_ID == 0)
#define SPI5_MOSI 0
#elif (SPI5_MOSI_PORT_ID == 1)
#define SPI5_MOSI      1
#define SPI5_MOSI_PORT A
#define SPI5_MOSI_PIN  GPIO_PIN_10
#elif (SPI5_MOSI_PORT_ID == 2)
#define SPI5_MOSI      1
#define SPI5_MOSI_PORT B
#define SPI5_MOSI_PIN  GPIO_PIN_8
#elif (SPI5_MOSI_PORT_ID == 3)
#define SPI5_MOSI      1
#define SPI5_MOSI_PORT E
#define SPI5_MOSI_PIN  GPIO_PIN_6
#elif (SPI5_MOSI_PORT_ID == 4)
#define SPI5_MOSI      1
#define SPI5_MOSI_PORT E
#define SPI5_MOSI_PIN  GPIO_PIN_14
#elif (SPI5_MOSI_PORT_ID == 5)
#define SPI5_MOSI      1
#define SPI5_MOSI_PORT F
#define SPI5_MOSI_PIN  GPIO_PIN_9
#elif (SPI5_MOSI_PORT_ID == 6)
#define SPI5_MOSI      1
#define SPI5_MOSI_PORT F
#define SPI5_MOSI_PIN  GPIO_PIN_11
#else
#error "Invalid SPI5_MOSI Pin Configuration!"
#endif

//   <o> SPI5_SCK Pin <0=>PB0 <1=>PE2 <2=>PE12 <3=>PF7 <4=>PH6
#define SPI5_SCK_PORT_ID 3
#if (SPI5_SCK_PORT_ID == 0)
#define SPI5_SCK_PORT B
#define SPI5_SCK_PIN  GPIO_PIN_0
#elif (SPI5_SCK_PORT_ID == 1)
#define SPI5_SCK_PORT E
#define SPI5_SCK_PIN  GPIO_PIN_2
#elif (SPI5_SCK_PORT_ID == 2)
#define SPI5_SCK_PORT E
#define SPI5_SCK_PIN  GPIO_PIN_12
#elif (SPI5_SCK_PORT_ID == 3)
#define SPI5_SCK_PORT F
#define SPI5_SCK_PIN  GPIO_PIN_7
#elif (SPI5_SCK_PORT_ID == 4)
#define SPI5_SCK_PORT H
#define SPI5_SCK_PIN  GPIO_PIN_6
#else
#error "Invalid SPI5_SCK Pin Configuration!"
#endif

//   <o> SPI5_NSS Pin <0=>Not Used <1=>PB1 <2=>PE4 <3=>PE11 <4=>PF6 <5=>PH5
#define SPI5_NSS_PORT_ID 0
#if (SPI5_NSS_PORT_ID == 0)
#define SPI5_NSS 0
#elif (SPI5_NSS_PORT_ID == 1)
#define SPI5_NSS      1
#define SPI5_NSS_PORT B
#define SPI5_NSS_PIN  GPIO_PIN_1
#elif (SPI5_NSS_PORT_ID == 2)
#define SPI5_NSS      1
#define SPI5_NSS_PORT E
#define SPI5_NSS_PIN  GPIO_PIN_4
#elif (SPI5_NSS_PORT_ID == 3)
#define SPI5_NSS      1
#define SPI5_NSS_PORT E
#define SPI5_NSS_PIN  GPIO_PIN_11
#elif (SPI5_NSS_PORT_ID == 4)
#define SPI5_NSS      1
#define SPI5_NSS_PORT F
#define SPI5_NSS_PIN  GPIO_PIN_6
#elif (SPI5_NSS_PORT_ID == 5)
#define SPI5_NSS      1
#define SPI5_NSS_PORT H
#define SPI5_NSS_PIN  GPIO_PIN_5
#else
#error "Invalid SPI5_NSS Pin Configuration!"
#endif

//   <e> SPI5 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI5_IT_ENABLE          0
//     <o> SPI5 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of SPI5
#define SPI5_IT_PRIORITY        2
//     <o> SPI5 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of SPI5
#define SPI5_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <3=>3 <5=>5
//     <i>  Selects DMA Stream (only Stream 3 or 5 can be used)
//     <o3> Channel <2=>2 <7=>7
//     <i>  Selects DMA Channel (only Channel 2 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI5_RX_DMA             0
#define SPI5_RX_DMA_NUMBER      2
#define SPI5_RX_DMA_STREAM      3
#define SPI5_RX_DMA_CHANNEL     2
#define SPI5_RX_DMA_PRIORITY    0
#define SPI5_RX_DMA_IT_PRIORITY 2
#define SPI5_RX_DMA_IT_SUB      4

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <4=>4 <5=>5 <6=>6
//     <i>  Selects DMA Stream (only Stream 4 or 6 can be used)
//     <o3> Channel <2=>2 <5=>5 <7=>7
//     <i>  Selects DMA Channel (only Channel 2 or 7 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI5_TX_DMA             0
#define SPI5_TX_DMA_NUMBER      2
#define SPI5_TX_DMA_STREAM      4
#define SPI5_TX_DMA_CHANNEL     2
#define SPI5_TX_DMA_PRIORITY    0
#define SPI5_TX_DMA_IT_PRIORITY 2
#define SPI5_TX_DMA_IT_SUB      2

// </e>

// <e> SPI6 (Serial Peripheral Interface 6)
#define SPI6_ENABLE             0

//   <o> SPI6_MISO Pin <0=>Not Used <1=>PG12
#define SPI6_MISO_PORT_ID       1
#if (SPI6_MISO_PORT_ID == 0)
#define SPI6_MISO 0
#elif (SPI6_MISO_PORT_ID == 1)
#define SPI6_MISO      1
#define SPI6_MISO_PORT G
#define SPI6_MISO_PIN  GPIO_PIN_12
#else
#error "Invalid SPI6_MISO Pin Configuration!"
#endif

//   <o> SPI6_MOSI Pin <0=>Not Used <1=>PG14
#define SPI6_MOSI_PORT_ID 1
#if (SPI6_MOSI_PORT_ID == 0)
#define SPI6_MOSI 0
#elif (SPI6_MOSI_PORT_ID == 1)
#define SPI6_MOSI      1
#define SPI6_MOSI_PORT G
#define SPI6_MOSI_PIN  GPIO_PIN_14
#else
#error "Invalid SPI6_MOSI Pin Configuration!"
#endif

//   <o> SPI6_SCK Pin <0=>PG13
#define SPI6_SCK_PORT_ID 0
#if (SPI6_SCK_PORT_ID == 0)
#define SPI6_SCK_PORT G
#define SPI6_SCK_PIN  GPIO_PIN_13
#else
#error "Invalid SPI6_SCK Pin Configuration!"
#endif

//   <o> SPI6_NSS Pin <0=>Not Used <1=>PG8
#define SPI6_NSS_PORT_ID 0
#if (SPI6_NSS_PORT_ID == 0)
#define SPI6_NSS 0
#elif (SPI6_NSS_PORT_ID == 1)
#define SPI6_NSS      1
#define SPI6_NSS_PORT G
#define SPI6_NSS_PIN  GPIO_PIN_8
#else
#error "Invalid SPI6_NSS Pin Configuration!"
#endif

//   <e> SPI6 Interrupt
//   <i> Must be enabled when using DMA.
#define SPI6_IT_ENABLE          1
//     <o> SPI6 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of SPI6
#define SPI6_IT_PRIORITY        2
//     <o> SPI6 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of SPI6
#define SPI6_IT_SUB             3
//   </e>

//   <e> DMA Rx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <6=>6
//     <i>  Selects DMA Stream (only Stream 6 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Rx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Rx
//     <o6> DMA Rx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Rx
//   </e>
#define SPI6_RX_DMA             1
#define SPI6_RX_DMA_NUMBER      2
#define SPI6_RX_DMA_STREAM      6
#define SPI6_RX_DMA_CHANNEL     1
#define SPI6_RX_DMA_PRIORITY    0
#define SPI6_RX_DMA_IT_PRIORITY 2
#define SPI6_RX_DMA_IT_SUB      4

//   <e> DMA Tx
//     <o1> Number <2=>2
//     <i>  Selects DMA Number (only DMA2 can be used)
//     <o2> Stream <5=>5
//     <i>  Selects DMA Stream (only Stream 5 can be used)
//     <o3> Channel <1=>1
//     <i>  Selects DMA Channel (only Channel 1 can be used)
//     <o4> Priority <0=>Low <1=>Medium <2=>High <3=>Very High
//     <i>  Selects DMA Priority
//     <o5> DMA Tx Interrupt Priority <0-15>
//     <i>  The Interrupt Priority of DMA Tx
//     <o6> DMA Tx Interrupt SubPriority <0-15>
//     <i>  The Interrupt SubPriority of DMA Tx
//   </e>
#define SPI6_TX_DMA             1
#define SPI6_TX_DMA_NUMBER      2
#define SPI6_TX_DMA_STREAM      5
#define SPI6_TX_DMA_CHANNEL     1
#define SPI6_TX_DMA_PRIORITY    0
#define SPI6_TX_DMA_IT_PRIORITY 2
#define SPI6_TX_DMA_IT_SUB      2

// </e>

// <e> CAN1 (Controller Area Network 1)
#define CAN1_ENABLE             0

//   <o> CAN1_RX Pin <0=>PA11 <1=>PB8 <2=>PD0 <3=>PI9 <4=>PG0
#define CAN1_RX_PORT_ID         0
#if (CAN1_RX_PORT_ID == 0)
#define CAN1_RX_PORT A
#define CAN1_RX_PIN  GPIO_PIN_11
#elif (CAN1_RX_PORT_ID == 1)
#define CAN1_RX_PORT B
#define CAN1_RX_PIN  GPIO_PIN_8
#elif (CAN1_RX_PORT_ID == 2)
#define CAN1_RX_PORT D
#define CAN1_RX_PIN  GPIO_PIN_0
#elif (CAN1_RX_PORT_ID == 3)
#define CAN1_RX_PORT I
#define CAN1_RX_PIN  GPIO_PIN_9
#elif (CAN1_RX_PORT_ID == 4)
#define CAN1_RX_PORT G
#define CAN1_RX_PIN  GPIO_PIN_0
#else
#error "Invalid CAN1_RX Pin Configuration!"
#endif

//   <o> CAN1_TX Pin <0=>PA12 <1=>PB9 <2=>PD1 <3=>PH13 <4=>PG1
#define CAN1_TX_PORT_ID 0
#if (CAN1_TX_PORT_ID == 0)
#define CAN1_TX_PORT A
#define CAN1_TX_PIN  GPIO_PIN_12
#elif (CAN1_TX_PORT_ID == 1)
#define CAN1_TX_PORT B
#define CAN1_TX_PIN  GPIO_PIN_9
#elif (CAN1_TX_PORT_ID == 2)
#define CAN1_TX_PORT D
#define CAN1_TX_PIN  GPIO_PIN_1
#elif (CAN1_TX_PORT_ID == 3)
#define CAN1_TX_PORT H
#define CAN1_TX_PIN  GPIO_PIN_13
#elif (CAN1_TX_PORT_ID == 4)
#define CAN1_TX_PORT G
#define CAN1_TX_PIN  GPIO_PIN_1
#else
#error "Invalid CAN1_TX Pin Configuration!"
#endif

//   <e> Enable CAN Transmit Interrupt
#define CAN1_ENABLE_TX_IT    0
//     <o> CAN Transmit Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Transmit
#define CAN1_TX_IT_PRIORITY  2
//     <o> CAN Transmit Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Transmit
#define CAN1_TX_IT_SUB       3
//   </e>

//   <e> Enable CAN Receive FIFO0 Interrupt
#define CAN1_ENABLE_RX0_IT   0
//     <o> CAN Receive FIFO0 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN1_RX0_IT_PRIORITY 2
//     <o> CAN Receive FIFO0 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN1_RX0_IT_SUB      3
//   </e>

//   <e> Enable CAN Receive FIFO1 Interrupt
#define CAN1_ENABLE_RX1_IT   0
//     <o> CAN Receive FIFO1 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO1
#define CAN1_RX1_IT_PRIORITY 2
//     <o> CAN Receive FIFO1 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO1
#define CAN1_RX1_IT_SUB      3
//   </e>

//   <e> Enable CAN Stauts Change or Error (SCE) Interrupt
#define CAN1_ENABLE_SCE_IT   0
//     <o> CAN SCE Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN1_SCE_IT_PRIORITY 2
//     <o> CAN SCE Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN1_SCE_IT_SUB      3
//   </e>

// </e>

// <e> CAN2 (Controller Area Network 2)
#define CAN2_ENABLE          0

//   <o> CAN2_RX Pin <0=>PB5 <1=>PB12 <2=>PG11
#define CAN2_RX_PORT_ID      0
#if (CAN2_RX_PORT_ID == 0)
#define CAN2_RX_PORT B
#define CAN2_RX_PIN  GPIO_PIN_5
#elif (CAN2_RX_PORT_ID == 1)
#define CAN2_RX_PORT B
#define CAN2_RX_PIN  GPIO_PIN_12
#elif (CAN2_RX_PORT_ID == 2)
#define CAN2_RX_PORT G
#define CAN2_RX_PIN  GPIO_PIN_11
#else
#error "Invalid CAN2_RX Pin Configuration!"
#endif

//   <o> CAN2_TX Pin <0=>PB6 <1=>PB13 <2=>PG12
#define CAN2_TX_PORT_ID 0
#if (CAN2_TX_PORT_ID == 0)
#define CAN2_TX_PORT B
#define CAN2_TX_PIN  GPIO_PIN_6
#elif (CAN2_TX_PORT_ID == 1)
#define CAN2_TX_PORT B
#define CAN2_TX_PIN  GPIO_PIN_13
#elif (CAN2_TX_PORT_ID == 2)
#define CAN2_TX_PORT G
#define CAN2_TX_PIN  GPIO_PIN_12
#else
#error "Invalid CAN2_TX Pin Configuration!"
#endif

//   <e> Enable CAN Receive FIFO0 Interrupt
#define CAN2_ENABLE_RX0_IT   0
//     <o> CAN Receive FIFO0 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN2_RX0_IT_PRIORITY 2
//     <o> CAN Receive FIFO0 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN2_RX0_IT_SUB      3
//   </e>

//   <e> Enable CAN Receive FIFO1 Interrupt
#define CAN2_ENABLE_RX1_IT   0
//     <o> CAN Receive FIFO1 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO1
#define CAN2_RX1_IT_PRIORITY 2
//     <o> CAN Receive FIFO1 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO1
#define CAN2_RX1_IT_SUB      3
//   </e>

//   <e> Enable CAN Stauts Change or Error (SCE) Interrupt
#define CAN2_ENABLE_SCE_IT   0
//     <o> CAN SCE Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN2_SCE_IT_PRIORITY 2
//     <o> CAN SCE Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN2_SCE_IT_SUB      3
//   </e>

// </e>

// <e> CAN3 (Controller Area Network 3)
// <i> Available only on STM32F413xx and STM32F423xx device series
#define CAN3_ENABLE          0

//   <o> CAN3_RX Pin <0=>PA8 <1=>PB3
#define CAN3_RX_PORT_ID      0
#if (CAN3_RX_PORT_ID == 0)
#define CAN3_RX_PORT A
#define CAN3_RX_PIN  GPIO_PIN_8
#elif (CAN3_RX_PORT_ID == 1)
#define CAN3_RX_PORT B
#define CAN3_RX_PIN  GPIO_PIN_3
#else
#error "Invalid CAN3_RX Pin Configuration!"
#endif

//   <o> CAN3_TX Pin <0=>PA15 <1=>PB4
#define CAN3_TX_PORT_ID 0
#if (CAN3_TX_PORT_ID == 0)
#define CAN3_TX_PORT A
#define CAN3_TX_PIN  GPIO_PIN_15
#elif (CAN3_TX_PORT_ID == 1)
#define CAN3_TX_PORT B
#define CAN3_TX_PIN  GPIO_PIN_4
#else
#error "Invalid CAN3_TX Pin Configuration!"
#endif

//   <e> Enable CAN Receive FIFO0 Interrupt
#define CAN3_ENABLE_RX0_IT     0
//     <o> CAN Receive FIFO0 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN3_RX0_IT_PRIORITY   2
//     <o> CAN Receive FIFO0 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN3_RX0_IT_SUB        3
//   </e>

//   <e> Enable CAN Receive FIFO1 Interrupt
#define CAN3_ENABLE_RX1_IT     0
//     <o> CAN Receive FIFO1 Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO1
#define CAN3_RX1_IT_PRIORITY   2
//     <o> CAN Receive FIFO1 Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO1
#define CAN3_RX1_IT_SUB        3
//   </e>

//   <e> Enable CAN Stauts Change or Error (SCE) Interrupt
#define CAN3_ENABLE_SCE_IT     0
//     <o> CAN SCE Interrupt Priority <0-15>
//     <i> The Interrupt Priority of CAN Receive FIFO0
#define CAN3_SCE_IT_PRIORITY   2
//     <o> CAN SCE Interrupt SubPriority <0-15>
//     <i> The Interrupt SubPriority of CAN Receive FIFO0
#define CAN3_SCE_IT_SUB        3
//   </e>

// </e>

// <e> ETH (Ethernet Interface)
#define ETH_ENABLE             0

//   <e> MII (Media Independent Interface)
#define ETH_MII                0

//     <o> ETH_MII_TX_CLK Pin <0=>PC3
#define ETH_MII_TX_CLK_PORT_ID 0
#if (ETH_MII_TX_CLK_PORT_ID == 0)
#define ETH_MII_TX_CLK_PORT C
#define ETH_MII_TX_CLK_PIN  GPIO_PIN_3
#else
#error "Invalid ETH_MII_TX_CLK Pin Configuration!"
#endif
//     <o> ETH_MII_TXD0 Pin <0=>PB12 <1=>PG13
#define ETH_MII_TXD0_PORT_ID 0
#if (ETH_MII_TXD0_PORT_ID == 0)
#define ETH_MII_TXD0_PORT B
#define ETH_MII_TXD0_PIN  GPIO_PIN_12
#elif (ETH_MII_TXD0_PORT_ID == 1)
#define ETH_MII_TXD0_PORT G
#define ETH_MII_TXD0_PIN  GPIO_PIN_13
#else
#error "Invalid ETH_MII_TXD0 Pin Configuration!"
#endif
//     <o> ETH_MII_TXD1 Pin <0=>PB13 <1=>PG14
#define ETH_MII_TXD1_PORT_ID 0
#if (ETH_MII_TXD1_PORT_ID == 0)
#define ETH_MII_TXD1_PORT B
#define ETH_MII_TXD1_PIN  GPIO_PIN_13
#elif (ETH_MII_TXD1_PORT_ID == 1)
#define ETH_MII_TXD1_PORT G
#define ETH_MII_TXD1_PIN  GPIO_PIN_14
#else
#error "Invalid ETH_MII_TXD1 Pin Configuration!"
#endif
//     <o> ETH_MII_TXD2 Pin <0=>PC2
#define ETH_MII_TXD2_PORT_ID 0
#if (ETH_MII_TXD2_PORT_ID == 0)
#define ETH_MII_TXD2_PORT C
#define ETH_MII_TXD2_PIN  GPIO_PIN_2
#else
#error "Invalid ETH_MII_TXD2 Pin Configuration!"
#endif
//     <o> ETH_MII_TXD3 Pin <0=>PB8 <1=>PE2
#define ETH_MII_TXD3_PORT_ID 0
#if (ETH_MII_TXD3_PORT_ID == 0)
#define ETH_MII_TXD3_PORT B
#define ETH_MII_TXD3_PIN  GPIO_PIN_8
#elif (ETH_MII_TXD3_PORT_ID == 1)
#define ETH_MII_TXD3_PORT E
#define ETH_MII_TXD3_PIN  GPIO_PIN_2
#else
#error "Invalid ETH_MII_TXD3 Pin Configuration!"
#endif
//     <o> ETH_MII_TX_EN Pin <0=>PB11 <1=>PG11
#define ETH_MII_TX_EN_PORT_ID 0
#if (ETH_MII_TX_EN_PORT_ID == 0)
#define ETH_MII_TX_EN_PORT B
#define ETH_MII_TX_EN_PIN  GPIO_PIN_11
#elif (ETH_MII_TX_EN_PORT_ID == 1)
#define ETH_MII_TX_EN_PORT G
#define ETH_MII_TX_EN_PIN  GPIO_PIN_11
#else
#error "Invalid ETH_MII_TX_EN Pin Configuration!"
#endif
//     <o> ETH_MII_RX_CLK Pin <0=>PA1
#define ETH_MII_RX_CLK_PORT_ID 0
#if (ETH_MII_RX_CLK_PORT_ID == 0)
#define ETH_MII_RX_CLK_PORT A
#define ETH_MII_RX_CLK_PIN  GPIO_PIN_1
#else
#error "Invalid ETH_MII_RX_CLK Pin Configuration!"
#endif
//     <o> ETH_MII_RXD0 Pin <0=>PC4
#define ETH_MII_RXD0_PORT_ID 0
#if (ETH_MII_RXD0_PORT_ID == 0)
#define ETH_MII_RXD0_PORT C
#define ETH_MII_RXD0_PIN  GPIO_PIN_4
#else
#error "Invalid ETH_MII_RXD0 Pin Configuration!"
#endif
//     <o> ETH_MII_RXD1 Pin <0=>PC5
#define ETH_MII_RXD1_PORT_ID 0
#if (ETH_MII_RXD1_PORT_ID == 0)
#define ETH_MII_RXD1_PORT C
#define ETH_MII_RXD1_PIN  GPIO_PIN_5
#else
#error "Invalid ETH_MII_RXD1 Pin Configuration!"
#endif
//     <o> ETH_MII_RXD2 Pin <0=>PB0 <1=>PH6
#define ETH_MII_RXD2_PORT_ID 0
#if (ETH_MII_RXD2_PORT_ID == 0)
#define ETH_MII_RXD2_PORT B
#define ETH_MII_RXD2_PIN  GPIO_PIN_0
#elif (ETH_MII_RXD2_PORT_ID == 1)
#define ETH_MII_RXD2_PORT H
#define ETH_MII_RXD2_PIN  GPIO_PIN_6
#else
#error "Invalid ETH_MII_RXD2 Pin Configuration!"
#endif
//     <o> ETH_MII_RXD3 Pin <0=>PB1 <1=>PH7
#define ETH_MII_RXD3_PORT_ID 0
#if (ETH_MII_RXD3_PORT_ID == 0)
#define ETH_MII_RXD3_PORT B
#define ETH_MII_RXD3_PIN  GPIO_PIN_1
#elif (ETH_MII_RXD3_PORT_ID == 1)
#define ETH_MII_RXD3_PORT H
#define ETH_MII_RXD3_PIN  GPIO_PIN_7
#else
#error "Invalid ETH_MII_RXD3 Pin Configuration!"
#endif
//     <o> ETH_MII_RX_DV Pin <0=>PA7
#define ETH_MII_RX_DV_PORT_ID 0
#if (ETH_MII_RX_DV_PORT_ID == 0)
#define ETH_MII_RX_DV_PORT A
#define ETH_MII_RX_DV_PIN  GPIO_PIN_7
#else
#error "Invalid ETH_MII_RX_DV Pin Configuration!"
#endif
//     <o> ETH_MII_RX_ER Pin <0=>PB10 <1=>PI10
#define ETH_MII_RX_ER_PORT_ID 0
#if (ETH_MII_RX_ER_PORT_ID == 0)
#define ETH_MII_RX_ER_PORT B
#define ETH_MII_RX_ER_PIN  GPIO_PIN_10
#elif (ETH_MII_RX_ER_PORT_ID == 1)
#define ETH_MII_RX_ER_PORT I
#define ETH_MII_RX_ER_PIN  GPIO_PIN_10
#else
#error "Invalid ETH_MII_RX_ER Pin Configuration!"
#endif
//     <o> ETH_MII_CRS Pin <0=>PA0 <1=>PH2
#define ETH_MII_CRS_PORT_ID 0
#if (ETH_MII_CRS_PORT_ID == 0)
#define ETH_MII_CRS_PORT A
#define ETH_MII_CRS_PIN  GPIO_PIN_0
#elif (ETH_MII_CRS_PORT_ID == 1)
#define ETH_MII_CRS_PORT H
#define ETH_MII_CRS_PIN  GPIO_PIN_2
#else
#error "Invalid ETH_MII_CRS Pin Configuration!"
#endif
//     <o> ETH_MII_COL Pin <0=>PA3 <1=>PH3
#define ETH_MII_COL_PORT_ID 0
#if (ETH_MII_COL_PORT_ID == 0)
#define ETH_MII_COL_PORT A
#define ETH_MII_COL_PIN  GPIO_PIN_3
#elif (ETH_MII_COL_PORT_ID == 1)
#define ETH_MII_COL_PORT H
#define ETH_MII_COL_PIN  GPIO_PIN_3
#else
#error "Invalid ETH_MII_COL Pin Configuration!"
#endif

//   </e>

//   <e> RMII (Reduced Media Independent Interface)
#define ETH_RMII              0

//     <o> ETH_RMII_TXD0 Pin <0=>PB12 <1=>PG13
#define ETH_RMII_TXD0_PORT_ID 1
#if (ETH_RMII_TXD0_PORT_ID == 0)
#define ETH_RMII_TXD0_PORT B
#define ETH_RMII_TXD0_PIN  GPIO_PIN_12
#elif (ETH_RMII_TXD0_PORT_ID == 1)
#define ETH_RMII_TXD0_PORT G
#define ETH_RMII_TXD0_PIN  GPIO_PIN_13
#else
#error "Invalid ETH_RMII_TXD0 Pin Configuration!"
#endif
//     <o> ETH_RMII_TXD1 Pin <0=>PB13 <1=>PG14
#define ETH_RMII_TXD1_PORT_ID 1
#if (ETH_RMII_TXD1_PORT_ID == 0)
#define ETH_RMII_TXD1_PORT B
#define ETH_RMII_TXD1_PIN  GPIO_PIN_13
#elif (ETH_RMII_TXD1_PORT_ID == 1)
#define ETH_RMII_TXD1_PORT G
#define ETH_RMII_TXD1_PIN  GPIO_PIN_14
#else
#error "Invalid ETH_RMII_TXD1 Pin Configuration!"
#endif
//     <o> ETH_RMII_TX_EN Pin <0=>PB11 <1=>PG11
#define ETH_RMII_TX_EN_PORT_ID 0
#if (ETH_RMII_TX_EN_PORT_ID == 0)
#define ETH_RMII_TX_EN_PORT B
#define ETH_RMII_TX_EN_PIN  GPIO_PIN_11
#elif (ETH_RMII_TX_EN_PORT_ID == 1)
#define ETH_RMII_TX_EN_PORT G
#define ETH_RMII_TX_EN_PIN  GPIO_PIN_11
#else
#error "Invalid ETH_RMII_TX_EN Pin Configuration!"
#endif
//     <o> ETH_RMII_RXD0 Pin <0=>PC4
#define ETH_RMII_RXD0_PORT_ID 0
#if (ETH_RMII_RXD0_PORT_ID == 0)
#define ETH_RMII_RXD0_PORT C
#define ETH_RMII_RXD0_PIN  GPIO_PIN_4
#else
#error "Invalid ETH_RMII_RXD0 Pin Configuration!"
#endif
//     <o> ETH_RMII_RXD1 Pin <0=>PC5
#define ETH_RMII_RXD1_PORT_ID 0
#if (ETH_RMII_RXD1_PORT_ID == 0)
#define ETH_RMII_RXD1_PORT C
#define ETH_RMII_RXD1_PIN  GPIO_PIN_5
#else
#error "Invalid ETH_RMII_RXD1 Pin Configuration!"
#endif
//     <o> ETH_RMII_REF_CLK Pin <0=>PA1
#define ETH_RMII_REF_CLK_PORT_ID 0
#if (ETH_RMII_REF_CLK_PORT_ID == 0)
#define ETH_RMII_REF_CLK_PORT A
#define ETH_RMII_REF_CLK_PIN  GPIO_PIN_1
#else
#error "Invalid ETH_RMII_REF_CLK Pin Configuration!"
#endif
//     <o> ETH_RMII_CRS_DV Pin <0=>PA7
#define ETH_RMII_CRS_DV_PORT_ID 0
#if (ETH_RMII_CRS_DV_PORT_ID == 0)
#define ETH_RMII_CRS_DV_PORT A
#define ETH_RMII_CRS_DV_PIN  GPIO_PIN_7
#else
#error "Invalid ETH_RMII_CRS_DV Pin Configuration!"
#endif

//   </e>

//   <o> ETH Interrupt Priority <0-15>
//   <i> The Interrupt Priority of ETH
#define ETH_IT_PRIORITY     2
//   <o> ETH Interrupt SubPriority <0-15>
//   <i> The Interrupt SubPriority of ETH
#define ETH_IT_SUB          3

//   <h> Management Data Interface
//     <o> ETH_MDC Pin <0=>PC1
#define ETH_MDI_MDC_PORT_ID 0
#if (ETH_MDI_MDC_PORT_ID == 0)
#define ETH_MDI_MDC_PORT C
#define ETH_MDI_MDC_PIN  GPIO_PIN_1
#else
#error "Invalid ETH_MDC Pin Configuration!"
#endif
//     <o> ETH_MDIO Pin <0=>PA2
#define ETH_MDI_MDIO_PORT_ID 0
#if (ETH_MDI_MDIO_PORT_ID == 0)
#define ETH_MDI_MDIO_PORT A
#define ETH_MDI_MDIO_PIN  GPIO_PIN_2
#else
#error "Invalid ETH_MDIO Pin Configuration!"
#endif
//   </h>

// </e>

// <e> RTC (Real Time Clock)
#define RTC_ENABLE            0

//   <e> RTC Wake Up Interrupt
#define RTC_WKUP_IT_ENABLE    0
//      <o> RTC Wake up Interrupt Priority <0-15>
//      <i> The Interrupt Priority of RTC Wake up
#define RTC_WKUP_IT_PRIORITY  2
//      <o> RTC Wake up Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of RTC Wake up
#define RTC_WKUP_IT_SUB       3
//   </e>

//   <e> RTC Alarm Interrupt
#define RTC_ALARM_IT_ENABLE   0
//      <o> RTC Alarm  Interrupt Priority <0-15>
//      <i> The Interrupt Priority of RTC Alarm
#define RTC_ALARM_IT_PRIORITY 2
//      <o> RTC Alarm Interrupt SubPriority <0-15>
//      <i> The Interrupt SubPriority of RTC Alarm
#define RTC_ALARM_IT_SUB      3
//   </e>

// </e>

// <<< end of configuration section >>>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Enable and disable the clock of GPIO. */
#define _CSP_GPIO_PORT(x)          GPIO##x
#define CSP_GPIO_PORT(x)           _CSP_GPIO_PORT(x)
#define _CSP_GPIO_CLK_ENABLE(x)    __HAL_RCC_GPIO##x##_CLK_ENABLE()
#define CSP_GPIO_CLK_ENABLE(x)     _CSP_GPIO_CLK_ENABLE(x)

/* Pasting the DMA Stream. */
#define _CSP_DMA_STREAM(x, y)      DMA##x##_Stream##y
#define CSP_DMA_STREAM(x, y)       _CSP_DMA_STREAM(x, y)

/* Pasting the DMA Stream IRQn and IRQHandler. */
#define _CSP_DMA_STREAM(x, y)      DMA##x##_Stream##y
#define CSP_DMA_STREAM(x, y)       _CSP_DMA_STREAM(x, y)

#define _CSP_DMA_STREAM_IRQn(x, y) DMA##x##_Stream##y##_IRQn
#define CSP_DMA_STREAM_IRQn(x, y)  _CSP_DMA_STREAM_IRQn(x, y)

#define _CSP_DMA_STREAM_IRQ(x, y)  DMA##x##_Stream##y##_IRQHandler
#define CSP_DMA_STREAM_IRQ(x, y)   _CSP_DMA_STREAM_IRQ(x, y)

/* Pasting the DMA Channel */
#define _CSP_DMA_CHANNEL(x)        DMA_CHANNEL_##x
#define CSP_DMA_CHANNEL(x)         _CSP_DMA_CHANNEL(x)

/* Set DMA Priority */
#define CSP_DMA_PRIORITY(x)        ((x) << DMA_SxCR_PL_Pos)

/* Enable and disable the clock of DMA. */
#define _CSP_DMA_CLK_ENABLE(x)     __HAL_RCC_DMA##x##_CLK_ENABLE()
#define CSP_DMA_CLK_ENABLE(x)      _CSP_DMA_CLK_ENABLE(x)

/* CSP memory management functions. */
#define CSP_MALLOC                 malloc
#define CSP_FREE                   free
#define CSP_REALLOC                realloc
#include <stdlib.h>

/* Devices Family header files.  */
#include "stm32f4xx_hal.h"

#if (USART1_ENABLE || USART2_ENABLE || USART3_ENABLE || UART4_ENABLE ||        \
     UART5_ENABLE || USART6_ENABLE || UART7_ENABLE || UART8_ENABLE ||          \
     UART9_ENABLE || UART10_ENABLE)
#include "../UART_STM32F4xx.h"
#endif /* (USART1_ENABLE || USART2_ENABLE || USART3_ENABLE || UART4_ENABLE ||  \
           UART5_ENABLE || USART6_ENABLE || UART7_ENABLE || UART8_ENABLE ||    \
           UART9_ENABLE || UART10_ENABLE) */

#if (I2C1_ENABLE || I2C2_ENABLE || I2C3_ENABLE)
#include "../I2C_STM32F4xx.h"
#endif /* (I2C1_ENABLE || I2C2_ENABLE || I2C3_ENABLE) */

#if (SPI1_ENABLE || SPI2_ENABLE || SPI3_ENABLE || SPI4_ENABLE ||               \
     SPI5_ENABLE || SPI6_ENABLE)
#include "../SPI_STM32F4xx.h"
#endif /* (SPI1_ENABLE || SPI2_ENABLE || SPI3_ENABLE || SPI4_ENABLE ||         \
           SPI5_ENABLE || SPI6_ENABLE) */

#if (CAN1_ENABLE || CAN2_ENABLE || CAN3_ENABLE)
#include "../CAN_STM32F4xx.h"
#endif /* (CAN1_ENABLE || CAN2_ENABLE || CAN3_ENABLE) */

#if (ETH_ENABLE)
#include "../ETH_STM32F4xx.h"
#endif /* ETH_ENABLE */

#if (RTC_ENABLE)
#include "../RTC_STM32F4xx.h"
#endif /* RTC_ENABLE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CSP_CONFIG_H */
