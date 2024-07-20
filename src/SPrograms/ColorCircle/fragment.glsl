#version 450 core

in vec4 col;
in vec2 p;
in float oRad;
in float iRad;

out vec4 oColor;

void main()
{
	vec2 offset = gl_FragCoord.xy - p;
	float distance = sqrt(offset.x * offset.x + offset.y * offset.y);
	if (distance > oRad || distance < iRad) discard;
	else oColor = col;
}