#ifndef MULTIPROCESSING_HPP
#define MULTIPROCESSING_HPP

namespace architecture {

auto get_core_number() -> int;
auto wake_secondary_cores() -> void;

} // namespace architecture

#endif
