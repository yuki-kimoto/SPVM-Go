package SPVM::Go;

our $VERSION = "0.047";

1;

=head1 Name

SPVM::Go - Goroutines of The Go Programming Language

=head1 Description

Go class in L<SPVM> provide goroutines and channels in Go language.

=head1 Usage

  use Go;
  
  Go->go(method : void () {
    
    my $ch = Go->make;
    
    Go->go([$ch : ,] method : void () {
      
      $ch->write(1);
    });
    
    my $value = (int)$ch->read;
  });
  
  Go->gosched;

=head1 Details

L<Go|SPVM::Go> class provides a runtime environment that implements Goroutines
and Channels, mimicking the behavior of the Go programming language.

Unlike standard polling-based implementations that consume CPU cycles while
waiting, this module leverages the high-performance event loop provided by
L<libuv|https://libuv.org/>.

=head2 Efficient Waiting via Event Loop

When a Goroutine performs an operation that requires waiting, such as:

=over 2

=item * Timer-based waiting (e.g., C<time.sleep>)

=item * I/O operations (e.g., reading/writing sockets)

=item * Channel communication (waiting for data or space)

=back

The scheduler does not use busy-waiting or idle-looping. Instead, it registers
the operation with the libuv event loop and suspends the Goroutine.

The event loop puts the process into a low-power wait state, consuming virtually
zero CPU resources while waiting for the OS to signal that the event is ready.
Once the event occurs (e.g., a timer expires, data arrives, or a channel becomes
ready), the event loop notifies the scheduler, which then resumes the Goroutine
efficiently.

This architecture ensures high scalability and low CPU usage, allowing for
thousands of concurrent Goroutines to coexist within a single SPVM process
without significant overhead.

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

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_read : void ($fd : int, $timeout_duration : Go::Duration_1l = undef);>

Suspends the current goroutine for IO reading given the file descriptor $fd and the value of the timeout nanosecnods $timeout_duration.

The control is transferred to the scheduler.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

$timeout must be greater than 0. Otherwise an exception is thrown.

$timeout must be less than or equal to Fn->INT_MAX. Otherwise an exception is thrown.

If IO timeout occurs, an exception is thrown set C<eval_error_id> to the basic type ID of the L<Go::Error::IOTimeout|SPVM::Go::Error::IOTimeout> class.

=head2 gosched_io_read_sec

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_read_sec : void ($fd : int, $timeout_sec : double = 0);>

Same as L<"/gosched_io_read">, but the timeout is the seconds $timeout_sec.

=head2 gosched_io_write

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_write : void ($fd : int, $timeout_duration : Go::Duration_1l = undef);>

Suspends the current goroutine for IO writing given the file descriptor $fd and the timeout $timeout.

The control is transferred to the scheduler.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

$timeout must be greater than 0. Otherwise an exception is thrown.

$timeout must be less than or equal to Fn->INT_MAX. Otherwise an exception is thrown.

If IO timeout occurs, an exception is thrown set C<eval_error_id> to the basic type ID of the L<Go::Error::IOTimeout|SPVM::Go::Error::IOTimeout> class.

=head2 gosched_io_write_sec

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_write_sec : void ($fd : int, $timeout_sec : double = 0);>

Same as L<"/gosched_io_write">, but the timeout is the seconds $timeout_sec.

=head2 gosched_poll_write

C<static method gosched_poll_write : void ($context : L<Go::Context|SPVM::Go::Context>, $fd : int);>

Suspends the current goroutine for poll writing given the context $context and the file descriptor $fd.

=head2 gosched_pipe_read_v2

C<static method gosched_pipe_read_v2 : int ($context : L<Go::Context|SPVM::Go::Context>, $fd : int, $string : mutable string, $length : int = -1, $offset : int = 0);>

Suspends the current goroutine for pipe reading given the context $context, the file descriptor $fd, the buffer $string, the length $length, and the offset $offset.

Note: C<gosched_pipe_read> will be replaced by the implementation of C<gosched_pipe_read_v2>.

=head2 gosched_pipe_write_v2

C<static method gosched_pipe_write_v2 : int ($context : L<Go::Context|SPVM::Go::Context>, $fd : int, $string : string, $length : int = -1, $offset : int = 0);>

Suspends the current goroutine for pipe writing given the context $context, the file descriptor $fd, the buffer $string, the length $length, and the offset $offset.

Note: C<gosched_pipe_write> will be replaced by the implementation of C<gosched_pipe_write_v2>.

=head2 gosched_io_cancel

C<static method gosched_io_cancel : void ($fd : int);>

Cancels suspending the current goroutine for IO read/write given the file descriptor $fd

The control is transferred to the scheduler.

=head2 gosched_pipe_cancel

C<static method gosched_pipe_cancel : void ($fd : int);>

Cancels suspending the current goroutine for pipe read/write given the file descriptor $fd

The control is transferred to the scheduler.

=head2 sleep

