#include "helper.h"
#include <math.h>

//glm stuff
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using namespace std;

// some global variables:
bool wireframe_mode = false;
 
float t  = 0;  // the time parameter (incremented in the idle-function)
float speed = 0.1;  // rotation speed of the light source in degree/frame



//We need to keep track of matrices ourselves

/**
 * @brief P,V,M:
 * your matrices for setting the scene, no matrix stack anymore
 */
glm::mat4 P,V,M;		

/**
 * @brief The ShaderUniforms struct:
 * every shader has its own uniforms,
 * binding of uniforms is done in bindUniforms()
 *
 */
struct ShaderUniforms
{
	GLuint Shader;
	GLint location_MVP;
	GLint location_MV;
	GLint location_NormalMatrix ; 
	GLint location_Time;
	GLint location_LightSourceViewSpace;
	GLint location_Color;

	void bindUniforms(glm::mat4& M, glm::mat4& V, glm::mat4& P, glm::vec4& LightSource, glm::vec4& Color,float  t)
	{		
		location_Time					= glGetUniformLocation(Shader, "Time");
		location_MVP					= glGetUniformLocation(Shader, "MVP");
		location_MV						= glGetUniformLocation(Shader, "MV");
		location_NormalMatrix			= glGetUniformLocation(Shader, "NormalMatrix");
		location_LightSourceViewSpace	= glGetUniformLocation(Shader, "LightSource");
		location_Color					= glGetUniformLocation(Shader, "Color");


        // TODO create the matrices MV,MVP and NormalMatrix


        glm::mat4 MV;
        glm::mat4 MVP;
        glm::mat3 NormalMatrix;


		glUniformMatrix4fv(location_MVP, 1, false, glm::value_ptr(MVP));
		glUniformMatrix4fv(location_MV, 1, false, glm::value_ptr(MV));
		glUniformMatrix3fv(location_NormalMatrix, 1, false, glm::value_ptr(NormalMatrix));
		glUniform4fv(location_LightSourceViewSpace, 1, glm::value_ptr(LightSource));
		glUniform4fv(location_Color, 1, glm::value_ptr(Color));
		glUniform1f(location_Time, 10*t);
	}

};
/**
  * @brief SunShader, PhongShader:
  *  encapsulation of shaders
  */
 ShaderUniforms SunShader, PhongShader;
 

void initGL() {
 
    glClearColor(0,0,0,0);   // set the clear color to black
    glEnable(GL_DEPTH_TEST); // turn on the depth test
    glEnable(GL_CULL_FACE);  // turn on backface culling


    // set the camera:

    glm::vec3 eye(50,80,-160);
    glm::vec3 center(0,0,0);
    glm::vec3 up(0,1,0);


    V = glm::lookAt(eye,center,up);



    // enable line smoothing:
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);



    createProgram_VF("sun_VS.glsl",		"sun_FS.glsl",&SunShader.Shader);
    createProgram_VF("phong_VS.glsl",	"phong_FS.glsl",&PhongShader.Shader);

   
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei) w, (GLsizei) h);

	P = glm::perspective(70.0f, (GLfloat) w/ (GLfloat) h, 10.0f, 400.0f);  

}

void onIdle() {

  t+= speed;  // increase the time parameter
  
  glutPostRedisplay();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	//TODO  Implement the drawing of the scene here.

	// Note that the matrices and other uniforms have to be updated/bound
    // whenever you issue a new draw command with different values

	// Create a modelmatrix M for the positioning of  planets
	
	
	//draw a yellow sun
	
	//draw a blue earth
	
	// draw the grey earth moon 
	// remember that the transformation of the earth also affects toe moon
	
	//draw saturn with its rings
	
    // Hint: before you draw geometry make sure the shader is bound, as well as the uniforms



	glutSwapBuffers();
}


// the keyboard handler:

void keyboard(unsigned char key, int x, int y) {
  
  switch(key) {
    
    case 'p': // toggle polygon mode:	
      wireframe_mode = !wireframe_mode;
      if (wireframe_mode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
        
      // increase / decrease the speed of the point light P:     
    case '+':
      speed += 0.01;
      break;
    case '-':
       speed -= 0.01;
      break;
  }
  
  
  glutPostRedisplay();	
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(1042, 1024);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
  glutCreateWindow("Planet System");
  
   GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }
	
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutIdleFunc(onIdle);
	
  initGL();
  
  
  
  glutMainLoop();
}
