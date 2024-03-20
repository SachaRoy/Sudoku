#include <iostream>
#include <dirent.h>
#include "class_sudoku.hpp"
#include "enregistrements_sdk.cpp"


int main() {
    // Initialisation des variables
    Grid g1;
    std::string nom_file;
    std::string file;
    std::string input_usr;
    int n;
    bool boucle = true;

    // Début du programme
    std::cout << "BIENVENUE";

    while(boucle) {
        std::cout << "\nQue voulez-vous faire ?\n1) Résoudre une grille\n2) Enregistrer une grille\n3) Voir vos grilles\n4) Quitter" << std::endl;
        std::cin >> input_usr;

        if(input_usr == "1" || input_usr == "résoudre" || input_usr == "solve") { // Option de résolution de grilles
            /*
                Affiche la solution de la grille demandée
                Ne modifie pas la grille enregistrée
            */

            std::cout << "Quelle grille voulez-vous résoudre ? " << std::flush;
            std::cin >> nom_file;
            file = nom_file+".sdk";

            if(g1.init(file)) {  // Vérifie que la grille existe
                if(g1.solve()) {  // Si la grille est résolvable...
                    g1.aff();     // ...alors on affiche la solution
                }    
                else {
                    std::cout << "La grille "<< nom_file <<" n'est pas résolvable." << std::endl;
                }
                g1.free();
            }
            else {  // Si la grille n'existe pas, propose à l'utilisateur de l'enregistrer
                std::cout << nom_file << " n'existe pas, voulez-vous la créer ? (y/n) ";
                std::cin >> input_usr;

                if(input_usr == "y" || input_usr == "yes") {
                    if(save_sdk(file)) {  // Vérifie que la grille est bien enregistrée
                        std::cout << "Grille enregistrée" << std::endl;
                    }
                    else {
                        std::cout << "Erreur lors de l'enregistrement" << std::endl;
                    }
                }
                else {
                    std::cout << "Grille non enregistrée" << std::endl;
                }
            }
        }
        else if(input_usr == "2" || input_usr == "enregistrer" || input_usr == "save") { // Option d'enregistrement de grilles
            /*
                Enregistre une grille sur l'ordinateur au format .sdk (voir les spécificités du format dans le readme)
            */

            std::cout << "Nom de la grille: " << std::flush;
            std::cin >> nom_file;  // Demande le nom de la grille

            file = nom_file+".sdk";
            if(save_sdk(file)) {  // Vérifie que la grille est bien enregistrée
                std::cout << "Grille enregistrée" << std::endl;
            }
            else {
                std::cout << "Erreur lors de l'enregistrement" << std::endl;
            }
        }
        else if(input_usr == "3" || input_usr == "voir" || input_usr == "grilles") { // Option de visualisation de grilles
            /*
                Récupère les noms des grilles présentes dans le répertoire courant et affiche celle demandée
            */

            bool empty_rep = true;  // Permet de garder en mémoire si le répertoire courant possède des fichiers au format "sdk" ou non

            std::cout << "Voici vos grilles, laquelle voulez-vous afficher ?\n";
            DIR* rep = opendir(".");  // Ouvre le répertoire courant
            if(rep != NULL) {  // Vérifie que le répertoire courant est bien ouvert
                struct dirent* ent;  // Récupère les fichiers présents dans le répertoire courant
                while((ent = readdir(rep)) != NULL) {
                    std::string temp = ent->d_name;
                    if((temp).find(".sdk") != -1) {  // Seuls les fichiers au format "sdk" sont affichés
                        std::cout << temp.substr(0, temp.size()-4) << std::endl;
                        empty_rep = false;  // Il existe un fichier au format "sdk"
                    }
                }
                closedir(rep);  // Ferme le répertoire courant
                if(empty_rep) {
                    std::cout << "[AUCUNE GRILLE]\n";
                }
            }
            
            if(not empty_rep) {
                std::cin >> nom_file;
                file = nom_file+".sdk";

                if(g1.init(file)) {  // Si le fichier a été correctement lu...
                    g1.aff();        // ...affiche la grille
                    g1.free();
                }
                else {
                    std::cout << "Grille introuvable\n";
                }
            }            
        }
        else if(input_usr == "4" || input_usr == "quitter" || input_usr == "q") { // Option d'arrêt du programme
            boucle = false;  // Met fin à la boucle principale
        }
        else {
            std::cout << "Commande inconnue" << std::endl; // Option par défaut
        }
    }

    return 0;
}