/**
 * Full-screen textured quad shader
 */

const IntensityShader = {

	name: 'IntensityShader',

	uniforms: {

		'tDiffuse': { value: null },
		'opacity': { value: 1.0 },
		'intensity': {value: 1.0},
		'colorChannel': { value: 3 }  // 0 = Red, 1 = Green, 2 = Blue
	},

	vertexShader: /* glsl */`

		varying vec2 vUv;

		void main() {

			vUv = uv;
			gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );

		}`,

	fragmentShader: /* glsl */`

		uniform float opacity;

		uniform float intensity;

		uniform sampler2D tDiffuse;

		uniform int colorChannel;

		varying vec2 vUv;


		vec3 logTransformation( in vec3 color ){
			vec3 result = intensity * log(color + 1.0);
			return result;
		}

		void main() {

			vec4 texel = texture2D( tDiffuse, vUv );
			vec3 result = vec3(0.0);
			if(colorChannel == 0) result.r = texel.r;
			else if(colorChannel == 1) result.g = texel.g;
			else if(colorChannel == 2) result.b = texel.b;
			else result = texel.rgb;

			gl_FragColor = opacity * vec4(logTransformation(result), texel.a);

		}`

};

export { IntensityShader };