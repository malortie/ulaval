#Logique en programmation

Afin de comprendre les op�rateurs de bits � bits, il faut �tre en mesure de comprendre la base de **l'alg�bre
de boole**.  

[Alg�bre de Boole (logique)](http://fr.wikipedia.org/wiki/Alg%C3%A8bre_de_Boole_(logique))

##Tables de v�rit�

Soit _P_ et _Q_, la pr�condition et postcondition.

###Conjonction

| P | Q | P ? Q|
|:-:|:-:|:-:|
| 1 | 1 | 1 |
| 1 | 0 | 0 |
| 0 | 1 | 0 |
| 0 | 0 | 0 |

###Disjonction

| P | Q | P ? Q|
|:-:|:-:|:-:|
| 1 | 1 | 1 |
| 1 | 0 | 1 |
| 0 | 1 | 1 |
| 0 | 0 | 0 |  

###Implication

| P | Q | P ? Q |
|:-:|:-:|:-:|
| 1 | 1 | 1 |
| 1 | 0 | 0 |
| 0 | 1 | 1 |
| 0 | 0 | 1 |  

###Implication inverse,  
aussi appel�e implication r�ciproque

| P | Q | P ? Q |
|:-:|:-:|:-:|
| 1 | 1 | 1 |
| 1 | 0 | 1 |
| 0 | 1 | 0 |
| 0 | 0 | 1 |  

### �quivalence logique

| P | Q | P ? Q |
|:-:|:-:|:-:|
| 1 | 1 | 1 |
| 1 | 0 | 0 |
| 0 | 1 | 0 |
| 0 | 0 | 1 |  

### Disjonction exclusive

| P | Q | P ? Q |
|:-:|:-:|:-:|
| 1 | 1 | 0 |
| 1 | 0 | 1 |
| 0 | 1 | 1 |
| 0 | 0 | 0 |