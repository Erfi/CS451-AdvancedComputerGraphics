function keyRotation(code, object, camera){
    if (code == 97){ //a
        object.rotation.y -= 0.1;
    } else if (code == 100){//d
        object.rotation.y += 0.1;
    }else if (code == 119){//w
        object.rotation.x -= 0.1;
    }else if (code == 115){//s
        object.rotation.x += 0.1;
    }else if (code == 113){//q
	    object.position.z += 10;
    }else if (code == 101){//e
        object.position.z -= 10;
    }

    camera.lookAt(scene.position);
} 