/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/

#include <stdio.h>
#include <stdlib.h>
#include "Driver Files\boards.h"

/*********************************************************************/

static volatile int ticks = 0;

extern void SysTick_Handler(void) {
  ticks++;
}

static void delay(int n) {
  unsigned endTicks = ticks + n;
  while (ticks < endTicks);
}

/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/
int main(void) {
    int count = 0;
    // Make sure SystemCoreClock is up-to-date
    SystemCoreClockUpdate();

  // Enable SysTick timer interrupt
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS|BSP_INIT_BUTTONS);

//--------------------------------------------------------------
 #if BLE_TEST

  ble_stack_init();



#endif
//--------------------------------------------------------------
    /* Toggle LEDs. */
    while (true)
    {
    if(bsp_board_button_state_get(BUTTON_1))
    {
      count++;
      if(count%3 == 0)
      {
        bsp_board_led_on(1);
        bsp_board_led_off(2);
        bsp_board_led_off(3);
      }
      if(count%3 == 1)
      {
        bsp_board_led_on(2);
        bsp_board_led_off(3);
        bsp_board_led_off(1);
      }
      if(count%3 == 2)
      {
        bsp_board_led_on(3);
        bsp_board_led_off(2);
        bsp_board_led_off(1);
      }
      delay(200);
    }
    }
}

/*************************** End of file ****************************/
