package SPVM::Go::Fsnotify;

1;

=encoding utf8

=head1 Name

SPVM::Go::Fsnotify - File System Watcher

=head1 Description

The L<Go::Fsnotify|SPVM::Go::Fsnotify> class in L<SPVM|SPVM> has methods to watch file system changes, compatible with Go's fsnotify.

=head1 Usage

  use Go::Fsnotify;
  
  # Create a new watcher
  my $watcher = Go::Fsnotify->new;
  
  # Add a directory to watch
  $watcher->add("/path/to/dir");
  
  # Get events channel
  my $events_ch = $watcher->events;
  
  # Read events
  my $event = (Go::Fsnotify::Event)$events_ch->read;
  
  # Close the watcher
  $watcher->close;

=head1 Class Methods

=head2 new

C<static method new : L<Go::Fsnotify|SPVM::Go::Fsnotify> ();>

Creates a new L<Go::Fsnotify|SPVM::Go::Fsnotify> watcher instance.

=head1 Instance Methods

=head2 add

C<method add : void ($dir : string);>

Adds a directory to watch for file system events.

Exceptions:

If this watcher is closed, an exception is thrown.

=head2 events

C<method events : L<Go::Channel|SPVM::Go::Channel> ();>

Gets the L<Go::Channel|SPVM::Go::Channel> object for receiving file system events (L<Go::Fsnotify::Event|SPVM::Go::Fsnotify::Event>).

=head2 close

C<method close : void ();>

Closes the watcher, stops all active file system event handles, and closes the events channel.

=head1 Repository

=head1 Author

Yuki Kimoto C<kimoto.yuki@gmail.com>

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

=cut
