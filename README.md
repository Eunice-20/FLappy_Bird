# Flappy_bird

### Les commande compilation  et les demontraction 

pour mise a jour du code 
```
gcc src/main.c src/bird.c src/pipes.c src/game.c src/blocs.c src/fleches.c -o flappy.exe $(pkg-config --cflags --libs raylib) -lopengl32 -lgdi32 -lwinmm
```
 lancement du jeux
```
./flappy.exe
```
- Gestion fenêtres sur une interface graphique (GUI)

![alt text](IMG-VIDEO_MD/WindoseGraf.png)

## Démonstration
- Gestion gravite et deplacement Horizontal de l'oiseau

![Démo de Flappy Bird](IMG-VIDEO_MD/flappy_hrmGCpSitO.gif)
![alt text](IMG-VIDEO_MD/PositionGraf.png)

- Gestion tuyeau, l'oiseau est replacé à gauche du tuyau

![Démo de Flappy Bird - Tuyeau](IMG-VIDEO_MD/flappy_edwnQBuJ7D.gif)

![alt text](IMG-VIDEO_MD/OsTuyeau.png)

- Gestion des niveaux, changement de décor et ajout du chronomètre

![Démo de Flappy Bird - Bloc](IMG-VIDEO_MD/mintty_xHa7vQXL6c.gif)

- Création du niveau 3 avec 3 flèches, changement de décor pour le niveau extrême, déplacements horizontaux et verticaux des obstacles

![Démo de Flappy Bird - Fleche](IMG-VIDEO_MD/mintty_DhzawSjD9B.gif)
