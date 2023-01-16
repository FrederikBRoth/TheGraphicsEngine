#version 330 core
layout(location = 0) in vec3 aPos;

uniform vec4 model;
uniform vec4 projection;

out vec3 color;


void main() {
	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
	color = vec3(1.0f, 0.0f, 0.0f);

}