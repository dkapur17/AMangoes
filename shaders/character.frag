#version 330 core
out vec4 color;
uniform vec3 characterColor;

void main()
{
    color = vec4(characterColor, 1.0);
}