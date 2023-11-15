package SPVM::Go;

our $VERSION = "0.002";

1;

=head1 Name

SPVM::Go - Goroutines of The Go Programming Language

=head1 Description

The Go class of L<SPVM> has methods to create goroutines and manipulate channels.

Goroutines and channels are features of the Go programming language.

=head1 Usage

  use Go;
  
  Go->go(method : void () {
    
    my $ch = Go->make;
    
    Go->go([has ch : Go::Channel = $ch] method : void () {
      
      my $ch = $self->{ch};
      
      $ch->write(1);
    });
    
    my $ok = 0;
    
    my $value = (int)$ch->read(\$ok);
  });
  
  Go->gosched;

=head1 Class Methods

=head2 go

C<static method go : void ($task : L<Callback|SPVM::Callback>);>

Creates a goroutine.

=head2 make

C<static method make : L<Go::Channel|SPVM::Go::Channe> ($capacity : int = 0);>

Creates a channel(L<Go::Channel|SPVM::Go::Channe>) given the capacity of its buffer $capacity.

=head2 new_select

C<static method new_select : L<Go::Select|SPVM::Go::Select> ();>

Creats a new L<Go::Select|SPVM::Go::Select> object.

=head2 gosched

C<static method gosched : void ();>

Suspends the current goroutine.

The control is transferred to the scheduler.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

=head2 gosched_io_read

C<static method gosched_io_read : void ($fd : int, $timeout_ref : double[] = undef);>

Suspends the current goroutine for IO reading given the file descriptor $fd and the value of the timeout reference $timeout_ref.

The control is transferred to the scheduler.

The value of $timeout_ref is updated by the rest timeout. If it is less than 0, timeout has occured.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

=head2 gosched_io_write

C<static method gosched_io_write : void ($fd : int, $timeout_ref : double[] = undef);>

Suspends the current goroutine for IO writing given the file descriptor $fd and the value of the timeout reference $timeout_ref.

The control is transferred to the scheduler.

The value of $timeout_ref is updated by the rest timeout. If it is less than 0, timeout has occured.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

=head2 sleep

C<static method sleep : void ($seconds : double = 0);>

Sleeps the seconds $seconds.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

=head1 Repository

L<SPVM::Go - Github|https://github.com/yuki-kimoto/SPVM-Go>

=head1 See Also

=over 2

=item * L<The Go Programming Language|https://go.dev/> - SPVM::Go is a porting of goroutines.

=item * L<Coro> - SPVM::Go uses coroutines.

=back

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

