/////////////////////////////////////////////////////////////
// Filename : sc_inv.cpp
// Author   : Lounis KESSAL
// Company  : ENSEA
// Comment  : Generer les stimulis ==> modeliser cyclope
/////////////////////////////////////////////////////////////
#include "seuil.h"

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

		int grad = std::max( std::max(temp1,temp2), temp3);

		if (grad<seuil)
		{
			grad=0;
		}

		pixel_out.write(grad);
		fifo.push(previousPixel);
		previousPixel = currentPixel;
	}
}

void inv::synchro_out()
{
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}
