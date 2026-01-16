package SPVM::Go::Context;

1;

=encoding utf8

=head1 Name

SPVM::Go::Context - Context propagation, cancellation, and value sharing (Go-style)

=head1 Description

Go::Context class in L<SPVM> provides a way to carry deadlines, cancellation signals, and other request-scoped values across API boundaries and between goroutines.

It is based on the implementation of C<context.Context> in the Go programming language.

=head1 Usage

  use Go::Context;
  
  # Create a background context
  my $ctx = Go::Context->with_background;
  
  # Create a context with 5 seconds timeout
  my $derived = Go::Context->with_timeout_sec($ctx, 5.0);
  my $ctx_with_timeout = $derived->ctx;
  my $cancel = $derived->cancel;
  
  # Done channel
  my $done = $ctx_with_timeout->done;
  
  # Manually cancel when finished
  $cancel->();

=head1 Class Methods

=head2 with_background

C<static method with_background : L<Go::Context|SPVM::Go::Context> ();>

Returns a non-nil, empty L<Go::Context|SPVM::Go::Context>. It is never canceled, has no values, and has no deadline. It is typically used by the main function, initialization, and tests.

See L<context.Background|https://pkg.go.dev/context#Background>.

=head2 without_cancel

C<static method without_cancel : L<Go::Context|SPVM::Go::Context> ($parent_ctx : L<Go::Context|SPVM::Go::Context>);>

Returns a copy of C<$parent_ctx> that is not canceled when C<$parent_ctx> is canceled.

See L<context.WithoutCancel|https://pkg.go.dev/context#WithoutCancel>.

=head2 with_cancel

C<static method with_cancel : L<Go::Context::Derived|SPVM::Go::Context::Derived> ($parent_ctx : L<Go::Context|SPVM::Go::Context>);>

Returns a L<Go::Context::Derived|SPVM::Go::Context::Derived> object containing a new context and a cancel function.

See L<context.WithCancel|https://pkg.go.dev/context#WithCancel>.

=head2 with_cancel_cause

C<static method with_cancel_cause : L<Go::Context::Derived|SPVM::Go::Context::Derived> ($parent_ctx : L<Go::Context|SPVM::Go::Context>, $cause : string);>

Similar to L</with_cancel>, but also sets a cause for the cancellation.

See L<context.WithCancelCause|https://pkg.go.dev/context#WithCancelCause>.

=head2 with_deadline

C<static method with_deadline : L<Go::Context::Derived|SPVM::Go::Context::Derived> ($parent_ctx : L<Go::Context|SPVM::Go::Context>, $deadline : L<Go::Time|SPVM::Go::Time>);>

Returns a derived context that is canceled when the C<$deadline> expires or the parent's C<done> channel is closed.

See L<context.WithDeadline|https://pkg.go.dev/context#WithDeadline>.

=head2 with_deadline_cause

C<static method with_deadline_cause : L<Go::Context::Derived|SPVM::Go::Context::Derived> ($parent_ctx : L<Go::Context|SPVM::Go::Context>, $deadline : L<Go::Time|SPVM::Go::Time>, $cause : string);>

Similar to L</with_deadline>, but also sets a cause when the C<$deadline> expires.

See L<context.WithDeadlineCause|https://pkg.go.dev/context#WithDeadlineCause>.

=head2 with_timeout

C<static method with_timeout : L<Go::Context::Derived|SPVM::Go::Context::Derived> ($parent_ctx : L<Go::Context|SPVM::Go::Context>, $timeout : L<Go::Duration_1l|SPVM::Go::Duration_1l>);>

A wrapper for L</with_deadline> that takes a duration C<$timeout> instead of a specific time.

See L<context.WithTimeout|https://pkg.go.dev/context#WithTimeout>.

=head2 with_timeout_sec

C<static method with_timeout_sec : L<Go::Context::Derived|SPVM::Go::Context::Derived> ($parent_ctx : L<Go::Context|SPVM::Go::Context>, $timeout_sec : double);>

A helper method that creates a timeout context from the specified number of seconds C<$timeout_sec> (as a C<double>).

=head2 with_value

C<static method with_value : L<Go::Context|SPVM::Go::Context> ($parent_ctx : L<Go::Context|SPVM::Go::Context>, $key : object, $value : object);>

Returns a copy of C<$parent_ctx> in which the value associated with C<$key> is C<$value>.

See L<context.WithValue|https://pkg.go.dev/context#WithValue>.

=head1 Instance Methods

=head2 deadline

C<method deadline : L<Go::Time|SPVM::Go::Time> ();>

Returns the time when work done on behalf of this context should be canceled.

See L<Context.Deadline|https://pkg.go.dev/context#Context.Deadline>.

=head2 done

C<method done : L<Go::Channel|SPVM::Go::Channel> ();>

Returns a channel that's closed when work done on behalf of this context should be canceled.

See L<Context.Done|https://pkg.go.dev/context#Context.Done>.

=head2 err

C<method err : int ();>

Returns an error code (basic type ID) explaining why this context was canceled.

See L<Context.Err|https://pkg.go.dev/context#Context.Err>.

=head2 cause

C<method cause : string ();>

Returns a string explaining why this context was canceled.

See L<context.Cause|https://pkg.go.dev/context#Cause>.

=head2 value

C<method value : object ($key : object);>

Returns the value associated with this context for C<$key>, or undef if no value is associated with C<$key>.

See L<Context.Value|https://pkg.go.dev/context#Context.Value>.

=head1 See Also

=over 2

=item * L<Go::Context::Derived|SPVM::Go::Context::Derived>

=item * L<Go::Time|SPVM::Go::Time>

=item * L<Go::Channel|SPVM::Go::Channel>

=back

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License