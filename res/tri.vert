#version 330

layout(location = 0 ) in vec3 pos;
layout(location = 1 ) in vec2 uvs;

out vec3 v_pos;
out vec2 v_uvs;

void main(){
    gl_Position = vec4(pos,1.0);
    v_pos = pos;
    v_uvs = uvs;
}