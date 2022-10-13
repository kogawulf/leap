#include "subcommand.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <eosio/chain/block_log.hpp>
#include <eosio/chain/config.hpp>

namespace bfs = boost::filesystem;
using namespace eosio::chain;

struct blocklog_options {
   std::string blocks_dir = "blocks";
   std::string output_file = "";
   uint32_t first_block = 0;
   uint32_t last_block = std::numeric_limits<uint32_t>::max();
   std::string output_dir;

   // flags
   bool no_pretty_print = false;
   bool as_json_array = false;

   std::optional<block_log_prune_config> blog_keep_prune_conf;
};


class blocklog_actions : public sub_command<blocklog_options> {
public:
   blocklog_actions() : sub_command() {}
   void setup(CLI::App& app);

   enum class action_type : uint32_t {
      ac_default = 0,
      make_index = 1,
      trim_blocklog = 2,
      extract_blocks = 3,
      smoke_test = 4,
      vacuum = 5,
      genesis = 6,
   };

   // callback
   int run_subcommand(action_type at = action_type::ac_default);

   // exception logger
   void lippincott() noexcept;

protected:
   void initialize();
   int trim_blocklog_end(bfs::path block_dir, uint32_t n);
   bool trim_blocklog_front(bfs::path block_dir, uint32_t n);
   bool extract_block_range(bfs::path block_dir, bfs::path output_dir, uint32_t start, uint32_t end);
   void smoke_test();
   int do_vacuum();
   int do_genesis();
   void read_log();
};