/** Ch01 - 3
 *=============================================================================!
 *
 *  Program: advanced_keyboard.cpp
 *
 *  by (BeH)
 *
 *  This program demonstrates advanced normal & special keyboard features.
 *  The  callback functions are 
 *
 *     int  glutSetKeyFunc( int repeatMode );
 *     void glutKeyboadUpFunc( void (*func)(unsigned char key, int x, int y) );
 *     void glutIgnoreKeyRepeat( int repeatMode );
 *     void glutSpecialUpFunc( void (*func)(int key, int x, int y) );
 *
 *  Press normal key to change image color:
 *    'Esc' - Escape the program.
 *
 *  Press special key to rotate image & change viewmode:
 *    'up   & down arrow'  -  move view location to back & front
 *    'left & rite arrow'  -  rotate view angle on left & rite
 *
 *  Ref:  http://kbaek2.tistory.com/category/OpenGL%20È°¿ë
 *
 *=============================================================================!
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
#ifdef    WIN32
#define   WIN32_LEAN_AND_MEAN
#define   WIN32_EXTRA_LEAN
#include <windows.h>
#endif
*/
#include <gl/glew.h>
#include <gl/glut.h>


GLsizei   wwidth = 480, wheight = 480; // initial window width & height
GLfloat   angle = 0.0f;          // Angle of rotation for the camera direction
GLfloat   lx = 0.0f, lz =-1.0f;  // Actual vector representing the camera's direction
GLfloat   xx = 0.0f, zz = 5.0f;  // X & Z position of the camera
GLfloat   drot  = 0.0f;          // The key states. These variables will be zero
GLfloat   dmov = 0.0f;           // when no key is being presses


// function prototypes
void  showOpenGLInfo( void );
void  initRendering();
void  display( void );
void  reshape( int, int );
void  keyboard( unsigned char, int, int );
void  pressKey( int, int, int );
void  releaseKey( int, int, int );


/******************************************************************************!
 *    Main function
 ******************************************************************************!
 */
/*
int   WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpszCmdParam , int nCmdShow )
{
*/
int   main( int argc, char *argv[] )
{
      // init GLUT and create Window
      glutInit( &argc, argv );
      glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
      glutInitWindowSize( wwidth, wheight );
      glutInitWindowPosition( 100,100 );
      glutCreateWindow( "OpenGL: Advanced Keyboard Features" );
      showOpenGLInfo();

      // initialize rendering & register callbacks
      initRendering();
      glutDisplayFunc( display );
      glutReshapeFunc( reshape );

      // handling keyboard input & Idling events
      glutKeyboardFunc( keyboard  );
      glutSpecialFunc( pressKey );
      glutIgnoreKeyRepeat(1);       // ignore key repeat press
      glutSpecialUpFunc( releaseKey );
      glutIdleFunc( display );

      // enter GLUT event processing cycle
      glutMainLoop();

      return 0;
}


/******************************************************************************!
 *    show OpenGL Info through the Console Mode
 ******************************************************************************!
 */
void  showOpenGLInfo( void )
{
   // glewExperimental = GL_TRUE; // need for keeping from access violation
      if (glewInit() != GLEW_OK) {
             fprintf( stderr, "Error: %s\n", glewGetErrorString(glewInit()) );
             exit(0);
      }
      fprintf( stderr, "OpenGL Vender:  %s\n", glGetString(GL_VENDOR) );
      fprintf( stderr, "OpenGL Version: %s\n", glGetString(GL_VERSION) );
      fprintf( stderr, "GLU    Version: %s\n", gluGetString(GLU_VERSION) );
      fprintf( stderr, "GLEW   Version: %s\n", glewGetString(GLEW_VERSION) );

      return;
}


/******************************************************************************!
 *    Initialize OpenGL rendering
 ******************************************************************************!
 */
