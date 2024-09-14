import * as THREE from 'three';

const LaplacianShader = {

	name: 'LaplacianShader',

    uniforms: {
        'tDiffuse': { value: null },
        'resolution': { value: new THREE.Vector2() },
        'L': { value: 1.0 },
        'colorChannel': { value: 3 },  // 0 = Red, 1 = Green, 2 = Blue
        'gray': { value: true } 
    },
    vertexShader: `
        varying vec2 vUv;

        void main() {
            vUv = uv;
            gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
        }
    `,
    fragmentShader: `
        uniform sampler2D tDiffuse;
        uniform vec2 resolution;
        uniform int colorChannel;
        uniform float L;
        uniform bool gray;
        varying vec2 vUv;

        void main() {
            vec2 texel = vec2(1.0 / resolution.x, 1.0 / resolution.y);
            vec4 color = texture2D( tDiffuse, vUv );
            const mat3 LaplacianKernel = mat3(
                1,  1,  1,
                1, -8,  1,
                1,  1,  1
            );

            int channel = colorChannel == 3? 0 : colorChannel; 
            // Fetch the 3x3 neighborhood of a fragment
            float tx0y0 = texture2D(tDiffuse, vUv + texel * vec2(-1, -1))[channel];
            float tx0y1 = texture2D(tDiffuse, vUv + texel * vec2(-1,  0))[channel];
            float tx0y2 = texture2D(tDiffuse, vUv + texel * vec2(-1,  1))[channel];
            float tx1y0 = texture2D(tDiffuse, vUv + texel * vec2( 0, -1))[channel];
            float tx1y1 = texture2D(tDiffuse, vUv + texel * vec2( 0,  0))[channel];
            float tx1y2 = texture2D(tDiffuse, vUv + texel * vec2( 0,  1))[channel];
            float tx2y0 = texture2D(tDiffuse, vUv + texel * vec2( 1, -1))[channel];
            float tx2y1 = texture2D(tDiffuse, vUv + texel * vec2( 1,  0))[channel];
            float tx2y2 = texture2D(tDiffuse, vUv + texel * vec2( 1,  1))[channel];

            float valueLaplacian = 
                LaplacianKernel[0][0] * tx0y0 + LaplacianKernel[1][0] * tx1y0 + LaplacianKernel[2][0] * tx2y0 +
                LaplacianKernel[0][1] * tx0y1 + LaplacianKernel[1][1] * tx1y1 + LaplacianKernel[2][1] * tx2y1 +
                LaplacianKernel[0][2] * tx0y2 + LaplacianKernel[1][2] * tx1y2 + LaplacianKernel[2][2] * tx2y2;

            float G = valueLaplacian;
            G = clamp(G, -L, L);
            G = (G + L) / (2.0 * L); 
            //if(colorChannel == 3 && !gray) gl_FragColor = vec4(color.rgb+0.1*vec3(G), 1.0);
            //else 
            gl_FragColor = vec4(vec3(G), 1.0);
        }
`
};
export { LaplacianShader };