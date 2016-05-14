
#include "GLuRayS_State.h"

#include <Engine/Display/GLXImageDisplay.h>
#include "gluray.h"

#include <cstring>
#include <assert.h>

#include "../../NextDeclarations.h"


void Matrix::Set(float *m_)
{
  memcpy(m, m_, sizeof(float)* 16);
}

Matrix::Matrix(float *m_)
{
  Set(m_);
}


Resource::Resource(int id)
{
  this->id= id;
}

Resource::Resource()
{
  this->id= -1;
}

void Resource::Resource::SetID(int id)
{
  this->id= id;
}

int Resource::Resource::GetID()
{
  return id;
}


Mutable::Mutable()
{
  is_valid= false;
}

void Mutable::Invalidate()
{
  is_valid= false;
}

void Mutable::Validate()
{
  is_valid= true;
}

bool Mutable::IsValid()
{
  return is_valid;
}


void MutableResource::SetID(int id)
{
  Resource::SetID(id);
  
  this->Invalidate();
}


ShaderInput::ShaderInput(string name)
{
  this->name= name;
}

ShaderInput::ShaderInput()
{
  this->name= "";
}

void ShaderInput::SetName(string name)
{
  this->name= name;
  
  this->Invalidate();
}

string ShaderInput::GetName()
{
  return name;
}


Uniform::Uniform()
{
  data= nullptr;
  type= UniformType::NoneType;
}

Uniform::~Uniform()
{
  switch(type)
  {
    case UniformType::Matrix3x3f:
    case UniformType::Matrix4x4f: if (data!= nullptr) delete (float *)data; break;
    case UniformType::Vector3f: 
    case UniformType::Vector4f: if (data!= nullptr) delete (float *)data; break;
    case UniformType::Vector3i:
    case UniformType::Vector4i: if (data!= nullptr) delete (int *)data; break;
    case UniformType::Vector3ub:
    case UniformType::Vector4ub: if (data!= nullptr) delete (unsigned char *)data; break;
  }

  data= nullptr;
}

void Uniform::SetVector3f(float x, float y, float z)
{
  type= UniformType::Vector3f;
  
  float *vector= new float[3];
  vector[0]= x;
  vector[1]= y;
  vector[2]= z;
  
  this->data= (void *)vector;
}

void Uniform::SetVector4f(float x, float y, float z, float w)
{
  type= UniformType::Vector3f;
  
  float *vector= new float[4];
  vector[0]= x;
  vector[1]= y;
  vector[2]= z;
  vector[3]= w;
  
  this->data= (void *)vector;
}

void Uniform::SetVector3i(int x, int y, int z)
{
  type= UniformType::Vector3f;
  
  int *vector= new int[3];
  vector[0]= x;
  vector[1]= y;
  vector[2]= z;
  
  this->data= (void *)vector;
}

void Uniform::SetVector4i(int x, int y, int z, int w)
{
  type= UniformType::Vector3f;
  
  int *vector= new int[4];
  vector[0]= x;
  vector[1]= y;
  vector[2]= z;
  vector[3]= w;
  
  this->data= (void *)vector;
}

void Uniform::SetVector3ub(unsigned char x, unsigned char y, unsigned char z)
{
  type= UniformType::Vector3f;
  
  unsigned char *vector= new unsigned char[3];
  vector[0]= x;
  vector[1]= y;
  vector[2]= z;
  
  this->data= (void *)vector;
}

void Uniform::SetVector4ub(unsigned char x, unsigned char y, unsigned char z, unsigned char w)
{
  type= UniformType::Vector3f;
  
  unsigned char *vector= new unsigned char[4];
  vector[0]= x;
  vector[1]= y;
  vector[2]= z;
  vector[3]= w;
  
  this->data= (void *)vector;
}

void Uniform::SetMatrix4x4f(const float *elements)
{
  this->type= UniformType::Matrix4x4f;
  
  float *matrix= new float[16];
  memcpy(matrix, elements, sizeof(float)* 16);
  
  this->data= (void *)matrix;
}

