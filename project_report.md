### COMP3501A - Final Project Report

#### Project Structure

The headers and source files are split up into the `include` and `src` directories; these are then further split into `Control`, `Objects`, and `Renderer`. The CMake structure is recursive in nature - each of the `src` subfolders have their own `CMakeLists.txt` file containing each of the .cpp files and adding any additional subfolders. All of the resources are in the `res` directory.

##### Class Tree

.
├── include
│   ├── Control
│   │   ├── GUI
│   │   │   ├── Menus
│   │   │   │   ├── game_over.h
│   │   │   │   ├── hud.h
│   │   │   │   ├── main_menu.h
│   │   │   │   ├── pause_menu.h
│   │   │   │   ├── text_window.h
│   │   │   │   ├── upgrades.h
│   │   │   │   └── you_win.h
│   │   │   └── menu.h
│   │   ├── game.h
│   │   ├── input.h
│   │   ├── mathematics.h
│   │   ├── path_config.h
│   │   ├── resource_manager.h
│   │   ├── resource.h
│   │   ├── scene_graph.h
│   │   ├── scene_node.h
│   │   └── time.h
│   ├── Objects
│   │   ├── Hazards
│   │   │   ├── acid_pool.h
│   │   │   ├── geyser.h
│   │   │   ├── hazard.h
│   │   │   └── mud_pool.h
│   │   ├── Hovertank
│   │   │   ├── Abilities
│   │   │   │   ├── ability.h
│   │   │   │   ├── energy_cannon.h
│   │   │   │   ├── EnergyEmitter.h
│   │   │   │   └── machine_gun.h
│   │   │   ├── hovertank_track.h
│   │   │   ├── hovertank_turret.h
│   │   │   ├── hovertank.h
│   │   │   └── scanner.h
│   │   ├── Projectiles
│   │   │   ├── Enemy_linear_projectile.h
│   │   │   ├── EnergyBlast.h
│   │   │   ├── linear_projectile.h
│   │   │   ├── parabolic_projectile.h
│   │   │   └── projectile.h
│   │   ├── Artifact.h
│   │   ├── CarePackage.h
│   │   ├── ChaserEnemy.h
│   │   ├── Enemy.h
│   │   ├── EnergySource.h
│   │   ├── EnvironmentObject.h
│   │   ├── particle.h
│   │   ├── Player.h
│   │   ├── ShooterEnemy.h
│   │   └── terrain.h
│   └── Renderer
│       ├── camera.h
│       ├── ebo.h
│       └── vao.h
├── res
│   └── ...
├── src
│   ├── Control
│   │   ├── GUI
│   │   │   ├── Menus
│   │   │   │   ├── CMakeLists.txt
│   │   │   │   ├── game_over.cpp
│   │   │   │   ├── hud.cpp
│   │   │   │   ├── main_menu.cpp
│   │   │   │   ├── pause_menu.cpp
│   │   │   │   ├── text_window.cpp
│   │   │   │   ├── upgrades.cpp
│   │   │   │   └── you_win.cpp
│   │   │   ├── CMakeLists.txt
│   │   │   └── menu.cpp
│   │   ├── CMakeLists.txt
│   │   ├── game.cpp
│   │   ├── input.cpp
│   │   ├── resource_manager.cpp
│   │   ├── resource.cpp
│   │   ├── scene_graph.cpp
│   │   ├── scene_node.cpp
│   │   └── time.cpp
│   ├── Objects
│   │   ├── Hazards
│   │   │   ├── acid_pool.cpp
│   │   │   ├── CMakeLists.txt
│   │   │   ├── geyser.cpp
│   │   │   ├── hazard.cpp
│   │   │   └── mud_pool.cpp
│   │   ├── Hovertank
│   │   │   ├── Abilities
│   │   │   │   ├── ability.cpp
│   │   │   │   ├── CMakeLists.txt
│   │   │   │   ├── energy_cannon.cpp
│   │   │   │   ├── EnergyEmitter.cpp
│   │   │   │   └── machine_gun.cpp
│   │   │   ├── CMakeLists.txt
│   │   │   ├── hovertank_track.cpp
│   │   │   ├── hovertank_turret.cpp
│   │   │   ├── hovertank.cpp
│   │   │   └── scanner.cpp
│   │   ├── Projectiles
│   │   │   ├── CMakeLists.txt
│   │   │   ├── Enemy_linear_projectile.cpp
│   │   │   ├── EnergyBlast.cpp
│   │   │   ├── linear_projectile.cpp
│   │   │   ├── parabolic_projectile.cpp
│   │   │   └── projectile.cpp
│   │   ├── Artifact.cpp
│   │   ├── CarePackage.cpp
│   │   ├── ChaserEnemy.cpp
│   │   ├── CMakeLists.txt
│   │   ├── Enemy.cpp
│   │   ├── EnergySource.cpp
│   │   ├── EnvironmentObject.cpp
│   │   ├── particle.cpp
│   │   ├── Player.cpp
│   │   ├── ShooterEnemy.cpp
│   │   └── terrain.cpp
│   ├── Renderer
│   │   ├── camera.cpp
│   │   ├── CMakeLists.txt
│   │   ├── ebo.cpp
│   │   └── vao.cpp
│   ├── CMakeLists.txt
│   └── main.cpp
├── CMakeLists.txt
├── project_report.md
└── README.md

