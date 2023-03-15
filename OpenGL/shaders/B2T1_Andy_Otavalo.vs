#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float group;

out vec3 ourColor;
out vec2 TexCoord;
out float aGroup;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	aGroup = group;

	//Reutilizamos las coordenadas de posicion para las texturas

	if(group == 0){
			TexCoord = vec2(aPos.x+0.5,aPos.y+0.1);
	}else{
			TexCoord = vec2(aPos.x+0.5,aPos.y+1.0);
	}

	//TexCoord = vec2((aPos.x+1.0)/2.0,(aPos.y+1.0)/2.0);
	
}