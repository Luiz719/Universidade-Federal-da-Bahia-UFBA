import * as THREE from 'three';

const UnsharpMaskShader = {

	name: 'UnsharpMaskShader',

    uniforms: {
        'tDiffuse': { value: null },  
        'resolution': { value: new THREE.Vector2() },
        'uK': { value: 1.0 },
        'colorChannel': { value: 3 }  // 0 = Red, 1 = Green, 2 = Blue     
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
        uniform float uK;
        varying vec2 vUv;

        void main() {
            vec2 texel = vec2(1.0 / resolution.x, 1.0 / resolution.y);

            float h = texel.x;
            float v = texel.y;

			vec4 blurred = vec4( 0.0 );

			blurred += texture2D( tDiffuse, vec2( vUv.x - 4.0 * h, vUv.y - 4.0 * v ) ) * 0.051;
			blurred += texture2D( tDiffuse, vec2( vUv.x - 3.0 * h, vUv.y - 3.0 * v ) ) * 0.0918;
			blurred += texture2D( tDiffuse, vec2( vUv.x - 2.0 * h, vUv.y - 2.0 * v ) ) * 0.12245;
			blurred += texture2D( tDiffuse, vec2( vUv.x - 1.0 * h, vUv.y ) ) * 0.1531;
			blurred += texture2D( tDiffuse, vec2( vUv.x, vUv.y ) ) * 0.1633;
			blurred += texture2D( tDiffuse, vec2( vUv.x + 1.0 * h, vUv.y + 1.0 * v ) ) * 0.1531;
			blurred += texture2D( tDiffuse, vec2( vUv.x + 2.0 * h, vUv.y + 2.0 * v ) ) * 0.12245;
			blurred += texture2D( tDiffuse, vec2( vUv.x + 3.0 * h, vUv.y + 3.0 * v) ) * 0.0918;
			blurred += texture2D( tDiffuse, vec2( vUv.x + 4.0 * h, vUv.y + 4.0 * v ) ) * 0.051;

            vec4 original = texture2D(tDiffuse, vUv);
            if(colorChannel == 0){
                original.g = 0.0;
                original.b = 0.0;
            }else if(colorChannel == 1){
                original.r = 0.0;
                original.b = 0.0;
            }else if(colorChannel == 2){
                original.r = 0.0;
                original.g = 0.0;
            }
            vec4 unsharp = original + uK * (original - blurred);
            

            gl_FragColor = unsharp;
        }
    `
};

export { UnsharpMaskShader };