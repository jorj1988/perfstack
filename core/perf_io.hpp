#pragma once
#include "perf.hpp"

namespace perf
{

/// Writer for producing json data from a perf types
class json_writer
{
public:
  /// Dump [e] to json in [out]
  void dump(const context::event &e, string &out, const char *tab);
  /// Dump [ctx] to json and return
  string dump(const context &ctx);

  void write(const context &ctx, const char *filename);
};

}
