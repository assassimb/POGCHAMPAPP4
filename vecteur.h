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
	int getindex();
	void setindex(int);
	T getactif();
	int estvide();
	bool ajouter(T);
	T retirer(int);
	T get(int);
	void vider();
	int doublecapacite();
	friend ostream& operator << <> (ostream& os, vecteur<T>& dt);
	void operator += (T);
	void operator ++ (int);
	void operator -- (int);
	void operator ++();
	void operator --();
	T operator [] (int);

private:
	T* resultat;
	int capacite;
	int taille;
	int index;
};

template <class T>
ostream& operator << <> (ostream& os, vecteur<T>& dt)
{
	taille = index.gettaille();
	for (int i = 0; i < taille; i++)
	{
		os << resultat[i] << endl;
	}
	return os;
}

template <class T>
void vecteur<T>::operator += (T donnee)
{
	if (taille == capacite)
	{
		capacite = doublecapacite();
	}
	resultat[taille] = donnee;
	taille++;
}

template <class T>
void vecteur<T>::operator ++ (int dt)
{
	if (index < taille - 1)
	{
		index++;
	}
}

template <class T>
void vecteur<T>::operator -- (int dt)
{
	if (index > 0)
	{
		index--;
	}
}

template<class T>
void vecteur<T>::operator ++()
{
	if (index < taille - 1)
	{
		index++;
	}
}

template<class T>
void vecteur<T>::operator --()
{
	if (index > 0)
	{
		index--;
	}
}

template <class T>
T vecteur<T>::operator [] (int index)
{
	if (index >= taille || index < 0)
	{
		return NULL;
	}
	return resultat[index];
}



template <class T>
vecteur<T>::vecteur()
{
	resultat = new T[1];
	taille = 0;
	capacite = 1;
	index = 0;
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
bool vecteur<T>::ajouter(T donnee)
{
	if (taille == capacite)
	{
		capacite = doublecapacite();
	}

	resultat[taille] = donnee;
	taille++;

	return true;
}

template <class T>
T vecteur<T>::retirer(int index)
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
T vecteur<T>::get(int index)
{
	T* specifier;

	if (index >= size || index < 0)
	{
		return nullptr;
	}

	specifier = resultat[index];

	return specifier;
}

template <class T>
int vecteur<T>::getindex()
{
	return index;
}

template <class T>
void vecteur<T>::setindex(int i)
{
	index = i;
}

template<class T>
T vecteur<T>::getactif()
{
	return resultat[index];
}

#endif