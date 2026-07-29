use Test::More;

use strict;
use warnings;
use lib 't/lib';

use SPVM 'TestCase::Go::Goroutine';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::Goroutine->transfer_minimal);

ok(SPVM::TestCase::Go::Goroutine->transfer_create_many_objects);

ok(SPVM::TestCase::Go::Goroutine->transfer);

ok(SPVM::TestCase::Go::Goroutine->die);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
