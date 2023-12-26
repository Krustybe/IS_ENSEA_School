/////////////////////////////////////////////////////////////
// Filename : sc_inv.cpp
// Author   : Lounis KESSAL
// Company  : ENSEA
// Comment  : Generer les stimulis ==> modeliser cyclope
/////////////////////////////////////////////////////////////
#include "gv2D.h"

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

		fifo.pop();
		pixel_out.write(abs(var + fifo.front() - previousPixel - currentPixel));
		fifo.push(previousPixel);
		previousPixel = currentPixel;
	}
}

void inv::synchro_out()
{
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}
