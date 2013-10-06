//=======================================================================
// Copyright 2001 University of Notre Dame.
// Authors: Jeremy G. Siek and Lie-Quan Lee
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

#ifndef BOOST_SUBGRAPH_HPP
#define BOOST_SUBGRAPH_HPP

// UNDER CONSTRUCTION

#include <boost/config.hpp>
#include <list>
#include <vector>
#include <map>
#include <cassert>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

namespace boost {

  struct subgraph_tag { };

  // Invariants of an induced subgraph:
  //   - If vertex u is in subgraph g, then u must be in g.parent().
  //   - If edge e is in subgraph e, then e must be in g.parent().
  //   - If edge e=(u,v) is in the root graph, then edge e
  //     is also in any subgraph that contains both vertex u and v.

  // The Graph template parameter must have a vertex_index 
  // and edge_index internal property. It is assumed that
  // the vertex indices are assigned automatically by the
  // graph during a call to add_vertex(). It is not
  // assumed that the edge vertices are assigned automatically,
  // they are explicitly assigned here.

  template <typename Graph>
  class subgraph {
    typedef graph_traits<Graph> Traits;
  public:
    // Graph requirements
    typedef typename Traits::vertex_descriptor         vertex_descriptor;
    typedef typename Traits::edge_descriptor           edge_descriptor;
    typedef typename Traits::directed_category         directed_category;
    typedef typename Traits::edge_parallel_category    edge_parallel_category;
    typedef typename Traits::traversal_category        traversal_category;

    // IncidenceGraph requirements
    typedef typename Traits::out_edge_iterator         out_edge_iterator;
    typedef typename Traits::degree_size_type          degree_size_type;

    // AdjacencyGraph requirements
    typedef typename Traits::adjacency_iterator        adjacency_iterator;

    // VertexListGraph requirements
    typedef typename Traits::vertex_iterator           vertex_iterator;
    typedef typename Traits::vertices_size_type        vertices_size_type;

    // EdgeListGraph requirements
    typedef typename Traits::edge_iterator             edge_iterator;
    typedef typename Traits::edges_size_type           edges_size_type;

    typedef typename Traits::in_edge_iterator          in_edge_iterator;

    typedef typename Graph::edge_property_type         edge_property_type;
    typedef typename Graph::vertex_property_type       vertex_property_type;
    typedef subgraph_tag                               graph_tag;
    typedef Graph                                      graph_type;
    typedef typename Graph::graph_property_type        graph_property_type;
    
    // Constructors

    // Create the main graph, the root of the subgraph tree
    subgraph(const graph_property_type& p = graph_property_type()) 
      : m_graph(p), m_parent(0), m_edge_counter(0)
    { }
    // Create the main graph, the root of the subgraph tree
    subgraph(vertices_size_type n, 
	     const graph_property_type& p = graph_property_type()) 
      : m_graph(n, p), m_parent(0), m_edge_counter(0)
    { }

    // Create a subgraph
    subgraph<Graph>& create_subgraph() {
      m_children.push_back( subgraph<Graph>() );
      m_children.back().m_parent = this;
      return m_children.back();
    }
    
    // Create a subgraph with the specified vertex set.
    template <typename VertexIterator>
    subgraph<Graph>& create_subgraph(VertexIterator first,
				     VertexIterator last)
    {
      m_children.push_back( subgraph<Graph>() );
      m_children.back().m_parent = this;
      for (; first != last; ++first)
	add_vertex(*first, m_children.back());
      return m_children.back();
    }

    // local <-> global descriptor conversion functions
    vertex_descriptor local_to_global(vertex_descriptor u_local) const
    {
      return m_global_vertex[u_local];
    }
    vertex_descriptor global_to_local(vertex_descriptor u_global) const
    {
      vertex_descriptor u_local; bool in_subgraph;
      tie(u_local, in_subgraph) = this->find_vertex(u_global);
      assert(in_subgraph == true);
      return u_local;
    }
    edge_descriptor local_to_global(edge_descriptor e_local) const
    {
      return m_global_edge[get(edge_index, m_graph, e_local)];
    }
    edge_descriptor global_to_local(edge_descriptor e_global) const
    {
      return 
	(*m_local_edge.find(get(edge_index, root().m_graph, e_global))).second;
    }

