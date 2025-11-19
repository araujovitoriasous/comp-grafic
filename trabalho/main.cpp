#include "OBJLoader.h"
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
OBJLoader loader;
int windowWidth = 800;
int windowHeight = 600;

// Arcball variables
float lastX, lastY;
bool isDragging = false;
float rotationMatrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

// Camera variables
Vector3 modelCenter;
float modelScale;

// Lighting
GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 0.0f};

void init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);

  // Light setup
  GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void reshape(int w, int h) {
  windowWidth = w;
  windowHeight = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

// Map mouse coordinates to sphere
Vector3 mapToSphere(int x, int y) {
  Vector3 v;
  v.x = (2.0f * x - windowWidth) / windowWidth;
  v.y = (windowHeight - 2.0f * y) / windowHeight;
  v.z = 0.0f;

  float dist = v.x * v.x + v.y * v.y;
  if (dist > 1.0f) {
    float norm = 1.0f / sqrt(dist);
    v.x *= norm;
    v.y *= norm;
  } else {
    v.z = sqrt(1.0f - dist);
  }
  return v;
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      isDragging = true;
      lastX = x;
      lastY = y;
    } else {
      isDragging = false;
    }
  }
}

void motion(int x, int y) {
  if (isDragging) {
    Vector3 v1 = mapToSphere(lastX, lastY);
    Vector3 v2 = mapToSphere(x, y);

    // Cross product to get axis
    Vector3 axis;
    axis.x = v1.y * v2.z - v1.z * v2.y;
    axis.y = v1.z * v2.x - v1.x * v2.z;
    axis.z = v1.x * v2.y - v1.y * v2.x;

    // Dot product to get angle
    float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float angle = acos(std::min(1.0f, std::max(-1.0f, dot))) * 180.0f / M_PI;

    if (std::abs(angle) > 0.001f) {
      glPushMatrix();
      glLoadIdentity();
      glRotatef(angle, axis.x, axis.y, axis.z);
      glMultMatrixf(rotationMatrix);
      glGetFloatv(GL_MODELVIEW_MATRIX, rotationMatrix);
      glPopMatrix();
    }

    lastX = x;
    lastY = y;
    glutPostRedisplay();
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // Position camera to see the whole object
  // Distance should be related to object size.
  // 2.5 * size is usually a good safe distance for 45 deg FOV
  float dist = modelScale * 2.5f;
  gluLookAt(0, 0, dist, 0, 0, 0, 0, 1, 0);

  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  // Apply rotation
  glMultMatrixf(rotationMatrix);

  // Center the model
  glTranslatef(-modelCenter.x, -modelCenter.y, -modelCenter.z);

  loader.draw();

  glutSwapBuffers();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <obj_file>" << std::endl;
    return 1;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("OBJ Renderer");

  init();

  if (!loader.load(argv[1])) {
    return 1;
  }

  modelCenter = loader.getCenter();
  modelScale = loader.getMaxDimension();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);

  glutMainLoop();
  return 0;
}
