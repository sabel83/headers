//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================

#ifndef BOOST_GRAPH_ADJACENCY_LIST_HPP
#define BOOST_GRAPH_ADJACENCY_LIST_HPP


#include <boost/config.hpp>

#include <vector>
#include <list>
#include <set>
#include <map>

#if !defined BOOST_NO_HASH
#include <hash_set>
#include <hash_map>
#endif

#if !defined BOOST_NO_SLIST
#include <slist>
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_selectors.hpp>
#include <boost/property_map.hpp>
#include <boost/pending/ct_if.hpp>
#include <boost/graph/detail/edge.hpp>

namespace boost {

  //===========================================================================
  // Selectors for the VertexList and EdgeList template parameters of
  // adjacency_list, and the container_gen traits class which is used
  // to map the selectors to the container type used to implement the
  // graph.
  //
  // The main container_gen traits class uses partial specialization,
  // so we also include a workaround.

#if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined BOOST_NO_SLIST
  struct slistS {};  
#endif

  struct vecS  { };
  struct listS { };
  struct setS { };
  struct multisetS { };
  struct mapS  { };
#if !defined BOOST_NO_HASH
  struct hash_mapS { };
  struct hash_setS { };
#endif

  template <class Selector, class ValueType>
  struct container_gen { };

  template <class ValueType>
  struct container_gen<listS, ValueType> {
    typedef std::list<ValueType> type;
  };
#if !defined BOOST_NO_SLIST
  template <class ValueType>
  struct container_gen<slistS, ValueType> {
    typedef BOOST_STD_EXTENSION_NAMESPACE::slist<ValueType> type;
  };
#endif
  template <class ValueType>
  struct container_gen<vecS, ValueType> {
    typedef std::vector<ValueType> type;
  };

  template <class ValueType>
  struct container_gen<mapS, ValueType> {
    typedef std::set<ValueType> type;
  };

  template <class ValueType>
  struct container_gen<setS, ValueType> {
    typedef std::set<ValueType> type;
  };

  template <class ValueType>
  struct container_gen<multisetS, ValueType> {
    typedef std::multiset<ValueType> type;
  };

#if !defined BOOST_NO_HASH
  template <class ValueType>
  struct container_gen<hash_mapS, ValueType> {
    typedef BOOST_STD_EXTENSION_NAMESPACE::hash_set<ValueType> type;
  };

  template <class ValueType>
  struct container_gen<hash_setS, ValueType> {
    typedef BOOST_STD_EXTENSION_NAMESPACE::hash_set<ValueType> type;
  };
#endif

#else // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#if !defined BOOST_NO_SLIST
  struct slistS {
    template <class T>
    struct bind { typedef std::slist<T> type; };
  };
#endif

  struct vecS  {
    template <class T>
    struct bind { typedef std::vector<T> type; };
  };

  struct listS { 
    template <class T>
    struct bind { typedef std::list<T> type; };
  };

  struct setS  { 
    template <class T>
    struct bind { typedef std::set<T, std::less<T> > type; };
  };

  struct multisetS  { 
    template <class T>
    struct bind { typedef std::multiset<T, std::less<T> > type; };
  };

#if !defined BOOST_NO_HASH
  struct hash_setS { 
    template <class T>
    struct bind { typedef std::hash_set<T, std::less<T> > type; };
  };
#endif

  struct mapS  { 
    template <class T>
    struct bind { typedef std::set<T, std::less<T> > type; };
  };

#if !defined BOOST_NO_HASH
  struct hash_mapS { 
    template <class T>
    struct bind { typedef std::hash_set<T, std::less<T> > type; };
  };
#endif

  template <class Selector> struct container_selector {
    typedef vecS type;
  };

#define BOOST_CONTAINER_SELECTOR(NAME) \
  template <> struct container_selector<NAME>  { \
    typedef NAME type; \
  }

