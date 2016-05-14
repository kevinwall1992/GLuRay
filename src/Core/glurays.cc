#include "GLuRayS.h"

#include <assert.h>


void grs_GenBuffers(GLsizei n, GLuint* buffers)
{
  for(unsigned int i= 0; i< n; i++)
    buffers[i]= Buffer::CreateBuffer(buffers[i]);
}

void grs_DeleteBuffers(GLsizei n, const GLuint* buffers)
{
  for(unsigned int i= 0; i< n; i++)
    Buffer::DeleteBuffer(buffers[i]);
}

Buffer * GetBufferFromTarget(GLenum target)
{
  if(target== GL_ARRAY_BUFFER)
    return Buffer::GetBoundVertexBuffer();
  else if(target== GL_ELEMENT_ARRAY_BUFFER)
    return Buffer::GetBoundElementBuffer();
  else if(target== GL_UNIFORM_BUFFER)
    return Buffer::GetBoundUniformBuffer();

  return nullptr;
}

void grs_BindBuffer(GLenum target, GLuint buffer)
{
  if(buffer< 1)
    return;
  
  if(target== GL_ARRAY_BUFFER)
    Buffer::GetBuffer(buffer)->BindAsVertexBuffer();
  else if(target== GL_ELEMENT_ARRAY_BUFFER)
    Buffer::GetBuffer(buffer)->BindAsElementBuffer();
  else if(target== GL_UNIFORM_BUFFER)
    Buffer::GetBuffer(buffer)->BindAsUniformBuffer(); 
}

void grs_BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
  Buffer *buffer= GetBufferFromTarget(target);
  if(buffer!= nullptr)
    buffer->InitializeData(size, data);
}

void grs_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
  Buffer *buffer= GetBufferFromTarget(target);
  if(buffer!= nullptr)
    buffer->SetData(data, size, offset);
}

void grs_BindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
  assert(("grs_BindBufferBase: only support GL_UNIFORM_BUFFER target", target== GL_UNIFORM_BUFFER));

  if(target== GL_UNIFORM_BUFFER)
    Buffer::GetBuffer(buffer)->BindToUniformBufferIndex(index);
}

void * grs_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
  Buffer *buffer= GetBufferFromTarget(target);
  
  if(buffer!= nullptr)
    return (void *)((char *)buffer->GetData()+ offset);

  return nullptr;
}

GLboolean grs_UnmapBuffer(GLenum target)
{
  return GL_TRUE;
}

void * grs_MapBuffer(GLenum target, GLenum access)
{
  Buffer *buffer= GetBufferFromTarget(target);

  if(buffer!= nullptr)
    return (void *)(buffer->GetData());

  return nullptr;
}


GLuint grs_CreateShader(GLenum type, GLuint gl_result)
{
  Shader *shader= Shader::GetShader(Shader::CreateShader(gl_result));
  shader->SetType(type);
  
  return shader->GetID();
}

void grs_ShaderSource(GLuint shader_id, GLsizei count, const GLchar* const* strings, const GLint* lengths)
{

}

void grs_CompileShader(GLuint shader)
{
  
}

void grs_DeleteShader(GLuint shader)
{
  Shader::DeleteShader(shader);
}

GLuint grs_CreateProgram(GLuint gl_result)
{
  return ShaderProgram::CreateShaderProgram(gl_result);
}

void grs_AttachShader(GLuint program, GLuint shader)
{
  ShaderProgram *shader_program= ShaderProgram::GetShaderProgram(program);
  
  shader_program->AttachShader(shader);
}

void grs_DetachShader(GLuint program, GLuint shader)
{
  ShaderProgram *shader_program= ShaderProgram::GetShaderProgram(program);
  
  shader_program->DetachShader(shader);
}

void grs_UseProgram(GLuint program)
{
  if(program< 1)
    return;
  
  ShaderProgram::GetShaderProgram(program)->Use();
}

void grs_DeleteProgram(GLuint program)
{
  ShaderProgram::DeleteShaderProgram(program);
}

GLint grs_GetUniformLocation(GLuint program, const GLchar* name, int gl_result)
{
  Uniform *uniform= ShaderProgram::GetShaderProgram(program)->GetUniform(name);
  if(uniform== nullptr)
    return ShaderProgram::GetShaderProgram(program)->CreateUniform(gl_result, name);
  
  return uniform->GetID();
}

