#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float Group;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	if(Group==0){
	FragColor = texture(texture1, TexCoord);
	}
	
	if(Group==1){
	FragColor = texture(texture2, TexCoord);
	}
	if(Group==2){
	FragColor = texture(texture3, TexCoord);
	}

	if(Group==3){
	FragColor = texture(texture4, TexCoord);
	}
	
}
