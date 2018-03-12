#version 120

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

varying float texId;

vec4 getTexColor( float _id, vec2 _st )
{
  vec4             rgba = texture2D( tex0, _st ).rgba;
  if( _id == 1.0 ) rgba = texture2D( tex1, _st ).rgba;
  if( _id == 2.0 ) rgba = texture2D( tex2, _st ).rgba;

  return rgba;
}

void main( void )
{
  vec2 st       = gl_TexCoord[ 0 ].st;
  vec4 texColor = getTexColor( texId, st );

  gl_FragColor = texColor * gl_Color;
}
