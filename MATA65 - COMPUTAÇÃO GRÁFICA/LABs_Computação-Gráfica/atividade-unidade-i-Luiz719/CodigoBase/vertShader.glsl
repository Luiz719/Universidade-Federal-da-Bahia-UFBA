precision mediump float;

uniform float time;
varying vec3 vNormal;

void main() {
    vNormal = normal;

    float radius = 60.0;
    float speed = 0.1;
    float angle = speed * time + position.x / radius;

    vec3 transformed = vec3(
        position.x + radius * cos(angle),
        position.y + radius * sin(angle),
        position.z
    );

    gl_Position = projectionMatrix * modelViewMatrix * vec4(transformed, 1.0);
}