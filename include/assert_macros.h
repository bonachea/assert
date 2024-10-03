! assert_macros.h: provides preprocessor-based assertion macros
! that are guaranteed to compile away statically when disabled.

! Enable repeated includes to toggle assertions based on current settings:
#undef call_assert
#undef call_assert_describe
#undef call_assert_diagnose

#ifndef ASSERTIONS
! Assertions are off by default
#define ASSERTIONS 0
#endif

! Deal with stringification issues:
! https://gcc.gnu.org/legacy-ml/fortran/2009-06/msg00131.html
#ifndef STRINGIFY
# if defined(__GFORTRAN__) || defined(_CRAYFTN)
#  define STRINGIFY(x) "x"
# else
#  define STRINGIFY(x) #x
# endif
#endif

#if ASSERTIONS
#  define call_assert_3(cond, desc, data) call assert(cond, "file " // __FILE__ // ", line " // string(__LINE__) // ": " // desc, data)
#  define call_assert_2(cond, desc) call assert(cond, "file " // __FILE__ // ", line " // string(__LINE__) // ": " // desc)
#  define call_assert_1(cond) call_assert_2(cond, "Failed assertion: " // STRINGIFY(cond))
#  define call_assert_dispatch(_1, _2, _3, NAME, ...) NAME
#  define call_assert(...) call_assert_dispatch(__VA_ARGS__, call_assert_3, call_assert_2, call_assert_1, _DUMMY)(__VA_ARGS__)
#else
#  define call_assert(...) 
#endif

