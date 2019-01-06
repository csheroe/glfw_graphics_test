#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

struct PointLight
{
vec3 pos;
vec3 color;
};
uniform PointLight light;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 normalMat;
uniform mat4 projMat;


out vec3 view_Half;
out vec3 view_Normal;
out vec3 view_lightDir;

void main()
{
	view_Normal = vec3(normalMat* vec4(normal, 0.0));
	gl_Position = projMat * viewMat * modelMat * vec4(position,1.0);
	vec4 view_light_pos = 	viewMat*vec4(light.pos, 1);
	vec4 view_pos = viewMat*modelMat*vec4(position,1.0);
	view_lightDir = normalize(view_light_pos.xyz - view_pos.xyz);
	vec3 view_direction = normalize(-view_pos.xyz);
	view_Half = normalize(view_lightDir + view_direction).xyz;
	gl_Position = projMat*view_pos;
}
