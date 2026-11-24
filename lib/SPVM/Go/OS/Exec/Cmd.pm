package SPVM::Go::OS::Exec::Cmd;



1;

=encoding utf8

=head1 Name

SPVM::Go::OS::Exec::Cmd - Command Configuration and Execution

=head1 Description

Go::OS::Exec::Cmd class in L<SPVM> represents an external command to be executed, similar to C<exec.Cmd> in the Go programming language.

=head1 Usage

  use Go;
  use Go::OS::Exec;
  use Go::OS::Exec::Cmd;
  
  my $cmd = Go::OS::Exec->command(Go->bg, ["perl", "-e", "print 'Hello';"]);
  my $status = $cmd->run;

=head1 Details

L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> holds the command path, arguments, environment variables, working directory, standard I/O and extra file descriptors, and context, then executes the command via L<Go::Schedule|SPVM::Go::Schedule>.

=head1 Fields

=head2 path

C<has path : rw string;>

The path to the executable file to run.

=head2 args

C<has args : rw string[];>

The command arguments passed to the executable.

=head2 env

C<has env : rw string[];>

The environment variables for the child process.

=head2 dir

C<has dir : rw string;>

The working directory for the child process.

=head2 stdout

C<has stdout : rw L<Go::OS::File|SPVM::Go::OS::File>;>

The standard output file or pipe end for the child process.

=head2 stderr

C<has stderr : rw L<Go::OS::File|SPVM::Go::OS::File>;>

The standard error file or pipe end for the child process.

=head2 stdin

C<has stdin : rw L<Go::OS::File|SPVM::Go::OS::File>;>

The standard input file or pipe end for the child process.

=head2 extra_files

C<has extra_files : rw L<Go::OS::File|SPVM::Go::OS::File>[];>

Additional files or pipe ends inherited by the child process starting at file descriptor 3.

=head2 context

C<has context : rw L<Go::Context|SPVM::Go::Context>;>

The context used for cancellation and timeout control during command execution.

=head1 Class Methods

=head2 new

C<static method new : L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> ();>

Creates a new L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> object.

=head1 Instance Methods

=head2 to_uv_process_options

C<method to_uv_process_options : L<UV::ProcessOptions|SPVM::UV::ProcessOptions> ();>

Converts the command settings and stdio descriptors into a L<UV::ProcessOptions|SPVM::UV::ProcessOptions> object.

=head2 run

C<method run : long ();>

Starts the command and waits for it to finish, returning the combined status value C<($exit_status << 8) | $term_signal>.

=head1 Well Known Child Classes

=head1 See Also

=over 2

=item * L<Go::OS::Exec|SPVM::Go::OS::Exec>

=item * L<Go::OS::File|SPVM::Go::OS::File>

=item * L<Go::Context|SPVM::Go::Context>

=item * L<Go::Schedule|SPVM::Go::Schedule>

=back

=head1 Repository

L<SPVM::Go - Github|https://github.com/yuki-kimoto/SPVM-Go>

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
