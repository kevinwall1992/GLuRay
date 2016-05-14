#include "defines.h"
#include "gluray.h"


// GL_VERSION_1_0

void glBegin(GLenum mode)
{
  next_glBegin(mode);
  printGLError();

  gr_beginPrimitive(mode);

  debugPrint("glBegin(mode= %s)\n", getEnumString(mode));
}

void glCallList(GLuint list)
{
  gr_callList(list);
  debugPrint("glCallList(list= %u)\n", list);
}

void glClear(GLbitfield mask)
{
  next_glClear(mask);
  printGLError();

  gr_clear(mask);

  debugPrint("glClear(mask= %x)\n", mask);
}

void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  next_glClearColor(red, green, blue, alpha);
  printGLError();

  gr_setBackgroundColor(red, green, blue, alpha);

  debugPrint("glClearColor(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
  next_glColor3d(red, green, blue);
  printGLError();

  gr_setColor(red,green,blue, 1.0f);

  debugPrint("glColor3d(red= %f, green= %f, blue= %f)\n", red, green, blue);
}

void glColor3dv(const GLdouble* v)
{
  next_glColor3dv(v);
  printGLError();

  gr_setColor(v[0],v[1],v[2], 1.0f);

  debugPrint("glColor3dv(v= %x)\n", v);
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
  next_glColor3f(red, green, blue);
  printGLError();

  gr_setColor(red,green,blue, 1.0f);

  debugPrint("glColor3f(red= %f, green= %f, blue= %f)\n", red, green, blue);
}

void glColor3fv(const GLfloat* v)
{
  next_glColor3fv(v);
  printGLError();

  gr_setColor(v[0],v[1],v[2], 1.0f);

  debugPrint("glColor3fv(v= %x)\n", v);
}

void glColor3iv(const GLint* v)
{
  next_glColor3iv(v);
  printGLError();

  gr_setColor(v[0],v[1],v[2], 1.0f);

  debugPrint("glColor3iv(v= %x)\n", v);
}

void glColor3ubv(const GLubyte* v)
{
  next_glColor3ubv(v);
  printGLError();

  gr_setColorub(v[0], v[1], v[2], 255);

  debugPrint("glColor3ubv(v= %x)\n", v);
}

void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
  next_glColor4d(red, green, blue, alpha);
  printGLError();

  gr_setColor(red,green,blue, alpha);

  debugPrint("glColor4d(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glColor4dv(const GLdouble* v)
{
  next_glColor4dv(v);
  printGLError();

  gr_setColor(v[0],v[1],v[2],v[3]);

  debugPrint("glColor4dv(v= %x)\n", v);
}

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  next_glColor4f(red, green, blue, alpha);
  printGLError();

  gr_setColor(red,green,blue, alpha);

  debugPrint("glColor4f(red= %f, green= %f, blue= %f, alpha= %f)\n", red, green, blue, alpha);
}

void glColor4fv(const GLfloat* v)
{
  next_glColor4fv(v);
  printGLError();

  gr_setColor(v[0],v[1],v[2],v[3]);

  debugPrint("glColor4fv(v= %x)\n", v);
}

void glColor4ubv(const GLubyte* v)
{
  next_glColor4ubv(v);
  printGLError();

  gr_setColorub(v[0],v[1],v[2],v[3]);

  debugPrint("glColor4ubv(v= %x)\n", v);
}

void glDeleteLists(GLuint list, GLsizei range)
{
  next_glDeleteLists(list, range);
  printGLError();

  gr_deleteLists(list, range);

  debugPrint("glDeleteLists(list= %u, range= %u)\n", list, range);
}

void glDisable(GLenum cap)
{
  next_glDisable(cap);
  printGLError();

  gr_disable(cap);

  debugPrint("glDisable(cap= %s)\n", getEnumString(cap));
}

void glEnable(GLenum cap)
{
  next_glEnable(cap);
  printGLError();

  gr_enable(cap);

  debugPrint("glEnable(cap= %s)\n", getEnumString(cap));
}

void glEnd()
{
  next_glEnd();
  printGLError();

  gr_endPrimitive();

  debugPrint("glEnd()\n");
}

