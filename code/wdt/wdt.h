#include "common.h"
#include "TM4C123.h"
#include "core_cm4.h"
/*toda #define*/
typedef void(*tpf_wdt_cb)(void);

typedef enum{
WDT0=0,
WDT1=1,
INVALID_WDTn	
}wdt_index_t;

typedef enum{
USE_NORMAL_INT =0,
USE_NMI=1,
DISABLE_INT=2,	
INVALID_INT_VALUE
}wdt_int_t;

typedef struct{
  wdt_index_t  wdt_index;
	uint32_t   timeout_ms;
	boolean  use_testmode;
	boolean use_resetmode;
	wdt_int_t wdt_int;
	tpf_wdt_cb wdt_cb;
	
}wdt_confg_t;

int32_t wdt_init(wdt_confg_t*pwdt_confg);


void wdt_reset(wdt_index_t wdtn);

boolean wdt_get_int_status(wdt_index_t wdtn);



boolean wdt_deinit(wdt_index_t wdtn);
