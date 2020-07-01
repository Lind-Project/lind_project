# Copyright (C) 1988 Henry Spencer.
# Copyright (C) 2009-2017 Free Software Foundation, Inc.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

BEGIN {
        FS = "@";
        printf ("failures=0\n");
}

$0 !~ /^#/  && NF == 3 {
#	printf ("status=$(echo '%s'| { grep -E -e '%s' > /dev/null 2>&1; echo $?; cat >/dev/null; })\n",$3, $2);
        printf ("status=$(echo '%s'| { grep -E -e '%s' >/dev/null 2>&1 ; echo $?; })\n",$3, $2);
        printf ("if test $status -ne %s ; then\n", $1);
        printf ("\techo Spencer test \\#%d failed\n", ++n);
        printf ("\tfailures=1\n");
        printf ("fi\n");
}

END { printf ("exit $failures\n"); }
