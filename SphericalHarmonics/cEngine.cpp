
#include <future>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "cEngine.h"
#include <intrin.h>
#include <limits>

Engine::Engine() {

    start = true;
    rotation = 0;
    v_rotation = 90;
    b_rotation = false;
    b_change_lm = false;
    active_draw = -1;

    l = 6;
    m = 0;


    points = (cSphericalHarmonics::points_array*)malloc(sizeof(cSphericalHarmonics::points_array));
    

    VAO = (unsigned int*) malloc(sizeof(double));
    VBO = (unsigned int*) malloc(sizeof(double));
    EBO = (unsigned int*) malloc(sizeof(double));

    create_points();

    glViewport(0, 0, 2000, 2000);

    glEnable(GL_DEBUG_OUTPUT);

    glEnable(GL_DEPTH_TEST);
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

    glEnable(GL_MULTISAMPLE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Engine::~Engine() {
    delete VAO;
    delete VBO;
    delete EBO;
    delete camera;
    delete points;
}

void Engine::init_shader() {
    Shader s("shaders/shader.vs", "shaders/shader.fs", "shaders/shader.gs");

    camera = new Camera(s.ID, glm::dvec3(2.0, -2.0, 2.0), glm::dvec3(0.0, 0.0, 0.0), 1.0);

}

void Engine::render(double* delta_time, double zoom) {
    glBindVertexArray(0);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //if (b_rotation)
    camera->updateRotation(rotation, v_rotation);

    camera->updateZoom(zoom);

    if (b_change_lm) {
        std::cin >> l;
        std::cin >> m;
        create_points();
        b_change_lm = false;
    }


    glBindVertexArray(*VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);

        glDrawElements(GL_TRIANGLE_STRIP, points->size_ind, GL_UNSIGNED_INT, (void*)(0));



        /*for (int r = 0; r < 20; r++) {
            glDrawElements(GL_TRIANGLE_STRIP, 21, GL_UNSIGNED_INT, (void*)(42 * 4 * (2 * r)));
        }


        for (int r = 0; r < 20; r++) {
            glDrawElements(GL_TRIANGLE_STRIP, 21, GL_UNSIGNED_INT, (void*)(42 * 4 * (2 * r) + 21 * 4));
        }


        for (int r = 0; r < 20; r++) {
            glDrawElements(GL_TRIANGLE_STRIP, 21, GL_UNSIGNED_INT, (void*)(42*4*(2*r + 1)));
        }

        for (int r = 0; r < 20; r++) {
            glDrawElements(GL_TRIANGLE_STRIP, 21, GL_UNSIGNED_INT, (void*)(42 * 4 * (2 * r + 1) + 21 * 4));
        }*/
        glBindVertexArray(0);

}

void Engine::create_points() {


    cSphericalHarmonics::calculateSphericalHarmonic(points, l, m);

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);


    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, ((points)->size-1) * sizeof(double), points->p_array, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, points->size_ind * sizeof(unsigned int), points->ind_array, GL_STATIC_DRAW);

    glVertexAttribLPointer(0, 3, GL_DOUBLE, 4 * sizeof(double), (void*)(0));
    glEnableVertexAttribArray(0);


    glVertexAttribLPointer(1, 1, GL_DOUBLE, 4 * sizeof(double), (void*)(3 * sizeof(double)));
    glEnableVertexAttribArray(1);

    //glVertexAttribLPointer(1, 1, GL_DOUBLE, 4 * sizeof(double), (void*)(3 * sizeof(double)));
    //glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Engine::processInput(GLFWwindow* window, double* delta_time)
{


    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (rotation + 100 * *delta_time >= 360)
            rotation -= 360;
        rotation += 100 * *delta_time;
        b_rotation = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        b_rotation = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (rotation - 100 * *delta_time <= 0)
            rotation += 360;
        rotation -= 100 * *delta_time;
        b_rotation = true;
    }

    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        b_rotation = false;
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (v_rotation + 100 * *delta_time >= 90)
            v_rotation = 90;
        else v_rotation += 100 * *delta_time;
        b_rotation = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
        b_rotation = false;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (v_rotation - 100 * *delta_time <= -90)
            v_rotation = -90;
        else v_rotation -= 100 * *delta_time;
        b_rotation = true;
    }

    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        b_rotation = false;
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        
        b_change_lm = true;
    }
}

