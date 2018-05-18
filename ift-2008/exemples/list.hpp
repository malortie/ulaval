/**
* \file list.hpp
* \brief Une liste doublement chaînée
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
 * \brief Classe de liste doublement chaînée.
 * \tparam T Le type de donnée
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
	 * \brief Classe représentant un noeud.
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
		 * \brief Constructeur permetant d'insérer un noeud entre deux autres.
		 * \param data La valeur de type T
		 * \param prev Le noeud précédant 
		 * \param next La valeur suivant
		 */
		node(const_value data, node_pointer prev, node_pointer next) : m_data(data), m_prev(prev), m_next(next)
		{

		}
	
		node_pointer m_prev; /*!< Un pointeur vers le noeud précédant. */
		node_pointer m_next; /*!< Un pointeur vers le noeud suivant. */
		value_type	 m_data; /*!< La valeur du noeud représenté par l'objet. */
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
		 * \brief Constructeur permetant d'insérer un noeud entre deux autres.
		 * \param data La valeur de type T
		 * \param prev Le noeud précédant (immuable)
		 * \param next La valeur suivant (immuable)
		 */
		node(const_value data, const_node_pointer prev, const_node_pointer next) : m_data(data), m_prev(prev), m_next(next)
		{

		}

		const_node_pointer	m_prev; /*!< Un pointeur immuable vers le noeud précédant. */
		const_node_pointer	m_next; /*!< Un pointeur immuable vers le noeud suivant. */
		const value_type	m_data; /*!< La valeur immuable du noeud représenté par l'objet. */
	};