  BOOST_CONTAINER_SELECTOR(vecS);
  BOOST_CONTAINER_SELECTOR(listS);
  BOOST_CONTAINER_SELECTOR(mapS);
#if !defined BOOST_NO_HASH
  BOOST_CONTAINER_SELECTOR(hash_mapS);
#endif
#if !defined BOOST_NO_SLIST
  BOOST_CONTAINER_SELECTOR(slistS);
#endif

  template <class Selector, class ValueType>
  struct container_gen {
    typedef typename container_selector<Selector>::type Select;
    typedef typename Select:: template bind<ValueType>::type type;
  };

#endif // !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  template <class StorageSelector>
  struct parallel_edge_traits { };

  template <>
  struct parallel_edge_traits<vecS> { 
    typedef allow_parallel_edge_tag type; };

  template <>
  struct parallel_edge_traits<listS> { 
    typedef allow_parallel_edge_tag type; };

#if !defined BOOST_NO_SLIST
  template <>
  struct parallel_edge_traits<slistS> { 
    typedef allow_parallel_edge_tag type; };
#endif

  template <>
  struct parallel_edge_traits<setS> { 
    typedef disallow_parallel_edge_tag type; };

  template <>
  struct parallel_edge_traits<multisetS> { 
    typedef allow_parallel_edge_tag type; };

#if !defined BOOST_NO_HASH
  template <>
  struct parallel_edge_traits<hash_setS> {
    typedef disallow_parallel_edge_tag type; 
  };
#endif

  // mapS is obsolete, replaced with setS
  template <>
  struct parallel_edge_traits<mapS> { 
    typedef disallow_parallel_edge_tag type; };

#if !defined BOOST_NO_HASH
  template <>
  struct parallel_edge_traits<hash_mapS> {
    typedef disallow_parallel_edge_tag type; 
  };
#endif

  namespace detail {
    template <class Directed> struct is_random_access { 
      enum { value = false};
      typedef false_type type;
    };
    template <>
    struct is_random_access<vecS> { 
      enum { value = true }; 
      typedef true_type type;
    };

  } // namespace detail



  //===========================================================================
  // The adjacency_list_traits class, which provides a way to access
  // some of the associated types of an adjacency_list type without
  // having to first create the adjacency_list type. This is useful
  // when trying to create interior vertex or edge properties who's
  // value type is a vertex or edge descriptor.

  template <class EdgeListS = vecS,
            class VertexListS = vecS,
            class DirectedS = directedS>
  struct adjacency_list_traits
  {
    typedef typename detail::is_random_access<VertexListS>::type
      is_rand_access;
    typedef typename DirectedS::is_bidir_t is_bidir;
    typedef typename DirectedS::is_directed_t is_directed;

    typedef typename boost::ct_if_t<is_bidir,
      bidirectional_tag,
      typename boost::ct_if_t<is_directed,
        directed_tag, undirected_tag
      >::type
    >::type directed_category;

    typedef typename parallel_edge_traits<EdgeListS>::type
      edge_parallel_category;

    typedef void* vertex_ptr;
    typedef typename boost::ct_if_t<is_rand_access,
      std::size_t, vertex_ptr>::type vertex_descriptor;
    typedef detail::edge_desc_impl<directed_category, vertex_descriptor>
      edge_descriptor;
  };

} // namespace boost

#include <boost/graph/detail/adjacency_list.hpp>

namespace boost {

  //===========================================================================
  // The adjacency_list class.
  //

