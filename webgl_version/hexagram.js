/************
 * @Overview This file contains objects 'Hexagram' and its functions.
 * Created on 2 December, 2016
 * Author: EnzoLiao95
 *
 * @Usage Only used to construct WebGL assignments.
 * Include this file in HTML:
 * 	<script type="text/javascript" src="hexagram.js"></script>
 ***********/


var Hexagram =
{
	/* Object initialization */
	create: function(canvasName)
	{
		// New hexagram object
		var hexagram = {};

		/* Hexagram initiation */
		hexagram.init = function(canvas)
		{
			try {
			  hexagram.gl = canvas.getContext("experimental-webgl");
			  hexagram.gl.viewportWidth  = canvas.width;
			  hexagram.gl.viewportHeight = canvas.height;
			}
			catch (e) 
			{ // Throw error and catch it
			}

			// If browser cannot initialise WebGL
			if (!hexagram.gl) alert("ERROR: Cannot initialise WebGL!");
		};

		/* This function is used to compile GLSL shader source */
		hexagram.getShader = function(gl, id)
		{
			var shaderScript = document.getElementById(id);
			// Shader creation failed
			if (!shaderScript) return null;

			// GLSL code string definition
			var codeStr = "";
			var shaderChild = shaderScript.firstChild;
			while (shaderChild)
			{
				if (shaderChild.nodeType == 3)
					codeStr += shaderChild.textContent;
				shaderChild = shaderChild.nextSibling;
			}

			var shader;
			// Check shader type
			if (shaderScript.type == "x-shader/x-fragment") shader = gl.createShader(gl.FRAGMENT_SHADER);
			else if (shaderScript.type == "x-shader/x-vertex") shader = gl.createShader(gl.VERTEX_SHADER);
			else return null;

			// Load shader source and compile the shader
			gl.shaderSource(shader, codeStr);
			gl.compileShader(shader);

			// Alert and return if the compiler failed
			if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
			{
				alert(gl.getShaderInfoLog(shader));
				return null;
			}

			return shader;
		}

		/* Initialise shaders with GLSL source compiled above */
		hexagram.initShaders = function(gl)
		{
			// Create shader program
			var shaderProgram = gl.createProgram();

			// Attach and link shader
			gl.attachShader(shaderProgram, hexagram.getShader(gl, "shader-vs"));
			gl.attachShader(shaderProgram, hexagram.getShader(gl, "shader-fs"));
			gl.linkProgram(shaderProgram);

			// Fail to link shader program
			if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS))
				alert("ERROR: Could not initialise shaders!");

			// Use shader program linked before
			gl.useProgram(shaderProgram);

			// Enable array of vertex position
			shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
			gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

			// Enable array of vertex color
			shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
			gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);

			shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
			shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
		
			return shaderProgram;
		}

		// mvMatrix and pMatrix creation
		hexagram.mvMatrix = mat4.create();
		hexagram.pMatrix = mat4.create();
		
		// Matrix stack
		hexagram.mvMatrixStack = [];

		/* Push matrix to matrix stack */
		hexagram.mvPushMatrix = function()
		{
			var copy = mat4.create();
			mat4.set(hexagram.mvMatrix, copy);
			hexagram.mvMatrixStack.push(copy);
		};
		
		/* Pop matrix from matrix stack */
		hexagram.mvPopMatrix = function()
		{
			if (hexagram.mvMatrixStack.length == 0)
				throw "ERROR: Invalid popMatrix!";
			hexagram.mvMatrix = hexagram.mvMatrixStack.pop();
		};
		
		/* Hexagram uniformation */
		hexagram.setMatrixUniforms = function()
		{
			var gl = hexagram.gl;
			var shaderProgram = hexagram.shaderProgram;
			gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, hexagram.pMatrix);
			gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, hexagram.mvMatrix);
		};
		
		/* Initialise vertex buffer */
		hexagram.initBuffers = function(gl, shaderProgram)
		{
			// Initialise vertex buffer 
			var vertexPositionBuffer = {};
			var vertexColorBuffer = {};

			// Triangles position data
			var triangles = {};
			triangles[0] = [ 0.0, 0.0, 0.0, 0.288675, 0.5, 0.0, 0.0, 1.0, 0.0 ];
			triangles[1] = [ 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -0.288675, 0.5, 0.0 ];
			triangles[2] = [ 0.0, 0.0, 0.0, -0.288675, 0.5, 0.0, -0.866025, 0.5, 0.0 ];
			triangles[3] = [ 0.0, 0.0, 0.0, -0.866025, 0.5, 0.0, -0.577350, 0.0, 0.0 ];
			triangles[4] = [ 0.0, 0.0, 0.0, -0.577350, 0.0, 0.0, -0.866025, -0.5, 0.0 ];
			triangles[5] = [ 0.0, 0.0, 0.0, -0.866025, -0.5, 0.0, -0.288675, -0.5, 0.0 ];
			triangles[6] = [ 0.0, 0.0, 0.0, -0.288675, -0.5, 0.0 , 0.0, -1.0, 0.0 ];
			triangles[7] = [ 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.288675, -0.5, 0.0 ];
			triangles[8] = [ 0.0, 0.0, 0.0, 0.288675, -0.5, 0.0, 0.866025, -0.5, 0.0 ];
			triangles[9] = [ 0.0, 0.0, 0.0, 0.866025, -0.5, 0.0, 0.577350, 0.0, 0.0 ];
			triangles[10] = [ 0.0, 0.0, 0.0, 0.577350, 0.0, 0.0, 0.866025, 0.5, 0.0 ];
			triangles[11] = [ 0.0, 0.0, 0.0, 0.866025, 0.5, 0.0, 0.288675, 0.5, 0.0 ];

			// Vertex color data
			var colors = {};
			colors[0] = [ 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0 ];
			colors[1] = [ 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0 ];
			colors[2] = [ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0 ];
			colors[3] = [ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 ];
			colors[4] = [ 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 ];
			colors[5] = [ 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0 ];
			colors[6] = [ 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0 ];
			colors[7] = [ 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0 ];
			colors[8] = [ 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0 ];
			colors[9] = [ 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0 ];
			colors[10] = [ 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0 ];
			colors[11] = [ 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0 ];

			// Declare new buffer objects
			hexagram.vertexPositionBuffer = {};
			hexagram.vertexColorBuffer = {};

			// The hexagram consists of 12 triangles
			for (var i = 0; i < 12; i++)
			{
				// Create new buffer
				vertexPositionBuffer[i] = gl.createBuffer();

				// Bind vertex position buffer 
				gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer[i]);
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(triangles[i]), gl.STATIC_DRAW);

				// Each position vector has dimension equaling to 3
				vertexPositionBuffer[i].itemSize = 3;

				// Each triangle has 3 vertices
				vertexPositionBuffer[i].numItems = 3;

				// Bing vertex color buffer
				vertexColorBuffer[i] = gl.createBuffer();
				gl.bindBuffer(gl.ARRAY_BUFFER, vertexColorBuffer[i]);
				gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors[i]), gl.STATIC_DRAW);

				// Each color vector has dimension equaling to 4
				vertexColorBuffer[i].itemSize = 4;
				vertexColorBuffer[i].numItems = 3;

				hexagram.vertexPositionBuffer[i] = vertexPositionBuffer[i];
				hexagram.vertexColorBuffer[i] = vertexColorBuffer[i];
			}
		};

		/* Draw this hexagram */
		hexagram.drawImage = function()
		{
			var gl = hexagram.gl;
			var shaderProgram = hexagram.shaderProgram;

			// Viewport settings
			gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
			gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

			// Perspective settings
			mat4.perspective(90, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, hexagram.pMatrix);
			mat4.identity(hexagram.mvMatrix);
			mat4.translate(hexagram.mvMatrix, [0.0, 0.0, -1.0]);

			var vertexPositionBuffer, vertexColorBuffer;
			for (var i = 0; i < 12; i++)
			{
				var vertexPositionBuffer = hexagram.vertexPositionBuffer[i];
				var vertexColorBuffer = hexagram.vertexColorBuffer[i];

				// Bind position buffer
				gl.bindBuffer(gl.ARRAY_BUFFER, vertexPositionBuffer);
				gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, vertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

				// Bing color buffer
				gl.bindBuffer(gl.ARRAY_BUFFER, vertexColorBuffer);
				gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, vertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0);

				// Draw the image with binded data
			 	hexagram.setMatrixUniforms();
				gl.drawArrays(gl.TRIANGLES, 0, vertexPositionBuffer.numItems);
			}
		};

		hexagram.canvas = document.getElementById(canvasName); 
		hexagram.init(hexagram.canvas);
		hexagram.shaderProgram = hexagram.initShaders(hexagram.gl);
		hexagram.initBuffers(hexagram.gl, hexagram.shaderProgram);

		// Background color initialization
		hexagram.gl.clearColor(0.7, 0.7, 0.7, 1.0);
		hexagram.gl.enable(hexagram.gl.DEPTH_TEST);

		return hexagram;
	}
};
