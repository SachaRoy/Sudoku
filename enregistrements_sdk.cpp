#include <iostream>
#include <fstream>
#include <string>


bool save_sdk(std::string file) {
    // Initialisation des variables
    std::ofstream f;
    f.open(file);
    char temp, temp2;
    int c{0};

    // Début du programme
    if(f.is_open()) {  // Vérifie que le fichier existe bien
        for(int i{0}; i<81; i++) { // Boucle de parcours de grille (haut-gauche vers bas-droite)
            std::cin >> temp; // Demande la prochaine valeur à insérer dans la grille
            if(temp == '0') {
                c++;  // Incrémente un compteur permettant la compression des 0
            }
            else {
                if(c != 0) {      // S'il y a des 0 à stocker...
                    temp2 = c+64;
                    f << temp2;   // ...insère une lettre représentant les c 0 à stocker (voir les spécificités du format "sdk" dans le readme)
                    c = 0;
                }
                f << temp;  // Enregistre la valeur rentrée dans le fichier
            }
        }
        if(c != 0) {  // Gère le cas où les dernières cases sont vides
            temp2 = c+64;
            f << temp2;
        }
        return true;
    }
    else {
        return false;
    }
}