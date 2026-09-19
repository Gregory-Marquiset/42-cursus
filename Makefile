# Raccourcis vers ./cursus — `make` ouvre le portail web, `make <projet> ARGS="..."` lance un projet
.DEFAULT_GOAL := portal
PROJECTS := libft ft_printf gnl push_swap minitalk fdf philo minishell cub3d cpp webserv \
            inception transcendence cloud-1
.PHONY: portal menu status stop stop-all clean help $(PROJECTS)

portal:      ; @./cursus
menu:        ; @./cursus menu
$(PROJECTS): ; @./cursus $@ $(ARGS)
status:      ; @./cursus status
stop:        ; @./cursus stop $(STACK)
stop-all:    ; @./cursus stop-all
clean:       ; @./cursus clean
help:        ; @./cursus help
