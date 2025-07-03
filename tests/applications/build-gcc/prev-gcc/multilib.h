static const char *const multilib_raw[] = {
". !m64 !m32;",
"64:../lib64 m64 !m32;",
"32:../lib32 !m64 m32;",
NULL
};

static const char *const multilib_matches_raw[] = {
"m64 m64;",
"m32 m32;",
NULL
};

static const char *multilib_extra = "";

static const char *const multilib_exclusions_raw[] = {
NULL
};

static const char *multilib_options = "m64/m32";
