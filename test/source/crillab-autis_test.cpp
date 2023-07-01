#include <string>

#include "crillab-autis/crillab-autis.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is crillab-autis", "[library]")
{
  auto const exported = exported_class {};
  REQUIRE(std::string("crillab-autis") == exported.name());
}
