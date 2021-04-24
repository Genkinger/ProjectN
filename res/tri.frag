#version 330

in vec3 v_pos;
in vec2 v_uvs;
out vec4 color;

uniform sampler2D sam;

void main(){
    color = texture2D(sam,v_uvs);
//    color = vec4(0.5*sin(v_pos.x)+0.5,0.5*sin(v_pos.y*2)+0.5,0.5*cos(v_pos.x*v_pos.y)+0.5,1);
}
