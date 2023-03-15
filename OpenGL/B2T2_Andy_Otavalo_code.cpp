#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_s.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


//Flag
bool flag = false;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B2T2_Andy_Otavalo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/B2T2_Andy_Otavalo.vs", "shaders/B2T2_Andy_Otavalo.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float vertices[] = {
        //Grupo 1
        // positions        //id    //indices
        0.0f,0.0f, 0.0f,    0.0f,   //0     //Origen Grupo 1  
        0.1f,0.3f, 0.0f,    0.0f,   //1
        0.0f,0.5f, 0.0f,    0.0f,   //2
        -0.1f,0.3f,0.0f,    0.0f,   //3
        -0.3f,0.1f,0.0f,    0.0f,   //4
        -0.5f,0.0f,0.0f,    0.0f,   //5
        -0.3f,-0.1f,0.0f,   0.0f,   //6
        -0.1f,-0.3f,0.0f,   0.0f,   //7
        0.0f,-0.5f,0.0f,    0.0f,   //8
        0.1f,-0.3f,0.0f,    0.0f,   //9
        0.3f,-0.1f,0.0f,    0.0f,   //10
        0.5f,0.0f,0.0f,     0.0f,   //11
        0.3f,0.1f,0.0f,     0.0f,   //12

        //Grupo 2
        0.0f,0.0f,0.0f,     1.0f,   //13    //Origen Grupo 2
        0.3f,0.2f,0.0f,     1.0f,   //14
        0.2f,0.3f,0.0f,     1.0f,   //15
        -0.2,0.3f,0.0f,     1.0f,   //16
        -0.3f,0.2f,0.0f,    1.0f,   //17
        -0.3,-0.2f,0.0f,    1.0f,   //18
        -0.2f,-0.3f,0.0f,   1.0f,   //19
        0.2,-0.3f,0.0f,     1.0f,   //20
        0.3f,-0.2f,0.0f,    1.0f,   //21

        //Grupo 3
        0.0f,0.5f,0.0f,     2.0f,   //22
        -0.8f,0.8f,0.0f,    2.0f,   //23
        -0.5f,0.0f,0.0f,    2.0f,   //24
        -0.8f,-0.8f,0.0f,   2.0f,   //25
        0.0f,-0.5f,0.0f,    2.0f,   //26
        0.8f,-0.8f,0.0f,    2.0f,   //27
        0.5f,0.0f,0.0f,     2.0f,   //28
        0.8f,0.8f,0.0f,     2.0f,   //29
       
    };
    unsigned int indices[] = {
        //Grupo 1
        0,1,2,
        0,2,3,
        0,4,5,
        0,5,6,
        0,7,8,
        0,8,9,
        0,10,11,
        0,11,12,

        //Grupo 2
        13,14,15,
        13,16,17,
        13,18,19,
        13,20,21,

        //Grupo 3
        22,23,24,
        24,25,26,
        26,27,28,
        28,29,22,

    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // id group attribute
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("textures/B2T2_texture1.jpg", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/B2T2_texture2.jpg", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render 
        // ------
        float scale = sin(glfwGetTime());
        float visibility = (scale + 1.0) / 2.0;

        glClearColor(0.5f,visibility,0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //Grupo 1
        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform = glm::scale(transform, glm::vec3(scale, scale, scale));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 transform2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transform2 = glm::rotate(transform2, (float)glfwGetTime()*(-1), glm::vec3(0.0f, 0.0f, 1.0f));


        // get matrix's uniform location and set matrix
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "transform2");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform2));

        
        ourShader.setFloat("visible",visibility);
        // render container
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);



        if (flag) {
            //-----------------------------------------------------------------------
            //Figura Arriba-Izquierda
            transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
            transform = glm::translate(transform, glm::vec3(-0.8f, 0.8f, 0.0f));
            transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
            transform = glm::rotate(transform, (float)glfwGetTime() * (-1), glm::vec3(0.0f, 0.0f, 1.0f));

            // get matrix's uniform location and set matrix
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //another option
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

            glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);

            //-----------------------------------------------------------------------
            //Figura Arriba-Derecha
            transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
            transform = glm::translate(transform, glm::vec3(0.8f, 0.8f, 0.0f));
            transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
            transform = glm::rotate(transform, (float)glfwGetTime() * (-1), glm::vec3(0.0f, 0.0f, 1.0f));

            // get matrix's uniform location and set matrix
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //another option
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

            glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);

            //Figura Abajo-Izquierda
            transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
            transform = glm::translate(transform, glm::vec3(-0.8f, -0.8f, 0.0f));
            transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
            transform = glm::rotate(transform, (float)glfwGetTime() * (-1), glm::vec3(0.0f, 0.0f, 1.0f));

            // get matrix's uniform location and set matrix
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //another option
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

            glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);

            //-----------------------------------------------------------------------
            //Figura Abajo-Derecha
            transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
            transform = glm::translate(transform, glm::vec3(0.8f, -0.8f, 0.0f));
            transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));
            transform = glm::rotate(transform, (float)glfwGetTime() * (-1), glm::vec3(0.0f, 0.0f, 1.0f));

            // get matrix's uniform location and set matrix
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //another option
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

            glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
        }
        


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        flag = true;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        flag = false;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}