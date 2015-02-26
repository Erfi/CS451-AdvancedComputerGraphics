/*
Erfan Azad
22 February 2015
File: pop.js
Description: main javascript file for a poping sphere!
*/


var renderer = null, 
	scene = null,
	camera = null,
	animating = false,
	spheres = null;
	colors = null;
	materials = null;
	meshArray = null;
	range = 40;
	number = 50;
	animating =  false;
	rotSpeed = 0.05;
	Direct_Light_1 = null;


function onLoad(){
	var container = document.getElementById("container");

	//Renderer
	renderer = new THREE.WebGLRenderer({ antialias: true });
	renderer.setSize(container.offsetWidth, container.offsetHeight);
	renderer.setClearColor( 0xffffff );
	container.appendChild(renderer.domElement);

	//scene
	scene = new THREE.Scene();

	//camera
	camera = new THREE.PerspectiveCamera( 45, container.offsetWidth/ container.offsetHeight, 1, 1000 );
	camera.position.set( 0, 0, 100 );

	//LIGHTS
	//Ambiant
	var Amb_light = new THREE.AmbientLight( 0x404040); // soft white light
	scene.add( Amb_light );
	
	//Direct
	Direct_Light_1 = new THREE.DirectionalLight( 0xffffff, 1);
	Direct_Light_1.position.set( 0, 0, 1000);
	scene.add( Direct_Light_1 );


	//Spot
	//TO DO (OPTIONAL)

	//make the scene objects
	buildSpheres(number, 2);
	buildColors(number);
	buildMaterials(number);
	buildMeshArray(number);
	addSpheres(range);

	addKeyboardHandler();
	run();	
}

function buildSpheres(number, size){
	spheres = [];
	// var material;
	for(i=0; i<number; i++){
		spheres[i] = new THREE.SphereGeometry( size, 32, 32 );
		// material = new THREE.MeshBasicMaterial( {color: clr} );
	}
}

function buildColors(number){
	colors = [];
	for(i=0; i<number; i++){
		colors[i] = new THREE.Color( Math.random(), Math.random(), Math.random());
	}
}

function buildMaterials(number){
	if(colors != null){
		materials = [];
		for(i=0; i<number; i++){
			materials[i] = new THREE.MeshPhongMaterial( {color: colors[i]});
		}
	}else{
		window.alert("You have to create the 'colors' array first!");
	}
}

function buildMeshArray(number){
	if(spheres != null && materials != null){
		meshArray = [];
		for(i=0; i<number; i++){
			meshArray[i]= new THREE.Mesh( spheres[i], materials[i] );
		}
	}else{
		window.alert("You have to create the 'spheres' array and 'materials' array first!");
	}
}

function addSpheres(range){
	if(meshArray != null){
		for(i=0; i<meshArray.length; i++){
			meshArray[i].translateX ((Math.random()*range)-range/2);
			meshArray[i].translateY ((Math.random()*range)-range/2);
			meshArray[i].translateZ ((Math.random()*range)-range/2);
			meshArray[i].updateMatrix();
			scene.add(meshArray[i]);
		}
	}else{
		window.alert("You have to create the 'meshArray'  first!");
	}
}

function addMouseHandler(){

}

function addKeyboardHandler(){
	window.addEventListener("keypress", onKeyPress, false);
}

function onKeyPress(Event){
	checkRotation(Event.keyCode);
}

function checkRotation(code){

    var x = camera.position.x,
        y = camera.position.y,
        z = camera.position.z,
        light_x = Direct_Light_1.position.x,
        light_y = Direct_Light_1.position.y,
        light_z = Direct_Light_1.position.z;


    if (code == 97){ //a
        camera.position.x = x * Math.cos(rotSpeed) + z * Math.sin(rotSpeed);
        camera.position.z = z * Math.cos(rotSpeed) - x * Math.sin(rotSpeed);
        Direct_Light_1.position.x = light_x * Math.cos(rotSpeed) + light_z * Math.sin(rotSpeed);
        Direct_Light_1.position.z = light_z * Math.cos(rotSpeed) - light_x * Math.sin(rotSpeed);
    } else if (code == 100){//d
        camera.position.x = x * Math.cos(rotSpeed) - z * Math.sin(rotSpeed);
        camera.position.z = z * Math.cos(rotSpeed) + x * Math.sin(rotSpeed);
        Direct_Light_1.position.x = light_x * Math.cos(rotSpeed) - light_z * Math.sin(rotSpeed);
        Direct_Light_1.position.z = light_z * Math.cos(rotSpeed) + light_x * Math.sin(rotSpeed);
    }else if (code == 119){//w
        camera.position.y = y * Math.cos(rotSpeed) - z * Math.sin(rotSpeed);
        camera.position.z = z * Math.cos(rotSpeed) + y * Math.sin(rotSpeed);
        Direct_Light_1.position.y = light_y * Math.cos(rotSpeed) - light_z * Math.sin(rotSpeed);
        Direct_Light_1.position.z = light_z * Math.cos(rotSpeed) + light_y * Math.sin(rotSpeed);
    }else if (code == 115){//s
        camera.position.y = y * Math.cos(rotSpeed) + z * Math.sin(rotSpeed);
        camera.position.z = z * Math.cos(rotSpeed) - y * Math.sin(rotSpeed);
        Direct_Light_1.position.y = light_y * Math.cos(rotSpeed) + light_z * Math.sin(rotSpeed);
        Direct_Light_1.position.z = light_z * Math.cos(rotSpeed) - light_y * Math.sin(rotSpeed);
    }else if (code == 113){//q
        camera.position.z = z + (30*rotSpeed);
        Direct_Light_1.position.z = light_z + (30*rotSpeed);
        console.log(camera.position.z);
    }else if (code == 101){//e
        camera.position.z = z - (30*rotSpeed);
        Direct_Light_1.position.z = light_z - (30*rotSpeed);
        console.log(camera.position.z);
    }
    
    camera.lookAt(scene.position);
    
} 

function run(){
    // Render the scene
    renderer.render( scene, camera );
    for(i=0; i<spheres.length; i++){
    	// wiggle(meshArray[i]);
    }
    requestAnimationFrame(run);
}

function wiggle(mesh){
	if(mesh != null){
		mesh.position.x+=(Math.random()-0.5);
		mesh.position.y+=(Math.random()-0.5);
		mesh.position.z+=(Math.random()-0.5);
	}
}

function explode(){

}

function gather(){

}
