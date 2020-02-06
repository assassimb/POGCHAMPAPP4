#ifndef VECTEUR_H
#define VECTEUR_H

#include <iostream>
using namespace std;

template <class T>
class vecteur
{
public:
	vecteur();
	~vecteur();
	int getcapacite();
	int gettaille();
	int estvide();
	bool ajouter(T);
	T* retirer(int);
	T* get(int);
	void vider();
	int doublecapacite();
	void afficher(ostream& s);

private:
	T* resultat;
	int capacite;
	int taille;
	int index;
};

template <class T>
vecteur<T>::vecteur()
{
	resultat = new T[1];
	taille = 0;
	capacite = 1;
}

template <class T>
vecteur<T>::~vecteur()
{
	delete resultat;
}
template <class T>
int vecteur<T>::getcapacite()
{
	return capacite;
}

template <class T>
int vecteur<T>::gettaille()
{
	return taille;
}

template <class T>
int vecteur<T>::doublecapacite()
{

	capacite = capacite * 2;
	T* temp;
	temp = new T[capacite];

	for (int i = 0; i < capacite; i++)
	{
		temp[i] = NULL;
	}

	for (int i = 0; i < taille; i++)
	{
		temp[i] = resultat[i];
	}
	delete resultat;
	resultat = temp;
	return capacite;
}

template <class T>
void vecteur<T>::vider()
{
	for (int i = 0; i < taille; i++)
	{
		delete resultat[i];
		resultat[i] = NULL;
	}
	taille = 0;
	delete[] resultat;
}

template <class T>
int vecteur<T>::estvide()
{
	if (taille == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

template <class T>
bool vecteur<T>::ajouter(T in)
{
	if (taille == capacite)
	{
		capacite = doublecapacite();
	}

	resultat[taille] = in;
	taille++;

	return true;
}

template <class T>
T* vecteur<T>::retirer(int index)
{
	taille = gettaille();
	T* retirer = resultat[index];

	for (int i = index; i < (taille - 1); i++)
	{
		resultat[i] = resultat[i + 1];
	}
	resultat[taille - 1] = NULL;
	taille = taille - 1;
	return retirer;
}

template <class T>
T* vecteur<T>::get(int index)
{
	T* specifier;

	specifier = resultat[index];

	return specifier;
}

template <class T>
void vecteur<T>::afficher(ostream& s)
{
	for (int i = 0; i < taille; i++)
	{
		resultat[i]->afficher(cout);
	}
}

#endif