  template <class EdgeListS = vecS,   // a Sequence or an AssociativeContainer
            class VertexListS = vecS, // a Sequence or a RandomAccessContainer
            class DirectedS = directedS,
            class VertexProperty = no_property,
            class EdgeProperty = no_property,
            class GraphProperty = no_property>
  class adjacency_list
    : public detail::adj_list_gen<
      adjacency_list<EdgeListS,VertexListS,DirectedS,
                     VertexProperty,EdgeProperty,GraphProperty>,
      VertexListS, EdgeListS, DirectedS, 
      VertexProperty, EdgeProperty, GraphProperty>::type
  {
    typedef adjacency_list self;
    typedef typename detail::adj_list_gen<
      self, VertexListS, EdgeListS, DirectedS, 
      VertexProperty, EdgeProperty, GraphProperty
    >::type Base;
  public:
    typedef typename Base::stored_vertex stored_vertex;
    typedef typename Base::vertices_size_type vertices_size_type;
    typedef typename Base::edges_size_type edges_size_type;
    typedef typename Base::degree_size_type degree_size_type;

    typedef EdgeProperty edge_property_type;
    typedef VertexProperty vertex_property_type;
    typedef GraphProperty graph_property_type;

    inline adjacency_list(const GraphProperty& p = GraphProperty()) 
      : m_property(p) { }

    inline adjacency_list(const adjacency_list& x)
      : Base(x), m_property(x.m_property) { }

    inline adjacency_list& operator=(const adjacency_list& x) {
      Base::operator=(x);
      m_property = x.m_property;
      return *this;
    }

    // Required by Mutable Graph
    inline adjacency_list(vertices_size_type num_vertices, 
                          const GraphProperty& p = GraphProperty())
      : Base(num_vertices), m_property(p) { }

    // Required by Iterator Constructible Graph
    template <class EdgeIterator>
    inline adjacency_list(EdgeIterator first, EdgeIterator last,
			  vertices_size_type n = 0,
			  edges_size_type m = 0,
                          const GraphProperty& p = GraphProperty())
      : Base(n, first, last), m_property(p) { }

    template <class EdgeIterator, class EdgePropertyIterator>
    inline adjacency_list(vertices_size_type num_vertices,
                          EdgeIterator first, EdgeIterator last,
                          EdgePropertyIterator ep_iter,
                          const GraphProperty& p = GraphProperty())
      : Base(num_vertices, first, last, ep_iter), m_property(p) { }

    // Deprecated
    template <class EdgeIterator>
    inline adjacency_list(vertices_size_type num_vertices,
                          EdgeIterator first, EdgeIterator last,
                          const GraphProperty& p = GraphProperty())
      : Base(num_vertices, first, last), m_property(p) { }


    void swap(adjacency_list& x) {
      // Is there a more efficient way to do this?
      adjacency_list tmp(x);
      x = *this;
      *this = tmp;
    }

    //  protected:  (would be protected if friends were more portable)
    GraphProperty m_property;
  };

  template <class EL, class VL, class DS, class VP,class EP,class GP,class Tag>
  inline
  typename graph_property<adjacency_list<EL,VL,DS,VP,EP,GP>, Tag>::type&
  get_property(adjacency_list<EL,VL,DS,VP,EP,GP>& g, Tag) {
    return get_property_value(g.m_property, Tag());
  }

  template <class EL, class VL, class DS, class VP,class EP,class GP,class Tag>
  inline
  const typename graph_property<adjacency_list<EL,VL,DS,VP,EP,GP>, Tag>::type&
  get_property(const adjacency_list<EL,VL,DS,VP,EP,GP>& g, Tag) {
    return get_property_value(g.m_property, Tag());
  }

  // dwa 09/25/00 - needed to be more explicit so reverse_graph would work.
  template <class Directed, class Vertex,
      class EdgeListS,
      class VertexListS,
      class DirectedS,
      class VertexProperty,
      class EdgeProperty,
      class GraphProperty>
  inline Vertex
  source(const detail::edge_base<Directed,Vertex>& e,
         const adjacency_list<EdgeListS, VertexListS, DirectedS,
                        VertexProperty, EdgeProperty, GraphProperty>&)
  {
    return e.m_source;
  }

  template <class Directed, class Vertex,
      class EdgeListS,
      class VertexListS,
      class DirectedS,
      class VertexProperty,
      class EdgeProperty,
      class GraphProperty>
  inline Vertex
  target(const detail::edge_base<Directed,Vertex>& e,
         const adjacency_list<EdgeListS, VertexListS, DirectedS,
                        VertexProperty, EdgeProperty, GraphProperty>&)
  {
    return e.m_target;
  }

} // namespace boost


#endif // BOOST_GRAPH_ADJACENCY_LIST_HPP
