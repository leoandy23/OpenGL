#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//Funciones ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ancho y alto ventana
const unsigned int SCR_WIDTH = 800; //ancho de la ventana
const unsigned int SCR_HEIGHT = 800; //alto de la ventana

//Vertex shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //posicion de la imagen
"}\0";

//Fragment shaders

//Figura 1
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4( 0.99f,0.4f,0.39f,1.0f);\n"
"}\n\0";

//Figura 2
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.99f,0.8f,0.0f, 1.0f);\n"
"}\n\0";

//Figura 3
const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.4f,0.4f,0.79f,1.0f);\n"
"}\n\0";

//Figura 4
const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.18f,0.8f,0.4f,1.0f);\n"
"}\n\0";

//Figura 5
const char* fragmentShader5Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.59f,0.79f,0.22f,1.0f);\n"
"}\n\0";

//Figura 6
const char* fragmentShader6Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f,0.59f,0.98f,1.0f);\n"
"}\n\0";

//Figura 7
const char* fragmentShader7Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.99f,0.59f,0.2f,1.0f);\n"
"}\n\0";

int main()
{
    // inicializacion de las librerias glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //OS X
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif

    // creacion de la ventana glfw
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1P2_Andy_Otavalo", NULL, NULL);

    // cierra la ventana en caso que esta no
    //se haya creado correctamente
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Termina la ejecución si la inicializacion 
    //de los punteros de OpenGL con GLAD sea erronea
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //creacion de un Vertex Shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //verifica el vertex shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // envia un mensaje si encuentra fallos al compilar el Vertex Shader
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //creacion de fragment shader
    //Figura 1
    int fragmentShaderF1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF1, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderF1);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF1, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Figura 2
    int fragmentShaderF2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF2, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderF2);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Figura 3
    int fragmentShaderF3 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF3, 1, &fragmentShader3Source, NULL);
    glCompileShader(fragmentShaderF3);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF3, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF3, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Figura 4
    int fragmentShaderF4 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF4, 1, &fragmentShader4Source, NULL);
    glCompileShader(fragmentShaderF4);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF4, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF4, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Figura 5
    int fragmentShaderF5 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF5, 1, &fragmentShader5Source, NULL);
    glCompileShader(fragmentShaderF5);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF5, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF5, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Figura 6
    int fragmentShaderF6 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF6, 1, &fragmentShader6Source, NULL);
    glCompileShader(fragmentShaderF6);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF6, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF6, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Figura 7
    int fragmentShaderF7 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderF7, 1, &fragmentShader7Source, NULL);
    glCompileShader(fragmentShaderF7);
    // Verifica la creación del fragment shader
    glGetShaderiv(fragmentShaderF7,GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderF7,512,NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Shader Programs
    //Figura 1
    int shaderProgramF1 = glCreateProgram();
    glAttachShader(shaderProgramF1, vertexShader);
    glAttachShader(shaderProgramF1, fragmentShaderF1);
    glLinkProgram(shaderProgramF1);
    // Verifica la ejecución del program
    glGetProgramiv(shaderProgramF1, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Figura 2
    int shaderProgramF2 = glCreateProgram();
    glAttachShader(shaderProgramF2, vertexShader);
    glAttachShader(shaderProgramF2, fragmentShaderF2);
    glLinkProgram(shaderProgramF2);
    // Verifica la ejecución del program
    glGetProgramiv(shaderProgramF2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Figura 3
    int shaderProgramF3 = glCreateProgram();
    glAttachShader(shaderProgramF3, vertexShader);
    glAttachShader(shaderProgramF3, fragmentShaderF3);
    glLinkProgram(shaderProgramF3);
    // Verifica la ejecución del program 
    glGetProgramiv(shaderProgramF3, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF3, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Figura 4
    int shaderProgramF4 = glCreateProgram();
    glAttachShader(shaderProgramF4, vertexShader);
    glAttachShader(shaderProgramF4, fragmentShaderF4);
    glLinkProgram(shaderProgramF4);
    // Verifica la ejecución del program 
    glGetProgramiv(shaderProgramF4, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF4, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Figura 5
    int shaderProgramF5 = glCreateProgram();
    glAttachShader(shaderProgramF5, vertexShader);
    glAttachShader(shaderProgramF5, fragmentShaderF5);
    glLinkProgram(shaderProgramF5);
    // Verifica la ejecución del program 
    glGetProgramiv(shaderProgramF5, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF5, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Figura 6
    int shaderProgramF6 = glCreateProgram();
    glAttachShader(shaderProgramF6, vertexShader);
    glAttachShader(shaderProgramF6, fragmentShaderF6);
    glLinkProgram(shaderProgramF6);
    // Verifica la ejecución del program 
    glGetProgramiv(shaderProgramF6, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF6, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Figura 7
    int shaderProgramF7 = glCreateProgram();
    glAttachShader(shaderProgramF7, vertexShader);
    glAttachShader(shaderProgramF7, fragmentShaderF7);
    glLinkProgram(shaderProgramF7);
    // Verifica la ejecución del program
    glGetProgramiv(shaderProgramF7, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramF7, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Elimina los vertex y fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderF1);
    glDeleteShader(fragmentShaderF2);
    glDeleteShader(fragmentShaderF3);
    glDeleteShader(fragmentShaderF4);
    glDeleteShader(fragmentShaderF5);
    glDeleteShader(fragmentShaderF6);
    glDeleteShader(fragmentShaderF7);

    //Vertices de cada figura
    float vertexs1[] = {
        //Figura 1
          0.0f,0.7f,0.0f,     //0
          -0.2f,0.5f,0.0f,    //1
          0.2f,0.5f,0.0f,     //2
          0.0f,0.3f,0.0f,     //3
    };

    float vertexs2[] = {
        //Figura 2
          0.1f,0.3f,0.0f,     //4     
          -0.3f,0.3f,0.0f,    //5
          0.1f,-0.1f,0.0f,    //6
    };


    float vertexs3[] = {
        //Figura 3
          -0.4f,0.2f,0.0f,    //7
          -0.2f,0.2f,0.0f,    //8
          -0.2f,0.0f,0.0f,    //9
          0.0f,0.0f,0.0f,     //10
    };
 
    float vertexs4[] = {
        //Figura 4
         0.0f,0.0f,0.0f,     //11
         0.3f,-0.3f,0.0f,    //12
         0.0f,-0.3f,0.0f,    //13
    };

 
    float vertexs5[] = {
        //Figura 5
         0.0f,-0.1f,0.0f,    //14
         -0.2f,-0.3f,0.0f,   //15
         0.0f,-0.5f,0.0f,    //16
    };

    float vertexs6[] = {
        //Figura 6
          0.2f,-0.3f,0.0f,    //17
          0.4f,-0.3f,0.0f,    //18
          0.4f,-0.5f,0.0f,    //19
    };

    float vertexs7[] = {
        //Figura 7
          -0.1f,-0.4f,0.0f,   //20
          -0.1f,-0.7f,0.0f,   //21
          0.1f,-0.6f,0.0f,    //22
    };

    //EBO_ADD
    unsigned int indices1[] = {  
      0, 1, 2, 
      1, 2, 3
    };

    unsigned int indices2[] = {
      0, 1, 2,
      1,2,3
    };

   // VBO, VAO, EBO
    unsigned int VBO[7], VAO[7], EBO[2];
    glGenVertexArrays(7, VAO);
    glGenBuffers(7, VBO);
    glGenBuffers(2, EBO);

    //Figura 1
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs1), vertexs1, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Figura 2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs2), vertexs2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //Figura 3
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs3), vertexs3, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Figura 4
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs4), vertexs4, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Figura 5
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs5), vertexs5, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //Figura 6
    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs6), vertexs6, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Figura 7
    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs7), vertexs7, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //Se puede descomentar para que solo me grafique las lineas de las figuras
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        //Color de fondo de la ventana
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Dibujo de los triangulos
        //Figura 1
        glUseProgram(shaderProgramF1);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Figura 2
        glUseProgram(shaderProgramF2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Figura 3
        glUseProgram(shaderProgramF3);
        glBindVertexArray(VAO[2]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Figura 4
        glUseProgram(shaderProgramF4);
        glBindVertexArray(VAO[3]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Figura 5
        glUseProgram(shaderProgramF5);
        glBindVertexArray(VAO[4]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Figura 6
        glUseProgram(shaderProgramF6);
        glBindVertexArray(VAO[5]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Figura 7
        glUseProgram(shaderProgramF7);
        glBindVertexArray(VAO[6]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // elimina VAO, VBO y EBO
    glDeleteVertexArrays(7, VAO);
    glDeleteBuffers(7, VBO);
    glDeleteBuffers(2, EBO);

    // Termina borrando todos los recursos GLFW previamente asignados
    glfwTerminate();
    return 0;
}

// mantiene abierta la ventana principal
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// procesa las medidas de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}