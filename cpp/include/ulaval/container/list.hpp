/**
* \file list.hpp
* \brief Une liste doublement cha�n�e
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/21/2015
*/


#ifndef LIST_HPP__
#define LIST_HPP__

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
 * \class list
 *
 * \brief Classe de liste doublement cha�n�e.
 * \tparam T Le type de donn�e
 *
 */
template<typename T>
class list
{
	typedef list<T>				class_value;
	typedef class_value&		class_reference;
	typedef class_value*		class_pointer;


	/**
	 * \class node
	 *
	 * \brief Classe repr�sentant un noeud.
	 * \tparam _isConst Indique s'il s'agit d'un noeud constant.
	 *
	 */
	template<bool _isConst>
	struct node;

	typedef node<false>			node_value;
	typedef node<false>&		node_reference;
	typedef node<false>*		node_pointer;

	typedef node<true>			const_node_value;
	typedef node<true>&			const_node_reference;
	typedef node<true>*			const_node_pointer;

	typedef T					value_type;
	typedef value_type&			reference;
	typedef value_type*			pointer;

	typedef const value_type	const_value;
	typedef const reference		const_reference;
	typedef const pointer		const_pointer;

	typedef std::size_t			size_type;
	typedef std::ptrdiff_t		difference_type;


	//
	// NOEUD MUABLE
	//

	template<>
	struct node<false>
	{
		/**
		 * \brief Constructeur
		 */
		node() : m_data(0), m_prev(0), m_next(0)
		{

		}

		/**
		 * \brief Constructeur permetant d'ins�rer un noeud entre deux autres.
		 * \param data La valeur de type T
		 * \param prev Le noeud pr�c�dant 
		 * \param next La valeur suivant
		 */
		node(const_value data, node_pointer prev, node_pointer next) : m_data(data), m_prev(prev), m_next(next)
		{

		}
	
		node_pointer m_prev; /*!< Un pointeur vers le noeud pr�c�dant. */
		node_pointer m_next; /*!< Un pointeur vers le noeud suivant. */
		value_type	 m_data; /*!< La valeur du noeud repr�sent� par l'objet. */
	};

	//
	// NOEUD IMMUABLE
	//

	template<>
	struct node<true>
	{
		/**
		 * \brief Constructeur
		 */
		node() : m_data(0), m_prev(0), m_next(0)
		{

		}


		/**
		 * \brief Constructeur permetant d'ins�rer un noeud entre deux autres.
		 * \param data La valeur de type T
		 * \param prev Le noeud pr�c�dant (immuable)
		 * \param next La valeur suivant (immuable)
		 */
		node(const_value data, const_node_pointer prev, const_node_pointer next) : m_data(data), m_prev(prev), m_next(next)
		{

		}

		const_node_pointer	m_prev; /*!< Un pointeur immuable vers le noeud pr�c�dant. */
		const_node_pointer	m_next; /*!< Un pointeur immuable vers le noeud suivant. */
		const value_type	m_data; /*!< La valeur immuable du noeud repr�sent� par l'objet. */
	};

public:

	/**
	* \class _iterator
	*
	* \brief Classe d'it�rateur bidirectionnel
	* \tparam _isReverse D�termine le sens du d�placement
	* \tparam _isConst Propri�t� de modification des variables point�es
	*
	*/
	template<bool _isReverse, bool _isConst>
	struct _iterator;

	typedef _iterator<false, false> iterator;
	typedef _iterator<true, false>	reverse_iterator;

	typedef _iterator<false, true>	const_iterator;
	typedef _iterator<true, true>	const_reverse_iterator;

	//
	// IT�RATEUR BIDIRECTIONNEL MUABLE (sens naturel)
	//

	template<>
	struct _iterator<false, false>
	{
		typedef _iterator<false, false> _MyType;

		/**
		 * \brief Constructeur
		 *
		 * \param ptr Un pointeur vers un noeud. 
		 */
		_iterator(node_pointer ptr) : m_ptr(ptr)
		{

		}

		/**
		 * \brief Surcharge de l'op�rateur d'affectation.
		 *
		 * \param it un it�rateur list<T>.
		 * \return Un it�rateur.
		 */
		_MyType& operator=(const _MyType& it)
		{
			m_ptr = it.m_ptr;

			return *this;
		}

