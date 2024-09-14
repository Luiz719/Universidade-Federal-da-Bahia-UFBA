// Desenhando objetos gráficos 2D

import * as THREE from 'three';

import { GUI } from 'gui';

const 	gui 		= new GUI();
const 	rendSize 	= new THREE.Vector2();

var 	controls, 
		scene,
		camera,
		renderer;

const lines = [];

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

	const vertices = [];

	vertices.push(	new THREE.Vector3( -0.5, -0.5, 0.0 ) );
	vertices.push(	new THREE.Vector3(  0.5, -0.5, 0.0 ) );
	vertices.push(	new THREE.Vector3(  0.5,  0.5, 0.0 ) );
	vertices.push(	new THREE.Vector3( -0.5,  0.5, 0.0 ) );

	var geometry = new THREE.BufferGeometry().setFromPoints( vertices );
	
	const dashMaterial = new THREE.LineDashedMaterial({
		color: 0xffffff,
		linewidth: 1,
		scale: 1,
		dashSize: 0.2, 
		gapSize: 0.05, 
	  });

	var lineStrip = new THREE.Line( geometry );
	lineStrip.name = "linhaPoligonalAberta";
	lines.push(lineStrip.name);
	scene.add( lineStrip );	

	var lineLoop = new THREE.LineLoop( geometry );
	lineLoop.name = "linhaPoligonalFechada";
	lines.push(lineLoop.name);
	lineLoop.visible = false;
	scene.add( lineLoop );	

	var lineDashed = new THREE.Line(geometry, dashMaterial);
	lineDashed.computeLineDistances();
	lineDashed.name = "linhaTracejada";
	lines.push(lineDashed.name);
	lineDashed.visible = false;
	scene.add( lineDashed );
	
	const material = new THREE.LineBasicMaterial({ color: 0xff00ff });
	var lineSegments = new THREE.LineSegments(geometry, material);
	lineSegments.name = "lineSegment";
	lines.push(lineSegments.name);
	lineSegments.visible = false;
	scene.add(lineSegments);

	renderer.clear();
	renderer.render(scene, camera);
	
	initGUI();
};

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function initGUI() {

	controls = 	{	lineType : "linhaPoligonalAberta"
				};
	gui.add( controls, "lineType", lines).onChange(changeLine);
	gui.open();
};

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function changeLine(value) {

	lines.forEach(op => {scene.getObjectByName(op).visible = (op == value);})

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
