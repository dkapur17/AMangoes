#version 330 core
out vec4 color;
uniform vec3 mazeColor;
in vec3 vertexColor;
in vec4 vertexPosition;

uniform bool lights;
uniform float topDist;
uniform float leftDist;
uniform float rightDist;
uniform float bottomDist;

uniform vec3 playerPosition;

void main()
{
    float illuminationFactor = 0.008;
    float dist = sqrt(pow(vertexPosition.x,2)+pow(vertexPosition.y,2));
    if(lights)
        color = vec4(vertexColor, 1.0);
    else
    {
        if(vertexPosition.x <= 0 && vertexPosition.x < -leftDist)
            color = vec4(vertexColor, 0.0);
        else if(vertexPosition.x > 0 && vertexPosition.x > rightDist)
            color = vec4(vertexColor, 0.0);
        else if(vertexPosition.y <= 0 && vertexPosition.y < -topDist)
            color = vec4(vertexColor, 0.0);
        else if(vertexPosition.y > 0 && vertexPosition.y > bottomDist)
            color = vec4(vertexColor, 0.0);
        else
            color = vec4(vertexColor,  25/dist);
    }
}