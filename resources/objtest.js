var backgroundColor = color(255, 255, 255);
var nodeColor = color(40, 168, 107);
var edgeColor = color(34, 68, 204);
var nodeSize = 8;

var node0 = [-100, -100, -100];
var node1 = [-100, -100,  100];
var node2 = [-100,  100, -100];
var node3 = [-100,  100,  100];
var node4 = [ 100, -100, -100];
var node5 = [ 100, -100,  100];
var node6 = [ 100,  100, -100];
var node7 = [ 100,  100,  100];
var nodes = [node0, node1, node2, node3, node4, node5, node6, node7];

var edge0  = [0, 1];
var edge1  = [1, 3];
var edge2  = [3, 2];
var edge3  = [2, 0];
var edge4  = [4, 5];
var edge5  = [5, 7];
var edge6  = [7, 6];
var edge7  = [6, 4];
var edge8  = [0, 4];
var edge9  = [1, 5];
var edge10 = [2, 6];
var edge11 = [3, 7];
var edges = [edge0, edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11];

// Rotate shape around the z-axis
var rotateZ3D = function(theta) {
    var sinTheta = sin(theta);
    var cosTheta = cos(theta);
    
    for (var n=0; n<nodes.length; n++) {
        var node = nodes[n];
        var x = node[0];
        var y = node[1];
        node[0] = x * cosTheta - y * sinTheta;
        node[1] = y * cosTheta + x * sinTheta;
    }
};

var rotateX3D = function(theta) {
    var sinTheta = sin(theta);
    var cosTheta = cos(theta);
    
    for (var n=0; n<nodes.length; n++) {
        var node = nodes[n];
        var y = node[1];
        var z = node[2];
        node[1] = y * cosTheta - z * sinTheta;
        node[2] = z * cosTheta + y * sinTheta;
    }
};


var rotateY3D = function(theta) {
    var sinTheta = sin(theta);
    var cosTheta = cos(theta);
    
    for (var n=0; n<nodes.length; n++) {
        var node = nodes[n];
        var x = node[0];
        var z = node[2];
        node[0] = x * cosTheta + z * sinTheta;
        node[2] = z * cosTheta - x * sinTheta;
    }
};


draw = function() {
    background(backgroundColor);
    
    pushMatrix();
    translate(200, 200);
    
    // Draw edges
    stroke(edgeColor);
    for (var e=0; e<edges.length; e++) {
        var n0 = edges[e][0];
        var n1 = edges[e][1];
        var node0 = nodes[n0];
        var node1 = nodes[n1];
        line(node0[0], node0[1], node1[0], node1[1]);
    }

    // Draw nodes
    fill(nodeColor);
    noStroke();
    for (var n=0; n<nodes.length; n++) {
        var node = nodes[n];
        ellipse(node[0], node[1], nodeSize, nodeSize);
    }
    
    popMatrix();
};


rotateZ3D(60);
rotateY3D(60);
rotateX3D(60);
