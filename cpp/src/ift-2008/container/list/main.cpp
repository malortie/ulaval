/**
 * \file main.cpp
 * \brief Exemples avec une liste doublement cha�n�e.
 * \author Marc-Antoine Lortie
 * \version 1.0
 * \date 5/21/2015
 */
 
#include <time.h>
#include <string.h>
#include <iomanip>

#include "list.hpp"

using namespace ulaval;

// D�claration d'un type de liste doublement cha�n�e contenant des entiers.
typedef ulaval::conteneurs::list<int>	liste_entiers;

// D�claration d'un it�rateur op�rant sur des liste doublement 
// cha�n�e qui contient des entiers.
typedef liste_entiers::iterator			iterateur_entier;

/* \brief Fonction permettant d'afficher les valeurs d'une liste d'entier.
 * \details Fonction permettant de formater, aligner et 
 *			d'afficher 16 entiers par ligne.
 *
 * \param current Un it�rateur repr�sentant la position de d�part
 * \param end Un it�rateur repr�sentant la position de fin (non affich�e)
 */
void print_list(iterateur_entier& current, iterateur_entier& end)
{
	// Compteur statique pour mesurer le nombre d'�l�ments imprim�s.
	static std::size_t inc = 0;

	// V�rifie si inc est un diviseur de 16.
	// Affiche un saut de ligne.
	if (inc++ > 0 && (inc % 16) == 0)
		std::cout << std::endl;

	// Affiche la valeur contenue dans le noeud, � la position de current.
	// Alignement des valeurs � gauche et laisser un espace de 3, plus ' '
	std::cout << std::left << std::setw(3) << *current << ' ';

	// D�finition d'un it�rateur pour comparer la position suivante 
	// avec celle de fin.
	iterateur_entier it = current;
	++it;

	// Si la position suivante est diff�rente de la position cible,
	// appel r�cursif de print_list.
	if (it != end)
		print_list(it, end);

	// Remise � z�ro du compteur.
	inc = 0;
}

int main(int argc, char**argv)
{
	//
	// Exemple 1: D�monstration des m�thodes de base d'utilisation de la liste. 
	//
	
	// D�claration d'une liste d'entiers.
	liste_entiers l;	// {}

	// Ajout de valeurs � la fin de la liste.
	l.push_back(0);		// {0}
	l.push_back(1);		// {0  1}
	l.push_back(2);		// {0  1  2}
	l.push_back(3);		// {0  1  2  3}
	
	std::cout << "taille de l: "
			  << l.size()
			  << std::endl; // taille de l: 4
	
	
	// Ajout de valeurs au d�but de la liste.
	l.push_front(-1);	// {-1  0  1  2  3}
	l.push_front(-2);	// {-2 -1  0  1  2  3}
	l.push_front(-3);	// {-3 -2 -1  0  1  2  3}
	
	std::cout << "taille de l: "
			  << l.size()
			  << std::endl; // taille de l: 7
	
	// D�finition d'un it�rateur initialis� �
	// la t�te de la liste.
	iterateur_entier it = l.begin();
	// {-3 -2 -1  0  1  2  3}
	//   ^
	
	// incr�mentation de l'it�rateur.
	++it;
	// {-3 -2 -1  0  1  2  3}
	//      ^
	
	it = l.insert_after(it, 12);
	/* {-3 -2  12 -1  0  1  2  3}
				   ^
	insert_after retourne un it�rateur
	� la position du noeud d'insertion.
	*it -> 12
	*/
	
	it = l.insert_after(++it, 64);
	// {-3 - 2  12 -1  64  0  1  2  3}
	
	it = l.insert_after(++it, 64);
	// {-3 - 2  12 -1  64  0  64  1  2  3}
	
	it = l.insert_after(++it, 64);
	// {-3 - 2  12 -1  64  0  64  1  64  2  3}
	
	*(++it) = 64;
	// {-3 - 2  12 -1  64  0  64  1  64  64  3}
	
	*(++it) = 4;
	// {-3 - 2  12 -1  64  0  64  1  64  64  4}
	
	// Suppression de tous les noeuds ayant comme valeur 64.
	l.remove(64);
	// {-3 - 2  12 -1  0  1  4}
	
	// Suppression de toutes les valeurs dans la liste.
	l.clear();
	
	
	//
	// Exemple 2: Utilisation de la liste avec des valeurs al�atoires. 
	//
	
	// D�finition du nombre de valeurs � ajouter
	// al�atoirement dans la liste.
	const std::size_t NOMBRE_VALEURS = 128;
	
	// Initialisation du g�n�rateur de nombre al�atoires.
	srand(time_t(0));

	// Insertion de valeurs arbitraires dans la liste.
	for (std::size_t i = 0; i < NOMBRE_VALEURS; ++i)
		l.push_back((rand() % NOMBRE_VALEURS) + 1);
	
	
	// D�finition d'un it�rateur situ� au d�but de la liste.
	iterateur_entier debut = l.begin();

	// D�finition d'un it�rateur situ� � la fin de la liste.
	iterateur_entier fin = l.end();

	// Affichage du premier �l�ment de la liste.
	// (n�cessaire pour la fonction print_list qui utilise
	//  l'op�rateur modulus pour formater le tableau � l'�cran
	//  avec des colonnes de 16.)
	std::cout << std::left << std::setw(3) << *debut << ' ';

	// Affichage de la liste.
	print_list(++debut, fin);
	
	/* Sortie en console:

	   39  40  119 6   24  22  46  30  83  21  94  69  119 26  58  50
	   114 46  54  89  113 20  24  51  26  44  82  65  126 23  15  79
	   73  28  12  118 60  74  41  100 94  95  64  96  110 105 53  8
	   27  43  78  93  120 66  69  2   42  9   28  65  99  57  49  79
	   21  85  18  81  95  69  18  30  76  64  29  71  60  112 72  85
	   34  81  44  81  112 91  117 10  80  96  54  18  21  55  128 10
	   113 26  50  31  104 77  18  85  4   128 29  4   75  119 28  31
	   110 104 120 60  67  37  79  81  117 122 71  60  123 89  35  7
	  */

	l.clear(); // {}
	
	return 0;
}