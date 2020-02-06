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
#include <fstream>

using namespace std;

MonInterface::MonInterface(const char *theName) : VisiTest(theName)
{
	donnee.typeTest = 1;
	donnee.registreSW = SW;
	donnee.retourSW = 1;

	donnee.registreLD = LD;
	donnee.valeurLD = 1;

	donnee.etatLD = 1;
	donnee.etatSW = 1;

	resetTest();
	resetArchive();
	setArchive(Archive.getindex(), Archive.gettaille());
}

void MonInterface::testSuivant()
{

	donnee.typeTest = donnee.typeTest % 3;
	if (donnee.typeTest == 0)
	{
		donnee.typeTest = 3;
	}

	setArchive(donnee);
	setArchive(donnee.registreLD, donnee.registreSW);

	cout << hex << donnee.valeurLD << endl;

	test();

	setTest(donnee);

	if (sauvegarde == true)
	{
		DonneesTest *temp = new DonneesTest;

		cout << "fonction de sauvegarde" << endl;

		temp->typeTest = donnee.typeTest;

		temp->registreSW = SW;
		temp->registreLD = LD;

		temp->retourSW = cfpga.LireSwitch();
		temp->valeurLD = cfpga.LireSwitch();
		temp->etatLD = cfpga.LireSwitch();
		temp->etatSW = cfpga.LireSwitch();

		Archive += temp;
		setArchive(Archive.getindex() + 1, Archive.gettaille());
	}

	if (donnee.etatLD > 0x80)
	{
		donnee.typeTest = 1;
		donnee.retourSW = 1;

		donnee.valeurLD = 1;

		donnee.etatLD = 1;
		donnee.etatSW = 1;
	}
	else
	{
		donnee.typeTest++;
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
		parite();
	}

	else
	{
		return false;
	}
}

bool MonInterface::echo()
{

	donnee.retourSW = cfpga.LireSwitch();
	donnee.valeurLD = cfpga.LireSwitch();
	donnee.etatSW = cfpga.LireSwitch();
	donnee.etatLD = cfpga.LireSwitch();

	return true;
}

bool MonInterface::parite()
{
	int valeurSW = cfpga.LireSwitch();
	donnee.retourSW = cfpga.LireSwitch();
	donnee.etatSW = cfpga.LireSwitch();
	int switchActive = 0;

	if ((valeurSW & 128) == 128)
		switchActive++;
	if ((valeurSW & 64) == 64)
		switchActive++;
	if ((valeurSW & 32) == 32)
		switchActive++;
	if ((valeurSW & 16) == 16)
		switchActive++;
	if ((valeurSW & 8) == 8)
		switchActive++;
	if ((valeurSW & 4) == 4)
		switchActive++;
	if ((valeurSW & 2) == 2)
		switchActive++;
	if ((valeurSW & 1) == 1)
		switchActive++;

	if (switchActive == 0 || switchActive % 2 == 0)
		donnee.etatLD = 0xff;
	if ((switchActive % 2) == 1)
		donnee.etatLD = 0;

	donnee.valeurLD = donnee.etatLD;

	return true;
}

void MonInterface::arreter()
{
	sauvegarde = false;
	cout << "arreter" << endl;
}

void MonInterface::demarrer()
{
	sauvegarde = true;
	cout << "demarrage" << endl;
}

void MonInterface::vider()
{
	Archive.vider();
	cout << "vider" << endl;
}

void MonInterface::modeFile()
{
	modedesauvegarde = QUEUE;
}

void MonInterface::modePile()
{
	modedesauvegarde = PILE;
}

void MonInterface::premier()
{
	Archive.setindex(0);
	archivecourante();
}

void MonInterface::dernier()
{
	Archive.setindex(Archive.gettaille() - 1);
	archivecourante();
}

void MonInterface::precedent()
{
	Archive--;
	archivecourante();
}

void MonInterface::suivant()
{
	Archive++;
	archivecourante();
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

void MonInterface::archivecourante()
{
	if (Archive.getactif() != NULL)
	{
		setArchive(*Archive.getactif());
	}
	setArchive(Archive.getindex() + 1, Archive.gettaille());
}