//Erfan Azad
//21 Feb 2015

var renderer = null, 
	scene = null,
	camera = null,
	cube = null,
	animating = false;


function onLoad(){
	// Grab our container div
    var container = document.getElementById("container");

    // Create the Three.js renderer, add it to our div
    renderer = new THREE.WebGLRenderer( { antialias: true } );
    renderer.setSize(container.offsetWidth, container.offsetHeight);
    container.appendChild( renderer.domElement );

    // Create a new Three.js scene
    scene = new THREE.Scene();

    // Create a camera and add it to the scene
    camera = new THREE.PerspectiveCamera( 45,
        container.offsetWidth / container.offsetHeight, 1, 4000 );
    camera.position.set( 0, 0, 20 );

	// add subtle ambient lighting
	var ambientLight = new THREE.AmbientLight(0x444444);
	scene.add(ambientLight);

    // Create a directional light to show off the object
    var light = new THREE.DirectionalLight( 0xffffff, 1.5);
    light.position.set(10, 0, 4);
    scene.add( light );

    // Create a shaded, texture-mapped cube and add it to the scene
    // First, create the texture map
    var mapUrl = "../IMAGES/brick.png";
    var map = new THREE.ImageUtils.loadTexture(mapUrl);
    map.wrapS = THREE.RepeatWrapping;
    map.wrapT = THREE.RepeatWrapping;
    map.repeat.set( 4, 4 );

    // Now, create a Phong mateial to show shading; pass in the map
    var material = new THREE.MeshLambertMaterial({ map: map });


    // var clr = new THREE.Color( Math.random(), Math.random(), Math.random());
    // var material = new THREE.MeshPhongMaterial( {color: clr} );



    // Create the cube geometry
    // var geometry = new THREE.BoxGeometry(1, 1, 1);
    var geometry = new THREE.BoxGeometry( 5, 5, 5 );

    // And put the geometry and material together into a mesh
    cube = new THREE.Mesh(geometry, material);

     // Turn it toward the scene, or we won't see the cube shape!
    cube.rotation.x = Math.PI / 5;
    cube.rotation.y = Math.PI / 5;

    // Add the cube to our scene
    scene.add( cube );

    // Add a mouse up handler to toggle the animation
    addMouseHandler();
    // document.addEventListener('mousedown', onDocumentMouseDown, false);
    // window.addEventListener('resize', onWindowResize, false);

    // Run our render loop
	run(); 
}



function run(){
    // Render the scene
    renderer.render( scene, camera );
    // Spin the cube for next frame
    if (animating)
    {
        cube.rotation.y -= 0.01;
    }
        // Ask for another frame
    requestAnimationFrame(run);
}

function addMouseHandler(){
    var dom = renderer.domElement;
    dom.addEventListener( 'mouseup', onMouseUp, false);
}


function onMouseUp    (event){
    event.preventDefault();
    animating = !animating;
}






