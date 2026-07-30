package SPVM::Go::UV::Callback::Close;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Callback::Close - Callback for Close Handle

=head1 Description

C<Go::UV::Callback::Close> in L<SPVM> is the interface for the callback passed to L<uv_close|https://docs.libuv.org/en/v1.x/handle.html#c.uv_close>.

=head1 Usage

  use Go::UV::Callback::Close;

=head1 Interface Methods

=head2 Anonymous method

C<required method : void ($uv_handle : L<Go::UV::Handle|SPVM::Go::UV::Handle>);>

The callback method called when the handle has been closed.

See L<Go::UV::Handle#close|SPVM::Go::UV::Handle/"close"> method for usage.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
