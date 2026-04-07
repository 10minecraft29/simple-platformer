#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/Entity.h"
#include "engine/Physics.h"
#include "engine/TileMap.h"
#include "engine/Texture.h"
#include "engine/SpriteRenderer.h"

float deltaTime, lastFrame;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Landoodle123 has ligma", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 800, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    TileMap map;

    Texture playerTex("assets/player.png");
    Texture enemyTex("assets/enemy.png");

    Entity player(100, 100, 64, 64);
    Entity enemy(300, 100, 64, 64);

    Animation playerAnim(4, 0.1f);
    Animation enemyAnim(2, 0.3f);

    player.anim = &playerAnim;
    enemy.anim = &enemyAnim;

    enemy.vx = 100;

    while (!glfwWindowShouldClose(window)) {
        float current = glfwGetTime();
        deltaTime = current - lastFrame;
        lastFrame = current;

        // INPUT
        player.vx = 0;
        if (glfwGetKey(window, GLFW_KEY_A)) player.vx = -200;
        if (glfwGetKey(window, GLFW_KEY_D)) player.vx = 200;
        if (glfwGetKey(window, GLFW_KEY_SPACE) && player.onGround)
            player.vy = -700;

        // PHYSICS
        Physics::applyGravity(player, deltaTime);
        Physics::move(player, map, deltaTime);

        Physics::applyGravity(enemy, deltaTime);
        Physics::move(enemy, map, deltaTime);

        // Enemy patrol
        if (enemy.vx == 0) enemy.vx = (rand() % 2 ? 100 : -100);

        // ANIMATION
        player.anim->update(deltaTime);
        enemy.anim->update(deltaTime);

        // RENDER
        glClear(GL_COLOR_BUFFER_BIT);

        playerTex.bind();
        SpriteRenderer::draw(
            player.x, player.y, player.w, player.h,
            player.anim->getU1(), 0.0f,
            player.anim->getU2(), 1.0f
        );

        enemyTex.bind();
        SpriteRenderer::draw(
            enemy.x, enemy.y, enemy.w, enemy.h,
            enemy.anim->getU1(), 0.0f,
            enemy.anim->getU2(), 1.0f
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