void grs_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
  Uniform *uniform= Uniform::GetUniform(location);
  assert(("grs_Uniform*: uniform does not exist", uniform!= nullptr));
  
  uniform->SetVector3f(v0, v1, v2);
}

void grs_Uniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
  if(count> 1)
    return;
  
  Uniform *uniform= Uniform::GetUniform(location);
  assert(("grs_Uniform*: uniform does not exist", uniform!= nullptr));
  
  uniform->SetVector3f(value[0], value[1], value[2]);
}

void grs_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  Uniform *uniform= Uniform::GetUniform(location);
  assert(("grs_Uniform*: uniform does not exist", uniform!= nullptr));
  
  uniform->SetVector4f(v0, v1, v2, v3);
}

void grs_Uniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
  if(count> 1)
    return;
  
  Uniform *uniform= Uniform::GetUniform(location);
  assert(("grs_Uniform*: uniform does not exist", uniform!= nullptr));
  
  uniform->SetVector4f(value[0], value[1], value[2], value[3]);
}

void grs_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
  assert(("grs_UniformMatrix4fv: Host code asked for transpose.", transpose== false));
  
  if(count> 1)
    return;
  
  Uniform *uniform= Uniform::GetUniform(location);
  assert(("grs_Uniform*: uniform does not exist", uniform!= nullptr));
  
  uniform->SetMatrix4x4f(value);
}

void grs_GenVertexArrays(GLsizei n, GLuint* arrays)
{
  for(unsigned int i= 0; i< n; i++)
    arrays[i]= VertexArrayObject::CreateVertexArrayObject(arrays[i]);
}

void grs_DeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
  for(unsigned int i= 0; i< n; i++)
    VertexArrayObject::DeleteVertexArrayObject(arrays[i]);
}

void grs_BindVertexArrays(GLuint array)
{
  if(array< 1)
    return;
  
  VertexArrayObject::GetVertexArrayObject(array)->Bind();
}

GLint grs_GetAttributeLocation(GLuint program, const GLchar* name, int gl_result)
{
  VertexAttribute *vertex_attribute= VertexAttribute::GetVertexAttribute(name);
  if(vertex_attribute== nullptr)
    return ShaderProgram::GetShaderProgram(program)->CreateVertexAttribute(gl_result, name);
  
  return vertex_attribute->GetID();
}

void grs_EnableVertexAttributeArray(GLuint attribute)
{
  VertexAttributeArray *vertex_attribute_array= VertexAttributeArray::GetVertexAttributeArray(attribute);
  
  if(vertex_attribute_array== nullptr)
    vertex_attribute_array= VertexAttributeArray::GetVertexAttributeArray(VertexAttributeArray::CreateVertexAttributeArray(attribute));
  
  vertex_attribute_array->Enable();
}

void grs_DisableVertexAttributeArray(GLuint attribute)
{
  VertexAttributeArray::GetVertexAttributeArray(attribute)->Disable();
}

void grs_VertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
  VertexAttributeArray *vertex_attribute_array= VertexAttributeArray::GetVertexAttributeArray(index);
  
  if(vertex_attribute_array== nullptr)
    vertex_attribute_array= VertexAttributeArray::GetVertexAttributeArray(VertexAttributeArray::CreateVertexAttributeArray(index));
  
  vertex_attribute_array->SetValues(size, type, stride, (size_t)pointer);
  vertex_attribute_array->SetSourceBufferID(Buffer::GetBoundVertexBuffer()->GetID());
}


void grs_DrawArrays(GLenum mode, GLint first, GLsizei count)
{
  RenderModel *render_model_instance= RenderModel::GetRenderModelInstance(false);
  
  if(render_model_instance!= nullptr)
    render_model_instance->Draw(DrawCall::GetArraysDrawCall(mode, first, count));
}

void grs_DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices)
{
  RenderModel *render_model_instance= RenderModel::GetRenderModelInstance(true);
  
  if(render_model_instance!= nullptr)
    render_model_instance->Draw(DrawCall::GetElementsDrawCall(mode, count, type, (size_t)indices));
}

void grs_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices)
{
  RenderModel *render_model_instance= RenderModel::GetRenderModelInstance(true);
  
  if(render_model_instance!= nullptr)
    render_model_instance->Draw(DrawCall::GetElementsDrawCall(mode, count, type, (size_t)indices, start, end));
}
