! assert_macros.h: provides preprocessor-based assertion macros
! that are guaranteed to compile away statically when disabled.

! Enable repeated includes to toggle assertions based on current settings:
#undef call_assert
#undef call_assert_describe
#undef call_assert_diagnose

! Check user-provided flags to decide whether assertions are enabled
#if defined(DEBUG) && defined(NDEBUG)
# error Please define at most one of DEBUG or NDEBUG
#endif

! Deal with Fortran's stringification debacle:
! https://gcc.gnu.org/legacy-ml/fortran/2009-06/msg00131.html
#ifdef __GFORTRAN__
#define STRINGIFY(x) "x"
#else
#define STRINGIFY(x) #x
#endif

#if defined(DEBUG)
# define call_assert(assertion) call assert(assertion, STRINGIFY(assertion) // " in file " // __FILE__ // ", line " // string(__LINE__) // ")")
# define call_assert_describe(assertion, description) call assert(assertion, description // " in file " // __FILE__ // ", line " // string(__LINE__) // ": " )
# define call_assert_diagnose(assertion, description, diagnostic_data) call assert(assertion, "file " // __FILE__ // ", line " // string(__LINE__) // ": " // description, diagnostic_data)
#else
# define call_assert(assertion)
# define call_assert_describe(assertion, description)
# define call_assert_diagnose(assertion, description, diagnostic_data)
#endif
