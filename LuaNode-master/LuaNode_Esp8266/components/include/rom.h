// Headers to the various functions in the rom (as we discover them)

#ifndef _ROM_H_
#define _ROM_H_

#include "c_types.h"

typedef struct {
	uint32_t state[5];
	uint32_t count[2];
	uint8_t buffer[64];
} SHA1_CTX;

// Cycle-counter
extern unsigned int xthal_get_ccount (void);

// 2, 3 = reset (module dependent?), 4 = wdt
int rtc_get_reset_reason (void);

// Hardware exception handling
struct exception_frame
{
  uint32_t epc;
  uint32_t ps;
  uint32_t sar;
  uint32_t unused;
  union {
    struct {
      uint32_t a0;
      // note: no a1 here!
      uint32_t a2;
      uint32_t a3;
      uint32_t a4;
      uint32_t a5;
      uint32_t a6;
      uint32_t a7;
      uint32_t a8;
      uint32_t a9;
      uint32_t a10;
      uint32_t a11;
      uint32_t a12;
      uint32_t a13;
      uint32_t a14;
      uint32_t a15;
    };
    uint32_t a_reg[15];
  };
  uint32_t cause;
};

/**
 * C-level exception handler callback prototype.
 *
 * Does not need an RFE instruction - it is called through a wrapper which
 * performs state capture & restore, as well as the actual RFE.
 *
 * @param ef An exception frame containing the relevant state from the
 *           exception triggering. This state may be manipulated and will
 *           be applied on return.
 * @param cause The exception cause number.
 */
typedef void (*exception_handler_fn) (struct exception_frame *ef, uint32_t cause);


#endif
