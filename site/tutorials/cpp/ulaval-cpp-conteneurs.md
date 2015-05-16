#Conteneurs


Cette section ne liste pas tous les [conteneurs](http://en.wikipedia.org/wiki/Container_%28abstract_data_type%29) présents dans la [librairie STL](http://en.wikipedia.org/wiki/Standard_Template_Library), mais seulement ceux qui sont fondamentaux.

---

* [Conteneurs de séquences](#conteneurs-de-s%C3%A9quences)
  * [array](#array)
  * [deque](#deque)
  * [list](#list)
  * [vector](#vector)
* [Conteneurs associatifs](#conteneurs-associatifs)
  * [map](#map)
  * [set](#set)
* [Adaptateurs de conteneurs](#adaptateurs-de-conteneurs)
  * [queue](#queue)
  * [stack](#stack)


##Conteneurs de séquences

###[array](http://en.cppreference.com/w/cpp/container/array)

Un tableau est un [conteneur](http://fr.wikipedia.org/wiki/Conteneur_(informatique)) de taille constante **_N_** ne pouvant être redimensionné après la [compilation](http://fr.wikipedia.org/wiki/Compilateur). Il s'agit d'une équivalence au [tableau C](http://en.wikipedia.org/wiki/C_syntax#Array_definition) définie de façon [générique](http://fr.wikipedia.org/wiki/G%C3%A9n%C3%A9ricit%C3%A9).

####Déclaration

```cpp
template< 
    class T, 
    std::size_t N 
> struct array;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_N_**| La [capacité](http://en.wikipedia.org/wiki/Capacity_of_a_set) du tableau. |


```cpp

#include <iostream>
#include <array>

int main() {
    std::array<int, 4> a;

    a.fill(0);    // {0, 0,  0, 0}

    a.at(2) = -8; // {0, 0, -8, 0}

    // Affectation de la valeur 2 au dernier indice de a.
    a.at(a.size() - 1) = 2;  // {0, 0, -8, 2}

    // N <= 0
    std::cout << std::boolalpha 
		  << a.empty() 
		  << std::endl;	 // false

    // N > 0
    std::cout << std::boolalpha
		   << !a.empty()
	           << std::endl; // true

    // Valeur à l'indice 0
	*a.begin();	   // 0

	// Affectation de la valeur 7 au premier indice de a.
	(*a.begin()) = 7; // {7, 0, -8, 2}

	/*	Inversion de 7 avec 2
		Syntaxe des pointeurs */
	*a.begin()	^= *a.end();    // {5, 0, -8, 2 }
	*a.end()	^= *a.begin();	// {5, 0, -8, 7 }
	*a.begin()	^= *a.end();	// {2, 0, -8, 7 }

	/*	Inversion de 7 avec 2
		Syntaxe utilisant l'opérateur [] */
	a.begin()[0] ^= a.end()[7];  // {5, 0, -8, 2}
	a.end()[0] ^= a.begin()[7];  // {5, 0, -8, 7}
	a.begin()[0] ^= a.end()[7];  // {2, 0, -8, 7}

    return 0;
}

```

###[deque](http://en.cppreference.com/w/cpp/container/deque)

Un [deque](http://en.cppreference.com/w/cpp/container/deque) est une une structure de données à insertion bidirectionelle. Le [deque](http://en.cppreference.com/w/cpp/container/deque) possède toutes les charactéristiques de la [queue](http://fr.wikipedia.org/wiki/File_%28structure_de_donn%C3%A9es%29), mais a également la propriété d'insérer des éléments au début de la [liste](http://fr.wikipedia.org/wiki/Liste_%28informatique%29). Il s'agit d'une [liste doublement chaînée](http://en.wikipedia.org/wiki/Double-ended_queue).

####Déclaration

```cpp
template<
    class T,
    class Allocator = std::allocator<T>
> class deque;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_Allocator_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  de [l'allocateur](http://fr.wikipedia.org/wiki/Allocateurs_(C%2B%2B)) |

####Exemple
```cpp

#include <iostream>
#include <deque>

int main() {
    std::deque<int> d;
    d.push_back(0);   // {0}
    d.push_back(1);   // {0 1}
    d.push_back(2);   // {0 1 2}

    d.push_front(-1); // {-1  0  1  2}
    d.push_front(-2); // {-2 -1  0  1  2}
    d.push_front(-3); // {-3 -2 -1  0  1  2}

    d.pop_back();     // {-3 -2 -1  0  1}
    d.pop_front();    // {-2 -1  0  1}
    d.pop_back();     // {-2 -1  0}

    d.pop_back();     // {-2 -1}

    d.pop_front();    // {-1}
    d.pop_front();    // {}

    return 0;
}

```

###[list](http://en.cppreference.com/w/cpp/container/list)

Une [list](http://en.cppreference.com/w/cpp/container/list) est une structure de données séquentielle à [sens unique](http://fr.wikipedia.org/wiki/Fonction_%C3%A0_sens_unique), contrairement au [vector](http://en.cppreference.com/w/cpp/container/vector), la [list](http://en.cppreference.com/w/cpp/container/list) ne peut accéder à un [élément précis](http://en.cppreference.com/w/cpp/container/vector/at). Pour trouver cet élément, elle doit le faire selon une recherche binaire. Une fois rendue à l'élément, il est impossible de reculer, elle doit donc continuer ou recommencer à partir du [début](http://en.cppreference.com/w/cpp/container/list/begin).

```cpp
template<
    class T,
    class Allocator = std::allocator<T>
> class list;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_Allocator_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  de [l'allocateur](http://fr.wikipedia.org/wiki/Allocateurs_(C%2B%2B)) |


####Exemple
```cpp

#include <iostream>
#include <list>

int main() {
    std::list<int> l; // {}

    l.push_back(0);   // {0}
    l.push_back(1);   // {0 1}
    l.push_back(2);   // {0 1 2}

    l.push_front(-1); // {-1  0  1  2}
    l.push_front(-2); // {-2 -1  0  1  2}
    l.push_front(-3); // {-3 -2 -1  0  1  2}

    l.pop_back();     // {-3 -2 -1  0  1}
    l.pop_front();    // {-2 -1  0  1}
    l.pop_back();     // {-2 -1  0}

    l.pop_back();     // {-2 -1}

    l.pop_front();    // {-1}
    l.pop_front();    // {}

    return 0;
}


```


###[vector](http://en.cppreference.com/w/cpp/container/vector)

Un [vector](http://en.cppreference.com/w/cpp/container/vector) est un type de conteneur dont la [capacité](http://en.wikipedia.org/wiki/Capacity_of_a_set) pouvant être modifiée au [temps d'exécution](http://fr.wikipedia.org/wiki/Environnement_d%27ex%C3%A9cution), contrairement au [tableau C](http://en.wikipedia.org/wiki/C_syntax#Array_definition) qui possède une taille fixe et prédéfinie.

####Déclaration

```cpp
template<
    class T,
    class Allocator = std::allocator<T>
> class vector;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_Allocator_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  de [l'allocateur](http://fr.wikipedia.org/wiki/Allocateurs_(C%2B%2B)) |


####Exemple

```cpp

#include <iostream>
#include <vector>

int main() {
    // Déclaration d'une pile d'entier.
    std::vector <int> v;   // {}

    // Ajout d'éléments à la fin de v.
    v.push_back(1);	    // {1}
    v.push_back(2);	    // {1 2}
    v.push_back(3);	    // {1 2 3}
    v.push_back(4);	    // {1 2 3 4}

    // Retrait d'éléments à la fin de v.
    v.pop_back();	    // {1 2 3}
    v.pop_back();	    // {1 2}

    // Ajout d'éléments à la fin de v.
    v.push_back(5);	    // {1 2 5}
    v.push_back(6);	    // {1 2 5 6}

    // Modification de l'élément à l'indice 2 de v.
    *(v.begin() + 2) = -5;  // {1 2 -5 6}

    // Suppression de tous les éléments de v.
    v.clear();		    // {}

    return 0;
}

```


---

##Conteneurs associatifs

###[map](http://en.cppreference.com/w/cpp/container/map)

Un [map](http://en.cppreference.com/w/cpp/container/map) constitue une [collection](http://en.wikipedia.org/wiki/Collection_(abstract_data_type)) de [clés uniques](http://fr.wikipedia.org/wiki/Cl%C3%A9_primaire) auxquelles sont associés une valeur. Voir [attributs-valeur](http://en.wikipedia.org/wiki/Attribute%E2%80%93value_pair) pour plus d'informations.


####Déclaration

```cpp
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
> class map;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_Key_**|Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de la clé.  |
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de l'élément associé.|
|**_Compare_**| Le [prédicat](http://en.wikipedia.org/wiki/Function_object)) de comparaison  |
|**_Container_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  du [conteneur](http://fr.wikipedia.org/wiki/Conteneur_(informatique)). |


####Exemple

```cpp
#include <iostream>
#include <map>

int main() {

    // Déclaration d'un dictionaire contenant des paires 
	// de type (const char* -> double)
	std::map<const char*, double> m;

	// Insertion d'une première paire
	// "e" -> 2.71828
	m.insert(std::pair<const char*, double>("e", 2.71828));  // { ("e", 2.71828) }

	// Il est possible d'utiliser std::make_pair pour ne
	// pas avoir à préciser le type des paires
	// soit  (const char* -> double)

	m.insert(std::make_pair("pi", 3.1415)); /* { ("e", 2.71828),  "e" -> 2.71828
						     ("pi", 3.1415) } "pi" -> 3.1415 */

	m.insert(std::make_pair("phi", 1.68033)); /* { ("e", 2.71828),	"e"   -> 2.71828
						       ("pi", 3.1415),	"pi"  -> 3.1415
						       ("phi",1.68033) }  "phi" -> 1.68033 */

	m.insert(std::make_pair("G", 0.83462)); /* { ("e", 2.71828),   "e"   -> 2.71828
						     ("pi", 3.1415),   "pi"  -> 3.1415
						     ("phi", 1.68033), "phi" -> 1.68033
						     ("G", 0.83462) }  "G"   -> 0.83462 */
	// Affichage de toutes les paires.
	for (std::map<const char*, double>::iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout 
			<< "("
			<< it->first
			<< ", "
			<< it->second
			<< ")"
			<< std::endl;
	}

	/* ------------------------
	 * Resultat en console
	 * ------------------------
	 *
	 *	("e", 2.71828)
	 *	("pi", 3.1415)
	 *	("phi", 1.68033)
	 *	("G", 0.83462) 
	 */

    return 0;
}
```

###[set](http://en.cppreference.com/w/cpp/container/set)

Un [set](http://en.cppreference.com/w/cpp/container/set) est est un [conteneur associatif](http://en.wikipedia.org/wiki/Associative_containers) qui ne comporte que des éléments [uniques](http://en.wikipedia.org/wiki/Uniqueness_quantification). Le [set](http://en.cppreference.com/w/cpp/container/set) peut se voir comme étant une spécialisation du [vector](http://en.cppreference.com/w/cpp/container/vector), à l'égard des valeurs de chaque élément.

####Déclaration

```cpp
template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class set;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_Compare_**| Le [prédicat](http://en.wikipedia.org/wiki/Function_object) de comparaison  |
|**_Container_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  du [conteneur](http://fr.wikipedia.org/wiki/Conteneur_(informatique)). |


####Exemple

```cpp
#include <iostream>
#include <set>

int main() {
    // Déclaration d'un ensemble d'entiers.
	std::set<int> s;
	
	// Insertion de valeurs dans s.
	// Chaque valeur doit être unique.
	s.insert(1);  // {1}
	s.insert(-1); // {1 -1}
	s.insert(2);  // {1 -1  2}
	s.insert(3);  // {1 -1  2  3}

	// Un set (ensemble) ne contient que des éléments uniques.
	// Par conséquent, cela n'affecte pas la cardinalité.
	s.insert(2);  // {1 -1  2  3}
	s.insert(2);  // {1 -1  2  3}
	s.insert(2);  // {1 -1  2  3}

	// Retrait de la valeur 2.
	s.erase(std::find(std::begin(s), std::end(s), 2)); // {1 -1  3}

	// Insertion à nouveau de 2 à la fin de s.
	s.insert(2);  // {1 -1  3  2}
    return 0;
}
```

---

##Adaptateurs de conteneurs

###[queue](http://en.cppreference.com/w/cpp/container/queue)

Une [queue](http://en.cppreference.com/w/cpp/container/queue) est une [file](http://fr.wikipedia.org/wiki/File_%28structure_de_donn%C3%A9es%29) qui suit le principe de **FIFO** (*First-in*, *First-out*). Les éléments sont insérés au fur et à mesure comme une [pile](http://fr.wikipedia.org/wiki/Pile_%28informatique%29). 

La différence entre une [file](http://fr.wikipedia.org/wiki/File_%28structure_de_donn%C3%A9es%29) et une [pile](http://fr.wikipedia.org/wiki/Pile_%28informatique%29), est l'ordre dans lequels les éléments sont retirés. Les éléments d'une [pile](http://fr.wikipedia.org/wiki/Pile_%28informatique%29) sont retirés à partir de la fin de la [liste](http://fr.wikipedia.org/wiki/Liste_%28informatique%29), tandis que ceux d'une [file](http://fr.wikipedia.org/wiki/File_%28structure_de_donn%C3%A9es%29) sont retirés à partir de du début ou la tête de celle-ci.

####Déclaration

```cpp
template<
    class T,
    class Container = std::deque<T>
> class queue;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_Container_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  du [conteneur](http://fr.wikipedia.org/wiki/Conteneur_(informatique)). |

####Exemple

```cpp
#include <iostream>
#include <queue>

int main() {
   // Déclaration d'une file d'entier.
    std::queue<int> q; // {}

    // Ajout d'éléments à la fin de q.
    q.push(1); // {1}
    q.push(2); // {1 2}
    q.push(3); // {1 2 3}
    q.push(4); // {1 2 3 4}

    // Retrait d'éléments au début de q.
    q.pop();   // {2 3 4}
    q.pop();   // {3 4}

    // Ajout d'éléments à la fin de q.
    q.push(5); // {3 4 5}
    q.push(6); // {3 4 5 6}

    // Retrait d'éléments au début de q.
    q.pop();   // {4 5 6}

    // Ajout d'éléments à la fin de q.
    q.push(7); // {4 5 6 7}

    // Suppression des éléments dans q
    q.clear(); // {}

    return 0;
}

```

###[stack](http://en.cppreference.com/w/cpp/container/stack)

Un [stack](http://en.cppreference.com/w/cpp/container/stack) est une [pile](http://fr.wikipedia.org/wiki/Pile_%28informatique%29) qui se sert du principe **LIFO** (*Last-in*, *first-out*) sur les éléments qui le composent. Dans une [pile](http://fr.wikipedia.org/wiki/Pile_%28informatique%29), les éléments sont retirés à partir de la fin de la [liste](http://fr.wikipedia.org/wiki/Liste_%28informatique%29).

####Déclaration

```cpp
template<
    class T,
    class Container = std::deque<T>
> class stack;
```

####Paramètres génériques
|Nom|Description|
|:--|:--|
|**_T_**| Le [type](http://fr.wikipedia.org/wiki/Type_(informatique)) de chaque élément. |
|**_Container_**| La [classe](http://fr.wikipedia.org/wiki/Classe_(informatique))  du [conteneur](http://fr.wikipedia.org/wiki/Conteneur_(informatique)). |


####Exemple

```cpp

#include <iostream>
#include <stack>

int main() {
   // Déclaration d'une pile d'entier.
    std::stack<int> s; // {}

    // Ajout d'éléments à la fin de s.
    s.push(1); // {1}
    s.push(2); // {1 2}
    s.push(3); // {1 2 3}
    s.push(4); // {1 2 3 4}

    // Retrait d'éléments à la fin de s.
    s.pop();   // {1 2 3}
    s.pop();   // {1 2}

    // Ajout d'éléments à la fin de s.
    s.push(5); // {1 2 5}
    s.push(6); // {1 2 5 6}
    s.push(7); // {1 2 5 6 7}

    s.clear(); // {}

    return 0;
}

```