public:

	/**
	* \class _iterator
	*
	* \brief Classe d'itérateur bidirectionnel
	* \tparam _isReverse Détermine le sens du déplacement
	* \tparam _isConst Propriété de modification des variables pointées
	*
	*/
	template<bool _isReverse, bool _isConst>
	struct _iterator;

	typedef _iterator<false, false> iterator;
	typedef _iterator<true, false>	reverse_iterator;

	typedef _iterator<false, true>	const_iterator;
	typedef _iterator<true, true>	const_reverse_iterator;

	//
	// ITÉRATEUR BIDIRECTIONNEL MUABLE (sens naturel)
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
		 * \brief Surcharge de l'opérateur d'affectation.
		 *
		 * \param it un itérateur list<T>.
		 * \return Un itérateur.
		 */
		_MyType& operator=(const _MyType& it)
		{
			m_ptr = it.m_ptr;

			return *this;
		}

		/**
		 * \brief Surcharge de l'opérateur d'égalité.
		 *
		 * \param it un itérateur list<T>.
		 * \return Vrai si l'itérateur est équivalent, sinon Faux.
		 */
		bool operator==(const _MyType& it) const
		{
			return m_ptr == it.m_ptr;
		}

		/**
		 * \brief Surcharge de l'opérateur d'égalité.
		 *
		 * \param it un itérateur list<T>.
		 * \return Vrai si l'itérateur est différent, sinon Faux.
		 */
		bool operator!=(const _MyType& it) const
		{
			return m_ptr != it.m_ptr;
		}

		/**
		 * \brief Opérateur de pré-incrémentation
		 * \return Une référence sur l'itérateur.
		 */
		_MyType& operator++() // pre-increment
		{
			m_ptr = m_ptr->m_next;

			return *this;
		}

		/**
		 * \brief Opérateur de post-incrémentation
		 * \return Une copie de l'objet avant incrémentation.
		 */
		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			it.m_ptr = it.m_ptr->m_next;

			return it;
		}

		/**
		 * \brief Opérateur de pré-décrémentation
		 * \return Une référence sur l'itérateur.
		 */
		_MyType& operator--() // pre-decrement
		{
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		/**
		 * \brief Opérateur de post-décrémentation
		 * \return Une copie de l'objet avant décrémentation.
		 */
		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}

		/**
		 * \brief Retourne une référence de type T à la valeur contenue dans le noeud pointé par l'itérateur.
		 * \return Une référence de type T à la valeur contenue dans le noeud pointé par l'itérateur.
		 */
		value_type& operator*()
		{
			return m_ptr->m_data;
		}

		/**
		 * \brief  Retourne une référence immuable de type T à la valeur contenue dans le noeud pointé par l'itérateur.
		 * \return Une référence immuable de type T à la valeur contenue dans le noeud pointé par l'itérateur.
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
	// ITÉRATEUR BIDIRECTIONNEL MUABLE (sens inverse)
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
			// Comme il s'agit de la spécialisation de sens inverse,
			// il faut affecter le pointeur principal vers le précédant.
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			// Comme il s'agit de la spécialisation de sens inverse,
			// il faut affecter le pointeur principal vers le précédant.
			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}


		_MyType& operator--() // pre-decrement
		{
			m_ptr = m_ptr->m_next;

			// Comme il s'agit de la spécialisation de sens inverse,
			// il faut affecter le pointeur principal vers le suivant.
			return *this;
		}

		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			// Comme il s'agit de la spécialisation de sens inverse,
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
	// ITÉRATEUR BIDIRECTIONNEL IMMUABLE (sens naturel)
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
	// ITÉRATEUR BIDIRECTIONNEL IMMUABLE (sens inverse)
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
			// Comme il s'agit de la spécialisation de sens inverse,
			// il faut affecter le pointeur principal vers le précédant.
			m_ptr = m_ptr->m_prev;

			return *this;
		}

		_MyType operator++(int) // post-increment
		{
			_MyType it = *this;

			// Comme il s'agit de la spécialisation de sens inverse,
			// il faut affecter le pointeur principal vers le précédant.
			it.m_ptr = it.m_ptr->m_prev;

			return it;
		}


		_MyType& operator--() // pre-decrement
		{
			// Comme il s'agit de la spécialisation de sens inverse,
			// il faut affecter le pointeur principal vers le suivant.
			m_ptr = m_ptr->m_next;

			return *this;
		}

		_MyType operator--(int) // post-decrement
		{
			_MyType it = *this;

			// Comme il s'agit de la spécialisation de sens inverse,
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
	 * \brief Retourne un itérateur au début de la liste.
	 * \return Un itérateur au début de la liste.
	 */
	iterator begin()
	{
		return iterator(m_root->m_next);
	}

	/**
	 * \brief Retourne un itérateur à la fin de la liste.
	 * \return Un itérateur à la fin  de la liste.
	 */
	iterator end()
	{
		return iterator(m_tail);
	}

	/**
	 * \brief Retourne un itérateur à rebours à la fin de la liste.
	 * \return Un itérateur à rebours à la fin de la liste.
	 */
	reverse_iterator rbegin()
	{
		return reverse_iterator(m_tail->m_prev);
	}

	/**
	 * \brief Retourne un itérateur à rebours au début de la liste.
	 * \return Un itérateur à rebours au début de la liste.
	 */
	reverse_iterator rend()
	{
		return reverse_iterator(m_root);
	}

	/**
	 * \brief Retourne un itérateur immuable au début de la liste.
	 * \return Un itérateur immuable au début de la liste.
	 */
	const_iterator cbegin()
	{
		return const_iterator(m_root->m_next);
	}

	/**
	 * \brief Retourne un itérateur immuable à la fin de la liste.
	 * \return Un itérateur immuable à la fin  de la liste.
	 */
	const_iterator cend()
	{
		return const_iterator(m_tail);
	}

	/**
	 * \brief Retourne un itérateur immuable à rebours à la fin de la liste.
	 * \return Un itérateur immuable à rebours à la fin de la liste.
	 */
	const_reverse_iterator crbegin()
	{
		return const_reverse_iterator(m_tail->m_prev);
	}

	/**
	 * \brief Retourne un itérateur immuable à rebours au début de la liste.
	 * \return Un itérateur immuable à rebours au début de la liste.
	 */
	const_reverse_iterator crend()
	{
		return const_reverse_iterator(m_root);
	}

	/**
	 * \brief Retourne une référence à la valeur du premier noeud de la liste.
	 * \return Une référence à la valeur du premier noeud de la liste.
	 */
	reference front()
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_root->m_next->m_data;
	}

	/**
	 * \brief Retourne une référence constante à la valeur du premier noeud de la liste.
	 * \return Une référence constante à la valeur du premier noeud de la liste.
	 */
	const_reference front() const
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_root->m_next->m_data;
	}

	/**
	 * \brief Retourne une référence à la valeur du dernier noeud de la liste.
	 * \return Une référence à la valeur du dernier noeud de la liste.
	 */
	reference back()
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_tail->m_prev->m_data;
	}

	/**
	 * \brief Retourne une référence constante à la valeur du dernier noeud de la liste.
	 * \return Une référence constante à la valeur du dernier noeud de la liste.
	 */
	const_reference back() const
	{
		if (m_length <= 0) throw std::out_of_range("m_length <= 0");

		return m_tail->m_prev->m_data;
	}


	/**
	 * \brief Vérifie si la liste est contient des noeuds.
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
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		_clear(m_root->m_next, m_tail);

		// Remise des pointeurs de début et de fin de liste.
		m_root->m_next = m_tail;
		m_tail->m_prev = m_root;

		// Remise à zéro de la longeur de la liste.
		m_length = 0;
	}

	/**
	 * \brief Permet d'ajouter un noeud à la fin de la liste.
	 *
	 * \param data La valeur à affecter à l'emplacement du noeud.
	 */
	void push_back(const value_type data)
	{
		node_pointer n			= new node_value;

		// Affectation de la valeur au noeud alloué.
		n->m_data				= data;

		// Affectation du suivant du noeud alloué au noeud de fin de liste.
		n->m_next				= m_tail;

		// Affectation du précédant du noeud alloué au dernier noeud.
		n->m_prev				= m_tail->m_prev;

		// Affectation du suivant du dernier noeud au noeud alloué.
		m_tail->m_prev->m_next	= n;

		// Affectation du précédant du noeud de fin de liste au noeud alloué.
		m_tail->m_prev			= n;

		// Incrémentation unitaire de la longeur de la liste.
		m_length++;
	}

	/**
	 * \brief Permet d'ajouter un noeud au début de la liste.
	 *
	 * \param data La valeur à affecter à l'emplacement du noeud.
	 */
	void push_front(const value_type data)
	{
		node_pointer n			= new node_value;

		// Affectation de la valeur au noeud alloué.
		n->m_data				= data;

		// Affectation du suivant du noeud alloué au premier noeud.
		n->m_next				= m_root->m_next;

		// Affectation du précédant du noeud alloué au noeud racine.
		n->m_prev				= m_root;

		// Affectation du précédant du premier noeud au noeud alloué.
		m_root->m_next->m_prev	= n;

		// Affectation du suivant du noeud racine au noeud alloué.
		m_root->m_next			= n;

		// Incrémentation unitaire de la longeur de la liste.
		m_length++;
	}

	/**
	 * \brief Permet de retirer le noeud situé à la fin de la liste.
	 */
	void pop_back()
	{
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		// Suppression du dernier élément de la liste.
		node_pointer n = m_tail->m_prev;
		if (n && n->m_prev)
		{
			// Affectation du suivant de l'avant-dernier objet au noeud de fin de liste.
			n->m_prev->m_next = m_tail;

			// Affectation du précédant du noeud de fin de liste à l'avant-dernier.
			m_tail->m_prev = n->m_prev;

			// Déallocation de la mémoire et suppression du dernier noeud.
			delete n;
			n = NULL;

			// Décrémentation unitaire de la longeur de la liste.
			m_length--;
		}
	}

	/**
	 * \brief Permet de retirer le noeud situé au début de la liste.
	 */
	void pop_front()
	{
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		// Suppression du premier élément de la liste.
		// Affection des pointeurs de début au second noeud.
		node_pointer n = m_root->m_next;
		if (n && n->m_next)
		{
			// Affectation du précédant du second noeud à au noeud racine.
			n->m_next->m_prev = m_root;

			// Affectation du suivant de la racine au second noeud.
			m_root->m_next = n->m_next;

			// Déallocation de la mémoire et suppression du premier noeud.
			delete n;
			n = NULL;

			// Décrémentation unitaire de la longeur de la liste.
			m_length--;
		}

	}

	/**
	 * \brief Permet d'insérer un noeud entre deux autres.
	 *
	 * \param prev le noeud précédant le noeud d'insertion.
	 * \param current le noeud succédant le noeud d'insertion.
	 * \param data La valeur du noeud d'insertion.
	 *
	 * \return Un itérateur à la position du noeud d'insertion.
	 */
	iterator insert(iterator& prev, iterator& current, const_reference data)
	{
		node_pointer n = new node_value;

		if (n)
		{
			n->m_data = data;

			// Affectation du suivant du noeud alloué au noeud présent.
			n->m_next = current.m_ptr;

			// Affectation du précédant du noeud alloué au noeud précédant.
			n->m_prev = prev.m_ptr;

			// Affectation du suivant du noeud précédant au noeud alloué.
			prev.m_ptr->m_next = n;

			// Affectation du précédant du noeud présent au noeud alloué.
			current.m_ptr->m_prev = n;

			// Incrémentation unitaire de la longeur de la liste.
			m_length++;

			return iterator(n);
		}

		return  NULL;
	}

	/**
	 * \brief Permet d'insérer un noeud après une position spécifiée.
	 *
	 * \param pos le noeud précédant le noeud d'insertion.
	 * \param data La valeur du noeud d'insertion.
	 *
	 * \return Un itérateur à la position du noeud d'insertion.
	 */
	iterator insert_after(iterator& pos, const_value data)
	{
		node_pointer n = new node_value;

		if (n)
		{
			n->m_data = data;

			// Affectation du suivant du noeud alloué au suivant du noeud présent.
			n->m_next = pos.m_ptr->m_next;

			// Affectation du précédant du noeud alloué au noeud présent.
			n->m_prev = pos.m_ptr;

			// Affectation du suivant du noeud présent au noeud alloué.
			pos.m_ptr->m_next = n;

			// Incrémentation unitaire de la longeur de la liste.
			m_length++;

			return iterator(n);
		}

		return NULL;
	}

	/**
	 * \brief Permet de retirer tous les noeuds possédants une valeur spécifiée.
	 *
	 * \param data La valeur de suppression. (prédicat)
	 */
	void remove(const_value data)
	{
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return;
		}

		// Garde un suivit du nombre de noeuds supprimés afin de
		// soustraire de la longeur de la liste.
		size_type nombreElemRetires = 0;

		_remove(m_root->m_next, m_tail, data, &nombreElemRetires);

		// Décrémentation de la longeur de la liste. par le nombre de noeuds supprimés.
		m_length -= nombreElemRetires;
	}

	/**
	 * \brief Permet de retirer tous les noeuds de la liste après la position spécifiée.
	 *
	 * \param pos La position de départ de la supression (non suprimée)
	 */
	void remove_after(iterator& pos)
	{
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			throw std::out_of_range("m_length <= 0");
		}

		// Vérification si la position n'est pas celle de racine ou celle de fin de liste.
		if (pos == m_root || pos == m_tail)
			throw std::invalid_argument("pos != m_root && pos != m_tail");

		// Garde un suivit du nombre de noeuds supprimés afin de
		// soustraire de la longeur de la liste.
		size_type nombreElemRetires = 0;

		_remove_after(pos.m_ptr->m_next, m_tail, &nombreElemRetires);

		// Décrémentation de la longeur de la liste. par le nombre de noeuds supprimés.
		m_length -= nombreElemRetires;
	}

	/**
	 * \brief Permet de retirer tous les noeuds de la liste avant la position spécifiée.
	 *
	 * \param pos La position de départ de la supression (non suprimée)
	 */
	void remove_before(iterator& pos)
	{
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			throw std::out_of_range("m_length <= 0");
		}

		// Vérification si la position n'est pas celle de racine ou celle de fin de liste.
		if (pos == m_root || pos == m_tail)
			throw std::invalid_argument("pos != m_root && pos != m_tail");

		// Garde un suivit du nombre de noeuds supprimés afin de
		// soustraire de la longeur de la liste.
		size_type nombreElemRetires = 0;

		_remove_after(m_root->m_next, pos.m_ptr, &nombreElemRetires);

		// Décrémentation de la longeur de la liste. par le nombre de noeuds supprimés.
		m_length -= nombreElemRetires;
	}

	/**
	 * \brief Permet de supprimer le noeud à la position spécifiée.
	 *
	 * \param pos La position de suppression.
	 *
	 * \return Un itérateur à la position du prochain noeud.
	 */
	iterator erase(iterator& pos)
	{
		// Vérification si la liste contient au moins un élément.
		if (m_length <= 0 &&
			m_root->m_next == m_tail &&
			m_tail->m_prev == m_root)
		{
			return NULL;
		}

		// Vérification si la position n'est pas celle de racine ou celle de fin de liste.
		if (pos == m_root || pos == m_tail)
			throw std::invalid_argument("pos != m_root && pos != m_tail");

		// Définition d'un pointeur vers le noeud succédant la position spécifiée.
		node_pointer next = pos.m_ptr->m_next;

		// Affectation du suivant du noeud précédant de la position spécifiée
		// à celui succédant la position spécifiée.
		pos.m_ptr->m_prev->m_next = next;

		// Déallocation de la mémoire et suppression du noeud à la position spécifiée.
		delete pos.m_ptr;
		pos.m_ptr = NULL;

		// Décrémentation unitaire de la longeur de la liste.
		m_length--;

		return iterator(next);
	}

	/**
	 * \brief Permet d'échanger les valeurs de deux listes de même longeur.
	 *
	 * \param l Une liste cible avec laquelle échanger les valeurs de chaque noeud.
	 */
	void swap(class_reference l)
	{
		// Vérification à savoir si les deux listes ont la même longeur.
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
	 * \param count La longueur absolue de la liste après redimension. (non additionnée).
	 */
	void resize(const size_type count)
	{
		// La longeur se doit d'être différente de celle actuelle.
		if (count != m_length)
		{
			// Si la longeur spécifiée est plus grande que celle présente,
			// Vrai: utilisation de _resize_greater.
			// Faux: utilisation de _resize_smaller.
			if (count > m_length)
				_resize_greater(m_tail->m_prev, m_tail, std::labs(count - m_length));
			else
				_resize_smaller(m_tail->m_prev, m_tail, std::labs((m_length - count)));

			// mise à jour de la longeur de la liste.
			m_length = count;
		}
	}

	/**
	* \brief Permet d'affecter une valeur à tous les noeuds de la liste.
	*
	* \param data La valeur d'affectation.
	*/
	void fill(const_reference data)
	{
		_fill(m_root->m_next, m_tail, data);
	}

private:

	//
	// Méthodes utilitaires.
	//

	void _constructor()
	{

		m_root = new node_value;
		m_tail = new node_value;
		m_root->m_data = m_tail->m_data = -1;

		// Affection du précédant de la racine à NULL.
		m_root->m_prev = NULL;

		// Affection du suivant de la racine au noeud de fin.
		m_root->m_next = m_tail;

		// Affection du précédant du noeud de fin à la racine.
		m_tail->m_prev = m_root;

		// Affection du suivant du noeud de fin à NULL.
		m_tail->m_next = NULL;

		m_length = 0;
	}

	void _destructor()
	{
		// Déallocation de la mémoire et suppression du noeud racine.
		delete m_root;
		m_root = NULL;

		// Déallocation de la mémoire et suppression du noeud de fin de liste.
		delete m_tail;
		m_tail = NULL;
	}


	void _clear(node_pointer start, node_pointer last)
	{
		node_pointer next = start->m_next;

		// Déallocation de la mémoire et suppression du noeud présent.
		delete start;
		start = NULL;

		// Si le noeud suivant diffère du noeud cible, continuation
		// par récurrence avec le prochain noeud.
		if (next != last)
			_clear(next, last);
	}

	void _swap(node_pointer s1, node_pointer e1, node_pointer s2, node_pointer e2)
	{
		value_type data;
		node_pointer n1 = s1->m_next,
					 n2	= s2->m_next;

		// Échange des valeurs pour les noeuds spécifiés par s1 et s2.
		data		= s1->m_data;
		s1->m_data	= s2->m_data;
		s2->m_data	= data;

		// Si les deux noeuds auquels correspond chaque liste diffèrent de leur
		// cible, continuation par récurrence, avec les les prochains noeuds
		// de chaque liste.
		if (n1 != e1 && n2 != e2)
			_swap(n1, e1, n2, e2);
	}

	void _remove(node_pointer current, node_pointer to, const_value data, size_type* nombreElemRetires)
	{
		node_pointer next = current->m_next;

		// Vérifie si la valeur du noeud présent correspond à celle donnée par le prédicat.
		if (current->m_data == data) 
		{
			// Affectation du précédant du noeud suivant au noeud précédant.
			next->m_prev = current->m_prev;

			// Affectation du suivant du noeud précédant au noeud suivant.
			current->m_prev->m_next = next;

			// Déallocation de la mémoire et suppression du noeud présent.
			delete current;
			current = NULL;

			// Incrémentation unitaire du nombre d'éléments retirés (pointeur).
			(*nombreElemRetires)++;
		}

		// Si le prochain diffère du noeud cible, continuation 
		// par récurrence avec le prochain noeud.
		if (next != to)
			_remove(next, to, data, nombreElemRetires);
	}

	void _remove_after(node_pointer current, node_pointer to, size_type* nombreElemRetires)
	{
		node_pointer next	= current->m_next;

		// Affectation du suivant du noeud précédant au noeud suivant.
		current->m_prev->m_next = next;

		// Affectation du précédant du noeud suivant au noeud précédant.
		next->m_prev = current->m_prev;

		// Déallocation de la mémoire et suppression du noeud présent.
		delete current;
		current = NULL;

		// Incrémentation unitaire du nombre d'éléments retirés (pointeur).
		(*nombreElemRetires)++;

		// Si le prochain diffère du noeud cible, continuation 
		// par récurrence avec le prochain noeud.
		if (next != to)
			_remove_after(next, to, nombreElemRetires);
	}

	void _resize_greater(node_pointer prev, node_pointer current, const size_type& count)
	{
		node_pointer n = new node_value;

		if (n)
		{
			n->m_data = 0;

			// Affectation du suivant du noeud alloué au noeud cible. 
			n->m_next = current;

			// Affectation du précédant du noeud alloué au noeud précédant. 
			n->m_prev = prev;

			// Affectation du suivant du noeud précédant au noeud alloué. 
			prev->m_next = n;

			// Affectation du précédant du noeud cible au noeud alloué. 
			current->m_prev = n;

			// Si le nombre d'éléments à ajouter > 0, continuation
			// par récurrence, en soustrayant 1 au nombre restant.
			if ((count - 1) > 0)
				_resize_greater(n, current, count - 1);
		}
	}

	void _resize_smaller(node_pointer current, node_pointer next, const size_type& count)
	{
		node_pointer prev = current->m_prev;
		if (prev)
		{
			// Affectation du suivant du noeud précédant au noeud cible. 
			prev->m_next = next;

			// Affectation du précédant du noeud cible au noeud précédant. 
			next->m_prev = prev;

			// Déallocation de la mémoire et suppression du noeud présent.
			delete current;
			current = NULL;

			// Si le nombre d'éléments à retier > 0, continuation
			// par récurrence, en soustrayant 1 au nombre restant.
			if ((count - 1) > 0)
				_resize_smaller(prev, next, count - 1);
		}
	}

	void _fill(node_pointer current, node_pointer to, const_reference data)
	{
		current->m_data = data;

		// Si le noeud suivant est différent du noeud cible, continuation
		// par récurrence.
		if (current->m_next != to)
			_fill(current->m_next,to, data);
	}


private:
	
	node_pointer	m_root; /*!< Le noeud représentant la tête de la liste. */
	node_pointer	m_tail; /*!< Le noeud représentant la fin de la liste. */
	size_type		m_length;  /*!< La longeur de la liste. */
};



}
}


#endif // LIST_HPP__