    // Is vertex u (of the root graph) contained in this subgraph?
    // If so, return the matching local vertex.
    std::pair<vertex_descriptor, bool>
    find_vertex(vertex_descriptor u_global) const
    {
      typename std::map<vertex_descriptor, vertex_descriptor>::const_iterator
	i = m_local_vertex.find(u_global);
      return std::make_pair((*i).second, i != m_local_vertex.end());
    }

    // Return the parent graph.
    subgraph& parent() { return *m_parent; }
    const subgraph& parent() const { return *m_parent; }

    bool is_root() const { return m_parent == 0; }
    
    // Return the root graph of the subgraph tree.
    subgraph& root() {
      if (this->is_root())
	return *this;
      else
	return m_parent->root();
    }
    const subgraph& root() const {
      if (this->is_root())
	return *this;
      else
	return m_parent->root();
    }

    // Return the children subgraphs of this graph/subgraph.
    typedef std::list< subgraph<Graph> > ChildrenList;
    typedef typename ChildrenList::const_iterator
      const_children_iterator;

    typedef typename ChildrenList::iterator children_iterator;

    std::pair<const_children_iterator, const_children_iterator>
    children() const
    {
      return std::make_pair(const_children_iterator(m_children.begin()), 
			    const_children_iterator(m_children.end()));
    }

    std::pair<children_iterator, children_iterator>
    children() 
    {
      return std::make_pair(children_iterator(m_children.begin()), 
			    children_iterator(m_children.end()));
    }

    //  private:
    Graph m_graph;
    subgraph<Graph>* m_parent;
    ChildrenList m_children;
    std::vector<vertex_descriptor> m_global_vertex; // local -> global
    std::map<vertex_descriptor, vertex_descriptor> m_local_vertex;  // global -> local

    typedef typename property_map<Graph, edge_index_t>::type EdgeIndexMap;
    typedef typename property_traits<EdgeIndexMap>::value_type edge_index_type;

    std::vector<edge_descriptor> m_global_edge;              // local -> global
    std::map<edge_index_type, edge_descriptor> m_local_edge; // global -> local
    edge_index_type m_edge_counter; // for generating unique edge indices

    edge_descriptor
    local_add_edge(vertex_descriptor u_local, vertex_descriptor v_local,  
		   edge_descriptor e_global)
    {
      edge_descriptor e_local; 
      bool inserted;
      tie(e_local, inserted) = add_edge(u_local, v_local, m_graph);
      put(edge_index, m_graph, e_local, m_edge_counter++);
      m_global_edge.push_back(e_global);
      m_local_edge[get(edge_index, this->root(), e_global)] = e_local;
      return e_local;
    }

  };

  //===========================================================================
  // Functions special to the Subgraph Class

  template <typename G>
  typename subgraph<G>::vertex_descriptor
  add_vertex(typename subgraph<G>::vertex_descriptor u_global,
             subgraph<G>& g)
  {
    assert(!g.is_root());
    typename subgraph<G>::vertex_descriptor u_local, v_global, uu_global;
    typename subgraph<G>::edge_descriptor e_global;

    u_local = add_vertex(g.m_graph);
    g.m_global_vertex.push_back(u_global);
    g.m_local_vertex[u_global] = u_local;
    
    subgraph<G>& r = g.root();

    // remember edge global and local maps
    {
      typename subgraph<G>::out_edge_iterator ei, ei_end;
      for (tie(ei, ei_end) = out_edges(u_global, r); 
	   ei != ei_end; ++ei) {
	e_global = *ei;
	v_global = target(e_global, r);
	if (g.find_vertex(v_global).second == true)
	  g.local_add_edge(u_local, g.global_to_local(v_global), e_global);
      }
    }
    if (is_directed(g)) { // not necessary for undirected graph
      typename subgraph<G>::vertex_iterator vi, vi_end;
      typename subgraph<G>::out_edge_iterator ei, ei_end;
      for (tie(vi, vi_end) = vertices(r); vi != vi_end; ++vi) {
	v_global = *vi;
	if (g.find_vertex(v_global).second)
	  for (tie(ei, ei_end) = out_edges(*vi, r); ei != ei_end; ++ei) {
	    e_global = *ei;
	    uu_global = target(e_global, r);
	    if (uu_global == u_global && g.find_vertex(v_global).second) 
	      g.local_add_edge(g.global_to_local(v_global), u_local, e_global);
	  }
      }
    }

    return u_local;
  }  

