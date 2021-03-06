/**********************************************************************************
*                     Copyright (c) 2013-2015 Carson Brownlee
*         Texas Advanced Computing Center, University of Texas at Austin
*                       All rights reserved
* 
*       This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* 
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************************/

#ifndef ORENDERABLE_H
#define ORENDERABLE_H

#include "ospray/ospray.h"
#include "ospray/common/OSPCommon.h"

#include <Interface/MantaInterface.h>
#include <Interface/Scene.h>
#include <Interface/Object.h>
#include <Interface/Context.h>
#include <Core/Geometry/BBox.h>
#include <Core/Exceptions/Exception.h>
#include <Core/Exceptions/InternalError.h>
#include <Model/Instances/Instance.h>
#include <Model/TexCoordMappers/UniformMapper.h>
#include <Model/Groups/Group.h>
#include <Model/Primitives/MeshTriangle.h>
#include <Model/Primitives/PrimitiveCommon.h>

#include <UseMPI.h>
#if USE_MPI
  #include "Mesh_DSM.h"
  #include "DynBVH_D.h"
#endif

#include "defines.h"
#include "Renderable.h"




#include <cassert>

using namespace Manta;

enum OGeometryType {
  OR_TRIANGLES, OR_POINTS, OR_CYLINDERS
};

struct OData
{
  // OData();
 Manta::Mesh* mesh;
size_t num_prims;
OSPGeometry ospMesh;
OSPModel ospModel;
OSPMaterial mat;
GLMaterial glmat;
// embree::Handle<embree::Device::RTMaterial> d_material;
// embree::Handle<embree::Device::RTShape> d_mesh;
OGeometryType geomType; //geometry type: triangles, cylinders, spheres
};

class OGeometryGenerator : public GeometryGenerator
{
public:
  OGeometryGenerator() : _data(NULL) {_vertCounter=0;}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) = 0;
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) = 0;
  void setData(OData* data) { _data = data; }
protected:
  OData* _data;
};

//instead of sotring the entire display list, keep track of each
//begin end segment as a seperate item
//IMPORTANT:: Need to add as to work queue when mrenderable is finished, but only if it's MESH isn't empty!!!!!!
class ORenderable : public Renderable
{
public:
  ORenderable(OGeometryGenerator* gen);
  virtual ~ORenderable();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z)
  {
    _generator->addVertex(x,y,z);
  }
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z)
  {
    _generator->addNormal(x,y,z);
  }
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z)
  {
    _generator->addTextureCoord(u,v,w,z);
  }
  virtual void setGenerator(GeometryGenerator* gen)
  {
    _generator = gen;
    OGeometryGenerator* mgg = dynamic_cast<OGeometryGenerator*>(gen);
    assert(mgg);
    mgg->setData(_data);
  }

  virtual bool isEmpty();  //NOTE: MESH could still be empty...
  virtual size_t getNumPrims() ; // NOTE: num prims of groups, MESH could still be empty
  OData* _data;
};

class OGeometryGeneratorVoid: public OGeometryGenerator
{
public:
  OGeometryGeneratorVoid();
  virtual ~OGeometryGeneratorVoid();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z) {}
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};


class OGeometryGeneratorTriangles : public OGeometryGenerator
{
public:
  OGeometryGeneratorTriangles()
  {}
  virtual ~OGeometryGeneratorTriangles();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class OGeometryGeneratorTriangleStrip : public OGeometryGenerator
{
public:
  OGeometryGeneratorTriangleStrip()
  {}
  virtual ~OGeometryGeneratorTriangleStrip();
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addNormal(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};


class OGeometryGeneratorQuads : public OGeometryGenerator
{
public:
  OGeometryGeneratorQuads()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class OGeometryGeneratorQuadStrip : public OGeometryGenerator
{
public:
  OGeometryGeneratorQuadStrip()
  {}
  virtual void addVertex(Manta::Real x, Manta::Real y, Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z);
};

class OGeometryGeneratorLines : public OGeometryGenerator
{
public:
  OGeometryGeneratorLines();
  virtual  ~OGeometryGeneratorLines();
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
  Manta::Real radius;
  Vector last_vertex;
};

class OGeometryGeneratorLineStrip : public OGeometryGeneratorLines
{
public:
  OGeometryGeneratorLineStrip()
    :OGeometryGeneratorLines()
  {}
  virtual ~OGeometryGeneratorLineStrip() {}
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};

class OGeometryGeneratorPoints : public OGeometryGenerator
{
public:
  OGeometryGeneratorPoints();
  virtual  ~OGeometryGeneratorPoints();
  virtual void addVertex(Manta::Real x,Manta::Real y,Manta::Real z);
  virtual void addTextureCoord(Manta::Real u, Manta::Real v, Manta::Real w, Manta::Real z) {}
};

#endif
