
#include <stdio.h>
#include <stdlib.h>

/* Prototype de la fonction rii.c */
/**********************************/
extern void filtre_rii(float b, float a, float in[], int N);

float inbuf[] = 
{
	#include "carre_100b.dat"
};

float outbuf[sizeof(inbuf)]; /* sizeof: Calcule le nombre d'échantillons */
unsigned SAMPLES = sizeof(inbuf); 

void main()
{
	float coeff_x = 0.125; /* coeff de xn */
	float coeff_s = 0.875; /* coeff de sn-1 */
	int i;
	
	filtre_rii(coeff_x, coeff_s, &inbuf[0], SAMPLES);

	exit(0);
}

/************************************************
Filtre recursif d'ordre 1 (sn = b*xn + a*sn-1)
Arguments : rii (b,a,in,N,out)
========	
	a,b : coeffs du filtre
	in : tableau des echantillons
	N : Nbre d'echantillons
	out : tableau des echantillons filtres
************************************************/
void filtre_rii(float b, float a, float in[], int N)
{
	int i;
	float sn_1=0.;

	for (i=0; i<N; i++)
	{
		outbuf[i] = (b*in[i] + a*sn_1)/2;
		sn_1 = b*in[i] + a*sn_1;
	}
		
	for (i=0; i<N; i++)
	{
		outbuf[N-1-i] += (b*in[N-1-i] + a*sn_1)/2;
		sn_1 = b*in[N-1-i] + a*sn_1;
	}
}
