
#include "sleep.h"

#include <string.h>
#include "xparameters.h"
#include "xil_printf.h"

#include "xdevcfg.h"



#define DDR_BASEADDR        0x00000000
#define VDMA_BASEADDR_R      XPAR_AXI_VDMA_0_BASEADDR
#define VDMA_BASEADDR_W      XPAR_AXI_VDMA_1_BASEADDR
#define GPIO_BASEADDR        XPAR_AXI_GPIO_0_BASEADDR
#define TPG_BASEADDR  		XPAR_V_TPG_0_S_AXI_CTRL_BASEADDR
#define H_STRIDE            640
#define H_ACTIVE            640
#define V_ACTIVE            480

#define VIDEO_BASEADDR0 DDR_BASEADDR + 0x1000000


int main(void)
{


	   // Один раз посылаем настройки по I2C

		Xil_Out32((GPIO_BASEADDR + 0x004), 0x0);
		Xil_Out32((GPIO_BASEADDR + 0x000), 0x1);
		sleep(1);
		Xil_Out32((GPIO_BASEADDR + 0x000), 0x0);






        // Настраиваем VDMA0 который выводит на VGA

		//MM2S(выход) VDMA Control Register
	    Xil_Out32((VDMA_BASEADDR_R + 0x000), 0x3);        // enable circular mode



	    //MM2S Start Address (1 to 16)
	    Xil_Out32((VDMA_BASEADDR_R + 0x05c), VIDEO_BASEADDR0);    // start address



	    //MM2S Frame Delay and Stride Register
	    Xil_Out32((VDMA_BASEADDR_R + 0x058), (H_STRIDE*3));       // h offset (800 * 4) bytes
	    //MM2S Horizontal Size Register
		Xil_Out32((VDMA_BASEADDR_R + 0x054), (H_ACTIVE*3));       // h size (800 * 4) bytes
		//MM2S Vertical Size Register
		Xil_Out32((VDMA_BASEADDR_R + 0x050), V_ACTIVE);           // v size (600)


 // Настраиваем VDMA1 который вводит


		Xil_Out32((VDMA_BASEADDR_W + 0x030), 0x8B);        // enable circular mode


		//S2MM Start Address (1 to 16)
		Xil_Out32((VDMA_BASEADDR_W + 0x0AC), VIDEO_BASEADDR0);    // start address




		//S2MM Frame Delay and Stride Register
		Xil_Out32((VDMA_BASEADDR_W + 0x0A8), (H_STRIDE*3));       // h offset (800 * 4) bytes
		//S2MM Horizontal Size Register
		Xil_Out32((VDMA_BASEADDR_W + 0x0A4), (H_ACTIVE*3));       // h size (800 * 4) bytes
		//S2MM Frame Delay and Stride Register
		Xil_Out32((VDMA_BASEADDR_W + 0x0A0), V_ACTIVE);           // v size (600)





    while(1)
    {
        sleep(5);
        xil_printf("EBAZ4205_OV7670 \n\r");
    }
    return 0;
}

