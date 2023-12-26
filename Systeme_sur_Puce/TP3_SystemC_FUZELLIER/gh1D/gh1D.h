#include <systemc.h>
#include "gdr.h"

#ifndef inv_H
#define inv_H

/////////////////////
SC_MODULE (inv)
{
	sc_in <bool> clk;
	sc_in <bool> reset;
	sc_in <bool> blank;
	sc_in <sc_uint<8> > pixel_in;
	sc_out <sc_uint<8> > pixel_out;

	sc_out <bool> bk_out;
	sc_out <bool> hpix_out;

	void inv_trait(void);
	void synchro_out(void);
	SC_CTOR(inv)
	{
		SC_METHOD(inv_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie

	}
};

#endif
