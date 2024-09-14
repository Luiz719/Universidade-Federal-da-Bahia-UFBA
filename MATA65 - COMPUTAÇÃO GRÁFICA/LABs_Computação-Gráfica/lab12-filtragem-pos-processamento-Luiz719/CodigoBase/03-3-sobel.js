// Calculando o gradiente da imagem via pós-processamento

import * as THREE 				from 'three';
	
import { GUI } 					from 'gui';
	
import { EffectComposer } 		from 'three/addons/postprocessing/EffectComposer.js';
import { RenderPass } 			from 'three/addons/postprocessing/RenderPass.js';
import { ShaderPass } 			from 'three/addons/postprocessing/ShaderPass.js';
import { LuminosityShader } 	from 'three/addons/shaders/LuminosityShader.js';
import { CustomSobelShader }	from './shaders/CustomSobelShader.js';


const gui = new GUI();

let 	scene,
		camera,
		renderer,
		composer;

const 	params = { enable : true, component: 2, gray: true, colorChannel: 3};

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function main() {

	scene = new THREE.Scene();
	renderer = new THREE.WebGLRenderer();
	
	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	camera = new THREE.OrthographicCamera( -0.5, 0.5, 0.5, -0.5, -1.0, 1.0 );
	scene.add( camera );
	
	var textureLoader = new THREE.TextureLoader().load("/Assets/Images/lena.png", onLoadTexture);
	
	document.getElementById("threejs-canvas").appendChild(renderer.domElement);

	// Global Axis
	var globalAxis = new THREE.AxesHelper( 1.0 );
	scene.add( globalAxis );

	gui.add( params, 'enable' ).onChange(onChangeGUI);
	gui.add( params, 'component', {xComponent: 0, yComponent: 1, both: 2 } ).onChange(onChangeGUI);
	gui.add( params, 'gray').onChange(onChangeGUI);
	gui.add( params, 'colorChannel', { 'Red': 0, 'Green': 1, 'Blue': 2, 'All':3 }).onChange(onChangeGUI);

	gui.open();
};

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function onLoadTexture(tex) {

	if (!tex.image) 
		console.log("ERROR: loading texture");
	else {
		
		// Plane
		var plane 			= new THREE.Mesh 	( 	new THREE.PlaneGeometry(1.0, 1.0, 20, 20), 
													new THREE.MeshBasicMaterial( { map 	: tex }) );
		plane.position.set(0.0, 0.0, -0.5);
		plane.name = "Imagem";
		scene.add( plane );	

		renderer.setSize(tex.image.width, tex.image.height);

		// postprocessing

		composer = new EffectComposer( renderer );
		const renderPass = new RenderPass( scene, camera );
		composer.addPass( renderPass );

		// converte a imagem para tons de cinza

		const effectGrayScale = new ShaderPass( LuminosityShader );
		composer.addPass( effectGrayScale );

		// calcula o gradiente da imagem com o filtro Sobel e registra a magnitude do gradiente na imagem

		const effectSobel = new ShaderPass( CustomSobelShader );
		effectSobel.uniforms[ 'resolution' ].value.x = window.innerWidth * window.devicePixelRatio;
		effectSobel.uniforms[ 'resolution' ].value.y = window.innerHeight * window.devicePixelRatio;
		effectSobel.uniforms[ 'component' ].value = params.component;
		effectSobel.uniforms['colorChannel'].value = params.colorChannel;
		composer.addPass( effectSobel );

		composer.render();
		}
};

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function onChangeGUI() {

	if ( params.enable == true){
		//const sobelPass = composer.passes[2].material.uniforms['component'] = params.component;
		const renderPass = new RenderPass( scene, camera );
		composer.addPass( renderPass );
		if(params.gray){
			const effectGrayScale = new ShaderPass( LuminosityShader );
			composer.addPass( effectGrayScale );
		}
		const effectSobel = new ShaderPass( CustomSobelShader );
		effectSobel.uniforms[ 'resolution' ].value.x = window.innerWidth * window.devicePixelRatio;
		effectSobel.uniforms[ 'resolution' ].value.y = window.innerHeight * window.devicePixelRatio;
		effectSobel.uniforms[ 'component' ].value = params.component;
		effectSobel.uniforms['colorChannel'].value = params.colorChannel;

		composer.addPass( effectSobel );

        composer.render();
	}else 
		renderer.render( scene, camera );
}

main();
