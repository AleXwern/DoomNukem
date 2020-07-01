// cameraControl.js
// Based on PointLightedCube.js (c) 2012 Matsuda 
// from WebGL Programming Guide.
 
// Modified by Ying Zhu in 2016.

// Vertex shader program
var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' +
  'attribute vec4 a_Color;\n' +
  'attribute vec4 a_Normal;\n' +
  'uniform mat4 u_MvpMatrix;\n' +
  'uniform mat4 u_ModelMatrix;\n' +    // Model matrix
  'uniform mat4 u_NormalMatrix;\n' +   // Coordinate transformation matrix of the normal
  'uniform vec3 u_LightColor;\n' +     // Light color
  'uniform vec3 u_LightPosition;\n' +  // Position of the light source
  'uniform vec3 u_AmbientLight;\n' +   // Ambient light color
  'varying vec4 v_Color;\n' +
  'void main() {\n' +
  '  gl_Position = u_MvpMatrix * a_Position;\n' +
     // Recalculate the normal based on the model matrix and make its length 1.
  '  vec3 normal = normalize(vec3(u_NormalMatrix * a_Normal));\n' +
     // Calculate world coordinate of vertex
  '  vec4 vertexPosition = u_ModelMatrix * a_Position;\n' +
     // Calculate the light direction and make it 1.0 in length
  '  vec3 lightDirection = normalize(u_LightPosition - vec3(vertexPosition));\n' +
     // Calculate the dot product of the normal and light direction
  '  float nDotL = max(dot(normal, lightDirection), 0.0);\n' +
     // Calculate the color due to diffuse reflection
  '  vec3 diffuse = u_LightColor * a_Color.rgb * nDotL;\n' +
     // Calculate the color due to ambient reflection
  '  vec3 ambient = u_AmbientLight * a_Color.rgb;\n' +
     // Add the surface colors due to diffuse reflection and ambient reflection
  '  v_Color = vec4(diffuse + ambient, a_Color.a);\n' + 
  '}\n';

// Fragment shader program
var FSHADER_SOURCE =
  '#ifdef GL_ES\n' +
  'precision mediump float;\n' +
  '#endif\n' +
  'varying vec4 v_Color;\n' +
  'void main() {\n' +
  '  gl_FragColor = v_Color;\n' +
  '}\n';

// The following lines are added by Ying Zhu (03/2016)

// Camera control parameters
var pitchAngle = 0;
var minPitchAngle = -90;
var maxPitchAngle = 90;

var yawAngle = 0;
var minYawAngle = -90;
var maxYawAngle = 90;

var rollCamera = false;

var rollAngle = 0;
var minRollAngle = -180;
var maxRollAngle = 180; 

var trackLeftRight = 0;
var pushInPullOut = 0;
var craneUpDown = 0;

var step = 0.5;

var fov = 30;
var fovMin = 10;
var fovMax = 160;

var animated = true;

//*** End of the code added by Ying Zhu (03/2016)