void  initRendering()
{
      // set background color & shading model
      glClearColor( 0.8f, 0.8f, 1.0f, 1.0f ); // black background
   // glShadeModel( GL_FLAT );
      glEnable( GL_DEPTH_TEST );

}


/******************************************************************************!
 *    Handling resize window
 ******************************************************************************!
 */
void  reshape( int w, int h )
{
      // Prevent a divide by zero, when window is too short
      // (you cant make a window of zero width).
      if (h == 0) h = 1;
      float aspect =  (GLfloat)w / (GLfloat)h;

      // Set the viewport to be the entire window
      glViewport(0, 0, w, h);

      // Use the Projection Matrix
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity(); // Reset Matrix

      // Set the correct perspective.
      gluPerspective( 45.0f, aspect, 0.1f, 100.0f );

      // Get Back to the Modelview
      glMatrixMode( GL_MODELVIEW );
}



/******************************************************************************!
 *    drawing handler
 ******************************************************************************!
 */
void  computePos( float );
void  computeDir( float );

void  display( void )
{
      char  info[128];

      // clear all color & depth buffers
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Reset transformations
      glLoadIdentity();

      if (dmov) computePos( dmov );
      if (drot)  computeDir( drot );
      gluLookAt( xx,    0.75f, zz,    // Set the camera
                 xx+lx, 0.75f, zz+lz,
                 0.0f,  1.0f,  0.0f );

      // Draw ground
      glColor3f( 0.2f, 0.2f, 1.0f );
      glBegin( GL_QUADS );
            glVertex3f(-100.0f, 0.0f, -100.0f );
            glVertex3f(-100.0f, 0.0f,  100.0f );
            glVertex3f( 100.0f, 0.0f,  100.0f );
            glVertex3f( 100.0f, 0.0f, -100.0f );
      glEnd();


      // Draw spheres
      for(int i = 0; i < 6; i++) {
            for(int j = 0; j < 6; j++) {
            glPushMatrix();
                  glTranslatef( (i-3)*10.0, 0.75, (j-3)*10.0 );
                  glColor3f( abs(i-6)/3.0, abs(j-3)/3.0, 0.01 );
               // glutSolidSphere( 0.75, 32, 16 );
	            glutWireCone( 0.75f, 1.5f, 24, 16 );
            glPopMatrix();
            }
      }

      sprintf( info, "Advanced Keyboard Features: x=%.1f, z=%.1f, angle=%.2f", xx, zz, angle );
      glutSetWindowTitle( info );

      glutSwapBuffers();
}

void  computePos( float dmov )
{
      xx += dmov * lx * 0.1f;
      zz += dmov * lz * 0.1f;
}

void  computeDir( float drot )
{
      angle += drot;
      lx =  sin( angle );
      lz = -cos( angle );
}


/******************************************************************************!
 *    Handle normal key events
 ******************************************************************************!
 */
void  keyboard( unsigned char key, int x, int y )
{
      switch (key) {
         case 27:
                  exit(0);
                  break;
         default:
                  break;
      }

      glutPostRedisplay();
}


/******************************************************************************!
 *    Handle special key events
 ******************************************************************************!
 */
void  pressKey( int key, int x, int y)
{
      switch (key) {
         case GLUT_KEY_LEFT:
                  drot = -0.01f;
                  break;
         case GLUT_KEY_RIGHT:
                  drot =  0.01f; 
                  break;
         case GLUT_KEY_UP  :
                  dmov =  0.50f;
                  break;
         case GLUT_KEY_DOWN:
                  dmov = -0.50f;
                  break;
         default:
                  break;
      }
      glutPostRedisplay();
}

void  releaseKey( int key, int x, int y)
{
      switch (key) {
         case GLUT_KEY_LEFT :
         case GLUT_KEY_RIGHT:
                  drot = 0.0f;
                  break;

         case GLUT_KEY_UP  :
         case GLUT_KEY_DOWN:
                  dmov = 0.0f;
                  break;
      }
      glutPostRedisplay();
}


