#include <systemc.h>
#include "gdr.h"
#include "sc_image.h"
#include "gh2D.h"

#define T_ns 100 // 100 ns 
char winimage[200];
/////////////////////////////////////
// Ne pas modifier
   char FichierIn[100], FichierOut[100];
// Jusqu'ici (ne pas modifier)
/////////////////////////////////////
void affiche_image(char *nomIMAGE, int x=0, int y=0);
// Programme principal
int i=0;
int NbrePixelParLigne;

int sc_main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Arguments incorrects \n"); 
		printf("Usage : %s image_in  image_out\n", argv[0]); 
		return 1;
	}
	// Exporter nom du fichier image
	strcpy(FichierIn, argv[1]); 
	strcpy(FichierOut, argv[2]);

	// Si argument => Creer un objet image GDR
	ENTETE_GDR EnteteImageIn(argv[1]);
	unsigned NbrePixel=EnteteImageIn.NbPixel();
	NbrePixelParLigne=EnteteImageIn.NbColonne();


	sc_signal <bool> pckout; // Clock Pixel
	sc_signal <bool> reset;
	sc_signal <sc_uint<8> > pixel_in, pixel_out;
	sc_signal <bool> sh, sv, blank;
	
	
	// Utiles pour la sauvegarde de l'image
	sc_signal <bool> bk_out, hpix_out;

	// Modelisation CYCLOPE
	image image1("image");
	image1.reset(reset);
	image1.bk_out(bk_out); // valider la sauvegarde de l'image
	image1.hpix_out(hpix_out); // valider la sauvegarde de l'image

	// Signaux utiles
	image1.sh(sh);
	image1.sv(sv);
	image1.blank(blank);
	image1.pckout(pckout);
	image1.pixel_in(pixel_in);  	
	image1.pixel_out(pixel_out);  	
	// END Modele cyclope

	// Exemple de traitement
	inv inv1("inv");
	inv1.reset(reset);
	inv1.blank(blank);
	inv1.clk(pckout);
	inv1.pixel_in(pixel_in);
	inv1.pixel_out(pixel_out);
	inv1.hpix_out(hpix_out);
	inv1.bk_out(bk_out);

	//<Begin TRACE>
	sc_trace_file *tf = sc_create_vcd_trace_file("image");
	sc_trace(tf, pckout, "HPIXEL");
	sc_trace(tf, reset, "RESET");
	sc_trace(tf, sh, "SH");
	sc_trace(tf, sv, "SV");
	sc_trace(tf, blank, "BLANK");
	sc_trace(tf, pixel_in, "PIXEL_IN");
	sc_trace(tf, pixel_out,"PIXEL_OUT");
	//<End TRACE>

	reset = 0; 
	sc_start(10, SC_NS);
	
	reset = 1;
	sc_start(); // Lancement de la simulation

	sc_close_vcd_trace_file(tf);

	affiche_image (argv[1], 200, 0);// Afficher l'image d'entree
	affiche_image (argv[2], 500, 0);// Afficher l'image resultat

	// Afficher les chrons sous Visual C++
	//WinExec("gtkwave image.vcd", 1);	
	
	// Afficher les chrons sous UNIX
	int STATUS = system("gtkwave image.vcd &");	// Afficher les chrons

	exit(0);
}
///////////////////////////////////////////////
// Affichage d'une image 
void affiche_image(char *nomIMAGE, int x, int y)
{
	char str[20];
	strcpy(winimage, "xv ");
	strcat(winimage, nomIMAGE); 
	
	sprintf(str, " %d ", x);
	strcat(winimage, str);
	sprintf(str, "%d &", y);
	strcat(winimage, str);

	// Afficher les images sous Visual C++
	//WinExec(winimage, 1);

	// Afficher les images sous UNIX
	int STATUS = system(winimage);
}
///////////////////////////////////////////////