void glEndList()
{
  gr_endList();
  debugPrint("glEndList()\n");
}

void glFinish()
{
  next_glFinish();
  printGLError();

  if (GLURAY_RENDER_MODE & GLURAY_RENDER_GLFINISH)
    gr_render();

  debugPrint("glFinish()\n");
}

void glFlush()
{
  next_glFlush();
  printGLError();

  if (GLURAY_RENDER_MODE & GLURAY_RENDER_GLFLUSH)
    gr_render();

  debugPrint("glFlush()\n");
}

void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
  next_glFrustum(left, right, bottom, top, zNear, zFar);
  printGLError();

  gr_frustum(left,right,bottom,top,zNear,zFar);

  debugPrint("glFrustum(left= %f, right= %f, bottom= %f, top= %f, zNear= %f, zFar= %f)\n", left, right, bottom, top, zNear, zFar);
}

void glLightfv(GLenum light, GLenum pname, const GLfloat* params)
{
  next_glLightfv(light, pname, params);
  printGLError();

  gr_light(light, pname, params);

  debugPrint("glLightfv(light= %s, pname= %s, params= %x)\n", getEnumString(light), getEnumString(pname), params);
}

void glLoadIdentity()
{
  next_glLoadIdentity();
  printGLError();

  gr_loadIdentity();

  debugPrint("glLoadIdentity()\n");
}

void glLoadMatrixd(const GLdouble* m)
{
  next_glLoadMatrixd(m);
  printGLError();

  gr_loadMatrixd(m);

  debugPrint("glLoadMatrixd(m= %x)\n", m);
}

void glLoadMatrixf(const GLfloat* m)
{
  next_glLoadMatrixf(m);
  printGLError();

  gr_loadMatrixf(m);

  debugPrint("glLoadMatrixf(m= %x)\n", m);
}

void glMaterialf(GLenum face, GLenum pname, GLfloat param)
{
  next_glMaterialf(face, pname, param);
  printGLError();

  gr_materialf(face, pname, param);

  debugPrint("glMaterialf(face= %s, pname= %s, param= %f)\n", getEnumString(face), getEnumString(pname), param);
}

void glMaterialfv(GLenum face, GLenum pname, const GLfloat* params)
{
  next_glMaterialfv(face, pname, params);
  printGLError();

  gr_materialfv(face, pname, params);

  debugPrint("glMaterialfv(face= %s, pname= %s, params= %x)\n", getEnumString(face), getEnumString(pname), params);
}

void glMateriali(GLenum face, GLenum pname, GLint param)
{
  next_glMateriali(face, pname, param);
  printGLError();

  gr_materiali(face, pname, param);

  debugPrint("glMateriali(face= %s, pname= %s, param= %i)\n", getEnumString(face), getEnumString(pname), param);
}

void glMaterialiv(GLenum face, GLenum pname, const GLint* params)
{
  next_glMaterialiv(face, pname, params);
  printGLError();

  gr_materialiv(face, pname, params);

  debugPrint("glMaterialiv(face= %s, pname= %s, params= %x)\n", getEnumString(face), getEnumString(pname), params);
}

void glMatrixMode(GLenum mode)
{
  next_glMatrixMode(mode);
  printGLError();

  gr_matrixMode(mode);

  debugPrint("glMatrixMode(mode= %s)\n", getEnumString(mode));
}

void glMultMatrixd(const GLdouble* m)
{
  next_glMultMatrixd(m);
  printGLError();

  gr_multMatrixd(m);

  debugPrint("glMultMatrixd(m= %x)\n", m);
}

void glMultMatrixf(const GLfloat* m)
{
  next_glMultMatrixf(m);
  printGLError();

  gr_multMatrixf(m);

  debugPrint("glMultMatrixf(m= %x)\n", m);
}

void glNewList(GLuint list, GLenum mode)
{
  gr_newList(list,mode);
  debugPrint("glNewList(list= %u, mode= %s)\n", list, getEnumString(mode));
}

void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz)
{
  gr_normal(nx,ny,nz);
  debugPrint("glNormal3d(nx= %f, ny= %f, nz= %f)\n", nx, ny, nz);
}

