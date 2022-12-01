#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec3 v_atribute;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 poz_car;
uniform float scaleFactor;

out vec3 frag_color;

void main()
{
	frag_color = v_color;

	vec3 poz_car3 = (vec4(poz_car,1)).xyz * vec3(1,0,1);
	vec3 v_position_comp = (Model*vec4(v_position,1)).xyz;
	vec3 v_position_comp_y0 = v_position_comp * vec3(1,0,1);
	vec3 dist = poz_car3 - v_position_comp_y0;
	float len = length(dist);
	vec3 v_position2;
	v_position2.x = v_position_comp.x;
	v_position2.y = v_position_comp.y - len*len*scaleFactor;
	v_position2.z = v_position_comp.z;
	gl_Position = Projection*View*vec4(v_position2, 1.0);
	 
	
}