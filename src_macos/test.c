#include "../minilibx_macos/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MINIMAP_SIZE 200  // Taille de la minimap
#define MAP_SCALE 10      // Facteur d'échelle pour la minimap

typedef struct {
    double x;
    double y;
    double direction_x; // Vecteur de direction du joueur sur l'axe x
    double direction_y; // Vecteur de direction du joueur sur l'axe y
} t_player;

typedef struct {
    void *mlx_ptr;
    void *win_ptr;
    char **map; // Matrice représentant la carte (0 pour vide, 1 pour mur, N/S/E/W pour joueur)
    int map_width;
    int map_height;
    t_player player; // Position et orientation du joueur
} t_data;

// Fonction pour dessiner un pixel dans la fenêtre
void draw_pixel(t_data *data, int x, int y, int color) {
    if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
    }
}

// Fonction pour trouver la position et l'orientation initiale du joueur
void find_player_position(t_data *data) {
    for (int i = 0; i < data->map_height; i++) {
        for (int j = 0; j < data->map_width; j++) {
            char current = data->map[i][j];
            if (current == 'N' || current == 'S' || current == 'W' || current == 'E') {
                // Initialisation de la position du joueur
                data->player.x = j + 0.5; // Le joueur est placé au centre de la case
                data->player.y = i + 0.5;

                // Orientation du joueur selon le symbole
                if (current == 'N') {
                    data->player.direction_x = 0;
                    data->player.direction_y = -1; // Dirigé vers le haut
                } else if (current == 'S') {
                    data->player.direction_x = 0;
                    data->player.direction_y = 1;  // Dirigé vers le bas
                } else if (current == 'W') {
                    data->player.direction_x = -1;
                    data->player.direction_y = 0;  // Dirigé vers la gauche
                } else if (current == 'E') {
                    data->player.direction_x = 1;
                    data->player.direction_y = 0;  // Dirigé vers la droite
                }

                // Remplacer le symbole par un 0 (case vide)
                data->map[i][j] = '0';
                return;
            }
        }
    }
}

// Fonction pour dessiner la minimap en centrant le joueur
void draw_minimap(t_data *data) {
    int i = 0, j = 0;
    
    // Taille de la partie visible de la minimap (en nombre de tuiles)
    int visible_tiles_x = MINIMAP_SIZE / MAP_SCALE;
    int visible_tiles_y = MINIMAP_SIZE / MAP_SCALE;

    // Calcul de l'offset (coin supérieur gauche de la minimap sur la carte)
    double offset_x = data->player.x / MAP_SCALE - visible_tiles_x / 2.0;
    double offset_y = data->player.y / MAP_SCALE - visible_tiles_y / 2.0;

    // Limiter l'offset pour ne pas sortir des bords de la carte
    if (offset_x < 0) offset_x = 0;
    if (offset_y < 0) offset_y = 0;
    if (offset_x + visible_tiles_x > data->map_width) offset_x = data->map_width - visible_tiles_x;
    if (offset_y + visible_tiles_y > data->map_height) offset_y = data->map_height - visible_tiles_y;

    // Dessiner les tuiles visibles dans la minimap
    i = 0;
    while (i < visible_tiles_y) {
        j = 0;
        while (j < visible_tiles_x) {
            int map_x = (int)(offset_x + j);
            int map_y = (int)(offset_y + i);

            if (data->map[map_y][map_x] == '1') { // 1 pour mur
                int mini_x = j * MAP_SCALE + (WIN_WIDTH - MINIMAP_SIZE - 10);
                int mini_y = i * MAP_SCALE + 10;

                int k = 0;
                while (k < MAP_SCALE) {
                    int l = 0;
                    while (l < MAP_SCALE) {
                        draw_pixel(data, mini_x + k, mini_y + l, 0xFFFFFF); // Blanc pour les murs
                        l++;
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }

    // Dessiner le joueur au centre de la minimap
    int player_x = WIN_WIDTH - MINIMAP_SIZE / 2 - 10;
    int player_y = 10 + MINIMAP_SIZE / 2;

    int k = -3;
    while (k <= 3) {
        int l = -3;
        while (l <= 3) {
            draw_pixel(data, player_x + k, player_y + l, 0xFF0000); // Rouge pour le joueur
            l++;
        }
        k++;
    }
}

// Fonction principale pour gérer l'affichage
int main() {
    t_data data;
    int i = 0, j = 0;

    // Initialisation de MiniLibX
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Minimap Example");

    // Initialisation de la carte (exemple de carte 10x10 avec des murs et une orientation du joueur)
    data.map_width = 10;
    data.map_height = 10;
    data.map = (char **)malloc(sizeof(char *) * data.map_height);

    char *map_data[10] = {
        "1111111111",
        "1000000001",
        "100N000001",  // Le joueur commence ici, orienté vers le nord
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1111111111"
    };

    for (i = 0; i < data.map_height; i++) {
        data.map[i] = strdup(map_data[i]);
    }

    // Trouver la position et l'orientation du joueur
    find_player_position(&data);

    // Boucle principale de rendu (affiche la minimap et autres éléments du jeu)
    while (1) {
        // Effacer l'écran (ajoutez une fonction pour cela si nécessaire)

        // Dessiner la minimap
        draw_minimap(&data);

        // Gestion des événements (ajustez selon votre gestion des événements)
        mlx_loop(data.mlx_ptr);
    }

    return 0;
}