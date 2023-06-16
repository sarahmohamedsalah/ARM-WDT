#include "wdt.h"
#include "common.h"
//marcos
#define RCGCWD_REG ((*(volatile uint32_t *)(0x400FE000)))
#define WDTLOAD_REG(X)  (*((volatile uint32_t *)((0x40000000)+(X==0?0:0x1000))))
#define WDTCTL_REG(X)   (*((volatile uint32_t *)((0x40000008)+(X==0?0:0x1000))))
#define WDTRIS_REG(X)         (*((volatile uint32_t *)((0x40000010)+(X==0?0:0x1000))))
#define WDTTEST_REG(X)    (*((volatile uint32_t *)((0x40000018)+(X==0?0:0x1000))))


#define WRC_IDX   (31)
#define INTTYPE_IDX  (2)
#define  RESEN_IDX  (1)
#define  INTEN_IDX   (0)
#define  WDTRIS_IDX  (0)
#define  STALL_IDX (0)
#define INVALID_WDTn   (2)
#define RRC_IDX (1)//check it 
//global variables

static tpf_wdt_cb gpf_wdt_cb=NULL;
static uint32_t ga_timeout[INVALID_WDTn]= {0,0};
static uint32_t SystemCoreClock;
static volatile uint64_t timeout_ticks;
static void get_wdt_timeout(wdt_index_t wdt_index , uint32_t timeout_ms){

if(timeout_ms !=0 &&(wdt_index <INVALID_WDTn))
{
timeout_ticks =(uint64_t)(timeout_ms*(SystemCoreClock/1000));
ga_timeout[wdt_index]=(uint32_t)timeout_ticks;
WDTLOAD_REG(wdt_index)=ga_timeout[wdt_index];//value 
}else{
//invalid input
}}
static void wait_for_wdt1(wdt_index_t wdt_ind){
if(wdt_ind == WDT1){
while (!GET_BIT(WDTCTL_REG(WDT1),RRC_IDX));


}
}
	




int32_t wdt_init(wdt_confg_t*pwdt_confg){
    
	int32_t result =ERROR;
	if(pwdt_confg != NULL)
	{
	  SET_BIT(RCGCWD_REG ,pwdt_confg->wdt_index);
		get_wdt_timeout(pwdt_confg->wdt_index,pwdt_confg->timeout_ms);
		if(pwdt_confg->wdt_index==WDT1)
			wait_for_wdt1(pwdt_confg->wdt_index);
		if(pwdt_confg->use_resetmode)
		{
		SET_BIT(WDTCTL_REG(pwdt_confg->wdt_index),RESEN_IDX);
			}
		wait_for_wdt1(pwdt_confg->wdt_index);
		if(pwdt_confg->wdt_int==USE_NMI)
		{
		SET_BIT(WDTCTL_REG(pwdt_confg->wdt_index),INTTYPE_IDX);
		wait_for_wdt1(pwdt_confg->wdt_index);
			SET_BIT(WDTCTL_REG (pwdt_confg->wdt_index),INTEN_IDX);
			        wait_for_wdt1(pwdt_confg->wdt_index);
			        NVIC_EnableIRQ(WATCHDOG0_IRQn);
			        __enable_irq();
		}	
		else if(pwdt_confg->wdt_int== USE_NORMAL_INT)
		{
		  SET_BIT(WDTCTL_REG(pwdt_confg->wdt_index),INTEN_IDX);
			wait_for_wdt1(pwdt_confg->wdt_index);
			NVIC_EnableIRQ(WATCHDOG0_IRQn);
			        __enable_irq();
		}
		if(pwdt_confg->use_testmode){
		SET_BIT(WDTTEST_REG(pwdt_confg->wdt_index),STALL_IDX);
			wait_for_wdt1(pwdt_confg->wdt_index);
		}
		if(pwdt_confg->wdt_cb != NULL){
		gpf_wdt_cb = pwdt_confg->wdt_cb;
		}
		result =SUCCESS;
	}else {
result =INVALID_INPUT;
	
}
return result;

}


void wdt_reset(wdt_index_t wdtn){
if(ga_timeout[wdtn] != 0)
{
WDTLOAD_REG(wdtn) =ga_timeout[wdtn];
}


}

boolean wdt_get_int_status(wdt_index_t wdtn)
{
boolean result = FALSE;
	if(GET_BIT(WDTRIS_REG(wdtn),WDTRIS_IDX))
	{
	result = TRUE ;
	}
	return result;
}


boolean wdt_deinit(wdt_index_t wdtn){
/*TODO CHECK FIRST ON THE LOCK */
	if(wdtn <  INVALID_WDTn){
	
	CLR_BIT(RCGCWD_REG,wdtn);
	}else {
	//invalid index 
	
	}}
