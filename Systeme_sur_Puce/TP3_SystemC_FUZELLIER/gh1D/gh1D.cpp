/////////////////////////////////////////////////////////////
// Filename : sc_inv.cpp
// Author   : Lounis KESSAL
// Company  : ENSEA
// Comment  : Generer les stimulis ==> modeliser cyclope
/////////////////////////////////////////////////////////////
#include "gh1D.h"
#include <cmath>
//*****************************************
// get_pixel : sortir les pixels de l'inv
//*****************************************
void inv::inv_trait()
{
    int pix_tmp = 0;
	static int pix_tmp_liste[2]={0,0};
	static int i = 0;
	static int j = 1;
	if (reset.read() == 0)
	{
		pix_tmp = 0; 
	}else if(blank.read() == 1)
	{	
		
       	pix_tmp_liste[i] = pixel_in.read();
		pix_tmp=(pix_tmp_liste[i]-pix_tmp_liste[j])/2;
		i++;
		j++;

		if (i >= 2)
		{
			i = 0;
		}
		if (j >= 2)
		{
			j = 0;
		}

	}
    	pixel_out.write(pix_tmp);
}

void inv::synchro_out() // pour generer les synchro en sortie
{
	// laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}