##### Assets / Credits

- **Fonts:**

  | **Asset Name**     | **Author**              | **Link**                                           |
    | ------------------ | ----------------------- | -------------------------------------------------- |
    | Freedom.ttf        | HXDes                   | https://www.fontspace.com/freedom-font-f14832      |
    | FabulaValhalla.ttf | Adam Alexander T. Croke | https://www.1001freefonts.com/fabula-valhalla.font |

- **Meshes:**

  | **Asset Name**                     | Author         |
  | ---------------------------------- | -------------- |
  | plant.mesh                         | Pablo Rascazzi |
  | pool.mesh                          | Ben Williams   |
  | rock1.mesh, rock2.mesh, rock3.mesh | Pablo Rascazzi |
  | hovertank_Chassis.mesh             | Pablo Rascazzi |
  | hovertank_Scanner.mesh             | Pablo Rascazzi |
  | hovertank_Scanner_Cone.mesh        | Pablo Rascazzi |
  | hovertank_Track_Front.mesh         | Pablo Rascazzi |
  | hovertank_Track_Rear.mesh          | Pablo Rascazzi |
  | hovertank_Turret.mesh              | Pablo Rascazzi |
  | hovertank_Machine_Gun.mesh         | Pablo Rascazzi |
  | artifact.mesh                      | Pablo Rascazzi |
  | enemy.mesh                         | Pablo Rascazzi |
  | parachute.mesh                     | Pablo Rascazzi |
  | rubber_bullet.mesh                 | Pablo Rascazzi |
  | spike_ball.mesh                    | Pablo Rascazzi |

- **Textures:**

  | **Asset Name**        | **Author**                                                   | Link                                                         |
  | --------------------- | :----------------------------------------------------------- | ------------------------------------------------------------ |
  | acid.png              | Horus                                                        | https://www.filterforge.com/filters/2152.html                |
  | alien_plant.png       | Frostguard                                                   | https://www.filterforge.com/filters/8489.html                |
  | dirt.png              | Sneath                                                       | https://www.filterforge.com/filters/11775.html               |
  | geyser.png            | Jakob Owens                                                  | https://unsplash.com/photos/nKFPNayRbFE                      |
  | mud.png               | G.A.G                                                        | https://www.filterforge.com/filters/6278.html                |
  | rocky.png             | David Mould (Texture Demo)                                   |                                                              |
  | snow.png              | Ghost IV                                                     | https://www.filterforge.com/filters/992.html                 |
  | electric.png          | Rian                                                         | https://www.filterforge.com/filters/4740.html                |
  | energy_blast.png      | Francisco Jacobo                                             | https://www.filterforge.com/filters/14211.html               |
  | rubber.png            | ScreenscapeS<br />Edited by: Pablo Rascazzi                  | https://www.filterforge.com/filters/13303.html               |
  | chaser_enemy.png      | Bobbiethejean                                                | https://www.filterforge.com/filters/9039.html                |
  | crate.png             | Mike Blackney                                                | https://www.filterforge.com/filters/750.html                 |
  | hovertank_texture.png | Katsukagi<br />Georges "TRaK" Grondin<br />Fupi<br />Edited by: Pablo Rascazzi | https://3dtextures.me/2019/04/30/metal-plate-012/<br />https://3dtextures.me/2019/06/11/metal-plate-020/<br />https://opengameart.org/content/wall-cover-3<br />https://opengameart.org/content/old-ventilation-cover-dark<br />https://opengameart.org/content/metal-panel-dark-brown-alt<br />https://opengameart.org/content/wall-cover-4<br />https://opengameart.org/content/warning-stripes-trim-trim-medium-border-light<br />https://opengameart.org/content/shiny-window-pane |
  | parachute.png         | minglepingle (Cloth)<br />Novaesky (Steel Cable)<br />Edited by: Pablo Rascazzi | https://www.filterforge.com/filters/12704.html<br />https://www.filterforge.com/filters/15744.html |
  | scanning.png          | capnsparrow<br />Edited by: Pablo Rascazzi                   | https://www.filterforge.com/filters/4106.html                |
  | shooter_enemy.png     | Bobbiethejean                                                | https://www.filterforge.com/filters/9039.html                |
  | sparkle_particle.png  | Ben Williams                                                 |                                                              |
  | water_particle.png    | David Mould (Fire Demo)                                      |                                                              |

  | **Asset Name**            | **Author**   |
  | ------------------------- | ------------ |
  | button.png                | Navin Haider |
  | energy_bar_background.png | Navin Haider |
  | energy_blast.png          | Navin Haider |
  | game_over.png             | Navin Haider |
  | health_bar_background.png | Navin Haider |
  | injured_screen_effect.png | Ben Williams |
  | linear.png                | Navin Haider |
  | mission_accomplished.png  | Navin Haider |
  | parabolic.png             | Navin Haider |
  | title_screen.png          | Navin Haider |

  

