#include "GLuRayS_Rendering.h"

#include <Engine/Display/GLXImageDisplay.h>
#include "gluray.h"

#include <cstring>
#include <assert.h>


template<typename T>
T GetUniformData(Uniform *resource)
{
  return T();
}

template<>
Matrix GetUniformData<Matrix>(Uniform *resource)
{
  return resource->GetMatrix();
}

template<typename T>
T GetVertexAttributeData(VertexAttributeArray *resource, int offset)
{
  return T();
}

template<>
Vector3f GetVertexAttributeData<Vector3f>(VertexAttributeArray *resource, int offset)
{
  Vector3f vector;
  resource->GetVector3f(offset, vector.v[0], vector.v[1], vector.v[2]);
  
  return vector;
}


DrawCall DrawCall::GetArraysDrawCall(int mode, int first, int count)
{
  DrawCall draw_call;
  
  draw_call.arrays.mode= mode;
  draw_call.arrays.first= first;
  draw_call.arrays.count= count;
  
  draw_call.use_elements= false;
  
  return draw_call;
}

DrawCall DrawCall::GetElementsDrawCall(int mode, int count, int type, int offset, int start, int end)
{
  DrawCall draw_call;
  
  draw_call.elements.mode= mode;
  draw_call.elements.count= count;
  draw_call.elements.type= type;
  draw_call.elements.offset= offset;
  draw_call.elements.start= start;
  draw_call.elements.end= end;
  
  draw_call.use_elements= true;
  
  return draw_call;
}
  

vector<RenderModelInstantiator *> RenderModel::instantiators;
vector<RenderModel *> RenderModel::render_model_instances;

vector<RenderModel *> RenderModel::drawn_render_models;
 
void RenderModel::DeleteInvalidRenderModels()
{
  for(unsigned int i= 0; i< RenderModel::render_model_instances.size(); i++)
  {
    if(!render_model_instances[i]->IsDisplayListInvalid())
      continue;

    for(unsigned int j= 0; j< drawn_render_models.size(); j++)
      if(drawn_render_models[j]== render_model_instances[i])
      {
        drawn_render_models.erase(drawn_render_models.begin()+ j);
        j--;
      }

    delete render_model_instances[i];
    render_model_instances.erase(render_model_instances.begin()+ i);
    i--;
  }
}

RenderModel::RenderModel()
{ 
  GetCurrentBindings(shader_id, vao_id, element_buffer_id);
  display_list_id= -1;

  size= 0;
  
  render_model_instances.push_back(this);
}

int RenderModel::GetSize()
{
  return size;
}

RenderModel * RenderModel::FindRenderModelInstance(int shader_id, int vao_id, int element_buffer_id)
{
  DeleteInvalidRenderModels();

  for(unsigned int i= 0; i< RenderModel::render_model_instances.size(); i++)
  {
    RenderModel *render_model= RenderModel::render_model_instances[i];
    
    if(render_model->shader_id== shader_id && 
       render_model->vao_id== vao_id && 
       render_model->element_buffer_id== element_buffer_id)
      return render_model;
  }
  
  return nullptr;
}

RenderModel * RenderModel::GetLargestDrawnRenderModel()
{
  if(RenderModel::drawn_render_models.size()== 0)
    return nullptr;

  RenderModel *largest_render_model= RenderModel::drawn_render_models[0];

  for(unsigned int i= 1; i< RenderModel::drawn_render_models.size(); i++)
    if(RenderModel::drawn_render_models[i]->GetSize()> largest_render_model->GetSize())
      largest_render_model= RenderModel::drawn_render_models[i];

  drawn_render_models.clear();

  return largest_render_model;
}

void RenderModel::AddInstantiator(RenderModelInstantiator *instantiator)
{
  instantiators.push_back(instantiator);
}

bool RenderModel::DoesRenderModelInstanceExist(int shader_id, int vao_id, int element_buffer_id)
{
  return FindRenderModelInstance(shader_id, vao_id, element_buffer_id)!= nullptr;
}

RenderModel * RenderModel::CreateRenderModelInstance()
{
  assert(("No instantiators!", instantiators.size()> 0));
  
  float best_index= 0;
  float best_score= instantiators[best_index]->ScoreFit();
  
  for(unsigned int i= 1; i< instantiators.size(); i++)
  {
    float score= instantiators[i]->ScoreFit();
    if(score> best_score)
    {
      best_index= i;
      best_score= score;
    }
  }
  
  if(best_score== 0)
    return nullptr;
  else
    return instantiators[best_index]->CreateInstance();
}

void RenderModel::GetCurrentBindings(int &shader_id, int &vao_id, int &element_buffer_id)
{
  shader_id= ShaderProgram::GetActiveProgram()->GetID();
  vao_id= VertexArrayObject::GetBoundVertexArrayObject()->GetID();
  
  Buffer *element_buffer= Buffer::GetBoundElementBuffer();
  element_buffer_id= element_buffer!= nullptr ? element_buffer->GetID() : -1;
}

