#include <iostream>
#include <string>

/*
Fichier header de la classe "Grid" permettant la représentation de grilles de sudoku
La grille est stockée dans un tableau unidimentionnel de 81 entiers
*/
class Grid {
    // Méthodes privées
    private:
    int* val;
    int n_col(int c);
    int n_line(int c);
    int n_area(int c);
    
    
    // Méthodes publiques
    public:
    bool init(std::string file);
    void free();
    void aff();
    int get(int l, int c);
    bool solve();
    bool check_col(int c, int v);
    bool check_line(int c, int v);
    bool check_area(int c, int v);
    bool check(int c, int v);
};