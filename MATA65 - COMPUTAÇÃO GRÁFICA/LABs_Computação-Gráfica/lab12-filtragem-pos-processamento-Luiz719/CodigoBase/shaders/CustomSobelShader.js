import * as THREE from 'three';

const CustomSobelShader = {

	name: 'CustomSobelShader',

	uniforms: {

		'tDiffuse': { value: null },
		'resolution': { value: new THREE.Vector2() },
        'component': { value: 0 }, // 0 for X component, 1 for Y component
		'colorChannel': { value: 3 }  // 0 = Red, 1 = Green, 2 = Blue
	},

	vertexShader: /* glsl */`

		varying vec2 vUv;

		void main() {

			vUv = uv;

			gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );

		}`,

	fragmentShader: /* glsl */`

		uniform sampler2D tDiffuse;
		uniform vec2 resolution;
        uniform int colorChannel;
		uniform int component;
		varying vec2 vUv;

		void main() {

			vec2 texel = vec2( 1.0 / resolution.x, 1.0 / resolution.y );

		// kernel definition (in glsl matrices are filled in column-major order)

			const mat3 Gx = mat3( -1, -2, -1, 0, 0, 0, 1, 2, 1 ); // x direction kernel
			const mat3 Gy = mat3( -1, 0, 1, -2, 0, 2, -1, 0, 1 ); // y direction kernel

		// fetch the 3x3 neighbourhood of a fragment

            int channel = colorChannel == 3? 0 : colorChannel; 

		// first column

			float tx0y0 = texture2D( tDiffuse, vUv + texel * vec2( -1, -1 ) )[channel];
			float tx0y1 = texture2D( tDiffuse, vUv + texel * vec2( -1,  0 ) )[channel];
			float tx0y2 = texture2D( tDiffuse, vUv + texel * vec2( -1,  1 ) )[channel];

		// second column

			float tx1y0 = texture2D( tDiffuse, vUv + texel * vec2(  0, -1 ) )[channel];
			float tx1y1 = texture2D( tDiffuse, vUv + texel * vec2(  0,  0 ) )[channel];
			float tx1y2 = texture2D( tDiffuse, vUv + texel * vec2(  0,  1 ) )[channel];

		// third column

			float tx2y0 = texture2D( tDiffuse, vUv + texel * vec2(  1, -1 ) )[channel];
			float tx2y1 = texture2D( tDiffuse, vUv + texel * vec2(  1,  0 ) )[channel];
			float tx2y2 = texture2D( tDiffuse, vUv + texel * vec2(  1,  1 ) )[channel];

		// gradient value in x direction

			float valueGx = Gx[0][0] * tx0y0 + Gx[1][0] * tx1y0 + Gx[2][0] * tx2y0 +
				Gx[0][1] * tx0y1 + Gx[1][1] * tx1y1 + Gx[2][1] * tx2y1 +
				Gx[0][2] * tx0y2 + Gx[1][2] * tx1y2 + Gx[2][2] * tx2y2;

		// gradient value in y direction

			float valueGy = Gy[0][0] * tx0y0 + Gy[1][0] * tx1y0 + Gy[2][0] * tx2y0 +
				Gy[0][1] * tx0y1 + Gy[1][1] * tx1y1 + Gy[2][1] * tx2y1 +
				Gy[0][2] * tx0y2 + Gy[1][2] * tx1y2 + Gy[2][2] * tx2y2;

		// magnitute of the total gradient
			if(component == 0){
				valueGx = 0.0;
			}else if(component == 1){
				valueGy = 0.0;
			}

			float G = sqrt( ( valueGx * valueGx ) + ( valueGy * valueGy ) );

			gl_FragColor = vec4( vec3( G ), 1 );

		}`

};

export { CustomSobelShader };