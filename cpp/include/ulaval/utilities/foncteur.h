/**
 * \file foncteur.h
 *
 * \brief Fichier contenant les déclarations des méthodes de \class foncteur.
 *
 * \author Marc-Antoine Lortie
 *
 * \date 06/16/15
 */

#ifndef FONCTEUR_H__
#define FONCTEUR_H__

/**
 * \namespace ulaval
 */
namespace ulaval
{

/**
 * \namespace utilities
 */
namespace utilities
{

/**
 * \class functor Une classe de foncteur
 *
 * \tparam R Le type de retour.
 * \tparam Args Un ensemble de types pour les arguments.
 */
template<typename R, typename... Args>
class foncteur
{
public:

	//
	// Définitions de types
	//

	/**
	 * \typedef R(*F)(Args...) Le type de la classe foncteur
	 */
	using Foncteur = foncteur<R, Args...>;

	/**
	 * \typedef R(*F)(Args...) Le type de la fonction (pointeur)
	 */
	using F = R(*)(Args...);

	/**
	 * \brief Constructeur par defaut
	 */
	foncteur();

	/**
	 * \brief Constructeur prenant en entree un foncteur
	 *
	 * \param p_f Un objet de type Foncteur
	 */
	foncteur(const Foncteur& p_f);

	/**
	 * \brief Constructeur prenant en entree une fonction de type F
	 *
	 * \param p_f Un pointeur vers une fonction possédant la même signature que celle de Foncteur.
	 */
	foncteur(F p_f); // functor(F p_f) <=> functor(R(*p_f)(Args...))

	//
	// Surcharges d'opérateurs
	//

	/**
	 * \brief Surcharge de l'opérateur de déréférentiation
	 *
	 * \return Une valeur de type R.
	 */
	F operator*(); // F operator*() <=> R(*)(Args...) operator*()

	/**
	* \brief Surcharge de l'opérateur d'appel (application de méthode)
	*
	* \param args Un ensemble de paramètres de même type que ceux de la signature.
	*
	* \return Une valeur de type R.
	*/
	R operator()(Args... args); // (Args...) -> ({int a, int b, int ...})

	/**
	* \brief Surcharge de l'opérateur d'affectation
	*
	* \param p_f Un objet de type foncteur
	*
	* \return Une référence sur l'objet lui-même.
	*/
	Foncteur& operator=(const Foncteur& p_f);

	/**
	* \brief Surcharge de l'opérateur d'affectation
	*
	* \param F Un pointeur vers une fonction possédant la même signature que celle de Foncteur.
	*
	* \return Une référence sur l'objet lui-même.
	*/
	Foncteur& operator=(F p_f);

private:

	F m_f; /*!< Pointeur de fonction. */
};

} /* utilities */

} /* ulaval */

#include "foncteur.hpp"

#endif // FONCTEUR_H__
