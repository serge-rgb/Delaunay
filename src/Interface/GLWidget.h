/*
 * GLWidget.h
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

#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include "../common.h"
#include "../Renderer.h"

class GLWidget : QGLWidget{
public:
    GLWidget(QWidget *parent = 0);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent * event);
private:
    Renderer renderer;
    vector<Vec> clicks;
};

#endif /* GLWIDGET_H_ */
