#include "GLuRayS_State.h"


template<typename T>
class DataSource
{
public:
  virtual T GetData()= 0;
  virtual bool IsEmpty()= 0;
};
typedef DataSource<Matrix> DS_Matrix;

template<typename T>
class ArrayDataSource : public DataSource<T>
{
  int element_offset;
  
protected:
  ArrayDataSource()
  {
    element_offset= 0;
  }
  
  int GetElementOffset()
  {
    return element_offset++;
  }
  
public:
  void Reset(int element_offset= 0)
  {
    this->element_offset= element_offset;
  }
  
  virtual T GetDataAt(int element_offset)= 0;
};
typedef ArrayDataSource<Vector3f> ADS_Vector3f;


template<typename T>
class ResourceConnector
{
  string name;
  int id;
  
  T *resource;
  
protected:
  T * GetResource()
  {
    return resource;
  }
  
  void SetResource(Resource *resource)
  {
    this->resource= dynamic_cast<T *>(resource);
  }
  
public:
  ResourceConnector(string name)
  {
    this->name= name;
    this->id= -1;
    
    this->resource= nullptr;
  }
  
  ResourceConnector(int id)
  {
    this->name= "";
    this->id= id;
    
    this->resource= nullptr;
  }
  
  string GetName() { return name; }
  int GetID() { return id; }
  
  virtual bool Connect()
  {
    return false; 
  }
  
  bool IsConnected()
  {
     return resource!= nullptr;
  }
  
  bool DoesMatch()
  {
    Connect();
    bool is_connected= IsConnected();
    resource= nullptr;
    
    return is_connected;
  }
};


template<typename T>
T GetUniformData(Uniform *resource);

template<typename T>
T GetVertexAttributeData(VertexAttributeArray *resource, int offset);

template<typename T>
class UniformDataSource : public DataSource<T>, public ResourceConnector<Uniform>
{
public:
  UniformDataSource(string name) : ResourceConnector<Uniform>(name) { }
  UniformDataSource(int id) : ResourceConnector<Uniform>(id) { }
  
  bool IsEmpty()
  {
      if(IsConnected())
        return false;
    
      return !Connect();
  }
  
  bool Connect()
  {
    if(GetID()< 0 && GetName()== "")
      return false;
    
    if(GetID()< 0)
      SetResource(Uniform::GetUniform(GetName()));
    else
      SetResource(Uniform::GetUniform(GetID()));
    
    return IsConnected();
  }
  
  T GetData()
  {
    return GetUniformData<T>(GetResource());
  }
};

template<typename T>
class VertexAttributeDataSource : public ArrayDataSource<T>, public ResourceConnector<VertexAttributeArray>
{
public:
  VertexAttributeDataSource(string name) : ResourceConnector<VertexAttributeArray>(name) { }
  VertexAttributeDataSource(int id) : ResourceConnector<VertexAttributeArray>(id) { }
  
  bool IsEmpty()
  {
      if(IsConnected())
        return false;
    
      return !Connect();
  }
  
  bool Connect()
  { 
    if(GetID()< 0 && GetName()== "")
      return false;

    int id= GetID();
    if(GetID()< 0)
    {
      VertexAttribute *vertex_attribute= VertexAttribute::GetVertexAttribute(GetName());
      
      if(vertex_attribute!= nullptr)
        id= vertex_attribute->GetID();
    }
    
    if(id>= 0)
      SetResource(VertexAttributeArray::GetVertexAttributeArray(id));
    
    return IsConnected();
  }
  
  T GetData()
  {
    return GetVertexAttributeData<T>(GetResource(), this->GetElementOffset());
  }
  
  T GetDataAt(int element_offset)
  {
    return GetVertexAttributeData<T>(GetResource(), element_offset);
  }
};

struct DrawCall
{
  bool use_elements;
  
  union
  {
    struct 
    {
      int mode;
      int first;
      int count;
    }arrays;
    
    struct
    {
      int mode;
      int count;
      int type;
      int offset;
      
      int start;
      int end;
    }elements;
  };
  
  static DrawCall GetArraysDrawCall(int mode, int first, int count);
  static DrawCall GetElementsDrawCall(int mode, int count, int type, int offset, int start= -1, int end= -1);
};


class RenderModel;
class RenderModelInstantiator
{
public:
  RenderModelInstantiator();
  
  virtual RenderModel * CreateInstance()= 0;
  virtual float ScoreFit()= 0;
};

class RenderModel
{
  static vector<RenderModelInstantiator *> instantiators;
  static vector<RenderModel *> render_model_instances;

  static void DeleteInvalidRenderModels();
  
protected:
  
  static vector<RenderModel *> drawn_render_models;
  
  int shader_id;
  int vao_id;
  int element_buffer_id;
  
  int display_list_id;

  int size;

  void DisableElementBuffer();
  virtual bool IsDisplayListInvalid()= 0;
  
  static bool DoesRenderModelInstanceExist(int shader_id, int vao_id, int element_buffer_id);
  static void GetCurrentBindings(int &shader_id, int &vao_id, int &element_buffer_id);
  static int GetAvailableDisplayListID();
  
  static RenderModel * CreateRenderModelInstance();

public:
  RenderModel();
  
  virtual void Draw(DrawCall draw_call)= 0;
  virtual float * GetProjectionMatrix()= 0;
  
  int GetSize();
  
  static RenderModel * GetRenderModelInstance(bool use_element_buffer);
  static RenderModel * FindRenderModelInstance(int shader_id, int vao_id, int element_buffer_id);
  static RenderModel * GetLargestDrawnRenderModel();
  static void AddInstantiator(RenderModelInstantiator *instantiator);
};

class BasicRenderModel : public RenderModel
{
  ADS_Vector3f *positions;
  ADS_Vector3f *normals;
  DS_Matrix *view_matrix;
  DS_Matrix *projection_matrix;
  DS_Matrix *display_matrix;

protected:

  bool IsDisplayListInvalid();
  
public:
  
  BasicRenderModel(ADS_Vector3f *positions, 
                  ADS_Vector3f *normals, 
                  DS_Matrix *view_matrix, 
                  DS_Matrix *projection_matrix, 
                  DS_Matrix *display_matrix);
  ~BasicRenderModel();
  
  void Draw(DrawCall draw_call);
  float * GetProjectionMatrix();
};


class BasicRenderModelInstantiator : public RenderModelInstantiator
{
  VertexAttributeDataSource<Vector3f> *positions;
  VertexAttributeDataSource<Vector3f> *normals;
  UniformDataSource<Matrix> *view_matrix;
  UniformDataSource<Matrix> *projection_matrix;
  UniformDataSource<Matrix> *display_matrix;
  
public:
  BasicRenderModelInstantiator(string vertex_attribute_name, 
                               string normal_attribute_name, 
                               string view_matrix_name, 
                               string projection_matrix_name, 
                               string display_matrix_name);
  ~BasicRenderModelInstantiator();
  
  RenderModel * CreateInstance();
  float ScoreFit();
};
