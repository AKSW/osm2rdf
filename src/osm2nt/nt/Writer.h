// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#ifndef OSM2NT_NT_WRITER_H_
#define OSM2NT_NT_WRITER_H_

#include <ostream>

#include "osmium/geom/wkt.hpp"
#include "osmium/osm/area.hpp"
#include "osmium/osm/location.hpp"
#include "osmium/osm/node.hpp"
#include "osmium/osm/relation.hpp"
#include "osmium/osm/tag.hpp"
#include "osmium/osm/way.hpp"

#include "osm2nt/nt/Triple.h"

namespace osm2nt {
namespace nt {

class Writer {
 public:
  explicit Writer(std::ostream* os);
  void writeTriple(const osm2nt::nt::Triple& t);
  void writeOsmArea(const osmium::Area& area);
  void writeOsmBox(const osm2nt::nt::Subject* s,
                   const osm2nt::nt::Predicate* p, const osmium::Box& box);
  void writeOsmLocation(const osm2nt::nt::Subject* s,
                        const osmium::Location& l);
  void writeOsmNode(const osmium::Node& node);
  void writeOsmRelation(const osmium::Relation& relation);
  void writeOsmRelationMembers(const osm2nt::nt::Subject* s,
                               const osmium::RelationMemberList& members);
  void writeOsmTag(const osm2nt::nt::Subject* s, const osmium::Tag& tag);
  void writeOsmTagList(const osm2nt::nt::Subject* s,
                       const osmium::TagList& tags);
  void writeOsmWay(const osmium::Way& way);
  void writeOsmWayNodeList(const osm2nt::nt::Subject* s,
                           const osmium::WayNodeList& nodes);
 protected:
  std::ostream* out;
  osmium::geom::WKTFactory<> wktFactory;
};

}  // namespace nt
}  // namespace osm2nt

#endif  // OSM2NT_NT_WRITER_H_
