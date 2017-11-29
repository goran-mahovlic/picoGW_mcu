/*
 / ____)              _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
  (C)2017 Semtech

*/

#include "mbed.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "string.h"
#include "CmdUSB.h"
#include "board.h"

#include "loragw_reg.h"

//CMDMANAGER CmdManager(PA_9, PA_10);
CMDMANAGER CmdManager(PA_2, PA_3);


void Error_Handler(void);

#if DEBUG_MAIN == 1
#define DEBUG_MSG(str)                pc.printf(str)
#define DEBUG_PRINTF(fmt, args...)    pc.printf("%s:%d: "fmt, __FUNCTION__, __LINE__, args)
#define DEBUG_ARRAY(a,b,c)            for(a=0;a!=0;){}
#define CHECK_NULL(a)                 if(a==NULL){return LGW_HAL_ERROR;}
#else
#define DEBUG_MSG(str)
#define DEBUG_PRINTF(fmt, args...)
#define DEBUG_ARRAY(a,b,c)            for(a=0;a!=0;){}
#define CHECK_NULL(a)                 if(a==NULL){return LGW_HAL_ERROR;}
#endif

void Error_Handler(void) {
    DEBUG_MSG("error\n");
}

int main(void) {


	
    uint8_t dataflash;

    /* Check if it is requested to jump to the bootloader (for reflashing...) */
    dataflash = *(uint8_t *)DATA_EEPROM_BASE;
    if (dataflash == GOTO_BOOTLOADER) {
        FLASH_Prog(DATA_EEPROM_BASE, 0);
        ((void (*)(void)) * ((uint32_t*) BOOTLOADER_ADDR))();
    }
/*
			DigitalOut myLED(LED1);

while(1)
		{
		myLED = 1;
		wait(1);
			myLED = 0;
			wait(1);
}
	*/
		
//		pc.baud(115200);
		//pc.printf("Hello\n");

		
    /* Initialize the concentrator */
    lgw_connect();
    CmdManager.Init();
		//DigitalOut myLED(LED1);
		//DigitalOut myLED3(LED3);
    /* Wait for commands coming from host */
    while (1) {
				
			//myLED = 0;
			//myLED3 = 1;
			CmdManager.ReceiveCmd();
        if (CmdManager.DecodeCmd()) {
						//DigitalOut myLED(LED1);
						//myLED = 1;
            CmdManager.TransmitCmd();
					  //pc.printf("1\n");
        }
    }
}
