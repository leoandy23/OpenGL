#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aGroup;

out float Group;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Group = aGroup;
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	if(Group==0){
		TexCoord = vec2(aTexCoord.x/874.0, aTexCoord.y/637.0);
	}
	
	if(Group==1){
		TexCoord = vec2(aTexCoord.x/588.0, aTexCoord.y/415.0);
	}

	if(Group==2){
		TexCoord = vec2(aTexCoord.x/561.0, aTexCoord.y/413.0);
	}
	
	if(Group==3){
	TexCoord = vec2(aTexCoord.x/518.0, aTexCoord.y/367.0);
	}
	
}