function main() {
  // Retrieve <canvas> element
  var canvas = document.getElementById('webgl');

  // Get the rendering context for WebGL
  var gl = getWebGLContext(canvas);
  if (!gl) {
    console.log('Failed to get the rendering context for WebGL');
    return;
  }

  // Initialize shaders
  if (!initShaders(gl, VSHADER_SOURCE, FSHADER_SOURCE)) {
    console.log('Failed to intialize shaders.');
    return;
  }

  // Set the vertex coordinates, the color and the normal
  var n = initVertexBuffers(gl);
  if (n < 0) {
    console.log('Failed to set the vertex information');
    return;
  }

  initMouseMotionCallback(canvas);

  initKeyboardCallback();
  
  // Set the clear color and enable the depth test
  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.enable(gl.DEPTH_TEST);

  // Get the storage locations of uniform variables and so on
  var u_ModelMatrix = gl.getUniformLocation(gl.program, 'u_ModelMatrix');
  var u_MvpMatrix = gl.getUniformLocation(gl.program, 'u_MvpMatrix');
  var u_NormalMatrix = gl.getUniformLocation(gl.program, 'u_NormalMatrix');
  var u_LightColor = gl.getUniformLocation(gl.program, 'u_LightColor');
  var u_LightPosition = gl.getUniformLocation(gl.program, 'u_LightPosition');
  var u_AmbientLight = gl.getUniformLocation(gl.program, 'u_AmbientLight');
  if (!u_MvpMatrix || !u_NormalMatrix || !u_LightColor || !u_LightPosition　|| !u_AmbientLight) { 
    console.log('Failed to get the storage location');
    return;
  }

  var vpMatrix = new Matrix4();   // View projection matrix

  // Set the light color (white)
  gl.uniform3f(u_LightColor, 1.0, 1.0, 1.0);
  // Set the light direction (in the world coordinate)
  gl.uniform3f(u_LightPosition, 2.3, 4.0, 3.5);
  // Set the ambient light
  gl.uniform3f(u_AmbientLight, 0.2, 0.2, 0.2);

  var currentAngle = 0.0;  // Current rotation angle
  var modelMatrix = new Matrix4();  // Model matrix
  var mvpMatrix = new Matrix4();    // Model view projection matrix
  var normalMatrix = new Matrix4(); // Transformation matrix for normals

  var tick = function() {
      
//*** The following lines are added by Ying Zhu (03/2016)
    
    // If you want to move the camera, you need to put the 
    // projection transformation and view transformations inside the 
    // rendering loop. 
    
    // Replaced fixed field of view with a variable fov, which can be changed by users.    
    vpMatrix.setPerspective(fov, canvas.width/canvas.height, 1, 100);
    
    // Camera transformations should be done after the view transformation but
    // before the projection transformation. 
    
    // Move the camera horizontally. 
    // In fact, we are moving the entire scene to the opposite direction of the camera motion.
    // If you translate the camera to the left, it's equivalent to translating the entire scene to the right.    
    vpMatrix.translate(-trackLeftRight, 0, 0);
    
    // Move the camera vertically. 
    // We are moving the entire scene to the opposite direction of the camera motion.
    vpMatrix.translate(0, -craneUpDown, 0);
    
    // Move the camera forward and backward.
    // We are moving the entire scene to the opposite direction of the camera motion.
    vpMatrix.translate(0, 0, pushInPullOut);
    
    // Rotations must be done before translation. 
    
    // Camera pitch
    // We are rotating the entire scene in the opposite direction. 
    vpMatrix.rotate(pitchAngle, 1, 0, 0);
    
    // Camera yaw
    // We are rotating the entire scene in the opposite direction. 
    vpMatrix.rotate(yawAngle, 0, 1, 0);
    
    // Camera roll
    // We are rotating the entire scene in the opposite direction. 
    vpMatrix.rotate(rollAngle, 0, 0, 1);

//*** end of the code added by Ying Zhu (03/2016)
  
    vpMatrix.lookAt(6, 6, 14, 0, 0, 0, 0, 1, 0);
  
    currentAngle = animate(currentAngle);  // Update the rotation angle

    // Calculate the model matrix
    modelMatrix.setRotate(currentAngle, 0, 1, 0); // Rotate around the y-axis
    // Pass the model matrix to u_ModelMatrix
    gl.uniformMatrix4fv(u_ModelMatrix, false, modelMatrix.elements);

    // Pass the model view projection matrix to u_MvpMatrix
    mvpMatrix.set(vpMatrix).multiply(modelMatrix);
    gl.uniformMatrix4fv(u_MvpMatrix, false, mvpMatrix.elements);

    // Pass the matrix to transform the normal based on the model matrix to u_NormalMatrix
    normalMatrix.setInverseOf(modelMatrix);
    normalMatrix.transpose();
    gl.uniformMatrix4fv(u_NormalMatrix, false, normalMatrix.elements);

    // Clear color and depth buffer
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Draw the cube
    gl.drawElements(gl.TRIANGLES, n, gl.UNSIGNED_BYTE, 0);

    requestAnimationFrame(tick, canvas); // Request that the browser ?calls tick
  };
  tick();
}

