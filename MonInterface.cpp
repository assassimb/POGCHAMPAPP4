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

using namespace std;

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

	test();

	if (archiveActivee == true)
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
	if (donnee.typeTest == 1)
	{
		echo();
	}

	if (donnee.typeTest == 2)
	{
		return false;
	}

	if (donnee.typeTest == 3)
	{
		return false;
	}
}

bool MonInterface::echo()
{
	donnee.registreSW = 8;

	donnee.retourSW = cfpga.LireSwitch();
	donnee.registreLD = 10;

	donnee.valeurLD = cfpga.LireSwitch();
	donnee.etatSW = cfpga.LireSwitch();
	donnee.etatLD = cfpga.LireSwitch();

	return 0;
}

void MonInterface::arreter()
{
	archiveActivee = false;
}

void MonInterface::demarrer()
{
	archiveActivee = true;
}

