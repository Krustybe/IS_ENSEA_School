/////////////////////////////////////////////////////////////
// Filename : sc_inv.cpp
// Author   : Lounis KESSAL
// Company  : ENSEA
// Comment  : Generer les stimulis ==> modeliser cyclope
/////////////////////////////////////////////////////////////
#include "grad.h"

//*****************************************
// get_pixel : sortir les pixels de l'inv
//*****************************************
void inv::inv_trait()
{
    int pix_tmp = 0;
	
	if (reset.read() == 0)
	{	
		pix_tmp = 0; 
	}
	else if(blank.read() == 1)
	{
		int currentPixel= pixel_in.read();
		int var = fifo.front();
		int temp1, temp2, temp3;

		fifo.pop();
		temp1 = abs(var - fifo.front() + previousPixel - currentPixel);
		temp2 = abs(var + fifo.front() - previousPixel - currentPixel);
		temp3 = (3/4)* (temp1 + temp2);
		

		pixel_out.write( std::max( std::max(temp1,temp2), temp3));
		fifo.push(previousPixel);
		previousPixel = currentPixel;
	}
}

void inv::synchro_out()
{
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}
