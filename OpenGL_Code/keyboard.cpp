/** Ch01 - 3
 *=============================================================================!
 *
 *  Program: keyboard.cpp
 *
 *  by (BeH)
 *
 *  This program demonstrates normal & special keyboard event handler.
 *  The  callback functions are 
 *
 *     void glutKeyboardFunc( void (*func)(unsigned char key, int x, int y) );
 *     void glutSpecialFunc( void (*func)(int key, int x, int y) );
 *
 *  Press normal key to change image color:
 *    'r' - red,      'g' - green,   'b' - blue, 
 *    'y' - yellow,   'c' - cyan,    'm' - magenta,
 *    '+' & '-' key - magnify & reduce the image size
 *    'Esc' - Escape the program.
 *
 *  Press special key to rotate image & change viewmode:
 *    'up   & down arrow'  -  rotate angle on x-axis
 *    'left & rite arrow'  -  rotate angle on y-axis
 *    'PgUp & PgDn'        -  rotate angle on z-axis
 *    'Home'               -  reset the angle to initial state
 *
 *    'F1 to F4'           -  change the viewing mode
 *    'F11 & F12'          -  toggle the window to full size & initial size
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

#define   PI   3.1415926535897932384626

// set window size & image size coordinates & image view mode 
GLsizei   viewmode;
GLsizei   wwidth = 320, wheight = 320; // initial window width & height
GLdouble  magfac = 0.60;
GLdouble  ix1 =  0.0,  ix2 = 2.0,
          iy1 =  0.0,  iy2 = 2.0,
          iz1 = -1.0,  iz2 = 1.0;
GLfloat   xrot, yrot, zrot;
GLfloat   red=1.0, green=1.0, blue=1.0, alpha=1.0;

// function prototypes
void  showOpenGLInfo( char * );
void  initRendering();
void  reshape( int, int );
void  display( void );
void  keyboard( unsigned char, int, int );
void  special( int, int, int );


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
      glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
      glutInitWindowSize( wwidth, wheight );
      glutInitWindowPosition( 100,100 );
      glutCreateWindow( "OpenGL: Keyboard Events Handler" );
      showOpenGLInfo( argv[0] );

      // initialize rendering & register callbacks
      initRendering();
      glutDisplayFunc( display );
      glutReshapeFunc( reshape );

      // handling keyboard input events
      glutKeyboardFunc( keyboard  );
      glutSpecialFunc( special );

      // enter GLUT event processing cycle
      glutMainLoop();

      return 0;
}


/******************************************************************************!
 *    show OpenGL Info through the Console Mode
 ******************************************************************************!
 */
void  showOpenGLInfo( char *progname )
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

      fprintf( stderr, "\n%s\n\n", progname);
      fprintf( stderr, "This program demonstrates the normal & special "
                       "keyboard event handler\n\n"
                       "F1 ~ F4      - change the view mode\n"
                       "F9 & F10     - toggle the fullsize window\n"
                       "Arrow keys   - rotate the object on x & y axis\n"
                       "Page Up/Down - rotate the object on z axis\n"
                       "'+' & '-'    - magnify & reduce the object\n"
                       "Home - reset the rotation angle\n"
                       "Esc  - exit the program\n" );
      return;
}


/******************************************************************************!
 *    Initialize OpenGL rendering
 ******************************************************************************!
 */
void  initRendering()
{
      glClearColor( 0.0f, 0.0f, 0.0f, 1.0f ); // black background
      glShadeModel( GL_FLAT );
}


/******************************************************************************!
 *    Handling resize window
 ******************************************************************************!
 */
