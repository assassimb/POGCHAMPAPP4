/*
*   Voir fichier d'entête pour informations.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QStyleFactory>
#include "MonInterface.h"
#include <iostream>
//#include "CommunicationFPGA.h"
#include <fstream>

using namespace std;

enum Registre { SW = 8, BTN = 9, LD = 10, AN0 = 11, AN1 = 12, AN2 = 13, AN3 = 14 };

MonInterface::MonInterface(const char * theName) : VisiTest(theName)
{
	donnee.typeTest = 1;
	donnee.registreSW = 1;
	donnee.retourSW = 1;

	donnee.registreLD = 1;
	donnee.valeurLD = 1;

	donnee.etatLD = 1;
	donnee.etatSW = 1;

	resetTest();
	resetArchive();
}

void MonInterface::testSuivant()
{

	donnee.typeTest = donnee.typeTest % 3;
	if (donnee.typeTest == 0)
	{
		donnee.typeTest = 3;
	}

	setTest(donnee);


	if (sauvegarde == true)
	{
		setArchive(donnee);
		setArchive(donnee.registreLD, donnee.registreSW);
	}

	cout << hex << donnee.valeurLD << endl;

   if(donnee.etatLD > 0x80)
	{
		donnee.typeTest = 1;

		donnee.registreSW = 1;
		donnee.retourSW = 1;

		donnee.registreLD = 1;
		donnee.valeurLD = 1;

		donnee.etatLD = 1;
		donnee.etatSW = 1;
	}
	else
	{
		donnee.typeTest++;
		
		donnee.registreSW++;
		donnee.retourSW <<= 1;

		donnee.registreLD++;
		donnee.valeurLD <<= 1;

		donnee.etatLD <<= 1;
		donnee.etatSW <<= 1;
	}

   message("bye");
}

bool MonInterface::test()
{
	/*if (donnee.typeTest == 1)
	{
		echo();
	}
	*/
	if (donnee.typeTest == 2)
	{
		return false;
	}

	if (donnee.typeTest == 3)
	{
		return false;
	}
}

/*bool MonInterface::echo()
{
	CommunicationFPGA fpga;
	int val;

	if (!fpga.estOk())
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	if (!fpga.lireRegistre(SW, val))
	{
		cout << fpga.messageErreur() << endl;
		return 1;
	}

	fpga.ecrireRegistre(SW, val);
	donnee.retourSW = val;

	cout << "SW: " << hex << val << endl;

	return 0;
}*/

void MonInterface::arreter()
{
	sauvegarde = false;
}

void MonInterface::demarrer()
{
	sauvegarde = true;
}

void MonInterface::vider()
{
	Archive.vider();
}

void  MonInterface::modeFile()
{
	modedesauvegarde = QUEUE;
}

void  MonInterface::modePile()
{
	modedesauvegarde = PILE;
}

void  MonInterface::premier()
{
	Archive.setindex(0);
	setArchive(*Archive.getactif());
	setArchive(Archive.getindex() + 1, Archive.gettaille());
}

void  MonInterface::dernier()
{
	Archive.setindex(Archive.gettaille() -1);
	setArchive(*Archive.getactif());
	setArchive(Archive.getindex() + 1, Archive.gettaille());
}

void  MonInterface::precedent()
{
	Archive--;
	setArchive(*Archive.getactif());
	setArchive(Archive.getindex() + 1, Archive.gettaille());
}

void  MonInterface::suivant()
{
	Archive++;
	setArchive(*Archive.getactif());
	setArchive(Archive.getindex() + 1, Archive.gettaille());
}

/*void  MonInterface::sauvegarder(char* nomFichier)
{
	ofstream ofs(nomFichier);
	ofs << Archive;
	ofs.close();
	cout << "Archive : ---- " << endl << Archive << endl;
	cout << "Archive[0] : ---- " << endl << Archive[0] << endl;
}*/

void MonInterface::quitter()
{

}
