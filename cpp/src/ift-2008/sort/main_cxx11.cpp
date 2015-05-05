/**
* \file main_cxx11.cpp
* \brief Fichier du point d'entrée principal
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/5/2015
*/

#include <iostream>
#include <string.h>
#include <istream>
#include <vector>
#include <random>
#include <algorithm>

#include "ulaval/time_measure_cxx11.h"

using namespace std;

using namespace ulaval;

/**
* \brief fonction de comparaison pour le trie (prédicat)
*
* \param[in] i Première valeur à être comparée
* \param[in] j Seconde valeur à être comparée
*
* \return vrai si i < j, sinon retourne faux
*
**/
bool predicat(int i, int j)
{
	return (i < j);
};

/**
* \brief Affiche un en-tête à titre d'exemple et d'utilisation
*
* \param[in] p_message Le message à affcher
*
**/
void afficher_message(const char* p_message)
{
	std::cout << "***\t\tIFT-2008\t\t***\n"
		<< "*\n"
		<< "* Voici un example pour l'utilisation de la classe CompteurTemporel.\n"
		<< "*\n"
		<< "* " << p_message << "\n"
		<< "*\n"
		<< "***\n\n";
};

/**
* \brief Affiche la durée formatée
*
* \param[in] p_duree La valeur à afficher
*
**/
void afficher_duree(double p_duree)
{
	std::cout << "Temps d'execution de la recherche:\n"
		<< "(s)   : " << std::fixed << p_duree << "\n"
		<< "(ms)  : " << std::fixed << p_duree * 1e+3 << "\n"
		<< "(mcs) : " << std::fixed << p_duree * 1e+6 << "\n"
		<< "(ns)  : " << std::fixed << p_duree * 1e+9 << "\n"
		<< "(ps)  : " << std::fixed << p_duree * 1e+12 << "\n\n";
};

int main(int argc, char** argv)
{
	// Création d'un objet de type compteur (non actif)
	CompteurTemporel<double> compteur(false);

	// Définition de la valeur minimale du nombre aléatoire.
	const unsigned long long RANGE_MIN = 1;

	// Définition de la valeur maximale du nombre aléatoire.
	const unsigned long long RANGE_MAX = static_cast<unsigned long long>(1e+6L);

	// Définition du nombre d'iteration.
	const unsigned long long NOMBRE_ELEMENTS = static_cast<unsigned long long>(1e+6L);



	// Déclaration du générateur de nombre pseudo-aléatoire.
	std::random_device rd;

	// Définition du moteur de nombre aleatoire. 
	std::default_random_engine re(rd());

	// Définition du type de distribution de
	// nombres aléatoire entre [RANGE_MIN, RANGE_MAX]
	std::uniform_int_distribution<int> rand(RANGE_MIN, RANGE_MAX);



	// Déclaration d'une variable pour la durée.
	double duree;



	// Définition d'un vecteur ayant une capcité de $NOMBRE_ELEMENTS
	std::vector<int> vecteur(NOMBRE_ELEMENTS);




	/**
	* Exemple: Effectuer le trie d'une liste d'éléments contenu dans
	*			 un vecteur.
	*/

	// Affichage des informations du programmes.
	afficher_message("Trier une liste en utilisant std::sort()");

	// Ajout d'entiers dans le vecteur.
	for (auto it = vecteur.begin(); it < vecteur.end(); ++it)
		*it = rand(re);

	// Remise a zéro du compteur.
	compteur.reinitialiser(true);

	// Application de la fonction de trie sur le vecteur.
	std::sort(vecteur.begin(), vecteur.end(), predicat);

	// Capture de la durée d'éxécution.
	duree = compteur.duree() * 1e-3;

	// Affichage du temps d'éxécution de la recherche.
	afficher_duree(duree);


	return 0;
}