void  reshape( int w, int h )
{
      // set window size & image size coordinates & image view mode 
      double  x1, x2, y1, y2, z1, z2;
      double  aspect, ww, hh, ixc, iyc, izc;
      double  theta, distance;

      // Calculate coordinates & object size
      ixc = 0.5 * (ix2 + ix1);  // x-coord. center point in image 
      iyc = 0.5 * (iy2 + iy1);  // y-coord. center point in image 
      izc = 0.5 * (iz2 + iz1);  // z-coord. center point in image 

      x1 = (ix1 - (1.0-magfac)*ixc) / magfac; 
      x2 = (ix2 - (1.0-magfac)*ixc) / magfac; 
      y1 = (iy1 - (1.0-magfac)*iyc) / magfac; 
      y2 = (iy2 - (1.0-magfac)*iyc) / magfac; 
      z1 = (iz1 - (1.0-magfac)*izc) / magfac; 
      z2 = (iz2 - (1.0-magfac)*izc) / magfac; 

      ww = (GLdouble)w / (GLdouble)wwidth;
      hh = (GLdouble)h / (GLdouble)wheight;


     /*---------------------------------------------------------------!
      *  Set Image View Mode
      *---------------------------------------------------------------!
      */
      // Prevent a divide by zero, when window is too short
      if (h == 0) h = 1;
      aspect = (GLdouble)w / (GLdouble)h;

      // Tell OpenGL how to convert from coordinates to pixel values    
      glViewport( 0, 0, w, h );
      
      glMatrixMode( GL_PROJECTION );     // Select the Projection Matrix
      glLoadIdentity();                  // Reset  the Projection Matrix


      switch (viewmode)
      {
         case 1:  // Set range of the ortho view area
                  glOrtho( x1*ww, x2*ww,
                           y1*hh, y2*hh, z1, z2 );
               // gluOrtho2D( x1*ww, x2*ww, y1*hh, y2*hh );
                  glTranslatef( ixc*ww - ixc, iyc*hh - iyc, izc );
                  break;


         case 2:  // Set range of the ortho view area & magnify the image
                  if (w >= h) {
                  glOrtho( x1*aspect, x2*aspect,
                           y1*1.000f, y2*1.000f, z1, z2 );
               // gluOrtho2D( x1*aspect, x2*aspect, y1, y2 );
                  glTranslatef( ixc*aspect - ixc, iyc*1.000f - iyc, izc );
                  } else {
                  glOrtho( x1/1.000f, x2/1.000f,
                           y1/aspect, y2/aspect, z1, z2 );
               // gluOrtho2D( x1, x2, y1/aspect, y2/aspect );
                  glTranslatef( ixc/1.000f - ixc, iyc/aspect - iyc, izc );
                  }
                  break;


         case 3:  // Set range of the Frustum view area & magnify the image
                  if (w >= h) {
                  glFrustum( x1*aspect, x2*aspect,
                             y1*1.000f, y2*1.000f,
                             100.0*(double)w, 1000.0*(double)w );
                  gluLookAt( ixc - ixc*aspect, iyc - iyc*1.000f, 101.0*(double)w,
                             ixc - ixc*aspect, iyc - iyc*1.000f, 0.0f,
                             0.0, 1.0, 0.0 );
                  } else {
                  glFrustum( x1/1.000f, x2/1.000f,
                             y1/aspect, y2/aspect,
                             100.0*(double)w, 1000.0*(double)w );
                  gluLookAt( ixc - ixc/1.000f, iyc - iyc/aspect, 101.0*(double)w,
                             ixc - ixc/1.000f, iyc - iyc/aspect, 0.0f,
                             0.0, 1.0, 0.0 );
                  }
                  break;


         case 4:  // Set the camera perspective
                  distance = 100.0f * (double)w;
                  theta = 2.0f * atan2( abs(y2-y1)/2.0, distance ) / (PI/180.0f);
                  gluPerspective( theta,                // camera angle
                                  aspect,               // w-to-h ratio
                                  100.0*(double)w, 1000.0*(double)w );
                  gluLookAt( ixc, iyc, 101.0*(double)w,
                             ixc, iyc, 0.0f,
                             0.0, 1.0, 0.0 );
                  break;


         default:
                  gluOrtho2D( x1*ww, x2*ww,  y1*hh, y2*hh );
                  // move the coord. to the center of image
                  glTranslatef( ixc*ww - ixc, iyc*hh - iyc, izc );
                  break;
      }

      glMatrixMode( GL_MODELVIEW );
      glLoadIdentity();
}


/******************************************************************************!
 *    drawing handler
 ******************************************************************************!
 */
void  display( void )
{
      char  info[128];

      // clear all color & depth buffers
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

      /*  Translate & rotate the image  */
      glPushMatrix();
      glTranslatef( 1.0, 1.0, 0.0 );       // move rotation axis to center
      glRotatef( xrot, 1.0f, 0.0f, 0.0f ); // rotate the image
      glRotatef( yrot, 0.0f, 1.0f, 0.0f );
      glRotatef( zrot, 0.0f, 0.0f, 1.0f );
      glTranslatef(-1.0, -1.0, 0.0 );      // restore axis origin


      /*  Draw triangle  */
      glColor4f( red, green, blue, alpha ); // color set as RGBA 
      glBegin( GL_TRIANGLES );
            glVertex3f( 0.0f, 0.0f, 0.0f );
            glVertex3f( 2.0f, 1.0f, 0.0f );
            glVertex3f( 1.0f, 2.0f, 0.0f );
      glEnd();
      glPopMatrix();     // restore the coord. matrix

      sprintf_s( info, "x=%.1f, y=%.1f, z=%.1f,  mag=%.2f", xrot, yrot, zrot, magfac );
      glutSetWindowTitle( info );

      glFlush();
}


