#ifndef DESCRIPTOR_INTERFACE_HPP
#define DESCRIPTOR_INTERFACE_HPP

#include "../lib/array.hpp"
#include "../lib/span.hpp"
#include "block_cache.hpp"
#include "file.hpp"
#include "inode_cache.hpp"
#include "pipe_interface.hpp"
#include "sleep_lock.hpp"
#include "spin_lock.hpp"

#include <cstddef>
#include <cstdint>

namespace file {

enum class file_descriptor_type_t { unused, inode, pipe, input, output, socket };

enum class open_mode_t { do_not_create, create_directory, create_file };

struct file_descriptor_status_t {
    file_descriptor_type_t file_descriptor_type;
    file::inode_type_t inode_type;
    size_t size;
    bool readable;
    bool writable;
};

struct file_descriptor_t {
    file_descriptor_type_t type;
    bool readable;
    bool writable;
    inode_index_t index_of_inode_on_disk;
    size_t read_offset;
    size_t write_offset;
    int pipe_index;
    int socket_index;
};

struct file_descriptor_table_t {
    synchronization::sleep_lock lock;
    array_t<file_descriptor_t, descriptor_interface_constants::maximum_number_of_file_descriptors_per_process> data =
        {};
};

class descriptor_interface {
public:
    static auto get() -> descriptor_interface & {
        static descriptor_interface instance;
        return instance;
    }

    auto initialize_file_descriptors(uint64_t process_id) -> void;
    auto remove_file_descriptors(uint64_t process_id) -> void;
    auto clone_file_descriptors(int from_process_id, int to_process_id) -> void;

    auto open(uint64_t process_id, path_name_t path, bool readable, bool writable, open_mode_t mode) -> int;
    auto close(uint64_t process_id, uint64_t file_descriptor_index) -> void;
    auto read(uint64_t process_id, uint64_t file_descriptor_index, span_t<byte_t> buffer) -> size_t;
    auto write(uint64_t process_id, uint64_t file_descriptor_index, span_t<byte_t> buffer) -> size_t;

    auto seek(uint64_t process_id, uint64_t file_descriptor_index, bool read, size_t new_read_offset, bool write,
              size_t new_write_offset) -> void;
    auto link(uint64_t process_id, uint64_t file_descriptor_index, path_name_t new_path) -> bool;
    auto unlink(uint64_t process_id, uint64_t file_descriptor_index, path_name_t path) -> void;

    auto status(uint64_t process_id, uint64_t file_descriptor_index) -> file_descriptor_status_t;
    auto copy(uint64_t file_descriptor_index) -> int;

    auto socket(bool connected) -> int;
    auto connect(uint64_t file_descriptor_index,
                 networking::internet_protocol_address_t destination_internet_protocol_address,
                 networking::port_number_t destination_port_number) -> bool;
    auto bind(uint64_t file_descriptor_index, networking::port_number_t source_port_number) -> bool;
    auto listen(uint64_t file_descriptor_index) -> bool;
    auto accept(uint64_t file_descriptor_index) -> int;
    auto receive(uint64_t file_descriptor_index, span_t<byte_t> buffer,
                 networking::internet_protocol_address_t *internet_protocol_address_address,
                 networking::port_number_t *port_number_address) -> size_t;
    auto transmit(uint64_t file_descriptor_index, span_t<byte_t> buffer,
                  networking::internet_protocol_address_t internet_protocol_address,
                  networking::port_number_t port_number) -> size_t;
    auto pipe(array_t<int32_t, 2> *file_descriptors) -> bool;

    auto recover() -> void;

    descriptor_interface(const descriptor_interface &) = delete;
    auto operator=(const descriptor_interface &) -> descriptor_interface & = delete;
    descriptor_interface(descriptor_interface &&) = delete;
    auto operator=(descriptor_interface &&) -> descriptor_interface & = delete;

private:
    file::block_cache_t block_cache;
    file::inode_cache_t inode_cache{&block_cache};
    process::pipe_interface pipes;
    synchronization::sleep_lock directory_lock;
    array_t<file_descriptor_table_t, process::thread_scheduler_constants::maximum_number_of_processes>
        file_descriptors{};
    synchronization::spin_lock lock;
    bool initialized = false;

    synchronization::sleep_lock test_lock;
    int number_of_completed_tests = 0;

    void print_directory_tree(uint32_t index_of_inode_on_disk, int level);
    void print_state();

    descriptor_interface() = default;
    ~descriptor_interface() = default;
};

} // namespace file

#endif
