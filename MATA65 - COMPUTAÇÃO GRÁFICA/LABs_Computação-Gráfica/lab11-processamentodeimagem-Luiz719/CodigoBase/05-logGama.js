import * as THREE from 'three';
import { GUI } from 'gui';

const gui = new GUI();

let scene, camera, renderer, weights, parameters, oTex;

const transformations = { "None": 0, "Log": 1, "Gamma": 2 };

function main() {
    scene = new THREE.Scene();
    renderer = new THREE.WebGLRenderer();
    renderer.autoClear = false;
    renderer.setClearColor(new THREE.Color(0.0, 0.0, 0.0));

    buildGUI();

    camera = new THREE.OrthographicCamera(-0.5, 0.5, 0.5, -0.5, -1.0, 1.0);
    scene.add(camera);

    let textureLoader = new THREE.TextureLoader();
    textureLoader.load("../../Assets/Images/lena.png", onLoadTexture);

    document.getElementById("threejs-canvas").appendChild(renderer.domElement);

    let globalAxis = new THREE.AxesHelper(1.0);
    scene.add(globalAxis);
}

function onLoadTexture(tex) {
    if (!tex.image) {
        console.log("ERROR: loading texture");
    } else {
        oTex = tex;
        console.log("Image size: " + tex.image.width + " x " + tex.image.height);
        console.log("Pixel size: " + 1.0 / tex.image.width + " x " + 1.0 / tex.image.height);

        weights = new THREE.Vector3(1, 1, 1);

        const matShader = new THREE.ShaderMaterial({
            uniforms: {
                uSampler: { type: "t", value: tex },
                uW: { type: "v3", value: weights },
                uC: { type: "f", value: 1.0 },
                uGama: { type: "f", value: 1.0 },
                uTransform: { type: "i", value: 0 },
            },
            vertexShader: document.getElementById('grayScale-vs').textContent,
            fragmentShader: document.getElementById('grayScale-fs').textContent
        });

        let plane = new THREE.Mesh(new THREE.PlaneGeometry(1.0, 1.0, 20, 20), matShader);
        plane.position.set(0.0, 0.0, -0.5);
        plane.name = "Imagem";
        scene.add(plane);

        renderer.setSize(tex.image.width, tex.image.height);
        update();
    }
}

function buildGUI() {
    parameters = { transform: 'None', c: 1.0, gama: 1.0 };

    gui.add(parameters, 'transform', Object.keys(transformations)).onChange(update);
    gui.add(parameters, 'c').min(0.0).max(5.0).step(0.1).onChange(update);
    gui.add(parameters, 'gama').min(0.0).max(15.0).step(0.1).onChange(update);

    gui.open();
}

function update() {
    let obj = scene.getObjectByName("Imagem");

    if (obj) {
        obj.material.uniforms.uC.value = parameters.c;
        obj.material.uniforms.uGama.value = parameters.gama;
        obj.material.uniforms.uTransform.value = transformations[parameters.transform];
        obj.material.uniformsNeedUpdate = true;

        weights.set(1, 0, 0);
        obj.material.uniforms.uW.value = weights;

        renderer.setViewport(0, 0, oTex.image.width / 2, oTex.image.height / 2);
        renderer.render(scene, camera);

        weights.set(0, 1, 0);
        obj.material.uniforms.uW.value = weights;

        renderer.setViewport(oTex.image.width / 2, 0, oTex.image.width / 2, oTex.image.height / 2);
        renderer.render(scene, camera);

        weights.set(0, 0, 1);
        obj.material.uniforms.uW.value = weights;

        renderer.setViewport(0, oTex.image.height / 2, oTex.image.width / 2, oTex.image.height / 2);
        renderer.render(scene, camera);

        weights.set(1, 1, 1);
        obj.material.uniforms.uW.value = weights;

        renderer.setViewport(oTex.image.width / 2, oTex.image.height / 2, oTex.image.width / 2, oTex.image.height / 2);
        renderer.render(scene, camera);
    }
}

main();
