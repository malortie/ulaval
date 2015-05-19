/**
* \file iterator.hpp
* \brief Contient cinq cat�gories d'it�rateurs, similaires � ceux de la librarie standard.
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
// BASE IT�RATEUR
//


/**
 * \class _iterator_base
 *
 * \brief Classe de base pour les it�rateurs
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
 *
 */
template <typename T, bool _isConst>
struct _iterator_base;


//
// BASE IT�RATEUR (muable)
//

/**
* \class _iterator_base
*
* \brief Classe de base pour les it�rateurs
* \tparam T Le type des �l�ments point�s. 
*
*/
template <typename T>
struct _iterator_base <T, false >
{
	typedef _iterator_base<T, false> _MyType;
	
	/**
	 * \brief Constructeur prenant en entr�e un pointeur vers un tableau et un indice de d�placement.
	 * \param ptr Un pointeur vers le premier �l�ment d'un tableau contenant des �l�ments de type T.
	 * \param offset La position de d�part de l'it�rateur.
	 */
	_iterator_base(T* ptr, int offset)
		: m_ptr(ptr), m_offset(offset)
	{

	}

	/**
	 * \brief Constructeur prenant en entr�e un it�rateur muable de type T. 
	 */
	_iterator_base(const _MyType& it)
		: m_ptr(it.m_ptr), m_offset(it.m_offset)
	{

	}

	/**
	 * \brief operateur de d'�galit�.
	 * \return Vrai si l'adresse de m_ptr est identique � celle de it et que l'indice de d�placement est identique � celui de it. Sinon, retourne Faux.
	 */
	bool operator==(const _MyType& it) const
	{
		return m_ptr == it.m_ptr && m_offset == it.m_offset;
	}

	/**
	 * \brief operateur de d'�galit�.
	 * \return Vrai si l'adresse de m_ptr diff�re de it ou  si l'indice de d�placement diff�re de it. Sinon, retourne Faux.
	 */
	bool operator!=(const _MyType& it) const
	{
		return m_ptr != it.m_ptr || m_offset != it.m_offset;
	}

protected:
	T* m_ptr; /*!< Pointeur vers un tableau */
	int m_offset; /*!< Indice de d�placement. */
};

//
// BASE IT�RATEUR (immuable)
//

/**
 * \class _iterator_base
 *
 * \brief Classe de base pour les it�rateurs
 * \tparam T Le type des �l�ments point�s.
 *
 */
template <typename T>
struct _iterator_base < T, true >
{
	typedef _iterator_base<T, true> _MyType;

	/**
	 * \brief Constructeur prenant en entr�e un pointeur vers un tableau et un indice de d�placement.
	 * \param ptr Un pointeur vers le premier �l�ment d'un tableau contenant des �l�ments de type T.
	 * \param offset La position de d�part de l'it�rateur.
	 */
	_iterator_base(const T* ptr, int offset)
		: m_ptr(ptr), m_offset(offset)
	{

	}

	/**
	 * \brief Constructeur prenant en entr�e un it�rateur immuable de type T.
	 */
	_iterator_base(const _MyType& it)
		: m_ptr(it.m_ptr), m_offset(it.m_offset)
	{

	}

protected:
	const T* m_ptr;  /*!< Pointeur immuable vers un tableau */
	int m_offset;  /*!< Indice de d�placement. */
};

//
// IT�RATEUR INPUT
//

/**
* \class _input_iterator
*
* \brief Classe de base pour les it�rateurs en lecture seulement
* \tparam T Le type des �l�ments point�s.
* \tparam _isConst Propri�t� de modification des variables point�es
*
*/
template<typename T, bool _isConst>
struct _input_iterator;

//
// IT�RATEUR INPUT (muable)
//

/**
 * \class _input_iterator
 *
 * \brief Classe de base pour les it�rateurs en lecture seulement
 * \tparam T Le type des �l�ments point�s.
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
	 * \brief Retourne une r�f�rence immuable � la position sp�cifi�e par l'indice de d�placement.
	 * \return Une r�f�rence immuable � la position sp�cifi�e par l'indice de d�placement.
	 */
	const T& operator*() const
	{
		return *(m_ptr + m_offset);
	}
};

