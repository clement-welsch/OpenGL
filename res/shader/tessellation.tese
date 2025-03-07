#version 460 core

// Quads
layout(triangles, equal_spacing, ccw) in;

void main()
{	
	gl_Position.xyzw =	gl_in[0].gl_Position.xyzw * gl_TessCoord.x +
						gl_in[1].gl_Position.xyzw * gl_TessCoord.y +
						gl_in[2].gl_Position.xyzw * gl_TessCoord.z;
}