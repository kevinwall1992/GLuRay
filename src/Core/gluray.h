
#ifdef __cplusplus
extern "C" {
#endif

void gr_init();
void gr_addVertex(float x, float y, float z);
void gr_texCoord(float x, float y, float z);
void gr_beginPrimitive(int type);
void gr_endPrimitive();
void gr_render();
void gr_setColor(float r, float g, float b, float a);
void gr_setColorub(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void gr_setBackgroundColor(float r, float g, float b, float a);
void gr_normal(float x,float y,float z);
void gr_materialfv(int face, int pname, const float* params);
void gr_materialf(int face, int pname, float param);
void gr_materialiv(int face, int pname, const int* params);
void gr_materiali(int face, int pname, int param);
void gr_translate(float x, float y, float z);
void gr_rotate(float angle, float x, float y, float z);
void gr_scale(float x, float y, float z);
void gr_newList(size_t list, int mode);
void gr_endList();
void gr_callList(int list);
void gr_deleteLists(GLuint list, GLsizei range);
void gr_enableClientState(GLenum st);
void gr_vertexPointer(GLint dim, GLenum type, GLsizei stride, const GLvoid* pointer);
void gr_colorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
void gr_drawArrays(GLenum type, GLint first, GLsizei count);
void gr_drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
void gr_drawElements_internal(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLint first);
void gr_disableClientState(GLenum st);
void gr_pushMatrix();
void gr_popMatrix();
void gr_loadIdentity();
void gr_viewport(int x, int y, int width, int height);
void gr_lookAt(float ex,float ey, float ez, float lx,
		     float ly, float lz, float ux, float uy, float uz);
void gr_makeCurrent(unsigned long winID);
void gr_chooseVisual(XVisualInfo* info);
void gr_matrixMode(int mode);
void gr_multMatrixf(const float* m);
void gr_multMatrixd(const double* m);
void gr_loadMatrixf(const float* m);
void gr_loadMatrixd(const double* m);
void gr_clear(GLbitfield mask);

void gr_light(int light, int pname, const float* params);
void gr_enable(int what);
void gr_disable(int what);

void gr_material(int pname, float* params);
void gr_frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble ar);
void gr_texImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width,
    GLint border, GLenum format, GLenum type, const GLvoid* data);
void gr_texImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
    GLint border, GLenum format, GLenum type, const GLvoid* data);
void gr_finalize();
void gr_lock(const int num);
void gr_unlock(const int num);


int gr_isInGLuRaySMode();
void gr_setGLuRaySMode();
void gr_setGLuRayMode();

void gr_genBuffers(GLsizei n, GLuint* buffers);
void gr_deleteBuffers(GLsizei n, const GLuint* buffers);
void gr_bindBuffer(GLenum target, GLuint buffer);
void gr_bufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
void gr_bufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
void gr_bindBufferBase(GLenum target, GLuint index, GLuint buffer);
void * gr_mapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GLboolean gr_unmapBuffer(GLenum target);
void * gr_mapBuffer(GLenum target, GLenum access);

GLuint gr_createShader(GLenum type, GLuint gl_result);
void gr_shaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths);
void gr_compileShader(GLuint shader);
void gr_deleteShader(GLuint shader);
GLuint gr_createProgram(GLuint gl_result);
void gr_attachShader(GLuint program, GLuint shader);
void gr_detachShader(GLuint program, GLuint shader);
void gr_useProgram(GLuint program);
void gr_deleteProgram(GLuint program);
GLint gr_getUniformLocation(GLuint program, const GLchar* name, int gl_result);
void gr_uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void gr_uniform3fv(GLint location, GLsizei count, const GLfloat* value);
void gr_uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void gr_uniform4fv(GLint location, GLsizei count, const GLfloat* value);
void gr_uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void gr_genVertexArrays(GLsizei n, GLuint* arrays);
void gr_deleteVertexArrays(GLsizei n, const GLuint* arrays);
void gr_bindVertexArrays(GLuint array);
GLint gr_getAttributeLocation(GLuint program, const GLchar* name, int gl_result);
void gr_enableVertexAttributeArray(GLuint attribute);
void gr_disableVertexAttributeArray(GLuint attribute);
void gr_vertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
void gr_drawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices);

#ifdef __cplusplus
}
#endif

