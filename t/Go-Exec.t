use Test::More;

use strict;
use warnings;
use lib 't/lib';

use SPVM 'TestCase::Go::OS::Exec';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::OS::Exec->basic);

ok(SPVM::TestCase::Go::OS::Exec->context_done);

ok(SPVM::TestCase::Go::OS::Exec->context_deadline);

ok(SPVM::TestCase::Go::OS::Exec->context_extra);

ok(SPVM::TestCase::Go::OS::Exec->stdout);

ok(SPVM::TestCase::Go::OS::Exec->stderr);

ok(SPVM::TestCase::Go::OS::Exec->extra_files);

ok(SPVM::TestCase::Go::OS::Exec->env);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
