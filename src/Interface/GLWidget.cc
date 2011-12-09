/*
 * GLWidget.cc
 *
 *
 *  This file is part of Delaunay.
 *
 *  Delaunay is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Delaunay is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Delaunay.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "GLWidget.h"
#include "../Mesh.h" // For click generation

extern int W;
extern int H;

GLWidget::GLWidget(QWidget *parent) :
        QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), parent) {
    setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::initializeGL() {
    glPolygonMode((unsigned int) GL_FRONT_AND_BACK, (unsigned int) GL_LINE);
    glPointSize(7);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glLineWidth(3);
    this->setFixedSize(W,H);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);

    const Mesh mesh = Mesh::Generate(&clicks);
    renderer.Push(&mesh);
    renderer.Render();
    renderer.Remove(&mesh);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, rect().width(), 0, rect().height(), -100, 100);
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0,0,rect().width(),rect().height());
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    Vec pt(event->pos().x(), rect().height() - event->pos().y());
    clicks.push_back(pt);
    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_R) {
        clicks.clear();
        updateGL();
    }
}



