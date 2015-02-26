/*
Erfan Azad
24 February 2015
File: pop.js
Description: main javascript file for a poping sphere!
*/
var renderer = null, 
	scene = null,
	camera = null,
	joyCube = null,
	rotSpeed = 0.05,
	GUI = null;
	D_Light = null;

var spotLight = {
	S_Light : null,
	S_Color : 0xff0000,
};

var cubeControl = {
	material : 'phong',
	color : 0xff0000,
};

var mouseDown = false;
var rotateStartPoint = new THREE.Vector3(0, 0, 1);
var rotateEndPoint = new THREE.Vector3(0, 0, 1);

var curQuaternion;
var windowHalfX = window.innerWidth / 2;
var windowHalfY = window.innerHeight / 2;
var rotationSpeed = 2;
var lastMoveTimestamp,
	moveReleaseTimeDelta = 50;

var startPoint = {
	x: 0,
	y: 0
};

var deltaX = 0,
	deltaY = 0;



function onLoad(){
	var container = document.getElementById("container");

	//Renderer
	renderer = new THREE.WebGLRenderer({ antialias: true });
	renderer.setSize(container.offsetWidth, container.offsetHeight);
	renderer.setClearColor(0xffffff);
	container.appendChild(renderer.domElement);

	//scene
	scene = new THREE.Scene();

	//camera
	camera = new THREE.PerspectiveCamera( 45, container.offsetWidth/ container.offsetHeight, 1, 10000 );
	camera.position.set( 0, 0, 6000);

	//LIGHTS
	//Ambiant
	var Amb_light = new THREE.AmbientLight( 0x404040); // soft white light
	scene.add( Amb_light );
	
	//Direct
	D_Light = new THREE.DirectionalLight( 0xffffff , 0.2 );
	D_Light.position.set( 0, 0, 1);
	scene.add( D_Light );
	//Spot
	makeSpotLight();

	//make your objects
	joyCube = makeJoyCube();
	scene.add( joyCube );

	addKeyboardHandler();
	addMouseHandler();
	makeGUI();
	updateJoyCube();
	run();
}

//===========KEYBOARD CONTROLS=========
function addKeyboardHandler(){
	window.addEventListener("keypress", onKeyPress, false);
}

function onKeyPress(Event){
	Event.preventDefault();
	keyRotation(Event.keyCode, joyCube);
}

function keyRotation(code, object){
    if (code == 97){ //a
        object.rotation.y -= 0.1;
    } else if (code == 100){//d
        object.rotation.y += 0.1;
    }else if (code == 119){//w
        object.rotation.x -= 0.1;
    }else if (code == 115){//s
        object.rotation.x += 0.1;
    }else if (code == 113){//q
	    object.position.z += 100;
    }else if (code == 101){//e
        object.position.z -= 100;
    }

    camera.lookAt(scene.position);
}
//===========================================

//===========MOUSE CONTROLLS=================
function addMouseHandler(){
	document.addEventListener("mousedown", onMouseDown, false);
	document.addEventListener( 'mousewheel', onMouseWheel, false );
}

function onMouseWheel(event){
	event.preventDefault();
}

function onMouseDown(event){
	event.preventDefault();

	document.addEventListener('mousemove', onMouseMove, false);
	document.addEventListener('mouseup', onMouseUp, false);

	mouseDown = true;

	startPoint = {
		x: event.clientX,
		y: event.clientY
	};

	rotateStartPoint = rotateEndPoint = projectOnTrackball(0, 0);
}

function onMouseMove(event){
	event.preventDefault();
		deltaX = event.x - startPoint.x;
		deltaY = event.y - startPoint.y;

		handleRotation();

		startPoint.x = event.x;
		startPoint.y = event.y;

		lastMoveTimestamp = new Date();
}

function onMouseUp(event){
	event.preventDefault();
	if (new Date().getTime() - lastMoveTimestamp.getTime() > moveReleaseTimeDelta)
	{
		deltaX = event.x - startPoint.x;
		deltaY = event.y - startPoint.y;
	}

	mouseDown = false;

	document.removeEventListener('mousemove', onMouseMove, false);
	document.removeEventListener('mouseup', onMouseUp, false);
}
//==================================================================

//====================ROTATION FUNCTIONS============================
function handleRotation(){
	rotateEndPoint = projectOnTrackball(deltaX, deltaY);

	var rotateQuaternion = rotateMatrix(rotateStartPoint, rotateEndPoint);
	curQuaternion = joyCube.quaternion;
	curQuaternion.multiplyQuaternions(rotateQuaternion, curQuaternion);
	curQuaternion.normalize();
	joyCube.setRotationFromQuaternion(curQuaternion);

	rotateEndPoint = rotateStartPoint;
}

