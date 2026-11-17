use Test::More;

use strict;
use warnings;
use lib 't/lib';

use File::Temp ();

use SPVM 'TestCase::Go::Fsnotify';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  {
    my $tmp_dir = File::Temp->newdir;
    my $tmp_dir_path = "$tmp_dir";
    # Convert short path to long path on Windows to avoid libuv fs-event assertion failure
    if ($^O eq 'MSWin32') {
      require Win32;
      $tmp_dir_path = Win32::GetLongPathName($tmp_dir_path);
    }
    ok(SPVM::TestCase::Go::Fsnotify->basic($tmp_dir_path));
  }
}

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