UniformType::Enum Uniform::GetType()
{
  return type;
}

void Uniform::GetVector3f(float &x, float &y, float &z)
{
  assert(("GetVector3f: Attempted to interpret Uniform data as the wrong type.", type== UniformType::Vector3f));
  
  float *data= (float *)this->data;
  
  x= data[0];
  y= data[1];
  z= data[2];
}

void Uniform::GetVector4f(float &x, float &y, float &z, float &w)
{
  assert(("GetVector4f: Attempted to interpret Uniform data as the wrong type.", type== UniformType::Vector4f));
  
  float *data= (float *)this->data;
  
  x= data[0];
  y= data[1];
  z= data[2];
  w= data[3];
}

void Uniform::GetVector3i(int &x, int &y, int &z)
{
  assert(("GetVector3i: Attempted to interpret Uniform data as the wrong type.", type== UniformType::Vector3i));
  
  int *data= (int *)this->data;
  
  x= data[0];
  y= data[1];
  z= data[2];
}

void Uniform::GetVector4i(int &x, int &y, int &z, int &w)
{
  assert(("GetVector4i: Attempted to interpret Uniform data as the wrong type.", type== UniformType::Vector4i));
  
  int *data= (int *)this->data;
  
  x= data[0];
  y= data[1];
  z= data[2];
  w= data[3];
}

void Uniform::GetVector3ub(unsigned char &x, unsigned char &y, unsigned char &z)
{
  assert(("GetVector3ub: Attempted to interpret Uniform data as the wrong type.", type== UniformType::Vector3ub));
  
  unsigned char *data= (unsigned char *)this->data;
  
  x= data[0];
  y= data[1];
  z= data[2];
}

void Uniform::GetVector4ub(unsigned char &x, unsigned char &y, unsigned char &z, unsigned char &w)
{
  assert(("GetVector4ub: Attempted to interpret Uniform data as the wrong type.", type== UniformType::Vector4ub));
  
  unsigned char *data= (unsigned char *)this->data;
  
  x= data[0];
  y= data[1];
  z= data[2];
  w= data[3];
}

void * Uniform::GetData()
{
  return data;
}

Matrix Uniform::GetMatrix()
{
  Matrix foo= ((float *)GetData());
  
  return foo;
}

int Uniform::CreateUniform(int id, string name)
{
  assert(("CreateUniform: Attempted to create Uniform without active ShaderProgram.", ShaderProgram::GetActiveProgram()!= nullptr));
  
  return ShaderProgram::GetActiveProgram()->CreateUniform(id, name);
}

void Uniform::DeleteUniform(int id)
{
  assert(("CreateUniform: Attempted to create Uniform without active ShaderProgram.", ShaderProgram::GetActiveProgram()!= nullptr));
  
  ShaderProgram::GetActiveProgram()->DeleteUniform(id);
}

Uniform * Uniform::GetUniform(int id)
{
  return ShaderProgram::GetActiveProgram()->GetUniform(id);
}

Uniform * Uniform::GetUniform(string name)
{
  return ShaderProgram::GetActiveProgram()->GetUniform(name);
}


BlockUniform::BlockUniform()
  : Uniform()
{
  uniform_block= nullptr;
}

void BlockUniform::UpdateData()
{
  int buffer_offset;
  Buffer *uniform_buffer= Buffer::GetIndexedUniformBuffer(uniform_block->GetBlockBinding(), buffer_offset);
  
  this->data= (void *)(((char *)uniform_buffer->GetData())+ (buffer_offset+ offset));
}

void BlockUniform::SetUniformBlock(UniformBlock *uniform_block)
{
  this->uniform_block= uniform_block;
}

void BlockUniform::SetOffset(int offset)
{
  this->offset= offset;
}

void BlockUniform::GetVector3f(float &x, float &y, float &z)
{
  UpdateData();
  return Uniform::GetVector3f(x, y, z);
}

void BlockUniform::GetVector4f(float &x, float &y, float &z, float &w)
{
  UpdateData();
  return Uniform::GetVector4f(x, y, z, w);
}

