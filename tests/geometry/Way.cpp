// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#include "osm2ttl/geometry/Way.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "gtest/gtest.h"

namespace osm2ttl::geometry {

// ____________________________________________________________________________
osm2ttl::geometry::Way getDefaultObject() { return osm2ttl::geometry::Way(); }

// ____________________________________________________________________________
osm2ttl::geometry::Way getFilledObject() {
  osm2ttl::geometry::Way obj;
  obj.push_back(Location{0, 0});
  obj.push_back(Location{5, 0});
  obj.push_back(Location{0, 5});
  obj.push_back(Location{10, 10});
  return obj;
}

// ____________________________________________________________________________
TEST(GEOMETRY_Way, equalsOperator) {
  osm2ttl::geometry::Way o1;
  o1.push_back(Location{0, 0});
  o1.push_back(Location{5, 0});
  o1.push_back(Location{0, 5});

  osm2ttl::geometry::Way o2;
  o2.push_back(Location{0, 0});
  o2.push_back(Location{0, 5});
  o2.push_back(Location{5, 0});

  osm2ttl::geometry::Way o3;
  o3.push_back(Location{0, 0});
  o3.push_back(Location{0, 5});

  ASSERT_TRUE(o1 == o1);
  ASSERT_FALSE(o1 == o2);
  ASSERT_FALSE(o1 == o3);

  ASSERT_FALSE(o2 == o1);
  ASSERT_TRUE(o2 == o2);
  ASSERT_FALSE(o2 == o3);

  ASSERT_FALSE(o3 == o1);
  ASSERT_FALSE(o3 == o2);
  ASSERT_TRUE(o3 == o3);
}

// ____________________________________________________________________________
TEST(GEOMETRY_Way, notEqualsOperator) {
  osm2ttl::geometry::Way o1;
  o1.push_back(Location{0, 0});
  o1.push_back(Location{5, 0});
  o1.push_back(Location{0, 5});

  osm2ttl::geometry::Way o2;
  o2.push_back(Location{0, 0});
  o2.push_back(Location{0, 5});
  o2.push_back(Location{5, 0});

  osm2ttl::geometry::Way o3;
  o3.push_back(Location{0, 0});
  o3.push_back(Location{0, 5});

  ASSERT_FALSE(o1 != o1);
  ASSERT_TRUE(o1 != o2);
  ASSERT_TRUE(o1 != o3);

  ASSERT_TRUE(o2 != o1);
  ASSERT_FALSE(o2 != o2);
  ASSERT_TRUE(o2 != o3);

  ASSERT_TRUE(o3 != o1);
  ASSERT_TRUE(o3 != o2);
  ASSERT_FALSE(o3 != o3);
}

// ____________________________________________________________________________
TEST(GEOMETRY_Way, serializationBinary) {
  std::stringstream buffer;

  osm2ttl::geometry::Way origDefaultObject = getDefaultObject();
  osm2ttl::geometry::Way origFilledObject = getFilledObject();
  osm2ttl::geometry::Way loadedDefaultObject;
  osm2ttl::geometry::Way loadedFilledObject;

  // Store and load
  boost::archive::binary_oarchive oa(buffer);
  oa << origDefaultObject;
  oa << origFilledObject;
  // std::cerr << buffer.str() << std::endl;
  boost::archive::binary_iarchive ia(buffer);
  ia >> loadedDefaultObject;
  ia >> loadedFilledObject;

  // Compare
  ASSERT_TRUE(origDefaultObject == loadedDefaultObject);
  ASSERT_TRUE(origFilledObject == loadedFilledObject);
}

// ____________________________________________________________________________
TEST(GEOMETRY_Way, serializationText) {
  std::stringstream buffer;

  osm2ttl::geometry::Way origDefaultObject = getDefaultObject();
  osm2ttl::geometry::Way origFilledObject = getFilledObject();
  osm2ttl::geometry::Way loadedDefaultObject;
  osm2ttl::geometry::Way loadedFilledObject;

  // Store and load
  boost::archive::text_oarchive oa(buffer);
  oa << origDefaultObject;
  oa << origFilledObject;
  // std::cerr << buffer.str() << std::endl;
  boost::archive::text_iarchive ia(buffer);
  ia >> loadedDefaultObject;
  ia >> loadedFilledObject;

  // Compare
  ASSERT_TRUE(origDefaultObject == loadedDefaultObject);
  ASSERT_TRUE(origFilledObject == loadedFilledObject);
}

}  // namespace osm2ttl::geometry