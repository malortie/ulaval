/**
 * \brief Un exemple de foncteur avec quatres opérations de base:
 *		  Addition, soustraction, multiplication, division.
 *
 * \note Requiert C++11:
 *		 Eclipse:					-std=c++11
 *		 Netbeans:					-std=c++11
 *		 Visual Studio 2013/2015:	--
 *
 * \author Marc-Antoine Lortie
 *
 */

#include <iostream>

#include "foncteur.h"

using namespace ulaval::utilities;

int main(int argc, char**argv)
{
	// Fonction Lambda (C++ 11)
	//
	// Retourne la valeur de a additionée à celle de b.
	auto add = [](int a, int b) -> int
	{
		return a + b;
	};

	// Fonction Lambda (C++ 11)
	//
	// Retourne la valeur de a soustraite de celle de b.
	//
	// signature: int(int, int)
	// definition val sub: int -> int -> int
	//
	auto sub = [](int a, int b) -> int
	{
		return a - b;
	};

	// Fonction Lambda (C++ 11)
	//
	// Retourne la valeur de a multipliée par celle de b.
	auto mult = [](int a, int b) -> int
	{
		return a * b;
	};

	// Fonction Lambda (C++ 11)
	//
	// Retourne la valeur de a multipliée par celle de b.
	auto div = [](int a, int b) -> int
	{
		return a / b;
	};

	// Définition d'un foncteur qui prend en entrée des
	// fonctions dont la signature est int(int, int)
	foncteur<int, int, int> f(add); // foncteur(F p_f)
									// val: f.m_f -> int -> int -> int

	// Application du foncteur avec la méthode lambda add.

	std::cout << f(1, 2) << std::endl; // int operator()(int a, int b)
									   //
									   // Output: a + b
									   // ----------------------------
									   // > 3

	// Changement de fonction du foncteur pour celle de soustraction.

	f = sub;  // F operator=(const F& p_f)
			  // val: f.m_f -> int -> int -> int

	// Application du foncteur avec la méthode lambda sub.

	std::cout << f(5, 3) << std::endl; // int operator()(int a, int b)
									   //
									   // Output: a - b
									   // ----------------------------
									   // > 2

	// Changement de fonction du foncteur pour celle de multiplication.

	f = mult; // F operator=(const F& p_f)
			  // val: f.m_f -> int -> int -> int

	// Application du foncteur avec la méthode lambda mult.

	std::cout << f(2, 4) << std::endl; // int operator()(int a, int b)
									   //
									   // Output: a * b
									   // ----------------------------
									   // > 8

	// Changement de fonction du foncteur pour celle de division.

	f = div; // F operator=(const F& p_f)
			 // val: f.m_f -> int -> int -> int

	// Application du foncteur avec la méthode lambda div.

	std::cout << f(10, 5) << std::endl; // int operator()(int a, int b)
									   //
									   // Output: a / b
									   // ----------------------------
									   // > 2

	return 0;
}