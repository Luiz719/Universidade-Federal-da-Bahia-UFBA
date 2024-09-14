import * as THREE from 'three';
import { FontLoader } from '../Assets/scripts/three.js/examples/jsm/loaders/FontLoader.js';
import { TextGeometry } from '../Assets/scripts/three.js/examples/jsm/geometries/TextGeometry.js';

THREE.Cache.enabled = true;

const rendSize = new THREE.Vector2();

let camera, scene, renderer;
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

init();
animate();

function init() {
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

    rendSize.x = Math.min(window.innerWidth, window.innerHeight) * 1.6;
    rendSize.y = Math.min(window.innerWidth, window.innerHeight) * 0.8;

    renderer.setSize(rendSize.x, rendSize.y);
    document.body.appendChild(renderer.domElement);

    // CAMERA
    camera = new THREE.PerspectiveCamera(50, window.innerWidth / window.innerHeight, 1, 1500);
    camera.position.set(0, 75, 700);

    // SCENE
    scene = new THREE.Scene();
    scene.background = new THREE.Color(0x000000);

    group = new THREE.Group();
    scene.add(group);

    loadFont();
}

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

function animate() {
    requestAnimationFrame(animate);
    time += 0.05;
    group.children.forEach((child, index) => {
        child.material.uniforms.time.value = time;
        child.material.uniforms.index.value = index;
    });
    renderer.render(scene, camera);
}
