#ifdef GL_ES
precision mediump float;
#endif
 
varying vec2 v_texCoord;
 
void main()
{ 
	vec4 normalColor = texture2D(CC_Texture0, v_texCoord).rgba;
	gl_FragColor = vec4( normalColor.g, normalColor.b, normalColor.r, normalColor.a );
}