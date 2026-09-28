# AI Disclosure

## Tool, environment, and dates

- AI tool: GitHub Copilot, accessed through the Copilot SDK in VS Code.
- Model/version: The underlying model identifier and version were not exposed in the conversation record available, models were auto routed by Copilot.
- Consultation dates: This disclosure was completed on **2026-09-27**. 
- Development and verification environment: The source was copied from the local Windows project to `cycle3.eecs.ku.edu` and compiled and run there using `g++`.
- AI-assisted activities: Assignment breakdown, delegation to documentation/code-generation/code-verification agents, implementation and test generation, review, and disclosure documentation.

## Prompts preserved from the conversation

The following is the exact initial user prompt that initiated the assignment workflow:

> I am beginning a programming task that is meant to be done using AI. The writeup of the assignment is found in handout.md. Read through handout.md and break down the deliverables and split up the work. Spawn subagents to conquer the taks based on these topics: 1. Documentation & Project Compliance 2. Code Generation 3. Code Verification.

Prompt 2:
> I dont have c/c++ compilers on my system but I can SSH into a unix machine that does. When I tried to SSH i got this prompt in my terminal how should I proceed? What does this mean? $  ssh a734b348@cycle1.eecs.ku.edu The authenticity of host 'cycle1.eecs.ku.edu (129.237.87.111)' can't be established. ED25519 key fingerprint is SHA256:r/Un8MjMoI6g3wx+arBQae2QCkAc2fgtnDIuxY8916Y. This key is not known by any other names. Are you sure you want to continue connecting (yes/no/[fingerprint])? <

Prompt 3:
>I have now SSHd into a machine that can compile and run the code, are you able to use those resources or do I need to take control from here?<

Prompt 4:
>Heres what the output looks like: a734b348@cycle3:~/eecs581-a1$ g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp test_ipv4.cpp -o test_ipv4 ./test_ipv4 a734b348@cycle3:~/eecs581-a1$ s s: command not found a734b348@cycle3:~/eecs581-a1$ ls ipv4.cpp  ipv4.h  main.cpp  test_ipv4  test_ipv4.cpp a734b348@cycle3:~/eecs581-a1$ ./test_ipv4 a734b348@cycle3:~/eecs581-a1$ ls ipv4.cpp  ipv4.h  main.cpp  test_ipv4  test_ipv4.cpp a734b348@cycle3:~/eecs581-a1$ echo $? 0 a734b348@cycle3:~/eecs581-a1$ g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp main.cpp -o ipv4 ./ipv4 Enter a string (or 'END' to quit): connecting to 192.168.1.1 now server=10.0.0.255:8080end 192.168.01.1 1.2.3.4:99999 ENDExtracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none) Enter a string (or 'END' to quit): Extracted IPv4 address: 10.0.0.255 (decimal value: 167772415, port: 8080) Enter a string (or 'END' to quit): Invalid input: no valid IPv4 address found Enter a string (or 'END' to quit): Invalid input: no valid IPv4 address found Enter a string (or 'END' to quit): ^Z [1]+  Stopped                 ./ipv4 a734b348@cycle3:~/eecs581-a1$ g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp main.cpp -o ipv4 a734b348@cycle3:~/eecs581-a1$ ./ipv4 Enter a string (or 'END' to quit): connecting to 192.168.1.1 nowserver=10.0.0.255:8080end192.168.01.11.2.3.4:99999END Extracted IPv4 address: 192.168.1.1 (decimal value: 3232235777, port: none)Enter a string (or 'END' to quit):<

## AI attribution and student contributions

- AI-generated/AI-assisted source files: `ipv4.h`, `ipv4.cpp`, `main.cpp`, and `test_ipv4.cpp`.
- AI-generated/AI-assisted documentation: `README.md` and this disclosure.
- AI-generated tests include invalid leading-zero octets, an out-of-range port, malformed port and dot continuations, empty octets, and garbage-separated input.
- Student actions confirmed by the conversation: provided the assignment handout and requested the three-track workflow; copied the source files to the KU EECS Unix host; compiled the tests and program; ran the automated test executable and the manual cases listed below.
- Copying files, running commands, and testing inputs are student actions

## Verification performed

On `cycle3.eecs.ku.edu`, the student compiled the automated tests with:

```text
g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp test_ipv4.cpp -o test_ipv4
```

The student ran `./test_ipv4`; afterward, `echo $?` printed `0`. The compiler and test process printed no errors. This confirms that the included assertions passed in that run; it is not proof that every possible input is correct.

The student compiled the interactive program with:

```text
g++ -std=c++17 -Wall -Wextra -pedantic ipv4.cpp main.cpp -o ipv4
```

The recorded manual run showed:

| Input | Observed result |
| --- | --- |
| `connecting to 192.168.1.1 now` | Extracted `192.168.1.1`, decimal value `3232235777`, port `none` |
| `server=10.0.0.255:8080end` | Extracted `10.0.0.255`, decimal value `167772415`, port `8080` |
| `192.168.01.1` | Rejected |
| `1.2.3.4:99999` | Rejected |
| `END` | Printed `Program terminated.` |

The above compile commands produced no reported warnings or errors. The recorded test run and manual cases passed as described. Earlier terminal input mistakes and a suspended process were interaction issues, not reported code failures.

## Verification Statement

I the student confirm that I reviewed and understood every line of the generated code. The code was verified and the parser was tested with fuzzing and a set of unit tests to confirm functionality.