package SPVM::Go::UV::Handle::Idle;



1;

=encoding utf8

=head1 Name

SPVM::Go::UV::Handle::Idle - Idle Handle for libuv

=head1 Description

C<Go::UV::Handle::Idle> in L<SPVM> represents the idle handle for L<libuv|https://libuv.org/>, corresponding to the C<uv_idle_t> structure.

=head1 Super Class

L<Go::UV::Handle|SPVM::Go::UV::Handle>

=head1 Usage

  use Go::UV::Handle::Idle;
  
  my $idle = Go::UV::Handle::Idle->new;

=head1 Fields

=head2 idle_cb

C<has idle_cb : rw L<Go::UV::Callback::Idle|SPVM::Go::UV::Callback::Idle>;>

The callback called when the idle handle is active.

=head1 Class Methods

=head2 new

C<static method new : L<Go::UV::Handle::Idle|SPVM::Go::UV::Handle::Idle> ();>

Creates a new L<Go::UV::Handle::Idle|SPVM::Go::UV::Handle::Idle> object, and returns it.

=head1 Instance Methods

=head2 start

C<method start : void ($cb : L<Go::UV::Callback::Idle|SPVM::Go::UV::Callback::Idle>);>

Starts the idle handle with the callback C<$cb>. 

The callback C<$cb> is stored in L</"idle_cb"> field.

The callback C<$cb> is invoked when the idle handle is active.

This method calls the L<uv_idle_start|https://docs.libuv.org/en/v1.x/idle.html#c.uv_idle_start> function.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
