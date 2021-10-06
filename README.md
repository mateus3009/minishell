# minishell
A 42 project

## O que falta fazer?
**last updated: 2021-10-05**

### 42

- Norma

### Builtin

- cd (change old_pwd and pwd variables)
- unset
- export
- cd, unset, export e exit não podem funcionar na pipeline

### Parser

- Melhorar lógica
- Processar local variables token e adicionar ao g_minishell
- setar local variables

### Redirect

- Executar Heredoc como um processo filho (escutando sinais)
- Não usar fork para executar os redirects (usar apenas dup2)
