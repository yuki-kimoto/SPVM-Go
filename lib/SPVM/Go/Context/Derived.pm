package SPVM::Go::Context::Derived;

1;

=encoding utf8

=head1 Name

SPVM::Go::Context::Derived - Derived Context

=head1 Description

Go::Context::Derived class in L<SPVM> represents a container of a derived context and a cancel callback.

=head1 Usage

  use Go::Context::Derived;

=head1 Interfaces

=over 2

=item * L<SPVM::Go::Context|SPVM::Go::Context>

=back

=head1 Fields

=head2 context

C<has context :rw L<Go::Context|SPVM::Go::Context>;>

A derived context.

=head2 cancel_cb

C<has cancel_cb : rw L<Go::Context::CancelCallback|SPVM::Go::Context::CancelCallback>;>

A cancel callback.

=head1 Class Methods

=head2 new

C<static method new : L<Go::Context::Derived|SPVM::Go::Context::Derived> ();>

Creates a new C<Go::Context::Derived> object.

=head1 See Also

L<SPVM::Go::Context|SPVM::Go::Context>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

=cut
