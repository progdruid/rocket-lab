$input v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_texture,  0);

void main()
{
	gl_FragColor = texture2D(s_texture, v_texcoord0);
	//gl_FragColor = vec4(v_texcoord0, 1.0, 1.0);
}