#Programmation générique

1. [Le mot-clé typedef](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#le-mot-cl%C3%A9-typedef)   
  * [Notation](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#notation)
2. [Types abstraits](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#types-abstraits).
  * [Notation](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#notation-1)
  * [Structures de données](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#structures-de-donn%C3%A9es)
3. [Patrons de classe & Templates](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#patrons-de-classe-templates)
  * [Paramètres & Liste de paramètres](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#param%C3%A8tres--liste-de-param%C3%A8tres)
  * [Fonctions & Classes](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#fonctions--classes)
  * [Spécialisation](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#sp%C3%A9cialisation)



##Le mot-clé typedef

En C++, il est possible de définir un, ou plusieurs [alias](http://en.cppreference.com/w/cpp/language/typedef) à partir de [types fondamentaux](http://en.cppreference.com/w/cpp/language/types).

###Notation

Soit **P**, une [primitive](http://en.wikipedia.org/wiki/Primitive_data_type) ex: `int`, `float`, `double`.  
Soit **A**, un [alias](http://en.cppreference.com/w/cpp/language/typedef) quelconque.

```cpp
typedef P A
```

####Exemple 1: Un simple alias

Supposons que **P** est un type [intégral](http://en.wikipedia.org/wiki/Integer_%28computer_science%29) [entier](http://fr.wikipedia.org/wiki/Entier_relatif) `int`, alors un [alias](http://en.cppreference.com/w/cpp/language/typedef) possible **A** `Entier` serait donné par la notation suivante:

```cpp
typedef int Entier
```

####Exemple 2: Induction d'alias

La définition de plusieurs [alias](http://en.cppreference.com/w/cpp/language/typedef) peut s'effectuer de même que par induction. Il s'agit simplement de définir d'autres [alias](http://en.cppreference.com/w/cpp/language/typedef) en utilisant un autre ultérieurement définis. 

Dans cet exemple, nous créeons deux familles d'[alias](http://en.cppreference.com/w/cpp/language/typedef) pour un type entier, une première pour un entier modifiable dit muable, une autre pour un type entier [immuable](http://fr.wikipedia.org/wiki/Objet_immuable)

```cpp
typedef       int      Entier
typedef       int&     ReferenceEntier
typedef       int*     PointeurEntier

typedef const int      EntierImmuable
typedef const int&     ReferenceEntierImmuable
typedef const int*     PointeurEntierImmuable
```

Le même résultat peut être obtenu par cette approche:

```cpp
typedef       int              Entier
typedef       Entier&          ReferenceEntier
typedef       Entier*          PointeurEntier

typedef const Entier           EntierImmuable
typedef const ReferenceEntier  ReferenceEntierImmuable
typedef const PointeurEntier   PointeurEntierImmuable
```


Il n'est pas rare de constater l'utilisation de cette méthode dans plusieurs libraries C++, telles que [boost](http://www.boost.org/), [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page), et même dans [STL](http://en.wikipedia.org/wiki/Standard_Template_Library)


#####Exemple de la librairie [boost](http://www.boost.org/)

Source: [iterator.hpp](http://www.boost.org/doc/libs/1_46_1/boost/detail/iterator.hpp)

```cpp
template <class Iterator>
struct iterator_traits
{
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::iterator_category iterator_category;
};
```


#####Exemple de la librairie [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page)

Source: [details.h](https://github.com/cryos/eigen/blob/f65aeca01ccad55422aed000153bbd134bfde5d1/Eigen/src/StlSupport/details.h)

```cpp
template <class T>
  class aligned_allocator_indirection : public EIGEN_ALIGNED_ALLOCATOR<T>
  {
  public:
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef T         value_type;
```

#####Exemple de la [librairie standard C++ (STL)](http://en.wikipedia.org/wiki/C%2B%2B_Standard_Library)

Sources: [\<stdexcept\>](http://en.cppreference.com/w/cpp/header/stdexcept)

```cpp
		// CLASS logic_error
class logic_error
	: public _XSTD exception
	{	// base of all logic-error exceptions
public:
	typedef _XSTD exception _Mybase;
```

La classe [logic_error](http://en.cppreference.com/w/cpp/error/logic_error) hérite de la classe [exception](http://en.cppreference.com/w/cpp/error/exception).

L'utilisation du mot-clé `typedef` sur `_XSTD exception` permet de définir un [alias](http://en.cppreference.com/w/cpp/language/typedef) `_MyBase` qui référence le type de la classe de base, soit [exception](http://en.cppreference.com/w/cpp/error/exception).  


##Types abstraits

###Notation

Il est possible de déclarer un type abstrait en utilisant la notation:  
```cpp
typename MonType;
```

Il est également possible d'affecter un type abstrait à un type existant:  
```cpp
typename MonTypeEntier = int;
```

###Structures de données

####Accès à des types définis dans des structures de données

```cpp
struct A {
    typedef int TypeDansA; // typename TypeDansA ? int
};

class B {
    typedef int TypeNonAccessible; // typename TypeNonAccessible? int
public:
    typedef int TypeAccessible; // typename TypeAccessible ? int
};

int main() {
    // Un type appartient à la classe, et non à un objet.
    // Il s'agit du même concept derrière les fonctions/membres statique.
    // Il faut utiliser le nom de la classe pour accéder au type en utilisant
    // l'opérateur de résolution :: qui signifie (fr:portée) ou (en:scope resolution)


    typedef TypeDansMain = typename A::TypeDansA; // typename TypeDansMain ? typename A::TypeDansA ? int
    return 0;
}
```

####Autres notions sur les types

#####Types dépendant

Un des problèmes dans la définitions de nouveaux [types abstraits](http://fr.wikipedia.org/wiki/Th%C3%A9orie_des_types) est [l'ambiguité](http://fr.wikipedia.org/wiki/Ambigu%C3%AFt%C3%A9). Pour tenter d'illustrer la différence entre un type dépendant et indépendant, reprenons l'exemple précédant, mais abordons la sous une forme différente:  

```cpp
struct S { typedef int Concept; // typename Concept ? int };

int main() {
    typedef MonType = S::Concept;
    return 0;
}
```

Malgré le respect de la logique, le compilateur n'a pas la capacité de déduire si `A::Concept` constitue une [variable](http://fr.wikipedia.org/wiki/Variable_(informatique)), ou un [type de donnée](http://fr.wikipedia.org/wiki/Type_(informatique)).  

Il faut donc indiquer de manière explicite s'il s'agit d'une [variable](http://fr.wikipedia.org/wiki/Variable_(informatique)) ou d'un [type de donnée](http://fr.wikipedia.org/wiki/Type_(informatique)) en utilisant le mot-clé `typename` comme préfixe juste avant la référence au type spécifié, soit `Concept`.


```cpp
typedef MonType =          S::Concept;  // ? Invalide
typedef MonType = typename S::Concept;  // ? Valide
```

#####Types indépendant

```cpp
struct S { 
typedef int TypeLocalS; // typename TypeLocalS ? int 

    struct {
        typedef TypeLocalS TypeLocalT // typename TypeLocalT ? TypeLocalS ? int 
    };
};
```


##Patrons de classe (templates)

Les patrons de classe permettent la substitution d'un type spécifié sur une classe prédéfinie.


###Paramètres & Liste de paramètres

Un ensemble de types est représenté comme ce qui suit:

```cpp
<typename A, typename B, typename C, ...>
```

Une autre notation équivalente existe:

```cpp
<class A, class B, class C, ...>
```

>  **class T** équivaut à **typename T**.  
>  
>  Il est toutefois *conseillé* d'utiliser le  
>  mot-clé `typename` pour des raisons de  
>  clareté.  

Sous cette forme, cet [ensemble](http://en.wikipedia.org/wiki/Set_(mathematics)) de [types](http://fr.wikipedia.org/wiki/Type_(informatique)) est plus communément appelé un ensemble de paramètres, où chaque élément constitue un paramètre abstrait, ou encore [générique](http://fr.wikipedia.org/wiki/G%C3%A9n%C3%A9ricit%C3%A9).

###Fonctions & Classes

Pour rendre une fonction générique, il faut d'abord précéder sa déclaration
avec l'instruction `template<...>`, où `...` représente un [ensemble](http://en.wikipedia.org/wiki/Set_(mathematics)) de [types](http://fr.wikipedia.org/wiki/Type_(informatique)).

#####Exemples
```cpp

// Une fonction possédant un paramètre générique
template<typename T>
void f(){
   ...
}

// Définition de deux paramètres génériques ayant par défaut 
// typename T ? float
// typename U ? int
template<typename T = float, class U = int>
void g() {
   ...
}

```

Pour rendre une classe générique, le même procédé tel que mentionné ci-dessus est appliqué.
```cpp

template<typename T>
class MaClasse {
public:
    const T& variable() const {
        return m_variable;
    }
private:
    T m_variable;
};

template<typename A, typename B, typename C, typename D>
class Tuple {
public:
    const A& valeur1() const { return m_valeur1; }
    const B& valeur2() const { return m_valeur2; }
    const C& valeur3() const { return m_valeur3; }
    const C& valeur4() const { return m_valeur4; }
private:
    A m_valeur1;
    B m_valeur2;
    C m_valeur3;
    D m_valeur4;
};
```

###Spécialisation

Comme la programmation générique favorise l'abstraction, il est possible de pouvoir définir de une à plusieurs variations de la même méthode et ou classe en fonction du type.  


Pour qu'une fonction/classe soit considérée comme une [spécialisation](http://en.cppreference.com/w/cpp/language/template_specialization) d'une certaine méthode/classe, celle-ci doit respecter plusieurs critères.  

Soit **F**, une fonction/classe générique.  
Soit **f**, une fonction/classe représentant une [spécialisation](http://en.cppreference.com/w/cpp/language/template_specialization) de **f**.  
Les critères à respecter:

- **f** possède le meme nom que **F** 
- **f** respecte la [signature](http://fr.wikipedia.org/wiki/Signature_de_type) de **F**
- **f** est unique  

Pour définir **f** en fonction de **F**, il faut se servir du mot-clé `template` comme préfixe juste avant la définition de **f** par la notation suivante:  

`template<>` où `<>` représente un ensemble de paramètre vide.

####Défintion d'une fonction/classe générique.

> Rappel: **f** est une [spécialisation](http://en.cppreference.com/w/cpp/language/template_specialization) de la fonction/classe, **F**  

Soit **P** un [ensemble](http://en.wikipedia.org/wiki/Set_(abstract_data_type)) de paramètres de **F**
```cpp
template<typename T>
```  

Soit **F** une fonction/classe définie comme qui suit:  
```cpp
                       // Définition de F
template<typename T>   // P est un ensemble de paramètres
void f(){
    ...
}
```

Soit **f** une spécialisation de **F**, alors nous pourrions avoir:  

```cpp
             // Définition de f (spécialisation) de F
template<>   // P est un ensemble de paramètres vide
void f()<char>{ // Notez l'ajout des chevrons < > juste après les parenthèses ().
                // Le type char est spécifié pour dire qu'il s'agit d'une spécialisation
    ...
}
```

Notez l'ajout des chevrons `<>` juste après les parenthèses `()`. Le type `char` est subsituté entre les chevrons pour indiquer qu'il s'agit d'une [spécialisation](http://en.cppreference.com/w/cpp/language/template_specialization) de **F** pour les charactères.

Pour utiliser une fonction générique spécialisée, il faut tout simplement référencer celle-ci par son nom, ainsi que son type de spécialisation:

```cpp
int main(){
    f<bool>(); // ** Appel de F **. (Aucune spécialisation définie.)
    f<char>(); // ** Appel de f **. (Utilisation de la spécialisation de charactères) 

    return 0;
}
```

Si l'utilisation de **F** ne spécifie pas une [spécialisation](http://en.cppreference.com/w/cpp/language/template_specialization), la fonction générique par défaut, soit **F** sera appelée, à moins de définir plusieurs autres [spécialisations](http://en.cppreference.com/w/cpp/language/template_specialization).  



####Exemples
```cpp

template<typename T>
void f() {
    std::cout << "Méthode par défaut" << std::endl;
}

template<>
void f<char>() {
    std::cout << "Spécialisation pour le type char" << std::endl;
}

template<>
void f<bool>() {
    std::cout << "Spécialisation pour le type bool" << std::endl;
}

int main(){
    f<int>(); // std::cout << "Méthode par défaut" << std::endl;
    f<double>(); // std::cout << "Méthode par défaut" << std::endl;
    f<char>(); // std::cout << "Spécialisation pour le type char" << std::endl;
    f<bool>(); // std::cout << "Spécialisation pour le type bool" << std::endl;
    return 0;
}

```