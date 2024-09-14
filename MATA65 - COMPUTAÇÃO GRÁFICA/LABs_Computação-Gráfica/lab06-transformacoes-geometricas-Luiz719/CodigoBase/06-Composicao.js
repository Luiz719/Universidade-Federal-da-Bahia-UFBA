// Commposição de Transformações Geométricas.

import * as THREE from 'three';
import { GUI } 		from 'gui'

const 	rendSize 	= new THREE.Vector2();
var 	pos 		= 0.0;

var 	scene,
		renderer,
		camera,
		controls;

var gui = new GUI();

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function main() {

	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	rendSize.x = 
	rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);

	document.body.appendChild(renderer.domElement);

	scene 	= new THREE.Scene();

	camera = new THREE.OrthographicCamera( -5.0, 5.0, 5.0, -5.0, -1.0, 1.0 );
	scene.add( camera );

	initGUI();

	buildScene();

	renderer.render(scene, camera);
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function initGUI() {

	controls = 	{	UseMatrix : false,
					};

	gui.add( controls, 'UseMatrix').onChange(mudaMatrizes);
	gui.open();
};

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function mudaMatrizes(val) {

	if (val) {
		scene.getObjectByName("TransObjProp").visible 	= false;
		scene.getObjectByName("TransObjMatrix").visible = true;
		}
	else {
		scene.getObjectByName("TransObjProp").visible 	= true;
		scene.getObjectByName("TransObjMatrix").visible = false;
		}

	renderer.render(scene, camera);
}

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function buildScene() {

	var axis = new THREE.AxesHelper(5.0);
	scene.add(axis);

	// ***************************************************************
	// Grupo de objetos com transformações controladas pelos atributos 

	var grpObjTransf = new THREE.Object3D();
	grpObjTransf.name = "TransObjProp";

	var quad0 	= new THREE.Mesh 	( 	new THREE.PlaneGeometry( 1.0, 1.0 ), 
										new THREE.MeshBasicMaterial( {color:0xFFFFFF} ), 
									);
	quad0.name = "QuadBranco";
	quad0.scale.copy( new THREE.Vector3(2.0, 2.0, 1.0)); 
	quad0.rotateZ(Math.PI / 4.0);
	quad0.position.x = 0.0;
	quad0.position.y = 2.0;
	grpObjTransf.add(quad0);

	var quad1 	= new THREE.Mesh 	( 	new THREE.PlaneGeometry( 1.0, 1.0 ), 
										new THREE.MeshBasicMaterial( {color:0xFF0000} ), 
									);
	quad1.name = "QuadVerm";
	quad1.position.x = 0.0;
	quad1.position.y = 2.0;
	quad1.rotateZ(Math.PI / 4.0);
	quad1.scale.copy( new THREE.Vector3(1.5, 1.5, 1.0)); 
	grpObjTransf.add(quad1);

	var quad2 	= new THREE.Mesh 	( 	new THREE.PlaneGeometry( 1.0, 1.0 ), 
										new THREE.MeshBasicMaterial( {color:0x0000FF} ), 
									);
	quad2.name = "QuadAzul";
	quad2.position.x = 0.0;
	quad2.position.y = 2.0;
	quad2.scale.copy( new THREE.Vector3(1.0, 1.0, 1.0)); 
	quad2.rotateZ(Math.PI / 4.0);
	grpObjTransf.add(quad2);

	scene.add(grpObjTransf);

	// ***************************************************************
	// Grupo de objetos com transformações controladas por matrizes 

	var grpMatrixTransf = new THREE.Object3D();
	grpMatrixTransf.name = "TransObjMatrix";
	grpMatrixTransf.visible = false;

	var trans 		= new THREE.Matrix4().makeTranslation(0.0, 2.0, 0.0);
	var rot 		= new THREE.Matrix4().makeRotationZ(Math.PI / 4.0);
	var scale3 		= new THREE.Matrix4().makeScale(2.0, 2.0, 1.0);
	var scale4 		= new THREE.Matrix4().makeScale(1.5, 1.5, 1.0);
	var scale5 		= new THREE.Matrix4().makeScale(1.0, 1.0, 1.0);

	var compMat3	= new THREE.Matrix4();
	var compMat4	= new THREE.Matrix4();
	var compMat5	= new THREE.Matrix4();

	compMat3.multiply(scale3);
	compMat3.multiply(rot);
	compMat3.multiply(trans);
	
	compMat4.multiply(trans);
	compMat4.multiply(rot);
	compMat4.multiply(scale4);

	compMat5.multiply(trans);
	compMat5.multiply(scale5);
	compMat5.multiply(rot);

	var quad3 	= new THREE.Mesh 	( 	new THREE.PlaneGeometry( 1.0, 1.0 ), 
										new THREE.MeshBasicMaterial( {color:0xFFFFFF} ), 
									);
	quad3.name = "QuadBrancoM";
	quad3.matrix.copy(compMat3);
	quad3.matrixAutoUpdate = false;
	grpMatrixTransf.add(quad3);

	var quad4 	= new THREE.Mesh 	( 	new THREE.PlaneGeometry( 1.0, 1.0 ), 
										new THREE.MeshBasicMaterial( {color:0xFF0000} ), 
									);
	quad4.name = "QuadVermM";
	quad4.matrix.copy(compMat4);
	quad4.matrixAutoUpdate = false;
	grpMatrixTransf.add(quad4);

	var quad5 	= new THREE.Mesh 	( 	new THREE.PlaneGeometry( 1.0, 1.0 ), 
										new THREE.MeshBasicMaterial( {color:0x0000FF} ), 
									);
	quad5.name = "QuadAzulM";
	quad5.matrix.copy(compMat5);
	quad5.matrixAutoUpdate = false;
	grpMatrixTransf.add(quad5);						

	scene.add(grpMatrixTransf);
};

/// ***************************************************************
/// ***************************************************************
/// ***************************************************************

main();
