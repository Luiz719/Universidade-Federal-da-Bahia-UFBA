// Controle de camera com GUI.

import * as THREE 			from 'three';
import { GLTFLoader } 		from 'glTF-loader';
import { OrbitControls }	from 'orbit-ctrl';
import { GUI } 				from 'gui'



const 	rendSize 	= new THREE.Vector2();

let 	gui = new GUI();

let 	nearPlane 	= 0.01,
		farPlane 	= 100.0;

let 	scene,
		renderer, 
		camera, 
		mesh,
		orbitControls,
		clock,
		controls;

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function main() {
	
	clock = new THREE.Clock();
	
	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0xaaaaff));

	rendSize.x = Math.min(window.innerWidth, window.innerHeight) * 1.6;
	rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);

	document.body.appendChild(renderer.domElement);

	scene 	= new THREE.Scene();
	camera = new THREE.PerspectiveCamera( 	45.0, 
											rendSize.x/rendSize.y, 
											nearPlane, 
											farPlane );

	// Controle de Camera Orbital
	orbitControls = new OrbitControls(camera, renderer.domElement);
	orbitControls.autoRotate = false;
	
	const gltfLoader = new GLTFLoader();
	gltfLoader.load('/Assets/Models/glTF/city/scene.gltf', loadMesh);

	initGUI();
	
	render();
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function loadMesh(loadedMesh) {
		
	const root = loadedMesh.scene;
	root.name = "city";
	scene.add(root);
	setMaterial(root);
	
	const helper = new THREE.BoxHelper();
	helper.setFromObject(root);

	helper.geometry.computeBoundingBox();

	const max = helper.geometry.boundingBox.max;
	const min = helper.geometry.boundingBox.min;

	console.log("Dim = " + (max.x-min.x) + " , " + (max.y-min.y) + " , " + (max.z-min.z));
	
	camera.position.x = max.x;
	camera.position.y = max.y;
	camera.position.z = max.z;
	camera.lookAt(new THREE.Vector3(0.0, 0.0, 0.0));

	let farPlane = Math.max(	(max.x - min.x),
								(max.y - min.y),
								(max.z - min.z) );

	camera.far 	= farPlane*10.0;
	camera.updateProjectionMatrix();

	orbitControls.update();
	
	scene.add(new THREE.HemisphereLight( 0xffffbb, 0x080820, 1.2 ));	
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function initGUI() {
	
	controls = 	{	guiZBuffer	: true,
					guiCulling	: "FrontFace",
					guiNearFar	: "1x",
				};

	gui.add( controls, 'guiZBuffer').onChange(event => 	{ updateMaterial(scene.getObjectByName("city")); } );
	gui.add( controls, 'guiCulling', [ 	"FrontFace", 
										"BackFace", 
										"DoubleSide" ] ).onChange(event => { updateMaterial(scene.getObjectByName("city")); } );
	gui.add( controls, 'guiNearFar', [ 	"1x", 
										"10x", 
										"100x" ] ).onChange(event => { updateNearFarPlane(scene.getObjectByName("city")); } );
	gui.open();
		
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function render() {
	let delta = clock.getDelta();
    orbitControls.update(delta);

	renderer.render(scene, camera);
	requestAnimationFrame(render);
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function setMaterial(obj, isLast = true) {
	const lastNdx = obj.children.length - 1;

	switch (obj.name) {
		case 'mesh_0' 	: 	obj.material = new THREE.MeshPhongMaterial({ color : 0xff0000 });
							break;
		case 'mesh_1' 	: 	obj.material = new THREE.MeshPhongMaterial({ color : 0x00ff00 });
							break;
		case 'mesh_2' 	: 	obj.material = new THREE.MeshPhongMaterial({ color : 0x0000ff });
							break;
		default			: 	obj.material = new THREE.MeshPhongMaterial({ color : 0xffffff });
							break;
		}

	obj.children.forEach((child, ndx) => 	{	const isLast = ndx === lastNdx;
									    		setMaterial(child, isLast);
										  	} );
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function updateMaterial(obj, isLast = true) {
	const lastNdx = obj.children.length - 1;

	if (obj.type == 'Mesh') {

		obj.material.depthTest = controls.guiZBuffer;;

		switch( controls.guiCulling ) {
			case "FrontFace"	: 	obj.material.side = THREE.FrontSide; 
									break;
			case "BackFace"		: 	obj.material.side = THREE.BackSide; 
									break;
			case "DoubleSide"	: 	obj.material.side = THREE.DoubleSide; 
									break;
			}
		}
	obj.children.forEach((child, ndx) => 	{	const isLast = ndx === lastNdx;
									    		updateMaterial(child, isLast);
										  	} );
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function updateNearFarPlane(obj, isLast = true) {

	switch( controls.guiNearFar ) {
		case "1x"	: 	nearPlane = 0.01;
						farPlane = 100.0;
						break;
						
		case "10x"	: 	nearPlane = 0.001;
						farPlane = 1000.0;
						break;
		case "100x"	: 	nearPlane = 0.0001;
						farPlane = 10000.0;
						break;
		}

	camera.near = nearPlane;
	camera.far 	= farPlane;

	camera.updateProjectionMatrix();
	orbitControls.update();

	console.log(camera.near);
	console.log(camera.far);
	
	console.log(nearPlane);
	console.log(farPlane);
}

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************

main();
