#	gcc -D GENERATE_INCLUDE_LOGS -g filter.c log2uml.c parse_log.c -o ../../parse_log

parse_log: parse_log.c filter_list.h log2uml.c
	gcc -g filter.c parse_log.c -o ../../parse_log

seq_diag:  generate_seq_diagram.c filter.c log2uml.c filter_list.h
	gcc -g filter.c log2uml.c generate_seq_diagram.c -o ../../seq_diag

all: parse_log seq_diag
