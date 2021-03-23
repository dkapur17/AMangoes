#version 330 core
out vec4 color;
uniform vec3 mazeColor;

void main()
{
    color = vec4(mazeColor, 1.0);
}