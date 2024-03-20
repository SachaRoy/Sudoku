Ce code ne fonctionne que sous linux !

Format ".sdk": Format de fichier utilisé pour stocker des grilles de sudoku de taille 9x9.
- Les valeurs sont laissées comme telles
- Les vides sont représentés par un caractère ASCII en fonction de la taille du vide en commençant par le A pour représenter un espace, le B deux espaces, et ainsi de suite.
De cette façon une grille vide a une taille de 1 octet et une grille pleine a une taille de 81 octets.

À l'exécution, 4 options sont proposées:
- 1) Résolution d'une grille: cette option affiche la solution de la grille selectionnée. À noter qu'elle l'affiche seulement, la solution ne vient pas écraser la grille d'origine et elle n'est stockées nul part.
     Si la grille selectionnée n'existe pas, il vous sera proposé de l'enregistrer.
- 2) Enregistrer une grille: cette option permet d'enregistrer une grille au format "sdk".
     Le fichier sera enregistré dans le même répertoire que l'exécutable.
- 3) Voir une grille: cette option permet de savoir quelles grilles sont présentes dans le repertoire de l'exécutable.
     Il est possible de voir la grille séléctionnée.
- 4) Quitter: met fin au programme.