#### Fulfillment of Requirements

##### Game Description

##### Technical Requirements

0. Written in C++ using OpenGL to render; readable code with no serious bugs, suitable class hierarchy, good documentation.
   - We wrote the project in C++ using OpenGL.

1. Large textured heightfield terrain with collision detection. 
   - We generated a terrain heightfield using three layers of Perlin noise.
   - The terrain has two types of collision detection, one which does checks for collision between a line and a triangle, and another that interpolates the height of all 4 corners of a  terrain quad.


2. Game environment populated by textured, illuminated objects.

   - All objects in the world are textured.
   - All objects in the world are illuminated using Blinn-Phong lighting and a directional lighting.

   - The world is populated by three variations of instanced rocks along with a plant.

   - There are three types of environmental hazards throughout the world, a mud pool, an acid pool, and a geyser.


3. At least one use of a screen-space special effect.
   - When the player is hit, the screen flashes red on the corners.
   - ...


4. At least two distinct particle systems.

   - All of our particle systems use a single point which is instanced and is then expanded to quads in the geometry shader.

   - Each geyser has a particle system that simulates water being shot up into the air.

   - Each artifact has a "sparkling" effect before it has been scanned, this informs the player that it needs to be scanned.


5. At least two hierarchical objects with independently moving parts.

   - The hovertank is a hierarchical object that has a base as the root, and a turret and four hover tracks as children of the base. The the tank's turret has a scanner and 2 guns as children.

   - The care package has a parachute as a child which rotates individually from the crate.


6. Player-centric camera with player controls linked to current orientation.
   - Our game's camera is in third-person with the tank as its target. 
   - The camera rotates around the tank on the y-axis using the mouse movement.


8. Multiple stages to game.
   - The game has a main and a pause menu, along with an upgrade screen (that pauses the game), and mission accomplished/game over screens.


##### Gameplay Requirements

0. Hovertank navigating alien planet.

-

1. A thought-out setting with a variety of objects, including scenery and interactable objects both friendly and unfriendly. Give the player a role in the setting and a reason to take on the game's tasks.

- the world is populated with a variety of rocks, plants, and hazards that can be collided with
- each of the hazards has a different effect on the player; the geyser shoots them up into the air, mud slows them down, and acid damages them
- two types of aliens inhabit the world, one that shoots projectiles and one that deals melee damage

2. Tasks for the player to do.

- the player must find all artifacts while actively evading aliens and hazards

3. At least three distinct devices the player can use.

- scanner: used to open care packages and scan artifacts
- machine gun/energy cannon: different types of projectiles that stun the enemy they hit, one that is affected by gravity and one that isn't
energy blast: a shield like blast that stuns enemies in it's radius

4. Some kind of upgrade path fostering a sense of progression.

- whenever the player scans an artifact, they are awarded a set number of points, which can then be used to purchase upgrades
- the player is able to upgrade their health, speed, and energy (each has two levels), along with the effectiveness of each of the hazards (although they may not want to get some of the upgrades)
- the player can also purchase different abilities: the machine gun, energy cannon, and energy blast; these arrive in care packages that the player must find and pick up

5. Visual feedback about the player's status and actions.

- there is a HUD showing the player their health, energy level, weapon inventory, and number of artifacts collected
- an effect appears on the screen whenever the player is injured
- geyser rise and fall whenever the geyser is active/inactive
- artifact particles disappear after it has been collected
- a scanning effect appears whenever the player scans an artifact

6. Challenges that reward planning as well as reflexes.

- the player must collect a variety of artifacts, each one in a harder location than the previous (if following the natural path)
- many enemies populate the world, protecting the artifacts
- there are also hazards in which the player must avoid; the acid hazard deals damage to the player, while the mud slows them down (allowing enemies to catch-up)

##### Beyond the Minimum

- the terrain has quite advanced collision accomplished using ray-plane intersection
- in-depth GUI using ImGui
  - has many different menus, widgets
- gravity affects several objects in our game: the hovertank, care package, parabolic projectile (shot from the energy cannon), and all enemies


#### Postmortem

