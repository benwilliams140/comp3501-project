### COMP3501A - Final Project Report

#### Project Structure

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
│   ├── fonts
│   │   ├── FabulaValhalla.ttf
│   │   └── Freedom.ttf
│   ├── meshes
│   │   ├── environment
│   │   │   ├── plant.mesh
│   │   │   ├── pool.mesh
│   │   │   ├── rock1.mesh
│   │   │   ├── rock2.mesh
│   │   │   └── rock3.mesh
│   │   ├── hovertank
│   │   │   ├── hovertank_Chassis.mesh
│   │   │   ├── hovertank_Machine_Gun.mesh
│   │   │   ├── hovertank_Scanner_Cone.mesh
│   │   │   ├── hovertank_Scanner.mesh
│   │   │   ├── hovertank_Track_Front.mesh
│   │   │   ├── hovertank_Track_Rear.mesh
│   │   │   └── hovertank_Turret.mesh
│   │   ├── cube.mesh
│   │   ├── enemy.mesh
│   │   ├── parachute.mesh
│   │   ├── rubber_bullet.mesh
│   │   ├── sphere.mesh
│   │   └── spike_ball.mesh
│   ├── shaders
│   │   ├── artifact_particle_fp.glsl
│   │   ├── artifact_particle_gp.glsl
│   │   ├── artifact_particle_vp.glsl
│   │   ├── geyser_particle_fp.glsl
│   │   ├── geyser_particle_gp.glsl
│   │   ├── geyser_particle_vp.glsl
│   │   ├── instancing_fp.glsl
│   │   ├── instancing_vp.glsl
│   │   ├── lit_fp.glsl
│   │   ├── lit_vp.glsl
│   │   ├── simple_texture_fp.glsl
│   │   ├── simple_texture_vp.glsl
│   │   ├── terrain_fp.glsl
│   │   └── terrain_vp.glsl
│   └── textures
│       ├── environment
│       │   ├── acid.png
│       │   ├── alien_plant.png
│       │   ├── dirt.png
│       │   ├── geyser.png
│       │   ├── mud.png
│       │   ├── rocky.png
│       │   └── snow.png
│       ├── gui
│       │   ├── button.png
│       │   ├── energy_bar_background.png
│       │   ├── energy_blast.png
│       │   ├── game_over.png
│       │   ├── health_bar_background.png
│       │   ├── injured_screen_effect.png
│       │   ├── linear.png
│       │   ├── mission_accomplished.png
│       │   ├── parabolic.png
│       │   └── title_screen.png
│       ├── projectiles
│       │   ├── electric.png
│       │   ├── energy_blast.png
│       │   └── rubber.png
│       ├── chaser_enemy.png
│       ├── crate.png
│       ├── hovertank_texture.png
│       ├── parachute.png
│       ├── scanning.png
│       ├── shooter_enemy.png
│       ├── sparkle_particle.png
│       ├── uv6.png
│       └── water_particle.png
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
├── .gitignore
├── .gitmodules
├── CMakeLists.txt
├── CMakeSettings.json
├── project_report.md
└── README.md

##### Assets / Credits

- **Fonts:**

#### Fulfillment of Requirements

#### Postmortem

