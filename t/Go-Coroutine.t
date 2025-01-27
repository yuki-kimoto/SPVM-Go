use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Fn';
use SPVM 'TestCase::Go::Coroutine';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::Coroutine->transfer_minimal);

ok(SPVM::TestCase::Go::Coroutine->transfer_create_many_objects);

ok(SPVM::TestCase::Go::Coroutine->transfer);

ok(SPVM::TestCase::Go::Coroutine->die);

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
