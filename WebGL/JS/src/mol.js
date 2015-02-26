/*
Erfan Azad
23 February 2015
File: pop.js
Description: main javascript file for a poping sphere!
*/

var renderer = null, 
	scene = null,
	camera = null,
	water = null,
	rotSpeed = 0.05,
	Direct_Light_1 = null;



function onLoad(){
	var container = document.getElementById("container");

	//Renderer
	renderer = new THREE.WebGLRenderer({ antialias: true });
	renderer.setSize(container.offsetWidth, container.offsetHeight);
	renderer.setClearColor( 0xfff5f5 );
	container.appendChild(renderer.domElement);

	//scene
	scene = new THREE.Scene();

	//camera
	camera = new THREE.PerspectiveCamera( 45, container.offsetWidth/ container.offsetHeight, 1, 1000 );
	camera.position.set( 0, 0, 100);

	//LIGHTS
	//Ambiant
	var Amb_light = new THREE.AmbientLight( 0x404040); // soft white light
	scene.add( Amb_light );
	
	//Direct
	Direct_Light_1 = new THREE.DirectionalLight( 0xffffff, 1 );
	Direct_Light_1.position.set( 0, 0, 1);
	scene.add( Direct_Light_1 );
	//Spot
	//TO DO (OPTIONAL)

	//make your objects
	makeWater();
	scene.add( water );

	addKeyboardHandler();
	run();
}

function makeWater(){
	var hydrogenGeometry = new THREE.SphereGeometry( 5, 32, 32 );
	var oxygenGeometry = new THREE.SphereGeometry( 8, 32, 32 );

	var hydrogenMapUrl = "../IMAGES/hydrogen.png";
	var oxygenMapUrl = "../IMAGES/oxygen.png";

	var hydrogenMap = new THREE.ImageUtils.loadTexture(hydrogenMapUrl);
	var oxygenMap = new THREE.ImageUtils.loadTexture(oxygenMapUrl);

	var material_hydrogen = new THREE.MeshPhongMaterial({ map: hydrogenMap });
	var material_oxygen = new THREE.MeshPhongMaterial({ map: oxygenMap });

	var hydrogenMesh1 = new THREE.Mesh( hydrogenGeometry, material_hydrogen );
	var hydrogenMesh2 = new THREE.Mesh( hydrogenGeometry, material_hydrogen );
	var oxygenMesh = new THREE.Mesh( oxygenGeometry, material_oxygen);
	

	water = new THREE.Object3D();
	water.add(oxygenMesh);

	hydrogenMesh1.translateX(-10);
	hydrogenMesh1.translateY(-5);
	water.add(hydrogenMesh1);

	hydrogenMesh2.translateX(10);
	hydrogenMesh2.translateY(-5);
	water.add(hydrogenMesh2);
}

function addKeyboardHandler(){
	window.addEventListener("keypress", onKeyPress, false);
}

function onKeyPress(Event){
	keyRotation(Event.keyCode, water, camera);
}

function run(){
    // Render the scene
    renderer.render( scene, camera );
    // wiggle(water);
    requestAnimationFrame(run);
}

function wiggle(mesh){
	if(mesh != null){
		mesh.position.x+=(Math.random()-0.5);
		mesh.position.y+=(Math.random()-0.5);
		mesh.position.z+=(Math.random()-0.5);
	}
}



