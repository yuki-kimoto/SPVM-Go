package SPVM::Go::UV::Callback::Read;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Callback::Read - Callback for Read Operation

=head1 Description

C<Go::UV::Callback::Read> in L<SPVM> is the interface for the callback passed to L<uv_read_start|https://docs.libuv.org/en/v1.x/stream.html#c.uv_read_start>.

=head1 Usage

  use Go::UV::Callback::Read;

=head1 Interface Methods

=head2 Anonymous method

C<required method : void ($uv_stream : L<Go::UV::Handle::Stream|SPVM::Go::UV::Handle::Stream>, $nread : int, $buffer : string);>

The callback method called when data has been received from the stream.

See L<Go::UV::Handle::Stream#read_start|SPVM::Go::UV::Handle::Stream/"read_start"> method for usage.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
