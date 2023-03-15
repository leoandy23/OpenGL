//Importacion de librerias
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//Prototipos de los metodos
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Variables del ancho y alto de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


//Creacion de la variables donde se guardan los codigo fuente del vertex y fragment shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Asignamos un color en RGB normalizado al triangulo
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.1f, 0.9f, 1.0f);\n"
"}\n\0";

//Metodo Main
int main()
{
    //Inicializa la libreria glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    //Creamos la ventana con las dimensiones definidas anteriormente
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "First Triangle", NULL, NULL);

    //Verificamos que la ventana se haya creado correctamente
    if (window == NULL)
    {
        //Mostrar el error de ser el caso
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Hacer que el contexto de la ventana sea actual
    glfwMakeContextCurrent(window);

    //Esta función establece la devolución de llamada de cambio de tamaño del búfer de fotogramas 
    //de la ventana especificada, que se llama cuando se cambia el tamaño del búfer de fotogramas 
    //de la ventana especificada.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //Creamos un shader y como parametro especificamos que tipo de shader es
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Agregamos el codigo fuente del shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //Compilamos el codigo fuente del shader
    glCompileShader(vertexShader);

    //Comprobamos si la compilacion fue exitosa o no
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Creamos un shader de tipo fragment
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Agregamos el codigo fuente del fragment shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //Compilamos el codigo fuente del fragment shader
    glCompileShader(fragmentShader);

    //verificamos si la compilación del fragment shader es exitosa o no
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Crea un objeto de programa vacío y devuelve un valor distinto de cero 
    //mediante el cual se puede hacer referencia a él.
    int shaderProgram = glCreateProgram();

    //Adjunta el objeto shader especificado por shader al objeto del programa
    //especificado por program. Esto indica que el sombreador se incluirá en 
    //las operaciones de enlace que se realizarán en el programa.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    //Ejecuta los programas dependiendo de que shaders se hayan añadido al programa
    //en este caso se añadieron Vertex y Fragment shaders
    glLinkProgram(shaderProgram);

    //Verificamos que el programa se haya creado exitosamente
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Eliminamos los shaders creados, para limpiar la memoria
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //Arreglo de vertices del triangulo a crear
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.1f, -0.5f, 0.0f, // right 
         0.0f,  0.7f, 0.0f  // top   
    };


    unsigned int VBO, VAO;
    //Devuelve n nombres de objetos de matriz de vértices en matrices.
    glGenVertexArrays(1, &VAO);
    //Devuelve n nombres de objetos de búfer en búferes.
    glGenBuffers(1, &VBO);
    //Une los vertices que contiene el VAO
    glBindVertexArray(VAO);
    //Une los buffers que contiene VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Crea un nuevo almacén de datos para un objeto de búfer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //Especifica la ubicación y el formato de datos de la matriz de atributos 
    //de vértice genéricos en el índice de índice para usar al renderizar.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Habilita la matriz de atributos de vértice genérico especificada por índice
    glEnableVertexAttribArray(0);
    //Vacia el buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //Vacia el array de vertices
    glBindVertexArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //Si precionamos esc se cierra la ventana
        processInput(window);

        //Configuramos el color de fondo en rgb normalizado
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //Usamos el programa creado
        glUseProgram(shaderProgram);
        //Unimos los vertices
        glBindVertexArray(VAO); 
        //Dibujamos el triangulo
        glDrawArrays(GL_TRIANGLES, 0, 3);


        //Limpiamos todos los buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}