#Librairie String

* [Manipulation de cha�nes de charact�res](https://github.com/malortie/ulaval/wiki/C---Librairie-String#manipulation-de-cha%C3%AEnes-de-charact%C3%A8res)

##Manipulation de cha�nes de charact�res

* [strcpy](https://github.com/malortie/ulaval/wiki/C---Librairie-String#strcpy)

###strcpy

####D�claration

```c
char *strcpy( char *destination, const char *source );
```

####Description
La fonction **strcpy** permet de copier une [cha�ne de charact�re](http://fr.wikipedia.org/wiki/Cha%C3%AEne_de_caract%C3%A8res) de **_source_** vers **_destination_**.

####Param�tres
* `destination`  
La **_destination_** ou copier les charact�res.

* `source`  
La **_source_** � partir de laquelle les charact�res seront copi�s.

####Retour
**strcpy** retourne **_destination_**.

#####Remarques
**_destination_** doit �tre suffisament large, incluant le [charact�re nul](http://en.wikipedia.org/wiki/Null_character) pour recevoir la **_source_**.  
Si la taille de **_destination_** est inf�rieure � celle de **_source_**, le r�sultat est [non-d�fini]
(http://en.wikipedia.org/wiki/Undefined_behavior).

####Exemple
```c
const char* source = "Texte"; // {'T','e','x','t','e','\0'}
char destination[6];
strcpy(destination, source);

// Affiche la cha�ne de charact�res "Texte" 
// � la console, sans les guillements.
puts(destination);
```

