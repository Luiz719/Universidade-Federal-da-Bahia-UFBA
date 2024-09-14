import * as THREE from 'three';
import { GUI } from 'gui';

const gui = new GUI();
const rendSize = new THREE.Vector2();

var controls,
	scene,
	camera,
	renderer;

var n = 4; 
var a = 1;
var b = 1;

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function main() {

	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	rendSize.x = rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);

	document.body.appendChild(renderer.domElement);

	window.addEventListener('resize', onWindowResize);

	scene = new THREE.Scene();

	camera = new THREE.OrthographicCamera(-1.5, 1.5, 1.5, -1.5, -1.0, 1.0);

	const points = generateSuperEllipsePoints(n, a, b);

	var geometry = new THREE.BufferGeometry().setFromPoints(points);

	var line = new THREE.LineLoop(geometry);
	scene.add(line);

	renderer.clear();
	renderer.render(scene, camera);

	initGUI();
};

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function initGUI() {

	controls = { n: 4, a: 1, b: 1 };
	gui.add(controls, 'n', 0.25, 10, 0.25).onChange(changeSuperEllipse);
	gui.add(controls, 'a', 0.25, 2, 0.25).onChange(changeSuperEllipse);
	gui.add(controls, 'b', 0.25, 2, 0.25).onChange(changeSuperEllipse);
	gui.open();
};

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function generateSuperEllipsePoints(n, a, b) {
	const points = [];

	const numPoints = 200; 

	for (let i = 0; i <= numPoints; i++) {
		const t = (i / numPoints) * Math.PI * 2;
		const x = Math.pow(Math.abs(Math.cos(t)), 2 / n) * a * Math.sign(Math.cos(t));
		const y = Math.pow(Math.abs(Math.sin(t)), 2 / n) * b * Math.sign(Math.sin(t));
		points.push(new THREE.Vector3(x, y, 0));
	}

	return points;
}

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function changeSuperEllipse() {
	n = controls.n;
	a = controls.a;
	b = controls.b;

	scene.clear();

	const points = generateSuperEllipsePoints(n, a, b);

	var geometry = new THREE.BufferGeometry().setFromPoints(points);
	var line = new THREE.LineLoop(geometry);
	scene.add(line);

	renderer.clear();
	renderer.render(scene, camera);
}

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function onWindowResize() {
	let minDim = Math.min(window.innerWidth, window.innerHeight);
	renderer.setSize(minDim * 0.8, minDim * 0.8);
	renderer.clear();
	renderer.render(scene, camera);
}

// ******************************************************************** //
// ******************************************************************** //
// ******************************************************************** //
main();
