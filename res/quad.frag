#version 330
in vec2 v_uvs;
out vec4 color;
uniform sampler2D sam;

void main(){
    vec4 sampled = texture2D(sam,v_uvs);
    if(sampled.r == 0.0){
        discard;
    }
    color = sampled;

}