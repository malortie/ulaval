/**
* \file iterator.hpp
* \brief Contient cinq catégories d'itérateurs, similaires à ceux de la librarie standard.
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/19/2015
*/

#ifndef ITERATOR_HPP__
#define ITERATOR_HPP__

namespace ulaval
{
namespace iterateurs
{

//
// BASE ITÉRATEUR
//


/**
 * \class _iterator_base
 *
 * \brief Classe de base pour les itérateurs
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template <typename T, bool _isConst>
struct _iterator_base;


//
// BASE ITÉRATEUR (muable)
//

/**
* \class _iterator_base
*
* \brief Classe de base pour les itérateurs
* \tparam T Le type des éléments pointés. 
*
*/
template <typename T>
struct _iterator_base <T, false >
{
	typedef _iterator_base<T, false> _MyType;
	
	/**
	 * \brief Constructeur prenant en entrée un pointeur vers un tableau et un indice de déplacement.
	 * \param ptr Un pointeur vers le premier élément d'un tableau contenant des éléments de type T.
	 * \param offset La position de départ de l'itérateur.
	 */
	_iterator_base(T* ptr, int offset)
		: m_ptr(ptr), m_offset(offset)
	{

	}

	/**
	 * \brief Constructeur prenant en entrée un itérateur muable de type T. 
	 */
	_iterator_base(const _MyType& it)
		: m_ptr(it.m_ptr), m_offset(it.m_offset)
	{

	}

	/**
	 * \brief operateur de d'égalité.
	 * \return Vrai si l'adresse de m_ptr est identique à celle de it et que l'indice de déplacement est identique à celui de it. Sinon, retourne Faux.
	 */
	bool operator==(const _MyType& it) const
	{
		return m_ptr == it.m_ptr && m_offset == it.m_offset;
	}

	/**
	 * \brief operateur de d'égalité.
	 * \return Vrai si l'adresse de m_ptr diffère de it ou  si l'indice de déplacement diffère de it. Sinon, retourne Faux.
	 */
	bool operator!=(const _MyType& it) const
	{
		return m_ptr != it.m_ptr || m_offset != it.m_offset;
	}

protected:
	T* m_ptr; /*!< Pointeur vers un tableau */
	int m_offset; /*!< Indice de déplacement. */
};

//
// BASE ITÉRATEUR (immuable)
//

/**
 * \class _iterator_base
 *
 * \brief Classe de base pour les itérateurs
 * \tparam T Le type des éléments pointés.
 *
 */
template <typename T>
struct _iterator_base < T, true >
{
	typedef _iterator_base<T, true> _MyType;

	/**
	 * \brief Constructeur prenant en entrée un pointeur vers un tableau et un indice de déplacement.
	 * \param ptr Un pointeur vers le premier élément d'un tableau contenant des éléments de type T.
	 * \param offset La position de départ de l'itérateur.
	 */
	_iterator_base(const T* ptr, int offset)
		: m_ptr(ptr), m_offset(offset)
	{

	}

	/**
	 * \brief Constructeur prenant en entrée un itérateur immuable de type T.
	 */
	_iterator_base(const _MyType& it)
		: m_ptr(it.m_ptr), m_offset(it.m_offset)
	{

	}

protected:
	const T* m_ptr;  /*!< Pointeur immuable vers un tableau */
	int m_offset;  /*!< Indice de déplacement. */
};

//
// ITÉRATEUR INPUT
//

/**
* \class _input_iterator
*
* \brief Classe de base pour les itérateurs en lecture seulement
* \tparam T Le type des éléments pointés.
* \tparam _isConst Propriété de modification des variables pointées
*
*/
template<typename T, bool _isConst>
struct _input_iterator;

//
// ITÉRATEUR INPUT (muable)
//

/**
 * \class _input_iterator
 *
 * \brief Classe de base pour les itérateurs en lecture seulement
 * \tparam T Le type des éléments pointés.
 *
 */
template<typename T>
struct _input_iterator<T, false> : _iterator_base <T, false>
{
	typedef _input_iterator<T, false> _MyType;
	typedef _iterator_base<T, false> _MyBase;

	_input_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_input_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Retourne une référence immuable à la position spécifiée par l'indice de déplacement.
	 * \return Une référence immuable à la position spécifiée par l'indice de déplacement.
	 */
	const T& operator*() const
	{
		return *(m_ptr + m_offset);
	}
};

//
// ITÉRATEUR INPUT (immuable)
//

/**
 * \class _input_iterator
 *
 * \brief Classe de base pour les itérateurs en lecture seulement.
 * \tparam T Le type des éléments pointés.
 *
 */
template<typename T>
struct _input_iterator<T, true> : _iterator_base < T, true >
{
	typedef _input_iterator<T, true> _MyType;
	typedef _iterator_base<T, true> _MyBase;


