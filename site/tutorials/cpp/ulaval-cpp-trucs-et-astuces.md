#Trucs et astuces

Il est recommandé d'avoir lu et de comprendre les notions de base en logique de premier ordre. Les concepts présents dans cette page feront référence à des concepts de base avec le [calcul propositionnel](http://fr.wikipedia.org/wiki/Calcul_des_propositions).

[Rappel sur les tables de vérité](https://github.com/malortie/ulaval/wiki/Logique-en-programmation#tables-de-v%C3%A9rit%C3%A9)


##Table des matières
* [Intervertir deux entiers sans déclarer de variable temporaire](https://github.com/malortie/ulaval/wiki/Trucs-et-astuces#intervertir-deux-entiers-sans-d%C3%A9clarer-de-variable-temporaire)
* [Encoder une couleur 32 bits RGBA sur un entier de 4 octets](https://github.com/malortie/ulaval/wiki/Trucs-et-astuces#encoder-une-couleur-32-bits-rgba-sur-un-entier-int-de-4-octets)

##Intervertir deux entiers sans déclarer de variable temporaire.
```cpp

int a = 2;
int b = 3;

a ^= b;
b ^= a;
a ^= b;
```

####Précision

Pour comprendre cette opération, il faut connaître la représentation binaire.  

> a ? 2 ? 00000010  
> b ? 3 ? 00000011  

Par la suite il faut appliquer la [disjonction exclusive](https://github.com/malortie/ulaval/wiki/Logique-en-programmation#disjonction-exclusive) sur chacun des bits des entiers.


####Rappel 
#####Disjonction Exclusive
| P | Q | P ? Q |
|:-:|:-:|:-:|
| 1 | 1 | 0 |
| 1 | 0 | 1 |
| 0 | 1 | 1 |
| 0 | 0 | 0 |

####Démonstration

Chaque ligne de la table représente le premier octet (8 bits) de chacun des entiers.  

```cpp
a ^= b // a = a ^ b
```

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | id |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 0 | 0 | 0 | 0 | 0 | 0 | **1** | **0** | a |
| 0 | 0 | 0 | 0 | 0 | 0 | **1** | **1** | b |
| 0 | 0 | 0 | 0 | 0 | 0 | **0** | **1** | a |  

> a ? 1 ? 00000001  
> b ? 3 ? 00000011  

```cpp
b ^= a // b = b ^ a
```

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | id |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 0 | 0 | 0 | 0 | 0 | 0 | **0** | **1** | a |
| 0 | 0 | 0 | 0 | 0 | 0 | **1** | **1** | b |
| 0 | 0 | 0 | 0 | 0 | 0 | **1** | **0** | b |

> a ? 1 ? 00000001  
> b ? 2 ? 00000010

```cpp
a ^= b // a = a ^ b
```

| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | id |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 0 | 0 | 0 | 0 | 0 | 0 | **0** | **1** | a |
| 0 | 0 | 0 | 0 | 0 | 0 | **1** | **0** | b |
| 0 | 0 | 0 | 0 | 0 | 0 | **1** | **1** | a |

> a ? 3 ? 00000011  
> b ? 2 ? 00000010  

Nous avons donc:  

a = 3   
b = 2  

Comme convenu.  
  
> _C.Q.F.D_


##Encoder une couleur 32 bits [RGBA](http://en.wikipedia.org/wiki/RGBA_color_space) sur un [entier](http://en.wikipedia.org/wiki/Integer_(computer_science)) `int` de 4 octets.

```cpp

unsigned char rgba[] = { 255, 192, 42, 176}; // Équivaut à
                                              // rgba [0] = 255;
                                              // rgba [1] = 192;
                                              // rgba [2] = 42;
                                              // rgba [3] = 176;


unsigned int couleur = rgba[0] << 24 | // Décalage de 24 bits vers la gauche des 8 premiers bits de rgba.
                       rgba[1] << 16 | // Décalage de 16 bits vers la gauche des 8 seconds bits de rgba.
                       rgba[2] << 8  | // Décalage de 8 bits vers la gauche des 8 tertiaires bits de rgba.
                       rgba[3];        // Aucun décalage.

            // Procédé équivalent
            // (+ 0) est actuellement inutile. Il est utilisé pour 
            // simplifier l'alignement du texte.
            couleur = *(rgba + 0) << 24 | // Décalage de 24 bits vers la gauche des 8 premiers bits de rgba.
                      *(rgba + 1) << 16 | // Décalage de 16 bits vers la gauche des 8 seconds bits de rgba.
                      *(rgba + 2) << 8  | // Décalage de 8 bits vers la gauche des 8 tertiaires bits de rgba.
                      *(rgba + 3);        // Aucun décalage.   
```

####Démonstration

Soit **r**, **g**, **b**, **a**,    4 octets.
> **r** ? 255 ? 11111111  
> **g** ? 192 ? 11000000   
> **b** ? 42  ? 00101010  
> **a** ? 176 ? 10110000  


Soit la table suivante, ou chaque colone représente 4 bits, soit ½ octet

|0000|0000|0000|0000|0000|0000|0000|0000|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|

Nous avons:  

####Rouge

```cpp
rgba[0] << 24
```

|0000|0000|0000|0000|0000|0000|0000|0000||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0000|0000|0000|0000|0000|0000|**1111**|**1111**|r ? 255|
|||||||||<<|
|0000|0000|0000|0000|0000|0000|0000|0000|couleur|
|||||||||=||
|**1111**|**1111**|0000|0000|0000|0000|0000|0000|couleur|

####Vert

```cpp
rgba[1] << 16
```

|0000|0000|0000|0000|0000|0000|0000|0000||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0000|0000|0000|0000|0000|0000|**1100**|**0000**|g ? 192|
|||||||||<<|
|1111|1111|0000|0000|0000|0000|0000|0000|couleur|
|||||||||=|
|1111|1111|**1100**|**0000**|0000|0000|0000|0000|couleur|

####Bleu

```cpp
rgba[2] << 8
```

|0000|0000|0000|0000|0000|0000|0000|0000||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0000|0000|0000|0000|0000|0000|**0010**|**1010**|b ? 42|
|||||||||<<|
|1111|1111|1100|0000|0000|0000|0000|0000|couleur|
|||||||||=|
|1111|1111|1100|0000|**0010**|**1010**|0000|0000|couleur|

####Alpha

```cpp
rgba[3]
```

|0000|0000|0000|0000|0000|0000|0000|0000||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0000|0000|0000|0000|0000|0000|**1011**|**0000**|a ? 176|
||||||||||
|1111|1111|1100|0000|0010|1010|0000|0000|couleur|
|||||||||=|
|1111|1111|1100|0000|0010|1010|**1011**|**0000**|couleur|

Nous avons donc:
> `couleur` (forme binaire) ? `11111111 11000000 00101010 10110000`  
> `couleur` (forme décimale) ? `4290788016`  
> `couleur` (forme hexadécimale) ? `0xffc03ab0`  
