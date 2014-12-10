Ugly Pasteboard
===============

This is a naive implementation to access the OS X pasteboard.  I use this to
patch Tmux, so it does automatically copy to OS X pasteboard.


Installation
------------

On OS X install ``reattach-to-user-namespace`` via homebrew::

   $ brew install reattach-to-user-namespace

Build the ugly pasteboard lib::

   $ make

You need to download and extract the Tmux sources (Version 1.9a) and run the
following command::

   $ ./tmux_patch_source.sh PATH_TO_TMUX_SOURCE

After that follow the build instructions displayed by the script.


Usage
-----

If you call ``copy-selection``, the selected values are copied into the systems
pasteboard / clipboard.
