// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#include "osm2ttl/osm/Area.h"

#include <iostream>
#include <vector>
#include <utility>

#include "osmium/handler/node_locations_for_ways.hpp"
#include "osmium/index/map/sparse_file_array.hpp"
#include "osmium/osm/area.hpp"

#include "osm2ttl/osm/Ring.h"

// ____________________________________________________________________________
osm2ttl::osm::Area::Area(uint64_t id, const osmium::Area& area,
  osmium::handler::NodeLocationsForWays<
    osmium::index::map::SparseFileArray<
      osmium::unsigned_object_id_type, osmium::Location>>* nodeLocations) :
    _nodeLocations(nodeLocations) {
  _id = id;
  _box = area.envelope();

  for (const auto& ring : area.outer_rings()) {
    _rings.emplace_back();
    for (const auto& noderef : ring) {
      _rings.back().nodes.push_back(noderef.positive_ref());
    }

    for (const auto& iring : area.inner_rings(ring)) {
      _rings.back().inner.emplace_back();
      for (const auto& noderef : iring) {
      _rings.back().inner.back().nodes.push_back(noderef.positive_ref());
      }
    }
  }
}

// ____________________________________________________________________________
uint64_t osm2ttl::osm::Area::id() const {
  return _id;
}

// ____________________________________________________________________________
uint64_t osm2ttl::osm::Area::objId() const {
  return _objId;
}

// ____________________________________________________________________________
osmium::Box osm2ttl::osm::Area::bbox() const {
  return _box;
}

// ____________________________________________________________________________
char osm2ttl::osm::Area::tagAdministrationLevel() const {
  return _tagAdministrationLevel;
}

// ____________________________________________________________________________
std::vector<osm2ttl::osm::OuterRing> osm2ttl::osm::Area::rings() {
  return _rings;
}

// ____________________________________________________________________________
double osm2ttl::osm::Area::vagueArea() const {
  return (_box.top_right().x() - _box.bottom_left().x()) *
         (_box.top_right().y() - _box.bottom_left().y());
}

// ____________________________________________________________________________
bool osm2ttl::osm::Area::vagueIntersects(const osm2ttl::osm::Area& other)
  const {
  return _box.contains(other._box.bottom_left())
      || _box.contains(other._box.top_right());
}

// ____________________________________________________________________________
bool osm2ttl::osm::Area::vagueContains(const osm2ttl::osm::Area& other)
  const {
  return _box.contains(other._box.bottom_left())
      && _box.contains(other._box.top_right());
}

// ____________________________________________________________________________
double osm2ttl::osm::Area::area() const {
  double res = 0.0;

  for (const auto& outer : _rings) {
    res += osm2ttl::osm::Area::area(outer);
    for (const auto& inner : outer.inner) {
      res -= osm2ttl::osm::Area::area(inner);
    }
  }
  return res;
}

// ____________________________________________________________________________
double osm2ttl::osm::Area::area(const osm2ttl::osm::Ring& ring) const {
  double res = 0.0;
  for (size_t i = 0; i < ring.nodes.size(); ++i) {
    size_t j = (i + 1) % ring.nodes.size();
    osmium::Location l1 = _nodeLocations->get_node_location(ring.nodes[i]);
    osmium::Location l2 = _nodeLocations->get_node_location(ring.nodes[j]);
    res += 0.5 * std::abs((l1.x() * l2.y()) - (l1.y() * l2.x()));
    std::cout << "|" << l1 << " " << l2 << " :: " << res << "\n";
  }
  return res;
}


// ____________________________________________________________________________
bool osm2ttl::osm::Area::intersects(const osm2ttl::osm::Area& other)
  const {
  return false;
}

// ____________________________________________________________________________
bool osm2ttl::osm::Area::contains(const osm2ttl::osm::Area& other) const {
  return false;
}