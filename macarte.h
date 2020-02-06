#ifndef MACARTE_H
#define MACARTE_H

#include "CommunicationFPGA.h"
#include <iostream>

using namespace std;

enum Registre { SW = 8, BTN = 9, LD = 10, AN0 = 11, AN1 = 12, AN2 = 13, AN3 = 14 };

class Macarte : public CommunicationFPGA
{
private:

public:
	Macarte(){}
	~Macarte(){}
	
	int LireSwitch()
	{
		int valeur;
		lireRegistre(SW, valeur);
		cout << "valSW: " << dec << valeur << " hexvalSW: "<< hex << valeur << endl;
		ecrireRegistre(LD, valeur);
		return valeur;
	}

	int LireBoutons() 
	{
		int valeur;
		lireRegistre(BTN, valeur);
		cout << "valBTN: " << dec << valeur << " hexvalBTN: " << hex << valeur << endl;
		return valeur;
	}
};
#endif 
