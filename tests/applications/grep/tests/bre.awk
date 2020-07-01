# Copyright (C) 2001, 2006, 2009-2017 Free Software Foundation, Inc.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

BEGIN {
        FS="@";
        n = 0;
        printf ("# Generated Spencer BRE Test\n");
        printf ("failures=0\n");
}

$0 ~ /^#/  { next; }

NF == 3 {
#	printf ("status=$(echo '%s' | { grep -e '%s' > /dev/null 2>&1; echo $?; cat >/dev/null; })\n",$3, $2);
        printf ("status=$(echo '%s' | { grep -e '%s' > /dev/null 2>&1; echo $? ; })\n",$3, $2);
        printf ("if test $status -ne %s ; then\n", $1);
        printf ("\techo Spencer bre test \\#%d failed\n", ++n);
        printf ("\tfailures=1\n");
        printf ("fi\n");
}

NF == 4 {
#don't alarm users
#	printf ("echo '%s' | grep -e '%s' > /dev/null 2>&1\n",$3, $2);
#	printf ("if test $? -ne %s ; then\n", $1);
#	printf ("\techo Expected non conformance \\#%d ... continuing\n", ++n);
#	printf ("fi\n");
}

END { printf ("exit $failures\n"); }
