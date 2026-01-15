package SPVM::L<Go::Time|SPVM::Go::Time>;



1;

=encoding utf8

=head1 Name

SPVM::Go::Time - Time management with monotonic time support (Go-style)

=head1 Description

Go::Time class in L<SPVM> is a time management class based on the implementation of C<time.Time> in the Go programming language.

It internally maintains both wall clock time (C<CLOCK_REALTIME>) and monotonic time (C<CLOCK_MONOTONIC>). This dual-structure ensures that time measurements for durations remain accurate even if the system clock is adjusted.

=head1 Usage

  use Go::Time;
  
  # Get current time
  my $now = Go::Time->now;
  
  # 1.5 seconds later
  my $later = $now->add_sec(1.5);

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Class Methods

=head2 NANOSECOND

C<static method NANOSECOND : long ();>

Returns 1 nanosecond.

See L<Go Time Constants|https://pkg.go.dev/time#pkg-constants>.

=head2 MICROSECOND

C<static method MICROSECOND : long ();>

Returns 1,000 nanoseconds.

=head2 MILLISECOND

C<static method MILLISECOND : long ();>

Returns 1,000,000 nanoseconds.

=head2 SECOND

C<static method SECOND : long ();>

Returns 1,000,000,000 nanoseconds.

=head2 MINUTE

C<static method MINUTE : long ();>

Returns 60,000,000,000 nanoseconds.

=head2 HOUR

C<static method HOUR : long ();>

Returns 3,600,000,000,000 nanoseconds.

=head1 CLASS METHODS

=head2 new_from_unix

C<static method new_from_unix : L<Go::Time|SPVM::Go::Time> ($sec : long = 0, $nsec : long = 0);>

Creates a new L<Go::Time|SPVM::Go::Time> object from Unix seconds and nanoseconds.
See L<time.Unix|https://pkg.go.dev/time#Unix>.

=head2 now

C<static method now : L<Go::Time|SPVM::Go::Time> ();>

Creates a new L<Go::Time|SPVM::Go::Time> object representing the current system time. It captures both the wall clock and the monotonic clock.
See L<time.Now|https://pkg.go.dev/time#Now>.

=head1 Instance Methods

=head2 unix

C<method unix : long ();>

Returns the Unix "seconds" component of the time.
See L<Time.Unix|https://pkg.go.dev/time#Time.Unix>.

=head2 nanosecond

C<method nanosecond : long ();>

Returns the nanoseconds component within the second (0-999,999,999).
See L<Time.Nanosecond|https://pkg.go.dev/time#Time.Nanosecond>.

=head2 unix_nano

C<method unix_nano : long ();>

Returns the total elapsed time since the Unix epoch in nanoseconds.
See L<Time.UnixNano|https://pkg.go.dev/time#Time.UnixNano>.

=head2 add

C<method add : L<Go::Time|SPVM::Go::Time> ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

Returns a new L<Go::Time|SPVM::Go::Time> object with the given duration added.
See L<Time.Add|https://pkg.go.dev/time#Time.Add>.

=head2 add_sec

C<method add_sec : L<Go::Time|SPVM::Go::Time> ($seconds : double);>

A helper method that adds the specified number of seconds (as a C<double>) and returns a new L<Go::Time|SPVM::Go::Time> object.

=head2 sub

C<method sub : L<Go::Duration_1l|SPVM::Go::Duration_1l> ($go_time : L<Go::Time|SPVM::Go::Time>);>

Returns the duration C<t - go_time>. It handles monotonic clocks correctly.
See L<Time.Sub|https://pkg.go.dev/time#Time.Sub>.

=head2 equal

C<method equal : int ($go_time : L<Go::Time|SPVM::Go::Time>);>

Reports whether the time and C<go_time> represent the same instant.
See L<Time.Equal|https://pkg.go.dev/time#Time.Equal>.

=head2 after

C<method after : int ($go_time : L<Go::Time|SPVM::Go::Time>);>

Reports whether the time instant is after C<go_time>.
See L<Time.After|https://pkg.go.dev/time#Time.After>.

=head2 before

C<method before : int ($go_time : L<Go::Time|SPVM::Go::Time>);>

Reports whether the time instant is before C<go_time>.
See L<Time.Before|https://pkg.go.dev/time#Time.Before>.

=head2 clone

C<method clone : L<Go::Time|SPVM::Go::Time> ();>

Returns a deep copy of the L<Go::Time|SPVM::Go::Time> object. This method implements L<Cloneable|SPVM::Cloneable>.

=head2 to_timespec

C<method to_timespec : L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> ();>

Converts the internal time to a L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object.

=head1 See Also

=over 2

=item * L<Go::Duration_1l|SPVM::Go::Duration_1l>

=back


=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

