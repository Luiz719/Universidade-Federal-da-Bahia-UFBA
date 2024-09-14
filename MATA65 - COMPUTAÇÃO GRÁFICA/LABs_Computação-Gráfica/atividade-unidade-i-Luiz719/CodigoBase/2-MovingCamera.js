// Controle de camera com GUI.

import * as THREE 	from 'three';
import { FontLoader } from '../Assets/scripts/three.js/examples/jsm/loaders/FontLoader.js';
import { TextGeometry } from '../Assets/scripts/three.js/examples/jsm/geometries/TextGeometry.js';

THREE.Cache.enabled = true;
const 	rendSize 	= new THREE.Vector2();

var scene 			= null;
var renderer		= null;
var cameraPersp		= null;
var cameraOrto		= null;
var cameraHelper 	= null;
let group, textGeo, font;
let text = 'AURORA';
let bevelEnabled = true;
let fontName = 'gentilis';
let fontWeight = 'regular';

const depth = 20,
    size = 70,
    hover = 30,
    curveSegments = 4,
    bevelThickness = 2,
    bevelSize = 1.5;

let time = 0.0;

const splineHelperObjects = [];
let splinePointsLength = 4;
const positions = [];
const point = new THREE.Vector3();

const geometry = new THREE.BoxGeometry( 20, 20, 20 );

const ARC_SEGMENTS = 200;

const splines = {};

const params = {
    uniform: false,
    tension: 0.5,
    centripetal: false,
    chordal: false,
    addPoint: addPoint,
};

let progress = 0;
var returning = false;

/// ***************************************************************
/// **                                                           **
/// ***************************************************************

function main() {

	renderer = new THREE.WebGLRenderer();

	renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

	rendSize.x = Math.min(window.innerWidth, window.innerHeight) * 1.6;
	rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

	renderer.setSize(rendSize.x, rendSize.y);
	renderer.autoClear = false;

	document.body.appendChild(renderer.domElement);

	scene 	= new THREE.Scene();

	cameraPersp = new THREE.PerspectiveCamera();
	cameraPersp.fov 		= 70.0;
	cameraPersp.aspect 		= 1.0;
	cameraPersp.near 		= 1.0;
	cameraPersp.far			= 800.0;
	cameraPersp.position.x	= 0.0;
	cameraPersp.position.y	= 75.0;
	cameraPersp.position.z	= 600.0;

	scene.add( cameraPersp );

	cameraHelper = new THREE.CameraHelper(cameraPersp);
	scene.add( cameraHelper );

	cameraOrto = new THREE.OrthographicCamera(-700.0, 700.0, 700.0, -700.0, -1000.0, 1000.0);
	cameraOrto.position.x	= 40.0;
	cameraOrto.position.y	= 40.0;
	cameraOrto.position.z	= 40.0;
	cameraOrto.lookAt(new THREE.Vector3(0.0, 0.0, 0.0));

	group = new THREE.Group();
	scene.add(group);

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

    load([new THREE.Vector3(517.8948138100151, 368.20833723775337, -68.14695576714183),
		new THREE.Vector3(433.1106109599462, 187.33216755225334, 56.17866282558245),
		new THREE.Vector3(-188.51432395762038, -83.52037142248756, 221.37312352298727),
		new THREE.Vector3(-383.5859059887566, 299.5764901590089, -165.41585868581245)]);

	loadFont();

	render();
};

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function loadFont() {
    const loader = new FontLoader();
    loader.load('fonts/' + fontName + '_' + fontWeight + '.typeface.json', function (response) {
        font = response;
        refreshText();
    });
}

