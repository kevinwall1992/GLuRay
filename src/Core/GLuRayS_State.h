#ifndef __GLURAYS_STATE__
#define __GLURAYS_STATE__

#include <GL/gl.h>

#include <string>
#include <vector>
#include <utility>
#include <cstring>

using std::string;
using std::vector;
using std::pair;
using std::memcpy;


struct Matrix
{
  float m[16];
  
  void Set(float *m_);
  Matrix(float *m_);
};

struct Vector3f
{
  float v[3];
};


class Resource
{
  int id;
  
public:
  Resource(int id);
  Resource();
  
  virtual void SetID(int id);
  int GetID();
};

const int starting_id= 100;
template<class T>
class ResourceContainer
{
  int GetLowestAvailableID()
  {
    int lowest_available_id= starting_id;
    
    for(unsigned int i= 0; i< resources.size(); i++)
    {
      if(resources[i]->GetID()== lowest_available_id)
      {
        lowest_available_id++;
        i= 0;
      }
    }
    
    return lowest_available_id;
  }
  
public:
  vector<T *> resources;
  
  int CreateResource(int id= -1)
  {
    T *resource= new T();

    resource->SetID(id> -1 ? id : GetLowestAvailableID());
    resources.push_back(resource);
    
    return resource->GetID();
  }
  
  T * GetResource(int id)
  {
    for(unsigned int i= 0; i< resources.size(); i++)
      if(resources[i]->GetID()== id)
        return resources[i];

    return nullptr;
  }
  
  T * GetResource(string name)
  {
    for(unsigned int i= 0; i< resources.size(); i++)
      if(resources[i]->GetName()== name)
        return resources[i];

    return nullptr;
  }
  
  void DeleteResource(int id)
  {
    for(unsigned int i= 0; i< resources.size(); i++)
    {
      if(resources[i]->GetID()== id)
      {
        delete resources[i];
        resources.erase(resources.begin()+ i);
        return;
      }
    }
  }
};


class Mutable
{
  bool is_valid;
  
public:
  Mutable();
  
  void Invalidate();
  virtual void Validate();
  
  virtual bool IsValid();
};


class MutableResource : public Resource, public Mutable
{
public:
  void SetID(int id);

};


class ShaderInput : public MutableResource
{
  string name;
  
public:
  ShaderInput(string name);
  ShaderInput();
  
  void SetName(string name);
  
  string GetName();
};


struct UniformType
{
  enum Enum 
  {
    NoneType, Vector3f, Vector4f, Vector3i, Vector4i, Vector3ub, Vector4ub, Matrix3x3f, Matrix4x4f
  };
};

class Uniform : public ShaderInput
{
protected:
  
  void *data;
  UniformType::Enum type;
  
  Uniform();
  ~Uniform();
  
public:
  
  UniformType::Enum GetType();
  
  virtual void SetVector3f(float x, float y, float z);
  virtual void SetVector4f(float x, float y, float z, float w);
  virtual void SetVector3i(int x, int y, int z);
  virtual void SetVector4i(int x, int y, int z, int w);
  virtual void SetVector3ub(unsigned char x, unsigned char y, unsigned char z);
  virtual void SetVector4ub(unsigned char x, unsigned char y, unsigned char z, unsigned char w);
  virtual void SetMatrix4x4f(const float *elements);
  
  virtual void GetVector3f(float &x, float &y, float &z);
  virtual void GetVector4f(float &x, float &y, float &z, float &w);
  virtual void GetVector3i(int &x, int &y, int &z);
  virtual void GetVector4i(int &x, int &y, int &z, int &w);
  virtual void GetVector3ub(unsigned char &x, unsigned char &y, unsigned char &z);
  virtual void GetVector4ub(unsigned char &x, unsigned char &y, unsigned char &z, unsigned char &w);
  virtual Matrix GetMatrix();
  virtual void * GetData();
  
  static int CreateUniform(int expected_location= -1, string name= "");
  static void DeleteUniform(int id);
  static Uniform * GetUniform(int id);
  static Uniform * GetUniform(string name);
  
  
  friend class ResourceContainer<Uniform>;
};

class UniformBlock;
class BlockUniform : public Uniform
{
  
protected:
  
  UniformBlock *uniform_block;
  int offset;
  
  BlockUniform();
  
  void UpdateData();
  
public:
  void SetUniformBlock(UniformBlock *uniform_block);
  void SetOffset(int offset);
  
  void GetVector3f(float &x, float &y, float &z);
  void GetVector4f(float &x, float &y, float &z, float &w);
  void GetVector3i(int &x, int &y, int &z);
  void GetVector4i(int &x, int &y, int &z, int &w);
  void GetVector3ub(unsigned char &x, unsigned char &y, unsigned char &z);
  void GetVector4ub(unsigned char &x, unsigned char &y, unsigned char &z, unsigned char &w);
  Matrix GetMatrix();
  void * GetData();
  
  
  friend class ResourceContainer<BlockUniform>;
};

class VertexAttribute : public ShaderInput
{
  VertexAttribute();
  
public:
  
  static int CreateVertexAttribute(int expected_location= -1, string name= "");
  static void DeleteVertexAttribute(int id);
  static VertexAttribute * GetVertexAttribute(int id);
  static VertexAttribute * GetVertexAttribute(string name);
 
  friend class ResourceContainer<VertexAttribute>;
};

class UniformBlock : public ShaderInput
{
  ResourceContainer<BlockUniform> uniforms;  
  int block_binding;
  GLenum format;
  
  UniformBlock();
  
public:
  int GetBlockBinding();
  GLenum GetFormat();
  
  void SetID(int id);
  void SetBlockBinding(int index);
  void SetFormat(GLenum format);
  
