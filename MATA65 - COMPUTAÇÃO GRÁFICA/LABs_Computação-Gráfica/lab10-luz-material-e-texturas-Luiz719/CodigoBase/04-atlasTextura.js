// Atlas de textura 

import * as THREE 			from 'three';
import { OBJLoader } 		from 'obj-loaders';
import { OrbitControls }	from 'orb-cam-ctrl';

const 	rendSize 	= new THREE.Vector2();

var 	renderer,
	 	scene,
	 	camera,
	 	cameraControl;

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function main() {

	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	rendSize.x = Math.min(window.innerWidth, window.innerHeight) * 1.6;
	rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);
	renderer.shadowMap.enabled 	= true;
	renderer.shadowMap.type 	= THREE.PCFShadowMap; 

	document.body.appendChild(renderer.domElement);

	scene 	= new THREE.Scene();
	scene.background = new THREE.Color( 0xf0f0f0 );

	camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 100);

	// Controle de Camera Orbital
	cameraControl 	= new OrbitControls(camera, renderer.domElement);

	var objectLoader = new OBJLoader();
	objectLoader.load("/Assets/Models/OBJ/AtlasModels/bunny.obj", loadMesh);

	render();
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function loadMesh(loadedMesh) {
	
	const textureLoader = new THREE.TextureLoader();
	const texture 		= textureLoader.load("../../Assets/Models/OBJ/AtlasModels/textures/bunny-atlas.jpg");
	const material 		= new THREE.MeshBasicMaterial({map:texture});
	
	loadedMesh.children.forEach(function (child) {
		child.material = material;
		});

	scene.add(loadedMesh);
	
	const box = new THREE.Box3().setFromObject(loadedMesh);
	
	camera.position.x = 0.0;
	camera.position.y = 0.0;
	camera.position.z = box.max.z*5.0;
	camera.lookAt(new THREE.Vector3(0.0, 0.0, 0.0));
	
	const farPlane = Math.max(	(box.max.x - box.min.x),
								(box.max.y - box.min.y),
								(box.max.z - box.min.z) );
	camera.near = 0.1;
	camera.far = farPlane*10.0;
	camera.updateProjectionMatrix();

	// Global Axis
	var globalAxis = new THREE.AxesHelper(farPlane);
	scene.add( globalAxis );

	cameraControl.update();

	// Chao
	const chao = new THREE.Mesh( 	new THREE.PlaneGeometry( 10000.0, 10000.0, 2, 2 ), 
									new THREE.MeshLambertMaterial( { color: 0xd0d0d0, opacity: 0.2 } ) );
	chao.position.y = box.min.y;
	chao.rotateX( - Math.PI / 2 );
	chao.receiveShadow = true;
	chao.name = "chao";
	scene.add( chao );

	const helper = new THREE.GridHelper( 10000, 200  );
	helper.position.y = box.min.y + 1.5;
	helper.material.opacity = 0.25;
	helper.material.transparent = true;
	scene.add( helper );

	const light = new THREE.PointLight( 0xffffff, 1, 1000 );
	light.position.set( 0.0, box.max.y*5.0, 0.0 );
	light.castShadow 	= true;
	light.name 			= "pLight";
	scene.add( light );
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function render() {

	cameraControl.update();

	renderer.render(scene, camera);

	requestAnimationFrame(render);
}

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************

main();
