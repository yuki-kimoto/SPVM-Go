use Test::More;

use strict;
use warnings;
use lib 't/lib';

use SPVM 'TestCase::Go::Poll';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::Poll->basic);
ok(SPVM::TestCase::Go::Poll->parallel);
ok(SPVM::TestCase::Go::Poll->timeout);
ok(SPVM::TestCase::Go::Poll->gosched_io_cancel);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