void glNormal3dv(const GLdouble* v)
{
  gr_normal(v[0],v[1],v[2]);
  debugPrint("glNormal3dv(v= %x)\n", v);
}

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
  gr_normal(nx,ny,nz);
  debugPrint("glNormal3f(nx= %f, ny= %f, nz= %f)\n", nx, ny, nz);
}

void glNormal3fv(const GLfloat* v)
{
  gr_normal(v[0],v[1],v[2]);
  debugPrint("glNormal3fv(v= %x)\n", v);
}

void glNormal3i(GLint nx, GLint ny, GLint nz)
{
  next_glNormal3i(nx, ny, nz);
  printGLError();

  gr_normal(nx,ny,nz);

  debugPrint("glNormal3i(nx= %i, ny= %i, nz= %i)\n", nx, ny, nz);
}

void glNormal3iv(const GLint* v)
{
  next_glNormal3iv(v);
  printGLError();

  gr_normal(v[0],v[1],v[2]);

  debugPrint("glNormal3iv(v= %x)\n", v);
}

void glNormal3s(GLshort nx, GLshort ny, GLshort nz)
{
  next_glNormal3s(nx, ny, nz);
  printGLError();

  gr_normal(nx,ny,nz);

  debugPrint("glNormal3s(nx= %i, ny= %i, nz= %i)\n", nx, ny, nz);
}

void glNormal3sv(const GLshort* v)
{
  next_glNormal3sv(v);
  printGLError();

  gr_normal(v[0],v[1],v[2]);

  debugPrint("glNormal3sv(v= %x)\n", v);
}

void glPopMatrix()
{
  next_glPopMatrix();
  printGLError();

  gr_popMatrix();

  debugPrint("glPopMatrix()\n");
}

void glPushMatrix()
{
  next_glPushMatrix();
  printGLError();

  gr_pushMatrix();

  debugPrint("glPushMatrix()\n");
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
{
  if (format == GL_RGBA //TODO: this assumes compositors will read in rgba first...
    && (GLURAY_RENDER_MODE & GLURAY_RENDER_GLREADPIXELS) )
    gr_render();

  next_glReadPixels(x, y, width, height, format, type, pixels);
  printGLError();

  debugPrint("glReadPixels(x= %i, y= %i, width= %u, height= %u, format= %s, type= %s, pixels= %x)\n", x, y, width, height, getEnumString(format), getEnumString(type), pixels);
}

void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
  next_glRotated(angle, x, y, z);
  printGLError();

  gr_rotate(angle,x,y,z);

  debugPrint("glRotated(angle= %f, x= %f, y= %f, z= %f)\n", angle, x, y, z);
}

void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
  next_glRotatef(angle, x, y, z);
  printGLError();

  gr_rotate(angle,x,y,z);

  debugPrint("glRotatef(angle= %f, x= %f, y= %f, z= %f)\n", angle, x, y, z);
}

