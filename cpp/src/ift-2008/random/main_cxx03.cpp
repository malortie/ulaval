/**
* \file main_cxx03.cpp
* \brief Fichier du point d'entr�e principal
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
* \brief fonction de comparaison pour le trie (pr�dicat)
*
* \param[in] i Premi�re valeur � �tre compar�e
* \param[in] j Seconde valeur � �tre compar�e
*
* \return vrai si i < j, sinon retourne faux
*
**/
bool predicat(int i, int j)
{
	return (i < j);
};

/**
* \brief Affiche un en-t�te � titre d'exemple et d'utilisation
*
* \param[in] p_message Le message � affcher
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
* \brief Affiche la dur�e format�e
*
* \param[in] p_duree La valeur � afficher
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
* \param[in] p_min La valeur minimale du nombre pseudo-al�atoire
* \param[in] p_max La valeur maximale du nombre pseudo-al�atoire
*
* \return Le prochain nombre al�atoire compris entre p_min et p_max
*
**/
int next_random(int p_min, int p_max)
{
	return (rand() % p_max) + p_min;
}

int main(int argc, char** argv)
{
	// Cr�ation d'un objet de type compteur (non actif)
	ulaval::CompteurTemporel<double, ulaval::ratio_ms> compteur(false);

	// D�finition de la valeur minimale du nombre al�atoire.
	const unsigned long long RANGE_MIN = 1;

	// D�finition de la valeur maximale du nombre al�atoire.
	const unsigned long long RANGE_MAX = static_cast<unsigned long long>(1e+6L);

	// D�finition du nombre d'it�ration.
	const unsigned long long NOMBRE_ELEMENTS = static_cast<unsigned long long>(1e+6L);


	// Initialisation du generateur de nombres al�atoires.
	srand(static_cast<unsigned int>(time(0)));


	// D�claration d'une variable pour la duree.
	double duree;



	// D�finition d'un vecteur ayant une capcit� de $NOMBRE_ELEMENTS
	std::vector<int> vecteur(NOMBRE_ELEMENTS);


	/**
	* Exemple: Recherche d'une valeur arbitraire dans un vecteur
	*
	*/

	// Affichage des informations du programmes.
	afficher_message("Recherche d'une valeur arbitraire dans un vecteur");


	// D�finition d'une constante pour le nombre maximal d'iteration.
	const size_t NOMBRE_ITERATION_MAX = 1000;

	// D�finition d'une variable pour le nombre d'iteration.
	size_t iter = 0;

	// D�claration d'une variable pour maintenir une valeur entiere aleatoire.
	int valeur;

	// D�finition d'une variable de condition pour la recherche.
	bool continuerRecherche = true;

	// D�finition d'une variable de condition pour la localisation de
	// l'indice.
	bool valeurTrouvee = false;

	// Suppression des valeurs anterieures.
	vecteur.clear();
	vecteur.resize(NOMBRE_ELEMENTS);
	// Ajout d'entiers dans le vecteur.
	for (std::vector<int>::iterator it = vecteur.begin(); it < vecteur.end(); ++it)
		(*it) = next_random(RANGE_MIN, RANGE_MAX);

	// Remise a z�ro du compteur.
	compteur.reinitialiser(true);


	// D�but de la boucle.
	while (continuerRecherche && iter < NOMBRE_ITERATION_MAX)
	{
		// Affectation arbitraire d'une valeur enti�re.
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

		// Incrementation du nombre d'it�ration.
		++iter;
	}

	// Capture de la dur�e.
	duree = compteur.duree() * 1e-3;

	// Si la valeur recherch�e est localis�e, affichage de l'interval
	// de temps.
	if (valeurTrouvee)
	{
		// Affichage du temps d'�x�cution de la recherche.
		afficher_duree(duree);
	}
	else
	{
		// Aucune valeur trouv�e.
		std::cout
			<< "Aucune valeur trouv�e."
			<< "\n"
			<< "Veuillez relancer l'application."
			<< "\n\n";
	}

	return 0;
}