package SPVM::Go::UV::Handle::Timer;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Handle::Timer - Timer Handle for libuv

=head1 Description

C<Go::UV::Handle::Timer> in L<SPVM> represents the timer handle for L<libuv|https://libuv.org/>, corresponding to the C<uv_timer_t> structure.

=head1 Super Class

L<Go::UV::Handle|SPVM::Go::UV::Handle>

=head1 Usage

  use Go::UV::Handle::Timer;
  
  my $timer = Go::UV::Handle::Timer->new;

=head1 Fields

=head2 timer_cb

C<has timer_cb : rw L<Go::UV::Callback::Timer|SPVM::Go::UV::Callback::Timer>;>

The callback called when the timer timeout expires.

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Handle::Timer|SPVM::Go::UV::Handle::Timer> ();>

Creates a new L<Go::UV::Handle::Timer|SPVM::Go::UV::Handle::Timer> object, and returns it.

=head1 Instance Methods

=head2 start

C<method start : void ($cb : L<Go::UV::Callback::Timer|SPVM::Go::UV::Callback::Timer>, $timeout_msec : long, $interval_msec : long = 0);>

Starts the timer with a timeout of C<$timeout_msec> milliseconds and a repeat interval of C<$interval_msec> milliseconds.

The callback C<$cb> is stored in L</"timer_cb"> field.

The callback C<$cb> is invoked when the timer timeout expires.

This method calls the L<uv_timer_start|https://docs.libuv.org/en/v1.x/timer.html#c.uv_timer_start> function internally.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
