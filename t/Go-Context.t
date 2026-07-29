use Test::More;

use strict;
use warnings;
use lib 't/lib';

use TestUtil::ServerRunner;

use SPVM 'TestCase::Go::Context';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::Context->background);

ok(SPVM::TestCase::Go::Context->with_cancel);

ok(SPVM::TestCase::Go::Context->with_cancel_cause);

ok(SPVM::TestCase::Go::Context->without_cancel);

ok(SPVM::TestCase::Go::Context->with_value);

ok(SPVM::TestCase::Go::Context->with_deadline);

ok(SPVM::TestCase::Go::Context->with_deadline_canceled_halfway);

ok(SPVM::TestCase::Go::Context->with_deadline_cause);

ok(SPVM::TestCase::Go::Context->with_timeout);

ok(SPVM::TestCase::Go::Context->with_timeout_sec);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
