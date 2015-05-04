#include <iostream>
#include <string.h>
#include <istream>
#include <vector>
#include <random>
#include <algorithm>

#include "ulaval/time_measure.h"

using namespace std;

using namespace ulaval;

int main(int argc, char** argv)
{

	// D�finition d'une fonction lambda pour la comparaision.
	auto predicat = [](int i, int j) -> bool 
	{ 
		return (i < j);
	};

	// D�finition d'une fonction pour afficher un message d'utilisation de la
	// classe CompteurTemporel.
	auto afficher_message = [](const char* message) 
	{
		std::cout << "***\t\tIFT-2008\t\t***\n"
		<< "*\n"
		<< "* Voici un example pour l'utilisation de la classe CompteurTemporel.\n"
		<< "*\n"
		<< "* " << message << "\n"
		<< "*\n"
		<< "***\n\n";
	};

	// D�finition d'une fonction lambda pour la comparaison.
	auto afficher_duree = [](double duree)
	{
		std::cout << "Temps d'execution de la recherche:\n"
			<< "(s)   : " << std::fixed << duree			<< "\n"
			<< "(ms)  : " << std::fixed << duree * 1e+3		<< "\n"
			<< "(mcs) : " << std::fixed << duree * 1e+6		<< "\n"
			<< "(ns)  : " << std::fixed << duree * 1e+9		<< "\n"
			<< "(ps)  : " << std::fixed << duree * 1e+12	<< "\n\n";
	};




	// Cr�ation d'un objet de type compteur (non actif)
	CompteurTemporel<double, std::milli, std::chrono::duration<double, std::milli>>
		compteur(false);


	// D�finition de la valeur minimale du nombre al�atoire.
	const unsigned long long RANGE_MIN = 1;

	// D�finition de la valeur maximale du nombre al�atoire.
	const unsigned long long RANGE_MAX = static_cast<unsigned long long>(1e+6L);

	// D�finition du nombre d'it�ration.
	const unsigned long long NOMBRE_ELEMENTS = static_cast<unsigned long long>(1e+6L);



	// D�claration du g�n�rateur de nombre pseudo-al�atoire.
	std::random_device rd;

	// D�finition du moteur de nombre al�atoire. 
	std::default_random_engine re(rd());

	// D�finition du type de distribution de
	// nombres al�atoire entre [RANGE_MIN, RANGE_MAX]
	std::uniform_int_distribution<int> rand(RANGE_MIN, RANGE_MAX);



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
	const size_t NOMBRE_ITERATION_MAX = 50;

	// D�finition d'une variable pour le nombre d'iteration.
	size_t iter = 0;

	// D�claration d'une variable pour maintenir une valeur entiere aleatoire.
	int valeur;

	// D�finition d'une variable de condition pour la recherche.
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

		// D�finition de l'indice (position de l'iterateur) une fois la valeur trouvee.
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

		// Incrementation du nombre d'it�ration.
		++iter;
	}

	// Capture de la dur�e.
	duree = compteur.duree() * 1e-3;

	// Affichage du temps d'�x�cution de la recherche.
	afficher_duree(duree);

	return 0;
}