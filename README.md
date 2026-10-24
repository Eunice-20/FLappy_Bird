# Flappy_bird

commande compilation a pre modification
pour main simple
```
gcc src/main.c -o flappy_bird.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```
pour main.c et bird.c
```
gcc src/main.c src/bird.c -o flappy.exe $(pkg-config --cflags --libs raylib) -lopengl32 -lgdi32 -lwinmm
```
pour main.c, bird.c et pipes.c
```
gcc src/main.c src/bird.c src/pipes.c -o flappy.exe $(pkg-config --cflags --libs raylib) -lopengl32 -lgdi32 -lwinmm
```
```
./flappy.exe
```
Gestion fenêtres sur une interface graphique (GUI)

![alt text](IMG-VIDEO_MD/WindoseGraf.png)

## Démonstration
Gestion gravite et deplacement Horizontal de l'oiseau

![Démo de Flappy Bird](IMG-VIDEO_MD/flappy_hrmGCpSitO.gif)
![alt text](IMG-VIDEO_MD/PositionGraf.png)

Gestion tuyeau, l'oiseau est replacé à gauche du tuyau

![Démo de Flappy Bird - Tuyeau](IMG-VIDEO_MD/flappy_edwnQBuJ7D.gif)

![alt text](IMG-VIDEO_MD/OsTuyeau.png)