function initVertexBuffers(gl) {
  // Create a cube
  //    v6----- v5
  //   /|      /|
  //  v1------v0|
  //  | |     | |
  //  | |v7---|-|v4
  //  |/      |/
  //  v2------v3
  // Coordinates
  var vertices = new Float32Array([
     2.0, 2.0, 2.0,  -2.0, 2.0, 2.0,  -2.0,-2.0, 2.0,   2.0,-2.0, 2.0, // v0-v1-v2-v3 front
     2.0, 2.0, 2.0,   2.0,-2.0, 2.0,   2.0,-2.0,-2.0,   2.0, 2.0,-2.0, // v0-v3-v4-v5 right
     2.0, 2.0, 2.0,   2.0, 2.0,-2.0,  -2.0, 2.0,-2.0,  -2.0, 2.0, 2.0, // v0-v5-v6-v1 up
    -2.0, 2.0, 2.0,  -2.0, 2.0,-2.0,  -2.0,-2.0,-2.0,  -2.0,-2.0, 2.0, // v1-v6-v7-v2 left
    -2.0,-2.0,-2.0,   2.0,-2.0,-2.0,   2.0,-2.0, 2.0,  -2.0,-2.0, 2.0, // v7-v4-v3-v2 down
     2.0,-2.0,-2.0,  -2.0,-2.0,-2.0,  -2.0, 2.0,-2.0,   2.0, 2.0,-2.0  // v4-v7-v6-v5 back
  ]);

  // Colors
  var colors = new Float32Array([
    1, 0, 0,   1, 0, 0,   1, 0, 0,  1, 0, 0,     // v0-v1-v2-v3 front
    1, 0, 0,   1, 0, 0,   1, 0, 0,  1, 0, 0,     // v0-v3-v4-v5 right
    1, 0, 0,   1, 0, 0,   1, 0, 0,  1, 0, 0,     // v0-v5-v6-v1 up
    1, 0, 0,   1, 0, 0,   1, 0, 0,  1, 0, 0,     // v1-v6-v7-v2 left
    1, 0, 0,   1, 0, 0,   1, 0, 0,  1, 0, 0,     // v7-v4-v3-v2 down
    1, 0, 0,   1, 0, 0,   1, 0, 0,  1, 0, 0　    // v4-v7-v6-v5 back
 ]);

  // Normal
  var normals = new Float32Array([
    0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,  // v0-v1-v2-v3 front
    1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,  // v0-v3-v4-v5 right
    0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,  // v0-v5-v6-v1 up
   -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  -1.0, 0.0, 0.0,  // v1-v6-v7-v2 left
    0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,   0.0,-1.0, 0.0,  // v7-v4-v3-v2 down
    0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0,   0.0, 0.0,-1.0   // v4-v7-v6-v5 back
  ]);

  // Indices of the vertices
  var indices = new Uint8Array([
     0, 1, 2,   0, 2, 3,    // front
     4, 5, 6,   4, 6, 7,    // right
     8, 9,10,   8,10,11,    // up
    12,13,14,  12,14,15,    // left
    16,17,18,  16,18,19,    // down
    20,21,22,  20,22,23     // back
 ]);

  // Write the vertex property to buffers (coordinates, colors and normals)
  if (!initArrayBuffer(gl, 'a_Position', vertices, 3, gl.FLOAT)) return -1;
  if (!initArrayBuffer(gl, 'a_Color', colors, 3, gl.FLOAT)) return -1;
  if (!initArrayBuffer(gl, 'a_Normal', normals, 3, gl.FLOAT)) return -1;

  // Unbind the buffer object
  gl.bindBuffer(gl.ARRAY_BUFFER, null);

  // Write the indices to the buffer object
  var indexBuffer = gl.createBuffer();
  if (!indexBuffer) {
    console.log('Failed to create the buffer object');
    return false;
  }
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, indices, gl.STATIC_DRAW);

  return indices.length;
}

function initArrayBuffer(gl, attribute, data, num, type) {
  // Create a buffer object
  var buffer = gl.createBuffer();
  if (!buffer) {
    console.log('Failed to create the buffer object');
    return false;
  }
  // Write date into the buffer object
  gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
  gl.bufferData(gl.ARRAY_BUFFER, data, gl.STATIC_DRAW);
  // Assign the buffer object to the attribute variable
  var a_attribute = gl.getAttribLocation(gl.program, attribute);
  if (a_attribute < 0) {
    console.log('Failed to get the storage location of ' + attribute);
    return false;
  }
  gl.vertexAttribPointer(a_attribute, num, type, false, 0, 0);
  // Enable the assignment of the buffer object to the attribute variable
  gl.enableVertexAttribArray(a_attribute);

  return true;
}

