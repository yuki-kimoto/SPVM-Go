package SPVM::Go::UV::Handle::Poll;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Handle::Poll - Poll Handle for libuv

=head1 Description

C<Go::UV::Handle::Poll> in L<SPVM> represents the poll handle for L<libuv|https://libuv.org/>, corresponding to the C<uv_poll_t> structure.

=head1 Super Class

L<Go::UV::Handle|SPVM::Go::UV::Handle>

=head1 Usage

  use Go::UV::Handle::Poll;
  
  my $poll = Go::UV::Handle::Poll->new;

=head1 Fields

=head2 poll_cb

C<has poll_cb : rw L<Go::UV::Callback::Poll|SPVM::Go::UV::Callback::Poll>;>

The callback called when file descriptor events occur.

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Handle::Poll|SPVM::Go::UV::Handle::Poll> ();>

Creates a new L<Go::UV::Handle::Poll|SPVM::Go::UV::Handle::Poll> object, and returns it.

=head1 Instance Methods

=head2 start

C<method start : void ($cb : L<Go::UV::Callback::Poll|SPVM::Go::UV::Callback::Poll>, $events : int);>

Starts polling the file descriptor for events specified by C<$events> with the callback C<$cb>. 

The callback C<$cb> is stored in L</"poll_cb"> field.

The callback C<$cb> is invoked when the specified events occur.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
