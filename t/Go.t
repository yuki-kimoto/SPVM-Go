use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Fn';
use SPVM 'TestCase::Go';

use SPVM 'Go';
use SPVM::Go;
use SPVM 'Fn';

use Time::HiRes;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go->go_minimal);

ok(SPVM::TestCase::Go->go_basic);

ok(SPVM::TestCase::Go->go_die);

ok(SPVM::TestCase::Go->go_extra);

# sleep
{
  my $start = Time::HiRes::time;
  
  ok(SPVM::TestCase::Go->sleep);
  
  my $end = Time::HiRes::time;
  
  my $proc_time = $end - $start;
  
  warn("[Test Output]Proc time:$proc_time");
  
  ok($proc_time > 1.46 && $proc_time < 1.52);
}

ok(SPVM::TestCase::Go->thread_exception);

# Version
{
  my $version_string = SPVM::Fn->get_version_string("Go");
  is($SPVM::Go::VERSION, $version_string);
}

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