void glScaled(GLdouble x, GLdouble y, GLdouble z)
{
  next_glScaled(x, y, z);
  printGLError();

  gr_scale(x,y,z);

  debugPrint("glScaled(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glScalef(GLfloat x, GLfloat y, GLfloat z)
{
  next_glScalef(x, y, z);
  printGLError();

  gr_scale(x,y,z);

  debugPrint("glScalef(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glTexCoord2fv(const GLfloat* v)
{
  next_glTexCoord2fv(v);
  printGLError();

  gr_texCoord(v[0], v[1], 0.0);

  debugPrint("glTexCoord2fv(v= %x)\n", v);
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
{
  next_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
  printGLError();

  gr_texImage1D(target, level, internalformat, width, border, format, type, pixels);

  debugPrint("glTexImage1D(target= %s, level= %i, internalformat= %i, width= %u, border= %i, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, internalformat, width, border, getEnumString(format), getEnumString(type), pixels);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
{
  next_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
  printGLError();

  gr_texImage2D(target, level, internalformat, width, height, border, format, type, pixels);

  debugPrint("glTexImage2D(target= %s, level= %i, internalformat= %i, width= %u, height= %u, border= %i, format= %s, type= %s, pixels= %x)\n", getEnumString(target), level, internalformat, width, height, border, getEnumString(format), getEnumString(type), pixels);
}

void glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
  next_glTranslated(x, y, z);
  printGLError();

  gr_translate(x,y,z);

  debugPrint("glTranslated(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
  next_glTranslatef(x, y, z);
  printGLError();

  gr_translate(x,y,z);

  debugPrint("glTranslatef(x= %f, y= %f, z= %f)\n", x, y, z);
}

void glVertex2d(GLdouble x, GLdouble y)
{
  next_glVertex2d(x, y);
  printGLError();

  gr_addVertex(x,y,0);

  debugPrint("glVertex2d(x= %f, y= %f)\n", x, y);
}

void glVertex3d(GLdouble x, GLdouble y, GLdouble z)
{
  gr_addVertex(x,y,z);
}

void glVertex3dv(const GLdouble* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
  gr_addVertex(x,y,z);
}

void glVertex3fv(const GLfloat* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex3iv(const GLint* v)
{
  gr_addVertex(v[0],v[1],v[2]);

}

void glVertex3sv(const GLshort* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex4dv(const GLdouble* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex4fv(const GLfloat* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex4iv(const GLint* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glVertex4sv(const GLshort* v)
{
  gr_addVertex(v[0],v[1],v[2]);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
  next_glViewport(x, y, width, height);
  printGLError();

  gr_viewport(x,y,width,height);

  debugPrint("glViewport(x= %i, y= %i, width= %u, height= %u)\n", x, y, width, height);
}


// GL_VERSION_1_1

void glColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  next_glColorPointer(size, type, stride, pointer);
  printGLError();

  gr_colorPointer(size,type,stride, pointer);

  debugPrint("glColorPointer(size= %i, type= %s, stride= %u, pointer= %x)\n", size, getEnumString(type), stride, pointer);
}

void glDisableClientState(GLenum array)
{
  next_glDisableClientState(array);
  printGLError();

  gr_disableClientState(array);

  debugPrint("glDisableClientState(array= %s)\n", getEnumString(array));
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
  gr_drawArrays(mode, first, count);
  debugPrint("glDrawArrays(mode= %s, first= %i, count= %u)\n", getEnumString(mode), first, count);
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
  gr_drawElements(mode, count, type, indices);
  debugPrint("glDrawElements(mode= %s, count= %u, type= %s, indices= %x)\n", getEnumString(mode), count, getEnumString(type), indices);
}

void glEnableClientState(GLenum array)
{
  next_glEnableClientState(array);
  printGLError();

  gr_enableClientState(array);

  debugPrint("glEnableClientState(array= %s)\n", getEnumString(array));
}

void glVertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
  next_glVertexPointer(size, type, stride, pointer);
  printGLError();

  gr_vertexPointer(size,type,stride,pointer);

  debugPrint("glVertexPointer(size= %i, type= %s, stride= %u, pointer= %x)\n", size, getEnumString(type), stride, pointer);
}


// GL_VERSION_1_2

void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
  gr_drawRangeElements(mode, start, end, count, type, indices);
  debugPrint("glDrawRangeElements(mode= %s, start= %u, end= %u, count= %u, type= %s, indices= %x)\n", getEnumString(mode), start, end, count, getEnumString(type), indices);
}


// GL_VERSION_1_3


// GL_VERSION_1_4


// GL_VERSION_1_5

void glBindBuffer(GLenum target, GLuint buffer)
{
  next_glBindBuffer(target, buffer);

  gr_bindBuffer(target, buffer);
  debugPrint("glBindBuffer(target= %s, buffer= %u)\n", getEnumString(target), buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{
  next_glBufferData(target, size, NULL, usage);

  gr_bufferData(target, size, data, usage);
  debugPrint("glBufferData(target= %s, size= %u, data= %x, usage= %s)\n", getEnumString(target), size, data, getEnumString(usage));
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
  gr_bufferSubData(target, offset, size, data);
  debugPrint("glBufferSubData(target= %s, offset= %i, size= %u, data= %x)\n", getEnumString(target), offset, size, data);
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
  next_glDeleteBuffers(n, buffers);
  printGLError();

  gr_deleteBuffers(n, buffers);

  debugPrint("glDeleteBuffers(n= %u, buffers= %x)\n", n, buffers);
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
  next_glGenBuffers(n, buffers);
  printGLError();

  gr_genBuffers(n, buffers);

  debugPrint("glGenBuffers(n= %u, buffers= %x)\n", n, buffers);
}

GLboolean isBufferIntercepted(GLenum target)
{
  return target== GL_ARRAY_BUFFER || 
         target== GL_ELEMENT_ARRAY_BUFFER || 
         target== GL_UNIFORM_BUFFER;
}

GLboolean glUnmapBuffer(GLenum target)
{
  GLboolean result;

  if(isBufferIntercepted(target))
    result= gr_unmapBuffer(target);
  else
  {
    result= next_glUnmapBuffer(target);
    printGLError();
  }
  
  debugPrint("glUnmapBuffer(target= %s)= %i\n", getEnumString(target), result);

  return result;
}

void * glMapBuffer(GLenum target, GLenum access)
{
  void *result= NULL;

  if(isBufferIntercepted(target))
    result= gr_mapBuffer(target, access);
  else
  {
    result= next_glMapBuffer(target, access);
    printGLError();
  }

  debugPrint("glMapBuffer(target= %s, access= %s)= %x\n", getEnumString(target), getEnumString(access), result);

  return result;
}

// GL_VERSION_2_0

void glAttachShader(GLuint program, GLuint shader)
{
  next_glAttachShader(program, shader);
  printGLError();

  gr_attachShader(program, shader);

  debugPrint("glAttachShader(program= %u, shader= %u)\n", program, shader);
}

void glDeleteShader(GLuint shader)
{
  next_glDeleteShader(shader);
  printGLError();

  gr_deleteShader(shader);

  debugPrint("glDeleteShader(shader= %u)\n", shader);
}

void glCompileShader(GLuint shader)
{
  next_glCompileShader(shader);
  printGLError();

  gr_compileShader(shader);

  debugPrint("glCompileShader(shader= %u)\n", shader);
}

GLuint glCreateProgram()
{
  GLuint result= next_glCreateProgram();
  printGLError();

  gr_createProgram(result);

  debugPrint("glCreateProgram()= %u\n", result);

  return result;
}

GLuint glCreateShader(GLenum type)
{
  GLuint result= next_glCreateShader(type);
  printGLError();

  gr_createShader(type, result);

  debugPrint("glCreateShader(type= %s)= %u\n", getEnumString(type), result);

  return result;
}

void glDeleteProgram(GLuint program)
{
  next_glDeleteProgram(program);
  printGLError();

  gr_deleteProgram(program);

  debugPrint("glDeleteProgram(program= %u)\n", program);
}

void glDisableVertexAttribArray(GLuint index)
{
  next_glDisableVertexAttribArray(index);
  printGLError();

  gr_disableVertexAttributeArray(index);

  debugPrint("glDisableVertexAttribArray(index= %u)\n", index);
}

void glEnableVertexAttribArray(GLuint index)
{
  next_glEnableVertexAttribArray(index);
  printGLError();

  gr_enableVertexAttributeArray(index);

  debugPrint("glEnableVertexAttribArray(index= %u)\n", index);
}

GLint glGetAttribLocation(GLuint program, const GLchar* name)
{
  GLuint result= gr_getAttributeLocation(program, name, -1);
  debugPrint("glGetAttribLocation(program= %u, name= %s)= %i\n", program, name, result);

  return result;
}

GLint glGetUniformLocation(GLuint program, const GLchar* name)
{
  GLuint result= gr_getUniformLocation(program, name, -1);
  debugPrint("glGetUniformLocation(program= %u, name= %s)= %i\n", program, name, result);

  return result;
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar*const* string, const GLint* length)
{
  next_glShaderSource(shader, count, string, length);
  printGLError();

  gr_shaderSource(shader, count, string, length);

  debugPrint("glShaderSource(shader= %u, count= %u, string= %x, length= %x)\n", shader, count, string, length);
}

void glUniform1f(GLint location, GLfloat v0)
{
  debugPrint("glUniform1f(location= %i, v0= %f)\n", location, v0);
}

void glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
{
  debugPrint("glUniform1fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform1i(GLint location, GLint v0)
{
  debugPrint("glUniform1i(location= %i, v0= %i)\n", location, v0);
}

void glUniform1iv(GLint location, GLsizei count, const GLint* value)
{
  debugPrint("glUniform1iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
  debugPrint("glUniform2f(location= %i, v0= %f, v1= %f)\n", location, v0, v1);
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
  debugPrint("glUniform2fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform2i(GLint location, GLint v0, GLint v1)
{
  debugPrint("glUniform2i(location= %i, v0= %i, v1= %i)\n", location, v0, v1);
}

void glUniform2iv(GLint location, GLsizei count, const GLint* value)
{
  debugPrint("glUniform2iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
  debugPrint("glUniform3i(location= %i, v0= %i, v1= %i, v2= %i)\n", location, v0, v1, v2);
}

void glUniform3iv(GLint location, GLsizei count, const GLint* value)
{
  debugPrint("glUniform3iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
  debugPrint("glUniform4i(location= %i, v0= %i, v1= %i, v2= %i, v3= %i)\n", location, v0, v1, v2, v3);
}

void glUniform4iv(GLint location, GLsizei count, const GLint* value)
{
  debugPrint("glUniform4iv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix2fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix3fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  next_glUniform3f(location, v0, v1, v2);
  printGLError();

  gr_uniform3f(location, v0, v1, v2);

  debugPrint("glUniform3f(location= %i, v0= %f, v1= %f, v2= %f)\n", location, v0, v1, v2);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
  next_glUniform3fv(location, count, value);
  printGLError();

  gr_uniform3fv(location, count, value);

  debugPrint("glUniform3fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  next_glUniform4f(location, v0, v1, v2, v3);
  printGLError();

  gr_uniform4f(location, v0, v1, v2, v3);

  debugPrint("glUniform4f(location= %i, v0= %f, v1= %f, v2= %f, v3= %f)\n", location, v0, v1, v2, v3);
}

void glUniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
  next_glUniform4fv(location, count, value);
  printGLError();

  gr_uniform4fv(location, count, value);

  debugPrint("glUniform4fv(location= %i, count= %u, value= %x)\n", location, count, value);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  next_glUniformMatrix4fv(location, count, transpose, value);
  printGLError();

  gr_uniformMatrix4fv(location, count, transpose, value);

  debugPrint("glUniformMatrix4fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUseProgram(GLuint program)
{
  next_glUseProgram(program);
  printGLError();

  gr_useProgram(program);

  debugPrint("glUseProgram(program= %u)\n", program);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
{
  next_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
  printGLError();

  gr_vertexAttributePointer(index, size, type, normalized, stride, pointer);

  debugPrint("glVertexAttribPointer(index= %u, size= %i, type= %s, normalized= %i, stride= %u, pointer= %x)\n", index, size, getEnumString(type), normalized, stride, pointer);
}


// GL_VERSION_2_1

void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix2x3fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix2x4fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix3x2fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix3x4fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix4x2fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  debugPrint("glUniformMatrix4x3fv(location= %i, count= %u, transpose= %i, value= %x)\n", location, count, transpose, value);
}

// GL_VERSION_3_0

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
  next_glBindBufferBase(target, index, buffer);
  printGLError();

  gr_bindBufferBase(target, index, buffer);

  debugPrint("glBindBufferBase(target= %s, index= %u, buffer= %u)\n", getEnumString(target), index, buffer);
}

void glBindVertexArray(GLuint array)
{
  next_glBindVertexArray(array);
  printGLError();

  gr_bindVertexArrays(array);

  debugPrint("glBindVertexArray(array= %u)\n", array);
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
  next_glClearBufferfv(buffer, drawbuffer, value);
  printGLError();

  if(buffer== GL_COLOR)
    gr_clear(GL_COLOR_BUFFER_BIT);
  if(buffer== GL_DEPTH)
    gr_clear(GL_DEPTH_BUFFER_BIT);
  

  debugPrint("glClearBufferfv(buffer= %s, drawbuffer= %i, value= %x)\n", getEnumString(buffer), drawbuffer, value);
}

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
  next_glDeleteVertexArrays(n, arrays);
  printGLError();

  gr_deleteVertexArrays(n, arrays);

  debugPrint("glDeleteVertexArrays(n= %u, arrays= %x)\n", n, arrays);
}

void glGenVertexArrays(GLsizei n, GLuint* arrays)
{
  next_glGenVertexArrays(n, arrays);
  printGLError();

  gr_genVertexArrays(n, arrays);

  debugPrint("glGenVertexArrays(n= %u, arrays= %x)\n", n, arrays);
}

void * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  void *result= NULL;

  if(isBufferIntercepted(target))
    result= gr_mapBufferRange(target, offset, length, access);
  else
  {
    result= next_glMapBufferRange(target, offset, length, access);
    printGLError();
  }

  debugPrint("glMapBufferRange(target= %s, offset= %i, length= %u, access= %x)= %x\n", getEnumString(target), offset, length, access, result);

  return result;
}


// GL_VERSION_3_1

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
  if(instancecount== 1)
    gr_drawArrays(mode, first, count);
  debugPrint("glDrawArraysInstanced(mode= %s, first= %i, count= %u, instancecount= %u)\n", getEnumString(mode), first, count, instancecount);
}


// GL_VERSION_3_2


// GL_VERSION_3_3


// GL_VERSION_4_0


// GL_VERSION_4_1


// GL_VERSION_4_2

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
  if(instancecount== 1)
    gr_drawArrays(mode, first, count);
  debugPrint("glDrawArraysInstancedBaseInstance(mode= %s, first= %i, count= %u, instancecount= %u, baseinstance= %u)\n", getEnumString(mode), first, count, instancecount, baseinstance);
}


// GL_VERSION_4_3


// GL_VERSION_4_4


// GL_VERSION_4_5


//GLX

XVisualInfo * glXChooseVisual(Display * dpy, GLint screen, GLint * attriblist) {
  XVisualInfo * result = NULL;
  result = next_glXChooseVisual(dpy, screen, attriblist);
  gr_chooseVisual(result);

  debugPrint("glXChooseVisual()\n");
  
  return result;
}

void glXDestroyContext(Display * dpy, GLXContext ctx) 
{
  //next_glXDestroyContext(dpy, ctx);
  //debugPrint("glXDestroyContext()\n");

  //Should this not block the call?
}

Bool glXMakeCurrent(Display * dpy, GLXDrawable drawable, GLXContext ctx) 
{
  gr_makeCurrent(drawable);
  
  Bool result;
  result = next_glXMakeCurrent(dpy, drawable, ctx);

  debugPrint("glXMakeCurrent()\n");
  
  return result;
}

void glXSwapBuffers(Display * dpy, GLXDrawable drawable) 
{
  if (GLURAY_RENDER_MODE & GLURAY_RENDER_GLXSWAPBUFFERS)
    gr_render();
  
  next_glXSwapBuffers(dpy, drawable);
}


// MPI

#include <UseMPI.h>
#if USE_MPI
#include <mpi.h>
#endif

#if USE_MPI
int MPI_Init(int *argc, char*** argv)
{
  printf("GLURAY Initializing MPI\n");
  int provided=-1;
  int requested=MPI_THREAD_MULTIPLE;

  //int argc = 1;
  //char*** argv = NULL;
  int initialized;
  MPI_Initialized(&initialized);
  if (!initialized)
  {
    MPI_Init_thread(argc, argv, requested, &provided);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0 && (provided != requested))
      printf("Error:  MPI provided does not support MPI_THREAD_MULTIPLE\n do not run with more than one thread\n");
}
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("MPI_Init rank: %d\n", rank);
}

int MPI_Finalize(void)
{
  GLLOCK();
  next_MPI_Finalize();
  GLUNLOCK();
}
#endif

