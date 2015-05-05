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
void afficher_message(const char* message)
{
	std::cout << "***\t\tIFT-2008\t\t***\n"
		<< "*\n"
		<< "* Voici un example pour l'utilisation de la classe CompteurTemporel.\n"
		<< "*\n"
		<< "* " << message << "\n"
		<< "*\n"
		<< "***\n\n";
};

/**
* \brief Affiche la durée formatée
*
* \param[in] p_duree La valeur à afficher
*
**/
void afficher_duree(double duree)
{
	std::cout << "Temps d'execution de la recherche:\n"
		<< "(s)   : " << std::fixed << duree << "\n"
		<< "(ms)  : " << std::fixed << duree * 1e+3 << "\n"
		<< "(mcs) : " << std::fixed << duree * 1e+6 << "\n"
		<< "(ns)  : " << std::fixed << duree * 1e+9 << "\n"
		<< "(ps)  : " << std::fixed << duree * 1e+12 << "\n\n";
};

int main(int argc, char** argv)
{
	// Création d'un objet de type compteur (non actif)
	ulaval::CompteurTemporel<double> compteur(false);


	// Définition de la valeur minimale du nombre aléatoire.
	const unsigned long long RANGE_MIN = 1;

	// Définition de la valeur maximale du nombre aléatoire.
	const unsigned long long RANGE_MAX = static_cast<unsigned long long>(1e+6L);

	// Définition du nombre d'itération.
	const unsigned long long NOMBRE_ELEMENTS = static_cast<unsigned long long>(1e+6L);



	// Déclaration du générateur de nombre pseudo-aléatoire.
	std::random_device rd;

	// Définition du moteur de nombre aléatoire. 
	std::default_random_engine re(rd());

	// Définition du type de distribution de
	// nombres aléatoire entre [RANGE_MIN, RANGE_MAX]
	std::uniform_int_distribution<int> rand(RANGE_MIN, RANGE_MAX);



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
	const size_t NOMBRE_ITERATION_MAX = 50;

	// Définition d'une variable pour le nombre d'iteration.
	size_t iter = 0;

	// Déclaration d'une variable pour maintenir une valeur entiere aleatoire.
	int valeur;

	// Définition d'une variable de condition pour la recherche.
	bool continuerRecherche = true;

	// Suppression des valeurs anterieures.
	vecteur.clear();
	vecteur.resize(NOMBRE_ELEMENTS);

	// Ajout d'entiers dans le vecteur.
	for (auto it = vecteur.begin(); it < vecteur.end(); ++it)
		*it = rand(re);

	// Remise a zero du compteur.
	compteur.reinitialiser(true);

	// Debut de la boucle.
	while (continuerRecherche && iter < NOMBRE_ITERATION_MAX)
	{
		// Affectation arbitraire d'une valeur entiere.
		valeur = rand(re);

		// Définition de l'indice (position de l'iterateur) une fois la valeur trouvee.
		auto index = std::find(vecteur.begin(), vecteur.end(), valeur);

		// Affichage de l'indice (si non-nul)
		if (index != vecteur.end())
		{
			// Affichage de la valeur trouvee.
			std::cout
				<< "La valeur recherchee ("
				<< valeur
				<< ") se trouve a l'indice ("
				<< index - vecteur.begin()
				<< ")\n\n";

			// Arret de la recherche.
			continuerRecherche = false;
		}

		// Incrementation du nombre d'itération.
		++iter;
	}

	// Capture de la durée.
	duree = compteur.duree() * 1e-3;

	// Affichage du temps d'éxécution de la recherche.
	afficher_duree(duree);

	return 0;
}