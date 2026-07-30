package SPVM::Go::UV::Loop;



1;

=encoding utf8

=head1 Name

L<SPVM::Go::UV::Loop|SPVM::Go::UV::Loop> - libuv Event Loop

=head1 Description

C<Go::UV::Loop> class in L<SPVM> represents an event loop in L<libuv|https://libuv.org/>.

=head1 Usage

  use Go::UV::Loop;
  use Go::UV::Constant as UV_C;
  
  my $uv_loop = Go::UV::Loop->new;
  
  $uv_loop->run(UV_C->UV_RUN_DEFAULT);

=head1 Fields

=head2 uv_handles_h

C<has uv_handles_h : Hash of L<Go::UV::Handle|SPVM::Go::UV::Handle>;>

A hash that holds active handles associated with this event loop.

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Loop|SPVM::Go::UV::Loop> ();>

Creates a new L<libuv loop|https://docs.libuv.org/en/v1.x/loop.html#c.uv_loop_init>.

=head1 Instance Methods

=head2 run

C<method run : int ($uv_run_mode : int);>

Runs the event loop with the specified mode, and returns the return value of L<uv_run|https://docs.libuv.org/en/v1.x/loop.html#c.uv_run>.

See L<Go::UV::Constant|SPVM::Go::UV::Constant> for constants such as C<UV_RUN_XXX> specified at $uv_run_mode.

=head2 idle_init

C<method idle_init : void ($uv_idle : L<Go::UV::Handle::Idle|SPVM::Go::UV::Handle::Idle>);>

Initializes an idle handle $uv_idle associated with the event loop. See L<uv_idle_init|https://docs.libuv.org/en/v1.x/idle.html#c.uv_idle_init>.

=head2 timer_init

C<method timer_init : void ($uv_timer : L<Go::UV::Handle::Timer|SPVM::Go::UV::Handle::Timer>);>

Initializes a timer handle $uv_timer associated with the event loop. See L<uv_timer_init|https://docs.libuv.org/en/v1.x/timer.html#c.uv_timer_init>.

=head2 poll_init

C<method poll_init : void ($uv_poll : L<Go::UV::Handle::Poll|SPVM::Go::UV::Handle::Poll>, $fd : int);>

Initializes a poll handle $uv_poll for the given file descriptor $fd associated with the event loop. See L<uv_poll_init|https://docs.libuv.org/en/v1.x/poll.html#c.uv_poll_init>.

=head2 async_init

C<method async_init : void ($uv_async : L<Go::UV::Handle::Async|SPVM::Go::UV::Handle::Async>, $cb : L<Go::UV::Callback::Async|SPVM::Go::UV::Callback::Async>);>

Initializes an async handle $uv_async associated with the event loop with a callback $cb. L<Go::UV::Handle::Async#async_cb|SPVM::Go::UV::Handle::Async/"async_cb"> field is set to $cb. See L<uv_async_init|https://docs.libuv.org/en/v1.x/async.html#c.uv_async_init>.

=head2 pipe_init

C<method pipe_init : void ($uv_pipe : L<Go::UV::Handle::Pipe|SPVM::Go::UV::Handle::Pipe>, $ipc : int);>

Initializes a pipe handle $uv_pipe associated with the event loop with $ipc. See L<uv_pipe_init|https://docs.libuv.org/en/v1.x/pipe.html#c.uv_pipe_init>.

=head2 DESTROY

C<method DESTROY : void ();>

Destroys the event loop and releases its resources. See L<uv_loop_close|https://docs.libuv.org/en/v1.x/loop.html#c.uv_loop_close>.