	_input_iterator(const T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_input_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Retourne une référence immuable à la position spécifiée par l'indice de déplacement.
	 * \return Une référence immuable à la position spécifiée par l'indice de déplacement.
	 */
	const T& operator*() const
	{
		return *(m_ptr + m_offset);
	}
};

//
// ITÉRATEUR SORTIE
//

/**
 * \class _output_iterator
 *
 * \brief Classe de base pour les itérateurs en lecture et en écriture.
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isConst>
struct _output_iterator;

//
// ITÉRATEUR SORTIE (muable)
//

/**
 * \class _output_iterator
 *
 * \brief Classe de base pour les itérateurs en lecture et en écriture.
 * \tparam T Le type des éléments pointés.
 *
 */
template<typename T>
struct _output_iterator<T, false> : _input_iterator < T, false >
{
	typedef _output_iterator<T, false> _MyType;
	typedef _input_iterator<T, false> _MyBase;

	_output_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_output_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Retourne une référence à la position spécifiée par l'indice de déplacement.
	 * \return Une référence à la position spécifiée par l'indice de déplacement.
	 */
	T& operator*()
	{
		return *(m_ptr + m_offset);
	}
};

//
// ITÉRATEUR SORTIE (immuable)
//

/**
 * \class _output_iterator
 *
 * \brief Classe de base pour les itérateurs en lecture et en écriture.
 * \tparam T Le type des éléments pointés.
 *
 */
template<typename T>
struct _output_iterator<T, true> : _input_iterator < T, true >
{
	typedef _output_iterator<T, true> _MyType;
	typedef _input_iterator<T, true> _MyBase;


	_output_iterator(const T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_output_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}
};

//
// ITÉRATEUR UNIDIRECTIONEL
//

/**
* \class _forward_iterator
*
* \brief Classe de base pour les itérateurs unidirectionnels
* \tparam T Le type des éléments pointés.
* \tparam _isReverse Détermine le sens du déplacement
* \tparam _isConst Propriété de modification des variables pointées
*
*/
template<typename T, bool _isReverse, bool _isConst>
struct _forward_iterator;


//
// ITÉRATEUR UNIDIRECTIONEL (sens naturel)
//

/**
 * \class _forward_iterator
 *
 * \brief Classe de base pour les itérateurs unidirectionnels
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isConst>
struct _forward_iterator<T, false, _isConst> : _output_iterator < T, _isConst >
{
	typedef _forward_iterator<T, false, _isConst> _MyType;
	typedef _output_iterator<T, _isConst> _MyBase;

	_forward_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_forward_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Opérateur de pré-incrémentation
	 * \return Une référence sur l'itérateur.
	 */
	_MyType& operator++() // pre-increment
	{
		m_offset++;

		return *this;
	}

	/**
	 * \brief Opérateur de post-incrémentation
	 * \return Une copie de l'objet avant incrémentation.
	 */
	_MyType operator++(int) // post-increment
	{
		_MyType it = *this;
		m_offset++;

		return it;
	}
};


//
// ITÉRATEUR UNIDIRECTIONEL (sens inverse)
//

/**
 * \class _forward_iterator
 *
 * \brief Classe de base pour les itérateurs unidirectionnels
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isConst>
struct _forward_iterator<T, true, _isConst> : _output_iterator < T, _isConst >
{
	typedef _forward_iterator<T, true, _isConst> _MyType;
	typedef _output_iterator<T, _isConst> _MyBase;

	_forward_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_forward_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Opérateur de pré-incrémentation
	 * \return Une référence sur l'itérateur.
	 */
	_MyType& operator++() // pre-increment
	{
		// Comme il s'agit de la spécialisation de sens inverse,
		// il faut décrémenter l'indice de déplacement.
		m_offset--;

		return *this;
	}

	/**
	 * \brief Opérateur de post-incrémentation
	 * \return Une copie de l'objet avant incrémentation.
	 */
	_MyType operator++(int) // post-increment
	{
		_MyType it = *this;

		// Comme il s'agit de la spécialisation de sens inverse,
		// il faut décrémenter l'indice de déplacement.
		m_offset--;

		return it;
	}
};


//
// ITÉRATEUR BIDIRECTIONNEL
//

/**
 * \class _bidirectional_iterator
 *
 * \brief Classe de base pour les itérateurs bidirectionnels
 * \tparam T Le type des éléments pointés.
 * \tparam _isReverse Détermine le sens du déplacement
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isReverse, bool _isConst>
struct _bidirectional_iterator;

//
// ITÉRATEUR BIDIRECTIONNEL (sens naturel)
//

/**
* \class _bidirectional_iterator
*
* \brief Classe de base pour les itérateurs bidirectionnels
* \tparam T Le type des éléments pointés.
* \tparam _isConst Propriété de modification des variables pointées
*
*/
template<typename T, bool _isConst>
struct _bidirectional_iterator<T, false, _isConst> : _forward_iterator < T, false, _isConst >
{
	typedef _bidirectional_iterator<T, false, _isConst> _MyType;
	typedef _forward_iterator<T, false, _isConst> _MyBase;

