use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'TestCase::Go';

use SPVM 'Go';
use SPVM::Go;
use SPVM 'Fn';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

ok(SPVM::TestCase::Go->go_minimal);

ok(SPVM::TestCase::Go->go);

ok(SPVM::TestCase::Go->channel);

ok(SPVM::TestCase::Go->select);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

# Version
{
  my $version_string = SPVM::Fn->get_version_string("Go");
  is($SPVM::Go::VERSION, $version_string);
}

done_testing;
