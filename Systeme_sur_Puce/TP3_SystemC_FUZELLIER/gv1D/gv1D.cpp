/////////////////////////////////////////////////////////////
// Filename : sc_inv.cpp
// Author   : Lounis KESSAL
// Company  : ENSEA
// Comment  : Generer les stimulis ==> modeliser cyclope
/////////////////////////////////////////////////////////////
#include "gv1D.h"

//*****************************************
// get_pixel : sortir les pixels de l'inv
//*****************************************

extern int NbrePixelParLigne;
void inv::inv_trait()
{
    int pix_tmp = 0;

	static int pix_tmp_listeV[1000];
	static int i = 0;
	static int compteurColone = 0;
	static int testblank = 0;
	static int nouvelleLigne = 1;
	int pix_sortie = 0;
	if (reset.read() == 0) // reset
	{
		pix_tmp = 0; 
	}else if (blank.read() == 0)
	{
		nouvelleLigne=1;
	}else if(blank.read() == 1)
	{
		if (nouvelleLigne == 1)
		{
			nouvelleLigne = 0;
			compteurColone = 0;
		}

	pix_tmp = (int)pixel_in.read();
	pix_sortie = fabs(pix_tmp_listeV[compteurColone]-(int) pix_tmp);

	pix_tmp_listeV[compteurColone]=pix_tmp;
		
	compteurColone++;		
	}

    	pixel_out.write(pix_sortie/2);
}

void inv::synchro_out() // pour generer les synchro en sortie
{
	// laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}
