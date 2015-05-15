#Programmation g�n�rique

1. [Le mot-cl� typedef](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#le-mot-cl%C3%A9-typedef)   
  * [Notation](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#notation)
2. [Types abstraits](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#types-abstraits).
  * [Notation](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#notation-1)
  * [Structures de donn�es](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#structures-de-donn%C3%A9es)
3. [Patrons de classe & Templates](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#patrons-de-classe-templates)
  * [Param�tres & Liste de param�tres](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#param%C3%A8tres--liste-de-param%C3%A8tres)
  * [Fonctions & Classes](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#fonctions--classes)
  * [Sp�cialisation](https://github.com/malortie/ulaval/wiki/Programmation-g%C3%A9n%C3%A9rique#sp%C3%A9cialisation)



##Le mot-cl� typedef

En C++, il est possible de d�finir un, ou plusieurs [alias](http://en.cppreference.com/w/cpp/language/typedef) � partir de [types fondamentaux](http://en.cppreference.com/w/cpp/language/types).

###Notation

Soit **P**, une [primitive](http://en.wikipedia.org/wiki/Primitive_data_type) ex: `int`, `float`, `double`.  
Soit **A**, un [alias](http://en.cppreference.com/w/cpp/language/typedef) quelconque.

```cpp
typedef P A
```

####Exemple 1: Un simple alias

Supposons que **P** est un type [int�gral](http://en.wikipedia.org/wiki/Integer_%28computer_science%29) [entier](http://fr.wikipedia.org/wiki/Entier_relatif) `int`, alors un [alias](http://en.cppreference.com/w/cpp/language/typedef) possible **A** `Entier` serait donn� par la notation suivante:

```cpp
typedef int Entier
```

####Exemple 2: Induction d'alias

La d�finition de plusieurs [alias](http://en.cppreference.com/w/cpp/language/typedef) peut s'effectuer de m�me que par induction. Il s'agit simplement de d�finir d'autres [alias](http://en.cppreference.com/w/cpp/language/typedef) en utilisant un autre ult�rieurement d�finis. 

Dans cet exemple, nous cr�eons deux familles d'[alias](http://en.cppreference.com/w/cpp/language/typedef) pour un type entier, une premi�re pour un entier modifiable dit muable, une autre pour un type entier [immuable](http://fr.wikipedia.org/wiki/Objet_immuable)

```cpp
typedef       int      Entier
typedef       int&     ReferenceEntier
typedef       int*     PointeurEntier

typedef const int      EntierImmuable
typedef const int&     ReferenceEntierImmuable
typedef const int*     PointeurEntierImmuable
```

Le m�me r�sultat peut �tre obtenu par cette approche:

```cpp
typedef       int              Entier
typedef       Entier&          ReferenceEntier
typedef       Entier*          PointeurEntier

typedef const Entier           EntierImmuable
typedef const ReferenceEntier  ReferenceEntierImmuable
typedef const PointeurEntier   PointeurEntierImmuable
```


Il n'est pas rare de constater l'utilisation de cette m�thode dans plusieurs libraries C++, telles que [boost](http://www.boost.org/), [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page), et m�me dans [STL](http://en.wikipedia.org/wiki/Standard_Template_Library)


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

La classe [logic_error](http://en.cppreference.com/w/cpp/error/logic_error) h�rite de la classe [exception](http://en.cppreference.com/w/cpp/error/exception).

L'utilisation du mot-cl� `typedef` sur `_XSTD exception` permet de d�finir un [alias](http://en.cppreference.com/w/cpp/language/typedef) `_MyBase` qui r�f�rence le type de la classe de base, soit [exception](http://en.cppreference.com/w/cpp/error/exception).  


##Types abstraits

###Notation

Il est possible de d�clarer un type abstrait en utilisant la notation:  
```cpp
typename MonType;
```

Il est �galement possible d'affecter un type abstrait � un type existant:  
```cpp
typename MonTypeEntier = int;
```

###Structures de donn�es

####Acc�s � des types d�finis dans des structures de donn�es

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
    // Un type appartient � la classe, et non � un objet.
    // Il s'agit du m�me concept derri�re les fonctions/membres statique.
    // Il faut utiliser le nom de la classe pour acc�der au type en utilisant
    // l'op�rateur de r�solution :: qui signifie (fr:port�e) ou (en:scope resolution)


    typedef TypeDansMain = typename A::TypeDansA; // typename TypeDansMain ? typename A::TypeDansA ? int
    return 0;
}
```

####Autres notions sur les types

#####Types d�pendant

Un des probl�mes dans la d�finitions de nouveaux [types abstraits](http://fr.wikipedia.org/wiki/Th%C3%A9orie_des_types) est [l'ambiguit�](http://fr.wikipedia.org/wiki/Ambigu%C3%AFt%C3%A9). Pour tenter d'illustrer la diff�rence entre un type d�pendant et ind�pendant, reprenons l'exemple pr�c�dant, mais abordons la sous une forme diff�rente:  

```cpp
struct S { typedef int Concept; // typename Concept ? int };

int main() {
    typedef MonType = S::Concept;
    return 0;
}
```

Malgr� le respect de la logique, le compilateur n'a pas la capacit� de d�duire si `A::Concept` constitue une [variable](http://fr.wikipedia.org/wiki/Variable_(informatique)), ou un [type de donn�e](http://fr.wikipedia.org/wiki/Type_(informatique)).  

Il faut donc indiquer de mani�re explicite s'il s'agit d'une [variable](http://fr.wikipedia.org/wiki/Variable_(informatique)) ou d'un [type de donn�e](http://fr.wikipedia.org/wiki/Type_(informatique)) en utilisant le mot-cl� `typename` comme pr�fixe juste avant la r�f�rence au type sp�cifi�, soit `Concept`.


```cpp
typedef MonType =          S::Concept;  // ? Invalide
typedef MonType = typename S::Concept;  // ? Valide
```

#####Types ind�pendant

```cpp
struct S { 
typedef int TypeLocalS; // typename TypeLocalS ? int 

    struct {
        typedef TypeLocalS TypeLocalT // typename TypeLocalT ? TypeLocalS ? int 
    };
};
```


##Patrons de classe (templates)

Les patrons de classe permettent la substitution d'un type sp�cifi� sur une classe pr�d�finie.


###Param�tres & Liste de param�tres

Un ensemble de types est repr�sent� comme ce qui suit:

```cpp
<typename A, typename B, typename C, ...>
```

Une autre notation �quivalente existe:

```cpp
<class A, class B, class C, ...>
```

>  **class T** �quivaut � **typename T**.  
>  
>  Il est toutefois *conseill�* d'utiliser le  
>  mot-cl� `typename` pour des raisons de  
>  claret�.  

Sous cette forme, cet [ensemble](http://en.wikipedia.org/wiki/Set_(mathematics)) de [types](http://fr.wikipedia.org/wiki/Type_(informatique)) est plus commun�ment appel� un ensemble de param�tres, o� chaque �l�ment constitue un param�tre abstrait, ou encore [g�n�rique](http://fr.wikipedia.org/wiki/G%C3%A9n%C3%A9ricit%C3%A9).

###Fonctions & Classes

Pour rendre une fonction g�n�rique, il faut d'abord pr�c�der sa d�claration
avec l'instruction `template<...>`, o� `...` repr�sente un [ensemble](http://en.wikipedia.org/wiki/Set_(mathematics)) de [types](http://fr.wikipedia.org/wiki/Type_(informatique)).

#####Exemples
```cpp

// Une fonction poss�dant un param�tre g�n�rique
template<typename T>
void f(){
   ...
}

// D�finition de deux param�tres g�n�riques ayant par d�faut 
// typename T ? float
// typename U ? int
template<typename T = float, class U = int>
void g() {
   ...
}

```

Pour rendre une classe g�n�rique, le m�me proc�d� tel que mentionn� ci-dessus est appliqu�.
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

###Sp�cialisation

Comme la programmation g�n�rique favorise l'abstraction, il est possible de pouvoir d�finir de une � plusieurs variations de la m�me m�thode et ou classe en fonction du type.  


Pour qu'une fonction/classe soit consid�r�e comme une [sp�cialisation](http://en.cppreference.com/w/cpp/language/template_specialization) d'une certaine m�thode/classe, celle-ci doit respecter plusieurs crit�res.  

Soit **F**, une fonction/classe g�n�rique.  
Soit **f**, une fonction/classe repr�sentant une [sp�cialisation](http://en.cppreference.com/w/cpp/language/template_specialization) de **f**.  
Les crit�res � respecter:

- **f** poss�de le meme nom que **F** 
- **f** respecte la [signature](http://fr.wikipedia.org/wiki/Signature_de_type) de **F**
- **f** est unique  

Pour d�finir **f** en fonction de **F**, il faut se servir du mot-cl� `template` comme pr�fixe juste avant la d�finition de **f** par la notation suivante:  

`template<>` o� `<>` repr�sente un ensemble de param�tre vide.

####D�fintion d'une fonction/classe g�n�rique.

> Rappel: **f** est une [sp�cialisation](http://en.cppreference.com/w/cpp/language/template_specialization) de la fonction/classe, **F**  

Soit **P** un [ensemble](http://en.wikipedia.org/wiki/Set_(abstract_data_type)) de param�tres de **F**
```cpp
template<typename T>
```  

Soit **F** une fonction/classe d�finie comme qui suit:  
```cpp
                       // D�finition de F
template<typename T>   // P est un ensemble de param�tres
void f(){
    ...
}
```

Soit **f** une sp�cialisation de **F**, alors nous pourrions avoir:  

```cpp
             // D�finition de f (sp�cialisation) de F
template<>   // P est un ensemble de param�tres vide
void f()<char>{ // Notez l'ajout des chevrons < > juste apr�s les parenth�ses ().
                // Le type char est sp�cifi� pour dire qu'il s'agit d'une sp�cialisation
    ...
}
```

Notez l'ajout des chevrons `<>` juste apr�s les parenth�ses `()`. Le type `char` est subsitut� entre les chevrons pour indiquer qu'il s'agit d'une [sp�cialisation](http://en.cppreference.com/w/cpp/language/template_specialization) de **F** pour les charact�res.

Pour utiliser une fonction g�n�rique sp�cialis�e, il faut tout simplement r�f�rencer celle-ci par son nom, ainsi que son type de sp�cialisation:

```cpp
int main(){
    f<bool>(); // ** Appel de F **. (Aucune sp�cialisation d�finie.)
    f<char>(); // ** Appel de f **. (Utilisation de la sp�cialisation de charact�res) 

    return 0;
}
```

Si l'utilisation de **F** ne sp�cifie pas une [sp�cialisation](http://en.cppreference.com/w/cpp/language/template_specialization), la fonction g�n�rique par d�faut, soit **F** sera appel�e, � moins de d�finir plusieurs autres [sp�cialisations](http://en.cppreference.com/w/cpp/language/template_specialization).  



####Exemples
```cpp

template<typename T>
void f() {
    std::cout << "M�thode par d�faut" << std::endl;
}

template<>
void f<char>() {
    std::cout << "Sp�cialisation pour le type char" << std::endl;
}

template<>
void f<bool>() {
    std::cout << "Sp�cialisation pour le type bool" << std::endl;
}

int main(){
    f<int>(); // std::cout << "M�thode par d�faut" << std::endl;
    f<double>(); // std::cout << "M�thode par d�faut" << std::endl;
    f<char>(); // std::cout << "Sp�cialisation pour le type char" << std::endl;
    f<bool>(); // std::cout << "Sp�cialisation pour le type bool" << std::endl;
    return 0;
}

```