//
// IT�RATEUR INPUT (immuable)
//

/**
 * \class _input_iterator
 *
 * \brief Classe de base pour les it�rateurs en lecture seulement.
 * \tparam T Le type des �l�ments point�s.
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
	 * \brief Retourne une r�f�rence immuable � la position sp�cifi�e par l'indice de d�placement.
	 * \return Une r�f�rence immuable � la position sp�cifi�e par l'indice de d�placement.
	 */
	const T& operator*() const
	{
		return *(m_ptr + m_offset);
	}
};

//
// IT�RATEUR SORTIE
//

/**
 * \class _output_iterator
 *
 * \brief Classe de base pour les it�rateurs en lecture et en �criture.
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
 *
 */
template<typename T, bool _isConst>
struct _output_iterator;

//
// IT�RATEUR SORTIE (muable)
//

/**
 * \class _output_iterator
 *
 * \brief Classe de base pour les it�rateurs en lecture et en �criture.
 * \tparam T Le type des �l�ments point�s.
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
	 * \brief Retourne une r�f�rence � la position sp�cifi�e par l'indice de d�placement.
	 * \return Une r�f�rence � la position sp�cifi�e par l'indice de d�placement.
	 */
	T& operator*()
	{
		return *(m_ptr + m_offset);
	}
};

//
// IT�RATEUR SORTIE (immuable)
//

/**
 * \class _output_iterator
 *
 * \brief Classe de base pour les it�rateurs en lecture et en �criture.
 * \tparam T Le type des �l�ments point�s.
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
// IT�RATEUR UNIDIRECTIONEL
//

/**
* \class _forward_iterator
*
* \brief Classe de base pour les it�rateurs unidirectionnels
* \tparam T Le type des �l�ments point�s.
* \tparam _isReverse D�termine le sens du d�placement
* \tparam _isConst Propri�t� de modification des variables point�es
*
*/
template<typename T, bool _isReverse, bool _isConst>
struct _forward_iterator;


//
// IT�RATEUR UNIDIRECTIONEL (sens naturel)
//

/**
 * \class _forward_iterator
 *
 * \brief Classe de base pour les it�rateurs unidirectionnels
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
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
	 * \brief Op�rateur de pr�-incr�mentation
	 * \return Une r�f�rence sur l'it�rateur.
	 */
	_MyType& operator++() // pre-increment
	{
		m_offset++;

		return *this;
	}

	/**
	 * \brief Op�rateur de post-incr�mentation
	 * \return Une copie de l'objet avant incr�mentation.
	 */
	_MyType operator++(int) // post-increment
	{
		_MyType it = *this;
		m_offset++;

		return it;
	}
};


//
// IT�RATEUR UNIDIRECTIONEL (sens inverse)
//

/**
 * \class _forward_iterator
 *
 * \brief Classe de base pour les it�rateurs unidirectionnels
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
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
	 * \brief Op�rateur de pr�-incr�mentation
	 * \return Une r�f�rence sur l'it�rateur.
	 */
	_MyType& operator++() // pre-increment
	{
		// Comme il s'agit de la sp�cialisation de sens inverse,
		// il faut d�cr�menter l'indice de d�placement.
		m_offset--;

		return *this;
	}

	/**
	 * \brief Op�rateur de post-incr�mentation
	 * \return Une copie de l'objet avant incr�mentation.
	 */
	_MyType operator++(int) // post-increment
	{
		_MyType it = *this;

		// Comme il s'agit de la sp�cialisation de sens inverse,
		// il faut d�cr�menter l'indice de d�placement.
		m_offset--;

		return it;
	}
};


//
// IT�RATEUR BIDIRECTIONNEL
//

/**
 * \class _bidirectional_iterator
 *
 * \brief Classe de base pour les it�rateurs bidirectionnels
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isReverse D�termine le sens du d�placement
 * \tparam _isConst Propri�t� de modification des variables point�es
 *
 */
template<typename T, bool _isReverse, bool _isConst>
struct _bidirectional_iterator;