  int CreateUniform(int offset, int expected_location= -1, string name= "");
  void DeleteUniform(int id);
  Uniform * GetUniform(int id);
  Uniform * GetUniform(string name);
  
  friend class ResourceContainer<UniformBlock>;
};

class Shader : public Resource
{
  static ResourceContainer<Shader> shaders;

  int source_count;
  char **sources;
  int *lengths;
  GLenum type;
  
  Shader();

public:
  
  void SetType(GLenum type);
  void SetSources(int source_count, const char **sources, const int *lengths);

  void Free();
  
  static int CreateShader(int id= -1);
  static void DeleteShader(int id);
  
  static Shader * GetShader(int id);
  
  friend class ResourceContainer<Shader>;
};


class ShaderProgram : public MutableResource
{
  static ResourceContainer<ShaderProgram> shader_programs;
  static int active_program_id;
  
  ResourceContainer<Uniform> uniforms;
  ResourceContainer<VertexAttribute> vertex_attributes;
  ResourceContainer<UniformBlock> uniform_blocks;
  
  vector<int> shader_ids;

  bool is_complete;
  
  ShaderProgram();
  
  void FindInputs();
  bool IsComplete();
  
public:

  int CreateUniform(int id= -1, string name= "");
  void DeleteUniform(int id);
  Uniform * GetUniform(int id);
  Uniform * GetUniform(string name);
  
  int CreateVertexAttribute(int id= -1, string name= "");
  void DeleteVertexAttribute(int id);
  VertexAttribute * GetVertexAttribute(int id);
  VertexAttribute * GetVertexAttribute(string name);
  
  int CreateUniformBlock(int id= -1, string name= "");
  void DeleteUniformBlock(int id);
  UniformBlock * GetUniformBlock(int id);
  UniformBlock * GetUniformBlock(string name);
  
  void AttachShader(int id);
  void DetachShader(int id);
  
  vector<int> GetReservedAttributeLocations();
  vector<int> GetReservedUniformLocations();
  
  void Use();
  
  static int CreateShaderProgram(int id= -1);
  static void DeleteShaderProgram(int id);
  static ShaderProgram * GetShaderProgram(int id);
  static ShaderProgram * GetActiveProgram();
  
  friend class ResourceContainer<ShaderProgram>;
};

struct RangeBinding
{
  int buffer_id;
  int offset;
};

class Buffer : public MutableResource
{
  static ResourceContainer<Buffer> buffers;
  static int bound_vertex_buffer_id;
  static int bound_element_buffer_id;
  static int bound_uniform_buffer_id;
  
  static vector<RangeBinding> uniform_buffer_bindings;
  
  void *data;
  int size;
  
  Buffer();
  ~Buffer();  

public:
  
  void InitializeData(int size, const void *data= nullptr);
  void SetData(const void *data, int size, int offset= 0);
  void *GetData();
  
  float GetFloat(int offset);
  double GetDouble(int offset);
  int GetInt(int offset);
  unsigned int GetUnsignedInt(int offset);
  unsigned short GetUnsignedShort(int offset);
  unsigned char GetUnsignedByte(int offset);
  
  void BindAsVertexBuffer();
  void BindAsElementBuffer();
  void BindAsUniformBuffer();
  void BindToUniformBufferIndex(int index, int offset= 0);
  
  static int CreateBuffer(int id= -1);
  static void DeleteBuffer(int id);
  static Buffer * GetBuffer(int id);
  static Buffer * GetBoundVertexBuffer();
  static Buffer * GetBoundElementBuffer();
  static Buffer * GetBoundUniformBuffer();
  static Buffer * GetIndexedUniformBuffer(int index, int &offset);
  
  friend class ResourceContainer<Buffer>;
};

class VertexAttributeArray : public MutableResource
{
  int source_buffer_id;
  
  int size;
  int type;
  int stride;
  int offset;
  
  bool enabled;
  
  VertexAttributeArray();
  
public:
  
  void SetValues(int size, int type, int stride, int offset);
  void SetSourceBufferID(int source_buffer_id);
  
  void Enable();
  void Disable();
  
  int GetSize();
  int GetType();
  int GetStride();
  int GetOffset();
  int GetSourceBufferID();
  
  void GetVector3f(int index, float &v0, float &v1, float &v2);
  void GetVector4f(int index, float &v0, float &v1, float &v2, float &v3);
  void GetVector3i(int index, int &v0, int &v1, int &v2);
  void GetVector4i(int index, int &v0, int &v1, int &v2, int &v3);
  void GetVector3ub(int index, unsigned char &v0, unsigned char &v1, unsigned char &v2);
  void GetVector4ub(int index, unsigned char &v0, unsigned char &v1, unsigned char &v2, unsigned char &v3);
  
  static int CreateVertexAttributeArray(int id);
  static void DeleteVertexAttributeArray(int id);
  static VertexAttributeArray * GetVertexAttributeArray(int id);
  
  
  friend class ResourceContainer<VertexAttributeArray>;
};


class VertexArrayObject : public MutableResource
{
  static ResourceContainer<VertexArrayObject> vaos;
  static int bound_vao_id;
  
  ResourceContainer<VertexAttributeArray> attributes;
  
  VertexArrayObject();
  
public:
  
  int CreateVertexAttributeArray(int id);
  void DeleteVertexAttributeArray(int id);
  VertexAttributeArray * GetVertexAttributeArray(int id);
  
  void Bind();
  
  void Validate();
  bool IsValid();
  
  static int CreateVertexArrayObject(int id= -1);
  static void DeleteVertexArrayObject(int id);
  static VertexArrayObject * GetVertexArrayObject(int id);
  static VertexArrayObject * GetBoundVertexArrayObject();
  
  
  friend class ResourceContainer<VertexArrayObject>;
};

#endif


