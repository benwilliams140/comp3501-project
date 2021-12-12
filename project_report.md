### COMP3501A - Final Project Report

#### Project Structure

The headers and source files are split up into the `include` and `src` directories; these are then further split into `Control`, `Objects`, and `Renderer`. The CMake structure is recursive in nature.

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

- 

1. Large textured heightfield terrain with collision detection and shadows. 

- 

2. Game environment populated by textured, illuminated objects.

3. At least one use of a screen-space special effect.

4. At least two distinct particle systems.

5. At least two hierarchical objects with independently moving parts.

6. Player-centric camera with player controls linked to current orientation.

7. Gravity affecting at least some objects (ballistic motion).

8. Multiple stages to game.

##### Gameplay Requirements

0. Hovertank navigating alien planet.

1. A thought-out setting with a variety of objects, including scenery and interactable objects both friendly and unfriendly. Give the player a role in the setting and a reason to take on the game's tasks.

2. Tasks for the player to do.

3. At least three distinct devices the player can use.

4. Some kind of upgrade path fostering a sense of progression.

5. Visual feedback about the player's status and actions.

6. Challenges that reward planning as well as reflexes.

##### Beyond the Minimum

#### Postmortem

