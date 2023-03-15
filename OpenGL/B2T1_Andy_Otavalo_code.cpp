#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

//Factor de visibilidad inicial
//float visibilyFactor = 0.0f;
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B2T1_Andy_Otavalo", NULL, NULL);
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
    Shader ourShader("shaders/B2T1_Andy_Otavalo.vs", "shaders/B2T1_Andy_Otavalo.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //Reutilizamos las coordenadas de posicion para las texturas
    float vertices[] = {
        // positions         // colors          //ID Group

       // GRUPO 1
       //Figura 1
       0.0f,0.7f,0.0f,     0.99f,0.4f,0.39f,    0.0f,//0
       -0.2f,0.5f,0.0f,    0.99f,0.4f,0.39f,    0.0f,//1
       0.2f,0.5f,0.0f,     0.99f,0.4f,0.39f,    0.0f,//2
       0.0f,0.3f,0.0f,     0.99f,0.4f,0.39f,    0.0f,//3
       //Figura 2
       0.1f,0.3f,0.0f,     0.99f,0.8f,0.0f,     0.0f,//4     
       -0.3f,0.3f,0.0f,    0.99f,0.8f,0.0f,     0.0f,//5
       0.1f,-0.1f,0.0f,    0.99f,0.8f,0.0f,     0.0f,//6
       //Figura 3
       -0.4f,0.2f,0.0f,    0.4f,0.4f,0.79f,     0.0f,//7
       -0.2f,0.2f,0.0f,    0.4f,0.4f,0.79f,     0.0f,//8
       -0.2f,0.0f,0.0f,    0.4f,0.4f,0.79f,     0.0f,//9
       0.0f,0.0f,0.0f,     0.4f,0.4f,0.79f,     0.0f,//10

       //GRUPO 2
       //Figura 4
       0.0f,0.0f,0.0f,     0.18f,0.8f,0.4f,     1.0f,//11
       0.3f,-0.3f,0.0f,    0.18f,0.8f,0.4f,     1.0f,//12
       0.0f,-0.3f,0.0f,    0.18f,0.8f,0.4f,     1.0f,//13
       //Figura 5
       0.0f,-0.1f,0.0f,    0.59f,0.79f,0.22f,   1.0f,//14
       -0.2f,-0.3f,0.0f,   0.59f,0.79f,0.22f,   1.0f,//15
       0.0f,-0.5f,0.0f,    0.59f,0.79f,0.22f,   1.0f,//16
       //Figura 6
       0.2f,-0.3f,0.0f,    0.2f,0.59f,0.98f,    1.0f,//17
       0.4f,-0.3f,0.0f,    0.2f,0.59f,0.98f,    1.0f,//18
       0.4f,-0.5f,0.0f,    0.2f,0.59f,0.98f,    1.0f,//19
       //Figura 7
       -0.1f,-0.4f,0.0f,   0.99f,0.59f,0.2f,    1.0f,//20
       -0.1f,-0.7f,0.0f,   0.99f,0.59f,0.2f,    1.0f,//21
       0.1f,-0.6f,0.0f,    0.99f,0.59f,0.2f,    1.0f,//22
    };

    unsigned int indices[] = {  // note that we start from 0!

        //Figura 1
        0, 1, 2,
        1, 2, 3,
        //Figura 2     
        4,5,6,
        //Figura 3
        7,8,9,
        8,9,10,
        //Figura 4
        11,12,13,
        //Figura 5
        14,15,16,
        //Figura 6
        17,18,19,
        //Figura 7
        20,21,22,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);





    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);
    //unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);

    if (data){
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);    
    //data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
    if (data){
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
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
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
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //Variable en funcion del tiempo
        float timeValue = glfwGetTime();
        float visibilyFactor = (cos(timeValue)+1)/2;
        ourShader.setFloat("visible", visibilyFactor);
        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}