void BlockUniform::GetVector3i(int &x, int &y, int &z)
{
  UpdateData();
  return Uniform::GetVector3i(x, y, z);
}

void BlockUniform::GetVector4i(int &x, int &y, int &z, int &w)
{
  UpdateData();
  return Uniform::GetVector4i(x, y, z, w);
}

void BlockUniform::GetVector3ub(unsigned char &x, unsigned char &y, unsigned char &z)
{
  UpdateData();
  return Uniform::GetVector3ub(x, y, z);
}

void BlockUniform::GetVector4ub(unsigned char &x, unsigned char &y, unsigned char &z, unsigned char &w)
{
  UpdateData();
  return Uniform::GetVector4ub(x, y, z, w);
}

Matrix BlockUniform::GetMatrix()
{
  UpdateData();
  return Uniform::GetMatrix();
}

void * BlockUniform::GetData()
{
  UpdateData();
  
  return Uniform::GetData();
}


VertexAttribute::VertexAttribute()
{
  
}

int VertexAttribute::CreateVertexAttribute(int id, string name)
{
  assert(("CreateUniform: Attempted to create Uniform without active ShaderProgram.", ShaderProgram::GetActiveProgram()!= nullptr));
  
  return ShaderProgram::GetActiveProgram()->CreateVertexAttribute(id, name);
}

void VertexAttribute::DeleteVertexAttribute(int id)
{
  assert(("CreateUniform: Attempted to create Uniform without active ShaderProgram.", ShaderProgram::GetActiveProgram()!= nullptr));
  
  ShaderProgram::GetActiveProgram()->DeleteVertexAttribute(id);
}

VertexAttribute * VertexAttribute::GetVertexAttribute(int id)
{
  return ShaderProgram::GetActiveProgram()->GetVertexAttribute(id);
}

VertexAttribute * VertexAttribute::GetVertexAttribute(string name)
{
  return ShaderProgram::GetActiveProgram()->GetVertexAttribute(name);
}


UniformBlock::UniformBlock()
{
  block_binding= -1;
  format= -1;
}

int UniformBlock::GetBlockBinding()
{
  return block_binding;
}

GLenum UniformBlock::GetFormat()
{
  return format;
}

void UniformBlock::SetID(int id)
{
  Resource::SetID(id);
  SetBlockBinding(id);
}

void UniformBlock::SetBlockBinding(int block_binding)
{
  this->block_binding= block_binding;
}

void UniformBlock::SetFormat(GLenum format)
{
  this->format= format;
}

int UniformBlock::CreateUniform(int offset, int expected_location, string name)
{
  int id= uniforms.CreateResource(expected_location);
  BlockUniform *uniform= uniforms.GetResource(id);
  uniform->SetName(name);
  uniform->SetOffset(offset);
  uniform->SetUniformBlock(this);
  
  return id;
}

void UniformBlock::DeleteUniform(int id)
{
  uniforms.DeleteResource(id);
}

Uniform * UniformBlock::GetUniform(int id)
{
  return uniforms.GetResource(id);
}

Uniform * UniformBlock::GetUniform(string name)
{
  return uniforms.GetResource(name);
}


ResourceContainer<Shader> Shader::shaders;

Shader::Shader()
{
  this->source_count= -1;
  this->sources= nullptr;
  this->lengths= nullptr;
}

void Shader::SetType(GLenum type)
{
  this->type= type;
}

//Was necessary when GLuRayS parsed shaders using GLSL Reference Compiler 
void Shader::SetSources(int source_count, const char **sources, const int *lengths)
{

}

int Shader::CreateShader(int id)
{
  return shaders.CreateResource(id);
}

void Shader::DeleteShader(int id)
{
  shaders.DeleteResource(id);

}

Shader * Shader::GetShader(int id)
{
  return shaders.GetResource(id);
}

void Shader::Free()
{

}


ResourceContainer<ShaderProgram> ShaderProgram::shader_programs= ResourceContainer<ShaderProgram>();
int ShaderProgram::active_program_id= -1;