		/**
		 * \brief Surcharge de l'op�rateur d'�galit�.
		 *
		 * \param it un it�rateur list<T>.
		 * \return Vrai si l'it�rateur est �quivalent, sinon Faux.
		 */
		bool operator==(const _MyType& it) const
		{
			return m_ptr == it.m_ptr;
		}

		/**
		 * \brief Surcharge de l'op�rateur d'�galit�.
		 *
		 * \param it un it�rateur list<T>.
		 * \return Vrai si l'it�rateur est diff�rent, sinon Faux.
		 */
		bool operator!=(const _MyType& it) const
		{
			return m_ptr != it.m_ptr;
		}

		/**
		 * \brief Op�rateur de pr�-incr�mentation
		 * \return Une r�f�rence sur l'it�rateur.
		 */
		_MyType& operator++() // pre-increment
		{
			m_ptr = m_ptr->m_next;

			return *this;
		}

		/**
		 * \brief Op�rateur de post-incr�mentation
		 * \return Une copie de l'objet avant incr�mentation.
		 */
		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			it.m_ptr = it.m_ptr->m_next;

			return it;
		}

		/**
		 * \brief Op�rateur de pr�-d�cr�mentation
		 * \return Une r�f�rence sur l'it�rateur.
		 */
		_MyType& operator--() // pre-decrement
		{
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		/**
		 * \brief Op�rateur de post-d�cr�mentation
		 * \return Une copie de l'objet avant d�cr�mentation.
		 */
		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}

		/**
		 * \brief Retourne une r�f�rence de type T � la valeur contenue dans le noeud point� par l'it�rateur.
		 * \return Une r�f�rence de type T � la valeur contenue dans le noeud point� par l'it�rateur.
		 */
		value_type& operator*()
		{
			return m_ptr->m_data;
		}

		/**
		 * \brief  Retourne une r�f�rence immuable de type T � la valeur contenue dans le noeud point� par l'it�rateur.
		 * \return Une r�f�rence immuable de type T � la valeur contenue dans le noeud point� par l'it�rateur.
		 */
		const value_type& operator*() const
		{
			return m_ptr->m_data;
		}

	private:

		node_pointer m_ptr;  /*!< Pointeur vers un noeud */
		friend class class_value;
	};

	//
	// IT�RATEUR BIDIRECTIONNEL MUABLE (sens inverse)
	//

	template<>
	struct _iterator<true, false>
	{
		typedef _iterator<true, false> _MyType;

		_iterator(node_pointer ptr) : m_ptr(ptr)
		{

		}

		_MyType& operator=(const _MyType& it)
		{
			m_ptr = it.m_ptr;

			return *this;
		}

		bool operator==(const _MyType& it) const
		{
			return m_ptr == it.m_ptr;
		}

		bool operator!=(const _MyType& it) const
		{
			return m_ptr != it.m_ptr;
		}

		_MyType& operator++() // pre-increment
		{
			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le pr�c�dant.
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le pr�c�dant.
			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}


		_MyType& operator--() // pre-decrement
		{
			m_ptr = m_ptr->m_next;

			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le suivant.
			return *this;
		}

		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le suivant.
			it.m_ptr = it.m_ptr->m_next;

			return it;
		}

		value_type& operator*()
		{
			return m_ptr->m_data;
		}

		const value_type&  operator*() const
		{
			return m_ptr->m_data;
		}

	private:

		node_pointer m_ptr;
		friend class list<T>;
	};

	//
	// IT�RATEUR BIDIRECTIONNEL IMMUABLE (sens naturel)
	//

	template<>
	struct _iterator<false, true>
	{
		typedef _iterator<false, true> _MyType;

		_iterator(const_node_pointer ptr) : m_ptr(ptr)
		{

		}

		_MyType& operator=(const _MyType& it)
		{
			m_ptr = it.m_ptr;

			return *this;
		}

		bool operator==(const _MyType& it) const
		{
			return m_ptr == it.m_ptr;
		}

		bool operator!=(const _MyType& it) const
		{
			return m_ptr != it.m_ptr;
		}

		_MyType& operator++() // pre-increment
		{
			m_ptr = m_ptr->m_next;

			return *this;
		}

		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			it.m_ptr = it.m_ptr->m_next;

			return it;
		}


		_MyType& operator--() // pre-decrement
		{
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}

		const value_type& operator*() const
		{
			return m_ptr->m_data;
		}

	private:

		const_node_pointer m_ptr;
		friend class list<T>;
	};

	//
	// IT�RATEUR BIDIRECTIONNEL IMMUABLE (sens inverse)
	//

	template<>
	struct _iterator<true, true>
	{
		typedef _iterator<false, true> _MyType;

		_iterator(const_node_pointer ptr) : m_ptr(ptr)
		{

		}

		_MyType& operator=(const _MyType& it)
		{
			m_ptr = it.m_ptr;

			return *this;
		}

		bool operator==(const _MyType& it) const
		{
			return m_ptr == it.m_ptr;
		}

		bool operator!=(const _MyType& it) const
		{
			return m_ptr != it.m_ptr;
		}

		_MyType& operator++() // pre-increment
		{
			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le pr�c�dant.
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le pr�c�dant.
			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}


		_MyType& operator--() // pre-decrement
		{
			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le suivant.
			m_ptr = m_ptr->m_next;

			return *this;
		}

		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			// Comme il s'agit de la sp�cialisation de sens inverse,
			// il faut affecter le pointeur principal vers le suivant.
			it.m_ptr = it.m_ptr->m_next;

			return it;
		}

		const value_type& operator*() const
		{
			return m_ptr->m_data;
		}

	private:

		const_node_pointer m_ptr;
		friend class list<T>;
	};