// Rotation angle (degrees/second)
var ANGLE_STEP = 30.0;
// Last time that this function was called
var g_last = Date.now();
function animate(angle) {
  if (!animated) {
      return angle;
  }
  
  // Calculate the elapsed time
  var now = Date.now();
  var elapsed = now - g_last;
  g_last = now;
  // Update the current rotation angle (adjusted by the elapsed time)
  var newAngle = angle + (ANGLE_STEP * elapsed) / 1000.0;
  return newAngle %= 360;
}

//*** The following lines are added by Ying Zhu (03/2016).

// Register a keyboard callback function. 
function initKeyboardCallback() {
    document.onkeydown = function(event) {
        switch(event.keyCode) {
            case 82: // Use r or R to turn on/off camera rolling.  
                rollCamera = !rollCamera;
                break;
            case 65: // Use a or A to turn on/off animation. 
                animated = !animated;
                break;
            case 37: // Use left arrow to move the camera to the left.  
                trackLeftRight -= step; 
                break;
            case 38: // Use up arrow to move the camera forward. 
                 pushInPullOut += step;
                 break;
            case 39: // Use right arrow to move the camera to the right. 
                trackLeftRight += step;
                break; 
            case 40: // Use down arrow to move the camera backward.  
                pushInPullOut -= step;
                break;
            case 85: // Use u or U key to move the camera upward. 
                craneUpDown += step;
                break;
            case 68: // Use d or D key to move the camera downward. 
                craneUpDown -= step;
                break;
            case 107: // Use + key to zoom in. 
                fov -= step;
                fov = Math.max(fov, fovMin); // lower limit of fov
                break;
            case 109: // Use - key to zoom out. 
                fov += step;
                fov = Math.min(fov, fovMax); // upper limit of fov
                break;
            default: return;
        }
    }
}

var lastX = 0, lastY = 0;
var dMouseX = 0, dMouseY = 0;
var trackingMouseMotion = false;

// Register mouse callback functions 
function initMouseMotionCallback(canvas) {
    
    // If a mouse button is pressed, save the current mouse location
    // and start tracking mouse motion.  
    canvas.onmousedown = function(event) {
        var x = event.clientX;
        var y = event.clientY;
        
        var rect = event.target.getBoundingClientRect();
        // Check if the mouse cursor is in canvas. 
        if (rect.left <= x && rect.right > x &&
            rect.top <= y && rect.bottom > y) {
            lastX = x; 
            lastY = y;
            trackingMouseMotion = true;    
        }
    }

    // If the mouse button is release, stop tracking mouse motion.     
    canvas.onmouseup = function(event) {
        trackingMouseMotion = false; 
    }
    
    // Calculate how far the mouse cusor has moved and convert the mouse motion 
    // to rotation angles. 
    canvas.onmousemove = function(event) {
        var x = event.clientX;
        var y = event.clientY;
                    
        if (trackingMouseMotion) {
            var scale = 1;
            // Calculate how much the mouse has moved along X and Y axis, and then
            // normalize them based on the canvas' width and height. 
            dMouseX = (x - lastX)/canvas.width;
            dMouseY = (y - lastY)/canvas.height;            
                
            if (!rollCamera) { 
                // For camera pitch and yaw motions
                scale = 30;
                // Add the mouse motion to the current rotation angle so that the rotation 
                // is added to the previous rotations. 
                // Use scale to control the speed of the rotation.    
                yawAngle += scale * dMouseX;
                // Impose the upper and lower limits to the rotation angle. 
                yawAngle = Math.max(Math.min(yawAngle, maxYawAngle), minYawAngle); 
                
                pitchAngle += scale * dMouseY;
                pitchAngle = Math.max(Math.min(pitchAngle, maxPitchAngle), minPitchAngle);
            } else {
                // For camera roll motion
                scale = 100; 
                
                // Add the mouse motion delta to the rotation angle, don't just replace it.
                // Use scale to control the speed of the rotation. 
                rollAngle += scale * dMouseX;
                rollAngle %= 360;
            }
        }
        
        // Save the current mouse location in order to calculate the next mouse motion. 
        lastX = x;
        lastY = y;
    }
}