C<static method sleep : void ($duration : Go::Duration_1l = undef)>

Sleeps the nanoseconds $duration.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

$seconds must be less than or equal to Fn->INT_MAX. Otherwise an exception is thrown.

=head2 sleep_sec

C<static method sleep_sec : void ($sec : double = 0);>

Same as L</"sleep">, but sleeps the seconds $sec.

=head2 new_wait_group

C<static method new_wait_group : L<Go::Sync::WaitGroup|SPVM::Go::Sync::WaitGroup> ($add : int = 0);>

Creates a new L<Go::Sync::WaitGroup|SPVM::Go::Sync::WaitGroup> object given the initial counter value $add.

=head2 new_command

C<static method new_command : L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> ($context : L<Go::Context|SPVM::Go::Context>, $command : string[]);>

Creates a new L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> object given the context $context and the command arguments $command.

=head2 ENV_DEBUG

C<static method ENV_DEBUG : int ();>

Casts the value of L</"SPVM_GO_DEBUG> environment variable to int type and returns it.

=head1 Modules

=over 2

=item * L<Go::Channel|SPVM::Go::Channel>

=item * L<Go::Select|SPVM::Go::Select>

=item * L<Go::Select::Result|SPVM::Go::Select::Result>

=item * L<Go::Sync::WaitGroup|SPVM::Go::Sync::WaitGroup>

=item * L<Go::OS::Signal|SPVM::Go::OS::Signal>

=item * L<Go::Time|SPVM::Go::Time>

=item * L<Go::Duration_1l|SPVM::Go::Duration_1l>

=item * L<Go::Context|SPVM::Go::Context>

=back

=head1 Enviroment Variables

=head2 SPVM_GO_DEBUG

=head1 Repository

L<SPVM::Go - Github|https://github.com/yuki-kimoto/SPVM-Go>

=head1 See Also

=over 2

=item * L<The Go Programming Language|https://go.dev/> - SPVM::Go is a porting of goroutines.

=item * L<Coro> - SPVM::Go uses goroutines.

=back

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT Licensepackage SPVM::Go;

our $VERSION = "0.047";

1;

=head1 Name

SPVM::Go - Goroutines of The Go Programming Language

=head1 Description

Go class in L<SPVM> provide goroutines and channels in Go language.

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

=head1 Details

L<Go|SPVM::Go> class provides a runtime environment that implements Goroutines
and Channels, mimicking the behavior of the Go programming language.

Unlike standard polling-based implementations that consume CPU cycles while
waiting, this module leverages the high-performance event loop provided by
L<libuv|https://libuv.org/>.

=head2 Efficient Waiting via Event Loop

When a Goroutine performs an operation that requires waiting, such as:

=over 2

=item * Timer-based waiting (e.g., C<time.sleep>)

=item * I/O operations (e.g., reading/writing sockets)

=item * Channel communication (waiting for data or space)

=back

The scheduler does not use busy-waiting or idle-looping. Instead, it registers
the operation with the libuv event loop and suspends the Goroutine.

The event loop puts the process into a low-power wait state, consuming virtually
zero CPU resources while waiting for the OS to signal that the event is ready.
Once the event occurs (e.g., a timer expires, data arrives, or a channel becomes
ready), the event loop notifies the scheduler, which then resumes the Goroutine
efficiently.

This architecture ensures high scalability and low CPU usage, allowing for
thousands of concurrent Goroutines to coexist within a single SPVM process
without significant overhead.

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

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_read : void ($fd : int, $timeout_duration : Go::Duration_1l = undef);>

Suspends the current goroutine for IO reading given the file descriptor $fd and the value of the timeout nanosecnods $timeout_duration.

The control is transferred to the scheduler.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

$timeout must be greater than 0. Otherwise an exception is thrown.

$timeout must be less than or equal to Fn->INT_MAX. Otherwise an exception is thrown.

If IO timeout occurs, an exception is thrown set C<eval_error_id> to the basic type ID of the L<Go::Error::IOTimeout|SPVM::Go::Error::IOTimeout> class.

=head2 gosched_io_read_sec

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_read_sec : void ($fd : int, $timeout_sec : double = 0);>

Same as L<"/gosched_io_read">, but the timeout is the seconds $timeout_sec.

=head2 gosched_io_write

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_write : void ($fd : int, $timeout_duration : Go::Duration_1l = undef);>

Suspends the current goroutine for IO writing given the file descriptor $fd and the timeout $timeout.

The control is transferred to the scheduler.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

$timeout must be greater than 0. Otherwise an exception is thrown.

$timeout must be less than or equal to Fn->INT_MAX. Otherwise an exception is thrown.

If IO timeout occurs, an exception is thrown set C<eval_error_id> to the basic type ID of the L<Go::Error::IOTimeout|SPVM::Go::Error::IOTimeout> class.

=head2 gosched_io_write_sec

B<Deprecated:> This method will be removed in the near future.

