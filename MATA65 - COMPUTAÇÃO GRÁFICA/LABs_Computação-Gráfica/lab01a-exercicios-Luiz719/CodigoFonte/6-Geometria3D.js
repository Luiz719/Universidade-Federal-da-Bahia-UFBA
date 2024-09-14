// Desenhando objetos gráficos 3D do Three.JS

import * as THREE from 'three';

import { GUI } from 'gui';

const 	gui 		= new GUI();
const 	rendSize 	= new THREE.Vector2();

var 	controls, 
		objControls,
		scene,
		camera,
		renderer, 
		x,
		y, 
		z, 
		initialRotation = {},
		currentRotation = {x:0, y:0, z:0},
		oldColor = "#ffffff";

const objs = [];

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function main() {

	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	rendSize.x = 
	rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);

	document.body.appendChild(renderer.domElement);

	window.addEventListener ( 'resize', onWindowResize 	);

	scene 	= new THREE.Scene();

	camera = new THREE.OrthographicCamera( -1.0, 1.0, 1.0, -1.0, -1.0, 1.0 );

	var axis = new THREE.AxesHelper(0.8);
    axis.name = "eixos";
    scene.add(axis);


	var objMesh = new THREE.Mesh 	(new THREE.TetrahedronGeometry()); 
	objMesh.name 	= "Tetraedro";
	objs.push(objMesh.name);
	objMesh.visible = true;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };
	
	objMesh = new THREE.Mesh 	(new THREE.TorusGeometry(0.5, 0.3, 30, 30)); 
	objMesh.name 	= "Toro";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };
	
	var objMesh = new THREE.Mesh 	(new THREE.TorusKnotGeometry(0.5, 0.2)); 
	objMesh.name 	= "TorusKnot";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };

	objMesh = new THREE.Mesh 	(new THREE.ConeGeometry( 0.4, 1, 32, 10)); 
	objMesh.name 	= "Cone";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };

	objMesh = new THREE.Mesh 	(new THREE.CylinderGeometry( 0.4, 0.4, 0.7, 32, 10)); 
	objMesh.name 	= "Cilindro";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };

	objMesh = new THREE.Mesh 	(new THREE.SphereGeometry( 0.4)); 
	objMesh.name 	= "Esfera";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };

	objMesh = new THREE.Mesh 	(new THREE.BoxGeometry()); 
	objMesh.name 	= "Cubo";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	initialRotation[objMesh.name] = { x: objMesh.rotation.x, y: objMesh.rotation.y, z: objMesh.rotation.z };

	renderer.clear();
	renderer.render(scene, camera);

	initGUI();

}

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function initGUI() {

	controls = 	{	Forma3D : "Tetraedro"
					};
	objControls = { rotacaoX: 0,
					rotacaoY: 0,
					rotacaoZ: 0,
					wireframe: false,
					color: "#ffffff", 
					transparent: false, 
					opacity: 1
					};
				
	gui.add( controls, 'Forma3D', objs ).onChange(changeObj);
	const sub = gui.addFolder("Transformação-Objeto");
	sub.add(objControls, "rotacaoX", 0, 360, 1).onChange(changeRotation);
	sub.add(objControls, "rotacaoY", 0, 360, 1).onChange(changeRotation);
	sub.add(objControls, "rotacaoZ", 0, 360, 1).onChange(changeRotation);
	sub.add(objControls, 'wireframe').onChange(changeProperties);
	sub.add(objControls, 'color').onChange(changeProperties);
	sub.add(objControls, 'transparent').onChange(changeProperties);
	sub.add(objControls, 'opacity', 0, 1).onChange(changeProperties);
	gui.open();
};

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function changeObj(value) { 
	objs.forEach(op => {
						let obj = scene.getObjectByName(op);
						if(op == value){
							obj.visible = true;
							obj.rotation.set(currentRotation.x, currentRotation.y, currentRotation.z);
							obj.material.wireframe = objControls.wireframe;
							obj.material.transparent = objControls.transparent;
							obj.material.opacity = objControls.opacity;
						}else{
							obj.visible = false;
						}
						obj.material.color.set(oldColor);
						}
				);
	renderer.clear();
	renderer.render(scene, camera);
}

function changeRotation(){
	x = objControls.rotacaoX;
	y = objControls.rotacaoY;
	z = objControls.rotacaoZ;
	const obj = scene.getObjectByName(controls.Forma3D);
	obj.rotation.set(initialRotation[controls.Forma3D].x + (x * Math.PI) / 180.0, 
					 initialRotation[controls.Forma3D].y + (y * Math.PI) / 180.0, 
					 initialRotation[controls.Forma3D].z + (z * Math.PI) / 180.0);
	currentRotation = obj.rotation;
	renderer.clear();
	renderer.render(scene, camera);
}

function changeProperties(){
	const obj = scene.getObjectByName(controls.Forma3D);
	obj.material.wireframe = objControls.wireframe;
	obj.material.transparent = objControls.transparent;
	obj.material.opacity = objControls.opacity;
	obj.material.needsUpdate = true; 
	try{
		obj.material.color.set(objControls.color);
		oldColor = objControls.color;
	}catch(e){
		obj.material.color.set(objControls.color)
	}finally{
		renderer.clear();
		renderer.render(scene, camera);
	}
}

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function onWindowResize() {

	let minDim = Math.min(window.innerWidth, window.innerHeight);

	renderer.setSize(minDim*0.8, minDim*0.8);

	renderer.clear();
	renderer.render(scene, camera);
}

// ******************************************************************** //
// ******************************************************************** //
// ******************************************************************** //

main();
