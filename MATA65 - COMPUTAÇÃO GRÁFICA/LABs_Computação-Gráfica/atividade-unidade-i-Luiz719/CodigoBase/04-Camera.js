import * as THREE from 'three';

import { OrbitControls } from '../Assets/scripts/three.js/examples/jsm/controls/OrbitControls.js';

let camera, scene, renderer;
const splineHelperObjects = [];
let splinePointsLength = 4;
const positions = [];
const point = new THREE.Vector3();

const geometry = new THREE.BoxGeometry( 20, 20, 20 );

const ARC_SEGMENTS = 200;

const splines = {};

const params = {
    uniform: true,
    tension: 0.5,
    centripetal: true,
    chordal: true,
    addPoint: addPoint,
};

init();

function init() {

    scene = new THREE.Scene();
    scene.background = new THREE.Color( 0xf0f0f0 );

    camera = new THREE.PerspectiveCamera( 70, window.innerWidth / window.innerHeight, 1, 10000 );
    camera.position.set( 0, 250, 1000 );
    scene.add( camera );

    renderer = new THREE.WebGLRenderer( { antialias: true } );
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize( window.innerWidth, window.innerHeight );
    renderer.shadowMap.enabled = true;
    document.body.appendChild(renderer.domElement);

    // Controls
    const controls = new OrbitControls( camera, renderer.domElement );
    controls.damping = 0.2;
    controls.addEventListener( 'change', render );

    window.addEventListener( 'resize', onWindowResize );

    /*******
     * Curves
     *********/

    for ( let i = 0; i < splinePointsLength; i ++ ) {

        addSplineObject( positions[ i ] );

    }

    positions.length = 0;

    for ( let i = 0; i < splinePointsLength; i ++ ) {

        positions.push( splineHelperObjects[ i ].position );

    }

    const geometry = new THREE.BufferGeometry();
    geometry.setAttribute( 'position', new THREE.BufferAttribute( new Float32Array( ARC_SEGMENTS * 3 ), 3 ) );

    let curve = new THREE.CatmullRomCurve3( positions );
    curve.curveType = 'catmullrom';
    curve.mesh = new THREE.Line( geometry.clone(), new THREE.LineBasicMaterial( {
        color: 0xff0000,
        opacity: 0.35
    } ) );
    curve.mesh.castShadow = true;
    splines.uniform = curve;

    curve = new THREE.CatmullRomCurve3( positions );
    curve.curveType = 'centripetal';
    curve.mesh = new THREE.Line( geometry.clone(), new THREE.LineBasicMaterial( {
        color: 0x00ff00,
        opacity: 0.35
    } ) );
    curve.mesh.castShadow = true;
    splines.centripetal = curve;

    curve = new THREE.CatmullRomCurve3( positions );
    curve.curveType = 'chordal';
    curve.mesh = new THREE.Line( geometry.clone(), new THREE.LineBasicMaterial( {
        color: 0x0000ff,
        opacity: 0.35
    } ) );
    curve.mesh.castShadow = true;
    splines.chordal = curve;

    for ( const k in splines ) {

        const spline = splines[ k ];
        scene.add( spline.mesh );

    }

    load( [ new THREE.Vector3( 289.76843686945404, 452.51481137238443, 56.10018915737797 ),
        new THREE.Vector3( - 53.56300074753207, 171.49711742836848, - 14.495472686253045 ),
        new THREE.Vector3( - 91.40118730204415, 176.4306956436485, - 6.958271935582161 ),
        new THREE.Vector3( - 383.785318791128, 491.1365363371675, 47.869296953772746 ) ] );

    render();

}

function addSplineObject( position ) {

    const material = new THREE.MeshLambertMaterial( { color: Math.random() * 0xffffff } );
    const object = new THREE.Mesh( geometry, material );

    if ( position ) {

        object.position.copy( position );

    } else {

        object.position.x = Math.random() * 1000 - 500;
        object.position.y = Math.random() * 600;
        object.position.z = Math.random() * 800 - 400;

    }

    object.castShadow = true;
    object.receiveShadow = true;
    object.visible = false;
    scene.add( object );
    splineHelperObjects.push( object );
    return object;

}

function addPoint() {

    splinePointsLength ++;

    positions.push( addSplineObject().position );

    updateSplineOutline();

    render();

}


function updateSplineOutline() {

    for ( const k in splines ) {

        const spline = splines[ k ];

        const splineMesh = spline.mesh;
        const position = splineMesh.geometry.attributes.position;

        for ( let i = 0; i < ARC_SEGMENTS; i ++ ) {

            const t = i / ( ARC_SEGMENTS - 1 );
            spline.getPoint( t, point );
            position.setXYZ( i, point.x, point.y, point.z );

        }

        position.needsUpdate = true;

    }

}


function load( new_positions ) {

    while ( new_positions.length > positions.length ) {

        addPoint();

    }

    for ( let i = 0; i < positions.length; i ++ ) {

        positions[ i ].copy( new_positions[ i ] );

    }

    updateSplineOutline();

}

function render() {

    splines.uniform.mesh.visible = params.uniform;
    splines.centripetal.mesh.visible = params.centripetal;
    splines.chordal.mesh.visible = params.chordal;
    renderer.render( scene, camera );

}

function onWindowResize() {

    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();

    renderer.setSize( window.innerWidth, window.innerHeight );

    render();

}
