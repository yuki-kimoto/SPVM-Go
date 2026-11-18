package SPVM::Go::OS::Signal;

1;

=head1 Name

SPVM::Go::OS::Signal - Signal Manipulation

=head1 Description

Go::OS::Signal class in L<SPVM> provides a way to handle OS signals using channels.

=head1 Usage

  use Go::OS::Signal;
  use Sys::Signal::Constant as SIGNAL_C;
  use Sys;
  
  my $sig = Go::OS::Signal->new;
  
  my $ch = Go->make(1);
  
  $sig->notify($ch, SIGNAL_C->SIGTERM);
  
  Sys->kill(SIGNAL_C->SIGTERM, Sys->process_id);
  
  my $signal = $ch->read;

=head1 Constructor Methods

=head2 new

C<static method new : L<Go::OS::Signal|SPVM::Go::OS::Signal> ();>

Creates a new L<Go::OS::Signal|SPVM::Go::OS::Signal> object.

=head1 Instance Methods

=head2 ignore

C<method ignore : void ($signal : int);>

Ignores the signal $signal.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the values of signals.

=head2 notify

C<method notify : void ($channel : L<Go::Channel|SPVM::Go::Channel>, $signal : int);>

Creates a goroutine to read the sent signal and write it to the $channel.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the values of signals.

=head2 stop

C<method stop : void ($channel : L<Go::Channel|SPVM::Go::Channel>, $signal : int);>

Stops the signal handling for the signal $signal and the channel $channel.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the values of signals.

=head2 reset

C<method reset : void ();>

Resets all signal handlers and clears registered channels.

=head2 DESTROY

C<method DESTROY : void ();>

Destructor. Calls L</"reset">.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License

=cut
