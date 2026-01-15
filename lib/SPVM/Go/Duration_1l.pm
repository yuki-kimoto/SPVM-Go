package SPVM::Go::Duration_1l;

1;

=encoding utf8

=head1 Name

SPVM::Go::Duration_1l - A duration of time (Go-style, long)

=head1 Description

Go::Duration_1l class in L<SPVM> represents the elapsed time between two instants as a long nanosecond count.

This class is defined as a C<mulnum_t>, which means it can be handled efficiently in memory.

=head1 Usage

    use Go::Duration_1l;
    
    # Create from nanoseconds
    my $duration = Go::Duration_1l->new(500_000_000L);
    
    # Create from seconds (double)
    my $duration = Go::Duration_1l->new_from_sec(1.5);

=head1 Fields

C<has nsec : long;>

The number of nanoseconds represented by the duration. For example, 1 second is stored as 1,000,000,000.

=head1 Class Methods

=head2 new

C<static method new : L<Go::Duration_1l|SPVM::Go::Duration_1l> ($nsec : long = 0);>

Creates a new L<Go::Duration_1l|SPVM::Go::Duration_1l> object from the given nanoseconds.

See L<time.Duration|https://pkg.go.dev/time#Duration>.

=head2 new_from_timespec

C<static method new_from_timespec : L<Go::Duration_1l|SPVM::Go::Duration_1l> ($timespec : L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec>);>

Creates a new L<Go::Duration_1l|SPVM::Go::Duration_1l> object from a L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object.

It throws an exception if the C<tv_sec> of the C<$timespec> exceeds the range that can be represented as nanoseconds in a C<long> type.

=head2 new_from_sec

C<static method new_from_sec : L<Go::Duration_1l|SPVM::Go::Duration_1l> ($seconds : double);>

Creates a new L<Go::Duration_1l|SPVM::Go::Duration_1l> object from seconds (C<double>).

=head2 to_timespec

C<static method to_timespec : L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

Converts the L<Go::Duration_1l|SPVM::Go::Duration_1l> object to a L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object.

This method correctly handles negative durations by normalizing the C<tv_nsec> field to a positive value (0 to 999,999,999).

=head2 to_sec

C<static method to_sec : double ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

Returns the duration as a floating point number of seconds.

See L<Duration.Seconds|https://pkg.go.dev/time#Duration.Seconds>.

=head1 See Also

=over 2

=item * L<Go::Time|SPVM::Go::Time>

=item * L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec>

=back

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
