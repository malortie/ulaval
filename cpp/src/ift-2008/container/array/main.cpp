#include <iostream>
#include "array.hpp"

int main(int argc, char**argv)
{
	// Déclaration d'un type de quintuplet (5 éléments)
	typedef ulaval::conteneurs::array<int, 5> Quintuplet;

	// Déclaration d'un quintuplet.
	Quintuplet a;

	// Affectations de valeurs.
	a[0] =  3;
	a[1] = -8;
	a[2] =  2;
	a[3] =  10;
	a[4] = -1;

	// Itérateur bidirectionnel.
	//
	// Quintuplet::iterator <=> ulaval::iterateurs::_random_access_iterator<T, false, false>
	//
	for (Quintuplet::iterator it = a.begin(); it != a.end(); ++it)
		std::cout << *it << ' ';

	// Fin de ligne.
	std::cout << std::endl;

	//
	// Output:
	//
	// 3 -8  2  10 -1
	//

	// Itérateur bidirectionnel à sens inverse.
	//
	// Quintuplet::reverse_iterator <=> ulaval::iterateurs::_random_access_iterator<T, true, false>
	//
	for (Quintuplet::reverse_iterator it = a.rbegin(); it != a.rend(); ++it)
		std::cout << *it << ' ';

	// Fin de ligne.
	std::cout << std::endl;

	//
	// Output:
	//
	// -1  10  2 -8  3
	//

	return 0;
}