ShaderProgram::ShaderProgram()
{
  is_complete= false;
}

void ShaderProgram::FindInputs()
{
  int maximum_name_size;
  next_glGetProgramiv(this->GetID(), GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &maximum_name_size);
  char *name_buffer= new char[maximum_name_size];
  
  int active_uniform_buffer_count;
  next_glGetProgramiv(this->GetID(), GL_ACTIVE_UNIFORM_BLOCKS, &active_uniform_buffer_count);
  for(unsigned int i= 0; i< active_uniform_buffer_count; i++)
  {
    next_glGetActiveUniformBlockName(this->GetID(), i, maximum_name_size, nullptr, name_buffer);
    string name= name_buffer;
    
    GLint block_binding;
    next_glGetActiveUniformBlockiv(this->GetID(), i, GL_UNIFORM_BLOCK_BINDING, &block_binding);
    
    UniformBlock *uniform_block= uniform_blocks.GetResource(CreateUniformBlock(i, name));
    uniform_block->SetBlockBinding(block_binding);
    
  }
  
  next_glGetProgramiv(this->GetID(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maximum_name_size);
  delete name_buffer;
  name_buffer= new char[maximum_name_size];
  
  int active_uniform_count;
  next_glGetProgramiv(this->GetID(), GL_ACTIVE_UNIFORMS, &active_uniform_count);
  for(unsigned int i= 0; i< active_uniform_count; i++)
  {
    next_glGetActiveUniformName(this->GetID(), i, maximum_name_size, nullptr, name_buffer);
    string name= name_buffer;
    
    GLint block_index;
    GLint offset;
    next_glGetActiveUniformsiv(this->GetID(), 1, &i, GL_UNIFORM_BLOCK_INDEX, &block_index);
    next_glGetActiveUniformsiv(this->GetID(), 1, &i, GL_UNIFORM_OFFSET, &offset);
    
    if(block_index< 0)
    {
      CreateUniform(i, name);
    }
    else
    {
      UniformBlock *uniform_block= uniform_blocks.GetResource(block_index);
      Uniform *uniform= uniform_block->GetUniform(uniform_block->CreateUniform(offset, i, name));
    }
  }
  
  next_glGetProgramiv(this->GetID(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maximum_name_size);
  delete name_buffer;
  name_buffer= new char[maximum_name_size];
  
  int active_attribute_count;
  next_glGetProgramiv(this->GetID(), GL_ACTIVE_ATTRIBUTES, &active_attribute_count);
  for(unsigned int i= 0; i< active_attribute_count; i++)
  {
    GLint size;
    GLenum type;
    next_glGetActiveAttrib(this->GetID(), i, maximum_name_size, nullptr, &size, &type, name_buffer);
    string name= name_buffer;
    GLint location= next_glGetAttribLocation(this->GetID(), name_buffer);
    
    CreateVertexAttribute(location, name);
  }

  delete name_buffer;

  is_complete= true;
}

bool ShaderProgram::IsComplete()
{
  return is_complete;
}

int ShaderProgram::CreateUniform(int id, string name)
{
  id= uniforms.CreateResource(id);
  uniforms.GetResource(id)->SetName(name);
  
  return id;
}

void ShaderProgram::DeleteUniform(int id)
{
  uniforms.DeleteResource(id);
}

Uniform * ShaderProgram::GetUniform(int id)
{
  if(!IsComplete())
    FindInputs();
  
  Uniform *uniform= uniforms.GetResource(id);
  
  if(uniform!= nullptr)
    return uniform;
  
  for(unsigned int i= 0; i< uniform_blocks.resources.size(); i++)
  {
    uniform= uniform_blocks.resources[i]->GetUniform(id);
    if(uniform!= nullptr)
      return uniform;
  }
  
  return nullptr;
}

Uniform * ShaderProgram::GetUniform(string name)
{
  if(!IsComplete())
    FindInputs();
  
  Uniform *uniform= uniforms.GetResource(name);
  
  if(uniform!= nullptr)
    return uniform;
  
  for(unsigned int i= 0; i< uniform_blocks.resources.size(); i++)
  {
    uniform= uniform_blocks.resources[i]->GetUniform(name);
    if(uniform!= nullptr)
      return uniform;
  }
  
  return nullptr;
}

int ShaderProgram::CreateVertexAttribute(int id, string name)
{
  id= vertex_attributes.CreateResource(id);
  vertex_attributes.GetResource(id)->SetName(name);
  
  return id;
}

void ShaderProgram::DeleteVertexAttribute(int id)
{
  vertex_attributes.DeleteResource(id);
}

VertexAttribute * ShaderProgram::GetVertexAttribute(int id)
{
  if(!IsComplete())
    FindInputs();
  
  return vertex_attributes.GetResource(id);
}

VertexAttribute * ShaderProgram::GetVertexAttribute(string name)
{
  if(!IsComplete())
    FindInputs();
  
  return vertex_attributes.GetResource(name);
}

int ShaderProgram::CreateUniformBlock(int id, string name)
{
  id= uniform_blocks.CreateResource(id);
  uniform_blocks.GetResource(id)->SetName(name);
  
  return id;
}

void ShaderProgram::DeleteUniformBlock(int id)
{
  uniform_blocks.DeleteResource(id);
}

UniformBlock * ShaderProgram::GetUniformBlock(int id)
{
  if(!IsComplete())
    FindInputs();
  
  return uniform_blocks.GetResource(id);
}

UniformBlock * ShaderProgram::GetUniformBlock(string name)
{
  if(!IsComplete())
    FindInputs();
  
  return uniform_blocks.GetResource(name);
}

void ShaderProgram::AttachShader(int id)
{
  shader_ids.push_back(id);
}

void ShaderProgram::DetachShader(int id)
{
  for(unsigned int i= 0; i< shader_ids.size(); i++)
    if(shader_ids[i]== id)
      shader_ids.erase(shader_ids.begin()+ i);
}

void ShaderProgram::Use()
{
  active_program_id= this->GetID();
}

int ShaderProgram::CreateShaderProgram(int id)
{
  return shader_programs.CreateResource(id);
}

void ShaderProgram::DeleteShaderProgram(int id)
{
  shader_programs.DeleteResource(id);
}

ShaderProgram * ShaderProgram::GetShaderProgram(int id)
{
  ShaderProgram::shader_programs.GetResource(id);
}

ShaderProgram * ShaderProgram::GetActiveProgram()
{
  return shader_programs.GetResource(active_program_id);
}


ResourceContainer<Buffer> Buffer::buffers= ResourceContainer<Buffer>();
int Buffer::bound_vertex_buffer_id= -1;
int Buffer::bound_element_buffer_id= -1;
int Buffer::bound_uniform_buffer_id= -1;
vector<RangeBinding> Buffer::uniform_buffer_bindings;

Buffer::Buffer()
{
  data= nullptr;
  size= -1;
}

Buffer::~Buffer()
{
  if(data!= nullptr)
    delete ((char *)data);
}

void Buffer::InitializeData(int size, const void *data)
{
  if(this->data!= nullptr)
   delete (char *)this->data;
  this->data= (void *)(new char[size]); 
  this->size= size;

  if(data!= nullptr)
    std::memcpy(this->data, data, size);
}

void Buffer::SetData(const void *data, int size, int offset)
{
  std::memcpy((void *)(((char *)this->data)+ offset), data, size);
}

void * Buffer::GetData()
{
  return data;
}

float Buffer::GetFloat(int offset)
{
  return ((float *)(((char *)this->data)+ offset))[0];
}

double Buffer::GetDouble(int offset)
{
  return ((double *)(((char *)this->data)+ offset))[0];
}

int Buffer::GetInt(int offset)
{
  return ((int *)(((char *)this->data)+ offset))[0];
}

unsigned int Buffer::GetUnsignedInt(int offset)
{
  return ((unsigned int *)(((char *)this->data)+ offset))[0];
}

unsigned char Buffer::GetUnsignedByte(int offset)
{
  return ((unsigned char *)(((char *)this->data)+ offset))[0];
}

void Buffer::BindAsVertexBuffer()
{
  bound_vertex_buffer_id= this->GetID();
}

void Buffer::BindAsElementBuffer()
{
  bound_element_buffer_id= this->GetID();
}

void Buffer::BindAsUniformBuffer()
{
  bound_uniform_buffer_id= this->GetID(); 
}

void Buffer::BindToUniformBufferIndex(int index, int offset)
{
  if(uniform_buffer_bindings.size()<= index)
  {
    uniform_buffer_bindings.resize(index+ 1);
  }
  
  uniform_buffer_bindings[index]= {this->GetID(), offset};
  
  BindAsUniformBuffer();
}

int Buffer::CreateBuffer(int id)
{
  return buffers.CreateResource(id);
}

void Buffer::DeleteBuffer(int id)
{
  buffers.DeleteResource(id);
}

Buffer * Buffer::GetBuffer(int id)
{
  return buffers.GetResource(id);
}

Buffer * Buffer::GetBoundVertexBuffer()
{
  return buffers.GetResource(bound_vertex_buffer_id);
}

Buffer * Buffer::GetBoundElementBuffer()
{
  return buffers.GetResource(bound_element_buffer_id);
}

Buffer * Buffer::GetBoundUniformBuffer()
{
  return buffers.GetResource(bound_uniform_buffer_id);
}

Buffer * Buffer::GetIndexedUniformBuffer(int index, int &offset)
{
  RangeBinding range_binding= uniform_buffer_bindings[index];
  offset= range_binding.offset;
  
  return buffers.GetResource(uniform_buffer_bindings[index].buffer_id);
}


VertexAttributeArray::VertexAttributeArray()
{
  this->size= 0;
  this->type= 0;
  this->stride= 0;
  this->offset= 0;
}

void VertexAttributeArray::SetValues(int size, int type, int stride, int offset)
{
  this->size= size;
  this->type= type;
  this->stride= stride;
  if(stride== 0)
  {
    if(type== GL_FLOAT)
      this->stride= size* sizeof(GLfloat);
    else if(type== GL_INT)
      this->stride= size* sizeof(GLint);
    else if(type== GL_UNSIGNED_BYTE)
      this->stride= size* sizeof(GLubyte);
  }
  this->offset= offset;
  
  this->Invalidate();
}

void VertexAttributeArray::SetSourceBufferID(int source_buffer_id)
{
  this->source_buffer_id= source_buffer_id;
  
  this->Invalidate();
}

void VertexAttributeArray::Enable()
{
  this->enabled= true;
}

void VertexAttributeArray::Disable()
{
  this->enabled= false;
}

int VertexAttributeArray::GetSize()
{
  return size;
}

int VertexAttributeArray::GetType()
{
  return type;
}

int VertexAttributeArray::GetStride()
{
  return stride;
}

int VertexAttributeArray::GetOffset()
{
  return offset;
}

int VertexAttributeArray::GetSourceBufferID()
{
  return source_buffer_id;
}

void VertexAttributeArray::GetVector3f(int index, float &v0, float &v1, float &v2)
{
  assert(("VertexAttributeArray::GetVector3f(): Mismatched types.", this->type== GL_FLOAT));
  
  Buffer *buffer= Buffer::GetBuffer(source_buffer_id);
  
  v0= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 0);
  v1= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 1);
  v2= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 2);
}

