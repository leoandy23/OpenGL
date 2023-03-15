#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1P3_Andy_Otavalo", NULL, NULL);
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

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("shaders/B1P3_Andy_Otavalo.vs", "shaders/B1P3_Andy_Otavalo.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
        //Figura 1
        0.0f,0.7f,0.0f,     0.99f,0.4f,0.39f,     //0
        -0.2f,0.5f,0.0f,    0.99f,0.4f,0.39f,    //1
        0.2f,0.5f,0.0f,     0.99f,0.4f,0.39f,     //2
        -0.2f,0.5f,0.0f,    0.99f,0.4f,0.39f,    //1
        0.2f,0.5f,0.0f,     0.99f,0.4f,0.39f,     //2
        0.0f,0.3f,0.0f,     0.99f,0.4f,0.39f,     //3
        //Figura 2
        0.1f,0.3f,0.0f,     0.99f,0.8f,0.0f,     //4     
        -0.3f,0.3f,0.0f,    0.99f,0.8f,0.0f,    //5
        0.1f,-0.1f,0.0f,    0.99f,0.8f,0.0f,    //6
        //Figura 3
        -0.4f,0.2f,0.0f,    0.4f,0.4f,0.79f,   //7
        -0.2f,0.2f,0.0f,    0.4f,0.4f,0.79f,   //8
        -0.2f,0.0f,0.0f,    0.4f,0.4f,0.79f,   //9
        -0.2f,0.2f,0.0f,    0.4f,0.4f,0.79f,   //8
        -0.2f,0.0f,0.0f,    0.4f,0.4f,0.79f,   //9
        0.0f,0.0f,0.0f,     0.4f,0.4f,0.79f,    //10
        //Figura 4
        0.0f,0.0f,0.0f,     0.18f,0.8f,0.4f,     //11
        0.3f,-0.3f,0.0f,    0.18f,0.8f,0.4f,    //12
        0.0f,-0.3f,0.0f,    0.18f,0.8f,0.4f,    //13
        //Figura 5
        0.0f,-0.1f,0.0f,    0.59f,0.79f,0.22f,    //14
        -0.2f,-0.3f,0.0f,   0.59f,0.79f,0.22f,   //15
        0.0f,-0.5f,0.0f,    0.59f,0.79f,0.22f,    //16
        //Figura 6
        0.2f,-0.3f,0.0f,    0.2f,0.59f,0.98f,  //17
        0.4f,-0.3f,0.0f,    0.2f,0.59f,0.98f,    //18
        0.4f,-0.5f,0.0f,    0.2f,0.59f,0.98f,    //19
        //Figura 7
        -0.1f,-0.4f,0.0f,   0.99f,0.59f,0.2f,   //20
        -0.1f,-0.7f,0.0f,   0.99f,0.59f,0.2f,   //21
        0.1f,-0.6f,0.0f,    0.99f,0.59f,0.2f,    //22
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();

        //Variable uniform en funcion del tiempo
        float timeValue = glfwGetTime();
        float offValue = cos(timeValue) / 4.0f - 0.25f;
        ourShader.setFloat("offset", offValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 26);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}