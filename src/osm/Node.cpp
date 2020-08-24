// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#include "osm2ttl/osm/Node.h"

#include "osmium/osm/node.hpp"
#include "osmium/osm/node_ref.hpp"

#include "osm2ttl/osm/TagList.h"

// ____________________________________________________________________________
osm2ttl::osm::Node::Node(const osmium::Node& node) {
  _id = node.positive_id();
  _geom = osm2ttl::geometry::Location(node.location().lon(),
                                      node.location().lat());
  _tags = osm2ttl::osm::convertTagList(node.tags());
}

// ____________________________________________________________________________
osm2ttl::osm::Node::Node(const osmium::NodeRef& nodeRef) {
  _id = nodeRef.positive_ref();
  _geom = osm2ttl::geometry::Location(nodeRef.location().lon(),
                                      nodeRef.location().lat());
}

// ____________________________________________________________________________
uint64_t osm2ttl::osm::Node::id() const noexcept {
  return _id;
}

// ____________________________________________________________________________
osm2ttl::geometry::Location osm2ttl::osm::Node::geom() const noexcept {
  return _geom;
}

// ____________________________________________________________________________
osm2ttl::osm::TagList osm2ttl::osm::Node::tags() const noexcept {
  return _tags;
}