void VertexAttributeArray::GetVector4f(int index, float &v0, float &v1, float &v2, float &v3)
{
  assert(("VertexAttributeArray::GetVector4f(): Mismatched types.", this->type== GL_FLOAT));
  
  Buffer *buffer= Buffer::GetBuffer(source_buffer_id);
  
  v0= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 0);
  v1= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 1);
  v2= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 2);
  v3= buffer->GetFloat(index* stride+ offset+ sizeof(float)* 3);
}

void VertexAttributeArray::GetVector3i(int index, int &v0, int &v1, int &v2)
{
  assert(("VertexAttributeArray::GetVector3i(): Mismatched types.", this->type== GL_INT));
  
  Buffer *buffer= Buffer::GetBuffer(source_buffer_id);
  
  v0= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 0);
  v1= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 1);
  v2= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 2);
}

void VertexAttributeArray::GetVector4i(int index, int &v0, int &v1, int &v2, int &v3)
{
  assert(("VertexAttributeArray::GetVector4i(): Mismatched types.", this->type== GL_INT));
  
  Buffer *buffer= Buffer::GetBuffer(source_buffer_id);
  
  v0= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 0);
  v1= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 1);
  v2= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 2);
  v3= buffer->GetFloat(index* stride+ offset+ sizeof(int)* 3);
}

