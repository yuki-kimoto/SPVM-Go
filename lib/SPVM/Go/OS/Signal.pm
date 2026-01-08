package SPVM::Go::OS::Signal;



1;

=head1 Name

SPVM::Go::OS::Signal - Signal Manipulation

=head1 Description

Go::OS::Signal class in L<SPVM> provides a way to handle OS signals using channels.

=head1 Usage

  use Go::OS::Signal;
  use Sys::Signal::Constant as SIGNAL;
  use Sys;
  
  Go::OS::Signal->start_signal_handler;
  
  Go->go(method : void () {
    
    Fn->defer(method : void () {
      Go::OS::Signal->stop_signal_handler;
    });
    
    my $ch = Go->make(1);
    
    Go::OS::Signal->notify($ch, SIGNAL->SIGTERM);
    
    Sys->kill(SIGNAL->SIGTERM, Sys->process_id);
    
    my $signal = $ch->read;
    
  });
  
  Go->gosched;

=head1 Class Methods

=head2 ignore

C<static method ignore : void ($signal : int);>

Ignores the signal $signal.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the values of signals.

=head2 notify

C<static method notify : void ($channel : L<Go::Channel|SPVM::Go::Channel>, $signal : int);>

Creates a goroutine to read the sent signal and write it to the $channel.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the values of signals.

=head2 stop

C<static method stop : void ($channel : L<Go::Channel|SPVM::Go::Channel>, $signal : int);>

Stops the signal handling for the signal $signal and the channel $channel.

See Sys::Signal::Constant about the values of signals.

=head2 start_signal_handler

C<static method start_signal_handler : void ();>

Starts signal handling.

This method should be called before the first goroutine execution and L</"stop_signal_handler"> method should be called at the beggining of the first goroutine execution using C<defer>.

  Go::OS::Signal->start_signal_handler;
  
  Go->go(method : void () {
    
    Fn->defer(method : void () {
      Go::OS::Signal->stop_signal_handler;
    });
    
    # Do something
  });
  
  Go->gosched;

=head2 stop_signal_handler

C<static method stop_signal_handler : void ();>

Stops signal handling. See L</"start_signal_handler"> method about the usage.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

