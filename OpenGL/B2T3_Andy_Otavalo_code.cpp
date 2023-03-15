#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Exercise 12 Task 4
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B2T3_Andy_Otavalo", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    //Exercise 11 Task 3
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/B2T3_Andy_Otavalo.vs", "shaders/B2T3_Andy_Otavalo.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //0.1f, 0.6f, 0.0f,     //0
    //0.4f, 0.6f, 0.0f,     //1
    //0.1f, 0.9f, 0.0f,     //2
    //0.4f, 0.9f, 0.0f,     //3
    //0.1f, 0.6f, 0.3f,    //4
    //0.4f, 0.6f, 0.3f,    //5
    //0.1f,  0.9f, 0.3f,   //6
    //0.4f,  0.9f, 0.3f,   //7
    float vertices[] = {
         // positions           // texture coords

         //Figura 1
         //Cara - Frente
         0.0f, 0.6f, 0.0f,      494.0f,314.0f,   0.0f,//0
         0.4f, 0.6f, 0.0f,      653.0f,314.0f,   0.0f,//1
         0.0f,  1.0f, 0.0f,     494.0f,425.0f,   0.0f,//2
         0.4f, 0.6f, 0.0f,      653.0f,314.0f,   0.0f,//1
         0.0f,  1.0f, 0.0f,     494.0f,425.0f,   0.0f,//2
         0.4f,  1.0f, 0.0f,     653.0f,425.0f,   0.0f,//3

         //Cara - Atras
         0.0f, 0.6f, 0.4f,      336.0f,317.0f,   0.0f,//4
         0.4f, 0.6f, 0.4f,      175.0f,317.0f,   0.0f,//5
         0.0f,  1.0f, 0.4f,     336.0f,425.0f,   0.0f,//6
         0.4f, 0.6f, 0.4f,      175.0f,317.0f,   0.0f,//5
         0.0f,  1.0f, 0.4f,     336.0f,425.0f,   0.0f,//6
         0.4f,  1.0f, 0.4f,     175.0,428.0f,    0.0f,//7

         //Cara - Derecha
         0.4f, 0.6f, 0.0f,      653.0f, 314.0f,  0.0f,//1
         0.4f, 1.0f, 0.0f,      653.0f, 425.0f,  0.0f,//3
         0.4f, 0.6f, 0.4f,      807.0f, 314.0f,  0.0f,//5
         0.4f, 1.0f, 0.0f,      653.0f, 425.0f,  0.0f,//3
         0.4f, 0.6f, 0.4f,      807.0f, 314.0f,  0.0f,//5
         0.4f,  1.0f, 0.4f,     807.0f, 425.0f,  0.0f,//7

         //Cara - Izquierda
         0.0f, 0.6f, 0.0f,      494.0f,314.0f,   0.0f,//0
         0.0f,  1.0f, 0.0f,     494.0f,425.0f,   0.0f,//2
         0.0f, 0.6f, 0.4f,      336.0f,317.0f,   0.0f,//4
         0.0f,  1.0f, 0.0f,     494.0f,425.0f,   0.0f,//2
         0.0f, 0.6f, 0.4f,      336.0f,317.0f,   0.0f,//4
         0.0f,  1.0f, 0.4f,     336.0f,425.0f,   0.0f,//6

         //Cara - Abajo
         0.0f, 0.6f, 0.0f,      494.0f,314.0f,   0.0f,//0
         0.4f, 0.6f, 0.0f,      653.0f,314.0f,   0.0f,//1
         0.0f, 0.6f, 0.3f,      494.0f,156.0f,   0.0f,//4
         0.4f, 0.6f, 0.0f,      653.0f,314.0f,   0.0f,//1
         0.0f, 0.6f, 0.4f,      494.0f,156.0f,   0.0f,//4
         0.4f, 0.6f, 0.4f,      653.0f,156.0f,   0.0f,//5

         //Cara - Arriba
         0.0f,  1.0f, 0.0f,     494.0f,425.0f,   0.0f,//2
         0.4f,  1.0f, 0.0f,     653.0f,425.0f,   0.0f,//3
         0.0f,  1.0f, 0.4f,     494.0f,586.0f,   0.0f,//6
         0.4f,  1.0f, 0.0f,     653.0f,425.0f,   0.0f,//3
         0.0f,  1.0f, 0.4f,     494.0f,586.0f,   0.0f,//6
         0.4f,  1.0f, 0.4f,     653.0f,586.0f,   0.0f,//7

         //-----------------------------------------------------------------
         //Figura 2
         //Cara - Frente
         -0.2f,-0.2f,0.0f,      152.0f,156.0f,   1.0f,//0
         0.2f,-0.2f,0.0f,       272.0f,156.0f,   1.0f,//1
         -0.2f,0.2f,0.0f,       152.0f,275.0f,   1.0f,//2
         0.2f,-0.2f,0.0f,       272.0f,156.0f,   1.0f,//1
         -0.2f,0.2f,0.0f,       152.0f,275.0f,   1.0f,//2
         0.2f,0.2f,0.0f,        272.0f,275.0f,   1.0f,//3

         //Cara - Atras
         -0.2f,-0.2f,0.4f,      512.0f,155.0f,   1.0f,//4
         0.2f,-0.2f,0.4f,       393.0f,155.0f,   1.0f,//5
         -0.2f,0.2f,0.4f,       512.0f,275.0f,   1.0f,//6
         0.2f,-0.2f,0.4f,       393.0f,155.0f,   1.0f,//5
         -0.2f,0.2f,0.4f,       512.0f,275.0f,   1.0f,//6
         0.2f,0.2f,0.4f,        393.0f,275.0f,   1.0f,//7

         //Cara - Derecha 
         0.2f,-0.2f,0.0f,       272.0f, 156.0f,  1.0f,//1
         0.2f,0.2f,0.0f,        272.0f, 275.0f,  1.0f,//3
         0.2f,-0.2f,0.4f,       393.0f, 156.0f,  1.0f,//5
         0.2f,0.2f,0.0f,        272.0f, 275.0f,  1.0f,//3
         0.2f,-0.2f,0.4f,       393.0f, 156.0f,  1.0f,//5
         0.2f,0.2f,0.4f,        393.0f, 275.0f,  1.0f,//7

         //Cara - Izquierda
         -0.2f,-0.2f,0.0f,      152.0f,156.0f,   1.0f,//0
         -0.2f,0.2f,0.0f,       152.0f,275.0f,   1.0f,//2
         -0.2f,-0.2f,0.4f,      31.0f,156.0f,    1.0f,//4
         -0.2f,0.2f,0.0f,       152.0f,275.0f,   1.0f,//2
         -0.2f,-0.2f,0.4f,      31.0f,156.0f,    1.0f,//4
         -0.2f,0.2f,0.4f,       31.0f,275.0f,    1.0f,//6

         //Cara - Abajo
         -0.2f,-0.2f,0.0f,      152.0f,156.0f,   1.0f,//0
         0.2f,-0.2f,0.0f,       272.0f,156.0f,   1.0f,//1
         -0.2f,-0.2f,0.4f,      152.0f,36.0f,    1.0f,//4
         0.2f,-0.2f,0.0f,       272.0f,156.0f,   1.0f,//1
         -0.2f,-0.2f,0.4f,      152.0f,36.0f,    1.0f,//4
         0.2f,-0.2f,0.4f,       272.0f,36.0f,    1.0f,//5

         //Cara - Arriba
         -0.2f,0.2f,0.0f,       152.0f,275.0f,   1.0f,//2
         0.2f,0.2f,0.0f,        272.0f,275.0f,   1.0f,//3
         -0.2f,0.2f,0.4f,       152.0f,396.0f,   1.0f,//6
         0.2f,0.2f,0.0f,        272.0f,275.0f,   1.0f,//3
         -0.2f,0.2f,0.4f,       152.0f,396.0f,   1.0f,//6
         0.2f,0.2f,0.4f,        272.0f,396.0f,   1.0f,//7

         //-----------------------------------------------------------------
         ////Figura 3
         //Cara - Frente
         -0.6f, 0.1f, 0.0f,     165.0f, 137.0f,  2.0f,//0
         -0.2f, 0.1f, 0.0f,     291.0f, 137.0f,  2.0f,//1
         -0.6f, 0.5f, 0.0f,     165.0f, 262.0f,  2.0f,//2
         -0.2f, 0.1f, 0.0f,     291.0f, 137.0f,  2.0f,//1
         -0.6f, 0.5f, 0.0f,     165.0f, 262.0f,  2.0f,//2
         -0.2f, 0.5f, 0.0f,     291.0f, 262.0f,  2.0f,//3
         
         //Cara - Atras
         -0.6f, 0.1f, 0.4f,     540.0f, 137.0f,  2.0f,//4
         -0.2f, 0.1f, 0.4f,     417.0f, 137.0f,  2.0f,//5
         -0.6f, 0.5f, 0.4f,     540.0f, 262.0f,  2.0f,//6
         -0.2f, 0.1f, 0.4f,     417.0f, 137.0f,  2.0f,//5
         -0.6f, 0.5f, 0.4f,     540.0f, 262.0f,  2.0f,//6
         -0.2f, 0.5f, 0.4f,     417.0, 262.0f,   2.0f,//7
                                
         //Cara - Derecha       
         -0.2f, 0.1f, 0.0f,     291.0f, 137.0f,  2.0f,//1
         -0.2f, 0.5f, 0.0f,     291.0f, 262.0f,  2.0f,//3
         -0.2f, 0.1f, 0.4f,     417.0f, 137.0f,  2.0f,//5
         -0.2f, 0.5f, 0.0f,     291.0f, 262.0f,  2.0f,//3
         -0.2f, 0.1f, 0.4f,     417.0f, 137.0f,  2.0f,//5
         -0.2f, 0.5f, 0.4f,     417.0f, 262.0f,  2.0f,//7
                                                 
         //Cara - Izquierda                      
         -0.6f, 0.1f, 0.0f,     165.0f, 137.0f,  2.0f,//0
         -0.6f, 0.5f, 0.0f,     165.0f, 262.0f,  2.0f,//2
         -0.6f, 0.1f, 0.4f,     41.0f, 137.0f,   2.0f,//4
         -0.6f, 0.5f, 0.0f,     165.0f, 262.0f,  2.0f,//2
         -0.6f, 0.1f, 0.4f,     41.0f, 137.0f,   2.0f,//4
         -0.6f, 0.5f, 0.4f,     41.0f, 262.0f,   2.0f,//6
                                                 
         //Cara - Abajo                          
         -0.6f, 0.1f, 0.0f,     165.0f, 137.0f,  2.0f,//0
         -0.2f, 0.1f, 0.0f,     291.0f, 137.0f,  2.0f,//1
         -0.6f, 0.1f, 0.4f,     165.0f, 12.0f,   2.0f,//4
         -0.2f, 0.1f, 0.0f,     291.0f, 137.0f,  2.0f,//1
         -0.6f, 0.1f, 0.4f,     165.0f, 12.0f,   2.0f,//4
         -0.2f, 0.1f, 0.4f,     291.0f, 12.0f,   2.0f,//5
                                                 
         //Cara - Arriba                         
         -0.6f, 0.5f, 0.0f,     165.0f, 262.0f,  2.0f,//2
         -0.2f, 0.5f, 0.0f,     291.0f, 262.0f,  2.0f,//3
         -0.6f, 0.5f, 0.4f,     165.0f, 387.0f,  2.0f,//6
         -0.2f, 0.5f, 0.0f,     291.0f, 262.0f,  2.0f,//3
         -0.6f, 0.5f, 0.4f,     165.0f, 387.0f,  2.0f,//6
         -0.2f, 0.5f, 0.4f,     291.0f, 387.0f,  2.0f,//7

        //-----------------------------------------------------------------
         ////Figura 4
         ////Cara - Frente
             -0.5f, 0.1f, 0.0f, 137.0f, 116.0f, 3.0f,//0
             -0.2f, 0.1f, 0.0f, 262.0f, 116.0f, 3.0f,//1
             -0.5f, 0.4f, 0.0f, 137.0f, 241.0f, 3.0f,//2
             -0.2f, 0.1f, 0.0f, 262.0f, 116.0f, 3.0f,//1
             -0.5f, 0.4f, 0.0f, 137.0f, 241.0f, 3.0f,//2
             -0.2f, 0.4f, 0.0f, 262.0f, 241.0f, 3.0f,//3

             //Cara - Atras
             -0.5f, 0.1f, 0.3f, 512.0f, 116.0f, 3.0f,//4
             -0.2f, 0.1f, 0.3f, 387.0f, 116.0f, 3.0f,//5
             -0.5f, 0.4f, 0.3f, 512.0f, 241.0f, 3.0f,//6
             -0.2f, 0.1f, 0.3f, 387.0f, 116.0f, 3.0f,//5
             -0.5f, 0.4f, 0.3f, 512.0f, 241.0f, 3.0f,//6
             -0.2f, 0.4f, 0.3f, 387.0f, 241.0f, 3.0f,//7

             //Cara - Derecha       
             -0.2f, 0.1f, 0.0f, 262.0f, 116.0f, 3.0f,//1
             -0.2f, 0.4f, 0.0f, 262.0f, 241.0f, 3.0f,//3
             -0.2f, 0.1f, 0.3f, 387.0f, 116.0f, 3.0f,//5
             -0.2f, 0.4f, 0.0f, 262.0f, 241.0f, 3.0f,//3
             -0.2f, 0.1f, 0.3f, 387.0f, 116.0f, 3.0f,//5
             -0.2f, 0.4f, 0.3f, 387.0f, 241.0f, 3.0f,//7

             //Cara - Izquierda                      
             -0.5f, 0.1f, 0.0f, 137.0f, 116.0f, 3.0f,//0
             -0.5f, 0.4f, 0.0f, 137.0f, 241.0f, 3.0f,//2
             -0.5f, 0.1f, 0.3f, 12.0f, 116.0f,  3.0f,//4
             -0.5f, 0.4f, 0.0f, 137.0f, 241.0f, 3.0f,//2
             -0.5f, 0.1f, 0.3f, 12.0f, 116.0f,  3.0f,//4
             -0.5f, 0.4f, 0.3f, 12.0f, 241.0f,  3.0f,//6

             //Cara - Abajo                          
             -0.5f, 0.1f, 0.0f, 137.0f, 116.0f, 3.0f,//0
             -0.2f, 0.1f, 0.0f, 262.0f, 116.0f, 3.0f,//1
             -0.5f, 0.1f, 0.3f, 137.0f, 0.0f,   3.0f,//4
             -0.2f, 0.1f, 0.0f, 262.0f, 116.0f, 3.0f,//1
             -0.5f, 0.1f, 0.3f, 137.0f, 0.0f,   3.0f,//4
             -0.2f, 0.1f, 0.3f, 262.0f, 0.0f,   3.0f,//5

             //Cara - Arriba                         
             -0.5f, 0.4f, 0.0f, 137.0f, 241.0f, 3.0f,//2
             -0.2f, 0.4f, 0.0f, 262.0f, 241.0f, 3.0f,//3
             -0.5f, 0.4f, 0.3f, 137.0f, 366.0f, 3.0f,//6
             -0.2f, 0.4f, 0.0f, 262.0f, 241.0f, 3.0f,//3
             -0.5f, 0.4f, 0.3f, 137.0f, 366.0f, 3.0f,//6
             -0.2f, 0.4f, 0.3f, 262.0f, 366.0f, 3.0f,//7
                                                 
           
        
    };

    //Figura 2 Coordenadas
    //-0.2f,-0.2f,0.0f,  //0
    //0.2f,-0.2f,0.0f,   //1
    //-0.2f,0.2f,0.0f,  //2
    //0.2f,0.2f,0.0f,   //3
    //-0.2f,-0.2f,0.4f,  //4
    //0.2f,-0.2f,0.4f,   //5
    //-0.2f,0.2f,0.4f,  //6
    //0.2f,0.2f,0.4f,   //7

    //Figura 3
    //-0.5f,0.1f,0.0f,  //0  -
    //-0.2f,0.1f,0.0f,   //1 -
    //-0.5f,0.4f,0.0f,  //2 -
    //-0.2f,0.4f,0.0f,   //3 -
    //-0.5f,0.1f,0.3f,  //4 -
    //-0.2f,0.1f,0.3f,   //5 -
    //-0.5f,0.4f,0.3f,  //6 -
    //-0.2f,0.4f,0.3f,   //7


    // world space positions of our cubes
    unsigned int nblocks = 33;
    glm::vec3 cubePositions[] = {
        //Figura 1
        glm::vec3(0.0f,  0.0f,  0.0f),

        //Figura 2
        glm::vec3(-0.7f,  0.8,0.0f),
        glm::vec3(0.3f,0.8f, 0.0f),
        glm::vec3(-0.2f,1.3f, 0.0f),

        //Figura 3
        glm::vec3(-0.6f,0.1f, 0.0f),
        glm::vec3(-0.6f,0.1f, -0.4f),
        glm::vec3(-0.6f,0.1f, 0.4f),
        glm::vec3(-0.6f,0.1f, -0.8f),
        glm::vec3(-0.6f,0.1f, 0.8f),
        glm::vec3(-1.0f,0.1f, 0.0f),
        glm::vec3(-1.0f,0.1f, -0.4f),
        glm::vec3(-1.0f,0.1f, 0.4f),
        glm::vec3(-1.0f,0.1f, -0.8f),
        glm::vec3(-1.0f,0.1f, 0.8f),
        glm::vec3(-0.2f,0.1f, 0.0f),
        glm::vec3(-0.2f,0.1f, -0.4f),
        glm::vec3(-0.2f,0.1f, 0.4f),
        glm::vec3(-0.2f,0.1f, -0.8f),
        glm::vec3(-0.2f,0.1f, 0.8f),
        glm::vec3(0.2f,0.1f, 0.0f),
        glm::vec3(0.2f,0.1f, -0.4f),
        glm::vec3(0.2f,0.1f, 0.4f),
        glm::vec3(0.2f,0.1f, -0.8f),
        glm::vec3(0.2f,0.1f, 0.8f),
        glm::vec3(-1.4f,0.1f, 0.0f),
        glm::vec3(-1.4f,0.1f, -0.4f),
        glm::vec3(-1.4f,0.1f, 0.4f),
        glm::vec3(-1.4f,0.1f, -0.8f),
        glm::vec3(-1.4f,0.1f, 0.8f),

        //Figura 4
        glm::vec3(1.3f,0.5f,-1.2f),
        glm::vec3(1.3f,0.5f,1.1f),
        glm::vec3(-1.0f,0.5f,-1.2f),
        glm::vec3(-1.0f,0.5f,1.1f),

        
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //ID group
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2,texture3,texture4;
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
    unsigned char* data = stbi_load("textures/Texture5.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
    data = stbi_load("textures/TextureEx.jpg", &width, &height, &nrChannels, 0);    if (data)
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

    // texture 3
   // ---------
   // ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/TextureEx2.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);


    // texture 4
   // ---------
   // ---------
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/TextureEx3.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
    ourShader.setInt("texture3", 2);
    ourShader.setInt("texture4", 3);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        float stime = sin((float)glfwGetTime())/2.0;
        float ctime = cos((float)glfwGetTime()) / 2.0 + 0.5;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f,abs(ctime), 0.5f, 1.0f);



        //glClear(GL_COLOR_BUFFER_BIT);
        //Exercise 11 Task 3
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);

        // activate shader
        ourShader.use();

        //Exercise 12 Task 3
        // pass projection matrix to shader (note that in this case it could change every frame)

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);

        //glDrawArrays(GL_TRIANGLES, 0, 76);

        for (unsigned int i = 0; i < nblocks; i++)
        {

            // calculate the model matrix for each object and pass it to shader before drawing
           
            if (i == 0) {
                glm::vec3 cubeOffset(cubePositions[i][0], cubePositions[i][1] + (ctime * 1.5), cubePositions[i][2]);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubeOffset);
                float angle = 180.0;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            if (i >= 1 && i <= 3) {
                glm::vec3 cubeOffset(cubePositions[i][0], cubePositions[i][1], cubePositions[i][2] + (stime*1.5));
                //cubePositions[i][2] = cubePositions[i][2] + (ctime*0.001);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubeOffset);
                float angle = 180.0f;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 36, 36);
            }
            

            if(i >= 4 && i<=28 ) {
                glm::mat4 model = glm::mat4(1.0f);
                
                model = glm::translate(model, cubePositions[i]);
                float angle = 180.0f;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES,72,36);
            }

            if (i >= 29) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 180.0f;
                float senT = sin((float)glfwGetTime());
                model = glm::scale(model, glm::vec3(-1.0F, senT,1.0f));
                model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.8f, 0.0f));
                ourShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 108, 36);
            }


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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}