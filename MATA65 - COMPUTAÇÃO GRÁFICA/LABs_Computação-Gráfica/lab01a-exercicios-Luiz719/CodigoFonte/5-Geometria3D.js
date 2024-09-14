// Desenhando objetos gráficos 3D do Three.JS

import * as THREE from 'three';

import { GUI } from 'gui';

const 	gui 		= new GUI();
const 	rendSize 	= new THREE.Vector2();

var 	controls, 
		scene,
		camera,
		renderer;

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


	var objMesh = new THREE.Mesh 	( 	new THREE.TetrahedronGeometry(), 
										new THREE.MeshBasicMaterial({color:0xffff00, wireframe:true })
									); 
	objMesh.name 	= "Tetraedro";
	objs.push(objMesh.name);
	objMesh.visible = true;
	objMesh.rotateY(60.0 * Math.PI / 180.0); 
	objMesh.updateMatrix();
	scene.add( objMesh );

	objMesh = new THREE.Mesh 	( 	new THREE.TorusGeometry(0.5, 0.3, 30, 30), 
									new THREE.MeshBasicMaterial({color:0x00ff00, wireframe:false })
								); 
	objMesh.name 	= "Toro";
	objs.push(objMesh.name);
	objMesh.visible = false;
	scene.add( objMesh );
	
	var objMesh = new THREE.Mesh 	( 	new THREE.TorusKnotGeometry(0.5, 0.2), 
										new THREE.MeshBasicMaterial({color:0x0000ff, wireframe:true })
									); 
	objMesh.name 	= "TorusKnot";
	objs.push(objMesh.name);
	objMesh.visible = false;
	objMesh.rotateX(60.0 * Math.PI / 180.0); 
	objMesh.rotateY(30.0 * Math.PI / 180.0); 
	objMesh.updateMatrix();
	scene.add( objMesh );

	objMesh = new THREE.Mesh 	( 	new THREE.ConeGeometry( 0.4, 1, 32, 10),
									new THREE.MeshBasicMaterial( {color: 0x22af00, wireframe:true} ) 
								); 
	objMesh.name 	= "Cone";
	objs.push(objMesh.name);
	objMesh.rotateX(60.0 * Math.PI / 180.0); 
	objMesh.rotateY(60.0 * Math.PI / 180.0); 
	objMesh.rotateZ(260.0 * Math.PI / 180.0);
	objMesh.updateMatrix();
	objMesh.visible = false;
	scene.add( objMesh );

	objMesh = new THREE.Mesh 	( 	new THREE.CylinderGeometry( 0.4, 0.4, 0.7, 32, 10),
									new THREE.MeshBasicMaterial( {color: 0x22afff, wireframe:true} ) 
								); 
	objMesh.name 	= "Cilindro";
	objs.push(objMesh.name);
	objMesh.rotateX(60.0 * Math.PI / 180.0); 
	objMesh.rotateY(30.0 * Math.PI / 180.0); 
	objMesh.updateMatrix();
	objMesh.visible = false;
	scene.add( objMesh );


	objMesh = new THREE.Mesh 	( 	new THREE.SphereGeometry( 0.4),
									new THREE.MeshBasicMaterial( {color: 0xfff22a, wireframe:true} ) 
								); 
	objMesh.name 	= "Esfera";
	objs.push(objMesh.name);
	objMesh.rotateX(40.0 * Math.PI / 180.0); 
	objMesh.rotateY(270.0 * Math.PI / 180.0); 
	objMesh.rotateZ(30.0 * Math.PI / 180.0);
	objMesh.updateMatrix();
	objMesh.visible = false;
	scene.add( objMesh );

	objMesh = new THREE.Mesh 	( 	new THREE.BoxGeometry(),
									new THREE.MeshBasicMaterial( {color: 0xf31225, wireframe:true} ) 
								); 
	objMesh.name 	= "Cubo";
	objs.push(objMesh.name);
	objMesh.rotateX(90.0 * Math.PI / 180.0); 
	objMesh.updateMatrix();
	objMesh.visible = false;
	scene.add( objMesh );

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

	gui.add( controls, 'Forma3D', objs ).onChange(changeObj);
	gui.open();
};

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function changeObj(value) { 
	objs.forEach(op => {scene.getObjectByName(op).visible = (op == value);})
	renderer.clear();
	renderer.render(scene, camera);
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
