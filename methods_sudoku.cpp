#include <fstream>
#include "class_sudoku.hpp"


int ctoi(char c) {  // Fonction auxiliaire facilitant la conversion "char" vers "int"
    int rep = c-48;
    return rep;
}


bool Grid::init(std::string file) {  // Initialise une grille à partir d'un fichier "sdk"
    std::ifstream f;
    f.open(file);

    if(f.is_open()) {  // Vérifie que le fichier est bien ouvert
        this->val = new int[81];  // Initialise le tableau contenant les valeurs de la grille

        std::string line;
        std::getline(f, line);  // Récupère les données stockées dans le fichier

        int j{0};  // Stock la position où insérer des valeurs dans la grille
        for(char e: line) {  // Boucle de parcours des données
            if(e >= 'A') {  // Décompression des 0
                for(int i{0}; i<e-64; i++) {
                    this->val[i+j] = 0;
                }
                j += e-64;
            }
            else {
                this->val[j] = ctoi(e);  // Enregistre les valeurs dans le tableau
                j++;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

void Grid::free() {  // Libère une grille de la mémoire
    delete this->val;
}

void Grid::aff() {  // Affiche une grille sous la forme d'une matrice de taille 9x9 (haut-gauche vers bas-droite)
    for(int i{0}; i<9; i++) {
        for(int j{0}; j<9; j++) {  // Affiche une ligne de 9 éléments séparés par un espace
            std::cout << this->get(i, j) << " ";  // Envoie la valeur en position (i,j) dans la grille, vers la sortie standard
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
}

int Grid::get(int l, int c) {  // Renvoie la valeur en position (i,j) dans la grille
    return this->val[c+l*9];
}

int Grid::n_col(int c) {  // Renvoie le numéro de la colonne de la case c dans la grille
    return c%9;
}

int Grid::n_line(int c) {  // Renvoie le numéro de la ligne de la case c dans la grille
    return c/9;
}

int Grid::n_area(int c) {  // Renvoie le numéro de la région de la case c dans la grille
    return 3*(this->n_col(c)/3) + this->n_line(c)/3;
}

bool Grid::check_col(int c, int v) {  // Vérifie que la valeur v n'est pas déjà présente dans la colonne de la case c
    bool rep = true;
    int col = n_col(c);
    for(int i{0}; i<9; i++) {  // Parcours la colonne de c
        if(this->get(i, col) == v && (9*i)+col != c) {  // Vérifie que la case ne contient pas v
            rep = false;
            break;
        }
    }
    return rep;
}

bool Grid::check_line(int c, int v) {  // Vérifie que la valeur v n'est pas déjà présente dans la ligne de la case c
    bool rep = true;
    int l = n_line(c);
    for(int i{0}; i<9; i++) {  // Parcours la ligne de c
        if(this->get(l, i) == v && (9*l)+i != c) {  // Vérifie que la case ne contient pas v
            rep = false;
            break;
        }
    }
    return rep;
}

bool Grid::check_area(int c, int v) {  // Vérifie que la valeur v n'est pas déjà présente dans la région de la case c
    bool rep = true;
    int g = n_area(c);
    for(int i{(g/3)*3}; i<((g/3)+1)*3; i++) {
        for(int j{(g%3)*3}; j<((g%3)+1)*3; j++) {  // Parcours la région de c
            if(this->get(j, i) == v && (9*j)+i != c) {  // Vérifie que la case ne contient pas v
                rep = false;
                break;
            }
        }
    }
    return rep;
}


bool Grid::check(int c, int v) {  // Vérifie que l'on peut insérer la valeur v dans la case c
    return this->check_col(c, v) && this->check_line(c, v) && this->check_area(c, v);
}

bool Grid::solve() {  // Résout une grille par backtracking, modifie la grille en question
    for(int i{0}; i<81; i++) {  // Parcours de la grille
        if(this->val[i] == 0) {  // Vérifie si la case courante est vide
            for(int n{1}; n<=9; n++) {  // Boucle parcourant les valeurs possibles à mettre dans la case courante
                this->val[i] = n;  // Insère une valeur dans la grille
                if(this->check(i, n)) {  // vérifie que la valeur insérée est conforme aux contraintes du sudoku
                    if(this->solve()) {  // Appel récursif de la fonction solve sur la nouvelle grille
                        return true;  // Renvoie que la grille est bien conforme aux contraintes du sudoku
                    }
                }
            }
            this->val[i] = 0;  // Si aucune valeur ne convient, on vide la case courante...
            return false;      // ...et on renvoie que la grille n'est pas conforme aux contraintes du sudoku (on effectue le retour arrière)
        }
    }
    return true;  // On a réussi à remplir une grille convenablement
}