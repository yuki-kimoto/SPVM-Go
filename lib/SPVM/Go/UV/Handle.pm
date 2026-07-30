package SPVM::Go::UV::Handle;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Handle - Base Handle for libuv

=head1 Description

C<Go::UV::Handle> in L<SPVM> represents the base handle for L<libuv|https://libuv.org/>, corresponding to the C<uv_handle_t> structure.

=head1 Usage

  use Go::UV::Handle;

=head1 Fields

=head2 close_cb

C<has close_cb : rw L<Go::UV::Callback::Close|SPVM::Go::UV::Callback::Close>;>

The callback called when the handle has been closed.

=head2 loop

C<has loop : ro L<Go::UV::Loop|SPVM::Go::UV::Loop>;>

The event loop associated with the handle.

=head1 Instance Methods

=head2 close

C<method close : void ($close_cb : L<Go::UV::Callback::Close|SPVM::Go::UV::Callback::Close> = undef);>

Request the handle to be closed. The callback $close_cb is invoked when the handle has been closed. 

The callback $close_cb is stored in L</"close_cb"> field.

This method calls the L<uv_close|https://docs.libuv.org/en/v1.x/handle.html#c.uv_close> function.

=head2 get_type

C<method get_type : int ();>

Returns the handle type.

This method calls the L<uv_handle_get_type|https://docs.libuv.org/en/v1.x/handle.html#c.uv_handle_get_type> function.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
