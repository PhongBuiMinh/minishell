DATA STRUCT:
t_ast_node {
    t_ast_node_type  type;           // Node purpose: CMD, PIPELINE, IDENTIFIER, REDIRECTION
    union u_data     data;           // ← Type-specific data (only one active)
    t_ast_node      *next;           // → Next sibling in list
}

t_ast_node_type  type:
AST_PIPELINE
└── cmds
    ├── AST_COMMAND
    │     └── args
    │         ├── AST_IDENTIFIER("ls")
    │         ├── AST_IDENTIFIER("-l")
    │         └── AST_IDENTIFIER("/home")
    │
    ├── AST_COMMAND
    │     └── args
    │         ├── AST_IDENTIFIER("grep")
    │         └── AST_IDENTIFIER("txt")
    │
    └── AST_COMMAND
          └── args
              ├── AST_IDENTIFIER("wc")
              └── AST_IDENTIFIER("-l")

Minishell Command Lifecycle:
1. readline() → raw input
2. lexer() → t_token list (CMD, ARG, PIPE, REDIR, etc.)
3. parser() → t_ast tree (command nodes + pipes/subshells)
4. expander() → expand $VAR, ~, $? in tokens
5. executor() → traverse AST → init t_exec → exec/builtins

main()
  ├─ init_shell(&shell)
  ├─ init_signals(&shell)
  │
  └─ while (readline loop):
      ├─ read line
      ├─ parse_line(line, &shell)
      ├─ execute_ast(shell.ast, &shell)
      │   │
      │   ├─ Identify AST type
      │   │   ├─ AST_CMD:
      │   │   │   ├─ expand_variables(&shell)
      │   │   │   ├─ apply_redirections(&cmd, &exec)
      │   │   │   └─ execute_builtin() or execute_external()
      │   │   │
      │   │   └─ AST_PIPELINE:
      │   │       ├─ create_pipes()
      │   │       ├─ fork() × N
      │   │       │   ├─ Child has access to shell via exec->shell
      │   │       │   ├─ Setup redirections
      │   │       │   └─ execve()
      │   │       └─ waitpid() × N
      │   │
      │   └─ return exit_status
      │
      ├─ shell.exit_status = result
      └─ $? available for next command

Signal arrives
  │
  ├─ handle_sigint() / handle_sigquit()
  │   └─ g_signal_received = SIGINT/SIGQUIT  ← ONLY THIS
  │
  └─ Main loop checks g_signal_received
      ├─ Reset flag: g_signal_received = 0
      ├─ Update shell state: shell.exit_status = 130
      └─ Continue execution
          └─ All data flows through:
              ├─ t_shell_state (environment, exit codes, etc.)
              ├─ t_executor (execution context)
              ├─ t_cmd_exec (command details)
              └─ t_redirection (I/O redirections)

Minishell Command Execution Pipeline (From Input to Execution):
Input
  ↓
Lexer/Parser
  ↓
AST created
  ↓
Expander
  ↓
Variables expanded
  ↓
Executor (execute_ast)
  ├─ Check AST node type
  │   ├─ AST_CMD → execute_command()
  │   └─ AST_PIPELINE → execute_pipeline()
  │
  ├─ IF AST_CMD (single command):
  │   ├─ save_std_fds()
  │   ├─ apply_redirections()
  │   ├─ ast_cmd_to_argv()
  │   ├─ is_builtin_cmd()?
  │   │   ├─ YES: execute_builtin()
  │   │   └─ NO: execute_external()
  │   │         ├─ fork()
  │   │         ├─ find_executable()
  │   │         ├─ env_to_envp()
  │   │         ├─ execve()
  │   │         └─ waitpid()
  │   └─ restore_std_fds()
  │
  └─ IF AST_PIPELINE (cmd1 | cmd2 | cmd3):
      ├─ create_pipes()
      ├─ Loop through commands:
      │   ├─ fork() for each command
      │   ├─ redirect_io() (pipe setup)!
      │   ├─ close_pipes() in child
      │   ├─ ast_cmd_to_argv()
      │   ├─ find_executable()
      │   └─ execve()
      ├─ close_pipes() in parent
      └─ waitpid() for all children
  ↓
Return exit_status
  ↓
Update shell->last_status
Store in $? for next expansion

Execution with example:
User types: echo $? | cat
  ↓
LEXER/PARSER
  ↓
AST_PIPELINE created:
  ├─ cmd[0]: echo $?
  └─ cmd[1]: cat
  ↓
EXPANDER
  ├─ expand_ast_node(ast, env, last_status=0)
  └─ Replaces $? with "0"
  ↓
AST_PIPELINE (expanded):
  ├─ cmd[0]: echo 0
  └─ cmd[1]: cat
  ↓
EXECUTOR: execute_ast(ast, shell)
  ├─ Check: ast->type == AST_PIPELINE ✓
  ├─ Call: execute_pipeline(ast, shell)
  │   ├─ create_pipes() → [pipe_fd[0], pipe_fd[1]]
  │   │
  │   ├─ FORK child 1 (echo 0):
  │   │   ├─ redirect_io() → stdout to pipe write end
  │   │   ├─ close_pipes() → close all pipe FDs
  │   │   ├─ argv = ["echo", "0", NULL]
  │   │   ├─ is_builtin_cmd("echo") → YES
  │   │   └─ execute_command() → builtin_echo()
  │   │
  │   ├─ FORK child 2 (cat):
  │   │   ├─ redirect_io() → stdin from pipe read end
  │   │   ├─ close_pipes() → close all pipe FDs
  │   │   ├─ argv = ["cat", NULL]
  │   │   ├─ is_builtin_cmd("cat") → NO
  │   │   ├─ find_executable("cat") → "/bin/cat"
  │   │   ├─ env_to_envp(env) → envp array
  │   │   └─ execve("/bin/cat", argv, envp)
  │   │
  │   ├─ PARENT: close_pipes()
  │   └─ PARENT: waitpid() for both children → status=0
  │
  └─ Return: 0
  ↓
shell.last_status = 0  // Update $?
  ↓
Next command can use $? (value 0)
