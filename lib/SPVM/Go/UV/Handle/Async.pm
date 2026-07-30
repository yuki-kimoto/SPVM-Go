package SPVM::Go::UV::Handle::Async;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Handle::Async - Async Handle for libuv

=head1 Description

C<Go::UV::Handle::Async> in L<SPVM> represents the async handle for L<libuv|https://libuv.org/>, corresponding to the C<uv_async_t> structure.

=head1 Super Class

L<Go::UV::Handle|SPVM::Go::UV::Handle>

=head1 Usage

  use Go::UV::Handle::Async;
  
  my $async = Go::UV::Handle::Async->new;

=head1 Fields

=head2 async_cb

C<has async_cb : rw L<Go::UV::Callback::Async|SPVM::Go::UV::Callback::Async>;>

The callback called when the async handle has been awakened.

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Handle::Async|SPVM::Go::UV::Handle::Async> ();>

Creates a new L<Go::UV::Handle::Async|SPVM::Go::UV::Handle::Async> object, and returns it.

=head1 Instance Methods

=head2 send

C<method send : void ();>

Awakens the async handle.

This method calls the L<uv_async_send|https://docs.libuv.org/en/v1.x/async.html#c.uv_async_send> function.

Exceptions:

If uv_async_send fails, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
