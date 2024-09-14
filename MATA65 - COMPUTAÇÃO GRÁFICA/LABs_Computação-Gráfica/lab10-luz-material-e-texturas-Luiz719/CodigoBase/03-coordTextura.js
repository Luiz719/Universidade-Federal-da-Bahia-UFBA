// Mapeamento de Texturas 

import * as THREE 			from 'three';
import { OBJLoader } 		from 'obj-loaders';
import { OrbitControls }	from 'orb-cam-ctrl';

const 	rendSize 	= new THREE.Vector2();

var 	renderer,
		scene,
	 	camera,
	 	cameraControl,
	 	texture;

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
	cameraControl 		= new OrbitControls(camera, renderer.domElement);

	texture 			= new THREE.TextureLoader().load("/Assets/Textures/ash_uvgrid01.jpg");

	console.log(texture);

	var objectLoader 	= new OBJLoader();
	objectLoader.load("/Assets/Models/OBJ/Classicals/cube.obj", loadMesh);

	render();
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function loadMesh(loadedMesh) {

	const material 		= new THREE.MeshBasicMaterial( {map:texture } );
	
	loadedMesh.children.forEach(function (child) {
		child.material = material;
		});

	loadedMesh.children.forEach(function (child) {
		child.geometry.attributes.uv.array = modifyUVCoordinates(child.geometry.attributes.uv.array);
		child.geometry.attributes.uv.needsUpdate = true;
	});
	
	loadedMesh.name = "malha";

	scene.add(loadedMesh);
	
	const box = new THREE.Box3().setFromObject(loadedMesh);
	
	camera.position.x = box.max.x*2;
	camera.position.y = box.max.y*2;
	camera.position.z = box.max.z*2;
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
	const chao = new THREE.Mesh( 	new THREE.PlaneGeometry( 500.0, 500.0, 2, 2 ), 
									new THREE.MeshLambertMaterial( { color: 0xd0d0d0, opacity: 0.2 } ) );
	chao.position.y = box.min.y;
	chao.rotateX( - Math.PI / 2 );
	chao.receiveShadow = true;
	chao.name = "chao";
	scene.add( chao );

	const helper = new THREE.GridHelper( 500.0, 1000 );
	helper.position.y = box.min.y;
	helper.material.opacity = 0.25;
	helper.material.transparent = true;
	scene.add( helper );

	const light = new THREE.PointLight( 0xffffff, 1, 100 );
	light.position.set( 0.0, box.max.y, 0.0 );
	light.castShadow 	= true;
	light.name 			= "pLight";
	scene.add( light );

}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function modifyUVCoordinates(uvArray) {
    // Modify the UV coordinates to achieve the desired mapping
    // This is a simple example, adjust as needed for your specific texture
    for (let i = 0; i < uvArray.length; i += 2) {
        uvArray[i] = uvArray[i] * 2; // Scale U coordinates
        uvArray[i + 1] = uvArray[i + 1] * 2; // Scale V coordinates
    }
    return uvArray;
}


function render() {

	cameraControl.update();

	renderer.render(scene, camera);

	requestAnimationFrame(render);
}

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************

main();
