
varying vec3 N; 
varying vec4 P;

uniform vec4 LightSource;  // updated each draw call 
uniform vec4 Color;  // updated each draw call
 
void main() {

	
	//TODO add phong lighting

	vec3 L;
	vec3 E;

	vec3 R;

        gl_FragColor = Color;
}
