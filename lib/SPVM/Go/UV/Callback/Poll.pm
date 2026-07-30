package SPVM::Go::UV::Callback::Poll;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Callback::Poll - Callback for Poll Handle

=head1 Description

C<Go::UV::Callback::Poll> in L<SPVM> is the interface for the callback passed to L<uv_poll_start|https://docs.libuv.org/en/v1.x/poll.html#c.uv_poll_start>.

=head1 Usage

  use Go::UV::Callback::Poll;

=head1 Interface Methods

=head2 Anonymous method

C<required method : void ($uv_poll : L<Go::UV::Handle::Poll|SPVM::Go::UV::Handle::Poll>, $status : int, $events : int);>

The callback method called when the poll handle detects events or an error occurs.

See L<Go::UV::Handle::Poll#start|SPVM::Go::UV::Handle::Poll/"start"> method for usage.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
