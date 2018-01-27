#include <linux/linkage.h>

/* you can directly access the variables 
 * total_count and orig_divbyzero
 * (defined in main.c)
 * Set orig_divbyzero to the original
 * divbyzero handler in main.c
 */

ENTRY(__wrapper_divbyzero)
	/* NOT_IMPLEMENTED */
ENDPROC(__wrapper_divbyzero)
