cmake_minimum_required(VERSION 3.20)
project(ShootingGame3D)

set(CMAKE_CXX_STANDARD 14)
add_executable(ShootingGame3D src/main.cpp src/Game.cpp src/Game.h src/Components/Component.cpp src/Components/Component.h src/Actors/Actor.cpp src/Actors/Actor.h src/Components/SpriteComponent.cpp src/Components/SpriteComponent.h src/Commons/Math.h src/Commons/VertexArray.cpp src/Commons/VertexArray.h src/Commons/Shader.cpp src/Commons/Shader.h src/Commons/Texture.cpp src/Commons/Texture.h src/Commons/Mesh.cpp src/Commons/Mesh.h src/Components/MeshComponent.cpp src/Components/MeshComponent.h src/Actors/Camera.cpp src/Actors/Camera.h src/Commons/Renderer.cpp src/Commons/Renderer.h src/Scenes/ReadyScene.cpp src/Scenes/ReadyScene.h src/Scenes/Scene.cpp src/Scenes/Scene.h src/Actors/Ship.cpp src/Actors/Ship.h src/Actors/Bomb.cpp src/Actors/Bomb.h src/Actors/SkyBox.cpp src/Actors/SkyBox.h src/Actors/Missile.cpp src/Actors/Missile.h src/Actors/Enemy.cpp src/Actors/Enemy.h src/Components/BoxColliderComponent.cpp src/Components/BoxColliderComponent.h src/Commons/Collider.cpp src/Commons/Collider.h src/Actors/EnemyMarker.cpp src/Actors/EnemyMarker.h)

# SDL2のパスを設定
# 自身の環境に合わせて書き換えるべし
set(SDL2_LIB_PATH "/usr/local/Cellar/sdl2/2.0.16/lib/libSDL2-2.0.0.dylib")
set(SDL2_IMAGE_LIB_PATH "/usr/local/Cellar/sdl2_image/2.0.5/lib/libSDL2_image-2.0.0.dylib")
set(GLEW_LIB_PATH "/usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib")
set(FBXSDK_LIB_PATH "/Applications/Autodesk/FBX SDK/2020.2.1/lib/clang/debug/libfbxsdk.dylib")
include_directories("/usr/local/Cellar/sdl2/2.0.16/include/SDL2")
include_directories("/usr/local/Cellar/sdl2_image/2.0.5/include/SDL2")
include_directories("/usr/local/Cellar/glew/2.2.0_1/include")
include_directories("/Applications/Autodesk/FBX SDK/2020.2.1/include")

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_PATH} ${SDL2_IMAGE_LIB_PATH} ${GLEW_LIB_PATH} ${FBXSDK_LIB_PATH})

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