  //===========================================================================
  // Functions required by the IncidenceGraph concept 

  template <typename G>
  std::pair<typename graph_traits<G>::out_edge_iterator,
            typename graph_traits<G>::out_edge_iterator>
  out_edges(typename graph_traits<G>::vertex_descriptor u_local,
            const subgraph<G>& g) 
    { return out_edges(u_local, g.m_graph); }

  template <typename G>
  typename graph_traits<G>::degree_size_type
  out_degree(typename graph_traits<G>::vertex_descriptor u_local,
             const subgraph<G>& g) 
    { return out_degree(u_local, g.m_graph); }

  template <typename G>
  typename graph_traits<G>::vertex_descriptor
  source(typename graph_traits<G>::edge_descriptor e_local,
         const subgraph<G>& g) 
    { return source(e_local, g.m_graph); }

  template <typename G>
  typename graph_traits<G>::vertex_descriptor
  target(typename graph_traits<G>::edge_descriptor e_local,
         const subgraph<G>& g) 
    { return target(e_local, g.m_graph); }

  //===========================================================================
  // Functions required by the BidirectionalGraph concept 

  template <typename G>
  std::pair<typename graph_traits<G>::in_edge_iterator,
            typename graph_traits<G>::in_edge_iterator>
  in_edges(typename graph_traits<G>::vertex_descriptor u_local,
            const subgraph<G>& g) 
    { return in_edges(u_local, g.m_graph); }

  template <typename G>
  typename graph_traits<G>::degree_size_type
  in_degree(typename graph_traits<G>::vertex_descriptor u_local,
             const subgraph<G>& g) 
    { return in_degree(u_local, g.m_graph); }

  template <typename G>
  typename graph_traits<G>::degree_size_type
  degree(typename graph_traits<G>::vertex_descriptor u_local,
             const subgraph<G>& g) 
    { return degree(u_local, g.m_graph); }

  //===========================================================================
  // Functions required by the AdjacencyGraph concept 

  template <typename G>
  std::pair<typename subgraph<G>::adjacency_iterator,
            typename subgraph<G>::adjacency_iterator>
  adjacent_vertices(typename subgraph<G>::vertex_descriptor u_local,
                    const subgraph<G>& g) 
    { return adjacent_vertices(u_local, g.m_graph); }

  //===========================================================================
  // Functions required by the VertexListGraph concept 

  template <typename G>
  std::pair<typename subgraph<G>::vertex_iterator,
            typename subgraph<G>::vertex_iterator>
  vertices(const subgraph<G>& g) 
    { return vertices(g.m_graph); }

  template <typename G>
  typename subgraph<G>::vertices_size_type
  num_vertices(const subgraph<G>& g) 
    { return num_vertices(g.m_graph); }

  //===========================================================================
  // Functions required by the EdgeListGraph concept 
  
  template <typename G>
  std::pair<typename subgraph<G>::edge_iterator,
            typename subgraph<G>::edge_iterator>
  edges(const subgraph<G>& g) 
    { return edges(g.m_graph); }

  template <typename G>
  typename subgraph<G>::edges_size_type
  num_edges(const subgraph<G>& g) 
    { return num_edges(g.m_graph); }

  //===========================================================================
  // Functions required by the AdjacencyMatrix concept 

  template <typename G>
  std::pair<typename subgraph<G>::edge_descriptor, bool>
  edge(typename subgraph<G>::vertex_descriptor u_local,
       typename subgraph<G>::vertex_descriptor v_local,
       const subgraph<G>& g)
  {
    return edge(u_local, v_local, g.m_graph);
  }

  //===========================================================================
  // Functions required by the MutableGraph concept 

  namespace detail {

    template <typename Vertex, typename Edge, typename Graph>
    void add_edge_recur_down
    (Vertex u_global, Vertex v_global, Edge e_global, subgraph<Graph>& g);

    template <typename Vertex, typename Edge, typename Children, typename G>
    void children_add_edge(Vertex u_global, Vertex v_global, Edge e_global,
                           Children& c, subgraph<G>* orig)
    {
      for (typename Children::iterator i = c.begin(); i != c.end(); ++i)
        if ((*i).find_vertex(u_global).second
	    && (*i).find_vertex(v_global).second)
          add_edge_recur_down(u_global, v_global, e_global, *i, orig);
    }

