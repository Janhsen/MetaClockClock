/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */
#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */

/*! @name PORTC2 (number 45), LED_BLUE
  @{ */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_LED_BLUE_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_LED_BLUE_PIN 2U     /*!<@brief PORTC pin index: 2 */
                                           /* @} */

/*! @name PORTD0 (number 57), LANE0
  @{ */
#define BOARD_INITPINS_LANE0_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LANE0_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LANE0_PIN 0U     /*!<@brief PORTD pin index: 0 */
                                        /* @} */

/*! @name PORTD1 (number 58), LANE1
  @{ */
#define BOARD_INITPINS_LANE1_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LANE1_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LANE1_PIN 1U     /*!<@brief PORTD pin index: 1 */
                                        /* @} */

/*! @name PORTD2 (number 59), LANEq
  @{ */
#define BOARD_INITPINS_LANE2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LANE2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LANE2_PIN 2U     /*!<@brief PORTD pin index: 2 */
                                        /* @} */

/*! @name PORTD3 (number 60), LANE3
  @{ */
#define BOARD_INITPINS_LANE3_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LANE3_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LANE3_PIN 3U     /*!<@brief PORTD pin index: 3 */
                                        /* @} */

/*! @name PORTD4 (number 61), LANE4
  @{ */
#define BOARD_INITPINS_LANE4_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LANE4_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LANE4_PIN 4U     /*!<@brief PORTD pin index: 4 */
                                        /* @} */

/*! @name PORTC4 (number 49), LPUART_TX
  @{ */
#define BOARD_INITPINS_LPUART_TX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_LPUART_TX_PIN 4U     /*!<@brief PORTC pin index: 4 */
                                            /* @} */

/*! @name PORTC3 (number 46), LPUART_RX
  @{ */
#define BOARD_INITPINS_LPUART_RX_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_LPUART_RX_PIN 3U     /*!<@brief PORTC pin index: 3 */
                                            /* @} */

/*! @name PORTB17 (number 40), RS485_TX
  @{ */
#define BOARD_INITPINS_RS485_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_RS485_TX_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                           /* @} */

/*! @name PORTB16 (number 39), RS485_RX
  @{ */
#define BOARD_INITPINS_RS485_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_RS485_RX_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                           /* @} */

/*! @name PORTB2 (number 37), RS458_RTS
  @{ */
#define BOARD_INITPINS_RS458_RTS_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_RS458_RTS_PIN 2U     /*!<@brief PORTB pin index: 2 */
                                            /* @} */

/*! @name PORTD7 (number 64), BLE_MISO
  @{ */
#define BOARD_INITPINS_BLE_MISO_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_BLE_MISO_PIN 7U     /*!<@brief PORTD pin index: 7 */
                                           /* @} */

/*! @name PORTD6 (number 63), BLE_MOSI
  @{ */
#define BOARD_INITPINS_BLE_MOSI_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_BLE_MOSI_PIN 6U     /*!<@brief PORTD pin index: 6 */
                                           /* @} */

/*! @name PORTD5 (number 62), BLE_CLK
  @{ */
#define BOARD_INITPINS_BLE_CLK_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_BLE_CLK_PIN 5U     /*!<@brief PORTD pin index: 5 */
                                          /* @} */

/*! @name PORTC11 (number 56), BLE_CS
  @{ */
#define BOARD_INITPINS_BLE_CS_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_BLE_CS_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_BLE_CS_PIN 11U    /*!<@brief PORTC pin index: 11 */
                                         /* @} */

/*! @name PORTC10 (number 55), BLE_IRQ
  @{ */
#define BOARD_INITPINS_BLE_IRQ_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_INITPINS_BLE_IRQ_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_INITPINS_BLE_IRQ_PIN 10U    /*!<@brief PORTC pin index: 10 */
                                          /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/