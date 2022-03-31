/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/*
 * This demo application creates five co-routines and three tasks (four including
 * the idle task).  The co-routines execute as part of the idle task hook.
 *
 * Five of the created co-routines are the standard 'co-routine flash'
 * co-routines contained within the Demo/Common/Minimal/crflash.c file and
 * documented on the FreeRTOS.org WEB site.
 *
 * The flash co-routines control LED's zero to four.  LED five is toggled each
 * time the string is transmitted on the UART.  LED six is toggled each time
 * the string is CORRECTLY received on the UART.  LED seven is latched on should
 * an error be detected in any task or co-routine.
 *
 * In addition the idle task makes calls to prvSetAndCheckRegisters().
 * This simply loads the general purpose registers with a known value, then
 * checks each register to ensure the held value is still correct.  As a low
 * priority task this checking routine is likely to get repeatedly swapped in
 * and out.  A register being found to contain an incorrect value is therefore
 * indicative of an error in the task switching mechanism.
 *
 */

/*
 * This example file, taken from the FreeRTOS source distribution,
 * has been modified by Imperas to provide a simple demo for use
 * with OVP
 *
 */

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

#include "bsp.h"

/* Some default delays to use */
#define TASK_ONE_DELAY        (  600 / portTICK_RATE_MS )
#define TASK_TWO_DELAY        ( 1200 / portTICK_RATE_MS )

/* The time to delay between writing each character to the UART. */
#define CHAR_WRITE_DELAY      ( 2 / portTICK_RATE_MS )
/* The time to delay between writing each string to the UART. */
#define STRING_WRITE_DELAY    ( 400 / portTICK_RATE_MS )

/* The number of flash co-routines to create. */
#define mainNUM_FLASH_CO_ROUTINES    ( 5 )


/* The LED's toggled by the various tasks. */
#define FAIL_LED                ( 7 )
#define TASK_ONE_LED            ( 6 )
#define TASK_TWO_LED            ( 5 )

/*-----------------------------------------------------------*/

// Some simple Tasks
static void vTaskOne( void * pvParameters );
static void vTaskTwo( void * pvParameters );
void vUARTTask( void * pvParameters );

#define UART_TASK_PRIORITY          ( tskIDLE_PRIORITY     )
#define TASK_ONE_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1 )
#define TASK_TWO_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1 )

/*
 * Function to simply set a known value into the general purpose registers
 * then read them back to ensure they remain set correctly.  An incorrect value
 * being indicative of an error in the task switching mechanism.
 */
void prvSetAndCheckRegisters( void ) __attribute__ (( naked ));

/*
 * Latch the LED that indicates that an error has occurred.
 */
void vSetErrorLED( void );

/*
 * Sets up the PLL and ports used by the demo.
 */
static void prvSetupHardware( void );

/*-----------------------------------------------------------*/

void main( void )
{
    /* Create the queue used to communicate between the UART ISR and the Comms
    Rx task. */

    /* Setup the ports used by the demo and the clock. */
    prvSetupHardware();

    /* Create the co-routines that flash the LED's. */
    vStartFlashCoRoutines( mainNUM_FLASH_CO_ROUTINES );

    xTaskCreate( vTaskOne, "Task One", configMINIMAL_STACK_SIZE, NULL, TASK_ONE_TASK_PRIORITY, NULL );
    xTaskCreate( vTaskTwo, "Task Two", configMINIMAL_STACK_SIZE, NULL, TASK_TWO_TASK_PRIORITY, NULL );

    xTaskCreate( vUARTTask, "UART Task", configMINIMAL_STACK_SIZE, NULL, UART_TASK_PRIORITY, NULL );

    /* Start the scheduler running the tasks and co-routines just created. */
    vTaskStartScheduler();

    /* Should not get here unless we did not have enough memory to start the
    scheduler. */
    for( ;; );
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
    vParTestInitialise();
}

/*-----------------------------------------------------------*/