int RenderModel::GetAvailableDisplayListID()
{
  static int next_id= 5;
  
  return next_id++;
}

RenderModel * RenderModel::GetRenderModelInstance(bool use_element_buffer)
{
  int shader_id, vao_id, element_buffer_id;
  GetCurrentBindings(shader_id, vao_id, element_buffer_id);
  if(!use_element_buffer)
    element_buffer_id= -1;
  
  RenderModel *render_model= RenderModel::FindRenderModelInstance(shader_id, vao_id, element_buffer_id);
  if(render_model== nullptr)
    render_model= CreateRenderModelInstance();
  
  return render_model;
}
 
 
bool BasicRenderModel::IsDisplayListInvalid()
{
  VertexArrayObject *vao= VertexArrayObject::GetVertexArrayObject(this->vao_id);
  ShaderProgram *shader_program= ShaderProgram::GetShaderProgram(this->shader_id);
  Buffer *element_buffer= element_buffer_id< 0 ? nullptr : Buffer::GetBuffer(this->element_buffer_id);

  if((vao != nullptr && !vao->IsValid()) || 
    (shader_program != nullptr && !shader_program->IsValid()) || 
    (element_buffer != nullptr && !element_buffer->IsValid()))
    return true;
  else
    return false;
}

BasicRenderModel::BasicRenderModel(ADS_Vector3f *positions, ADS_Vector3f *normals, DS_Matrix *view_matrix, DS_Matrix *projection_matrix, DS_Matrix *display_matrix)
{
  this->positions= positions;
  this->normals= normals;
  this->view_matrix= view_matrix;
  this->projection_matrix= projection_matrix;
  this->display_matrix= display_matrix;
}

BasicRenderModel::~BasicRenderModel()
{
  if(display_list_id>= 0)
    gr_deleteLists(display_list_id, 1);

  delete positions;
  delete normals;
  delete view_matrix;
  delete projection_matrix;
  delete display_matrix;
}

void BasicRenderModel::Draw(DrawCall draw_call)
{
  if(!(draw_call.arrays.mode == GL_TRIANGLES || draw_call.arrays.mode == GL_QUADS))
    return;
        
  gr_init();
  gr_setBackgroundColor(1.0f, 1.0f, 1.0f, 1.0f);
  gr_matrixMode(GL_MODELVIEW);
  gr_loadMatrixf(view_matrix->GetData().m);
  

  if(display_list_id< 0)
  {
    display_list_id= GetAvailableDisplayListID();
    gr_newList(display_list_id, 4864);
    
    if(!draw_call.use_elements)
    {
      int mode= draw_call.arrays.mode;
      int first= draw_call.arrays.first;
      int count= draw_call.arrays.count;
      
      gr_beginPrimitive(mode);
      
      positions->Reset(first);
      for(int i= first; i< count; i++)
      {
        Vector3f vector= positions->GetData();
        
        gr_addVertex(vector.v[0], vector.v[1], vector.v[2]);
      }
      gr_endPrimitive();

      this->size= count- first;
    }
    else
    {
      int mode= draw_call.elements.mode;
      int count= draw_call.elements.count;
      int type= draw_call.elements.type;
      int offset= draw_call.elements.offset;
      
      Buffer *element_buffer= Buffer::GetBuffer(element_buffer_id);

      gr_beginPrimitive(mode);
      
      positions->Reset(offset);
      for(int i= 0; i< count; i++)
      {
        int index;
        
        switch(type)
        {
        case GL_UNSIGNED_INT: index= element_buffer->GetUnsignedInt(offset+ i* sizeof(GLuint)); break;
        case GL_UNSIGNED_SHORT: index= element_buffer->GetUnsignedShort(i); break;
        case GL_UNSIGNED_BYTE: index= element_buffer->GetUnsignedByte(i); break;
        default: assert(("Draw(): Element buffer invalid type!", false)); break;
        }
        
        Vector3f vector= positions->GetDataAt(index);
      
        gr_addVertex(vector.v[0], vector.v[1], vector.v[2]);

        if(!normals->IsEmpty())
        {
          Vector3f vector= normals->GetDataAt(index);
  
          gr_normal(vector.v[0], vector.v[1], vector.v[2]);
        }
      }
      gr_endPrimitive();
      this->size= count;
      
      element_buffer->Validate();
    }

    gr_endList();
    
    VertexArrayObject::GetVertexArrayObject(this->vao_id)->Validate();
    ShaderProgram::GetShaderProgram(this->shader_id)->Validate();
  }
  else
    gr_callList(display_list_id);
  
  drawn_render_models.push_back(this);
}

