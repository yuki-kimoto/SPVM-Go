package SPVM::Go::OS::File;



1;

=encoding utf8

=head1 Name

SPVM::Go::OS::File - File, TCP, and Pipe Descriptor Wrapper

=head1 Description

Go::OS::File class in L<SPVM> represents an operating system file descriptor, TCP socket, or pipe endpoint, similar to C<os.File> in the Go programming language.

=head1 Usage

  use Go;
  use Go::OS::File;
  
  my $file = Go::OS::File->new_pipe_end($fd);
  $file->write(Go->bg, "hello");
  $file->close;

=head1 Details

L<Go::OS::File|SPVM::Go::OS::File> wraps file descriptors and libuv stream handles for standard I/O streams (C<$STDIN>, C<$STDOUT>, C<$STDERR>), existing file descriptors, TCP sockets, and pipe endpoints used with L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd> and non-blocking I/O.

=head1 Class Variables

=head2 STDIN

C<our $STDIN : ro L<Go::OS::File|SPVM::Go::OS::File>;>

Standard input file wrapping file descriptor 0 with C<no_close> enabled.

=head2 STDOUT

C<our $STDOUT : ro L<Go::OS::File|SPVM::Go::OS::File>;>

Standard output file wrapping file descriptor 1 with C<no_close> enabled.

=head2 STDERR

C<our $STDERR : ro L<Go::OS::File|SPVM::Go::OS::File>;>

Standard error file wrapping file descriptor 2 with C<no_close> enabled.

=head1 Fields

=head2 type

C<has type : ro int;>

The internal descriptor type.

=head2 fd

C<has fd : ro int;>

The operating system file descriptor.

=head2 uv_stream

C<has uv_stream : L<UV::Handle::Stream|SPVM::UV::Handle::Stream>;>

The libuv stream handle associated with the TCP socket or pipe endpoint.

=head2 finish_cb

C<has finish_cb : L<Callback|SPVM::Callback>;>

The callback invoked to complete or cancel an in-progress read or write operation.

=head2 no_close

C<has no_close : byte;>

If true, C<close> throws an exception and C<DESTROY> does not close the descriptor.

=head2 closed

C<has closed : ro byte;>

Indicates whether the file has been closed.

=head1 Class Methods

=head2 new_file

C<static method new_file : L<Go::OS::File|SPVM::Go::OS::File> ($fd : int);>

Creates a L<Go::OS::File|SPVM::Go::OS::File> object for a non-negative file descriptor C<$fd> with C<no_close> set to 1.

=head2 new_tcp

C<static method new_tcp : L<Go::OS::File|SPVM::Go::OS::File> ($fd : int);>

Duplicates a non-negative TCP socket file descriptor C<$fd>, initializes a L<UV::Handle::TCP|SPVM::UV::Handle::TCP> handle on the event loop, opens the duplicated descriptor, and returns a L<Go::OS::File|SPVM::Go::OS::File> object.

=head2 new_pipe_end

C<static method new_pipe_end : L<Go::OS::File|SPVM::Go::OS::File> ($fd : int);>

Duplicates a non-negative pipe file descriptor C<$fd>, initializes a L<UV::Handle::Pipe|SPVM::UV::Handle::Pipe> handle on the event loop, opens the duplicated descriptor, and returns a pipe-end L<Go::OS::File|SPVM::Go::OS::File> object.

=head2 prepare_pipe_end

C<static method prepare_pipe_end : L<Go::OS::File|SPVM::Go::OS::File> ();>

Creates a placeholder L<Go::OS::File|SPVM::Go::OS::File> object for a pipe endpoint before a file descriptor is attached.

=head1 Instance Methods

=head2 read

C<method read : int ($context : L<Go::Context|SPVM::Go::Context>, $string : mutable string, $length : int = -1, $offset : int = 0);>

Reads bytes from the TCP or pipe stream into C<$string> cooperatively with the goroutine scheduler and context C<$context>.

=head2 write

C<method write : int ($context : L<Go::Context|SPVM::Go::Context>, $string : string, $length : int = -1, $offset : int = 0);>

Writes bytes from C<$string> to the TCP or pipe stream cooperatively with the goroutine scheduler and context C<$context>.

=head2 close

C<method close : void ();>

Cancels any active operation, closes the libuv stream handle if present, and marks the file as closed unless C<no_close> is set.

=head2 DESTROY

C<method DESTROY : void ();>

Calls C<close> automatically when destroyed unless C<no_close> is set.

=head1 Well Known Child Classes

=head1 See Also

=over 2

=item * L<Go::OS::Exec|SPVM::Go::OS::Exec>

=item * L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd>

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
