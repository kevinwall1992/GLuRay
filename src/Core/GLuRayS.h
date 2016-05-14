#include "GLuRayS_State.h"
#include "GLuRayS_Rendering.h"


void grs_GenBuffers(GLsizei n, GLuint* buffers);
void grs_DeleteBuffers(GLsizei n, const GLuint* buffers);
void grs_BindBuffer(GLenum target, GLuint buffer);
void grs_BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
void grs_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
void grs_BindBufferBase(GLenum target, GLuint index, GLuint buffer);
void * grs_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GLboolean grs_UnmapBuffer(GLenum target);
void * grs_MapBuffer(GLenum target, GLenum access);

GLuint grs_CreateShader(GLenum type, GLuint gl_result);
void grs_ShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths);
void grs_CompileShader(GLuint shader);
void grs_DeleteShader(GLuint shader);
GLuint grs_CreateProgram(GLuint gl_result);
void grs_AttachShader(GLuint program, GLuint shader);
void grs_DetachShader(GLuint program, GLuint shader);
void grs_UseProgram(GLuint program);
void grs_DeleteProgram(GLuint program);
GLint grs_GetUniformLocation(GLuint program, const GLchar* name, int gl_result);
void grs_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void grs_Uniform3fv(GLint location, GLsizei count, const GLfloat* value);
void grs_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void grs_Uniform4fv(GLint location, GLsizei count, const GLfloat* value);
void grs_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void grs_GenVertexArrays(GLsizei n, GLuint* arrays);
void grs_DeleteVertexArrays(GLsizei n, const GLuint* arrays);
void grs_BindVertexArrays(GLuint array);
GLint grs_GetAttributeLocation(GLuint program, const GLchar* name, int gl_result);
void grs_EnableVertexAttributeArray(GLuint attribute);
void grs_DisableVertexAttributeArray(GLuint attribute);
void grs_VertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
void grs_DrawArrays(GLenum mode, GLint first, GLsizei count);
void grs_DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
void grs_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices);
