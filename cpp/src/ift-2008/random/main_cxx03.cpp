/**
* \file main_cxx03.cpp
* \brief Fichier du point d'entrée principal
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/5/2015
*/

#include <iostream>
#include <string.h>
#include <istream>
#include <vector>
#include <algorithm>

#include "ulaval/time_measure_cxx03.h"

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

/**
* \brief Retourne un nombre pseudo aleatoire dans un interval
*
* \param[in] p_min La valeur minimale du nombre pseudo-aléatoire
* \param[in] p_max La valeur maximale du nombre pseudo-aléatoire
*
* \return Le prochain nombre aléatoire compris entre p_min et p_max
*
**/
int next_random(int p_min, int p_max)
{
	return (rand() % p_max) + p_min;
}

int main(int argc, char** argv)
{
	// Création d'un objet de type compteur (non actif)
	ulaval::CompteurTemporel<double, ulaval::ratio_ms> compteur(false);

	// Définition de la valeur minimale du nombre aléatoire.
	const unsigned long long RANGE_MIN = 1;

	// Définition de la valeur maximale du nombre aléatoire.
	const unsigned long long RANGE_MAX = static_cast<unsigned long long>(1e+6L);

	// Définition du nombre d'itération.
	const unsigned long long NOMBRE_ELEMENTS = static_cast<unsigned long long>(1e+6L);


	// Initialisation du generateur de nombres aléatoires.
	srand(static_cast<unsigned int>(time(0)));


	// Déclaration d'une variable pour la duree.
	double duree;



	// Définition d'un vecteur ayant une capcité de $NOMBRE_ELEMENTS
	std::vector<int> vecteur(NOMBRE_ELEMENTS);


	/**
	* Exemple: Recherche d'une valeur arbitraire dans un vecteur
	*
	*/

	// Affichage des informations du programmes.
	afficher_message("Recherche d'une valeur arbitraire dans un vecteur");


	// Définition d'une constante pour le nombre maximal d'iteration.
	const size_t NOMBRE_ITERATION_MAX = 1000;

	// Définition d'une variable pour le nombre d'iteration.
	size_t iter = 0;

	// Déclaration d'une variable pour maintenir une valeur entiere aleatoire.
	int valeur;

	// Définition d'une variable de condition pour la recherche.
	bool continuerRecherche = true;

	// Définition d'une variable de condition pour la localisation de
	// l'indice.
	bool valeurTrouvee = false;

	// Suppression des valeurs anterieures.
	vecteur.clear();
	vecteur.resize(NOMBRE_ELEMENTS);
	// Ajout d'entiers dans le vecteur.
	for (std::vector<int>::iterator it = vecteur.begin(); it < vecteur.end(); ++it)
		(*it) = next_random(RANGE_MIN, RANGE_MAX);

	// Remise a zéro du compteur.
	compteur.reinitialiser(true);


	// Début de la boucle.
	while (continuerRecherche && iter < NOMBRE_ITERATION_MAX)
	{
		// Affectation arbitraire d'une valeur entière.
		valeur = next_random(RANGE_MIN, RANGE_MAX);

		// Affichage de l'indice (si non-nul)
		for (size_t i = 0; i < vecteur.size() && !valeurTrouvee; ++i)
		{
			// Affichage de l'indice (si non-nul)
			if (vecteur.at(i) == valeur)
			{
				// Affichage de l'iteration:
				std::cout
					<< "iteration: "
					<< iter
					<< "\n\n";

				// Affichage de la valeur trouvee.
				std::cout
					<< "La valeur recherchee ("
					<< valeur
					<< ") se trouve a l'indice ("
					<< i
					//<< index - vecteur.begin()
					<< ")\n\n";

				// Arret de la recherche.
				continuerRecherche = false;
				valeurTrouvee = true;
			}
		}

		// Incrementation du nombre d'itération.
		++iter;
	}

	// Capture de la durée.
	duree = compteur.duree() * 1e-3;

	// Si la valeur recherchée est localisée, affichage de l'interval
	// de temps.
	if (valeurTrouvee)
	{
		// Affichage du temps d'éxécution de la recherche.
		afficher_duree(duree);
	}
	else
	{
		// Aucune valeur trouvée.
		std::cout
			<< "Aucune valeur trouvée."
			<< "\n"
			<< "Veuillez relancer l'application."
			<< "\n\n";
	}

	return 0;
}