function projectOnTrackball(touchX, touchY){
	var mouseOnBall = new THREE.Vector3();

	mouseOnBall.set(clamp(touchX / windowHalfX, -1, 1), clamp(-touchY / windowHalfY, -1, 1), 0.0);

	var length = mouseOnBall.length();

	if (length > 1.0){
		mouseOnBall.normalize();
	}else{
		mouseOnBall.z = Math.sqrt(1.0 - length * length);
	}
	return mouseOnBall;
}

function rotateMatrix(rotateStart, rotateEnd){
	var axis = new THREE.Vector3(),
		quaternion = new THREE.Quaternion();

	var angle = Math.acos(rotateStart.dot(rotateEnd) / (rotateStart.length() * rotateEnd.length()));

	if (angle)
	{
		axis.crossVectors(rotateStart, rotateEnd).normalize();
		angle *= rotationSpeed;
		quaternion.setFromAxisAngle(axis, angle);
	}
	return quaternion;
}

function clamp(value, min, max){
	return Math.min(Math.max(value, min), max);
}
//====================================================================


function makeJoyCube(){ //returns an insctance of a joyCube
	var joyCube = new THREE.Object3D();
	var cube = new THREE.BoxGeometry( 100, 100, 100 );
	// var material = new THREE.MeshNormalMaterial({color: 0xdddddd, shininess: 300});
	var material = new THREE.MeshPhongMaterial({color: 0xdddddd, shininess: 300});

	for(i=0; i<1000; i++){
		var cubeMesh = new THREE.Mesh( cube, material );
		cubeMesh.position.x = Math.random() * 2000 - 1000;
		cubeMesh.position.y = Math.random() * 2000 - 1000;
		cubeMesh.position.z = Math.random() * 2000 - 1000;

		cubeMesh.rotation.x = Math.random() * 2 * Math.PI;
		cubeMesh.rotation.y = Math.random() * 2 * Math.PI;

		cubeMesh.matrixAutoUpdate = false;
		cubeMesh.updateMatrix();

		joyCube.add(cubeMesh);
	}
	return joyCube;
}

function render(){
	if (!mouseDown)
	{
		var drag = 0.95;
		var minDelta = 0.05;

		if (deltaX < -minDelta || deltaX > minDelta)
		{
			deltaX *= drag;
		}
		else
		{
			deltaX = 0;
		}

		if (deltaY < -minDelta || deltaY > minDelta)
		{
			deltaY *= drag;
		}
		else
		{
			deltaY = 0;
		}

		handleRotation();
	}
	updateSpotLight();
	updateJoyCube();
	renderer.render(scene, camera);
}

function run(){
    // Render the scene
    render();
    requestAnimationFrame(run);
}


function makeSpotLight(){
	spotLight.S_Light = new THREE.SpotLight(spotLight.S_Color);
	spotLight.S_Light.position.set( camera.position.x, camera.position.y, camera.position.z );
	spotLight.S_Light.castShadow = true;
	spotLight.S_Light.shadowMapWidth = 1024;
	spotLight.S_Light.shadowMapHeight = 1024;
	spotLight.S_Light.shadowCameraNear = 500;
	spotLight.S_Light.shadowCameraFar = 4000;
	spotLight.S_Light.shadowCameraFov = 30;
	scene.add( spotLight.S_Light );
}

function updateSpotLight(){
	scene.remove(spotLight.S_Light);
	makeSpotLight();
}

function updateJoyCube(){
	var children = joyCube.children;
	var newMaterial;

	if(cubeControl.material == "normal"){
		newMaterial = new THREE.MeshNormalMaterial();
	}else if(cubeControl.material == "phong"){
		newMaterial = new THREE.MeshPhongMaterial({color: cubeControl.color, shininess: 300});
	}else if(cubeControl.material == "lambert"){
		newMaterial = new THREE.MeshLambertMaterial({color: cubeControl.color});
	}else if(cubeControl.material == "basic"){
		newMaterial = new THREE.MeshBasicMaterial({color: cubeControl.color});
	}else if(cubeControl.material == "wireframe"){
		newMaterial = new THREE.MeshBasicMaterial({color: cubeControl.color, wireframe: true});
	}
	for(i=0; i<children.length; i++){
		children[i].material = newMaterial;
	}
}

function makeGUI(){
	GUI = new dat.GUI();
	var f1 = GUI.addFolder('spotLight');
	var f2 = GUI.addFolder('joyCube');
	f1.addColor(spotLight, 'S_Color').name('Spotlight Color');
	f2.addColor(cubeControl, 'color').name('Color');
	f2.add(cubeControl, 'material').options([ 'basic', 'lambert', 'phong', 'wireframe', 'normal' ]);
	// f2.add(cubeControl, 'material');



}

//https://stemkoski.github.io/Three.js/GUI-Controller.html
