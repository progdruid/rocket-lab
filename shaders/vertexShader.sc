$input a_position, a_color0
$output v_color0

void main()
{
	gl_Position = vec4(a_position, 1.0);
	v_color0 = vec4(a_color0, 1.0);
}