    template <typename Vertex, typename Edge, typename Graph>
    void add_edge_recur_down
      (Vertex u_global, Vertex v_global, Edge e_global, subgraph<Graph>& g,
       subgraph<Graph>* orig)
    {
      if (&g != orig ) { 
	// add local edge only if u_global and v_global are in subgraph g
        Vertex u_local, v_local;
	bool u_in_subgraph, v_in_subgraph;
	tie(u_local, u_in_subgraph) = g.find_vertex(u_global);
	tie(v_local, v_in_subgraph) = g.find_vertex(v_global);
	if (u_in_subgraph && v_in_subgraph)
	  g.local_add_edge(u_local, v_local, e_global);
      }
      children_add_edge(u_global, v_global, e_global, g.m_children, orig);
    }

    template <typename Vertex, typename Graph>
    std::pair<typename subgraph<Graph>::edge_descriptor, bool>
    add_edge_recur_up(Vertex u_global, Vertex v_global,
                      const typename Graph::edge_property_type& ep,
                      subgraph<Graph>& g, subgraph<Graph>* orig)
    {
      if (g.is_root()) {
        typename subgraph<Graph>::edge_descriptor e_global;
        bool inserted;
        tie(e_global, inserted) = add_edge(u_global, v_global, ep, g.m_graph);
	put(edge_index, g.m_graph, e_global, g.m_edge_counter++);
	g.m_global_edge.push_back(e_global);
        children_add_edge(u_global, v_global, e_global, g.m_children, orig);
        return std::make_pair(e_global, inserted);
      } else
        return add_edge_recur_up(u_global, v_global, ep, *g.m_parent, orig);
    }

  } // namespace detail

  // Add an edge to the subgraph g, specified by the local vertex
  // descriptors u and v. In addition, the edge will be added to any
  // other subgraphs which contain vertex descriptors u and v.

  template <typename G>
  std::pair<typename subgraph<G>::edge_descriptor, bool>
  add_edge(typename subgraph<G>::vertex_descriptor u_local,
           typename subgraph<G>::vertex_descriptor v_local,
           const typename G::edge_property_type& ep,
           subgraph<G>& g)
  {
    if (g.is_root()) // u_local and v_local are really global
      return detail::add_edge_recur_up(u_local, v_local, ep, g, &g);
    else {
      typename subgraph<G>::edge_descriptor e_local, e_global;
      bool inserted;
      tie(e_global, inserted) = detail::add_edge_recur_up
        (g.local_to_global(u_local), g.local_to_global(v_local), ep, g, &g);
      e_local = g.local_add_edge(u_local, v_local, e_global);
      return std::make_pair(e_local, inserted);
    }
  }

  template <typename G>
  std::pair<typename subgraph<G>::edge_descriptor, bool>
  add_edge(typename subgraph<G>::vertex_descriptor u,
           typename subgraph<G>::vertex_descriptor v,
           subgraph<G>& g)
  {
    typename G::edge_property_type ep;
    return add_edge(u, v, ep, g);
  }

  namespace detail {

    //-------------------------------------------------------------------------
    // implementation of remove_edge(u,v,g)

    template <typename Vertex, typename Graph>
    void remove_edge_recur_down(Vertex u_global, Vertex v_global, 
                                subgraph<Graph>& g);

    template <typename Vertex, typename Children>
    void children_remove_edge(Vertex u_global, Vertex v_global,
                              const Children& c)
    {
      for (typename Children::iterator i = c.begin(); i != c.end(); ++i)
        if ((*i).find_vertex(u_global).second && (*i).find_vertex(v_global).second)
          remove_edge_recur_down(u_global, v_global, *i);
    }
    
    template <typename Vertex, typename Graph>
    void remove_edge_recur_down(Vertex u_global, Vertex v_global, 
                                subgraph<Graph>& g)
    {
      Vertex u_local, v_local;
      u_local = g.m_local_vertex[u_global];
      v_local = g.m_local_vertex[v_global];
      remove_edge(u_local, v_local, g.m_graph);
      children_remove_edge(u_global, v_global, g.m_children);
    }

