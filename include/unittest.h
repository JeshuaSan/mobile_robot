#ifndef UNTTEST_H
#define	UNTTEST_H

#include <stdint.h>

// Circular includes: pic24_util needs this include, but
// this needs reportError. Pre-declare here.
void reportError(const char* message);

/** Macro to convert a number to a string.
 *  Typical usage: <code>TOSTRING(__LINE__)</code>
 */
#define TOSTRING(x) _TOSTRING(x)
// A helper macro used by \ref TOSTRING.
#define _TOSTRING(x) #x
///@}

/** A macro to add the file name and line at which the
 *  macro was called to the given message.
 *  \param msg Message to add file/line info to.
 */
#define ERROR_FILE_LINE(msg) "Error in " __FILE__ " line " TOSTRING(__LINE__) ": " msg

// Uncomment the following line to remove all the ASSERTs
// from the program:
//#define _NOASSERT
#ifdef _NOASSERT
#define ASSERT(placeholder) (void)0
#define _COMPILE_ASSERT_SYMBOL_INNER(line, msg)
#define _COMPILE_ASSERT_SYMBOL(line, msg)
#define COMPILE_ASSERT(test, msg)
#else
/** A useful compile-time assert macro.
 * USAGE:  COMPILE_ASSERT( condition, message_to_print_if_fails)
 *
 * Note: these macros use typedef so they can't be use in a
 *			 value assignment type macro
 * Note: message_to_print_if_fails is used as C language variable in this
 *       clever little macro, SO.... your message must adhere to C variable
 *       naming rules, i.e. no spaces or funny characters.  Use underscores
 *       or CamelCase to separate words.
 */
#define COMPILE_ASSERT(test, msg)                      \
		typedef char _COMPILE_ASSERT_SYMBOL(__LINE__, msg) [ ((test) ? 1 : -1) ]
// A helper macro used by \ref COMPILE_ASSERT.
#define _COMPILE_ASSERT_SYMBOL_INNER(line, msg) __COMPILE_ASSERT_ ## line ## _____ ## msg
// A helper macro used by \ref COMPILE_ASSERT.
#define _COMPILE_ASSERT_SYMBOL(line, msg) _COMPILE_ASSERT_SYMBOL_INNER(line, msg)

/** Assert that test is true. See \ref picAssert for
 *  details. NOTE: only test results; DO NOT include main-line
 *  code in an ASSERT, since it can be compiled out.
 *  For example, <code>ASSERT(myFunc())</code> is dangerous,
 *  since <code>myFunc()</code> will no longer be called if
 *  ASSERT is disabled by defining _NDEBUG.
 */
#define ASSERT(test) picAssert(test, ERROR_FILE_LINE("ASSERT(" #test ") failed.\n"))

/** A function to reset the chip and report a message
 *  if the test is false. Assumes \ref reportError
 *  is called at start-up to report any assertion
 *  violations.
 *
 *  \param test Boolean results of test run. If false,
 *              reset and print message.
 *  \param message Message to print if assertion fails.
 */
static inline void picAssert(uint8_t test, const char* message) {
  if (!test)
    reportError(message);
}
#endif

#endif	/* UNTTEST_H */

