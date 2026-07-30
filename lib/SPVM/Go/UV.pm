package SPVM::Go::UV;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV - libuv Binding

=head1 Description

Go::UV class in L<SPVM> is a L<libuv|https://libuv.org/> binding.

=head1 Usage

  use Go::UV::Loop;
  use Go::UV::Constant as UV_C;
  
  my $uv_loop = Go::UV::Loop->new;
  
  # Do someting
  
  $uv_loop->run(UV_C->UV_RUN_DEFAULT);
  
Timer:

  use Go::UV::Handle::Timer;
  
  my $timeout_msec = 3_000;
  my $uv_timer = Go::UV::Handle::Timer->new;
  $uv_loop->timer_init($uv_timer);
  my $timer_cb = method : void ($uv_timer : Go::UV::Handle::Timer) {
    
    # Do something
    
    $uv_timer->close;
  };
  $uv_timer->start($timer_cb, $timeout_msec);

Socket IO:

  use Go::UV::Handle::Poll;
  
  my $uv_poll = Go::UV::Handle::Poll->new;
  $uv_loop->poll_init($uv_poll, $fd);
  my $poll_cb = method : void ($uv_poll : Go::UV::Handle::Poll, $status : int, $events : int) {
    
    # Do something
    
    $poll_cb->close;
  };
  
  my $events = UV_C->UV_READABLE | UV_C->UV_WRITABLE;
  $uv_poll->start($poll_cb, $events);

=head1 Class Methods

=head2 strerror

C<static method strerror : string ($status : int);>

Gets human-readable description for an error code by calling L<uv_strerror_r|https://docs.libuv.org/en/v1.x/errors.html#c.uv_strerror_r>, and returns it as a string.

=head1 Modules

=over 2

=item * L<Go::UV::Loop|SPVM::Go::UV::Loop>

=item * L<Go::UV::Constant|SPVM::Go::UV::Constant>

=item * L<Go::UV::Handle|SPVM::Go::UV::Handle>

=item * L<Go::UV::Handle::Idle|SPVM::Go::UV::Handle::Idle>

=item * L<Go::UV::Handle::Pipe|SPVM::Go::UV::Handle::Pipe>

=item * L<Go::UV::Handle::Async|SPVM::Go::UV::Handle::Async>

=item * L<Go::UV::Handle::Stream|SPVM::Go::UV::Handle::Stream>

=item * L<Go::UV::Handle::Timer|SPVM::Go::UV::Handle::Timer>

=item * L<Go::UV::Handle::Poll|SPVM::Go::UV::Handle::Poll>

=item * L<Go::UV::Request|SPVM::Go::UV::Request>

=item * L<Go::UV::Request::Write|SPVM::Go::UV::Request::Write>

=item * L<Go::UV::Callback::Write|SPVM::Go::UV::Callback::Write>

=item * L<Go::UV::Callback::Idle|SPVM::Go::UV::Callback::Idle>

=item * L<Go::UV::Callback::Async|SPVM::Go::UV::Callback::Async>

=item * L<Go::UV::Callback::Read|SPVM::Go::UV::Callback::Read>

=item * L<Go::UV::Callback::Close|SPVM::Go::UV::Callback::Close>

=item * L<Go::UV::Callback::Timer|SPVM::Go::UV::Callback::Timer>

=item * L<Go::UV::Callback::Poll|SPVM::Go::UV::Callback::Poll>

=back

=head1 Repository

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

