# Raccourcis vers ./cursus — `make` ouvre le menu
.DEFAULT_GOAL := menu
.PHONY: menu philo cpp webserv inception transcendence cloud-1 status stop clean help

menu:          ; @./cursus
philo:         ; @./cursus philo $(ARGS)
cpp:           ; @./cursus cpp $(ARGS)
webserv:       ; @./cursus webserv $(ARGS)
inception:     ; @./cursus inception
transcendence: ; @./cursus transcendence
cloud-1:       ; @./cursus cloud-1
status:        ; @./cursus status
stop:          ; @./cursus stop $(STACK)
clean:         ; @./cursus clean
help:          ; @./cursus help
