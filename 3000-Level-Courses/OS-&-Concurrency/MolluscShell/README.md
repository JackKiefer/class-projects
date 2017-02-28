## MolluscShell v2.0

Welcome to MolluscShell: a brand-new linux shell so-named due to its qualities of being snail-like and having limited usefulness.

MolluscShell supports the execution of all programs normally available in a linux shell, such as `ls`, `mkdir`, `rm`, etc., and also supports IO redirection with `|`, `<`, and `>`!

MolluscShell also contains implementation of the following commands:

| **Command** | **Arguments**    | **Description**                                                                                                                                                                        |
|---------|--------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| cd      | path/to/dir/ |                                                                                                                                                                   change directory |
| history |      ^*n*      | entering `history` with no arguments prints a list of  all commands entered thus far with a corresponding index. Adding the `^n` flag will re-execute the command at the *n*th index.  |
| ptime   |            - |                                                                                                               Prints the amount of time spent waiting on child processes thus far. |
| exit    |            - |                                                                                                                                                                 exits MolluscShell |


### Changelog
* MolluscShell v2.0
  * IO Redirection added
* MolluscShell v1.1
  * Bugfixes
  * Recursive history calls!
* MollsucShell v1.0
  * Initial release