    template <typename Vertex, typename Graph>
    void remove_edge_recur_up(Vertex u_global, Vertex v_global, 
                              subgraph<Graph>& g)
    {
      if (g.is_root()) {
        remove_edge(u_global, v_global, g.m_graph);
        children_remove_edge(u_global, v_global, g.m_children);
      } else
        remove_edge_recur_up(u_global, v_global, *g.m_parent);
    }

    //-------------------------------------------------------------------------
    // implementation of remove_edge(e,g)

    template <typename Edge, typename Graph>
    void remove_edge_recur_down(Edge e_global, subgraph<Graph>& g);

    template <typename Edge, typename Children>
    void children_remove_edge(Edge e_global, const Children& c)
    {
      for (typename Children::iterator i = c.begin(); i != c.end(); ++i)
        if ((*i).find_vertex(source(e_global, *i)).second
	    && (*i).find_vertex(target(e_global, *i)).second)
          remove_edge_recur_down(u_global, v_global, *i);
    }

    template <typename Edge, typename Graph>
    void remove_edge_recur_down(Edge e_global, subgraph<Graph>& g)
    {
      remove_edge(g.global_to_local(e_global), g.m_graph);
      children_remove_edge(e_global, g.m_children);
    }

    template <typename Edge, typename Graph>
    void remove_edge_recur_up(Edge e_global, subgraph<Graph>& g)
    {
      if (g.is_root()) {
        remove_edge(e_global, g.m_graph);
        children_remove_edge(e_global, g.m_children);
      } else
        remove_edge_recur_up(e_global, *g.m_parent);
    }

  } // namespace detail

  template <typename G>
  void
  remove_edge(typename subgraph<G>::vertex_descriptor u_local,
              typename subgraph<G>::vertex_descriptor v_local,
              subgraph<G>& g)
  {
    if (g.is_root())
      detail::remove_edge_recur_up(u_local, v_local, g.m_graph);
    else
      detail::remove_edge_recur_up(g.local_to_global(u_local),
                                   g.local_to_global(v_local), g);
  }
  
  template <typename G>
  void
  remove_edge(typename subgraph<G>::edge_descriptor e_local,
              subgraph<G>& g)
  {
    if (g.is_root())
      detail::remove_edge_recur_up(e_local, g.m_graph);
    else
      detail::remove_edge_recur_up(get(edge_global, g.m_graph, e_local), g);
  }

  namespace detail {
    
    template <typename G>
    typename subgraph<G>::vertex_descriptor
    add_vertex_recur_up(subgraph<G>& g)
    {
      typename subgraph<G>::vertex_descriptor u_local, u_global;
      if (g.is_root()) {
        u_global = add_vertex(g.m_graph);       
        g.m_global_vertex.push_back(u_global);
      } else {
        u_global = add_vertex_recur_up(*g.m_parent);
        u_local = add_vertex(g.m_graph);
        g.m_global_vertex.push_back(u_global);
        g.m_local_vertex[u_global] = u_local; 
      }
      return u_global;
    }
    
  } // namespace detail

  template <typename G>
  typename subgraph<G>::vertex_descriptor
  add_vertex(subgraph<G>& g)
  {
    typename subgraph<G>::vertex_descriptor  u_local, u_global;
    if (g.is_root()) {
      u_global = add_vertex(g.m_graph);
      g.m_global_vertex.push_back(u_global);
      u_local = u_global;
    } else {
      u_global = detail::add_vertex_recur_up(g.parent());
      u_local = add_vertex(g.m_graph);
      g.m_global_vertex.push_back(u_global);
      g.m_local_vertex[u_global] = u_local;
    }
    return u_local;
  }

  template <typename G>
  void remove_vertex(typename subgraph<G>::vertex_descriptor u,
                     subgraph<G>& g)
  {
    // UNDER CONSTRUCTION
    assert(false);
  }


  //===========================================================================
  // Functions required by the PropertyGraph concept 

  namespace detail {

    template <typename MapCategory>
    struct property_map_ref {
      template <typename ValueType>
      struct bind {
	typedef ValueType type;
	typedef ValueType const_type;
      };
    };
    template <>
    struct property_map_ref<lvalue_property_map_tag> {
      template <typename ValueType>
      struct bind {
	typedef ValueType& type;
	typedef const ValueType& const_type;
      };
    };

  } // namespace detail

