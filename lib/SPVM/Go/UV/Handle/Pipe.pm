package SPVM::Go::UV::Handle::Pipe;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Handle::Pipe - Pipe Handle for libuv

=head1 Description

C<Go::UV::Handle::Pipe> in L<SPVM> represents the pipe handle for L<libuv|https://libuv.org/>, corresponding to the C<uv_pipe_t> structure.

=head1 Super Class

L<Go::UV::Handle::Stream|SPVM::Go::UV::Handle::Stream>

=head1 Usage

  use Go::UV::Handle::Pipe;
  
  my $pipe = Go::UV::Handle::Pipe->new;

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Handle::Pipe|SPVM::Go::UV::Handle::Pipe> ();>

Creates a new L<Go::UV::Handle::Pipe|SPVM::Go::UV::Handle::Pipe> object, and returns it.

=head1 Instance Methods

=head2 open

C<method open : void ($fd : int);>

Associates an existing file descriptor C<$fd> with the pipe handle.

This method calls the L<uv_pipe_open|https://docs.libuv.org/en/v1.x/pipe.html#c.uv_pipe_open> function.

Exceptions:

If uv_pipe_open fails, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
