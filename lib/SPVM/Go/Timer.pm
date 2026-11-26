=head1 Name

SPVM::Go::Timer - Timers in Go

=head1 Description

L<Go::Timer|SPVM::Go::Timer> class in L<SPVM> provides timers for waiting and channel-based expiration notifications.

=head1 Usage

  use Go;
  use Go::Timer;
  
  my $timer = Go::Timer->new_timer_sec(1.0);
  my $time = $timer->c->read;
  
  Go::Timer->sleep_sec(0.5);

=head1 Class Methods

=head2 new

C<static method new : L<Go::Timer|SPVM::Go::Timer> ($options : object[] = undef);>

Creates a new L<Go::Timer|SPVM::Go::Timer> object given the options $options.

Options:

=over 2

=item * C<duration_nsec> : C<long>

The timer duration in nanoseconds. This option is required.

=back

Exceptions:

The C<duration_nsec> option must be specified. Otherwise an exception is thrown.

=head2 sleep

C<static method sleep : void ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

Sleeps for the duration $duration.

=head2 sleep_sec

C<static method sleep_sec : void ($seconds : double);>

Same as L</"sleep">, but sleeps for the seconds $seconds.

=head2 after

C<static method after : L<Go::Channel|SPVM::Go::Channel> ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

Waits for the duration $duration and returns a channel that receives the current L<Go::Time|SPVM::Go::Time> when the timer expires.

=head2 after_sec

C<static method after_sec : L<Go::Channel|SPVM::Go::Channel> ($seconds : double);>

Same as L</"after">, but waits for the seconds $seconds.

=head2 new_timer

C<static method new_timer : L<Go::Timer|SPVM::Go::Timer> ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

Creates a new L<Go::Timer|SPVM::Go::Timer> object given the duration $duration.

=head2 new_timer_sec

C<static method new_timer_sec : L<Go::Timer|SPVM::Go::Timer> ($seconds : double);>

Same as L</"new_timer">, but creates a timer for the seconds $seconds.

=head1 Instance Methods

=head2 c

C<method c : L<Go::Channel|SPVM::Go::Channel> ();>

Returns the channel on which the expiration time is sent.

=head2 stop

C<method stop : int ();>

Stops the timer, closes the underlying libuv timer handle and channel, and returns 1 if stopped, or 0 if already stopped.

=head1 See Also

=over 2

=item * L<Go|SPVM::Go>

=item * L<Go::Time|SPVM::Go::Time>

=item * L<Go::Duration_1l|SPVM::Go::Duration_1l>

=item * L<Go::Channel|SPVM::Go::Channel>

=back

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
