#ifdef GL_ES
    precision mediump float;
#endif
uniform float time;

varying vec3 vNormal;

void main() {
    gl_FragColor =  vec4(vNormal.xy*0.5,0.5+0.5*sin(time),1.0);

}