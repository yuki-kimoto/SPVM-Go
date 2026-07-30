package SPVM::Go::UV::Callback::Async;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Callback::Async - Callback for Async Handle

=head1 Description

C<Go::UV::Callback::Async> in L<SPVM> is the interface for the callback passed to L<uv_async_init|https://docs.libuv.org/en/v1.x/async.html#c.uv_async_init>.

=head1 Usage

  use Go::UV::Callback::Async;

=head1 Interface Methods

=head2 Anonymous method

C<required method : void ($uv_async : L<Go::UV::Handle::Async|SPVM::Go::UV::Handle::Async>);>

The callback method called when the async handle is triggered.

See L<Go::UV::Loop#async_init|SPVM::Go::UV::Loop/"async_init"> method for usage.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