/******************************************************************************!
 *    Handle normal key events
 ******************************************************************************!
 */
void  keyboard( unsigned char key, int x, int y )
{
      int   mod;

      switch (key) {
         case 'r':
                  red = 1.0f; green = 0.0f; blue = 0.0f;
                  mod = glutGetModifiers();
                  if (mod && GLUT_ACTIVE_ALT) { // only Alt key is active
                        red = 0.5f;
                  }
                  break;

         case 'g':
                  red = 0.0f; green = 1.0f; blue = 0.0f;
                  mod = glutGetModifiers();
                  if (mod && GLUT_ACTIVE_ALT) {
                        green = 0.5f;
                  }
                  break;

         case 'b':
                  red = 0.0f; green = 0.0f; blue = 1.0f;
                  mod = glutGetModifiers();
                  if (mod && GLUT_ACTIVE_ALT) {
                        blue = 0.5f;
                  }
                  break;

         case 'y':
                  red = 1.0f; green = 1.0f; blue = 0.0f;
                  mod = glutGetModifiers();
                  if (mod && GLUT_ACTIVE_ALT) {
                        red = 0.5f; green = 0.5f;
                  }
                  break;

         case 'c':
                  red = 0.0f; green = 1.0f; blue = 1.0f;
                  mod = glutGetModifiers();
                  if (mod && GLUT_ACTIVE_ALT) {
                        green = 0.5f; blue = 0.5f;
                  }
                  break;

         case 'm':
                  red = 1.0f; green = 0.0f; blue = 1.0f;
                  mod = glutGetModifiers();
                  if (mod && GLUT_ACTIVE_ALT) {
                        red = 0.5f; blue = 0.5f;
                  }
                  break;

         case '+':
                  magfac += 0.02;
                  break;
         case '-':
                  magfac -= 0.02;
                  break;

         case 27:
                  exit(0);
                  break;

         default:
                  red = 1.0f; green = 1.0f; blue = 1.0f; alpha = 1.0f;
                  break;
      }

      glutPostRedisplay();
}


/******************************************************************************!
 *    Handle special key events
 ******************************************************************************!
 */
void  special( int key, int x, int y )
{
      switch (key) {
         //  select image view mode when reshape the window
         case GLUT_KEY_F1: // both object shape & size is not changed
                  viewmode = 1; // Ortho view mode
                  break;

         case GLUT_KEY_F2: // both object shape & size is chaned
                  viewmode = 2; // Ortho view mode
                  break;

         case GLUT_KEY_F3: // object shape is not changed but object size is chaned
                  viewmode = 3; // Frustum view mode
                  break;
  
         case GLUT_KEY_F4: // object shape is not changed but object size is chaned
                  viewmode = 4; // Perspective view mode
                  break;


         //  spin key for image rotation
         case GLUT_KEY_UP:
                  xrot -= 2.0f;
                  if (xrot < -360.0f) xrot += 360.0f;
                  break;
         case GLUT_KEY_DOWN:
                  xrot += 2.0f;
                  if (xrot > +360.0f) xrot -= 360.0f;
                  break;
         case GLUT_KEY_LEFT:
                  yrot -= 2.0f;
                  if (yrot < -360.0f) yrot += 360.0f;
                  break;
         case GLUT_KEY_RIGHT:
                  yrot += 2.0f;
                  if (yrot > +360.0f) yrot -= 360.0f;
                  break;
         case GLUT_KEY_PAGE_DOWN:
                  zrot -= 2.0f;
                  if (zrot < -360.0f) zrot += 360.0f;
                  break;
         case GLUT_KEY_PAGE_UP:
                  zrot += 2.0f;
                  if (zrot > +360.0f) zrot -= 360.0f;
                  break;
         case GLUT_KEY_HOME:
                  xrot = yrot = zrot = 0.0f;
                  break;


         case GLUT_KEY_F10: 
                  glutFullScreen();
                  break;

         case GLUT_KEY_F9:
                  glutReshapeWindow( wwidth, wheight );
                  glutPositionWindow( 100, 100 );
                  break;

         default:
                  break;
      }

      glutPostRedisplay();
}

