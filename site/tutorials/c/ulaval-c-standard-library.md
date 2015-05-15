#Librairie String

* [Manipulation de chaînes de charactères](#manipulation-de-cha%C3%AEnes-de-charact%C3%A8res)

##Manipulation de chaînes de charactères

* [strcpy](#strcpy)

###strcpy

####Déclaration

```c
char *strcpy( char *destination, const char *source );
```

####Description
La fonction **strcpy** permet de copier une [chaîne de charactère](http://fr.wikipedia.org/wiki/Cha%C3%AEne_de_caract%C3%A8res) de **_source_** vers **_destination_**.

####Paramètres
* `destination`  
La **_destination_** ou copier les charactères.

* `source`  
La **_source_** à partir de laquelle les charactères seront copiés.

####Retour
**strcpy** retourne **_destination_**.

#####Remarques
**_destination_** doit être suffisament large, incluant le [charactère nul](http://en.wikipedia.org/wiki/Null_character) pour recevoir la **_source_**.  
Si la taille de **_destination_** est inférieure à celle de **_source_**, le résultat est [non-défini]
(http://en.wikipedia.org/wiki/Undefined_behavior).

####Exemple
```c
const char* source = "Texte"; // {'T','e','x','t','e','\0'}
char destination[6];
strcpy(destination, source);

// Affiche la chaîne de charactères "Texte" 
// à la console, sans les guillements.
puts(destination);
```

