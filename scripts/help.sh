#!/bin/bash

HELP_MESSAGE=(
	"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
	"=-=-=-=-=  Facilite ton analyse des activités ;)  =-=-=-=-="
	"=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
	"Usage: actan [OPTIONS]"
	""
	"Options:"
	"  -h, --help          show this help message"
)

show_help() {
	for l in "${HELP_MESSAGE[@]}"; do
		echo "$l"
	done
}