void VertexAttributeArray::GetVector3ub(int index, unsigned char &v0, unsigned char &v1, unsigned char &v2)
{
  assert(("VertexAttributeArray::GetVector3ub(): Mismatched types.", this->type== GL_UNSIGNED_BYTE));
  
  Buffer *buffer= Buffer::GetBuffer(source_buffer_id);
  
  v0= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 0);
  v1= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 1);
  v2= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 2);
}

void VertexAttributeArray::GetVector4ub(int index, unsigned char &v0, unsigned char &v1, unsigned char &v2, unsigned char &v3)
{
  assert(("VertexAttributeArray::GetVector4ub(): Mismatched types.", this->type== GL_UNSIGNED_BYTE));
  
  Buffer *buffer= Buffer::GetBuffer(source_buffer_id);
  
  v0= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 0);
  v1= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 1);
  v2= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 2);
  v3= buffer->GetFloat(index* stride+ offset+ sizeof(unsigned char)* 3);
}

int VertexAttributeArray::CreateVertexAttributeArray(int id)
{
  return VertexArrayObject::GetBoundVertexArrayObject()->CreateVertexAttributeArray(id);
}

void VertexAttributeArray::DeleteVertexAttributeArray(int id)
{
  VertexArrayObject::GetBoundVertexArrayObject()->DeleteVertexAttributeArray(id);
}

