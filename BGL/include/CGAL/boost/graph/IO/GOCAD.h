// Copyright (c) 2015  GeometryFactory (France).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s)     : Andreas Fabri
//                 Mael Rouxel-Labbé

#ifndef CGAL_BGL_IO_GOCAD_H
#define CGAL_BGL_IO_GOCAD_H

#include <CGAL/IO/GOCAD.h>

#include <CGAL/assertions.h>
#include <CGAL/boost/graph/IO/Generic_facegraph_builder.h>
#include <CGAL/boost/graph/iterator.h>
#include <CGAL/boost/graph/Named_function_parameters.h>

#include <boost/container/flat_map.hpp>

#include <fstream>
#include <iostream>
#include <utility>

#ifdef DOXYGEN_RUNNING
#define CGAL_BGL_NP_TEMPLATE_PARAMETERS NamedParameters
#define CGAL_BGL_NP_CLASS NamedParameters
#endif

namespace CGAL {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// Read

namespace IO {
namespace internal {

// Use CRTP to gain access to the protected members without getters/setters.
template <typename Graph, typename Point>
class GOCAD_builder
  : public Generic_facegraph_builder<Graph, Point, GOCAD_builder<Graph, Point> >
{
  typedef GOCAD_builder<Graph, Point>                                           Self;
  typedef Generic_facegraph_builder<Graph, Point, Self>                         Base;

  typedef typename Base::Point_container                                        Point_container;
  typedef typename Base::Face                                                   Face;
  typedef typename Base::Face_container                                         Face_container;

public:
  GOCAD_builder(std::istream& is, bool verbose) : Base(is, verbose) { }

  // @check ascii
  template <typename NamedParameters>
  bool read(std::istream& is,
            Point_container& points,
            Face_container& faces,
            const NamedParameters& np,
            bool verbose)
  {
    std::pair<std::string, std::string> name_and_color;
    bool res = read_GOCAD(is, name_and_color, points, faces, np, verbose);
    if(res)
    {
      name = name_and_color.first;
      color = name_and_color.second;
    }
    return res;
  }

public:
  std::string name;
  std::string color;
};

} // namespace internal
} // namespace IO

/// \ingroup PkgBGLIoFuncsGOCAD
///
/// \brief reads the graph `g` from the input stream, using the \ref IOStreamGocad.
///
/// \attention The graph `g` is not cleared, and the data from the stream is added.
///
/// \tparam Graph a model of `MutableFaceGraph`
/// \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"
///
/// \param is the input stream
/// \param name_and_color name and color of the mesh
/// \param g the graph to be built from the input data
/// \param verbose whether extra information is printed when an incident occurs during reading
/// \param np optional \ref bgl_namedparameters "Named Parameters" described below
///
/// \cgalNamedParamsBegin
///   \cgalParamNBegin{vertex_point_map}
///     \cgalParamDescription{a property map associating points to the vertices of `g`}
///     \cgalParamType{a class model of `ReadWritePropertyMap` with `boost::graph_traits<Graph>::%vertex_descriptor`
///                    as key type and `%Point_3` as value type}
///     \cgalParamDefault{`boost::get(CGAL::vertex_point, g)`}
///     \cgalParamExtra{If this parameter is omitted, an internal property map for `CGAL::vertex_point_t`
///                     must be available in `Graph`.}
///   \cgalParamNEnd
/// \cgalNamedParamsEnd
///
/// \pre The data must represent a 2-manifold
///
/// \returns `true` if the resulting mesh is valid.
///
template <typename Graph,
          typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool read_GOCAD(std::istream& is,
                std::pair<std::string, std::string>& name_and_color,
                Graph& g,
                const CGAL_BGL_NP_CLASS& np,
                bool verbose = true)
{
  typedef typename CGAL::GetVertexPointMap<Graph, CGAL_BGL_NP_CLASS>::type     VPM;
  typedef typename boost::property_traits<VPM>::value_type                     Point;

  IO::internal::GOCAD_builder<Graph, Point> builder(is, verbose);
  if(!builder(g, np))
    return false;

  name_and_color.first = builder.name;
  name_and_color.second = builder.color;

  return true;
}

/// \cond SKIP_IN_MANUAL

template <typename Graph, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool read_GOCAD(std::istream& is, Graph& g, const CGAL_BGL_NP_CLASS& np, bool verbose = true)
{
  std::pair<std::string, std::string> dummy;
  return read_GOCAD(is, dummy, g, np, verbose);
}

template <typename Graph>
bool read_GOCAD(std::istream& is, std::pair<std::string, std::string>& name_and_color, Graph& g)
{
  return read_GOCAD(is, name_and_color, g, parameters::all_default());
}

/// \endcond

/// \ingroup PkgBGLIoFuncsGOCAD
///
/// \brief reads the graph `g` from the file `fname`, using the \ref IOStreamGocad.
///
/// \attention The graph `g` is not cleared, and the data from the stream is added.
///
/// \tparam Graph a model of `MutableFaceGraph`
/// \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"
///
/// \param fname the name of the input file
/// \param name_and_color name and color of the mesh
/// \param g the graph to be built from the input data
/// \param verbose whether extra information is printed when an incident occurs during reading
/// \param np optional \ref bgl_namedparameters "Named Parameters" described below
///
/// \cgalNamedParamsBegin
///   \cgalParamNBegin{vertex_point_map}
///     \cgalParamDescription{a property map associating points to the vertices of `g`}
///     \cgalParamType{a class model of `ReadWritePropertyMap` with `boost::graph_traits<Graph>::%vertex_descriptor`
///                    as key type and `%Point_3` as value type}
///     \cgalParamDefault{`boost::get(CGAL::vertex_point, g)`}
///     \cgalParamExtra{If this parameter is omitted, an internal property map for `CGAL::vertex_point_t`
///                     must be available in `Graph`.}
///   \cgalParamNEnd
/// \cgalNamedParamsEnd
///
/// \sa Overloads of this function for specific models of the concept `FaceGraph`.
///
/// \pre The data must represent a 2-manifold
///
template <typename Graph,
          typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool read_GOCAD(const char* fname,
                std::pair<std::string, std::string>& name_and_color,
                Graph& g,
                const CGAL_BGL_NP_CLASS& np,
                bool verbose = true)
{
  std::ifstream is(fname);
  return read_GOCAD(is, name_and_color, g, np, verbose);
}

/// \cond SKIP_IN_MANUAL

template <typename Graph, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool read_GOCAD(const char* fname, Graph& g, const CGAL_BGL_NP_CLASS& np, bool verbose = true)
{
  std::pair<std::string, std::string> dummy;
  return read_GOCAD(fname, dummy, g, np, verbose);
}

template <typename Graph, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool read_GOCAD(const std::string& fname, Graph& g, CGAL_BGL_NP_CLASS np, bool verbose = true)
{
  return read_GOCAD(fname.c_str(), g, np, verbose);
}

template <typename Graph>
bool read_GOCAD(std::istream& is, Graph& g) { return read_GOCAD(is, g, parameters::all_default()); }
template <typename Graph>
bool read_GOCAD(const char* fname, Graph& g) { return read_GOCAD(fname, g, parameters::all_default()); }
template <typename Graph>
bool read_GOCAD(const std::string& fname, Graph& g) { return read_GOCAD(fname, g, parameters::all_default()); }

/// \endcond

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// Write

/// \ingroup PkgBGLIoFuncsGOCAD
///
/// \brief writes the graph `g` into the output stream `os`, using the \ref IOStreamGocad.
///
/// \tparam Graph a model of `FaceListGraph`
/// \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"
///
/// \param os the output stream
/// \param name the name that will be assigned to `g` in the output file
/// \param g the graph to be output
/// \param np optional \ref bgl_namedparameters "Named Parameters" described below
///
/// \cgalNamedParamsBegin
///   \cgalParamNBegin{vertex_point_map}
///     \cgalParamDescription{a property map associating points to the vertices of `g`}
///     \cgalParamType{a class model of `ReadablePropertyMap` with `boost::graph_traits<Graph>::%vertex_descriptor`
///                    as key type and `%Point_3` as value type}
///     \cgalParamDefault{`boost::get(CGAL::vertex_point, g)`}
///     \cgalParamExtra{If this parameter is omitted, an internal property map for `CGAL::vertex_point_t`
///                     must be available in `Graph`.}
///   \cgalParamNEnd
///
///   \cgalParamNBegin{stream_precision}
///     \cgalParamDescription{a parameter used to set the precision (i.e. how many digits are generated) of the output stream}
///     \cgalParamType{int}
///     \cgalParamDefault{`6`}
///   \cgalParamNEnd
/// \cgalNamedParamsEnd
///
template <typename Graph,
          typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_GOCAD(std::ostream& os,
                 const char* name,
                 const Graph& g,
                 const CGAL_BGL_NP_CLASS& np)
{
  typedef typename boost::graph_traits<Graph>::vertex_descriptor    vertex_descriptor;
  typedef typename boost::graph_traits<Graph>::halfedge_descriptor  halfedge_descriptor;
  typedef typename boost::graph_traits<Graph>::face_descriptor      face_descriptor;
  typedef typename boost::graph_traits<Graph>::vertices_size_type   vertices_size_type;

  using parameters::choose_parameter;
  using parameters::get_parameter;

  typename CGAL::GetVertexPointMap<Graph, CGAL_BGL_NP_CLASS>::const_type
      vpm = choose_parameter(get_parameter(np, internal_np::vertex_point),
                             get_const_property_map(CGAL::vertex_point, g));

  if(!os.good())
    return false;

  const int precision = choose_parameter(get_parameter(np, internal_np::stream_precision), 6);
  os << std::setprecision(precision);

  os << "GOCAD TSurf 1\n"
        "HEADER {\n"
        "name:";
  os << name << std::endl;
  os << "*border:on\n"
        "*border*bstone:on\n"
        "}\n"
        "GOCAD_ORIGINAL_COORDINATE_SYSTEM\n"
        "NAME Default\n"
        "AXIS_NAME \"X\" \"Y\" \"Z\"\n"
        "AXIS_UNIT \"m\" \"m\" \"m\"\n"
        "ZPOSITIVE Elevation\n"
        "END_ORIGINAL_COORDINATE_SYSTEM\n"
        "TFACE\n";

  boost::container::flat_map<vertex_descriptor, vertices_size_type> reindex;

  vertices_size_type i = 0;
  for(const vertex_descriptor v : vertices(g))
  {
    os << "VRTX " << i << " " << get(vpm, v) << "\n";
    reindex[v] = i++;
  }

  for(const face_descriptor f : faces(g))
  {
    halfedge_descriptor h = halfedge(f, g);
    os << "TRGL " << reindex[target(prev(h, g), g)] << " "
                  << reindex[target(h, g)] << " "
                  << reindex[target(next(h, g), g)] << "\n";
  }

  os << "END" << std::endl;

  return os.good();
}

template <typename Graph>
bool write_GOCAD(std::ostream& os, const char* name, const Graph& g)
{
  return write_GOCAD(os, name, g, parameters::all_default());
}

/// \ingroup PkgBGLIoFuncsGOCAD
///
/// \brief writes the graph `g` into a file named `fname`, using the \ref IOStreamGocad.
///
/// In this overload, `fname` is used as the name of the graph within the file.
///
/// \tparam Graph a model of `FaceListGraph`
/// \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"
///
/// \param fname the name of the output file
/// \param g the graph to be output
/// \param np optional \ref bgl_namedparameters "Named Parameters" described below
///
/// \cgalNamedParamsBegin
///   \cgalParamNBegin{vertex_point_map}
///     \cgalParamDescription{a property map associating points to the vertices of `g`}
///     \cgalParamType{a class model of `ReadablePropertyMap` with `boost::graph_traits<Graph>::%vertex_descriptor`
///                    as key type and `%Point_3` as value type}
///     \cgalParamDefault{`boost::get(CGAL::vertex_point, g)`}
///     \cgalParamExtra{If this parameter is omitted, an internal property map for `CGAL::vertex_point_t`
///                     must be available in `Graph`.}
///   \cgalParamNEnd
///
///   \cgalParamNBegin{stream_precision}
///     \cgalParamDescription{a parameter used to set the precision (i.e. how many digits are generated) of the output stream}
///     \cgalParamType{int}
///     \cgalParamDefault{`6`}
///   \cgalParamNEnd
/// \cgalNamedParamsEnd
///
/// \sa Overloads of this function for specific models of the concept `FaceGraph`.
///
template <typename Graph,
          typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_GOCAD(const char* fname,
                 const Graph& g,
                 const CGAL_BGL_NP_CLASS& np)
{
  std::ofstream os(fname);
  return write_GOCAD(os, fname, g, np);
}

/// \cond SKIP_IN_MANUAL

template <typename Graph, typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_GOCAD(const std::string& fname, const Graph& g, const CGAL_BGL_NP_CLASS& np)
{
  return write_GOCAD(fname.c_str(), g, np);
}

/// \endcond

/// \ingroup PkgBGLIoFuncsGOCAD
///
/// \brief writes the graph `g` in the  \ref IOStreamGocad into `os`.
///
/// The name assigned to `g`in the output is `anonymous`.
///
/// \tparam Graph a model of `FaceListGraph`
/// \tparam NamedParameters a sequence of \ref bgl_namedparameters "Named Parameters"
///
/// \param os the output stream
/// \param g the graph to be output
/// \param np optional \ref bgl_namedparameters "Named Parameters" described below
///
/// \cgalNamedParamsBegin
///   \cgalParamNBegin{vertex_point_map}
///     \cgalParamDescription{a property map associating points to the vertices of `g`}
///     \cgalParamType{a class model of `ReadablePropertyMap` with `boost::graph_traits<Graph>::%vertex_descriptor`
///                    as key type and `%Point_3` as value type}
///     \cgalParamDefault{`boost::get(CGAL::vertex_point, g)`}
///     \cgalParamExtra{If this parameter is omitted, an internal property map for `CGAL::vertex_point_t`
///                     must be available in `Graph`.}
///   \cgalParamNEnd
///
///   \cgalParamNBegin{stream_precision}
///     \cgalParamDescription{a parameter used to set the precision (i.e. how many digits are generated) of the output stream}
///     \cgalParamType{int}
///     \cgalParamDefault{`6`}
///   \cgalParamNEnd
/// \cgalNamedParamsEnd
///
template <typename Graph,
          typename CGAL_BGL_NP_TEMPLATE_PARAMETERS>
bool write_GOCAD(std::ostream& os,
                 const Graph& g,
                 const CGAL_BGL_NP_CLASS& np)
{
  return write_GOCAD(os, "anonymous", g, np);
}

/// \cond SKIP_IN_MANUAL

template <typename Graph>
bool write_GOCAD(std::ostream& os, const Graph& g)
{
  return write_GOCAD(os, "anonymous", g, parameters::all_default());
}

template <typename Graph>
bool write_GOCAD(const char* fname, const Graph& g) { return write_GOCAD(fname, g, parameters::all_default()); }
template <typename Graph>
bool write_GOCAD(const std::string& fname, const Graph& g) { return write_GOCAD(fname, g, parameters::all_default()); }

/// \endcond

} // namespace CGAL

#endif // CGAL_BGL_IO_GOCAD_H
