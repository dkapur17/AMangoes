#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection *  model * vec4(vertex.xy, 0.0, 1.0);
    vertexColor = vec3(aColor.x /255.0f, aColor.y / 255.0f, aColor.z/255.0f);
}