package SPVM::Go::OS::Exec;



1;

=encoding utf8

=head1 Name

SPVM::Go::OS::Exec - Executing Commands

=head1 Description

Go::OS::Exec class in L<SPVM> class provides functions to run external commands.

=head1 Usage

  use Go::OS::Exec;
  use Go::Context;
  
  my $cmd = Go::OS::Exec->command(Go->bg, ["perl", "-e", "print 'Hello';"]);
  my $status = $cmd->run;

=head1 Details

L<Go::OS::Exec|SPVM::Go::OS::Exec> class provides functions to run external commands, similar to C<os/exec> in the Go programming language.

=head1 Class Methods

=head2 command

C<static method command : L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> ($context : L<Go::Context|SPVM::Go::Context>, $command : string[]);>

Creates a new L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> object given the context $context and the command arguments $command.

=head1 Instance Methods

=head1 Well Known Child Classes

=head1 See Also

=over 2

=item * L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd>

=item * L<Go::Context|SPVM::Go::Context>

=back

=head1 Repository

L<SPVM::Go - Github|https://github.com/yuki-kimoto/SPVM-Go>

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