	_bidirectional_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_bidirectional_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Opérateur de pré-décrémentation
	 * \return Une référence sur l'itérateur.
	 */
	_MyType& operator--() // pre-decrement
	{
		m_offset--;

		return *this;
	}

	/**
	 * \brief Opérateur de post-décrémentation
	 * \return Une copie de l'objet avant décrémentation.
	 */
	_MyType operator--(int) // post-decrement
	{
		_MyType it = *this;
		m_offset--;

		return it;
	}
};

//
// ITÉRATEUR BIDIRECTIONNEL (sens inverse)
//

/**
 * \class _bidirectional_iterator
 *
 * \brief Classe de base pour les itérateurs bidirectionnels
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isConst>
struct _bidirectional_iterator<T, true, _isConst> : _forward_iterator < T, true, _isConst >
{
	typedef _bidirectional_iterator<T, true, _isConst> _MyType;
	typedef _forward_iterator<T, true, _isConst> _MyBase;

	_bidirectional_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_bidirectional_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Opérateur de pré-décrémentation
	 * \return Une référence sur l'itérateur.
	 */
	_MyType& operator--() // pre-decrement
	{
		// Comme il s'agit de la spécialisation de sens inverse,
		// il faut incrémenter l'indice de déplacement.
		m_offset++;

		return *this;
	}

	/**
	 * \brief Opérateur de post-décrémentation
	 * \return Une copie de l'objet avant décrémentation.
	 */
	_MyType operator--(int) // post-decrement
	{
		_MyType it = *this;

		// Comme il s'agit de la spécialisation de sens inverse,
		// il faut incrémenter l'indice de déplacement.
		m_offset++;

		return it;
	}
};

//
// ITÉRATEUR D'ACCÈS ALÉATOIRE 
//

/**
 * \class _random_access_iterator
 *
 * \brief Classe de base pour les itérateurs d'accès aléatoire
 * \tparam T Le type des éléments pointés.
 * \tparam _isReverse Détermine le sens du déplacement
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isReverse, bool _isConst>
struct _random_access_iterator;

//
// ITÉRATEUR D'ACCÈS ALÉATOIRE (sens naturel)
//

/**
 * \class _random_access_iterator
 *
 * \brief Classe de base pour les itérateurs d'accès aléatoire
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isConst>
struct _random_access_iterator<T, false, _isConst> : _bidirectional_iterator < T, false, _isConst >
{
	typedef _random_access_iterator<T, false, _isConst> _MyType;
	typedef _bidirectional_iterator<T, false, _isConst> _MyBase;

	_random_access_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_random_access_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Opérateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'itérateur à la position spécifiée par l'indice de déplacement augmenté de k.
	 */
	_MyType operator+(int k) const
	{
		return _MyType(m_ptr, m_offset + k);
	}

	/**
	 * \brief Opérateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'itérateur à la position spécifiée par l'indice de déplacement soustrait de k.
	 */
	_MyType operator-(int k) const
	{
		return _MyType(m_ptr, m_offset - k);
	}
};

//
// ITÉRATEUR D'ACCÈS ALÉATOIRE (sens inverse)
//

/**
 * \class _random_access_iterator
 *
 * \brief Classe de base pour les itérateurs d'accès aléatoire
 * \tparam T Le type des éléments pointés.
 * \tparam _isConst Propriété de modification des variables pointées
 *
 */
template<typename T, bool _isConst>
struct _random_access_iterator<T, true, _isConst> : _bidirectional_iterator < T, true, _isConst >
{
	typedef _random_access_iterator<T, true, _isConst> _MyType;
	typedef _bidirectional_iterator<T, true, _isConst> _MyBase;

	_random_access_iterator(T* ptr, int offset)
		: _MyBase(ptr, offset)
	{

	}

	_random_access_iterator(const _MyType& it)
		: _MyBase(it)
	{

	}

	/**
	 * \brief Opérateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'itérateur à la position spécifiée par l'indice de déplacement augmenté de k.
	 */
	_MyType operator+(int k) const
	{
		// Comme il s'agit de la spécialisation de sens inverse,
		// il faut soustraire de k.
		return _MyType(m_ptr, m_offset - k);
	}

	/**
	 * \brief Opérateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'itérateur à la position spécifiée par l'indice de déplacement soustrait de k.
	 */
	_MyType operator-(int k) const
	{
		// Comme il s'agit de la spécialisation de sens inverse,
		// il faut augmenter de k.
		return _MyType(m_ptr, m_offset + k);
	}
};

}
}

#endif /* ITERATOR_HPP__ */