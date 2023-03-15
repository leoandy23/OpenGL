#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float group;

out vec2 TexCoord;
out float aGroup;
out vec3 fcolor;

uniform mat4 transform;
uniform mat4 transform2;
uniform float visible;
void main(){
	TexCoord = vec2((aPos.x+1.0)/2.0,(aPos.y+1.0)/2.0);
	fcolor = vec3(abs(aPos.x),abs(aPos.y),visible);
	aGroup = group;

	if(aGroup==0){
		gl_Position = transform * vec4(aPos, 1.0);
	}
	
	if(aGroup==1){
		gl_Position = transform2 * vec4(aPos, 1.0);
	}
	
	if(aGroup==2){
		gl_Position = transform*vec4(aPos, 1.0);
	}
	
}