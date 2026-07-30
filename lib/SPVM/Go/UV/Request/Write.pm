package SPVM::Go::UV::Request::Write;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Request::Write - Write Request for libuv

=head1 Description

C<Go::UV::Request::Write> in L<SPVM> represents the write request for L<libuv|https://libuv.org/>, corresponding to the C<uv_write_t> structure. 

=head1 Usage

  use Go::UV::Request::Write;
  
  my $req_write = Go::UV::Request::Write->new;

=head1 Super Class

L<Go::UV::Request|SPVM::Go::UV::Request>.

=head1 Fields

=head2 write_cb

C<has write_cb : rw L<Go::UV::Callback::Write|SPVM::Go::UV::Callback::Write>;>

The callback called when the write request has completed.

=head2 write_buffer

C<has write_buffer : rw string;>

The buffer associated with the write request.

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Request::Write|SPVM::Go::UV::Request::Write> ();>

Creates a new L<Go::UV::Request::Write|SPVM::Go::UV::Request::Write> object, and returns it.

=head1 Instance Methods

=head2 write

C<method write : void ($uv_stream : L<Go::UV::Handle::Stream|SPVM::Go::UV::Handle::Stream>, $buffer : string, $buffer_length : int, $cb : L<Go::UV::Callback::Write|SPVM::Go::UV::Callback::Write>, $buffer_offset : int = 0);>

Writes data from $buffer with length $buffer_length and offset $buffer_offset to the stream $uv_stream. 

The callback $cb is stored in L</"write_cb"> field. The buffer $buffer is stored in L</"write_buffer"> field.

The callback $cb is invoked when the write operation completes.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
