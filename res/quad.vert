#version 330
layout(location = 0 ) in vec3 pos;
layout(location = 1 ) in vec2 uvs;
out vec2 v_uvs;
uniform mat4 mvp;

void main(){
    gl_Position = mvp * vec4(pos,1.0);
    v_uvs = uvs;
}