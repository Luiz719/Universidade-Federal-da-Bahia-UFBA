// Luz

import * as THREE 			from 'three';
import { TeapotGeometry } 	from 'teapot-geom';
import { OrbitControls }	from 'orb-cam-ctrl';
import { GUI } 				from 'gui'
import { RectAreaLightHelper } from '../Assets/scripts/three.js/examples/jsm/helpers/RectAreaLightHelper.js';
import { RectAreaLightUniformsLib } from '../Assets/scripts/three.js/examples/jsm/lights/RectAreaLightUniformsLib.js';

const   rendSize    	= new THREE.Vector2();

let 	scene 			= null;
let 	renderer		= null;
let 	camera 			= null;
let 	orbitControls	= null;
let 	params			= null;
let 	maxCoord;
let 	lights 			= [];
let 	helperLights 	= [];


const 	tLights			=  	{	L_AMBIENT 		: 0,
								L_DIRECIONAL 	: 1,
								L_POINT  		: 2,
								L_SPOT  		: 3,
								L_RECT			: 4,
								L_HEMI			: 5,
							}

let curLight 			= tLights.L_AMBIENT;

let clock  				= new THREE.Clock();
let gui 				= new GUI();

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function main() {

    scene = new THREE.Scene();
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(0x000000, 1.0);

    rendSize.x = window.innerWidth*0.7;
    rendSize.y = window.innerHeight*0.7;

    renderer.setSize(rendSize.x, rendSize.y);
    document.body.appendChild(renderer.domElement);

	camera = new THREE.PerspectiveCamera(70.0, rendSize.x/rendSize.y, 0.1, 30.0);
	
	orbitControls 	= new OrbitControls(camera, renderer.domElement);

	buildScene();

	initLights();
	initGUI();
			
	render();
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function render() {
	let delta = clock.getDelta();
    orbitControls.update(delta);

	renderer.render(scene, camera);
	requestAnimationFrame(render);
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function buildScene() {


	const teapot 		= new TeapotGeometry( 5, 8 );
	const mesh 			= new THREE.Mesh( 	teapot, 
											new THREE.MeshPhysicalMaterial( {	color : 0x708090 } ) 
										);
	mesh.name 			= "teapot";

	scene.add(mesh);

	

	let box 			= new THREE.Box3();
	box.setFromObject(mesh);

	// Adjust Camera Position and LookAt	
	maxCoord 			= Math.max(box.max.x,box.max.y,box.max.z);	

	camera.position.x 	= 
	camera.position.y 	= 
	camera.position.z 	= maxCoord;
	camera.far 			= new THREE.Vector3(	maxCoord*5, 
												maxCoord*5, 
												maxCoord*5).length();

	camera.lookAt(new THREE.Vector3(	(box.max.x + box.min.x) / 2.0,
										(box.max.y + box.min.y) / 2.0,
										(box.max.z + box.min.z) / 2.0 ));
	camera.updateProjectionMatrix();

	// Global Axis
	let globalAxis = new THREE.AxesHelper(maxCoord*1.3);
	scene.add( globalAxis );

	// Ground
	let groundMesh = new THREE.Mesh(	new THREE.PlaneGeometry( maxCoord*200.0, maxCoord*200.0, 50, 50), 
										new THREE.MeshPhongMaterial(	{	color 	: 0x556B2F,
																			side 	: THREE.DoubleSide,
																		} ));

	groundMesh.name 				= "ground";
	groundMesh.rotation.x 			= -Math.PI / 2;
	groundMesh.position.y 			= box.min.y * 1.1;

	scene.add(groundMesh);
	// Chao
	const chao = new THREE.Mesh( 	new THREE.PlaneGeometry( maxCoord*200.0, maxCoord*200.0, 2, 2 ), 
									new THREE.MeshLambertMaterial( { color: 0xd0d0d0 } ) );
	chao.position.y = box.min.y;
	chao.rotateX( - Math.PI / 2 );
	chao.receiveShadow = true;
	chao.name = "chao";
	scene.add( chao );

	const helper = new THREE.GridHelper( maxCoord*200.0, 1000 );
	helper.position.y = box.min.y - box.min.y * 0.10;
	helper.material.opacity = 0.25;
	helper.material.transparent = true;
	scene.add( helper );
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function initLights() {	

    for (let i = tLights.L_AMBIENT ; i <= tLights.L_HEMI ; i++) {
		switch (i) {
			case tLights.L_AMBIENT 		: 	lights[i] = new THREE.AmbientLight( 0xFFFFFF, 1.0 );
											lights[i].name 			= "ambLight";
											lights[i].visible 		= true;
											helperLights[i]			= null;											
											break;

			case tLights.L_DIRECIONAL 	: 	lights[i] = new THREE.DirectionalLight( 0xFFFFFF, 1.0 ); 
											lights[i].name 			= "dirLight";
											lights[i].visible 		= false;
											lights[i].position.set( 0.0, maxCoord, maxCoord );

											helperLights[i]			= new THREE.DirectionalLightHelper( lights[i], 4.0 );
											helperLights[i].name 	= "dirLightHlpr";
											helperLights[i].visible	= false;
											break;


			case tLights.L_POINT 	 	: 	lights[i] = new THREE.PointLight( 0xFFFFFF, 100.0, 0 );
											lights[i].name 			= "pntLight";
											lights[i].visible 		= false;
											lights[i].position.set( maxCoord, maxCoord , 0.0);

											helperLights[i] 		= new THREE.PointLightHelper( lights[i]);
											helperLights[i].name 	= "pntLightHlpr";
											helperLights[i].visible	= false;
											break;

			case tLights.L_SPOT 		: 	lights[i] = new THREE.SpotLight( 0xFFFFFF, 100.0, maxCoord*100.0, Math.PI*60.0/180.0 );
											lights[i].name 			= "sptLight";
											lights[i].visible 		= false;
											lights[i].position.set(0.0, maxCoord, 0.0 );

											helperLights[i] 		= new THREE.SpotLightHelper( lights[i] );
											helperLights[i].name 	= "sptLightHlpr";
											helperLights[i].visible	= false;
											break;

			case tLights.L_RECT  		:   RectAreaLightUniformsLib.init();
											const width = maxCoord;
											const height = maxCoord;
											const intensity = 1000;
											lights[i] = new THREE.RectAreaLight( 0xffffff, intensity,  width, height );
											lights[i].position.set(maxCoord, maxCoord , maxCoord );		
											lights[i].name 			= "sptLight";
											lights[i].visible 		= false;								
											helperLights[i] = new RectAreaLightHelper( lights[i] );
											helperLights[i].name 	= "rectLightHlpr";
											helperLights[i].visible	= false;											
											break;

			case tLights.L_HEMI  		:  	lights[i] = new THREE.HemisphereLight( 0xffffff, 0xffffff, 2 );
											lights[i].color.setHSL( 0.6, 1, 0.6 );
											lights[i].groundColor.setHSL( 0.095, 1, 0.75 );
											lights[i].position.set(maxCoord, maxCoord , maxCoord );		
											lights[i].name 			= "hemiLight";
											lights[i].visible 		= false;								
											helperLights[i] = new THREE.HemisphereLightHelper( lights[i] );
											helperLights[i].name 	= "hemiLightHlpr";
											helperLights[i].visible	= false;											
											break;
																			
		}
		scene.add( lights[i] );
		if (helperLights[i])
			scene.add( helperLights[i] );
		}
}


/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function initGUI() {	
	params = 	{	luzOn		: true,
					tipoLuz		: "Ambiente",
					ShadeAlg	: "Basic"
				};

	gui.add( params, 'luzOn').onChange(function()	{ 	lights[curLight].visible = params.luzOn;
														if (helperLights[curLight])
															helperLights[curLight].visible = params.luzOn;
													});
	gui.add( params, 'tipoLuz', [ 	"Ambiente", 
									"Direcional", 
									"Pontual", 
									"Spot" ,
									"Rect",
									"Hemi"] ).onChange(changeLight);

	gui.open();
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function changeLight() { 

	lights[curLight].visible = false;

	if (helperLights[curLight])
		helperLights[curLight].visible = false;

	switch (params.tipoLuz) {
		case "Ambiente" 	: 	curLight 		= tLights.L_AMBIENT;
								break;

		case "Direcional" 	: 	curLight 		= tLights.L_DIRECIONAL;
								break;

		case "Pontual" 		: 	curLight 		= tLights.L_POINT;
								break;

		case "Spot" 		: 	curLight 		= tLights.L_SPOT;
								break;
		case "Rect" 		: 	curLight 		= tLights.L_RECT;
								break;
		case "Hemi" 		: 	curLight 		= tLights.L_HEMI;
								break;
		}

	if (params.luzOn) {

		lights[curLight].visible = true;

		if (helperLights[curLight])
			helperLights[curLight].visible = true;
		}
}

main();