float * GetTransposeMatrix(float *matrix)
{
  float *transpose_matrix= new float[16];
  for(int i= 0; i< 4; i++)
    for(int j= 0; j< 4; j++)
      transpose_matrix[i* 4+ j]= matrix[j* 4+ i];
    
  return transpose_matrix;
}

float * GetInverseMatrix(float *matrix)
{
  float inverse_rotation[9]= { matrix[0], matrix[4], matrix[8], 
                               matrix[1], matrix[5], matrix[9], 
                               matrix[2], matrix[6], matrix[10] };
                                 
  float translation[3]= { matrix[3], matrix[7], matrix[11] };
  float inverse_translation[3];
  for(int i= 0; i< 3; i++)
  {
    float total= 0;
    for(int j= 0; j< 3; j++)
      total-= inverse_rotation[j+ i* 3]* translation[j];
    
    inverse_translation[i]= total;
  }
  
  float inverse_matrix[16]= { inverse_rotation[0], inverse_rotation[1], inverse_rotation[2], inverse_translation[0], 
                              inverse_rotation[3], inverse_rotation[4], inverse_rotation[5], inverse_translation[1],
                              inverse_rotation[6], inverse_rotation[7], inverse_rotation[8], inverse_translation[2],
                              0, 0, 0, 1 };
  float *inverse_matrix_= new float[16];
  memcpy(inverse_matrix_, inverse_matrix, sizeof(float)* 16);
                              
  return inverse_matrix_;
}

float * MatrixMultiply(float *a, float *b)
{
  float *product= new float[16];
  
  for(int i= 0; i< 4; i++)
  {
    for(int j= 0; j< 4; j++)
      product[i+ j* 4]= a[0+ i* 4]* b[j+ 0* 4]+ 
                        a[1+ i* 4]* b[j+ 1* 4]+ 
                        a[2+ i* 4]* b[j+ 2* 4]+ 
                        a[3+ i* 4]* b[j+ 3* 4];
  }
  
  return product;
}

float * BasicRenderModel::GetProjectionMatrix()
{
  if(!projection_matrix->IsEmpty())
  {
    float *projection_matrix= new float[16];
    memcpy(projection_matrix, this->projection_matrix->GetData().m, sizeof(float)* 16);
    float *elements= projection_matrix;
    
    return elements;
  }
  
  float *inverse_view_matrix= GetInverseMatrix((float *)this->view_matrix->GetData().m);
  float *projection_matrix= MatrixMultiply(inverse_view_matrix, (float *)this->display_matrix->GetData().m);
  
  delete inverse_view_matrix;
  return projection_matrix;
}


RenderModelInstantiator::RenderModelInstantiator()
{
  RenderModel::AddInstantiator(this);
}


template<typename T>
T *CopyDataSource(T *original)
{
  T *copy= new T(original->GetName());
  copy->IsEmpty();
  return copy;
}

BasicRenderModelInstantiator *paraview_instantiator= new BasicRenderModelInstantiator("vertexMC", "normalMC", "MCVCMatrix", "", "MCDCMatrix");
BasicRenderModelInstantiator *superbible_instantiator= new BasicRenderModelInstantiator("position", "normal", "mv_matrix", "proj_matrix", "");

BasicRenderModelInstantiator::BasicRenderModelInstantiator(string vertex_attribute_name, 
                                                          string normal_attribute_name, 
                                                          string view_matrix_name, 
                                                          string projection_matrix_name, 
                                                          string display_matrix_name)
{
  this->positions= new VertexAttributeDataSource<Vector3f>(vertex_attribute_name);
  this->normals= new VertexAttributeDataSource<Vector3f>(normal_attribute_name);
  this->view_matrix= new UniformDataSource<Matrix>(view_matrix_name);
  this->projection_matrix= new UniformDataSource<Matrix>(projection_matrix_name);
  this->display_matrix= new UniformDataSource<Matrix>(display_matrix_name);
}
  
RenderModel * BasicRenderModelInstantiator::CreateInstance()
{
  if(ScoreFit()<= 0)
    return nullptr;
  
  return new BasicRenderModel(dynamic_cast<ADS_Vector3f *>(CopyDataSource(positions)), 
                              dynamic_cast<ADS_Vector3f *>(CopyDataSource(normals)), 
                              dynamic_cast<DS_Matrix *>(CopyDataSource(view_matrix)), 
                              dynamic_cast<DS_Matrix *>(CopyDataSource(projection_matrix)), 
                              dynamic_cast<DS_Matrix *>(CopyDataSource(display_matrix)));
}

float BasicRenderModelInstantiator::ScoreFit()
{
  if(positions->DoesMatch() && 
     view_matrix->DoesMatch() && 
     (display_matrix->DoesMatch() || projection_matrix->DoesMatch()))
    return 1.0f+ (normals->DoesMatch() ? 1.0f : 0.0f);
  else
    return 0.0f;
}
