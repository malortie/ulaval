/**
* \file array.hpp
* \brief Un tableau de taille fixe possédant un itérateur.
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/18/2015
*/

#ifndef ARRAY_HPP__
#define ARRAY_HPP__

#include "iterator.hpp"

/**
 * \namespace ulaval
 */
namespace ulaval
{
/**
 * \namespace conteneurs
 */
namespace conteneurs
{

/**
 * \class array
 *
 * \brief Classe de base pour les itérateurs
 * \tparam T Le type de donnée du tableau
 * \tparam N La taille du tableau
 *
 */
template<typename T, std::size_t N>
struct array
{
	typedef T					value_type;
	typedef T&					reference;
	typedef T*					pointer;

	typedef const value_type	const_value;
	typedef const reference		const_reference;
	typedef const pointer		const_pointer;

	typedef std::size_t			size_type;
	typedef std::ptrdiff_t		difference_type;


	typedef array<T, N>			self_type;
	typedef self_type&			self_reference;
	typedef self_type*			self_pointer;


	typedef ulaval::iterateurs::_random_access_iterator<T, false, false>	iterator;
	typedef ulaval::iterateurs::_random_access_iterator<T, false, true>		const_iterator;
	typedef ulaval::iterateurs::_random_access_iterator<T, true, false>		reverse_iterator;
	typedef ulaval::iterateurs::_random_access_iterator<T, true, true>		const_reverse_iterator;

	/**
	 * \brief Constructeur
	 */
	array()
	{
		std::memset(m_data, 0, sizeof(m_data));
	}

	/**
	 * \brief Constructeur prenant en entrée un tableau C de taille N.
	 * \param a[N] Un tableau de taille N.
	 */
	array(value_type a[N])
	{
		std::memcpy(m_data, a, sizeof(a));
	}

	/**
	 * \brief Constructeur prenant en entrée un tableau C de taille N.
	 * \param a[N] Un tableau de taille N.
	 */
	array(const self_reference& other)
	{
		std::memcpy(m_data, other.m_data, sizeof(m_data));
	}

	/**
	 * \brief operator[]
	 * \param index La position de l'élément à retourner
	 * \return Une référence à la position specifiée par l'indice
	 */
	reference operator[](const size_type index)
	{
		return m_data[index];
	}

	/**
	 * \brief operator[]
	 * \param index La position de l'élément à retourner
	 * \return Une reference constante à la position spécifiée par l'indice
	 */
	const_reference operator[](const size_type index) const
	{
		return m_data[index];
	}

	/**
	 * \brief Retourne une pointeur vers le premier élément du tableau.
	 * \return Un pointeur vers le premier élément du tableau
	 */
	pointer data()
	{
		return m_data;
	}

	/**
	 * \brief Retourne l'élément à la position specifiée par l'indice.
	 * \return Une référence à la position spécifiée par l'indice
	 */
	reference at(const size_type index)
	{
		return m_data[index];
	}

	/**
	 * \brief Retourne l'élément à la position spécifiée par l'indice.
	 * \return Une référence constante à la position spécifiée par l'indice
	 */
	const_reference at(const size_type index) const
	{
		return m_data[index];
	}

	/**
	 * \brief Retourne l'élément au début du tableau.
	 * \return Une référence au début du tableau.
	 */
	reference front()
	{
		return m_data[0];
	}

	/**
	 * \brief Retourne l'élément au début du tableau.
	 * \return Une référence constante au début du tableau.
	 */
	const_reference front() const
	{
		return m_data[0];
	}

	/**
	 * \brief Retourne l'élément à la fin du tableau.
	 * \return Une référence à la fin du tableau.
	 */
	reference back()
	{
		return m_data[N - 1];
	}

	/**
	 * \brief Retourne l'élément à la fin du tableau.
	 * \return Une référence constante à la fin du tableau.
	 */
	const_reference back() const
	{
		return m_data[N - 1];
	}

	/**
	 * \brief Vérifie si le tableau est vide.
	 * \return Vrai si la taille du tableau est plus petite ou égale a zéro.
	 * \return Faux si le tableau contient au moins un élément.
	 */
	bool empty() const
	{
		return N <= 0;
	}

	/**
	 * \brief Retourne la taille du tableau.
	 * \return La taille du tableau.
	 */
	size_type size() const
	{
		return N;
	}

	/**
	 * \brief Retourne N.
	 * \return N
	 */
	size_type max_size() const
	{
		return N;
	}

	/**
	 * \brief Affecte une valeur a tous les éléments du tableau.
	 * \param val La valeur par défaut
	 */
	void fill(value_type val)
	{
		_fill(val, 0);
	}

	/**
	 * \brief Permet d'intervertir le tableau avec celui un autre array<T, N>.
	 * \param other Un object array<T, N> (contenant N éléments de type T).
	 */
	void swap(const self_reference other)
	{
		value_type tmp;

		_swap(other.m_data, &tmp, 0);
	}

	/**
	 * \brief Retourne un itérateur muable au début du tableau.
	 * \return Un itérateur muable au début du tableau.
	 */
	iterator begin()
	{
		return iterator(m_data, 0);
	}

	/**
	 * \brief Retourne un itérateur muable à la fin du tableau.
	 * \return Un itérateur muable à la fin du tableau.
	 */
	iterator end()
	{
		return iterator(m_data, N);
	}

	/**
	 * \brief Retourne un itérateur immuable au début  du tableau.
	 * \return Un itérateur immuable au début du tableau.
	 */
	const_iterator cbegin()
	{
		return const_iterator(m_data, 0);
	}

	/**
	 * \brief Retourne un itérateur immuable à la fin du tableau.
	 * \return Un itérateur immuable à la fin du tableau.
	 */
	const_iterator cend()
	{
		return const_iterator(m_data, N);
	}

	/**
	 * \brief Retourne un itérateur à rebours muable à la fin du tableau.
	 * \return Un itérateur à rebours muable à la fin du tableau.
	 */
	reverse_iterator rbegin()
	{
		return reverse_iterator(m_data, N - 1);
	}

	/**
	 * \brief Retourne un itérateur à rebours muable au début du tableau.
	 * \return Un itérateur à rebours muable au début du tableau.
	 */
	reverse_iterator rend()
	{
		return reverse_iterator(m_data, -1);
	}

	/**
	 * \brief Retourne un itérateur à rebours immuable à la fin du tableau.
	 * \return Un itérateur à rebours immuable à la fin du tableau.
	 */
	const_reverse_iterator crbegin()
	{
		return const_reverse_iterator(m_data, N - 1);
	}

	/**
	 * \brief Retourne un itérateur à rebours immuable au début du tableau.
	 * \return Un itérateur à rebours immuable au début du tableau.
	 */
	const_reverse_iterator crend()
	{
		return const_reverse_iterator(m_data, -1);
	}

private:

	void _fill(const value_type& val, const size_type i)
	{
		m_data[i] = val;

		if ((i + 1) < N)
			_fill(val, i + 1);
	}

	void _swap(pointer data, pointer tmp, const size_type i)
	{
		*tmp = m_data[i];
		m_data[i] = data[i];
		data[i] = *tmp;

		if ((i + 1) < N)
			_swap(data, tmp, i + 1);
	}

private:

	value_type m_data[N];  /*!< Le tableau contenant N éléments de type T. */

};

}
}



#endif // ARRAY_HPP__