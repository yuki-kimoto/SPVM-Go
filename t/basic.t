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

ok(SPVM::TestCase::Go->test);

ok(SPVM::TestCase::Go->test_schedule);

# Version
{
  my $version_string = SPVM::Fn->get_version_string("Go");
  is($SPVM::Go::VERSION, $version_string);
}

done_testing;