  template <typename Graph, typename PropertyTag, typename Key>
  class subgraph_property_map 
    : public put_get_at_helper< 
        typename property_traits<
           typename property_map<Graph, PropertyTag>::type
         >::value_type,
        subgraph_property_map<Graph, PropertyTag, Key> >
  {
    typedef typename property_map<Graph, PropertyTag>::type PropertyMap;
  public:
    typedef typename PropertyMap::category category;
    typedef typename property_traits<PropertyMap>::value_type value_type;
    typedef Key key_type;

    typedef typename detail::property_map_ref<category>::
      template bind<value_type> Ref;
    typedef typename Ref::type ref_type;
    typedef typename Ref::const_type const_ref_type;

    subgraph_property_map() { }

    subgraph_property_map(const subgraph<Graph>& g)
      : m_g(&const_cast<subgraph<Graph>&>(g)), 
	m_pmap(get(PropertyTag(), (const_cast<subgraph<Graph>&>(g)).root().m_graph)) { }
    
    inline ref_type operator[](key_type e_local) {
      if (m_g->m_parent == 0)
	return m_pmap[e_local];
      else
	return m_pmap[m_g->local_to_global(e_local)];
    }
    inline const_ref_type operator[](key_type e_local) const {
      if (m_g->m_parent == 0)
	return m_pmap[e_local];
      else
	return m_pmap[m_g->local_to_global(e_local)];
    }
    subgraph<Graph>* m_g;
    PropertyMap m_pmap;
  };

  namespace detail {

    struct subgraph_vertex_property_selector {
      template <class Graph, class Property, class Tag>
      struct bind {
	typedef subgraph_property_map<typename Graph::graph_type, Tag,
	  typename Graph::vertex_descriptor> type;
	typedef type const_type;
      };
    };

    struct subgraph_edge_property_selector {
      template <class Graph, class Property, class Tag>
      struct bind {
	typedef subgraph_property_map<typename Graph::graph_type, Tag,
	  typename Graph::edge_descriptor> type;
	typedef type const_type;
      };
    };
        
  } // namespace detail

  template <>
  struct vertex_property_selector<subgraph_tag> {
    typedef detail::subgraph_vertex_property_selector type;
  };

  template <>
  struct edge_property_selector<subgraph_tag> {
    typedef detail::subgraph_edge_property_selector type;
  };

  template <typename G, typename Property>
  typename property_map< subgraph<G>, Property>::type
  get(Property, subgraph<G>& g)
  {
    typedef typename property_map< subgraph<G>, Property>::type PMap;
    return PMap(g);
  }

  template <typename G, typename Property>
  typename property_map< subgraph<G>, Property>::const_type
  get(Property, const subgraph<G>& g)
  {
    typedef typename property_map< subgraph<G>, Property>::const_type PMap;
    return PMap(g);
  }

  template <typename G, typename Property, typename Key>
  typename property_traits<
    typename property_map< subgraph<G>, Property>::const_type
  >::value_type
  get(Property, const subgraph<G>& g, const Key& k)
  {
    typedef typename property_map< subgraph<G>, Property>::const_type PMap;
    PMap pmap(g);
    return pmap[k];
  }

  template <typename G, typename Property, typename Key, typename Value>
  void
  put(Property, const subgraph<G>& g, const Key& k, const Value& val)
  {
    typedef typename property_map< subgraph<G>, Property>::const_type PMap;
    PMap pmap(g);
    pmap[k] = val;
  }

  template <typename G, typename Tag>
  inline
  typename graph_property<G, Tag>::type&
  get_property(subgraph<G>& g, Tag tag) {
    return get_property(g.m_graph, tag);
  }

  template <typename G, typename Tag>
  inline
  const typename graph_property<G, Tag>::type&
  get_property(const subgraph<G>& g, Tag tag) {
    return get_property(g.m_graph, tag);
  }

  //===========================================================================
  // Miscellaneous Functions

  template <typename G>
  typename subgraph<G>::vertex_descriptor
  vertex(typename subgraph<G>::vertices_size_type n, const subgraph<G>& g)
  {
    return vertex(n, g.m_graph);
  }

} // namespace boost

#endif // BOOST_SUBGRAPH_HPP