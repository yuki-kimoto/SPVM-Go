package SPVM::Go::OS::File;



1;

=encoding utf8

=head1 Name

SPVM::Go::OS::File - File and Pipe Descriptor Wrapper

=head1 Description

Go::OS::File class in L<SPVM> represents an operating system file descriptor or pipe endpoint, similar to C<os.File> in the Go programming language.

=head1 Usage

  use Go;
  use Go::OS::File;
  
  my $pipe = Go::OS::File->prepare_pipe_end;
  $pipe->syswrite(Go->bg, "hello");
  $pipe->close;

=head1 Details

L<Go::OS::File|SPVM::Go::OS::File> wraps file descriptors and libuv stream handles for standard I/O streams (C<$STDIN>, C<$STDOUT>, C<$STDERR>), existing file descriptors, and pipe endpoints used with L<Go::OS::Exec::Cmd|SPVM::Go::OS::Exec::Cmd>.

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

The libuv stream handle associated with the pipe.

=head2 no_close

C<has no_close : byte;>

If true, C<close> throws an exception and C<DESTROY> does not close the descriptor.

=head2 opened

C<has opened : byte;>

Indicates whether the underlying file descriptor is currently open.

=head2 other_uv_pipe

C<has other_uv_pipe : L<UV::Handle::Pipe|SPVM::UV::Handle::Pipe>;>

The libuv pipe handle wrapping the paired endpoint descriptor.

=head1 Class Methods

=head2 new_file

C<static method new_file : L<Go::OS::File|SPVM::Go::OS::File> ($fd : int);>

Creates a L<Go::OS::File|SPVM::Go::OS::File> object for a non-negative file descriptor C<$fd> with C<no_close> set to 1.

=head2 prepare_pipe_end

C<static method prepare_pipe_end : L<Go::OS::File|SPVM::Go::OS::File> ();>

Creates a pipe pair, initializes the paired pipe handle on the event loop, and returns a pipe-end L<Go::OS::File|SPVM::Go::OS::File> object.

=head1 Instance Methods

=head2 close

C<method close : void ();>

Closes the pipe handles and file descriptor if C<no_close> is not set.

=head2 sysread

C<method sysread : int ($context : L<Go::Context|SPVM::Go::Context>, $string : mutable string, $length : int = -1, $offset : int = 0);>

Reads bytes from the pipe descriptor into C<$string> cooperatively with the goroutine scheduler and context C<$context>.

=head2 syswrite

C<method syswrite : int ($context : L<Go::Context|SPVM::Go::Context>, $string : string, $length : int = -1, $offset : int = 0);>

Writes bytes from C<$string> to the pipe descriptor cooperatively with the goroutine scheduler and context C<$context>.

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
