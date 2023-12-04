/* 
 * File:   application.c
 * Author: AyaAli
 * Created on September 22, 2023, 10:24 AM
 */
#include "application.h"

timer3_config_t timer3;
ccp_t ccp_obj;
volatile  uint_8 CCP_second_capature_flag = 0;
uint_32 second_capeture =0;
volatile  uint_32 TIMER3_Interrupt_Flag = 0;
volatile uint_8 Total_Period_Milliseconds = 0;
volatile uint_8 timer3_overflow = 0;
uint_8 freq = 0;
void CCP1_DefualtInterruptHundeler(){
Std_ReturnType ret = E_OK;
static uint_8 CCP1_Interrupt_Flag = 0;
CCP1_Interrupt_Flag++;
CCP_second_capature_flag++;
if(CCP1_Interrupt_Flag == 1){
    ret = Timer3_Write_Value(&timer3, 0);
}
else if(CCP1_Interrupt_Flag == 2){
    CCP1_Interrupt_Flag = 0;
    timer3_overflow = 0;
    ret = CCP_Captured_Mode_Read_Value(&second_capeture);
    
}
}
void TIMER3_DefualtInterruptHundeler(){
timer3_overflow++;
}
int main() {
   
Std_ReturnType ret = E_NOT_OK;
ccp_obj.CCP1_Interrupt_Hundeler = CCP1_DefualtInterruptHundeler;
ccp_obj.ccp_module_type = CCP1_Module;
ccp_obj.ccp_mode = CCP_CAPTURE_MODE_SELECTED;
ccp_obj.ccp_mode_variant =  CCP_CAPTURE_MODE_1_RISING_EDGE;
ccp_obj.ccp_pin.port = PORTC_INDEX;
ccp_obj.ccp_ct = CCP1_CCP2_TIMER3;
ccp_obj.ccp_pin.pin = PIN2;
ccp_obj.ccp_pin.direction = Input;


timer3.TMR3_Interrupt_Hundeler = TIMER3_DefualtInterruptHundeler;
timer3.Timer_priority = Interrupt_Periority_LOW;
timer3.timer3_mode = TIMER3_TIMER_MODE;
timer3.timer3_prescaller = TIMER3_PRESCALLER_DIV_BY_1;
timer3.timer3_preload_value = 0;
timer3.timer3_register_wr_mode = TIMER3_RW_REG_16BIT_MODE;
ret = Timer3_Init(&timer3);

ret = CCP_CAPTURE_Init(&ccp_obj);
while(1){
    if(CCP_second_capature_flag == 2){
    Total_Period_Milliseconds = (timer3_overflow * 65536)+ second_capeture;
    freq = (uint_32) (1/ (Total_Period_Milliseconds/ 1000000.0));
    CCP_second_capature_flag = 0;
    }

}
 return (EXIT_SUCCESS);
}
void application_initialize(void){
   Std_ReturnType ret = E_NOT_OK;

}
