// Sombras "fake"

import * as THREE 			from 'three';
import { OrbitControls } 	from 'orb-cam-ctrl';
import { OBJLoader } 		from 'OBJ-loaders';

const   rendSize    	= new THREE.Vector2();

var 	scene 			= null;
var 	renderer		= null;
var 	camera 			= null;
var 	orbitControls	= null;
var 	altura 			= 0.0;
var 	offset			= 0.01;
var 	clock  			= new THREE.Clock();

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function main() {

	scene 		= new THREE.Scene();

	renderer 	= new THREE.WebGLRenderer();
    rendSize.x 	= window.innerWidth*0.7;
    rendSize.y 	= window.innerHeight*0.7;

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));
	renderer.setSize(rendSize.x, rendSize.y);

	document.body.appendChild(renderer.domElement);

	camera 		= new THREE.PerspectiveCamera(70, rendSize.x/ rendSize.y, 0.1, 100.0);
	camera.position.set(0.0, 2.0, 3.0);
	camera.lookAt(0, 0, 0);

	// Controle de Camera Orbital
	orbitControls 				= new OrbitControls(camera, renderer.domElement);
	orbitControls.autoRotate 	= false;

	buildScene();
		
    // Luz Direcional
    const dLight = new THREE.DirectionalLight(0xFFFFFF, 1);
    dLight.position.set(0, 2.0, 0);
    scene.add(dLight);

	const helper = new THREE.DirectionalLightHelper( dLight );
	scene.add( helper );

	render();
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function buildScene() {
	// Eixos de referencia
	var globalAxis = new THREE.AxesHelper(1.0);
	scene.add( globalAxis );

	// Load Mesh
	const loader = new OBJLoader();
	loader.load('/Assets/Models/OBJ/Classicals/Bunny-72Kv.obj', loadMesh);		

	// Ground
    const groundSize 	= 40.0;
  	const txtLoader 	= new THREE.TextureLoader();
    const texture 		= txtLoader.load("/Assets/Textures/checker.png");
    texture.wrapS 		= THREE.RepeatWrapping;
    texture.wrapT 		= THREE.RepeatWrapping;
    texture.magFilter 	= THREE.NearestFilter;
    texture.repeat.set(groundSize / 2, groundSize / 2);

    const groundMesh 			= new THREE.Mesh 	( 	new THREE.PlaneGeometry(groundSize, groundSize), 
    													new THREE.MeshStandardMaterial( { 	map   		:   texture,
                        		                        								    side  		:   THREE.DoubleSide,
                        		                           									flatShading	: 	false,
 
                                                  										})
    												);
    groundMesh.rotation.x 		= Math.PI * -.5;
    scene.add(groundMesh);
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function loadMesh(loadedMesh) {

	var material 		= new THREE.MeshPhongMaterial( 	{ 	color 		: 	new THREE.Color(0.0, 0.0, 1.0),
															specular 	: 	new THREE.Color(0.7, 0.7, 0.7), 
															shininess	: 	100,
														} );


	loadedMesh.children.forEach(function (child) {
		child.material 		= material;
		});

	loadedMesh.name = "bunny";

	const box 		= new THREE.Box3().setFromObject(loadedMesh);
	
	const maxCoord 	= Math.max(	(box.max.x - box.min.x),
								(box.max.y - box.min.y),
								(box.max.z - box.min.z) );

	if (maxCoord > 1.0)
		loadedMesh.scale.x = 
		loadedMesh.scale.y = 
		loadedMesh.scale.z = 1.0 / maxCoord;

	const base = new THREE.Object3D();
	base.add(loadedMesh);

  	const txtLoader 	= new THREE.TextureLoader();
	const shadowTexture = txtLoader.load("/Assets/Textures/roundshadow.png");

	const shadowMesh = new THREE.Mesh(	new THREE.PlaneGeometry(1.0, 1.0), 
										new THREE.MeshBasicMaterial(	{	map 		: 	shadowTexture,
																			transparent : 	true, 	// so we can see the ground
																			depthWrite 	: 	false, 	// so we don't have to sort
																		}));
	shadowMesh.position.y = 0.001;  // so we're above the ground slightly
	shadowMesh.rotation.x = Math.PI * -.5;
	const shadowSize = 1.0;
	shadowMesh.scale.set(shadowSize, shadowSize, shadowSize);
	shadowMesh.name = "fakeShadow";
	base.add(shadowMesh);

	scene.add(base);
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function render() {
	var delta = clock.getDelta();
    orbitControls.update(delta);

	var obj = scene.getObjectByName("bunny");

	if (obj) {
		altura += offset;
		obj.translateY(offset);
		var shadow = scene.getObjectByName("fakeShadow");

		shadow.material.opacity = THREE.MathUtils.lerp(1.0, 0.25, altura);

		if (altura > 1.0) 
			offset *= -1.0;
		if (altura < 0.0) 
			offset *= -1.0;
		}

	renderer.render(scene, camera);
	requestAnimationFrame(render);
}

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************
/// ***************************************************************
main();
