
///INCLUDES 

#include "wdt.h"

//GLOBAL VARIABLES

wdt_confg_t wdt_cfg;

//local function 

static void wdt_cb (void){

while(1);
}
//APIs implemtation

int main(void){
wdt_cfg.timeout_ms =1000;
wdt_cfg.use_resetmode  =1;
wdt_cfg.use_testmode  =1;
wdt_cfg.wdt_index  = WDT0;
wdt_cfg.wdt_int = USE_NORMAL_INT;
wdt_cfg.wdt_cb= wdt_cb;
wdt_init(&wdt_cfg);	
     while(1){
			 wdt_reset(WDT0);





       }



}