C<static method gosched_io_write_sec : void ($fd : int, $timeout_sec : double = 0);>

Same as L<"/gosched_io_write">, but the timeout is the seconds $timeout_sec.

=head2 gosched_poll_write

C<static method gosched_poll_write : void ($context : L<Go::Context|SPVM::Go::Context>, $fd : int);>

Suspends the current goroutine for poll writing given the context $context and the file descriptor $fd.

=head2 gosched_pipe_read_v2

C<static method gosched_pipe_read_v2 : int ($context : L<Go::Context|SPVM::Go::Context>, $fd : int, $string : mutable string, $length : int = -1, $offset : int = 0);>

Suspends the current goroutine for pipe reading given the context $context, the file descriptor $fd, the buffer $string, the length $length, and the offset $offset.

Note: C<gosched_pipe_read> will be replaced by the implementation of C<gosched_pipe_read_v2>.

=head2 gosched_pipe_write_v2

C<static method gosched_pipe_write_v2 : int ($context : L<Go::Context|SPVM::Go::Context>, $fd : int, $string : string, $length : int = -1, $offset : int = 0);>

Suspends the current goroutine for pipe writing given the context $context, the file descriptor $fd, the buffer $string, the length $length, and the offset $offset.

Note: C<gosched_pipe_write> will be replaced by the implementation of C<gosched_pipe_write_v2>.

=head2 gosched_io_cancel

C<static method gosched_io_cancel : void ($fd : int);>

Cancels suspending the current goroutine for IO read/write given the file descriptor $fd

The control is transferred to the scheduler.

=head2 gosched_pipe_cancel

C<static method gosched_pipe_cancel : void ($fd : int);>

Cancels suspending the current goroutine for pipe read/write given the file descriptor $fd

The control is transferred to the scheduler.

=head2 sleep

C<static method sleep : void ($duration : Go::Duration_1l = undef)>

Sleeps the nanoseconds $duration.

Exceptions:

This method must be called from the main thread. Otherwise an exception is thrown.

$seconds must be less than or equal to Fn->INT_MAX. Otherwise an exception is thrown.

=head2 sleep_sec

C<static method sleep_sec : void ($sec : double = 0);>

Same as L</"sleep">, but sleeps the seconds $sec.

=head2 new_wait_group

C<static method new_wait_group : L<Go::Sync::WaitGroup|SPVM::Go::Sync::WaitGroup> ($add : int = 0);>

Creates a new L<Go::Sync::WaitGroup|SPVM::Go::Sync::WaitGroup> object given the initial counter value $add.

=head2 new_command

C<static method new_command : L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> ($context : L<Go::Context|SPVM::Go::Context>, $command : string[]);>

Creates a new L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> object given the context $context and the command arguments $command.

=head2 after

C<static method after : L<Go::Channel|SPVM::Go::Channel> ($duration : L<Go::Duration_1l|SPVM::Go::Duration_1l> = undef);>

Waits for the duration $duration and then sends a value to the returned channel, mimicking C<time.After> in the Go programming language.

=head2 after_sec

C<static method after_sec : L<Go::Channel|SPVM::Go::Channel> ($sec : double = 0);>

Same as L</"after">, but waits for the seconds $sec.

=head2 bg

C<static method bg : L<Go::Context|SPVM::Go::Context> ();>

Returns a non-nil, empty L<Go::Context|SPVM::Go::Context> that is never canceled, has no values, and has no deadline, acting as a shortcut for C<Go::Context->background>.

=head2 todo

C<static method todo : L<Go::Context|SPVM::Go::Context> ();>

Returns a non-nil, empty L<Go::Context|SPVM::Go::Context> to be used when it is unclear which context to use or it is yet to be available, acting as a shortcut for C<Go::Context->todo>.

=head2 ENV_DEBUG

C<static method ENV_DEBUG : int ();>

Casts the value of L</"SPVM_GO_DEBUG> environment variable to int type and returns it.

=head1 Modules

=over 2

=item * L<Go::Channel|SPVM::Go::Channel>

=item * L<Go::Select|SPVM::Go::Select>

=item * L<Go::Select::Result|SPVM::Go::Select::Result>

=item * L<Go::Sync::WaitGroup|SPVM::Go::Sync::WaitGroup>

=item * L<Go::OS::Signal|SPVM::Go::OS::Signal>

=item * L<Go::Time|SPVM::Go::Time>

=item * L<Go::Duration_1l|SPVM::Go::Duration_1l>

=item * L<Go::Context|SPVM::Go::Context>

=back

=head1 Enviroment Variables

=head2 SPVM_GO_DEBUG

=head1 Repository

L<SPVM::Go - Github|https://github.com/yuki-kimoto/SPVM-Go>

=head1 See Also

=over 2

=item * L<The Go Programming Language|https://go.dev/> - SPVM::Go is a porting of goroutines.

=item * L<Coro> - SPVM::Go uses goroutines.

=back

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