function createText() {
    const letters = [];
    let offsetX = 0;

    const vertexShader = `
    uniform float time;
    uniform float hover;
    uniform float index;
    void main() {
        vec3 transformed = position;
        float delay = pow(index, 2.0) * 0.1;

        transformed.y += sin(time) * 20.0;
        transformed.x += cos(time) * 20.0;

        float movementType = mod(index, 3.0);
        if (movementType == 0.0) {
            transformed.y += sin(time - delay) * 20.0;
        } else if (movementType == 1.0) {
            transformed.x += sin(time - delay) * 20.0;
        } else {
            float rotationAngle = sin(time - delay) * 0.5;
            mat3 rotation = mat3(
                cos(rotationAngle), 0.0, sin(rotationAngle),
                0.0, 1.0, 0.0,
                -sin(rotationAngle), 0.0, cos(rotationAngle)
            );
            transformed = rotation * transformed;
        }

        vec4 mvPosition = modelViewMatrix * vec4(transformed, 1.0);
        gl_Position = projectionMatrix * mvPosition;
    }
`;

    const fragmentShader = `
        void main() {
            gl_FragColor = vec4(1.0, 0.2, 0.3, 1.0);
        }
    `;

    for (let i = 0; i < text.length; i++) {
        if (text[i] === " ") continue;

        textGeo = new TextGeometry(text[i], {
            font: font,
            size: size,
            depth: depth,
            curveSegments: curveSegments,
            bevelThickness: bevelThickness,
            bevelSize: bevelSize,
            bevelEnabled: bevelEnabled
        });

        textGeo.computeBoundingBox();

        const letterWidth = textGeo.boundingBox.max.x - textGeo.boundingBox.min.x;

        const uniforms = {
            time: { value: time },
            hover: { value: hover },
            index: { value: i }
        };

        const shaderMaterial = new THREE.ShaderMaterial({
            uniforms: uniforms,
            vertexShader: vertexShader,
            fragmentShader: fragmentShader,
            side: THREE.DoubleSide
        });

        let textMesh = new THREE.Mesh(textGeo, shaderMaterial);
        textMesh.position.x = offsetX;
        textMesh.position.y = hover;
        textMesh.position.z = 0;
        letters.push(textMesh);

        offsetX += letterWidth + 10.5;
        group.add(textMesh);
    }

    const totalWidth = offsetX - 10.5;
    letters.forEach(letter => {
        letter.position.x -= totalWidth / 2;
    });
}

function refreshText() {
    group.clear();
    if (!text) return;
    createText();
}

function addSplineObject( position ) {

    const material = new THREE.MeshLambertMaterial( { color: 1.0 * 0xffffff } );
    const object = new THREE.Mesh( geometry, material );

    if ( position ) {

        object.position.copy( position );

    } else {

        object.position.x = Math.random() * 1000 - 500;
        object.position.y = Math.random() * 600;
        object.position.z = Math.random() * 800 - 400;

    }

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

    time += 0.05;
    group.children.forEach((child, index) => {
        child.material.uniforms.time.value = time;
        child.material.uniforms.index.value = index;
    });

    renderer.clear(true, true);

	//CAMERA FOLLOW CURVE
    splines.uniform.mesh.visible = params.uniform;
    splines.centripetal.mesh.visible = params.centripetal;
    splines.chordal.mesh.visible = params.chordal;

    const speed = 0.001;
    if (progress >= 1) {
        returning = true;
    } else if (progress <= 0) {
        returning = false;
    }

    if (returning) {
        progress -= speed;
    } else {
        progress += speed;
    }

    progress = Math.max(0, Math.min(1, progress));

    const pointOnCurve = new THREE.Vector3();
    splines.uniform.getPointAt(progress, pointOnCurve);

    cameraPersp.position.copy(pointOnCurve);

    const nextPointOnCurve = new THREE.Vector3();
    splines.uniform.getPointAt((progress + 0.01) % 1, nextPointOnCurve);

    cameraPersp.lookAt(group.position);

	//PIP
    renderer.setViewport(0.0, 0.0, rendSize.x, rendSize.y);
    cameraPersp.updateProjectionMatrix();
    cameraHelper.visible = false;
    cameraHelper.update();
    renderer.render(scene, cameraPersp);

    const pipWidth = rendSize.x / 3.0;
    const pipHeight = rendSize.y / 3.0;
    const pipX = rendSize.x - pipWidth - 10;  
    const pipY = 10;                          

    renderer.setViewport(pipX, pipY, pipWidth, pipHeight);
    cameraHelper.visible = true;
    cameraOrto.updateProjectionMatrix();
    cameraHelper.update();
    renderer.render(scene, cameraOrto);

    requestAnimationFrame(render);
}

/// ***************************************************************
/// ***                                                          **
/// ***************************************************************

function onWindowResize() {

    cameraPersp.aspect = window.innerWidth / window.innerHeight;
    cameraPersp.updateProjectionMatrix();

    renderer.setSize( window.innerWidth, window.innerHeight );

    render();

}

main();

