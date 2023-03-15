#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform float cambiarColor;


//funcion para cambiar el color 
void main()
{
        //FragColor = (vec4(ourColor, 1.0f) + cambiarColor)/2;
        FragColor = mix(texture(texture1, TexCoord), vec4(ourColor, 1.0), cambiarColor);
}







    
   
