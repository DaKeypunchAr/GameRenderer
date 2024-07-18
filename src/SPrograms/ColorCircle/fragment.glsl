#version 450 core

uniform vec4 uColor;
uniform vec2 uPoint;
uniform float uOuterRadius;
uniform float uInnerRadius;

out vec4 oColor;

void main()
{
	vec2 offset = gl_FragCoord.xy - uPoint; 
	float distance = sqrt(offset.x * offset.x + offset.y * offset.y);
	if (distance > uOuterRadius || distance < uInnerRadius) discard;
	else oColor = uColor;
}