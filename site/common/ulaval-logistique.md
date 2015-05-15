#Logique en programmation

Afin de comprendre les opérateurs de bits à bits, il faut être en mesure de comprendre la base de **l'algèbre
de boole**.  

[Algèbre de Boole (logique)](http://fr.wikipedia.org/wiki/Alg%C3%A8bre_de_Boole_(logique))

##Tables de vérité

Soit _P_ et _Q_, la précondition et postcondition.

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
aussi appelée implication réciproque

| P | Q | P ? Q |
|:-:|:-:|:-:|
| 1 | 1 | 1 |
| 1 | 0 | 1 |
| 0 | 1 | 0 |
| 0 | 0 | 1 |  

### Équivalence logique

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