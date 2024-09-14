/**
 * Full-screen textured quad shader
 */

const NegativeShader = {

	name: 'NegativeShader',

	uniforms: {

		'tDiffuse': { value: null },
		'opacity': { value: 1.0 }

	},

	vertexShader: /* glsl */`

		varying vec2 vUv;

		void main() {

			vUv = uv;
			gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );

		}`,

	fragmentShader: /* glsl */`

		uniform float opacity;

		uniform sampler2D tDiffuse;

		varying vec2 vUv;

        vec3 negativeTransformation( in vec3 color ){
			vec3 result = 1.0 - color;
			return result;
		}

		void main() {

			vec4 texel = texture2D( tDiffuse, vUv );
			gl_FragColor = opacity * vec4(negativeTransformation(texel.rgb), texel.a);

		}`

};

export { NegativeShader };