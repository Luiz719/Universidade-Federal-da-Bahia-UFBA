// Cenário com diversos objetos com materiais distintos.

import * as THREE from 'three';
import { OrbitControls } from 'orb-cam-ctrl';
			
const 	rendSize 	= new THREE.Vector2();

const 	clock 		= new THREE.Clock();

let 	scene,
		renderer,
		camera,
		camControl;

function main() {

	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	rendSize.x = window.innerWidth * 0.8
	rendSize.y = window.innerHeight * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);
	renderer.shadowMap.enabled 	= true;
	renderer.shadowMap.type 	= THREE.PCFShadowMap; 

	document.body.appendChild(renderer.domElement);

	scene 	= new THREE.Scene();
	scene.background = new THREE.Color( 0xf0f0f0 );


	camera = new THREE.PerspectiveCamera( 75.0, rendSize.x / rendSize.y, 0.01, 1000.0);
	camera.position.set(0.0, 0.5, 1.3);
	camera.lookAt(new THREE.Vector3(0.0, 0.0, 0.0));
	scene.add( camera );

	camControl 				= new OrbitControls(camera, renderer.domElement);
	camControl.autoRotate 	= false;
	camControl.rotateSpeed 	= 2.0;
	camControl.enablePan 	= true;
	camControl.enableZoom 	= true;
	
	buildScene();

	requestAnimationFrame(anime);

};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function buildScene() {

	// Objs Group

	let worldGrp = new THREE.Group();
	worldGrp.name = "world";
	scene.add(worldGrp);

    // Box
    let boxMaterial = new THREE.MeshPhongMaterial({ color: 0x0000FF });
    let box = new THREE.Mesh(new THREE.BoxGeometry(0.2, 0.2, 0.2), boxMaterial);
    box.name = "Box";
    box.translateX(-0.7);
    box.translateZ(0.7);
    worldGrp.add(box);

    // Cylinder
    let cylinderMaterial = new THREE.MeshNormalMaterial();
    let cylinder = new THREE.Mesh(new THREE.CylinderGeometry(0.1, 0.1, 0.5, 30), cylinderMaterial);
    cylinder.name = "Cylinder";
    cylinder.translateZ(0.7);
    worldGrp.add(cylinder);

    // Torus
    let torusMaterial = new THREE.MeshPhongMaterial({ color: 0xFFFFFF });
    let torus = new THREE.Mesh(new THREE.TorusGeometry(0.2, 0.1, 16, 100), torusMaterial);
    torus.name = "Torus";
    torus.translateX(0.7);
    torus.translateZ(0.7);
    worldGrp.add(torus);

    // Sphere
    let sphereMaterial = new THREE.MeshPhongMaterial({ color: 0xFFFF00 });
    let sphere = new THREE.Mesh(new THREE.SphereGeometry(0.2, 32, 32), sphereMaterial);
    sphere.name = "Sphere";
    worldGrp.add(sphere);

    // TorusKnot
    let torusKnotMaterial = new THREE.MeshPhongMaterial({ color: 0x00FF00 });
    let torusKnot = new THREE.Mesh(new THREE.TorusKnotGeometry(0.2, 0.03, 100, 16), torusKnotMaterial);
    torusKnot.name = "TorusKnot";
    torusKnot.translateX(-0.7);
    worldGrp.add(torusKnot);

    // Icosahedron
    let icosahedronMaterial = new THREE.MeshPhongMaterial({ color: 0x964B00 });
    let icosahedron = new THREE.Mesh(new THREE.IcosahedronGeometry(0.2), icosahedronMaterial);
    icosahedron.name = "Icosahedron";
    icosahedron.translateX(0.7);
    worldGrp.add(icosahedron);

    // Plane
    let planeMaterial = new THREE.MeshPhongMaterial({ color: 0x800080 });
    let plane = new THREE.Mesh(new THREE.PlaneGeometry(0.2, 0.5, 1, 1), planeMaterial);
    plane.name = "Plane";
    plane.translateX(-0.7);
    plane.translateZ(-0.7);
    worldGrp.add(plane);

    // Tetrahedron
    let tetrahedronMaterial = new THREE.MeshPhongMaterial({ color: 0xFF0000 });
    let tetrahedron = new THREE.Mesh(new THREE.TetrahedronGeometry(0.2), tetrahedronMaterial);
    tetrahedron.name = "Tetrahedron";
    tetrahedron.translateZ(-0.7);
    worldGrp.add(tetrahedron);

    // Dodecahedron
    let dodecahedronMaterial = new THREE.MeshPhongMaterial({ color: 0x00FFFF });
    let dodecahedron = new THREE.Mesh(new THREE.DodecahedronGeometry(0.2), dodecahedronMaterial);
    dodecahedron.name = "Dodecahedron";
    dodecahedron.translateX(0.7);
    dodecahedron.translateZ(-0.7);
    worldGrp.add(dodecahedron);

	// Chao
	const chao = new THREE.Mesh( 	new THREE.PlaneGeometry( 500.0, 500.0, 2, 2 ), 
									new THREE.MeshLambertMaterial( { color: 0xd0d0d0 } ) );
	chao.position.y = -0.3;
	chao.rotateX( - Math.PI / 2 );
	chao.receiveShadow = true;
	chao.name = "chao";
	scene.add( chao );

	const helper = new THREE.GridHelper( 500.0, 1000 );
	helper.position.y = -0.25;
	helper.material.opacity = 0.25;
	helper.material.transparent = true;
	scene.add( helper );

	const light = new THREE.PointLight( 0xffffff, 1, 100 );
	light.position.set( 0.0, 0.5, 0.0 );
	light.castShadow 	= true;
	light.name 			= "pLight";
	worldGrp.add( light );

	const lightHelper = new THREE.PointLightHelper( light, 0.2 );
	lightHelper.name = "pLightHelper";
	light.add( lightHelper );
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function anime() {

	camControl.update( clock.getDelta() );

	let world = scene.getObjectByName("world");
	world.rotateY(0.01);

	renderer.render(scene, camera);
	
	requestAnimationFrame( anime );
};


/// ***************************************************************
/// ***************************************************************
/// ***************************************************************

main();
