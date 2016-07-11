#!/bin/sh
printf "Generating Files.... \n"

aclocal >/dev/null 2>&1 
autoheader >/dev/null 2>&1
automake --add-missing --foreign >/dev/null 2>&1
autoconf >/dev/null 2>&1


printf "Your are now ready to run configure\nDone\n";