void prvWriteString( const char *pcString )
{
    while( *pcString )
    {
//        vTaskDelay( CHAR_WRITE_DELAY );
        uartWrite( *pcString );
        pcString++;
    }
    // Carriage return / linefeed
    uartWrite( 0x0d );
    uartWrite( 0x0a );
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    /* The co-routines are executed in the idle task using the idle task
    hook. */
    for( ;; )
    {
        /* Schedule the co-routines. */
        vCoRoutineSchedule();

        /* Run the register check function between each co-routine. */
        prvSetAndCheckRegisters();
    }
}
/*-----------------------------------------------------------*/

static void vTaskOne( void * pvParameters )
{
    for( ;; )
    {
        vParTestToggleLED( TASK_ONE_LED );
        /* Wait until it is time to toggle LED. */
        vTaskDelay( TASK_ONE_DELAY );
    }
}

static void vTaskTwo( void * pvParameters )
{
    for( ;; )
    {
        vParTestToggleLED( TASK_TWO_LED );
        /* Wait until it is time to toggle LED. */
        vTaskDelay( TASK_TWO_DELAY );
    }
}

/*-----------------------------------------------------------*/

void vUARTTask( void * pvParameters )
{
unsigned portBASE_TYPE uxIndex;

/* The strings that are written to the UART. */
const char *pcStringsToDisplay[] = {
                                            "Imperas Software Ltd",
                                            "OVP Virtual Platform",
                                            "ARM OVP Fast Processor Model Cortex-M3 running FreeRTOS 7.1.1",
                                            "www.FreeRTOS.org",
                                            ""
                                       };

    uxIndex = 0;

    for( ;; )
    {
        /* Display the string on the UART. */
        prvWriteString( pcStringsToDisplay[ uxIndex ] );

        /* Move on to the next string - wrapping if necessary. */
        uxIndex++;
        if( *( pcStringsToDisplay[ uxIndex ] ) == 0x00 )
        {
            uxIndex = 0;
            /* Longer pause on the last string to be sent. */
            vTaskDelay( STRING_WRITE_DELAY * 2 );
        }

        /* Wait until it is time to move onto the next string. */
        vTaskDelay( STRING_WRITE_DELAY );
    }
}

void vSetErrorLED( void )
{
    vParTestSetLED( FAIL_LED, pdTRUE );
}
/*-----------------------------------------------------------*/

void prvSetAndCheckRegisters( void )
{
    /* Fill the general purpose registers with known values. */
    __asm volatile( "    mov r11,      #10\n"
                    "    add r0,  r11, #1\n"
                    "    add r1,  r11, #2\n"
                    "    add r2,  r11, #3\n"
                    "    add r3,  r11, #4\n"
                    "    add r4,  r11, #5\n"
                    "    add r5,  r11, #6\n"
                    "    add r6,  r11, #7\n"
                    "    add r7,  r11, #8\n"
                    "    add r8,  r11, #9\n"
                    "    add r9,  r11, #10\n"
                    "    add r10, r11, #11\n"
                    "    add r12, r11, #12" );

    /* Check the values are as expected. */
    __asm volatile( "    cmp r11, #10\n"
                    "    bne set_error_led\n"
                    "    cmp r0, #11\n"
                    "    bne set_error_led\n"
                    "    cmp r1, #12\n"
                    "    bne set_error_led\n"
                    "    cmp r2, #13\n"
                    "    bne set_error_led\n"
                    "    cmp r3, #14\n"
                    "    bne set_error_led\n"
                    "    cmp r4, #15\n"
                    "    bne set_error_led\n"
                    "    cmp r5, #16\n"
                    "    bne set_error_led\n"
                    "    cmp r6, #17\n"
                    "    bne set_error_led\n"
                    "    cmp r7, #18\n"
                    "    bne set_error_led\n"
                    "    cmp r8, #19\n"
                    "    bne set_error_led\n"
                    "    cmp r9, #20\n"
                    "    bne set_error_led\n"
                    "    cmp r10, #21\n"
                    "    bne set_error_led\n"
                    "    cmp r12, #22\n"
                    "    bne set_error_led\n"
                    "    bx lr" );

  __asm volatile( "set_error_led:\n"
                    "    push {r14}\n"
                    "    ldr r1, =vSetErrorLED\n"
                    "    blx r1\n"
                    "    pop {r14}\n"
                    "    bx lr" );
}
/*-----------------------------------------------------------*/
