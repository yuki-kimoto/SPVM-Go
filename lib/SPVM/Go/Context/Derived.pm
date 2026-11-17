package SPVM::Go::Context::Derived;

1;

=encoding utf8

=head1 Name

SPVM::Go::Context::Derived - Derived Context

=head1 Description

C<Go::Context::Derived> class in L<SPVM> represents a derived context.

=head1 Usage

  use Go::Context::Derived;

=head1 Details

C<Go::Context::Derived> is a class that holds a parent context and a cancel callback.

=head1 Super Class

L<SPVM::Obj|SPVM::Obj>

=head1 Interfaces

=over 2

=item * L<SPVM::Go::Context|SPVM::Go::Context>

=back

=head1 Enumerations

=head1 Fields

=head2 ctx

  has ctx : rw SPVM::Go::Context;

B<Deprecated:> Use L</"context"> instead.

Parent context.

=head2 context

  has context : virtual rw SPVM::Go::Context;

Parent context.

=head2 cancel

  has cancel : rw SPVM::Go::Context::CancelCallback;

B<Deprecated:> Use L</"cancel_cb"> instead.

Cancel callback.

=head2 cancel_cb

  has cancel_cb : virtual rw SPVM::Go::Context::CancelCallback;

Cancel callback.

=head1 Class Methods

=head2 new

  static method new : SPVM::Go::Context::Derived ();

Creates a new C<Go::Context::Derived> object.

=head1 Instance Methods

=head1 Well Known Child Classes

=head1 See Also

L<SPVM::Go::Context|SPVM::Go::Context>

=head1 Repository

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

=cut
