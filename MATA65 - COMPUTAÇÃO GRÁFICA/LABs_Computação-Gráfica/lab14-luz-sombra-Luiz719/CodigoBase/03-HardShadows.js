// Sombras "hard"

import * as THREE 			from 'three';
import { OrbitControls } 	from 'orb-cam-ctrl';
import { OBJLoader } 		from 'OBJ-loaders';
import { GUI } 				from 'gui'

const   rendSize    	= new THREE.Vector2();

let 	scene 			= null;
let 	renderer		= null;
let 	camera 			= null;
let 	orbitControls	= null;
let 	params			= null;
let 	altura 			= 0.0;
let 	offset			= 0.001;

let 	clock 			= new THREE.Clock();

let gui 				= new GUI();

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function main() {

	scene 						= new THREE.Scene();

    rendSize.x 					= window.innerWidth*0.7;
    rendSize.y 					= window.innerHeight*0.7;

	renderer 					= new THREE.WebGLRenderer();
	renderer.shadowMap.enabled 	= true;
	renderer.shadowMap.type 	= THREE.BasicShadowMap; 

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));
	renderer.setSize(rendSize.x, rendSize.y);

    document.body.appendChild(renderer.domElement);

	camera 		= new THREE.PerspectiveCamera(70, rendSize.x/ rendSize.y, 0.1, 100.0);
	camera.position.set(0.0, 2.0, 3.0);
	camera.lookAt(0, 0, 0);

	// Controle de Camera Orbital
	orbitControls 				= new OrbitControls(camera, renderer.domElement);
	orbitControls.autoRotate 	= false;
		
	buildScene();
    initLight();
    initGUI();

	renderer.clear();
	render();
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function buildScene() {
	// Eixos de referencia
	let globalAxis = new THREE.AxesHelper(1.0);
	scene.add( globalAxis );

	// Load Mesh
	const loader = new OBJLoader();
	loader.load('/Assets/Models/OBJ/Classicals/Bunny-72Kv.obj', loadMesh);		

	// Ground
    const groundSize 	= 40.0;
  	const txtLoader 	= new THREE.TextureLoader();
    const texture 		= txtLoader.load("/Assets/Textures/checker.png");
    texture.wrapS 		= THREE.RepeatWrapping;
    texture.wrapT 		= THREE.RepeatWrapping;
    texture.magFilter 	= THREE.NearestFilter;

    texture.repeat.set(groundSize / 2, groundSize / 2);

    const groundMesh 			= new THREE.Mesh(	new THREE.PlaneGeometry(40.0, 40.0), 
    												new THREE.MeshStandardMaterial( { 	map 	:   texture,
                        		                        								side 	:   THREE.DoubleSide, 
                        		                        							})
    											);
    groundMesh.rotation.x 		= Math.PI * -.5;
	groundMesh.castShadow 		= false;
	groundMesh.receiveShadow 	= true;
    scene.add(groundMesh);
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function loadMesh(loadedMesh) {

	let material 		= new THREE.MeshStandardMaterial( 	{ 	color : new THREE.Color(0.0, 0.0, 1.0),
															} );

	loadedMesh.children.forEach(function (child) {
		child.material	= material;
		child.castShadow = true; 		//default is false
		child.receiveShadow = false; 	//default
		});

	loadedMesh.name		= "bunny";
	scene.add(loadedMesh);

	const box 		= new THREE.Box3().setFromObject(loadedMesh);
	
	const maxCoord 	= Math.max(	(box.max.x - box.min.x),
								(box.max.y - box.min.y),
								(box.max.z - box.min.z) );

	if (maxCoord > 1.0)
		loadedMesh.scale.x = 
		loadedMesh.scale.y = 
		loadedMesh.scale.z = 1.0 / maxCoord;

}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function initLight() {
    // Luz Pontual
    const pLight 					= new THREE.PointLight(0xFFFFFF, 0.5);
    pLight.castShadow 				= true;
	pLight.shadow.mapSize.width 	= 1024; // default
	pLight.shadow.mapSize.height 	= 1024; // default
    pLight.name 					= "pLight";
    pLight.position.set(0, 1.5, 0);

	const phelper 					= new THREE.PointLightHelper( pLight );
	pLight.add( phelper );
    scene.add(pLight);

    const dLight 					= new THREE.DirectionalLight(0xFFFFFF, 0.5);
    dLight.castShadow 				= true;
	dLight.shadow.mapSize.width 	= 1024; 
	dLight.shadow.mapSize.height 	= 1024; 
    dLight.name 					= "dLight";
    dLight.position.set(1.5, 1.5, -1.5);

	const dhelper 					= new THREE.DirectionalLightHelper( dLight );
	dLight.add( dhelper );
    scene.add(dLight);

}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function initGUI() {	

	params = 	{	algoritmo 	: THREE.BasicShadowMap,
					xResolution : 1024,
					yResolution : 1024,
					pLight		: true,
					dLight		: true,
					shadowPL	: true,
					shadowDL	: true,
				};

	const generatePowerOf2Options = () => {
		const options = [];
		for (let i = 1; i <= 12; i++) {
			options.push(Math.pow(2, i));
		}
		return options;
	};

	gui.add( params, 'algoritmo', {Basic: THREE.BasicShadowMap, PCF: THREE.PCFShadowMap, 
									PCFS: THREE.PCFSoftShadowMap, VSM: THREE.VSMShadowMap} 
			).onChange(function()	{ renderer.shadowMap.type 	= params.algoritmo; 
									});	
							
	gui.add(params, 'xResolution', generatePowerOf2Options()).onChange(changeSize);
	gui.add(params, 'yResolution', generatePowerOf2Options()).onChange(changeSize);

	
	gui.add( params, 'pLight').onChange(function()	{ 	let l = scene.getObjectByName("pLight");
														l.visible = params.pLight;
														l.shadow.mapSize.width 	= params.xResolution;
														l.shadow.mapSize.height = params.yResolution;
													});
	gui.add( params, 'shadowPL').onChange(function()	{ 	let l = scene.getObjectByName("pLight");
															l.castShadow = params.shadowPL;
															l.shadow.mapSize.width 	= params.xResolution;
															l.shadow.mapSize.height = params.yResolution;
													});
	gui.add( params, 'dLight').onChange(function()	{ 	let l = scene.getObjectByName("dLight");
														l.visible = params.dLight;
														l.shadow.mapSize.width 	= params.xResolution;
														l.shadow.mapSize.height = params.yResolution;
													});
	gui.add( params, 'shadowDL').onChange(function()	{ 	let l = scene.getObjectByName("dLight");
															l.castShadow = params.shadowDL;
															l.shadow.mapSize.width 	= params.xResolution;
															l.shadow.mapSize.height = params.yResolution;
													});
	gui.open();
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function changeSize(){
	let l = scene.getObjectByName("pLight");
	if(l){
		l.shadow.mapSize.width 	= params.xResolution;
		l.shadow.mapSize.height = params.yResolution;
	}
	l = scene.getObjectByName("dLight");
	if(l){
		l.shadow.mapSize.width 	= params.xResolution;
		l.shadow.mapSize.height = params.yResolution;
	}
	renderer.shadowMap.type 	= params.algoritmo;
	renderer.needsUpdate = true;
	renderer.render(scene, camera);
}


function render() {
	let delta = clock.getDelta();
    orbitControls.update(delta);

	let obj = scene.getObjectByName("bunny");

	if (obj) {
		altura += offset;
		obj.translateY(offset);

		if (altura > 1.0) 
			offset *= -1.0;
		if (altura < 0.0) 
			offset *= -1.0;
		}
		
	renderer.shadowMap.type 	= params.algoritmo
	renderer.needsUpdate = true;
	renderer.render(scene, camera);
	requestAnimationFrame(render);
}

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************
main();
