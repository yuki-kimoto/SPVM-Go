package SPVM::Go::Resource::Coro;



1;

=encoding utf8

=head1 Name

SPVM::Go::Resource::Coro - Short Description

=head1 Description

Go::Resource::Coro class in L<SPVM> is a L<resource|SPVM::Document::Resource> class for something.

=head1 Usage

MyClass.config:
  
  my $config = SPVM::Builder::Config->new_c99;
  
  $config->use_resource('Go::Resource::Coro');
  
  $config;

MyClass.c:

  #include "spvm_native.h"
  #include "foo.h"
  
  
  
  int32_t SPVM__MyClass__test(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    // Use functions in foo.h
    
    return 0;
  }
  
  
  
=head1 Details



=head1 Original Product



=head1 Original Product Version



=head1 Language



=head1 Language Standard



=head1 Required Libraries



=head1 Required Linker Flags



=head1 Required Resources



=head1 Header Files



=head1 Source Files



=head1 Compiler Flags



=head1 How to Create Resource



=head2 Donwload



=head2 Extracting Source Files



=head2 Extracting Header Files




=head1 Repository



=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

