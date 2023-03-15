#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>
#define STB_IMAGE_IMPLEMENTATION 

#include <learnopengl/stb_image.h>

#include <iostream>

//funcion para crear una ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Funcion para cambiar el color
void cambiarColor(Shader ourshader);


//valores de ancho y alto de la ventana
const unsigned int SCR_WIDTH = 900; // ancho
const unsigned int SCR_HEIGHT = 800; //alto


//funcion principal para ejecutar el codigo
int main()
{
    // inicializacion de las librerias glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // creacion de la ventana glfw
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Salome Garzon 0504118985", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // termina la ejecucion si la inicializacion de los punteros falla

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // creacion y construccion shader program
    Shader ourShader("shaders/shaderB2T1.vs", "shaders/shaderB2T1.fs");


    // coordenadas de posicion y color de cada triangulo
    float vertices1[] = {

        //T1
        //positions             // colors               //Texture    
         0.4f,  0.1f, 0.0f,     1.0f, 0.67f, 0.0f,      0.6f, 0.1f,     //0 A
         0.25f, 0.1f, 0.0f,     1.0f, 0.67f, 0.0f,      0.2f, 0.1f,     //1 B
         0.25f, 0.25f, 0.0f,    0.0f, 1.0f, 0.67f,      0.3f, 0.4f,     //2 C

        //T2
        //0.25f, 0.25f, 0.0f,     0.37f, 0.33f, 0.69f,    0.3f, 0.4f,
        0.35f, 0.15f, 0.0f,     0.37f, 0.33f, 0.69f,    0.5f, 0.2f,     //3 D
        0.35f, 0.4f, 0.0f,      0.69f, 0.33f, 0.37f,    0.5f, 0.5f,     //4 E
        0.25f, 0.5f, 0.0f,      0.37f, 0.69f, 0.33f,    0.3f, 0.7f,     //5 F

        //T3
        //0.35f, 0.4f, 0.0f,      1.0f, 0.85f, 0.1f,      0.5f, 0.5f,
        0.15f, 0.6f, 0.0f,      0.1f, 0.85f, 1.0f,      0.1f, 0.9f,     //6 G 
        0.55f, 0.6f, 0.0f,      0.85f, 1.0f, 0.1f,      0.9f, 0.9f      //7 H

    };

    float vertices2[] = {

        //T4
        //positions             // colors               //Texture    
        0.35f, 0.6f, 0.0f,      0.0f, 0.8f, 0.27f,      0.1f, 0.1f,     //0 I
        0.75f, 0.6f, 0.0f,      0.0f, 0.27f, 0.8f,      0.5f, 0.1f,     //1 J
        0.55f, 0.8f, 0.0f,      0.8f, 0.27f, 0.0f,      0.3f, 0.3f,     //2 M

        //T5
        //0.55f, 0.8f, 0.0f,      1.0f, 0.3f, 0.3f,       0.3f, 0.3f,
        0.65f, 0.9f, 0.0f,      0.3f, 0.3f, 1.0f,       0.5f, 0.4f,     //3 N
        0.45f, 0.9f, 0.0f,      0.3f, 1.0f, 0.3f,       0.1f, 0.4f,     //4 O
        0.55f, 1.0f, 0.0f,      0.3f, 1.0f, 0.3f,       0.3f, 0.5f,     //5 P

        //T6
        //0.75f, 0.6f, 0.0f,      0.0f, 0.5f, 1.0f,       0.5f, 0.1f,
        0.85f, 0.7f, 0.0f,      0.5f, 0.0f, 1.0f,       0.7f, 0.2f,     //6 K
        0.65f, 0.7f, 0.0f,      0.0f, 1.0f, 0.5f,       0.4f, 0.2f,     //7 L

        //T7
        //0.85f, 0.7f, 0.0f,      0.6f, 0.9f, 0.0f,       0.7f, 0.2f,
        0.85f, 0.9f, 0.0f,      0.0f, 0.9f, 0.6f,       0.7f, 0.4f,     //8 Q
        0.95f, 0.8f, 0.0f,      0.9f, 0.0f, 0.6f,       0.9f, 0.3f      //9 R

    };

    //EBO_ADD

    unsigned int indices1[] = {
      0, 1, 2,
      2, 3, 5,
      3, 4, 5,
      4, 6, 7

    };

    unsigned int indices2[] = {
      0, 1, 2,
      2, 3, 4,
      3, 4, 5,
      1, 6, 7,
      6, 8, 9
    };

    //Se define los VAOs, VBOs y EBOs
    unsigned int VBO[2], VAO[2], EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    // Grupo1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    // atributos de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // atributos de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //atributos de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Grupo2

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    // atributos de posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // atributos de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //atributos de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Texturas
    unsigned int textura1, textura2;

    // textura 1
    glGenTextures(1, &textura1);
    glBindTexture(GL_TEXTURE_2D, textura1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);
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

    // textura 2
    glGenTextures(1, &textura2);
    glBindTexture(GL_TEXTURE_2D, textura2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
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


    ourShader.use();
    ourShader.setInt("texture1", 0);

    // render loop
    //ejecuta el codigo mientras la ventana está abierta
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // color de la ventana 
        glClearColor(1.0f,1.0f,1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Textura 1
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textura1);

       
        // render the triangle
        ourShader.use();
        //funcion cambia el color de las primitivas
        cambiarColor(ourShader);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        // Textura 2
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textura2);

        // render the triangle
        ourShader.use();
        //funcion cambia el color de las primitivas
        cambiarColor(ourShader);

        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Elimina la informacion de los VAOs, VBOs y EBOs
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// Funcion que se encarga de mantener abierta la ventana principal
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Funcion que procesa las medidas de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//funcion para cambiar el color
void cambiarColor(Shader ourshader) {
    float timeValue = glfwGetTime();
    float colorValue = (sin(3.0f) / 2.0f) + 0.5f;
    ourshader.setFloat("cambiarColor", colorValue);
   
}

