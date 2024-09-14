import * as THREE from 'three';
import { GUI } from 'gui';

const gui = new GUI();
const rendSize = new THREE.Vector2();

var controls,
	scene,
	camera,
	renderer,
	ellipse,
	animeID,
	animated = false;

const clock = new THREE.Clock();


var oldTime = 0;
var shapeTime = 0;
var n = 4;
var a = 1;
var b = 1;

const aux = Array.from({ length: 15 }, (_, index) => 4 - (index * 0.25));
const aux2 = Array.from({ length: 12 }, (_, index) => 0.75 + (index * 0.25));
const nValues = aux.concat(aux2);

const directions = [
	new THREE.Vector3(1, 1, 0),   
	new THREE.Vector3(-1, 1, 0),  
	new THREE.Vector3(-1, -1, 0), 
	new THREE.Vector3(1, -1, 0)   
];

var currentDirection = 0; 
var currentN = 0; 

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

	window.addEventListener('resize', onWindowResize);

	scene = new THREE.Scene();

	camera = new THREE.OrthographicCamera(-7, 7, 7, -7, -6.0, 6.0);

	ellipse = generateSuperEllipsePlane(n, a, b);
	ellipse.position.y = 6;
	scene.add(ellipse);

	renderer.clear();
	renderer.render(scene, camera);

	initGUI();
};

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function initGUI() {
	controls = {
		animation: false,
		speed: 1 
	};
	gui.add(controls, 'animation').onChange(animate);
	gui.add(controls, 'speed', 0.1, 10, 0.1)
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

function generateSuperEllipsePlane(n, a, b) {
	const points = generateSuperEllipsePoints(n, a, b);
	var shape = new THREE.Shape(points);
	const geometry = new THREE.ExtrudeGeometry( shape );
	const superEllipse = new THREE.Mesh(geometry);
	return superEllipse;
}

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function animate(value) {
	if (value) {
		animated = true;
		animeID = requestAnimationFrame(anime);
	}
	else {
		animated = false;
		oldTime = 0;
		shapeTime = 0;
		clock.stop();
		cancelAnimationFrame(animeID);
	}
}

// ******************************************************************** //
// **                                                                ** //
// ******************************************************************** //
function anime() {
	if (animated) {
		if(!clock.running){
			clock.start();
		}
		const delta = clock.getDelta();
		const speed = controls.speed; 

		const newX = ellipse.position.x + directions[currentDirection].x * speed * delta;
		const newY = ellipse.position.y + directions[currentDirection].y * speed * delta;

		var position = ellipse.position.clone();
		var rotation = ellipse.rotation.clone();
		var color = ellipse.material.color;

		oldTime += delta;
		shapeTime += delta;

		if(shapeTime >= 3*(1/speed)){
			scene.clear();
			ellipse = generateSuperEllipsePlane(nValues[currentN], a, b);
			ellipse.rotation.set(...rotation);
			ellipse.position.set(...position);
			ellipse.material.color.set(...color);
			scene.add(ellipse);
			currentN = (currentN + 1) % nValues.length;
			shapeTime = 0;
		}

		ellipse.rotation.z += (speed * delta);

		if(oldTime >= 4*(1/speed)){
			ellipse.material.color.r = Math.random();
			ellipse.material.color.g = Math.random();
			ellipse.material.color.b = Math.random();
			oldTime = 0;
		}

		if (newX > 6 || newX < -6 || newY > 6 || newY < -6) {
			currentDirection = (currentDirection + 1) % directions.length;
		}
		else {
			ellipse.position.x = newX;
			ellipse.position.y = newY;
		}

		renderer.clear();
		renderer.render(scene, camera);
	}
	animeID = requestAnimationFrame(anime);
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
