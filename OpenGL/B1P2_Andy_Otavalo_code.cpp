#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location=1) in vec3 bPos;\n"
"out vec4 color;"
"void main()\n"
"{\n"
"   color = vec4(bPos,1.0);\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
"in vec4 color;\n"
"out vec4 fcolor;\n"
"void main()\n"
"{\n"
"   fcolor = vec4(color);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica P1B1", NULL, NULL);
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
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //Colores
    float color[] =
    {
        //Figura 1
        0.99f,0.4f,0.39f,1.0f,
        0.99f,0.4f,0.39f,1.0f,
        0.99f,0.4f,0.39f,1.0f,
        0.99f,0.4f,0.39f,1.0f,
        //Figura 2
        0.99f,0.8f,0.0f, 1.0f,
        0.99f,0.8f,0.0f, 1.0f,
        0.99f,0.8f,0.0f, 1.0f,
        //Figura 3
        0.4f,0.4f,0.79f,1.0f,
        0.4f,0.4f,0.79f,1.0f,
        0.4f,0.4f,0.79f,1.0f,
        0.4f,0.4f,0.79f,1.0f,
        //Figura 4
        0.18f,0.8f,0.4f,1.0f,
        0.18f,0.8f,0.4f,1.0f,
        0.18f,0.8f,0.4f,1.0f,
        //Figura 5
        0.59f,0.79f,0.22f,1.0f,
        0.59f,0.79f,0.22f,1.0f,
        0.59f,0.79f,0.22f,1.0f,
        //Figura 6
        0.2f,0.59f,0.98f,1.0f,
        0.2f,0.59f,0.98f,1.0f,
        0.2f,0.59f,0.98f,1.0f,
        //Figura 7
        0.99f,0.59f,0.2f,1.0f,
        0.99f,0.59f,0.2f,1.0f,
        0.99f,0.59f,0.2f,1.0f,
    };

    float vertices[] = {
        //Figura 1
        0.0f,0.7f,0.0f,     //0
        -0.2f,0.5f,0.0f,    //1
        0.2f,0.5f,0.0f,     //2
        0.0f,0.3f,0.0f,     //3
        //Figura 2
        0.1f,0.3f,0.0f,     //4     
        -0.3f,0.3f,0.0f,    //5
        0.1f,-0.1f,0.0f,    //6
        //Figura 3
        -0.4f,0.2f,0.0f,    //7
        -0.2f,0.2f,0.0f,    //8
        -0.2f,0.0f,0.0f,    //9
        0.0f,0.0f,0.0f,     //10
        //Figura 4
        //No se puede reutilizar el Vertice 10 por que tiene configurado el color anterior
        0.0f,0.0f,0.0f,     //11
        0.3f,-0.3f,0.0f,    //12
        0.0f,-0.3f,0.0f,    //13
        //Figura 5
        0.0f,-0.1f,0.0f,    //14
        -0.2f,-0.3f,0.0f,   //15
        0.0f,-0.5f,0.0f,    //16
        //Figura 6
        0.2f,-0.3f,0.0f,    //17
        0.4f,-0.3f,0.0f,    //18
        0.4f,-0.5f,0.0f,    //19
        //Figura 7
        -0.1f,-0.4f,0.0f,   //20
        -0.1f,-0.7f,0.0f,   //21
        0.1f,-0.6f,0.0f,    //22
    };

    //EBO_ADD
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
        //FIgura 6
        17,18,19,
        //Figura 7
        20,21,22,
    };

    //EBO_MODIFY
    //unsigned int VBO, VAO;
    unsigned int VBO[2], VAO, EBO;
    //

    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);

    //EBO_ADD
    glGenBuffers(1, &EBO);
    //

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //EBO_ADD
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // enlazar el buffer de color
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    // almacenar datos en el buffer de color
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    // describir los datos y activar vColor (location = 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(1);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //EBO_ADD
     // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //set to zero effectively unbinds any buffer object previously bound



    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        //EBO_MODIFY
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, VBO);

    //EBO_ADD
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}