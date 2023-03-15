#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float aGroup;
in vec3 fcolor;
// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visible;

void main()
{
	if(aGroup==0){
		FragColor = mix(texture(texture1, TexCoord),vec4(fcolor,1.0),visible);
	}
	
	if(aGroup==1){
		FragColor = texture(texture2, TexCoord);
	}	
	
	if(aGroup==2){
		FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord),visible);
	}
	
}