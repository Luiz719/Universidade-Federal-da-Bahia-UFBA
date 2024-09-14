const spotLight = new THREE.SpotLight(0xd7adad, 50);
if(name == "land"){
    spotLight.position.set(4.02, 3.44, 0.82); 
    spotLight.target = (10,0,-0.9);
    spotLight.angle = 44.28 * (Math.PI / 180);
}else{
    spotLight.position.set(-1.56, 3.44, -3.84); 
    spotLight.target = (-1.14,0,-7.3);
    spotLight.angle = 33.21 * (Math.PI / 180);
}
spotLight.penumbra = 0.15;
spotLight.distance = 5.4;
spotLight.castShadow = true;