public:

	list()
	{
		_constructor();
	}

	~list()
	{
		_destructor();
	}

	/**
	 * \brief Retourne un it�rateur au d�but de la liste.
	 * \return Un it�rateur au d�but de la liste.
	 */
	iterator begin()
	{
		return iterator(m_root->m_next);
	}

	/**
	 * \brief Retourne un it�rateur � la fin de la liste.
	 * \return Un it�rateur � la fin  de la liste.
	 */
	iterator end()
	{
		return iterator(m_tail);
	}

	/**
	 * \brief Retourne un it�rateur � rebours � la fin de la liste.
	 * \return Un it�rateur � rebours � la fin de la liste.
	 */
	reverse_iterator rbegin()
	{
		return reverse_iterator(m_tail->m_prev);
	}

	/**
	 * \brief Retourne un it�rateur � rebours au d�but de la liste.
	 * \return Un it�rateur � rebours au d�but de la liste.
	 */
	reverse_iterator rend()
	{
		return reverse_iterator(m_root);
	}

	/**
	 * \brief Retourne un it�rateur immuable au d�but de la liste.
	 * \return Un it�rateur immuable au d�but de la liste.
	 */
	const_iterator cbegin()
	{
		return const_iterator(m_root->m_next);
	}

	/**
	 * \brief Retourne un it�rateur immuable � la fin de la liste.
	 * \return Un it�rateur immuable � la fin  de la liste.
	 */
	const_iterator cend()
	{
		return const_iterator(m_tail);
	}

	/**
	 * \brief Retourne un it�rateur immuable � rebours � la fin de la liste.
	 * \return Un it�rateur immuable � rebours � la fin de la liste.
	 */
	const_reverse_iterator crbegin()
	{
		return const_reverse_iterator(m_tail->m_prev);
	}

	/**
	 * \brief Retourne un it�rateur immuable � rebours au d�but de la liste.
	 * \return Un it�rateur immuable � rebours au d�but de la liste.
	 */
	const_reverse_iterator crend()
	{
		return const_reverse_iterator(m_root);
	}

	/**
	 * \brief Retourne une r�f�rence � la valeur du premier noeud de la liste.
	 * \return Une r�f�rence � la valeur du premier noeud de la liste.
	 */
	reference front()
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_root->m_next->m_data;
	}

	/**
	 * \brief Retourne une r�f�rence constante � la valeur du premier noeud de la liste.
	 * \return Une r�f�rence constante � la valeur du premier noeud de la liste.
	 */
	const_reference front() const
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_root->m_next->m_data;
	}

	/**
	 * \brief Retourne une r�f�rence � la valeur du dernier noeud de la liste.
	 * \return Une r�f�rence � la valeur du dernier noeud de la liste.
	 */
	reference back()
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_tail->m_prev->m_data;
	}

	/**
	 * \brief Retourne une r�f�rence constante � la valeur du dernier noeud de la liste.
	 * \return Une r�f�rence constante � la valeur du dernier noeud de la liste.
	 */
	const_reference back() const
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_tail->m_prev->m_data;
	}


	/**
	 * \brief V�rifie si la liste est contient des noeuds.
	 * \return Vrai si la liste contient au moins un noeud.
	 * \return Faux si la liste ne contient aucun noeud.
	 */
	bool empty() const
	{
		return N <= 0;
	}
	/**
	 * \brief Retourne la longeur de la liste.
	 * \return La longeur de la liste.
	 */
	size_type size() const
	{
		return m_length;
	}

	/**
	 * \brief Permet de supprimer tous les noeuds de la liste.
	 */
	void clear()
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		_clear(m_root->m_next, m_tail);

		// Remise des pointeurs de d�but et de fin de liste.
		m_root->m_next = m_tail;
		m_tail->m_prev = m_root;

		// Remise � z�ro de la longeur de la liste.
		m_length = 0;
	}

	/**
	 * \brief Permet d'ajouter un noeud � la fin de la liste.
	 *
	 * \param data La valeur � affecter � l'emplacement du noeud.
	 */
	void push_back(const value_type data)
	{
		node_pointer n			= new node_value;

		// Affectation de la valeur au noeud allou�.
		n->m_data				= data;

		// Affectation du suivant du noeud allou� au noeud de fin de liste.
		n->m_next				= m_tail;

		// Affectation du pr�c�dant du noeud allou� au dernier noeud.
		n->m_prev				= m_tail->m_prev;

		// Affectation du suivant du dernier noeud au noeud allou�.
		m_tail->m_prev->m_next	= n;

		// Affectation du pr�c�dant du noeud de fin de liste au noeud allou�.
		m_tail->m_prev			= n;

		// Incr�mentation unitaire de la longeur de la liste.
		m_length++;
	}

	/**
	 * \brief Permet d'ajouter un noeud au d�but de la liste.
	 *
	 * \param data La valeur � affecter � l'emplacement du noeud.
	 */
	void push_front(const value_type data)
	{
		node_pointer n			= new node_value;

		// Affectation de la valeur au noeud allou�.
		n->m_data				= data;

		// Affectation du suivant du noeud allou� au premier noeud.
		n->m_next				= m_root->m_next;

		// Affectation du pr�c�dant du noeud allou� au noeud racine.
		n->m_prev				= m_root;

		// Affectation du pr�c�dant du premier noeud au noeud allou�.
		m_root->m_next->m_prev	= n;

		// Affectation du suivant du noeud racine au noeud allou�.
		m_root->m_next			= n;

		// Incr�mentation unitaire de la longeur de la liste.
		m_length++;
	}

	/**
	 * \brief Permet de retirer le noeud situ� � la fin de la liste.
	 */
	void pop_back()
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		// Suppression du dernier �l�ment de la liste.
		node_pointer n = m_tail->m_prev;
		if (n && n->m_prev)
		{
			// Affectation du suivant de l'avant-dernier objet au noeud de fin de liste.
			n->m_prev->m_next = m_tail;

			// Affectation du pr�c�dant du noeud de fin de liste � l'avant-dernier.
			m_tail->m_prev = n->m_prev;

			// D�allocation de la m�moire et suppression du dernier noeud.
			delete n;
			n = NULL;

			// D�cr�mentation unitaire de la longeur de la liste.
			m_length--;
		}
	}

	/**
	 * \brief Permet de retirer le noeud situ� au d�but de la liste.
	 */
	void pop_front()
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		// Suppression du premier �l�ment de la liste.
		// Affection des pointeurs de d�but au second noeud.
		node_pointer n = m_root->m_next;
		if (n && n->m_next)
		{
			// Affectation du pr�c�dant du second noeud � au noeud racine.
			n->m_next->m_prev = m_root;

			// Affectation du suivant de la racine au second noeud.
			m_root->m_next = n->m_next;

			// D�allocation de la m�moire et suppression du premier noeud.
			delete n;
			n = NULL;

			// D�cr�mentation unitaire de la longeur de la liste.
			m_length--;
		}

	}

	/**
	 * \brief Permet d'ins�rer un noeud entre deux autres.
	 *
	 * \param prev le noeud pr�c�dant le noeud d'insertion.
	 * \param current le noeud succ�dant le noeud d'insertion.
	 * \param data La valeur du noeud d'insertion.
	 *
	 * \return Un it�rateur � la position du noeud d'insertion.
	 */
	iterator insert(iterator& prev, iterator& current, const_reference data)
	{
		node_pointer n = new node_value;

		if (n)
		{
			n->m_data = data;

			// Affectation du suivant du noeud allou� au noeud pr�sent.
			n->m_next = current.m_ptr;

			// Affectation du pr�c�dant du noeud allou� au noeud pr�c�dant.
			n->m_prev = prev.m_ptr;

			// Affectation du suivant du noeud pr�c�dant au noeud allou�.
			prev.m_ptr->m_next = n;

			// Affectation du pr�c�dant du noeud pr�sent au noeud allou�.
			current.m_ptr->m_prev = n;

			// Incr�mentation unitaire de la longeur de la liste.
			m_length++;

			return iterator(n);
		}

		return  NULL;
	}

	/**
	 * \brief Permet d'ins�rer un noeud apr�s une position sp�cifi�e.
	 *
	 * \param pos le noeud pr�c�dant le noeud d'insertion.
	 * \param data La valeur du noeud d'insertion.
	 *
	 * \return Un it�rateur � la position du noeud d'insertion.
	 */
	iterator insert_after(iterator& pos, const_value data)
	{
		node_pointer n = new node_value;

		if (n)
		{
			n->m_data = data;

			// Affectation du suivant du noeud allou� au suivant du noeud pr�sent.
			n->m_next = pos.m_ptr->m_next;

			// Affectation du pr�c�dant du noeud allou� au noeud pr�sent.
			n->m_prev = pos.m_ptr;

			// Affectation du suivant du noeud pr�sent au noeud allou�.
			pos.m_ptr->m_next = n;

			// Incr�mentation unitaire de la longeur de la liste.
			m_length++;

			return iterator(n);
		}

		return NULL;
	}

	/**
	 * \brief Permet de retirer tous les noeuds poss�dants une valeur sp�cifi�e.
	 *
	 * \param data La valeur de suppression. (pr�dicat)
	 */
	void remove(const_value data)
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		// Garde un suivit du nombre de noeuds supprim�s afin de
		// soustraire de la longeur de la liste.
		size_type nombreElemRetires = 0;

		_remove(m_root->m_next, m_tail, data, &nombreElemRetires);

		// D�cr�mentation de la longeur de la liste. par le nombre de noeuds supprim�s.
		m_length -= nombreElemRetires;
	}

	/**
	 * \brief Permet de retirer tous les noeuds de la liste apr�s la position sp�cifi�e.
	 *
	 * \param pos La position de d�part de la supression (non suprim�e)
	 */
	void remove_after(iterator& pos)
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			throw std::out_of_range("m_length <= 0");
		}

		// V�rification si la position n'est pas celle de racine ou celle de fin de liste.
		if (pos == m_root || pos == m_tail)
			throw std::invalid_argument("pos != m_root && pos != m_tail");

		// Garde un suivit du nombre de noeuds supprim�s afin de
		// soustraire de la longeur de la liste.
		size_type nombreElemRetires = 0;

		_remove_after(pos.m_ptr->m_next, m_tail, &nombreElemRetires);

		// D�cr�mentation de la longeur de la liste. par le nombre de noeuds supprim�s.
		m_length -= nombreElemRetires;
	}

	/**
	 * \brief Permet de retirer tous les noeuds de la liste avant la position sp�cifi�e.
	 *
	 * \param pos La position de d�part de la supression (non suprim�e)
	 */
	void remove_before(iterator& pos)
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			throw std::out_of_range("m_length <= 0");
		}

		// V�rification si la position n'est pas celle de racine ou celle de fin de liste.
		if (pos == m_root || pos == m_tail)
			throw std::invalid_argument("pos != m_root && pos != m_tail");

		// Garde un suivit du nombre de noeuds supprim�s afin de
		// soustraire de la longeur de la liste.
		size_type nombreElemRetires = 0;

		_remove_after(m_root->m_next, pos.m_ptr, &nombreElemRetires);

		// D�cr�mentation de la longeur de la liste. par le nombre de noeuds supprim�s.
		m_length -= nombreElemRetires;
	}

	/**
	 * \brief Permet de supprimer le noeud � la position sp�cifi�e.
	 *
	 * \param pos La position de suppression.
	 *
	 * \return Un it�rateur � la position du prochain noeud.
	 */
	iterator erase(iterator& pos)
	{
		// V�rification si la liste contient au moins un �l�ment.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return NULL;
		}

		// V�rification si la position n'est pas celle de racine ou celle de fin de liste.
		if (pos == m_root || pos == m_tail)
			throw std::invalid_argument("pos != m_root && pos != m_tail");

		// D�finition d'un pointeur vers le noeud succ�dant la position sp�cifi�e.
		node_pointer next = pos.m_ptr->m_next;

		// Affectation du suivant du noeud pr�c�dant de la position sp�cifi�e
		// � celui succ�dant la position sp�cifi�e.
		pos.m_ptr->m_prev->m_next = next;

		// D�allocation de la m�moire et suppression du noeud � la position sp�cifi�e.
		delete pos.m_ptr;
		pos.m_ptr = NULL;

		// D�cr�mentation unitaire de la longeur de la liste.
		m_length--;

		return iterator(next);
	}

	/**
	 * \brief Permet d'�changer les valeurs de deux listes de m�me longeur.
	 *
	 * \param l Une liste cible avec laquelle �changer les valeurs de chaque noeud.
	 */
	void swap(class_reference l)
	{
		// V�rification � savoir si les deux listes ont la m�me longeur.
		if (m_length != l.m_length)
			throw std::out_of_range("m_length <> l.m_length");

		_swap(m_root->m_next, 
			  m_tail, 
			  l.m_root->m_next, 
			  l.m_tail);
	}

	/**
	 * \brief Permet de changer la longueur absolue de la liste.
	 *
	 * \param count La longueur absolue de la liste apr�s redimension. (non additionn�e).
	 */
	void resize(const size_type count)
	{
		// La longeur se doit d'�tre diff�rente de celle actuelle.
		if (count != m_length)
		{
			// Si la longeur sp�cifi�e est plus grande que celle pr�sente,
			// Vrai: utilisation de _resize_greater.
			// Faux: utilisation de _resize_smaller.
			if (count > m_length)
				_resize_greater(m_tail->m_prev, m_tail, std::labs(count - m_length));
			else
				_resize_smaller(m_tail->m_prev, m_tail, std::labs((m_length - count)));

			// mise � jour de la longeur de la liste.
			m_length = count;
		}
	}

	/**
	* \brief Permet d'affecter une valeur � tous les noeuds de la liste.
	*
	* \param data La valeur d'affectation.
	*/
	void fill(const_reference data)
	{
		_fill(m_root->m_next, m_tail, data);
	}

