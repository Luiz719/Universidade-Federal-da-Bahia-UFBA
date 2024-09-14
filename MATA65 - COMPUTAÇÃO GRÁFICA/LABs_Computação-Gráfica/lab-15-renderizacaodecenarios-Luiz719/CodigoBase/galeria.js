// Sombras "hard"

import * as THREE 			from 'three';
import { FirstPersonControls } 	from 'fps-cam-ctrl';
import { GLTFLoader } 		from 'GLTF-Loader';


const   rendSize    	= new THREE.Vector2();

let 	scene 			= null;
let 	renderer		= null;
let 	camera 			= null;
let 	controls	    = null;
let     gallerySize;
let 	clock 			= new THREE.Clock();

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function main() {

	scene 						= new THREE.Scene();

    rendSize.x 					= window.innerWidth*0.7;
    rendSize.y 					= window.innerHeight*0.7;

	renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.shadowMap.enabled = true;
    renderer.shadowMap.type = THREE.PCFSoftShadowMap;

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));
	renderer.setSize(rendSize.x, rendSize.y);

    document.body.appendChild(renderer.domElement);

    camera = new THREE.PerspectiveCamera(70, rendSize.x / rendSize.y, 0.1, 100.0);
    camera.position.set(0.0, 1.5, 5.0);
    camera.lookAt(0, 1, 0);

	// Controle de Camera Orbital
	controls 				= new FirstPersonControls(camera, renderer.domElement);
	controls.autoRotate 	= false;
	controls.lookSpeed = 0;
	buildScene();
   	initLight();

	renderer.clear();
	render();
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function buildScene() {
    let globalAxis = new THREE.AxesHelper(1.0);
    scene.add(globalAxis);

    const gltfLoader = new GLTFLoader();
    gltfLoader.load('./modelos/galeria/scene.gltf', loadMesh);
} 
let matrix;

function loadMesh(loadedMesh) {
    const root = loadedMesh.scene;
    root.name = "galeria";
    matrix = root.matrix;
    root.traverse((child) => {
        if (child.isMesh) {
            child.receiveShadow = true;
        }
    });

    const galleryBox = new THREE.Box3().setFromObject(root);
    gallerySize = galleryBox.getSize(new THREE.Vector3());
    scene.add(root);

    const budLoader = new GLTFLoader();
    budLoader.load('./modelos/esculturas/bud/scene.gltf', loadSculptures); 
    const dragonLoader = new GLTFLoader();
    dragonLoader.load('./modelos/esculturas/dragon/scene.gltf', loadSculptures);

    const deerLoader = new GLTFLoader();
    deerLoader.load('./modelos/esculturas/deer/scene.gltf', loadSculptures);

    const taurusLoader = new GLTFLoader();
    taurusLoader.load('./modelos/esculturas/taurus/scene.gltf', loadSculptures);

    const landLoader = new GLTFLoader();
    landLoader.load('./modelos/pinturas/land/scene.gltf', loadPictures);
 
    const artLoader = new GLTFLoader();
    artLoader.load('./modelos/pinturas/art/scene.gltf',loadPictures); 
}

function loadSculptures(loadedMesh) {
    const root = loadedMesh.scene;
    const bbox = new THREE.Box3().setFromObject(root);
    const size = new THREE.Vector3();
    bbox.getSize(size);

    const name = root.name;
    let scaleFactor;
    switch (name) {
        case 'bud':
            scaleFactor = 1.0 / Math.max(size.x, size.y, size.z);
            root.scale.setScalar(scaleFactor);
            root.position.set(0, -bbox.min.y * scaleFactor + 0.8, 0);
            break;
        case 'dragon':
            scaleFactor = gallerySize.y / (3* size.y); 
            root.scale.set(scaleFactor, scaleFactor, scaleFactor);
            root.position.set(3.0, -bbox.min.y * scaleFactor, 3.0);
            root.rotation.y += Math.PI;
            break;
        case 'deer':
            scaleFactor = gallerySize.y / (3* size.y); 
            root.scale.set(scaleFactor, scaleFactor, scaleFactor);
            root.position.set(3.0, -bbox.min.y * scaleFactor, -3.0);
            break;
        case 'taurus':
            scaleFactor = gallerySize.y / (3* size.y); 
            root.scale.set(scaleFactor, scaleFactor, scaleFactor);
            root.position.set(-4.0, -bbox.min.y * scaleFactor, 0);
            break;
    }

    var spotLight;
    if(name == "bud"){
        spotLight = new THREE.SpotLight(0xe8dd09, 50);
    }else{
        spotLight = new THREE.SpotLight(0xffffff, 50);
    }
    spotLight.position.set(root.position.x, 3, root.position.z);
    spotLight.target = root;
    spotLight.angle = Math.PI / 6;
    spotLight.penumbra = 0.1;
    spotLight.distance = 10;
    spotLight.castShadow = true;

    scene.add(spotLight);
    scene.add(root);

    root.traverse((child) => {
        if (child.isMesh) {
            child.castShadow = true;
        }
    });
}

function loadPictures(loadedMesh) {
    const root = loadedMesh.scene;
  
    const pictureBox = new THREE.Box3().setFromObject(root);
    const pictureSize = pictureBox.getSize(new THREE.Vector3());

    const name = root.name;

    let wallLength = gallerySize.x,
        x,
        z,
        scaleFactor;

    switch (name) {
        case 'land':
            scaleFactor = gallerySize.y / (2* pictureSize.y); 
            root.scale.set(scaleFactor, scaleFactor, scaleFactor);
            x = wallLength / 2 -0.03;
            z = 0;
            root.position.set(x, gallerySize.y / 2 -0.5, z);
            root.rotation.y = Math.PI / 2 ;
            break;
        case 'art':
            scaleFactor = gallerySize.y / (2* pictureSize.y); 
            root.scale.set(scaleFactor, scaleFactor, scaleFactor);
            x = 0;
            z = -wallLength / 2 +0.03; 
            root.position.set(x, gallerySize.y / 2 -0.5, z);        
            break;
    }

    const spotLight = new THREE.SpotLight(0xd7adad, 50);
    if(name == "land"){
        spotLight.position.set(4.02, 3.44, 0.82); 
        spotLight.target.position.set(10,0,-0.9);
        spotLight.angle = 44.28 * (Math.PI / 180);
    }else{
        spotLight.position.set(1.56, 3.44, -4.58); 
        spotLight.target.position.set(-1.14,0,-7.3);
        spotLight.angle = 33.21 * (Math.PI / 180);
    }
    spotLight.penumbra = 0.15;
    spotLight.distance = 5.4;
    spotLight.castShadow = true;
    scene.add(spotLight);
    scene.add(spotLight.target);
    scene.add(root);

    root.traverse((child) => {
        if (child.isMesh) {
            child.castShadow = true;
        }
    });
}


/// ***************************************************************
/// **                                                           **
/// ***************************************************************
function initLight() {
    const pLight = new THREE.PointLight(0xFFFFFF, 20);
    pLight.castShadow = true;
    pLight.shadow.mapSize.width = 1024;
    pLight.shadow.mapSize.height = 1024;
    pLight.name = "pLight";
    pLight.position.set(0, 4.5, 0);

    scene.add(pLight);
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function render() {
	let delta = clock.getDelta();
    controls.update(delta);
	renderer.render(scene, camera);
	requestAnimationFrame(render);
}

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************
main();
