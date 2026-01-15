use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Fn';
use TestUtil::ServerRunner;

use SPVM 'TestCase::Go::Time';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Go::Time->basic);

ok(SPVM::TestCase::Go::Time->new_from_unix);

ok(SPVM::TestCase::Go::Time->now);

ok(SPVM::TestCase::Go::Time->add);

ok(SPVM::TestCase::Go::Time->to_timespec);

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