//
// IT�RATEUR BIDIRECTIONNEL (sens naturel)
//

/**
* \class _bidirectional_iterator
*
* \brief Classe de base pour les it�rateurs bidirectionnels
* \tparam T Le type des �l�ments point�s.
* \tparam _isConst Propri�t� de modification des variables point�es
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
	 * \brief Op�rateur de pr�-d�cr�mentation
	 * \return Une r�f�rence sur l'it�rateur.
	 */
	_MyType& operator--() // pre-decrement
	{
		m_offset--;

		return *this;
	}

	/**
	 * \brief Op�rateur de post-d�cr�mentation
	 * \return Une copie de l'objet avant d�cr�mentation.
	 */
	_MyType operator--(int) // post-decrement
	{
		_MyType it = *this;
		m_offset--;

		return it;
	}
};

//
// IT�RATEUR BIDIRECTIONNEL (sens inverse)
//

/**
 * \class _bidirectional_iterator
 *
 * \brief Classe de base pour les it�rateurs bidirectionnels
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
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
	 * \brief Op�rateur de pr�-d�cr�mentation
	 * \return Une r�f�rence sur l'it�rateur.
	 */
	_MyType& operator--() // pre-decrement
	{
		// Comme il s'agit de la sp�cialisation de sens inverse,
		// il faut incr�menter l'indice de d�placement.
		m_offset++;

		return *this;
	}

	/**
	 * \brief Op�rateur de post-d�cr�mentation
	 * \return Une copie de l'objet avant d�cr�mentation.
	 */
	_MyType operator--(int) // post-decrement
	{
		_MyType it = *this;

		// Comme il s'agit de la sp�cialisation de sens inverse,
		// il faut incr�menter l'indice de d�placement.
		m_offset++;

		return it;
	}
};

//
// IT�RATEUR D'ACC�S AL�ATOIRE 
//

/**
 * \class _random_access_iterator
 *
 * \brief Classe de base pour les it�rateurs d'acc�s al�atoire
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isReverse D�termine le sens du d�placement
 * \tparam _isConst Propri�t� de modification des variables point�es
 *
 */
template<typename T, bool _isReverse, bool _isConst>
struct _random_access_iterator;

//
// IT�RATEUR D'ACC�S AL�ATOIRE (sens naturel)
//

/**
 * \class _random_access_iterator
 *
 * \brief Classe de base pour les it�rateurs d'acc�s al�atoire
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
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
	 * \brief Op�rateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'it�rateur � la position sp�cifi�e par l'indice de d�placement augment� de k.
	 */
	_MyType operator+(int k) const
	{
		return _MyType(m_ptr, m_offset + k);
	}

	/**
	 * \brief Op�rateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'it�rateur � la position sp�cifi�e par l'indice de d�placement soustrait de k.
	 */
	_MyType operator-(int k) const
	{
		return _MyType(m_ptr, m_offset - k);
	}
};

//
// IT�RATEUR D'ACC�S AL�ATOIRE (sens inverse)
//

/**
 * \class _random_access_iterator
 *
 * \brief Classe de base pour les it�rateurs d'acc�s al�atoire
 * \tparam T Le type des �l�ments point�s.
 * \tparam _isConst Propri�t� de modification des variables point�es
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
	 * \brief Op�rateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'it�rateur � la position sp�cifi�e par l'indice de d�placement augment� de k.
	 */
	_MyType operator+(int k) const
	{
		// Comme il s'agit de la sp�cialisation de sens inverse,
		// il faut soustraire de k.
		return _MyType(m_ptr, m_offset - k);
	}

	/**
	 * \brief Op�rateur d'addition
	 * \param k une constante.
	 * \return Une copie de l'it�rateur � la position sp�cifi�e par l'indice de d�placement soustrait de k.
	 */
	_MyType operator-(int k) const
	{
		// Comme il s'agit de la sp�cialisation de sens inverse,
		// il faut augmenter de k.
		return _MyType(m_ptr, m_offset + k);
	}
};

}
}

#endif /* ITERATOR_HPP__ */