private:

	//
	// M�thodes utilitaires.
	//

	void _constructor()
	{

		m_root = new node_value;
		m_tail = new node_value;
		m_root->m_data = m_tail->m_data = -1;

		// Affection du pr�c�dant de la racine � NULL.
		m_root->m_prev = NULL;

		// Affection du suivant de la racine au noeud de fin.
		m_root->m_next = m_tail;

		// Affection du pr�c�dant du noeud de fin � la racine.
		m_tail->m_prev = m_root;

		// Affection du suivant du noeud de fin � NULL.
		m_tail->m_next = NULL;

		m_length = 0;
	}

	void _destructor()
	{
		// D�allocation de la m�moire et suppression du noeud racine.
		delete m_root;
		m_root = NULL;

		// D�allocation de la m�moire et suppression du noeud de fin de liste.
		delete m_tail;
		m_tail = NULL;
	}


	void _clear(node_pointer start, node_pointer last)
	{
		node_pointer next = start->m_next;

		// D�allocation de la m�moire et suppression du noeud pr�sent.
		delete start;
		start = NULL;

		// Si le noeud suivant diff�re du noeud cible, continuation
		// par r�currence avec le prochain noeud.
		if (next != last)
			_clear(next, last);
	}

	void _swap(node_pointer s1, node_pointer e1, node_pointer s2, node_pointer e2)
	{
		value_type data;
		node_pointer n1 = s1->m_next,
					 n2	= s2->m_next;

		// �change des valeurs pour les noeuds sp�cifi�s par s1 et s2.
		data		= s1->m_data;
		s1->m_data	= s2->m_data;
		s2->m_data	= data;

		// Si les deux noeuds auquels correspond chaque liste diff�rent de leur
		// cible, continuation par r�currence, avec les les prochains noeuds
		// de chaque liste.
		if (n1 != e1 && n2 != e2)
			_swap(n1, e1, n2, e2);
	}

	void _remove(node_pointer current, node_pointer to, const_value data, size_type* nombreElemRetires)
	{
		node_pointer next = current->m_next;

		// V�rifie si la valeur du noeud pr�sent correspond � celle donn�e par le pr�dicat.
		if (current->m_data == data) 
		{
			// Affectation du pr�c�dant du noeud suivant au noeud pr�c�dant.
			next->m_prev = current->m_prev;

			// Affectation du suivant du noeud pr�c�dant au noeud suivant.
			current->m_prev->m_next = next;

			// D�allocation de la m�moire et suppression du noeud pr�sent.
			delete current;
			current = NULL;

			// Incr�mentation unitaire du nombre d'�l�ments retir�s (pointeur).
			(*nombreElemRetires)++;
		}

		// Si le prochain diff�re du noeud cible, continuation 
		// par r�currence avec le prochain noeud.
		if (next != to)
			_remove(next, to, data, nombreElemRetires);
	}

	void _remove_after(node_pointer current, node_pointer to, size_type* nombreElemRetires)
	{
		node_pointer next	= current->m_next;

		// Affectation du suivant du noeud pr�c�dant au noeud suivant.
		current->m_prev->m_next = next;

		// Affectation du pr�c�dant du noeud suivant au noeud pr�c�dant.
		next->m_prev = current->m_prev;

		// D�allocation de la m�moire et suppression du noeud pr�sent.
		delete current;
		current = NULL;

		// Incr�mentation unitaire du nombre d'�l�ments retir�s (pointeur).
		(*nombreElemRetires)++;

		// Si le prochain diff�re du noeud cible, continuation 
		// par r�currence avec le prochain noeud.
		if (next != to)
			_remove_after(next, to, nombreElemRetires);
	}

	void _resize_greater(node_pointer prev, node_pointer current, const size_type& count)
	{
		node_pointer n = new node_value;

		if (n)
		{
			n->m_data = 0;

			// Affectation du suivant du noeud allou� au noeud cible. 
			n->m_next = current;

			// Affectation du pr�c�dant du noeud allou� au noeud pr�c�dant. 
			n->m_prev = prev;

			// Affectation du suivant du noeud pr�c�dant au noeud allou�. 
			prev->m_next = n;

			// Affectation du pr�c�dant du noeud cible au noeud allou�. 
			current->m_prev = n;

			// Si le nombre d'�l�ments � ajouter > 0, continuation
			// par r�currence, en soustrayant 1 au nombre restant.
			if ((count - 1) > 0)
				_resize_greater(n, current, count - 1);
		}
	}

	void _resize_smaller(node_pointer current, node_pointer next, const size_type& count)
	{
		node_pointer prev = current->m_prev;
		if (prev)
		{
			// Affectation du suivant du noeud pr�c�dant au noeud cible. 
			prev->m_next = next;

			// Affectation du pr�c�dant du noeud cible au noeud pr�c�dant. 
			next->m_prev = prev;

			// D�allocation de la m�moire et suppression du noeud pr�sent.
			delete current;
			current = NULL;

			// Si le nombre d'�l�ments � retier > 0, continuation
			// par r�currence, en soustrayant 1 au nombre restant.
			if ((count - 1) > 0)
				_resize_smaller(prev, next, count - 1);
		}
	}

	void _fill(node_pointer current, node_pointer to, const_reference data)
	{
		current->m_data = data;

		// Si le noeud suivant est diff�rent du noeud cible, continuation
		// par r�currence.
		if (current->m_next != to)
			_fill(current->m_next,to, data);
	}


private:
	
	node_pointer	m_root; /*!< Le noeud repr�sentant la t�te de la liste. */
	node_pointer	m_tail; /*!< Le noeud repr�sentant la fin de la liste. */
	size_type		m_length;  /*!< La longeur de la liste. */
};



}
}


#endif // LIST_HPP__