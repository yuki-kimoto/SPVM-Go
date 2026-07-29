use Test::More;

use strict;
use warnings;
use lib 't/lib';

use SPVM 'TestCase::Go::Select';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::Select->minimal);

ok(SPVM::TestCase::Go::Select->blocking);

ok(SPVM::TestCase::Go::Select->non_blocking);

ok(SPVM::TestCase::Go::Select->select_closed_channel);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
