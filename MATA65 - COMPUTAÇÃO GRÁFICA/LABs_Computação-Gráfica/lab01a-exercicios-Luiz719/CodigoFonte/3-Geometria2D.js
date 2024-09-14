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
const patterns = ["Padrao 1", "Padrao 2", "Padrao 3", "Padrao 4"];
const properties = [
	{
	  "Padrao 1": {
		color: 0xffffff,
		linewidth: 1,
		transparent: false,
	  }
	},
	{
	  "Padrao 2": {
		color: 0x00ff0a,
		linewidth: 5,
		transparent: false,
	  }
	},
	{
	  "Padrao 3": {
		color: 0xf2c0ff,
		linewidth: 8,
		transparent: false,
	  }
	},
	{
	  "Padrao 4": {
		color: 0x0000ff,
		linewidth: 15,
		transparent: true,
		opacity: 0.2,
	  }
	}
  ]
  

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
	
	const material = new THREE.LineBasicMaterial();
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

	controls = 	{	lineType : "linhaPoligonalAberta",
					lineProperties: "Padrao 1"
				};
	gui.add( controls, "lineType", lines).onChange(changeLine);
	gui.add( controls, "lineProperties", patterns).onChange(changeProperties);
	gui.open();
};

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function changeLine(value) {
	const property = properties.find(obj => 
		Object.keys(obj)[0] == controls.lineProperties)[controls.lineProperties];
	lines.forEach(op => {let line = scene.getObjectByName(op);
						line.visible = (op == value);
						line.material.setValues(property);});
	renderer.clear();
	renderer.render(scene, camera);	
}

function changeProperties(value) {
	const property = properties.find(obj => Object.keys(obj)[0] == value)[value];
	scene.getObjectByName(controls.lineType).material.setValues(property);
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