VertexAttributeArray * VertexAttributeArray::GetVertexAttributeArray(int id)
{
  return VertexArrayObject::GetBoundVertexArrayObject()->GetVertexAttributeArray(id);
}


ResourceContainer<VertexArrayObject> VertexArrayObject::vaos= ResourceContainer<VertexArrayObject>();
int VertexArrayObject::bound_vao_id= -1;

VertexArrayObject::VertexArrayObject()
{
  
}

int VertexArrayObject::CreateVertexAttributeArray(int id)
{
  return attributes.CreateResource(id);
}

void VertexArrayObject::DeleteVertexAttributeArray(int id)
{
  attributes.DeleteResource(id);
}

VertexAttributeArray * VertexArrayObject::GetVertexAttributeArray(int id)
{
  return attributes.GetResource(id);
}

int VertexArrayObject::CreateVertexArrayObject(int id)
{
  return vaos.CreateResource(id);
}

void VertexArrayObject::DeleteVertexArrayObject(int id)
{
  vaos.DeleteResource(id);
}


VertexArrayObject * VertexArrayObject::GetVertexArrayObject(int id)
{
  return vaos.GetResource(id);
}

void VertexArrayObject::Validate()
{
  for(unsigned int i= 0; i< attributes.resources.size(); i++)
    attributes.resources[i]->Validate();
  
  Mutable::Validate();
}

bool VertexArrayObject::IsValid()
{
  for(unsigned int i= 0; i< attributes.resources.size(); i++)
    if(!attributes.resources[i]->IsValid())
      Invalidate();
  
  return Mutable::IsValid();
}

void VertexArrayObject::Bind()
{
  bound_vao_id= this->GetID();
}

VertexArrayObject * VertexArrayObject::GetBoundVertexArrayObject()
{
  return vaos.GetResource(bound_vao_id);
}

