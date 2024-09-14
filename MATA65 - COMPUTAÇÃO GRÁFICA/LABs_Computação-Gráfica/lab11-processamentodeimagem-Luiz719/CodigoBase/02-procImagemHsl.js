// Modificando a cor dos pixels de uma imagem via Fragment Shader

import * as THREE 	from 'three';
import { GUI } 		from 'gui';

const 	gui = new GUI();

let 	oTex, 
		scene,
		camera,
		renderer,
		weights,
		parameters;


/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function main() {

	scene = new THREE.Scene();
	renderer = new THREE.WebGLRenderer();
	renderer.autoClear = false;
	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	buildGUI();

	camera = new THREE.OrthographicCamera( -0.5, 0.5, 0.5, -0.5, -1.0, 1.0 );
	scene.add( camera );
	
	let textureLoader = new THREE.TextureLoader();
	const texture = textureLoader.load("../../Assets/Images/lena.png", onLoadTexture);
	
	document.getElementById("threejs-canvas").appendChild(renderer.domElement);

	// Global Axis
	let globalAxis = new THREE.AxesHelper( 1.0 );
	scene.add( globalAxis );
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function onLoadTexture(tex) {

	if (!tex.image) 
		console.log("ERROR: loading texture");
	else {
		oTex = tex;
		console.log("Image size: " + tex.image.width + " x " + tex.image.height);
		console.log("Pixel size: " + 1.0/tex.image.width + " x " + 1.0/tex.image.height);

		weights = new THREE.Vector3( 0.299, 0.587, 0.114 );
		
		const matShader = new THREE.ShaderMaterial( {
										uniforms		: 	{	uSampler 		: 	{ 	type: "t", 		value:tex },
																uW 				: 	{ 	type: "v3", 	value:weights },
																uGray			: 	{ 	type: "bool", 	value:false }
															},
										vertexShader	: 	document.getElementById( 'grayScale-vs' ).textContent,
										fragmentShader	: 	document.getElementById( 'grayScale-fs' ).textContent
										} );
		
		// Plano da Imagem
		let plane 			= new THREE.Mesh( 	new THREE.PlaneGeometry(1.0, 1.0, 20, 20), 
												matShader );
		plane.position.set(0.0, 0.0, -0.5);
		plane.name = "Imagem";
		scene.add( plane );	

		renderer.setSize(tex.image.width, tex.image.height);

		let obj = scene.getObjectByName("Imagem");

		weights.x 							= 1;
		weights.y 							= 0;
		weights.z 							= 0;

		obj.material.uniforms.uW.value 	= weights;

		renderer.setViewport(0, 0, tex.image.width/2, tex.image.height/2);
		renderer.render(scene, camera);

		weights.x 							= 0;
		weights.y 							= 1;
		weights.z 							= 0;

		obj.material.uniforms.uW.value 	= weights;

		renderer.setViewport(tex.image.width/2, 0,tex.image.width/2, tex.image.height/2);
		renderer.render(scene, camera);

		weights.x 							= 0;
		weights.y 							= 0;
		weights.z 							= 1;

		obj.material.uniforms.uW.value 	= weights;

		renderer.setViewport(0, tex.image.height/2, tex.image.width/2, tex.image.height/2);
		renderer.render(scene, camera);

		weights.x 							= 1;
		weights.y 							= 1;
		weights.z 							= 1;

		obj.material.uniforms.uW.value 	= weights;


		renderer.setViewport(tex.image.width/2, tex.image.height/2, tex.image.width/2, tex.image.height/2);
		renderer.render(scene, camera);



		}
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function buildGUI() {

	parameters = { 	gray: false,
					};

	gui.add( parameters, 'gray' ).onChange(update);

	gui.open();
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function update() {

	let obj = scene.getObjectByName("Imagem")

	obj.material.uniforms.uGray.value 	= parameters.gray;
	obj.material.uniformsNeedUpdate 	= true;

	weights.set(1, 0, 0);
	obj.material.uniforms.uW.value = weights;

	renderer.setViewport(0, 0, oTex.image.width / 2, oTex.image.height / 2);
	renderer.render(scene, camera);

	weights.set(0, 1, 0);
	obj.material.uniforms.uW.value = weights;

	renderer.setViewport(oTex.image.width / 2, 0, oTex.image.width / 2, oTex.image.height / 2);
	renderer.render(scene, camera);

	weights.set(0, 0, 1);
	obj.material.uniforms.uW.value = weights;

	renderer.setViewport(0, oTex.image.height / 2, oTex.image.width / 2, oTex.image.height / 2);
	renderer.render(scene, camera);

	weights.set(1, 1, 1);
	obj.material.uniforms.uW.value = weights;

	renderer.setViewport(oTex.image.width / 2, oTex.image.height / 2, oTex.image.width / 2, oTex.image.height / 2);
	renderer.render(scene, camera);
};

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************
main();
