
/* These functions control the VIC interrupts for the OR32.
 * The global interrupt enable control is defined elsewhere.
 */


/* Number of interrupt handlers */
#define MAX_INT_HANDLERS	32

/* Add interrupt handler */ 
int int_add(unsigned long vect, void (* handler)(void *), void *arg);

/* Initialize routine */
int int_init(void);

/* Enable interrupt */ 
int int_disable(unsigned long vect);

/* Enable interrupt */ 
int int_enable(unsigned long vect);
