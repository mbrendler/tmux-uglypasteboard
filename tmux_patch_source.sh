#! /bin/bash


HERE=$(readlink -f .)


if test "$1" == "" ; then
   echo usage: $0 PATH_TO_TMUX_SOURCE
   exit 1
fi


patch $1/window-copy.c < tmux_uglypasteboard.patch

if test "$(uname)" = 'Darwin' ; then
    EXTRA_LDFLAGS='-framework Carbon'
fi

echo
echo Now build tmux the following way:
echo cd $1
echo mkdir BD
echo cd BD
echo ../configure "LDFLAGS='$EXTRA_LDFLAGS -L$HERE'"
echo LDADD=-luglypasteboard make
echo make install
