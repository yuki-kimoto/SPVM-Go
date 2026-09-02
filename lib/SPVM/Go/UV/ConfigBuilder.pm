package SPVM::Go::UV::ConfigBuilder;

use parent 'SPVM::Builder::ConfigBuilder';

use strict;
use warnings;

sub build_config {
  
  my ($self) = @_;
  
  my $config = SPVM::Builder::Config->new_c99;
  
  $config->use_resource('Go::Resource::UV');
  
  my $resource_uv =  $config->get_resource('Go::Resource::UV');
  $config->add_define(@{$resource_uv->config->defines});
  $config->add_lib(@{$resource_uv->config->libs});
  
  $config->link_to('Go::UV');
  
  $config;
}

1;

=head1 Name

SPVM::Go::UV::ConfigBuilder - Config Builder for C<libuv>.

=head1 Description

SPVM::Go::UV::ConfigBuilder class is a config builder for C<libuv>.

This class is a Perl module.

=head1 Usage

  my $config_builder = SPVM::Go::UV::ConfigBuilder->new;
  
  my $config = $config_builder->build_config;

=head1 Class Methods

=head2 new

  my $config_builder = SPVM::Go::UV::ConfigBuilder->new;

Create a new L<SPVM::Go::UV::ConfigBuilder> object and returns it.

=head1 Instance Methods

=head2 build_config

  my $config = $config_builder->build_config;

Builds L<SPVM::Builder::Config> object for C<libuv>, and returns it.

=head1 See Also

=over 2

=item * L<SPVM::Go::UV>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
