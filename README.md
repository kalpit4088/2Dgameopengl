Graphics opengl project
=====================

Pacman Killer 2D game in OpenGL 3. More details in the statement [PDF](Assign1.pdf).

Kalpit Pokra
=======================

### Run the game using terminal
- cd "dir name"
- mkdir build && cd build
- cmake ..
- make
- ./graphics_asgn1


### Controls

- **Mousewheel** - Zoom
- **A**, **S**, **W**, **D** / **Mouse drag** - Pan (when zoomed)
- **Up**, **Right**, **Left** - Player ball movement


### Extra features

- Colourful background
- Score
- Zooming/panning using both mouse and keyboard
- Modularity


### Scoring
- If player ball collides with yellow balls(i.e. balls with slopes) score will increase by 3 also that ball will disappear.
- If player ball collides with silver balls score will increase by 2 also that ball will disappear.
- and if player ball collides with red balls score will increase by 1 also that ball will disappear.
- If player ball collides with moving porcupinr score will decrease by 1, also porcupine will disappear for a while and player ball also repositions itself.
