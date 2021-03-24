#version 330 core
out vec4 color;
uniform vec3 mazeColor;
in vec3 vertexColor;
in vec4 vertexPosition;

uniform bool lights;

uniform vec3 playerPosition;

void main()
{
    float illuminationFactor = 0.01;
    float dist = pow(playerPosition.x-vertexPosition.x,2)+pow(playerPosition.y-vertexPosition.y,2);
    if(lights)
        color = vec4(vertexColor, lights);
    else
        color = vec4(vertexColor, illuminationFactor/dist);
}