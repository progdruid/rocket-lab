$input a_position, a_color0
$output v_color0

#include <bgfx_shader.sh>

void main()
{
	v_color0 = vec4(a_color0, 1.0);
	gl_Position = vec4(a_position, 1.0);
}