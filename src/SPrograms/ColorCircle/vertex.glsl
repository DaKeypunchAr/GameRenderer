#version 450 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in float aOuterRadius;
layout (location = 2) in float aInnerRadius;
layout (location = 3) in vec4 aColor;
layout (location = 4) in vec2 aPoint;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out float oRad;
out float iRad;
out vec4 col;
out vec2 p;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0, 1.0);
	oRad = aOuterRadius;
	iRad = aInnerRadius;
	col = aColor;
	p = aPoint;
}