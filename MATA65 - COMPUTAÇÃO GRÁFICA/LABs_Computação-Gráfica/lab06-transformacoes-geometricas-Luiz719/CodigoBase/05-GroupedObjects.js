// Objetos no World Space.
import * as THREE from 'three';


const   rendSize    = new THREE.Vector2();


var     scene,
        renderer,
        camera,
        shouldRotate = true;

function main() {


   renderer = new THREE.WebGLRenderer();


   renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));


   rendSize.x =
   rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;


   renderer.setSize(rendSize.x, rendSize.y);


   document.body.appendChild(renderer.domElement);


   scene   = new THREE.Scene();


   camera = new THREE.OrthographicCamera( -1.0, 1.0, 1.0, -1.0, -5.0, 5.0 );
   scene.add( camera );
  
   buildScene();


   renderer.clear();
   renderer.render(scene, camera);
   
   animate();
};


/// ***************************************************************
/// **                                                           **
/// ***************************************************************


function buildScene() {

   // Box 
   var box = new THREE.BoxGeometry( 0.2, 0.2, 0.2 );             
   var boxMat = new THREE.MeshBasicMaterial( {color: 0x0000ff,wireframe:true} );
   var cube = new THREE.Mesh( box, boxMat );

   // Sphere
   var sphereGeometry = new THREE.SphereGeometry( 0.2, 10, 10 );                
   var sphereMat = new THREE.MeshBasicMaterial( {color: 0xff0000, wireframe:true} );
   var sphere = new THREE.Mesh( sphereGeometry, sphereMat );
 
   // Ring
   var ringGeometry = new THREE.RingGeometry( 0.2, 0.1, 15, 3 );                
   var ringMat = new THREE.MeshBasicMaterial( {color: 0x00ff00, wireframe:true} );
   var ring = new THREE.Mesh( ringGeometry, ringMat );
   ring.translateX(1.4);
  
   // TorusKnot
   var torusKnotGeometry = new THREE.TorusKnotGeometry( 0.2, 0.03, 60, 20, 3, 2 );                
   var torusKnotMat = new THREE.MeshBasicMaterial( {color: 0x7070aa, wireframe:true} );
   var torusKnot = new THREE.Mesh( torusKnotGeometry, torusKnotMat );
   torusKnot.translateX(-0.7);
  
   // Cilinder
   var cilinderGeometry = new THREE.CylinderGeometry( 0.1, 0.1, 0.5, 30);                
   var cilinderMat = new THREE.MeshBasicMaterial( {color: 0xffff00, wireframe:true} );
   var cilinder = new THREE.Mesh( cilinderGeometry, cilinderMat );
   cilinder.translateX(0.7);
  
   // Icosahedron
   var icosahedronGeometry = new THREE.IcosahedronGeometry(0.2);                
   var icosahedronMat = new THREE.MeshBasicMaterial( {color: 0x00ffff, wireframe:true} );
   var icosahedron = new THREE.Mesh( icosahedronGeometry, icosahedronMat );
   icosahedron.translateX(0.7);
  
   // Plane
   var planeGeometry = new THREE.PlaneGeometry(0.2, 0.5, 10, 10);                
   var planeMat = new THREE.MeshBasicMaterial( {color: 0xff00ff, wireframe:true} );
   var plane = new THREE.Mesh( planeGeometry, planeMat );
   plane.translateX(-1.4);
  
   // Tetrahedron
   var tetrahedronGeometry = new THREE.TetrahedronGeometry(0.2);                
   var tetrahedronMat = new THREE.MeshBasicMaterial( {color: 0x70aa70, wireframe:true} );
   var tetrahedron = new THREE.Mesh( tetrahedronGeometry, tetrahedronMat );
   tetrahedron.translateX(-0.7);

   // Dodecahedron
   var dodecahedronGeometry = new THREE.DodecahedronGeometry(0.2);                
   var dodecahedronMat = new THREE.MeshBasicMaterial( {color: 0xaa7070, wireframe:true} );
   var dodecahedron = new THREE.Mesh( dodecahedronGeometry, dodecahedronMat );

   const group1 = new THREE.Group();
   const group2 = new THREE.Group();
   const group3 = new THREE.Group();

   var axis1 = new THREE.AxesHelper( 0.3 );
   var axis2 = new THREE.AxesHelper( 0.3 );
   var axis3 = new THREE.AxesHelper( 0.3 );


   group1.add( axis1 );
   group2.add( axis2 );
   group3.add( axis3 );

   group1.position.copy(new THREE.Vector3(-0.7, 0.7, 0));
   group3.position.copy(new THREE.Vector3(0.7, -0.7, 0));

   group1.add(cube);
   group1.add(cilinder);
   group1.add(ring);
   group2.add(torusKnot);
   group2.add(sphere);
   group2.add(icosahedron);
   group3.add(plane);
   group3.add(tetrahedron);
   group3.add(dodecahedron);

   scene.add(group1, group2, group3);
}

function animate() {
    if (shouldRotate) {
        scene.traverse(function (object) {
            if (object instanceof THREE.Group) {
                object.rotateOnAxis(new THREE.Vector3(0,1,0), 0.01);         
            }
        });
    }

    renderer.render(scene, camera);
    requestAnimationFrame(animate);
}
/// ***************************************************************
/// ***************************************************************
/// ***************************************************************


main();





